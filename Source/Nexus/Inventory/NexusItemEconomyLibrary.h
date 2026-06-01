#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "NexusItemEconomyLibrary.generated.h"

class UNexusItemDefinition;
class UNexusItemInstance;


/**
 * The value/sellable side of the economy that the inventory *owns as data* — the merchant
 * subsystem and any other consumer read these; inventory holds no shop logic.
 *
 * Value is computed on demand from the definition's BaseValue plus, for a treasure, the
 * values of the gems socketed into it (stored per-instance in SocketedItems). Nothing is
 * cached, so the sell value can never drift from the actual sockets.
 */
UCLASS()
class NEXUS_API UNexusItemEconomyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Combined sell value of an instance: definition BaseValue (times stack count for a
	 * fungible stack) plus, for a treasure, every socketed gem's BaseValue and the
	 * full-socket completion bonus when all sockets are filled.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Economy")
	static int32 GetSellValue(const UNexusItemInstance* Instance);

	/** Base purchase price of one unit of a definition (the merchant may scale this). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Economy")
	static int32 GetUnitValue(const UNexusItemDefinition* Definition);

	UFUNCTION(BlueprintPure, Category = "Inventory|Economy")
	static bool IsSellable(const UNexusItemDefinition* Definition);

	UFUNCTION(BlueprintPure, Category = "Inventory|Economy")
	static bool IsBuyable(const UNexusItemDefinition* Definition);

	// Treasure gem socketing
	/**
	 * True if GemDef may be socketed into Treasure's SocketTag: the treasure exposes that
	 * socket, the socket is empty, and the gem's category matches the socket's accepted gem
	 * category.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Economy")
	static bool CanSocketGem(const UNexusItemInstance* Treasure, FGameplayTag SocketTag,
		const UNexusItemDefinition* GemDef);

	/**
	 * Socket GemDef into Treasure's SocketTag (raising its combined sell value and persisting
	 * per-instance). Does not consume the gem from any inventory — the caller (a merchant /
	 * combination flow) owns that. Returns false if CanSocketGem is false.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Economy")
	static bool SocketGem(UNexusItemInstance* Treasure, FGameplayTag SocketTag, UNexusItemDefinition* GemDef);
};
