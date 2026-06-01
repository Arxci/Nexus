#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Case.generated.h"


/**
 * Marks an item as an attaché *case* — the container itself, not something stored in it.
 * The equipped case drives the inventory's spatial-grid dimensions and exposes the charm
 * slots a player can socket charms into (charms grant passive bonuses through the same
 * PassiveEquipment path as armor; see FNexusFragment_Charm).
 *
 * A case is held by the inventory component as its EquippedCase (separate from the grid
 * contents); swapping the equipped case re-lays-out the spatial section, and items that no
 * longer fit follow the designer spill policy (auto-send to the item box).
 */
USTRUCT(BlueprintType, DisplayName = "Case")
struct NEXUS_API FNexusFragment_Case : public FNexusItemFragment
{
	GENERATED_BODY()

	/** Spatial-grid size this case provides, in cells (Width x Height). Min 1x1 at read sites. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Case")
	FIntPoint GridSize = FIntPoint(8, 6);

	/**
	 * Charm slots this case exposes. A charm is socketed into one of these by tag; the
	 * socketed charm's identity persists as per-instance state on the case instance.
	 * Empty = a case with no charm slots.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Case",
		meta = (Categories = "Charm.Slot"))
	FGameplayTagContainer CharmSlots;

	/**
	 * Marks this as the fallback starting case. Informational for tooling/selection UI;
	 * the inventory component equips a specific DefaultCaseDefinition rather than scanning
	 * for this flag, so leaving it false changes no runtime behaviour.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Case")
	bool bDefaultCase = false;
};
