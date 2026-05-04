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


UENUM(BlueprintType)
enum class ENexusEquipSwapPhase : uint8
{
	Idle       UMETA(DisplayName = "Idle"),
	Holstering UMETA(DisplayName = "Holstering"),
	Drawing    UMETA(DisplayName = "Drawing"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentChanged,         FGameplayTag, SlotTag, UNexusItemInstance*, Instance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentSlotAssignment,  FGameplayTag, SlotTag, UNexusItemInstance*, Instance);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusEquipmentComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusEquipmentComponent();

public:
	// Loadout (UI-driven)
	
	/**
	 * Place Instance into SlotTag.
	 *
	 * Validates SlotTag against the instance's FNexusFragment_Equippable::AllowedSlots
	 * AND against this component's AvailableSlots list. If the slot is already
	 * occupied by a different instance, the prior occupant is cleared first.
	 *
	 * Returns false if Instance is null, lacks an Equippable fragment, or the
	 * slot is invalid for either Instance or this component.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool AssignToSlot(UNexusItemInstance* Instance, FGameplayTag SlotTag);

	/**
	 * Remove the instance currently assigned to SlotTag. If the slot is the
	 * active slot, plays the holster montage and clears once finished;
	 * otherwise clears immediately. Use ClearSlotImmediate for a non-anim path
	 * (death/teardown/save-load).
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool ClearSlot(FGameplayTag SlotTag);

	/** Same as ClearSlot but never plays a holster montage; intended for teardown. */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool ClearSlotImmediate(FGameplayTag SlotTag);

	/** Clear every assigned slot immediately (no anim). */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	void ClearAll();

	/**
	 * Move the instance from FromSlot to ToSlot. If ToSlot already holds an
	 * instance, the two slots swap their occupants (provided each instance
	 * remains valid for its destination). Returns false on invalid slot pairs
	 * or incompatibility.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool MoveAssignment(FGameplayTag FromSlot, FGameplayTag ToSlot);

	/** True if Instance can be placed in SlotTag (compatibility + slot exposed). */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	bool CanAssignToSlot(const UNexusItemInstance* Instance, FGameplayTag SlotTag) const;

	/** True if SlotTag is in this component's AvailableSlots. */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	bool IsValidSlot(FGameplayTag SlotTag) const;

	/**
	 * UI helper: every slot Instance is allowed in AND that this component
	 * exposes. Returned in AvailableSlots order so the UI can render them in a
	 * stable, designer-controlled sequence.
	 */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	TArray<FGameplayTag> GetCompatibleSlotsForInstance(const UNexusItemInstance* Instance) const;

	/** Configurable slots this owner exposes (e.g., player has Primary/Secondary/Utility/Body). */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	const TArray<FGameplayTag>& GetAvailableSlots() const { return AvailableSlots; }

public:
	// Activation (input-driven)
	UFUNCTION(BlueprintCallable, Category = "Equipment|Activation")
	bool RequestActivateSlot(FGameplayTag SlotTag);

	/** Holster the currently active slot. Queues if a swap is in flight. */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Activation")
	bool RequestHolster();

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	FGameplayTag GetActiveSlot() const { return ActiveSlot; }

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	UNexusItemInstance* GetActiveInstance() const { return GetEquippedInSlot(ActiveSlot); }

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	ANexusEquippedActor* GetActiveActor() const { return GetEquippedActorInSlot(ActiveSlot); }

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	bool IsSwapping() const { return SwapPhase != ENexusEquipSwapPhase::Idle; }

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	ENexusEquipSwapPhase GetSwapPhase() const { return SwapPhase; }

public:
	// Utility
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UNexusItemInstance* GetEquippedInSlot(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	ANexusEquippedActor* GetEquippedActorInSlot(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsSlotOccupied(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	TArray<FGameplayTag> GetOccupiedSlots() const;


public:
	UFUNCTION(BlueprintCallable, Category = "Equipment|Anim Notify")
	void NotifyHideOutgoingSlot();

public:
	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotAssignment OnSlotAssigned;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotAssignment OnSlotCleared;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentChanged OnActiveSlotChanged;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ComponentPreLoad_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;

	UNexusAbilitySystemComponent* GetASC() const;
	UNexusInventoryComponent*     GetInventory() const;

	/**
	 * Slots this component exposes, in display order. Authored per-character
	 * archetype: a player has Primary/Secondary/Utility/Body, an NPC may only
	 * have Primary, a vehicle would expose entirely different slots.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment|Config",
		meta = (Categories = "Equipment.Slot"))
	TArray<FGameplayTag> AvailableSlots;

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
	void FinalizeAssignment(FGameplayTag SlotTag, UNexusItemInstance* Instance);
	
	void BeginSlotTransition(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot);
	void BeginHolsterPhase(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot);
	void BeginDrawPhase(FGameplayTag IncomingSlot);
	void CompleteSwap();
	void ProcessPendingActivation();

	UFUNCTION()
	void HandleHolsterPhaseFinished();

	UFUNCTION()
	void HandleDrawPhaseFinished();

	void AttachActorForSlotState(FGameplayTag SlotTag, bool bActive) const;
	float PlayMontageOnOwner(UAnimMontage* Montage) const;

	void SetSwapTag(const bool bOn) const;
	
	UFUNCTION()
	void HandleInventoryItemRemoved(UNexusItemInstance* RemovedInstance);

	TMap<TObjectPtr<UNexusItemInstance>, TSharedPtr<FStreamableHandle>> EquippableLoadHandles;
	
	ENexusEquipSwapPhase SwapPhase = ENexusEquipSwapPhase::Idle;
	FGameplayTag         SwapOutgoingSlot; // valid during Holstering
	FGameplayTag         SwapIncomingSlot; // valid during Holstering or Drawing

	/**
	 * Slot the player asked for during an in-flight swap. Optional<> over a
	 * separate bool to make "no pending vs pending-to-clear" unambiguous.
	 *
	 *   pending unset  → no queued request
	 *   pending = X    → activate X when current swap finishes
	 *   pending = ()   → holster everything when current swap finishes
	 */
	TOptional<FGameplayTag> PendingActivation;

	/**
	 * Slot whose actor still needs to be hidden because the holster montage
	 * is mid-play and we're waiting on the anim notify (or fallback timer)
	 * to fire. Separate from SwapOutgoingSlot because the swap can advance
	 * to the Drawing phase before the hide completes (e.g., concurrent
	 * holster/draw blends).
	 */
	FGameplayTag OutgoingPendingHide;

	FTimerHandle PhaseTimer;
};