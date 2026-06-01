#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Nexus/Interaction/NexusInteraction.h"

#include "NexusInteractionPromptLibrary.generated.h"


/**
 * The localization seam for interaction prompts. Maps an Interaction.Verb.* tag to
 * a display label, and resolves the single line the HUD/marker should show for a
 * focused interactable from its resolved interactions — the authored per-entry
 * override if set, else the verb label, or the gate reason when everything is
 * locked. The components stay UI-shape-agnostic; this is a pure read helper.
 *
 * The C++ table here is the default; a project can later swap in a DataTable-backed
 * lookup without touching the component, ability, or input.
 */
UCLASS()
class NEXUS_API UNexusInteractionPromptLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Localized label for a verb tag (PickUp → "Take", Open → "Open", …). */
	UFUNCTION(BlueprintPure, Category = "Interaction|Prompt")
	static FText GetVerbText(FGameplayTag Verb);

	/**
	 * The single prompt line for a focused interactable: the best enabled entry's
	 * override-or-verb text (Primary preferred), or the first gate reason when no
	 * entry is enabled, or empty when there's nothing to show.
	 */
	UFUNCTION(BlueprintPure, Category = "Interaction|Prompt")
	static FText ResolvePrompt(const TArray<FNexusResolvedInteraction>& Interactions);

	/** The prompt text for a single resolved entry (override if set, else the verb label). */
	UFUNCTION(BlueprintPure, Category = "Interaction|Prompt")
	static FText GetEntryPrompt(const FNexusResolvedInteraction& Interaction);
};
