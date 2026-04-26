// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EMSCompSaveInterface.h"
#include "NexusItemDefinition.h"
#include "NexusItemInstance.h"
#include "NexusInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChanged, UNexusItemInstance*, Instance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

/**
 * Owns the player's (or any character's) item instances. Storage only —
 * binding an item to a slot/abilities is the EquipmentComponent's job.
 *
 * Save/restore: Items array and per-instance state are persisted via
 * UEMSFunctionLibrary::SaveRawObject in ComponentSaved/Loaded, mirroring
 * NexusAbilitySystemComponent (NexusAbilitySystemComponent.cpp:399).
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusInventoryComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusInventoryComponent();

	// ---------------- Add / Remove ----------------

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UNexusItemInstance* AddItem(UNexusItemDefinition* Definition, int32 Count, int32& OutRemainder);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInstance(UNexusItemInstance* Instance);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 RemoveFromInstance(UNexusItemInstance* Instance, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveInstance(UNexusItemInstance* Instance);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearAll();

	// ---------------- Queries ----------------

	UFUNCTION(BlueprintPure, Category = "Inventory")
	const TArray<UNexusItemInstance*>& GetItems() const { return Items; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalCountForDefinition(UNexusItemDefinition* Definition) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalCountForIdentityTag(FGameplayTag IdentityTag) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalCountForCategory(FGameplayTag CategoryTag) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UNexusItemInstance* FindFirstByDefinition(UNexusItemDefinition* Definition) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UNexusItemInstance* FindFirstByIdentityTag(FGameplayTag IdentityTag) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool HasItemWithUnlockTag(FGameplayTag UnlockTag) const;

	template <typename T>
	void ForEachInstanceWithFragment(TFunctionRef<void(UNexusItemInstance*, const T&)> Fn) const;

	// ---------------- Capacity ----------------

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	float GetUsedWeight() const;

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	float GetWeightCapacity() const { return WeightCapacity; }

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	int32 GetSlotCount() const { return Items.Num(); }

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	int32 GetSlotCapacity() const { return SlotCapacity; }

	// ---------------- Delegates ----------------

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemChanged;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

protected:
	virtual void ComponentPreSave_Implementation() override;
	virtual void ComponentSaved_Implementation() override;
	virtual void ComponentPreLoad_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "0"))
	int32 SlotCapacity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "0.0"))
	float WeightCapacity = 0.0f;

	UPROPERTY(SaveGame)
	TArray<TObjectPtr<UNexusItemInstance>> Items;

private:
	int32 GetMaxStackForDefinition(const UNexusItemDefinition* Definition) const;

	void BroadcastChange(UNexusItemInstance* Instance, bool bAdded, bool bRemoved);
};

template <typename T>
void UNexusInventoryComponent::ForEachInstanceWithFragment(TFunctionRef<void(UNexusItemInstance*, const T&)> Fn) const
{
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (!Def) continue;
		if (const T* Frag = Def->template FindFragment<T>())
		{
			Fn(Instance, *Frag);
		}
	}
}