#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Templates/SubclassOf.h"

#include "Nexus/Interaction/NexusExamineTypes.h"

#include "NexusInteractionEffect.generated.h"

struct FNexusInteractionContext;
class UNexusItemDefinition;
class USoundBase;
class UNiagaraSystem;
class ANexusItemPickup;


/**
 * Base for an outcome that runs when an interaction completes. Authored as
 * instanced structs on a FNexusInteraction (mirrors the inventory fragment
 * model). Every effect mutates the world ONLY through a public API
 * (AcquireItem, inventory remove, the currency wallet, …) so the interaction
 * module stays a one-way leaf with no inventory/equipment/UI internals.
 *
 * A new outcome (set world state, open a UI panel, spawn an actor) is a new
 * subtype here — no change to the component, ability, or input.
 */
USTRUCT(BlueprintType, meta = (Hidden))
struct NEXUS_API FNexusInteractionEffect
{
	GENERATED_BODY()

	virtual ~FNexusInteractionEffect() = default;

	virtual void Execute(const FNexusInteractionContext& Context) const {}
};


/** Give an item to the interactor via the canonical acquire façade (the generalized pickup path). */
USTRUCT(BlueprintType, DisplayName = "Give Item")
struct NEXUS_API FNexusInteractionEffect_GiveItem : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNexusItemDefinition> Definition = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 Count = 1;

	/** Slot the item into equipment if it's equippable and a compatible slot is free. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAutoEquipIfPossible = true;

	/** Force the standard unholster even on a first acquire (suppress the ceremony flourish). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bSkipCeremony = false;

	/** Stat tags seeded onto brand-new instances (e.g. partial ammo). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, int32> InitialStatTags;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/** Spend Count of an item identity from the interactor's inventory (a key, a battery, a fuse). */
USTRUCT(BlueprintType, DisplayName = "Consume Item")
struct NEXUS_API FNexusInteractionEffect_ConsumeItem : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Item.Identity"))
	FGameplayTag IdentityTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 Count = 1;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/** Credit the currency wallet (RE-style treasure pickup → pesetas/spinels). */
USTRUCT(BlueprintType, DisplayName = "Award Currency")
struct NEXUS_API FNexusInteractionEffect_AwardCurrency : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount = 0;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/** Play a one-shot sound at the interactable's location. */
USTRUCT(BlueprintType, DisplayName = "Play Sound")
struct NEXUS_API FNexusInteractionEffect_PlaySound : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USoundBase> Sound = nullptr;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/** Spawn a one-shot Niagara effect at the interactable's location. */
USTRUCT(BlueprintType, DisplayName = "Play FX")
struct NEXUS_API FNexusInteractionEffect_PlayFX : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> Effect = nullptr;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/**
 * Mark this interaction's one-shot state consumed, so it is never offered again
 * (and survives save/load once the component's state is persisted). Uses the
 * active entry's state key unless StateKeyOverride is set. Equivalent to the
 * entry's bOneShot flag, but explicit and orderable among other effects.
 */
USTRUCT(BlueprintType, DisplayName = "Mark Consumed")
struct NEXUS_API FNexusInteractionEffect_MarkConsumed : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag StateKeyOverride;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/**
 * Write a world-state value (UNexusWorldStateSubsystem) — door=open, lever=pulled,
 * puzzle=solved. With bToggle it flips the key between 0 and 1 (a single RE7-style
 * door entry); otherwise it writes Value. Conditions read the same store, so the
 * change persists and re-gates other interactions across save/load.
 */
USTRUCT(BlueprintType, DisplayName = "Set World State")
struct NEXUS_API FNexusInteractionEffect_SetWorldState : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Interaction.State"))
	FGameplayTag Key;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Value = 1;

	/** Flip Key between 0 and 1 instead of writing Value (door open↔close in one entry). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bToggle = false;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/**
 * Enter the Examine/Inspect sub-mode on the interactor's UNexusExamineComponent:
 * pull the mesh into view, rotate it, reveal hidden details, optionally combine.
 * The effect only REQUESTS examine on the interactor through a public seam; the
 * component owns the sub-mode. A non-player interactor with no examine component
 * is a no-op.
 */
USTRUCT(BlueprintType, DisplayName = "Begin Examine")
struct NEXUS_API FNexusInteractionEffect_BeginExamine : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FNexusExamineData Examine;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/**
 * Request the UI layer open a panel (merchant, save, map, dialogue, heal screen)
 * via UNexusUIRequestSubsystem. The open-UI hook: Talk / Merchant / Save / Heal
 * are this effect with a panel tag — interaction triggers those systems without
 * owning their flows.
 */
USTRUCT(BlueprintType, DisplayName = "Open UI")
struct NEXUS_API FNexusInteractionEffect_OpenUI : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag PanelTag;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/**
 * Spawn an item pickup in the world at the interactable — the RE "search the
 * desk → items appear" pattern. Decoupled: it spawns the existing ANexusItemPickup
 * actor (which the player then collects normally), so a full inventory naturally
 * leaves the loot in the world instead of dropping it. Pair with bOneShot so a
 * searched container spills its contents exactly once.
 */
USTRUCT(BlueprintType, DisplayName = "Spawn Pickup")
struct NEXUS_API FNexusInteractionEffect_SpawnPickup : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNexusItemDefinition> Definition = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 Count = 1;

	/** Pickup actor class to spawn; defaults to ANexusItemPickup when unset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ANexusItemPickup> PickupClass;

	/** Spawn offset from the interactable, in its local space (drop it on the desk, not inside it). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector SpawnOffset = FVector(0.0f, 0.0f, 0.0f);

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};


/**
 * Activate an ability by tag on the interactor's ASC (or the interactable's, with
 * bTargetInteractable) — the request seam for contextual actions the combat /
 * ability systems own. The prompt-driven finisher is this: a Finisher verb gated
 * on a staggered enemy (RequiresInteractableState) whose effect activates the
 * combat finisher ability. A no-op if the target has no such ability granted, so
 * interaction requests without owning the finisher cinematic.
 */
USTRUCT(BlueprintType, DisplayName = "Activate Ability")
struct NEXUS_API FNexusInteractionEffect_ActivateAbility : public FNexusInteractionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Ability"))
	FGameplayTag AbilityTag;

	/** Activate on the interactable's own ASC instead of the interactor's. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bTargetInteractable = false;

	virtual void Execute(const FNexusInteractionContext& Context) const override;
};
