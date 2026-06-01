#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "NexusItemCombinationSubsystem.generated.h"

class UNexusCombinationRecipe;
class UNexusInventoryComponent;
class UNexusItemDefinition;
class UNexusItemInstance;


/**
 * Item combination — ammo crafting, herb mixing, gem→treasure socketing. A pure consumer:
 * it reads recipe assets and mutates inventory only through the public API (counts,
 * RemoveFromInstance) and the acquire façade for outputs. Inventory references none of this
 * (one-way coupling); a new recipe is a data asset, not a code change.
 */
UCLASS()
class NEXUS_API UNexusItemCombinationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UNexusItemCombinationSubsystem* Get(const UObject* WorldContext);

	/** True if Inventory holds every input the recipe needs. */
	UFUNCTION(BlueprintPure, Category = "Crafting")
	bool CanCraft(const UNexusInventoryComponent* Inventory, const UNexusCombinationRecipe* Recipe) const;

	/**
	 * Craft Recipe against Inventory: consume the inputs (public RemoveFromInstance) and give
	 * the output through the acquire façade. Returns false if the inputs aren't all present.
	 */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool Craft(UNexusInventoryComponent* Inventory, const UNexusCombinationRecipe* Recipe);

	/**
	 * Socket one GemDef from Inventory into Treasure's SocketTag: consume the gem (public
	 * API) and socket it (UNexusItemEconomyLibrary), raising the treasure's value and
	 * persisting it. Returns false if the gem can't be socketed or isn't held.
	 */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool CombineGemIntoTreasure(UNexusInventoryComponent* Inventory, UNexusItemInstance* Treasure,
		FGameplayTag SocketTag, UNexusItemDefinition* GemDef);

private:
	/** Remove up to Count of Definition across matching instances; returns how many were removed. */
	static int32 ConsumeCountOfDefinition(UNexusInventoryComponent* Inventory,
		const UNexusItemDefinition* Definition, int32 Count);
};
