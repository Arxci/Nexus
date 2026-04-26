// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EMSCompSaveInterface.h"
#include "NexusEquipmentComponent.generated.h"

class ANexusEquippedActor;
class UNexusAbility;
class UNexusAbilitySystemComponent;
class UNexusInventoryComponent;
class UNexusItemInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentChanged, FGameplayTag, SlotTag, UNexusItemInstance*, Instance);

/**
 * Binds inventory items to equipment slots and translates them into in-world
 * capabilities (spawned actor + granted abilities + owned tags). Reads items
 * from a sibling UNexusInventoryComponent — never owns items itself.
 *
 * Lives on ANexusCharacterBase alongside the inventory and ASC. Generic enough
 * that AI characters can use it for their loadouts later.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusEquipmentComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusEquipmentComponent();

	// ---------------- Lifecycle ----------------

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool EquipInstance(UNexusItemInstance* Instance);

	/**
	 * Walk the sibling inventory and equip the first item whose Equippable
	 * fragment matches SlotTag. Returns the equipped instance, or null if
	 * the inventory has no compatible item. Idempotent: if SlotTag already
	 * has an item equipped, returns that item without doing anything.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UNexusItemInstance* TryEquipFirstCompatibleForSlot(FGameplayTag SlotTag);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UnequipSlot(FGameplayTag SlotTag);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnequipAll();

	// ---------------- Queries ----------------

	UFUNCTION(BlueprintPure, Category = "Equipment")
	UNexusItemInstance* GetEquippedInSlot(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	ANexusEquippedActor* GetEquippedActorInSlot(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsSlotOccupied(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	FGameplayTag GetActiveSlot() const { return ActiveSlot; }

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetActiveSlot(FGameplayTag SlotTag);

	UFUNCTION(BlueprintPure, Category = "Equipment")
	UNexusItemInstance* GetActiveInstance() const;

	// ---------------- Delegates ----------------

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnEquipped;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnUnequipped;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnActiveSlotChanged;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// EMS Component Save Interface
	virtual void ComponentPreSave_Implementation() override;
	virtual void ComponentSaved_Implementation() override;
	virtual void ComponentPreLoad_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;

	UNexusAbilitySystemComponent* GetASC() const;
	UNexusInventoryComponent*     GetInventory() const;

	/** Slot → currently-equipped instance. Saved as the source of truth on load. */
	UPROPERTY(SaveGame)
	TMap<FGameplayTag, TObjectPtr<UNexusItemInstance>> EquippedSlots;

	/** Slot → spawned actor. Transient — re-spawned on load via re-equip. */
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<ANexusEquippedActor>> SpawnedActors;

	/** Slot → ability classes granted on equip, so we can revoke exactly what we added. */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FGameplayTagContainer> AppliedTagsBySlot;

	/** Slot → abilities granted on equip. Mirror of GrantedAbilities for clean revoke. */
	TMap<FGameplayTag, TArray<TSubclassOf<UNexusAbility>>> AppliedAbilitiesBySlot;

	UPROPERTY(SaveGame)
	FGameplayTag ActiveSlot;

private:
	void ApplyEquipEffects(FGameplayTag SlotTag, UNexusItemInstance* Instance);
	void RemoveEquipEffects(FGameplayTag SlotTag);
	
	UFUNCTION()
	void HandleInventoryItemRemoved(UNexusItemInstance* RemovedInstance);
	
};