#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "NexusMerchantSubsystem.generated.h"

class UNexusInventoryComponent;
class UNexusItemDefinition;
class UNexusItemInstance;


/**
 * The shop *flow* (buy / sell / upgrade), kept deliberately separate from the inventory.
 * It is a pure consumer: it prices items from the inventory's value data
 * (UNexusItemEconomyLibrary + the definition's BaseValue/bSellable/bBuyable), moves items
 * only through the public inventory API and the acquire façade, and debits/credits the
 * currency wallet on UNexusItemContainerSubsystem. It owns no item storage and the
 * inventory knows nothing about it (one-way coupling).
 *
 * The merchant *screen* UI and request/reward logic are out of scope; this is the
 * primitive layer they would build on.
 */
UCLASS()
class NEXUS_API UNexusMerchantSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UNexusMerchantSubsystem* Get(const UObject* WorldContext);

	// Pricing
	/** Price the merchant pays for selling Count of Instance (whole instance if it's socketed/customized). */
	UFUNCTION(BlueprintPure, Category = "Merchant")
	int32 GetSellPrice(const UNexusItemInstance* Instance, int32 Count) const;

	/** Price the player pays to buy Count of Definition. */
	UFUNCTION(BlueprintPure, Category = "Merchant")
	int32 GetBuyPrice(const UNexusItemDefinition* Definition, int32 Count) const;

	// Transactions
	/**
	 * Sell Count of Instance from PlayerInventory: remove via the public API and credit the
	 * wallet. A fungible stack sells Count units at unit value; a socketed/customized
	 * instance sells whole at its combined value. Returns false if not sellable / not held.
	 */
	UFUNCTION(BlueprintCallable, Category = "Merchant")
	bool SellInstance(UNexusInventoryComponent* PlayerInventory, UNexusItemInstance* Instance, int32 Count);

	/**
	 * Buy up to Count of Definition into PlayerInventory, clamped by wallet and capacity.
	 * Gives through the acquire façade and charges only for what actually landed. Returns
	 * false if nothing could be bought.
	 */
	UFUNCTION(BlueprintCallable, Category = "Merchant")
	bool BuyDefinition(UNexusInventoryComponent* PlayerInventory, UNexusItemDefinition* Definition, int32 Count);

	/**
	 * Spend Cost to apply a persistent upgrade to Instance: bump StatTag by Delta. Weapon
	 * upgrades are persistent instance stat tags (they save + broadcast for free); the
	 * weapon's effective-stat resolution reading these is a separate weapon-system concern.
	 * Returns false if the wallet can't afford it.
	 */
	UFUNCTION(BlueprintCallable, Category = "Merchant")
	bool UpgradeInstanceStat(UNexusItemInstance* Instance, FGameplayTag StatTag, float Delta, int32 Cost);
};
