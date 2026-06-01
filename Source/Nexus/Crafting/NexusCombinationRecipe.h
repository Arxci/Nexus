#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "NexusCombinationRecipe.generated.h"

class UNexusItemDefinition;


/** One required input: Count of a specific item definition. */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusRecipeInput
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe")
	TObjectPtr<UNexusItemDefinition> Definition = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe", meta = (ClampMin = "1"))
	int32 Count = 1;
};


/**
 * A combination recipe — ammo crafting, herb mixing, resource conversion. Pure data: the
 * combination subsystem reads it and consumes the inputs / produces the output entirely
 * through the public inventory API and the acquire façade. A new recipe is a new asset,
 * no code change (criterion 2). Gem→treasure socketing is handled by a dedicated subsystem
 * path rather than a recipe, since it mutates a specific treasure instance.
 */
UCLASS(BlueprintType)
class NEXUS_API UNexusCombinationRecipe : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Optional identity for catalogs / UI. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe",
		meta = (Categories = "Recipe"))
	FGameplayTag RecipeId;

	/** Items consumed by the craft. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe")
	TArray<FNexusRecipeInput> Inputs;

	/** Item produced by the craft (given through the acquire façade). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe")
	TObjectPtr<UNexusItemDefinition> Output = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recipe", meta = (ClampMin = "1"))
	int32 OutputCount = 1;
};
