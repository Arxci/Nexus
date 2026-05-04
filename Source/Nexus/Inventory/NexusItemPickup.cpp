#include "NexusItemPickup.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
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
		Interactable->OnInteractionEnded.AddDynamic(this, &ANexusItemPickup::HandleInteractionCompleted);
	}
}

void ANexusItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PickupMeshHandle.IsValid())
	{
		PickupMeshHandle->CancelHandle();
		PickupMeshHandle.Reset();
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

UNexusInventoryComponent* ANexusItemPickup::ResolveInventory(AActor* Interactor) const
{
	if (Interactor)
	{
		if (UNexusInventoryComponent* Direct = Interactor->FindComponentByClass<UNexusInventoryComponent>())
		{
			return Direct;
		}
	}

	if (const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		return PlayerPawn->FindComponentByClass<UNexusInventoryComponent>();
	}
	
	return nullptr;
}

void ANexusItemPickup::HandleInteractionCompleted(AActor* Interactor)
{
	if (bWasCollected || !Definition) return;

	UNexusInventoryComponent* Inventory = ResolveInventory(Interactor);
	if (!Inventory) return;

	const FNexusAddItemResult AddResult = Inventory->AddItem(Definition, InitialCount);
	
	if (InitialStatTags.Num() > 0)
	{
		for (UNexusItemInstance* New : AddResult.NewInstances)
		{
			if (!New) continue;
			for (const TPair<FGameplayTag, int32>& Pair : InitialStatTags)
			{
				New->SetStat(Pair.Key, Pair.Value);
			}
		}
	}

	if (AddResult.AmountAdded <= 0) return;

	if (AddResult.Remainder > 0)
	{
		InitialCount = AddResult.Remainder;
		return;
	}

	bWasCollected = true;
	Destroy();
}

void ANexusItemPickup::ActorLoaded_Implementation()
{
	if (bWasCollected)
	{
		Destroy();
	}
}