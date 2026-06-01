#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "Components/ActorComponent.h"

#include "GameplayTagContainer.h"

#include "EMSCompSaveInterface.h"

#include "NexusEquipmentComponent.generated.h"

class UAnimMontage;
class UAnimInstance;

class ANexusEquippedActor;
class UNexusAbility;
class UNexusAbilitySystemComponent;
class UNexusInventoryComponent;
class UNexusItemDefinition;
class UNexusItemInstance;
class UNexusEquipmentLoadout;
class INexusEquipmentInterface;


/** Which unholster animation a draw plays. Tap → Normal, hold → Ceremony (weapon inspect / flourish). */
UENUM(BlueprintType)
enum class EUnholsterStyle : uint8
{
	Normal   UMETA(DisplayName = "Normal"),
	Ceremony UMETA(DisplayName = "Ceremony"),
};


/** Per-slot lifecycle phase for an in-hand slot. Passive slots stay Idle. */
UENUM(BlueprintType)
enum class EEquipmentSlotPhase : uint8
{
	Idle         UMETA(DisplayName = "Idle"),         // assigned but not in hand (or empty)
	Unholstering UMETA(DisplayName = "Unholstering"), // being drawn
	Active       UMETA(DisplayName = "Active"),       // in hand, ready (fire/reload allowed)
	Holstering   UMETA(DisplayName = "Holstering"),   // being stowed
};


// One slot-event shape for every dispatcher: (SlotTag, Instance). Instance is the
// assigned item, or null where a slot has emptied.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentSlotChanged, FGameplayTag, SlotTag, UNexusItemInstance*, Instance);


/**
 * Runtime state for one occupied slot, keyed by SlotTag. The component owns one
 * of these per assigned slot. The plan's "FActiveGameplayEffectHandle PassiveFx[]"
 * maps onto this project's ability-driven ASC as the granted abilities + owned
 * tags recorded here, so clearing a slot removes exactly what assigning it added.
 */
USTRUCT()
struct FNexusEquipmentSlotState
{
	GENERATED_BODY()

	/** The assigned inventory item. Never owned here — a pointer into the inventory. */
	UPROPERTY()
	TObjectPtr<UNexusItemInstance> Assigned = nullptr;

	/** Spawned in-world actor for an in-hand item. Always null for a passive slot. */
	UPROPERTY(Transient)
	TObjectPtr<ANexusEquippedActor> InWorld = nullptr;

	/** Abilities granted to the host ASC on assign, removed on clear. */
	UPROPERTY(Transient)
	TArray<TSubclassOf<UNexusAbility>> GrantedAbilities;

	/** Loose tags pushed to the host ASC on assign, removed on clear. */
	FGameplayTagContainer GrantedTags;

	EEquipmentSlotPhase Phase = EEquipmentSlotPhase::Idle;
	bool bPassive = false;
};


/**
 * A starter item a character spawns already holding — the NPC equivalent of the
 * controlled character picking a weapon up. Configured per character class on the
 * equipment component; applied once at BeginPlay (skipped on a save-restore, which
 * restores the real slot state instead).
 */
USTRUCT(BlueprintType, DisplayName = "Starter Equipped")
struct NEXUS_API FNexusStarterEquipped
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starter",
		meta = (Categories = "Equipment.Slot"))
	FGameplayTag SlotTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starter")
	TSoftObjectPtr<UNexusItemDefinition> ItemDefinition;

	/** Draw the item into hands on spawn (in-hand slots only). Passive slots ignore this. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starter")
	bool bActivateOnSpawn = false;
};


/**
 * Data-driven equipment host. Owns per-slot runtime state keyed by SlotTag, with
 * the slot list read from a designer-authored UNexusEquipmentLoadout (never
 * hardcoded). Hosts both in-hand items (guns / melee / throwables, with a full
 * holster/unholster lifecycle) and passive items (armor / charm, stat-only) on
 * any actor that implements INexusEquipmentInterface — controlled character or NPC
 * alike. A single in-hand slot is active at a time; the lifecycle advances on anim
 * notifies, not on montage length.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusEquipmentComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusEquipmentComponent();

public:
	// Loadout / slot queries
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	const UNexusEquipmentLoadout* GetLoadout() const { return Loadout; }

	/** True if SlotTag is a slot this character's loadout exposes. */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	bool IsValidSlot(FGameplayTag SlotTag) const;

	/** True if SlotTag is a passive (armor / charm) slot. */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	bool IsSlotPassive(FGameplayTag SlotTag) const;

	/** Every slot tag the loadout exposes, in SortOrder order. */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	TArray<FGameplayTag> GetSlots() const;

	/**
	 * True if Instance may be placed in SlotTag: the slot exists, its mode matches
	 * the item's fragment (in-hand ↔ Equippable, passive ↔ PassiveEquipment), and
	 * the item's category tags intersect the slot's AcceptedItemTags (an empty
	 * AcceptedItemTags accepts any item of the right mode).
	 */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	bool CanAssignToSlot(const UNexusItemInstance* Instance, FGameplayTag SlotTag) const;

	/** UI helper: every exposed slot Instance is compatible with, in loadout order. */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	TArray<FGameplayTag> GetCompatibleSlotsForInstance(const UNexusItemInstance* Instance) const;

	/**
	 * Slot the component would auto-equip Instance into: the equippable fragment's
	 * PreferredSlot when free, else the first compatible free slot, else invalid.
	 * Shared with UNexusInventoryAcquireLibrary so pickup auto-equip and direct
	 * callers agree.
	 */
	UFUNCTION(BlueprintPure, Category = "Equipment|Loadout")
	FGameplayTag PickAutoAssignSlot(const UNexusItemInstance* Instance) const;

public:
	// Assignment (UI-driven)
	/**
	 * Place Instance into SlotTag. Rejected (with a warning) when Instance is
	 * incompatible per CanAssignToSlot. A passive slot applies the item's effects
	 * immediately; an in-hand slot async-loads the Equipped bundle and spawns the
	 * equipped actor. If the slot already holds a different item it is cleared first.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool AssignItemToSlot(FGameplayTag SlotTag, UNexusItemInstance* Instance);

	/**
	 * Remove the item in SlotTag. The active in-hand slot plays its holster montage
	 * and clears when it finishes; every other case (non-active, passive, teardown)
	 * clears immediately.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool ClearSlot(FGameplayTag SlotTag);

	/** Clear SlotTag now with no holster montage. For teardown / inventory removal / save-load. */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool ClearSlotImmediate(FGameplayTag SlotTag);

	/** Clear every assigned slot immediately. */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	void ClearAll();

	/**
	 * Move the item from FromSlot to ToSlot, swapping occupants when both are
	 * filled (each must remain compatible with its destination).
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool MoveItemBetweenSlots(FGameplayTag FromSlot, FGameplayTag ToSlot);

	/**
	 * Assign Instance to SlotTag and activate it once the (async) Equipped bundle
	 * resolves and the actor is spawned. Closes the race in a bare
	 * "AssignItemToSlot + RequestActivateSlot" pair where activation could run
	 * before the actor existed. UNexusInventoryAcquireLibrary is the canonical caller.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Loadout")
	bool AssignAndActivate(FGameplayTag SlotTag, UNexusItemInstance* Instance,
		EUnholsterStyle Style = EUnholsterStyle::Normal);

public:
	// Activation (input / AI-driven)
	/**
	 * Draw SlotTag. Normal plays the standard unholster; Ceremony plays the
	 * inspect/flourish variant (falling back to Normal if the item doesn't author
	 * one). Pressing the already-active slot deactivates it (toggle to empty
	 * hands). Activating a different slot while one is active chains holster →
	 * unholster. Calls during a transition are queued and run when it settles.
	 * Passive slots are never activatable (they're always on while assigned).
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Activation")
	bool RequestActivateSlot(FGameplayTag SlotTag, EUnholsterStyle Style = EUnholsterStyle::Normal);

	/** Holster the active slot back to empty hands. Queues if a transition is in flight. */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Activation")
	bool RequestDeactivateActiveSlot();

	/** Activate the next / previous occupied in-hand slot in loadout order, wrapping. */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Activation")
	bool RequestActivateNextSlot();
	UFUNCTION(BlueprintCallable, Category = "Equipment|Activation")
	bool RequestActivatePrevSlot();

	/** Quick-swap back to the slot active before the current one (the "previous weapon" key). */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Activation")
	bool RequestActivateLastSlot();

public:
	// Queries
	UFUNCTION(BlueprintPure, Category = "Equipment")
	UNexusItemInstance* GetAssigned(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	ANexusEquippedActor* GetEquippedActorInSlot(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsSlotOccupied(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsSlotActive(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	EEquipmentSlotPhase GetSlotPhase(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	TArray<FGameplayTag> GetOccupiedSlots() const;

	/** The slot Instance is assigned to, or invalid. Reverse of GetAssigned. */
	UFUNCTION(BlueprintPure, Category = "Equipment")
	FGameplayTag GetSlotForInstance(const UNexusItemInstance* Instance) const;

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	FGameplayTag GetActiveSlot() const { return ActiveSlot; }

	/** The slot active immediately before the current one (quick-swap target), or invalid. */
	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	FGameplayTag GetLastActiveSlot() const { return LastActiveSlot; }

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	UNexusItemInstance* GetActiveInstance() const { return GetAssigned(ActiveSlot); }

	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	ANexusEquippedActor* GetActiveActor() const { return GetEquippedActorInSlot(ActiveSlot); }

	/** True while a holster/unholster transition is mid-flight. */
	UFUNCTION(BlueprintPure, Category = "Equipment|Activation")
	bool IsSwapping() const;

public:
	// Anim-notify hooks (phase advancement is notify-driven, never timed off montage length)
	/**
	 * UNexusAnimNotify_HideOutgoingEquipped fires this at the authored frame of a
	 * holster montage: it hides the outgoing actor and hands off to the incoming
	 * draw in one step, so no frame shows both equipped actors.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Anim Notify")
	void NotifyHideOutgoingSlot();

	/**
	 * UNexusAnimNotify_EquipmentAction fires this with the action it carries.
	 * Holster advances a stow; Unholster / Ceremony complete a draw. All other
	 * actions (Fire, Reload, ...) are ignored here — they only drive item-mesh anim.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipment|Anim Notify")
	void HandleEquipmentActionNotify(FGameplayTag ActionTag);

public:
	// Delegates
	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotChanged OnSlotAssigned;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotChanged OnSlotCleared;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotChanged OnSlotActivated;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnEquipmentSlotChanged OnSlotDeactivated;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ComponentPreSave_Implementation() override;
	virtual void ComponentPreLoad_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;

protected:
	/** Slots this character exposes. One asset per character class; assigned per BP. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment|Config")
	TObjectPtr<UNexusEquipmentLoadout> Loadout;

	/** Items the character spawns already carrying (NPC starter weapon / armor). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment|Config")
	TArray<FNexusStarterEquipped> StarterEquipment;

	/** Live per-slot state, keyed by SlotTag. Only occupied slots have an entry. */
	UPROPERTY()
	TMap<FGameplayTag, FNexusEquipmentSlotState> SlotStates;

	/**
	 * Persisted slot → instance GUID. The runtime SlotStates pointers can't
	 * round-trip through EMS (transient inventory subobjects have no loadable
	 * path), so we persist the stable GUIDs and re-resolve them against the
	 * restored inventory on load.
	 */
	UPROPERTY(SaveGame)
	TMap<FGameplayTag, FGuid> SavedSlotGuids;

	/** The active slot — saved so a draw is restored on load. */
	UPROPERTY(SaveGame)
	FGameplayTag ActiveSlot;

private:
	// Host access — everything goes through the interfaces, never a concrete class.
	INexusEquipmentInterface*     GetHost() const;
	UAnimInstance*                GetHostAnimInstance() const;
	UNexusAbilitySystemComponent* GetASC() const;
	UNexusInventoryComponent*     GetInventory() const;

	// Assignment internals
	void FinalizeInHandAssignment(FGameplayTag SlotTag, UNexusItemInstance* Instance);
	void ApplySlotEffects(FGameplayTag SlotTag, FNexusEquipmentSlotState& State);
	void RemoveSlotEffects(FNexusEquipmentSlotState& State);
	void AttachActorForSlotState(FGameplayTag SlotTag, bool bActive) const;

	// Lifecycle state machine
	void BeginActivate(FGameplayTag SlotTag, EUnholsterStyle Style);
	void BeginHolsterPhase(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot, EUnholsterStyle IncomingStyle);
	void FinishHolsterPhase();
	void BeginDrawPhase(FGameplayTag IncomingSlot, EUnholsterStyle Style);
	void FinishDrawPhase();

	UAnimMontage* ResolveTransitionMontage(FGameplayTag SlotTag, FGameplayTag ActionTag) const;
	void HandleHolsterMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void HandleDrawMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	
	void SetSwapTag(bool bOn) const;

	bool CycleActiveSlot(int32 Direction);

	void DrainPendingActivationsAfterAssignment(FGameplayTag SlotTag);

	// Inventory hookup
	UFUNCTION()
	void HandleInventoryItemRemoved(UNexusItemInstance* RemovedInstance);

	// Case-charm hookup: re-apply the equipped case's socketed charms through the host ASC,
	// the same passive-effect path armor uses (no parallel system).
	UFUNCTION()
	void HandleEquippedCaseChanged();
	void RefreshCharms();

	// Starter loadout / save-restore
	void ApplyStarterEquipment();
	void ResolveEquippedFromSave();

private:
	TMap<TObjectPtr<UNexusItemInstance>, TSharedPtr<FStreamableHandle>> EquippableLoadHandles;

	/** Slot currently being stowed (Phase == Holstering). */
	FGameplayTag HolsteringSlot;

	/** Slot to draw once the in-flight holster finishes (the swap target); invalid for a plain deactivate. */
	FGameplayTag PendingDrawSlot;
	EUnholsterStyle PendingDrawStyle = EUnholsterStyle::Normal;

	/** Most-recently-stowed slot, the quick-swap-to-previous target. Runtime-only. */
	FGameplayTag LastActiveSlot;

	/** A clear requested on the active slot, deferred until its holster montage finishes. */
	FGameplayTag SlotPendingClear;

	/**
	 * A slot + draw style pairing. Transitions themselves are non-interruptible and never
	 * queued, but AssignAndActivate still needs to remember a requested draw until the
	 * slot's actor finishes its async spawn — that's the one deferred case below.
	 */
	struct FPendingActivation
	{
		FGameplayTag    SlotTag;
		EUnholsterStyle Style = EUnholsterStyle::Normal;
	};

	/** Activations waiting on an async actor spawn (AssignAndActivate). Drained in FinalizeInHandAssignment. */
	TArray<FPendingActivation> PendingActivationsAfterAssignment;

	/** Active slot captured from a save, consumed by the deferred ResolveEquippedFromSave. */
	FGameplayTag PendingRestoreActiveSlot;

	/** Set once starter equipment has been applied (or suppressed by a save-restore). */
	bool bStarterApplied = false;

	/**
	 * Abilities + loose tags currently granted to the host ASC by the equipped case's
	 * socketed charms. Tracked as flat lists so each grant has a matching ref-counted
	 * removal (two charms granting the same tag coexist). RefreshCharms removes exactly
	 * these, then re-grants from the current charm set.
	 */
	UPROPERTY(Transient)
	TArray<TSubclassOf<UNexusAbility>> GrantedCharmAbilities;
	TArray<FGameplayTag> GrantedCharmTags;
};