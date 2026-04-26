#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "NexusFragment_Consumable.generated.h"

class UNexusAbility;
class UNexusItemInstance;

/**
 * Item can be consumed from the inventory UI.
 *
 * On consume, UNexusInventoryComponent::ConsumeItem grants and activates
 * UseAbilityClass on the consumer's ASC, then decrements stack / charges.
 * When the resulting count reaches zero, the instance is destroyed unless
 * bRetainEmptyInstance is set (e.g. an empty water bottle that can be refilled).
 */
USTRUCT(BlueprintType, DisplayName = "Consumable")
struct NEXUS_API FNexusFragment_Consumable : public FNexusItemFragment
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UNexusAbility> UseAbilityClass;

	/**
	 * Charges per pickup. 0 = consume from StackCount (typical for stackables like
	 * herbs/ammo crates). >0 = seed Stat.Charges and consume from there (typical
	 * for non-stackable consumables like a med-spray with 3 uses).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0"))
	int32 ChargesPerPickup = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRetainEmptyInstance = false;

	/** Tags required on the consumer for the use ability to even attempt activation. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer ConsumerRequiredTags;

	virtual void InitializeInstance(UNexusItemInstance* Instance) const override;
};