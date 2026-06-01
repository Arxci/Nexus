#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "StructUtils/InstancedStruct.h"

#include "Nexus/Interaction/NexusInteractionCondition.h"
#include "Nexus/Interaction/NexusInteractionEffect.h"

#include "NexusInteraction.generated.h"


/** Which prompt slot an interaction occupies. Primary is the default verb; Secondary is the optional alternate (e.g. Examine alongside Open). */
UENUM(BlueprintType)
enum class ENexusInteractionSlot : uint8
{
	Primary   UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary"),
};


/**
 * One interaction an object offers: a verb, the conditions that gate it, and the
 * effects that run on success. This is the data unit that replaces the old single
 * hard-coded hold duration — a door, note, lever, safe or merchant differ only by
 * the entries authored here, not by a C++ actor subclass.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusInteraction
{
	GENERATED_BODY()

	/** The verb this interaction performs (Interaction.Verb.*). Drives the prompt label. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Interaction.Verb"))
	FGameplayTag Verb;

	/** Seconds the input must be held to complete. 0 = instant (tap completes on press). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float HoldDuration = 0.0f;

	/** Gates that must ALL pass for this interaction to be enabled. A failing gate supplies the prompt's reason. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FNexusInteractionCondition>> Conditions;

	/** Outcomes run in order on completion (each through a public API). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FNexusInteractionEffect>> Effects;

	/** Primary verb (default) or an optional Secondary surfaced alongside it. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ENexusInteractionSlot Slot = ENexusInteractionSlot::Primary;

	/** Higher wins when several entries are enabled at once. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Priority = 0;

	/**
	 * Consume this entry after the first successful completion — it is never offered
	 * again (looted container, one-shot save). Persists per-actor via the component's
	 * EMS save. (Open↔close "toggle" verbs are expressed as data instead: a Set World
	 * State effect with bToggle, or a paired Open/Close gated on the world flag.)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bOneShot = false;

	/** Optional authored prompt text; if empty the HUD derives it from the Verb tag (later phase). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText PromptOverride;

	/** Optional key for consumed-state tracking. Defaults to Verb when unset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag StateKey;

	/** The key used to record/query this entry's one-shot consumed state. */
	FGameplayTag GetStateKey() const { return StateKey.IsValid() ? StateKey : Verb; }
};


/**
 * A resolved view of one interaction for a specific interactor, produced by
 * INexusInteractableInterface::GetAvailableInteractions. The HUD reads these to
 * build the prompt — verb, hold-vs-tap, enabled/gated, and the fail reason —
 * without the interactable pushing any UI.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusResolvedInteraction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag Verb;

	UPROPERTY(BlueprintReadOnly)
	float HoldDuration = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	bool bEnabled = false;

	/** Reason shown when bEnabled is false (e.g. "Locked — needs Square Crank"). */
	UPROPERTY(BlueprintReadOnly)
	FText FailReason;

	/** Authored prompt override, if any (empty → HUD derives from Verb). */
	UPROPERTY(BlueprintReadOnly)
	FText Prompt;

	UPROPERTY(BlueprintReadOnly)
	ENexusInteractionSlot Slot = ENexusInteractionSlot::Primary;

	/** Index into the component's Interactions array, or INDEX_NONE for the legacy single-hold fallback. */
	UPROPERTY(BlueprintReadOnly)
	int32 EntryIndex = -1;
};


/**
 * Aggregate outcome of the effects that ran for one completed interaction.
 * Effects may report into it (GiveItem records how much it placed / couldn't
 * place); a completion listener — e.g. ANexusItemPickup deciding whether to tear
 * down or leave a remainder — reads it back off the component.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusInteractionResult
{
	GENERATED_BODY()

	/** Total item count successfully given this completion (summed across GiveItem effects). */
	UPROPERTY(BlueprintReadOnly)
	int32 ItemsAdded = 0;

	/** Total item count that could not be placed (inventory capacity), left for a later retry. */
	UPROPERTY(BlueprintReadOnly)
	int32 ItemsRemaining = 0;
};
