#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UNexusAttachmentDefinition;

/**
 * The pure attachment / upgrade / clamp fold, lifted out of UNexusAssemblyComponent so the
 * editor's author-time preview resolves stats through the SAME code the runtime uses — no
 * parallel reimplementation to drift. Operates in place on an already-seeded base map.
 *
 * Folds, in order (the FResolvedItemStats / FNexusStatClamp contract):
 *   (base + Σ attachment Add) × Π attachment Mul  ->  + upgrade additive  ->  clamp [min,max].
 * Only keys already present in InOutValues are touched; modifiers / upgrades against unseeded
 * keys are ignored. A clamp whose Max <= Min is unbounded.
 */
struct NEXUS_API FNexusStatResolver
{
	static void ApplyFold(
		TMap<FGameplayTag, float>& InOutValues,
		const TMap<FGameplayTag, FVector2D>& Clamps,
		const TArray<const UNexusAttachmentDefinition*>& AttachmentDefs,
		const TMap<FGameplayTag, float>& UpgradeStatTags);
};
