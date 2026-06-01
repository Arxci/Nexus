#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "NexusExamineTypes.generated.h"

class UStaticMesh;
class UNexusCombinationRecipe;


/**
 * A hidden detail revealed by rotating the examined mesh near a target
 * orientation — the RE signature "turn the statue to find the key code." On
 * reveal it surfaces text to the HUD and optionally sets a world-state flag so
 * the discovery persists and can gate other interactions.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusExamineReveal
{
	GENERATED_BODY()

	/** Relative orientation that triggers the reveal when the player rotates near it. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator RevealAngle = FRotator::ZeroRotator;

	/** How close (degrees) the orientation must be to trigger. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0"))
	float AngleTolerance = 25.0f;

	/** Optional world-state flag set to 1 when revealed (a discovered code/clue persists). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "Interaction.State"))
	FGameplayTag SetWorldStateKey;

	/** Text surfaced to the HUD on reveal. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = "true"))
	FText RevealText;
};


/**
 * The payload for an Examine sub-mode: the mesh to pose in front of the camera,
 * its description, the reveal hotspots, and any combine recipes offered while
 * examining (routed through UNexusItemCombinationSubsystem). Authored on the
 * BeginExamine effect, so an examinable is data on the generic component.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusExamineData
{
	GENERATED_BODY()

	/** The mesh pulled into view and rotated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = "true"))
	FText Description;

	/** Rotate-to-find hidden details. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FNexusExamineReveal> Reveals;

	/** Recipes offered while examining (examined + held items → output), run through the combination subsystem. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UNexusCombinationRecipe>> CombineRecipes;

	/** How far in front of the camera the mesh sits. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0"))
	float ViewDistance = 40.0f;

	/** Positional nudge from the view-forward point. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector ViewOffset = FVector::ZeroVector;

	/** Rotation sensitivity (degrees per unit of look input). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float RotationSpeed = 8.0f;
};
