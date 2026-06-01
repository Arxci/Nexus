#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "NexusInteractionCondition.generated.h"

struct FNexusInteractionContext;
class UNexusItemDefinition;


/**
 * Base for a data gate on an interaction. Authored as instanced structs on a
 * FNexusInteraction (mirrors the inventory's TInstancedStruct<FNexusItemFragment>
 * fragment model). The component evaluates every condition before offering /
 * starting an interaction; a failing condition supplies a player-facing reason
 * for the prompt instead of the interaction silently doing nothing.
 *
 * A new gate (requires-quest-stage, requires-tool-equipped) is a new subtype
 * here — no change to the component, ability, or input.
 */
USTRUCT(BlueprintType, meta = (Hidden))
struct NEXUS_API FNexusInteractionCondition
{
	GENERATED_BODY()

	virtual ~FNexusInteractionCondition() = default;

	/** True if this gate is satisfied for the given interactor/interactable. */
	virtual bool IsMet(const FNexusInteractionContext& Context) const { return true; }

	/** Player-facing reason shown when IsMet is false (e.g. "Locked — needs Square Crank"). */
	virtual FText GetFailReason(const FNexusInteractionContext& Context) const;
};


/** Requires the interactor to hold at least Count of an item with IdentityTag (key items, fuses, batteries). */
USTRUCT(BlueprintType, DisplayName = "Requires Item")
struct NEXUS_API FNexusInteractionCondition_RequiresItem : public FNexusInteractionCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Item.Identity"))
	FGameplayTag IdentityTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 Count = 1;

	/** Optional player-facing override; e.g. "Locked — needs Square Crank". */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText FailReasonOverride;

	virtual bool IsMet(const FNexusInteractionContext& Context) const override;
	virtual FText GetFailReason(const FNexusInteractionContext& Context) const override;
};


/**
 * Requires room in the interactor's inventory for Definition. Gates only the
 * FULLY-rejected case (zero remaining capacity) so partial pickups still take
 * what fits and leave a remainder — the GiveItem effect handles the partial.
 */
USTRUCT(BlueprintType, DisplayName = "Requires Free Space")
struct NEXUS_API FNexusInteractionCondition_RequiresFreeSpace : public FNexusInteractionCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNexusItemDefinition> Definition = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText FailReasonOverride;

	virtual bool IsMet(const FNexusInteractionContext& Context) const override;
	virtual FText GetFailReason(const FNexusInteractionContext& Context) const override;
};


/**
 * Requires this interaction's one-shot state to be unconsumed. Uses the active
 * entry's state key (its Verb) unless StateKeyOverride is set — so one entry can
 * gate on another's consumption (e.g. "Search" only meaningful after "Open").
 */
USTRUCT(BlueprintType, DisplayName = "Not Consumed")
struct NEXUS_API FNexusInteractionCondition_NotConsumed : public FNexusInteractionCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag StateKeyOverride;

	virtual bool IsMet(const FNexusInteractionContext& Context) const override;
};


/** How a RequiresWorldState gate compares the stored value against its target. */
UENUM(BlueprintType)
enum class ENexusWorldStateComparison : uint8
{
	Equal          UMETA(DisplayName = "=="),
	NotEqual       UMETA(DisplayName = "!="),
	GreaterOrEqual UMETA(DisplayName = ">="),
	LessOrEqual    UMETA(DisplayName = "<="),
	Greater        UMETA(DisplayName = ">"),
	Less           UMETA(DisplayName = "<"),
};


/**
 * Requires a world-state value (UNexusWorldStateSubsystem) to satisfy a
 * comparison — the gate behind an RE7-style door keyed on a flag, a valve that
 * must be turned first, a puzzle that must be solved. An unset key reads 0.
 */
USTRUCT(BlueprintType, DisplayName = "Requires World State")
struct NEXUS_API FNexusInteractionCondition_RequiresWorldState : public FNexusInteractionCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Interaction.State"))
	FGameplayTag Key;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ENexusWorldStateComparison Comparison = ENexusWorldStateComparison::Equal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Value = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText FailReasonOverride;

	virtual bool IsMet(const FNexusInteractionContext& Context) const override;
	virtual FText GetFailReason(const FNexusInteractionContext& Context) const override;
};


/**
 * Requires a state tag on the INTERACTABLE owner's ASC — the gate behind a
 * contextual action like a finisher that only appears on a staggered enemy
 * (RequiredTag = Character.State.Staggered). Host-agnostic: any actor with an
 * ASC. Fails (the action simply doesn't show) if the interactable has no ASC or
 * lacks the tag.
 */
USTRUCT(BlueprintType, DisplayName = "Requires Interactable State")
struct NEXUS_API FNexusInteractionCondition_RequiresInteractableState : public FNexusInteractionCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Character.State"))
	FGameplayTag RequiredTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText FailReasonOverride;

	virtual bool IsMet(const FNexusInteractionContext& Context) const override;
	virtual FText GetFailReason(const FNexusInteractionContext& Context) const override;
};
