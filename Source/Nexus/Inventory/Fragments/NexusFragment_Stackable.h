#pragma once

#include "CoreMinimal.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "NexusFragment_Stackable.generated.h"

/**
 * Item can stack within a single inventory slot. Without this fragment, an
 * item is treated as unique (each pickup occupies its own slot).
 */
USTRUCT(BlueprintType, DisplayName = "Stackable")
struct NEXUS_API FNexusFragment_Stackable : public FNexusItemFragment
{
	GENERATED_BODY()

	/** Hard cap per stack. RE4-style ammo stacks (e.g. 50) are typical. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 MaxStackSize = 99;
};