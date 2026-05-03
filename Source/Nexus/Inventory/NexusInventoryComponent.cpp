#include "NexusInventoryComponent.h"

#include "EMSData.h"
#include "EMSFunctionLibrary.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Stackable/NexusFragment_Stackable.h"

namespace
{
	float GetWeightContribution(const UNexusItemInstance* Instance)
	{
		if (!Instance) return 0.0f;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		return Def ? Def->Weight * Instance->GetStackCount() : 0.0f;
	}
}

UNexusInventoryComponent::UNexusInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Add/Remove
FNexusAddItemResult UNexusInventoryComponent::AddItem(UNexusItemDefinition* Definition, int32 Count)
{
	FNexusAddItemResult Result;
	if (!Definition || Count <= 0)
	{
		Result.Remainder = FMath::Max(0, Count);
		return Result;
	}

	const int32 OriginalCount = Count;

	if (WeightCapacity > 0.0f && Definition->Weight > 0.0f)
	{
		const float Available     = WeightCapacity - GetUsedWeight();
		const int32 MaxByWeight   = Available > 0.0f
			? FMath::FloorToInt(Available / Definition->Weight)
			: 0;
		Count = FMath::Min(Count, MaxByWeight);
	}

	Count = FMath::Min(Count, MaxItemsPerAddCall);

	if (Count <= 0)
	{
		Result.Remainder = OriginalCount;
		return Result;
	}

	const int32 MaxStack = GetMaxStackForDefinition(Definition);

	FBroadcastScope Scope(this);

	int32 Placed = 0;

	if (MaxStack > 1)
	{
		TArray<UNexusItemInstance*> Snapshot;
		Snapshot.Reserve(Items.Num());
		for (UNexusItemInstance* I : Items) { Snapshot.Add(I); }

		for (UNexusItemInstance* Existing : Snapshot)
		{
			const int32 Remaining = Count - Placed;
			if (Remaining <= 0) break;
			if (!Existing || Existing->GetDefinition() != Definition) continue;
			if (Existing->GetStackCount() >= MaxStack) continue;
			if (Existing->GetStatTags().Num() > 0) continue;

			const int32 Applied = Existing->ModifyStack(Remaining, MaxStack);
			if (Applied > 0)
			{
				Placed += Applied;
				CachedUsedWeight += Applied * Definition->Weight;
				Result.AffectedInstances.Add(Existing);
				EnqueueChange(Existing, false, false);
			}
		}
	}

	while (Placed < Count)
	{
		if (SlotCapacity > 0 && Items.Num() >= SlotCapacity) break;

		const int32 Remaining = Count - Placed;
		const int32 ToPlace   = FMath::Min(Remaining, MaxStack);

		UNexusItemInstance* NewInstance = NewObject<UNexusItemInstance>(this);
		NewInstance->Initialize(Definition, ToPlace);
		Items.Add(NewInstance);
		BindInstance(NewInstance);

		Placed += ToPlace;
		CachedUsedWeight += ToPlace * Definition->Weight;
		Result.AffectedInstances.Add(NewInstance);
		Result.NewInstances.Add(NewInstance);
		EnqueueChange(NewInstance, true, false);
	}

	Result.AmountAdded = Placed;
	Result.Remainder   = OriginalCount - Placed;
	return Result;
}

bool UNexusInventoryComponent::AddInstance(UNexusItemInstance* Instance)
{
	if (!Instance || !Instance->GetDefinition()) return false;
	if (Items.Contains(Instance)) return false;
	if (SlotCapacity > 0 && Items.Num() >= SlotCapacity) return false;

	if (WeightCapacity > 0.0f)
	{
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		const float Adding = Def->Weight * Instance->GetStackCount();
		if (Adding > 0.0f && GetUsedWeight() + Adding > WeightCapacity)
		{
			return false;
		}
	}

	FBroadcastScope Scope(this);

	if (Instance->GetOuter() != this)
	{
		Instance->Rename(nullptr, this, REN_DontCreateRedirectors);
	}
	Items.Add(Instance);
	BindInstance(Instance);
	CachedUsedWeight += GetWeightContribution(Instance);
	EnqueueChange(Instance, true, false);
	return true;
}

bool UNexusInventoryComponent::RemoveInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return false;

	FBroadcastScope Scope(this);

	const float Contribution = GetWeightContribution(Instance);
	const int32 Removed = Items.Remove(Instance);
	if (Removed > 0)
	{
		UnbindInstance(Instance);
		CachedUsedWeight = FMath::Max(0.0f, CachedUsedWeight - Contribution);
		EnqueueChange(Instance, false, true);
		return true;
	}
	
	return false;
}

void UNexusInventoryComponent::ClearAll()
{
	if (Items.Num() == 0) return;

	FBroadcastScope Scope(this);

	TArray<TObjectPtr<UNexusItemInstance>> Removed = MoveTemp(Items);
	CachedUsedWeight = 0.0f;

	for (UNexusItemInstance* Instance : Removed)
	{
		UnbindInstance(Instance);
		EnqueueChange(Instance, false, true);
	}
}

int32 UNexusInventoryComponent::RemoveFromInstance(UNexusItemInstance* Instance, int32 Count)
{
	if (!Instance || Count <= 0 || !Items.Contains(Instance)) return 0;

	FBroadcastScope Scope(this);

	const UNexusItemDefinition* Def = Instance->GetDefinition();
	const float UnitWeight = Def ? Def->Weight : 0.0f;

	const int32 Removed = -Instance->ModifyStack(-Count);
	CachedUsedWeight = FMath::Max(0.0f, CachedUsedWeight - Removed * UnitWeight);

	if (Instance->IsEmpty())
	{
		UnbindInstance(Instance);
		Items.RemoveSingle(Instance);
		EnqueueChange(Instance, false, true);
	}
	else if (Removed > 0)
	{
		EnqueueChange(Instance, false, false);
	}
	return Removed;
}


// Broadcast
void UNexusInventoryComponent::EnqueueChange(UNexusItemInstance* Instance, const bool bAdded, const bool bRemoved) 
{
	PendingChanges.Add({ Instance, bAdded, bRemoved });
}

void UNexusInventoryComponent::FlushPendingChanges()
{
	if (bFlushInProgress) return;
	if (PendingChanges.Num() == 0) return;

	TGuardValue InProgress(bFlushInProgress, true);

	while (PendingChanges.Num() > 0)
	{
		TArray<FPendingChange> ToFire = MoveTemp(PendingChanges);
		PendingChanges.Reset();

		bool bAnyChange = false;
		for (const FPendingChange& Change : ToFire)
		{
			UNexusItemInstance* Inst = Change.Instance.Get();
			if (!Inst) continue;

			if (Change.bAdded)        OnItemAdded.Broadcast(Inst);
			else if (Change.bRemoved) OnItemRemoved.Broadcast(Inst);
			else                      OnItemChanged.Broadcast(Inst);
			bAnyChange = true;
		}

		if (bAnyChange) OnInventoryChanged.Broadcast();
	}
}

void UNexusInventoryComponent::BindInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return;
	Instance->OnInstanceChanged.AddUniqueDynamic(this, &UNexusInventoryComponent::HandleInstanceChanged);
}

void UNexusInventoryComponent::UnbindInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return;
	Instance->OnInstanceChanged.RemoveDynamic(this, &UNexusInventoryComponent::HandleInstanceChanged);
}

void UNexusInventoryComponent::HandleInstanceChanged(UNexusItemInstance* Instance)
{
	if (!Instance || !Items.Contains(Instance)) return;
	
	FBroadcastScope Scope(this);
	EnqueueChange(Instance, false, false);
}

// Utility
int32 UNexusInventoryComponent::GetTotalCountForDefinition(const UNexusItemDefinition* Definition) const
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

UNexusItemInstance* UNexusInventoryComponent::FindFirstByDefinition(const UNexusItemDefinition* Definition) const
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

int32 UNexusInventoryComponent::GetMaxStackForDefinition(const UNexusItemDefinition* Definition)
{
	if (!Definition) return 1;
	if (const FNexusFragment_Stackable* Stack = Definition->FindFragment<FNexusFragment_Stackable>())
	{
		return FMath::Max(1, Stack->MaxStackSize);
	}
	return 1;
}


// Capacity
float UNexusInventoryComponent::GetUsedWeight() const
{
	return CachedUsedWeight;
}


// Save
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

void UNexusInventoryComponent::ComponentLoaded_Implementation()
{
	CachedUsedWeight = 0.0f;
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;

		const FString Key = FString::Printf(TEXT("InventoryItem_%s"),
			*Instance->GetInstanceGuid().ToString(EGuidFormats::DigitsWithHyphens));

		UEMSFunctionLibrary::LoadRawObject(GetOwner(), FRawObjectSaveData{ Instance, Key });
		Instance->RestoreLoadedState();

		BindInstance(Instance);
		if (const UNexusItemDefinition* Def = Instance->GetDefinition())
		{
			CachedUsedWeight += Def->Weight * Instance->GetStackCount();
		}
	}

	OnInventoryChanged.Broadcast();
}