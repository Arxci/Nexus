#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameplayTagContainer.h"

#include "NexusInventoryAcquireLibrary.generated.h"

class APawn;
class UNexusItemDefinition;
class UNexusItemInstance;


USTRUCT(BlueprintType)
struct NEXUS_API FNexusAcquireResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 AmountAdded = 0;

	/** Count that could not be placed (weight or slot limits). */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 Remainder = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UNexusItemInstance*> NewInstances;

	/**
	 * The slot one of the new instances was assigned to during auto-equip, or
	 * invalid if nothing was auto-equipped (no equippable fragment, no free
	 * compatible slot, fragment vetoed via bAllowAutoAssign, or the caller
	 * passed bAutoEquipIfPossible=false). Only the first eligible instance is
	 * auto-assigned — the rest live in inventory until the player swaps them
	 * in manually.
	 *
	 * Named *Assigned* rather than *Equipped* because the library returns
	 * before the (async) Equipped-bundle load + draw phase complete; the
	 * actor is in the slot but may not be visible yet. Listen on
	 * UNexusEquipmentComponent::OnActiveSlotChanged for the visual transition.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FGameplayTag AssignedSlot;

	/** True when this acquire was the first time Recipient's inventory saw Definition. */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	bool bWasFirstAcquire = false;
};


/**
 * Single entry point for "give an item to this pawn." Handles AddItem, optional
 * stat-tag seeding for new instances, mark-seen bookkeeping, and the auto-equip-
 * with-correct-action-tag routing (Action.Equipment.Ceremony on first acquire,
 * Action.Equipment.Unholster afterwards).
 *
 * Pickup actors, debug commands, loot drops, quest rewards, and cheats all go
 * through here so behaviour is consistent across call sites. The pickup actor
 * is the canonical caller — ANexusItemPickup::HandleInteractionCompleted is the
 * full extent of its acquire logic.
 *
 * Auto-equip rules:
 *   - bAutoEquipIfPossible must be true.
 *   - Recipient must carry both UNexusInventoryComponent and UNexusEquipmentComponent.
 *   - Instance must have an FNexusFragment_Equippable with bAllowAutoAssign=true.
 *   - Equipment->PickAutoAssignSlot must return a valid (free, compatible) slot.
 *
 * Any of those failing causes the item to stay in inventory unequipped — the
 * acquire succeeds, the auto-equip is silently skipped. No-op on first-acquire
 * ceremony when the equippable hasn't authored Action.Equipment.Ceremony —
 * the equipment component falls back to Action.Equipment.Unholster automatically.
 *
 * bSkipCeremony forces the unholster action even on a first acquire — debug
 * "give me a gun" commands set this true so a silent give doesn't trigger the
 * cinematic intro.
 */
UCLASS()
class NEXUS_API UNexusInventoryAcquireLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory|Acquire",
		meta = (AutoCreateRefTerm = "InitialStatTags"))
	static FNexusAcquireResult AcquireItem(
		APawn* Recipient,
		UNexusItemDefinition* Definition,
		int32 Count,
		bool bAutoEquipIfPossible,
		bool bSkipCeremony,
		const TMap<FGameplayTag, int32>& InitialStatTags);
};
