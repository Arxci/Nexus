#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "NexusFragment_KeyItem.generated.h"

/**
 * Item is a key/quest object. Locks ask the inventory for any item carrying a
 * matching UnlockTag — no direct asset references between locks and keys.
 *
 * Examples:
 *   - DA_Item_KeyL2 has UnlockTag = "Key.Building.Police.L2"
 *   - BP_Door_PoliceL2 queries Inventory->HasItemWithUnlockTag("Key.Building.Police.L2")
 *   - DA_Item_Fuse has UnlockTag = "Key.Generator.Fuse" and bConsumeOnUse = true
 */
USTRUCT(BlueprintType, DisplayName = "Key Item")
struct NEXUS_API FNexusFragment_KeyItem : public FNexusItemFragment
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Key"))
	FGameplayTag UnlockTag;

	/** If true, consumed when used (one-shot fuse, single-use keycard). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bConsumeOnUse = false;

	/** If true, cannot be dropped or sold by the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bQuestLocked = true;
};