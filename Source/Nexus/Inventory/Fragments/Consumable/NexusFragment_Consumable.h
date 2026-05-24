#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Consumable.generated.h"


/**
 * Marks an item as usable (the herb / first-aid / pill side of the genre) and
 * carries the minimal data UseItem needs. Deliberately small — this is the
 * foundation, not the whole healing system. Richer behaviour (cure status,
 * over-time effects, partial-heal animation) is added as more fields here or as
 * sibling fragments, the same way the weapon fragment grew.
 *
 * Applied through UNexusInventoryAcquireLibrary::UseItem, which reads this
 * fragment, applies the heal to the user's UNexusHealthComponent, and consumes
 * one from the stack when bConsumeOnUse is set.
 */
USTRUCT(BlueprintType, DisplayName = "Consumable")
struct NEXUS_API FNexusFragment_Consumable : public FNexusItemFragment
{
	GENERATED_BODY()

	/** Health restored on use. 0 = this consumable doesn't heal (e.g. a future cure-only item). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Consumable", meta = (ClampMin = "0.0"))
	float HealAmount = 0.0f;

	/** When true, a successful use removes one from the stack. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Consumable")
	bool bConsumeOnUse = true;
};