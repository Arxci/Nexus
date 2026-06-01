#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Charm.generated.h"

class UNexusAbility;


/**
 * Marks an item as a charm — socketed into the equipped case's charm slots (not the
 * equipment passive slots), it grants a passive bonus to the host. Charms deliberately
 * carry the *same* payload shape as FNexusFragment_PassiveEquipment (granted abilities +
 * loose tags) so a charm and a piece of armor apply through one mechanism: the case-charm
 * consumer grants/removes these on the host ASC exactly the way the equipment component
 * does for passive armor. No parallel effect system.
 *
 * Phase 3 carries the data + per-instance socket persistence; the consumer that applies
 * these to the ASC is wired in a later phase.
 */
USTRUCT(BlueprintType, DisplayName = "Charm")
struct NEXUS_API FNexusFragment_Charm : public FNexusItemFragment
{
	GENERATED_BODY()

	/**
	 * Passive abilities granted to the host ASC while this charm is socketed in the
	 * equipped case. Removed by handle when the charm is unsocketed (mirrors armor).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Charm")
	TArray<TSubclassOf<UNexusAbility>> GrantedAbilities;

	/**
	 * Loose gameplay tags applied to the host ASC while socketed (e.g.
	 * Character.State.Charm.ExtraRecoilControl). Reference-counted by the ASC, removed
	 * when the charm is unsocketed.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Charm")
	FGameplayTagContainer GrantedTags;
};
