// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusItemPickup.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NexusInventoryComponent.h"
#include "NexusItemDefinition.h"
#include "NexusItemInstance.h"
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
		// Save reload path: this pickup was already taken in a prior session.
		Destroy();
		return;
	}

	if (Interactable)
	{
		Interactable->OnInteractionEnded.AddDynamic(this, &ANexusItemPickup::HandleInteractionCompleted);
	}
}

void ANexusItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Editor + runtime: keep the preview mesh in sync with the assigned Definition
	// so designers can see what they're placing without entering PIE.
	if (!Mesh) return;

	UStaticMesh* Resolved = nullptr;
	if (Definition && !Definition->PickupMesh.IsNull())
	{
		Resolved = Definition->PickupMesh.LoadSynchronous();
	}
	Mesh->SetStaticMesh(Resolved);
}

#if WITH_EDITOR
void ANexusItemPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// CDO / archetype edits trigger PostEditChangeProperty too. RerunConstructionScripts
	// is undefined on those (no world, no proper actor lifecycle) and crashes — bail out
	// and let the change propagate to any real instances normally.
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

	// Single-player fallback: route to the local player pawn.
	if (const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		return PlayerPawn->FindComponentByClass<UNexusInventoryComponent>();
	}
	return nullptr;
}

void ANexusItemPickup::HandleInteractionCompleted()
{
	if (bWasCollected || !Definition) return;

	UNexusInventoryComponent* Inventory = ResolveInventory(/*Interactor*/ nullptr);
	if (!Inventory) return;

	int32 Remainder = 0;
	UNexusItemInstance* AddedInstance = Inventory->AddItem(Definition, InitialCount, Remainder);

	// Apply any authored stat-tag overrides (half-empty pickup, low durability...).
	if (AddedInstance)
	{
		for (const TPair<FGameplayTag, int32>& Pair : InitialStatTags)
		{
			AddedInstance->SetStat(Pair.Key, Pair.Value);
		}
	}

	const int32 Taken = InitialCount - Remainder;
	if (Taken > 0)
	{
		bWasCollected = true;
		Destroy();
	}
}

void ANexusItemPickup::ActorLoaded_Implementation()
{
	if (bWasCollected)
	{
		Destroy();
	}
}