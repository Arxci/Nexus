#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "NexusMerchantSubsystem.generated.h"

class UNexusAssemblyComponent;
class UNexusAttachmentDefinition;
class UNexusInventoryComponent;
class UNexusItemDefinition;
class UNexusItemInstance;


/**
 * Snapshot of one weapon upgrade track for a specific instance, for the gunsmith
 * UI: where the player is on the track and what the next tier costs. Derived from
 * the weapon's authored tiers + the instance's persisted upgrade stat — nothing
 * is stored here.
 */
USTRUCT(BlueprintType, DisplayName = "Weapon Upgrade State")
struct NEXUS_API FNexusWeaponUpgradeState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag StatTag;

	/** Current tier the instance has reached (0 = no upgrade). */
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentTier = 0;

	/** Total number of tiers on the track (the cap). 0 = no track authored. */
	UPROPERTY(BlueprintReadOnly)
	int32 MaxTier = 0;

	/** True when CurrentTier == MaxTier — nothing left to buy. */
	UPROPERTY(BlueprintReadOnly)
	bool bAtCap = false;

	/** Currency cost of the next tier (0 at cap). */
	UPROPERTY(BlueprintReadOnly)
	int32 NextCost = 0;

	/** Cumulative upgrade delta currently applied. */
	UPROPERTY(BlueprintReadOnly)
	float CurrentValue = 0.0f;

	/** Cumulative upgrade delta after buying the next tier (== CurrentValue at cap). */
	UPROPERTY(BlueprintReadOnly)
	float NextValue = 0.0f;
};


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

	// Attachments (merchant-menu unlock model: charge + install via the public
	// assembly API; no inventory-item footprint, removal returns nothing).
	/**
	 * Charge Cost and install Definition into SlotID on a live weapon's Assembly.
	 * Validates compatibility + constraints first (CanAttachItem), debits the wallet,
	 * then calls the public AttachItem (which persists the choice to the instance and
	 * updates the live weapon's mesh / stats / montage overrides without a respawn).
	 * Refunds on a late failure. Returns false if incompatible, unaffordable, or no
	 * assembly.
	 */
	UFUNCTION(BlueprintCallable, Category = "Merchant")
	bool InstallAttachment(UNexusAssemblyComponent* Assembly, FGameplayTag SlotID,
		UNexusAttachmentDefinition* Definition, int32 Cost);

	/** Remove the attachment in SlotID from Assembly (free; nothing returned to inventory). */
	UFUNCTION(BlueprintCallable, Category = "Merchant")
	bool UninstallAttachment(UNexusAssemblyComponent* Assembly, FGameplayTag SlotID);

	// Upgrades (discrete tiers)
	/** Where Instance sits on StatTag's upgrade track and what the next tier costs (for the gunsmith UI). */
	UFUNCTION(BlueprintPure, Category = "Merchant")
	FNexusWeaponUpgradeState GetUpgradeState(const UNexusItemInstance* Instance, FGameplayTag StatTag) const;

	/**
	 * Buy the next tier on StatTag's track for Instance: enforces the cap, charges
	 * the tier cost, applies the cumulative delta to the instance's persistent stat
	 * tag, and refreshes LiveAssembly (if the weapon is equipped) so the tune-up
	 * shows immediately. Returns false at cap / unaffordable / no track.
	 */
	UFUNCTION(BlueprintCallable, Category = "Merchant")
	bool PurchaseNextUpgradeTier(UNexusItemInstance* Instance, FGameplayTag StatTag,
		UNexusAssemblyComponent* LiveAssembly = nullptr);

	/**
	 * Low-level upgrade primitive: spend Cost, bump StatTag by Delta on Instance
	 * (persists + broadcasts; folds into the effective-stat resolution as a final
	 * additive tier), and refresh LiveAssembly if provided so a live weapon updates
	 * without a respawn. PurchaseNextUpgradeTier is the tiered front door; this is
	 * exposed for bespoke/continuous upgrade flows. Returns false if unaffordable.
	 */
	UFUNCTION(BlueprintCallable, Category = "Merchant")
	bool UpgradeInstanceStat(UNexusItemInstance* Instance, FGameplayTag StatTag, float Delta, int32 Cost,
		UNexusAssemblyComponent* LiveAssembly = nullptr);
};
