#include "NexusItemPickup.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/AssetManager.h"

#include "GameFramework/Pawn.h"

#include "Kismet/GameplayStatics.h"

#include "TimerManager.h"

#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"

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
		AssetId, TArray<FName>{ TEXT("Pickup") },
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

void ANexusItemPickup::HandleInteractionCompleted(AActor* Interactor)
{
	if (bWasCollected || !Definition) return;

	APawn* Pawn = Cast<APawn>(Interactor);
	if (!Pawn)
	{
		// Fall back to the local player pawn — the interaction system passes a
		// hero character today, but a future AI-driven interaction might pass
		// something else. Either way, no pawn = no acquire.
		Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	}
	if (!Pawn) return;

	const FNexusAcquireResult Result = UNexusInventoryAcquireLibrary::AcquireItem(
		Pawn, Definition, InitialCount, bAutoEquipOnPickup, bSkipCeremony, InitialStatTags);

	if (Result.AmountAdded <= 0) return;

	// Partial placement (weight / slot cap) leaves the remainder visible so the
	// player can interact again after dropping something. No teardown — the
	// world model should stay until the pickup actually fully empties.
	if (Result.Remainder > 0)
	{
		InitialCount = Result.Remainder;
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
