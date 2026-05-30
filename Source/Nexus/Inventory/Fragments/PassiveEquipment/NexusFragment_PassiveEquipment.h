#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_PassiveEquipment.generated.h"

class UNexusAbility;


/**
 * Marks an item as passive equipment — armor, a charm, a trinket. An item that
 * carries only this fragment slots into a bIsPassive=true slot. On assign the
 * equipment component grants these effects through the host ASC (looked up via
 * INexusAbilitySystemInterface); on clear it removes them by the handles it
 * tracked. No in-world actor is spawned and no montage plays — this is how armor
 * works on day one with zero new visual-asset work.
 *
 * This project's ability system is tag- and ability-driven rather than GAS
 * GameplayEffect-driven, so a passive "effect" is expressed as the abilities and
 * owned tags it grants while assigned: e.g. a damage-reduction passive ability
 * plus a Character.State.Armored tag the health component reads. Visible armor
 * (a mesh on a body socket) is a deferred v2 extension to this fragment — add an
 * optional SocketName + AttachMesh here and have the component spawn an attach
 * component on assign; the slot logic stays unchanged.
 */
USTRUCT(BlueprintType, DisplayName = "Passive Equipment")
struct NEXUS_API FNexusFragment_PassiveEquipment : public FNexusItemFragment
{
	GENERATED_BODY()

	/**
	 * Passive abilities granted to the host ASC while this item is assigned — the
	 * stat-effect side of armor / charm items (damage reduction, regen, carry-weight).
	 * Removed by handle when the slot is cleared.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Passive Equipment")
	TArray<TSubclassOf<UNexusAbility>> GrantedAbilities;

	/**
	 * Loose gameplay tags applied to the host ASC while assigned (e.g.
	 * Character.State.Armored). Reference-counted by the ASC, so two passives that
	 * grant the same tag coexist, and removed when the slot is cleared.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Passive Equipment")
	FGameplayTagContainer GrantedTags;
};