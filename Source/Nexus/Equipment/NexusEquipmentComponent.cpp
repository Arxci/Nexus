// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusEquipmentComponent.h"

#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "NexusEquippedActor.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/NexusFragment_Equippable.h"

UNexusEquipmentComponent::UNexusEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// React to inventory mutations so a dropped/destroyed item can't leave us
	// holding a dangling slot pointer with abilities still granted.
	if (UNexusInventoryComponent* Inv = GetInventory())
	{
		Inv->OnItemRemoved.AddDynamic(this, &UNexusEquipmentComponent::HandleInventoryItemRemoved);
	}
}

void UNexusEquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UNexusInventoryComponent* Inv = GetInventory())
	{
		Inv->OnItemRemoved.RemoveDynamic(this, &UNexusEquipmentComponent::HandleInventoryItemRemoved);
	}

	UnequipAll();
	Super::EndPlay(EndPlayReason);
}

void UNexusEquipmentComponent::HandleInventoryItemRemoved(UNexusItemInstance* RemovedInstance)
{
	if (!RemovedInstance) return;

	// Walk a snapshot — UnequipSlot mutates EquippedSlots.
	TArray<TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>> Snapshot;
	Snapshot.Reserve(EquippedSlots.Num());
	for (const TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>& Pair : EquippedSlots)
	{
		Snapshot.Add(Pair);
	}

	for (const TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>& Pair : Snapshot)
	{
		if (Pair.Value == RemovedInstance)
		{
			UnequipSlot(Pair.Key);
		}
	}
}

UNexusAbilitySystemComponent* UNexusEquipmentComponent::GetASC() const
{
	if (const INexusAbilitySystemInterface* ASCOwner = Cast<INexusAbilitySystemInterface>(GetOwner()))
	{
		return ASCOwner->GetNexusAbilitySystemComponent();
	}
	return nullptr;
}

UNexusInventoryComponent* UNexusEquipmentComponent::GetInventory() const
{
	return GetOwner() ? GetOwner()->FindComponentByClass<UNexusInventoryComponent>() : nullptr;
}

// ---------------- Lifecycle ----------------

bool UNexusEquipmentComponent::EquipInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return false;
	const UNexusItemDefinition* Def = Instance->GetDefinition();
	if (!Def) return false;

	const FNexusFragment_Equippable* Eq = Def->FindFragment<FNexusFragment_Equippable>();
	if (!Eq || !Eq->SlotTag.IsValid()) return false;

	const FGameplayTag SlotTag = Eq->SlotTag;

	if (IsSlotOccupied(SlotTag))
	{
		UnequipSlot(SlotTag);
	}

	EquippedSlots.Add(SlotTag, Instance);
	ApplyEquipEffects(SlotTag, Instance);

	OnEquipped.Broadcast(SlotTag, Instance);

	if (!ActiveSlot.IsValid())
	{
		SetActiveSlot(SlotTag);
	}
	return true;
}

UNexusItemInstance* UNexusEquipmentComponent::TryEquipFirstCompatibleForSlot(FGameplayTag SlotTag)
{
	if (!SlotTag.IsValid()) return nullptr;

	// Already equipped → no-op.
	if (UNexusItemInstance* Existing = GetEquippedInSlot(SlotTag))
	{
		return Existing;
	}

	UNexusInventoryComponent* Inv = GetInventory();
	if (!Inv) return nullptr;

	for (UNexusItemInstance* Inst : Inv->GetItems())
	{
		if (!Inst) continue;
		const UNexusItemDefinition* Def = Inst->GetDefinition();
		if (!Def) continue;

		const FNexusFragment_Equippable* Eq = Def->FindFragment<FNexusFragment_Equippable>();
		if (!Eq) continue;
		if (!Eq->SlotTag.MatchesTagExact(SlotTag)) continue;

		return EquipInstance(Inst) ? Inst : nullptr;
	}
	return nullptr;
}

bool UNexusEquipmentComponent::UnequipSlot(FGameplayTag SlotTag)
{
	UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
	if (!Instance) return false;

	RemoveEquipEffects(SlotTag);
	EquippedSlots.Remove(SlotTag);

	OnUnequipped.Broadcast(SlotTag, Instance);

	if (ActiveSlot.MatchesTagExact(SlotTag))
	{
		ActiveSlot = FGameplayTag();
		OnActiveSlotChanged.Broadcast(ActiveSlot, nullptr);
	}
	return true;
}

void UNexusEquipmentComponent::UnequipAll()
{
	TArray<FGameplayTag> Slots;
	EquippedSlots.GetKeys(Slots);
	for (const FGameplayTag& Slot : Slots)
	{
		UnequipSlot(Slot);
	}
}

// ---------------- Queries ----------------

UNexusItemInstance* UNexusEquipmentComponent::GetEquippedInSlot(FGameplayTag SlotTag) const
{
	return EquippedSlots.FindRef(SlotTag);
}

ANexusEquippedActor* UNexusEquipmentComponent::GetEquippedActorInSlot(FGameplayTag SlotTag) const
{
	return SpawnedActors.FindRef(SlotTag);
}

bool UNexusEquipmentComponent::IsSlotOccupied(FGameplayTag SlotTag) const
{
	return EquippedSlots.Contains(SlotTag);
}

void UNexusEquipmentComponent::SetActiveSlot(FGameplayTag SlotTag)
{
	if (ActiveSlot.MatchesTagExact(SlotTag)) return;
	if (SlotTag.IsValid() && !EquippedSlots.Contains(SlotTag)) return;

	ActiveSlot = SlotTag;
	OnActiveSlotChanged.Broadcast(ActiveSlot, GetEquippedInSlot(ActiveSlot));
}

UNexusItemInstance* UNexusEquipmentComponent::GetActiveInstance() const
{
	return GetEquippedInSlot(ActiveSlot);
}

// ---------------- Effects ----------------

void UNexusEquipmentComponent::ApplyEquipEffects(FGameplayTag SlotTag, UNexusItemInstance* Instance)
{
	const UNexusItemDefinition* Def = Instance ? Instance->GetDefinition() : nullptr;
	if (!Def) return;

	const FNexusFragment_Equippable* Eq = Def->FindFragment<FNexusFragment_Equippable>();
	if (!Eq) return;

	// 1. Spawn the visible actor.
	UClass* ActorClass = Eq->EquippedActorClass.LoadSynchronous();
	if (!ActorClass) ActorClass = ANexusEquippedActor::StaticClass();

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters Params;
		Params.Owner                          = GetOwner();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ANexusEquippedActor* Spawned          = World->SpawnActor<ANexusEquippedActor>(ActorClass, Params);
		if (Spawned)
		{
			if (const ACharacter* Char = Cast<ACharacter>(GetOwner()))
			{
				Spawned->AttachToComponent(Char->GetMesh(),
					FAttachmentTransformRules::SnapToTargetNotIncludingScale, Eq->AttachSocket);
			}
			Spawned->InitializeFromInstance(Instance);
			SpawnedActors.Add(SlotTag, Spawned);
		}
	}

	// 2. Grant abilities.
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		TArray<TSubclassOf<UNexusAbility>>& Granted = AppliedAbilitiesBySlot.FindOrAdd(SlotTag);
		for (const TSubclassOf<UNexusAbility>& AbilityClass : Eq->GrantedAbilities)
		{
			if (AbilityClass && ASC->GiveAbility(AbilityClass))
			{
				Granted.Add(AbilityClass);
			}
		}

		// 3. Push owned tags.
		FGameplayTagContainer Pushed;
		Pushed.AddTag(SlotTag);
		Pushed.AppendTags(Eq->OwnedTagsWhileEquipped);
		for (const FGameplayTag& Tag : Pushed)
		{
			ASC->AddLooseGameplayTag(Tag);
		}
		AppliedTagsBySlot.Add(SlotTag, Pushed);
	}
}

void UNexusEquipmentComponent::RemoveEquipEffects(FGameplayTag SlotTag)
{
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		if (TArray<TSubclassOf<UNexusAbility>>* Granted = AppliedAbilitiesBySlot.Find(SlotTag))
		{
			for (const TSubclassOf<UNexusAbility>& AbilityClass : *Granted)
			{
				ASC->TryDeactivateAbilityByClass(AbilityClass);
				ASC->RemoveAbility(AbilityClass);
			}
		}
		AppliedAbilitiesBySlot.Remove(SlotTag);

		if (FGameplayTagContainer* Tags = AppliedTagsBySlot.Find(SlotTag))
		{
			for (const FGameplayTag& Tag : *Tags)
			{
				ASC->RemoveLooseGameplayTag(Tag);
			}
		}
		AppliedTagsBySlot.Remove(SlotTag);
	}

	if (TObjectPtr<ANexusEquippedActor> Actor = SpawnedActors.FindRef(SlotTag))
	{
		Actor->Destroy();
	}
	SpawnedActors.Remove(SlotTag);
}

// ---------------- Save ----------------

void UNexusEquipmentComponent::ComponentPreSave_Implementation()
{
}

void UNexusEquipmentComponent::ComponentSaved_Implementation()
{
}

void UNexusEquipmentComponent::ComponentPreLoad_Implementation()
{
	UnequipAll();
}

void UNexusEquipmentComponent::ComponentLoaded_Implementation()
{
	TArray<FGameplayTag> Slots;
	EquippedSlots.GetKeys(Slots);
	for (const FGameplayTag& SlotTag : Slots)
	{
		if (UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag))
		{
			ApplyEquipEffects(SlotTag, Instance);
		}
	}

	if (ActiveSlot.IsValid())
	{
		OnActiveSlotChanged.Broadcast(ActiveSlot, GetEquippedInSlot(ActiveSlot));
	}
}