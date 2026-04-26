// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusInventoryComponent.h"

#include "EMSData.h"
#include "EMSFunctionLibrary.h"
#include "NexusItemDefinition.h"
#include "NexusItemInstance.h"
#include "Fragments/NexusFragment_KeyItem.h"
#include "Fragments/NexusFragment_Stackable.h"

UNexusInventoryComponent::UNexusInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ---------------- Add / Remove ----------------

UNexusItemInstance* UNexusInventoryComponent::AddItem(UNexusItemDefinition* Definition, int32 Count, int32& OutRemainder)
{
	OutRemainder = Count;
	if (!Definition || Count <= 0) return nullptr;

	const int32 MaxStack = GetMaxStackForDefinition(Definition);
	UNexusItemInstance* Result = nullptr;

	// 1. Top up existing stacks first.
	if (MaxStack > 1)
	{
		for (UNexusItemInstance* Existing : Items)
		{
			if (OutRemainder <= 0) break;
			if (!Existing || Existing->GetDefinition() != Definition) continue;
			if (Existing->GetStackCount() >= MaxStack) continue;

			const int32 Applied = Existing->ModifyStack(OutRemainder, MaxStack);
			if (Applied > 0)
			{
				OutRemainder -= Applied;
				Result        = Existing;
				BroadcastChange(Existing, /*bAdded*/false, /*bRemoved*/false);
			}
		}
	}

	// 2. Spawn new instances for the leftover.
	while (OutRemainder > 0)
	{
		if (SlotCapacity > 0 && Items.Num() >= SlotCapacity) break;

		UNexusItemInstance* NewInstance = NewObject<UNexusItemInstance>(this);
		const int32 ToPlace             = FMath::Min(OutRemainder, MaxStack);
		NewInstance->Initialize(Definition, ToPlace);
		Items.Add(NewInstance);
		OutRemainder -= ToPlace;
		Result        = NewInstance;
		BroadcastChange(NewInstance, /*bAdded*/true, /*bRemoved*/false);
	}

	return Result;
}

bool UNexusInventoryComponent::AddInstance(UNexusItemInstance* Instance)
{
	if (!Instance || !Instance->GetDefinition()) return false;
	if (SlotCapacity > 0 && Items.Num() >= SlotCapacity) return false;

	Instance->Rename(nullptr, this);
	Items.Add(Instance);
	BroadcastChange(Instance, /*bAdded*/true, /*bRemoved*/false);
	return true;
}

int32 UNexusInventoryComponent::RemoveFromInstance(UNexusItemInstance* Instance, int32 Count)
{
	if (!Instance || Count <= 0 || !Items.Contains(Instance)) return 0;

	const int32 Removed = -Instance->ModifyStack(-Count);
	if (Instance->IsEmpty())
	{
		RemoveInstance(Instance);
	}
	else
	{
		BroadcastChange(Instance, /*bAdded*/false, /*bRemoved*/false);
	}
	return Removed;
}

bool UNexusInventoryComponent::RemoveInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return false;
	const int32 Removed = Items.Remove(Instance);
	if (Removed > 0)
	{
		BroadcastChange(Instance, /*bAdded*/false, /*bRemoved*/true);
		return true;
	}
	return false;
}

void UNexusInventoryComponent::ClearAll()
{
	// Snapshot then clear so listeners that re-query the inventory during the
	// broadcast see the post-clear state, not a half-emptied array.
	TArray<TObjectPtr<UNexusItemInstance>> Removed = MoveTemp(Items);
	Items.Reset();

	for (UNexusItemInstance* Instance : Removed)
	{
		BroadcastChange(Instance, /*bAdded*/false, /*bRemoved*/true);
	}
}

// ---------------- Queries ----------------

int32 UNexusInventoryComponent::GetTotalCountForDefinition(UNexusItemDefinition* Definition) const
{
	if (!Definition) return 0;
	int32 Total = 0;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetDefinition() == Definition)
		{
			Total += Instance->GetStackCount();
		}
	}
	return Total;
}

int32 UNexusInventoryComponent::GetTotalCountForIdentityTag(FGameplayTag IdentityTag) const
{
	if (!IdentityTag.IsValid()) return 0;
	int32 Total = 0;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetIdentityTag().MatchesTagExact(IdentityTag))
		{
			Total += Instance->GetStackCount();
		}
	}
	return Total;
}

int32 UNexusInventoryComponent::GetTotalCountForCategory(FGameplayTag CategoryTag) const
{
	if (!CategoryTag.IsValid()) return 0;
	int32 Total = 0;
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (Def && Def->CategoryTags.HasTag(CategoryTag))
		{
			Total += Instance->GetStackCount();
		}
	}
	return Total;
}

UNexusItemInstance* UNexusInventoryComponent::FindFirstByDefinition(UNexusItemDefinition* Definition) const
{
	if (!Definition) return nullptr;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetDefinition() == Definition) return Instance;
	}
	return nullptr;
}

UNexusItemInstance* UNexusInventoryComponent::FindFirstByIdentityTag(FGameplayTag IdentityTag) const
{
	if (!IdentityTag.IsValid()) return nullptr;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetIdentityTag().MatchesTagExact(IdentityTag)) return Instance;
	}
	return nullptr;
}

bool UNexusInventoryComponent::HasItemWithUnlockTag(FGameplayTag UnlockTag) const
{
	if (!UnlockTag.IsValid()) return false;
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (!Def) continue;
		if (const FNexusFragment_KeyItem* Key = Def->FindFragment<FNexusFragment_KeyItem>())
		{
			if (Key->UnlockTag.MatchesTagExact(UnlockTag)) return true;
		}
	}
	return false;
}

// ---------------- Capacity ----------------

float UNexusInventoryComponent::GetUsedWeight() const
{
	float Used = 0.0f;
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (Def) Used += Def->Weight * Instance->GetStackCount();
	}
	return Used;
}

// ---------------- Internals ----------------

int32 UNexusInventoryComponent::GetMaxStackForDefinition(const UNexusItemDefinition* Definition) const
{
	if (!Definition) return 1;
	if (const FNexusFragment_Stackable* Stack = Definition->FindFragment<FNexusFragment_Stackable>())
	{
		return FMath::Max(1, Stack->MaxStackSize);
	}
	return 1;
}

void UNexusInventoryComponent::BroadcastChange(UNexusItemInstance* Instance, bool bAdded, bool bRemoved)
{
	if (bAdded)        OnItemAdded.Broadcast(Instance);
	else if (bRemoved) OnItemRemoved.Broadcast(Instance);
	else               OnItemChanged.Broadcast(Instance);

	OnInventoryChanged.Broadcast();
}

// ---------------- Save ----------------

void UNexusInventoryComponent::ComponentPreSave_Implementation()
{
}

void UNexusInventoryComponent::ComponentSaved_Implementation()
{
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const FString Key = FString::Printf(TEXT("InventoryItem_%s"),
			*Instance->GetInstanceGuid().ToString(EGuidFormats::DigitsWithHyphens));
		UEMSFunctionLibrary::SaveRawObject(GetOwner(), FRawObjectSaveData{ Instance, Key });
	}
}

void UNexusInventoryComponent::ComponentPreLoad_Implementation()
{
}

void UNexusInventoryComponent::ComponentLoaded_Implementation()
{
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const FString Key = FString::Printf(TEXT("InventoryItem_%s"),
			*Instance->GetInstanceGuid().ToString(EGuidFormats::DigitsWithHyphens));
		UEMSFunctionLibrary::LoadRawObject(GetOwner(), FRawObjectSaveData{ Instance, Key });
	}

	OnInventoryChanged.Broadcast();
}