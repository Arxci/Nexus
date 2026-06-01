#include "NexusItemPickup.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/AssetManager.h"

#include "TimerManager.h"
#include "Nexus/NexusAssetManager.h"

#include "Nexus/Nexus.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/Interaction/NexusInteraction.h"
#include "Nexus/Interaction/NexusInteractionCondition.h"
#include "Nexus/Interaction/NexusInteractionEffect.h"

ANexusItemPickup::ANexusItemPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Interactable = CreateDefaultSubobject<UNexusInteractableComponent>(TEXT("Interactable"));
}

void ANexusItemPickup::BeginPlay()
{
	Super::BeginPlay();

	if (bWasCollected)
	{
		Destroy();
		return;
	}

	RequestPickupMeshLoad();

	if (Interactable)
	{
		Interactable->OnInteractionCompleted.AddDynamic(this, &ANexusItemPickup::HandleInteractionCompleted);
	}

	ConfigureInteraction();
}

void ANexusItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PickupMeshHandle.IsValid())
	{
		PickupMeshHandle->CancelHandle();
		PickupMeshHandle.Reset();
	}

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PickupTeardownTimer);
	}

	Super::EndPlay(EndPlayReason);
}

void ANexusItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!Mesh) return;

#if WITH_EDITOR
	if (Definition && !Definition->PickupMesh.IsNull())
	{
		Mesh->SetStaticMesh(Definition->PickupMesh.LoadSynchronous());
	}
#endif
}

#if WITH_EDITOR
void ANexusItemPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)) return;

	const FName PropName = PropertyChangedEvent.GetPropertyName();
	if (PropName == GET_MEMBER_NAME_CHECKED(ANexusItemPickup, Definition))
	{
		RerunConstructionScripts();
	}
}
#endif

void ANexusItemPickup::ConfigurePickup(UNexusItemDefinition* InDefinition, int32 InCount)
{
	Definition   = InDefinition;
	InitialCount = FMath::Max(1, InCount);
	RequestPickupMeshLoad();
	ConfigureInteraction();
}

void ANexusItemPickup::RequestPickupMeshLoad()
{
	if (!Mesh || !Definition || Definition->PickupMesh.IsNull()) return;
	if (Mesh->GetStaticMesh()) return;
	if (PickupMeshHandle.IsValid() && !PickupMeshHandle->HasLoadCompleted()) return;

	const FPrimaryAssetId AssetId = Definition->GetPrimaryAssetId();
	if (!AssetId.IsValid()) return;

	TWeakObjectPtr<ANexusItemPickup> WeakSelf(this);
	UAssetManager& AM = UAssetManager::Get();
	PickupMeshHandle = AM.LoadPrimaryAsset(
		AssetId, TArray<FName>{ UNexusAssetManager::BundlePickup },
		FStreamableDelegate::CreateLambda([WeakSelf]()
		{
			ANexusItemPickup* Self = WeakSelf.Get();
			if (!Self || !Self->Mesh || !Self->Definition) return;
			if (Self->Mesh->GetStaticMesh()) return;
			if (UStaticMesh* Loaded = Self->Definition->PickupMesh.Get())
			{
				Self->Mesh->SetStaticMesh(Loaded);
			}
		}));
}

void ANexusItemPickup::ConfigureInteraction()
{
	if (!Interactable || !Definition) return;

	// Reskin: the pickup is data on the generic component. It authors a single
	// "Take" interaction — gated on inventory space, giving the item through the
	// canonical acquire façade — instead of hand-coding the acquire in C++.
	FNexusInteraction Entry;
	Entry.Verb = NexusGameplayTags::Interaction_Verb_PickUp;
	Entry.HoldDuration = PickupHoldDuration;

	// Gate on at least one cell free; partial pickups still take what fits and
	// leave the remainder (handled in HandleInteractionCompleted).
	TInstancedStruct<FNexusInteractionCondition> SpaceGate;
	SpaceGate.InitializeAs<FNexusInteractionCondition_RequiresFreeSpace>();
	SpaceGate.GetMutable<FNexusInteractionCondition_RequiresFreeSpace>().Definition = Definition;
	Entry.Conditions.Add(MoveTemp(SpaceGate));

	// Pick Up IS a GiveItem effect — identical auto-equip / ceremony / stat-seed
	// behaviour as the previous hand-coded path, now expressed as data.
	TInstancedStruct<FNexusInteractionEffect> GiveStruct;
	GiveStruct.InitializeAs<FNexusInteractionEffect_GiveItem>();
	FNexusInteractionEffect_GiveItem& Give = GiveStruct.GetMutable<FNexusInteractionEffect_GiveItem>();
	Give.Definition = Definition;
	Give.Count = InitialCount;
	Give.bAutoEquipIfPossible = bAutoEquipOnPickup;
	Give.bSkipCeremony = bSkipCeremony;
	Give.InitialStatTags = InitialStatTags;
	Entry.Effects.Add(MoveTemp(GiveStruct));

	TArray<FNexusInteraction> List;
	List.Add(MoveTemp(Entry));
	Interactable->SetInteractions(MoveTemp(List));
}

void ANexusItemPickup::HandleInteractionCompleted(AActor* Interactor)
{
	if (bWasCollected || !Definition || !Interactable) return;

	// The acquire ran as the entry's GiveItem effect; read back how much landed
	// to decide teardown vs. leaving a remainder.
	const FNexusInteractionResult Result = Interactable->GetLastInteractionResult();
	if (Result.ItemsAdded <= 0) return;

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInventory, Verbose, TEXT("[Pickup] %s acquired %d x %s (remainder=%d)."),
		*GetNameSafe(Interactor), Result.ItemsAdded, *GetNameSafe(Definition), Result.ItemsRemaining);
#endif

	// Partial placement (weight / slot cap) leaves the remainder visible so the
	// player can interact again after dropping something. Rebuild the Take entry
	// for the reduced count; no teardown until the pickup actually fully empties.
	if (Result.ItemsRemaining > 0)
	{
		InitialCount = Result.ItemsRemaining;
		ConfigureInteraction();
		return;
	}

	bWasCollected = true;

	// Hide the world model + drop collision immediately so the player's input
	// reads as "the pickup became my item." Further interaction attempts no-op
	// via the bWasCollected guard at the top. The actor itself sticks around
	// for TeardownDelaySeconds to cover the (async) Equipped-bundle load and
	// the ceremony / unholster anim; without this the player would see a
	// visible gap between the pickup vanishing and the gun appearing in hand.
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	if (TeardownDelaySeconds <= 0.0f)
	{
		Destroy();
		return;
	}

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			PickupTeardownTimer, this,
			&ANexusItemPickup::HandleTeardownComplete,
			TeardownDelaySeconds, /*bLoop*/ false);
	}
	else
	{
		// No world — defensive. Destroy synchronously.
		Destroy();
	}
}

void ANexusItemPickup::HandleTeardownComplete()
{
	Destroy();
}

void ANexusItemPickup::ActorLoaded_Implementation()
{
	if (bWasCollected)
	{
		Destroy();
	}
}
