// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "Components/ActorComponent.h"

#include "GameplayTagContainer.h"

#include "EMSCompSaveInterface.h"

#include "NexusEquipmentComponent.generated.h"

class USceneComponent;
class UAnimMontage;
class UAnimSequence;

class ANexusEquippedActor;
class UNexusAbility;
class UNexusAbilitySystemComponent;
class UNexusInventoryComponent;
class UNexusItemInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentChanged, FGameplayTag, SlotTag, UNexusItemInstance*, Instance);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusEquipmentComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusEquipmentComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool EquipInstance(UNexusItemInstance* Instance);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UNexusItemInstance* TryEquipFirstCompatibleForSlot(FGameplayTag SlotTag);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool UnequipSlot(FGameplayTag SlotTag);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnequipAll();

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

	UFUNCTION(BlueprintPure, Category = "Equipment")
	ANexusEquippedActor* GetActiveActor() const { return GetEquippedActorInSlot(ActiveSlot); }

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsSwapping() const { return bIsSwapping; }
	
	UFUNCTION(BlueprintCallable, Category = "Equipment|Anim Notify")
	void NotifyHideOutgoingSlot();

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnEquipped;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnUnequipped;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnActiveSlotChanged;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ComponentPreLoad_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;

	UNexusAbilitySystemComponent* GetASC() const;
	UNexusInventoryComponent*     GetInventory() const;

	UPROPERTY(SaveGame)
	TMap<FGameplayTag, TObjectPtr<UNexusItemInstance>> EquippedSlots;

	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<ANexusEquippedActor>> SpawnedActors;

	UPROPERTY(Transient)
	TMap<FGameplayTag, FGameplayTagContainer> AppliedTagsBySlot;

	TMap<FGameplayTag, TArray<TSubclassOf<UNexusAbility>>> AppliedAbilitiesBySlot;

	UPROPERTY(SaveGame)
	FGameplayTag ActiveSlot;

private:
	void ApplyEquipEffects(FGameplayTag SlotTag, UNexusItemInstance* Instance);
	void RemoveEquipEffects(FGameplayTag SlotTag);
	
	void HandleActiveSlotTransition(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot);
	void AttachActorForSlotState(const FGameplayTag SlotTag, const bool bActive) const;
	float PlayMontageOnOwner(UAnimMontage* Montage) const;

	UFUNCTION()
	void HandleInventoryItemRemoved(UNexusItemInstance* RemovedInstance);

	UFUNCTION()
	void HandleInventoryItemAdded(UNexusItemInstance* Instance);
	void RequestEquippedBundleLoad(UNexusItemInstance* Instance);
	void ReleaseEquippedBundleLoad(UNexusItemInstance* Instance);
	
	TMap<TObjectPtr<UNexusItemInstance>, TSharedPtr<FStreamableHandle>> EquippableLoadHandles;

	UFUNCTION()
	void HandleSwapLockoutFinished();
	
	FGameplayTag OutgoingPendingHide;

	FTimerHandle SwapLockoutTimer;
	bool bIsSwapping = false;
};