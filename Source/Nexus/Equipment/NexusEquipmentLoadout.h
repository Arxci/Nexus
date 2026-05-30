#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "NexusEquipmentLoadout.generated.h"

class UTexture2D;


/**
 * One slot a character exposes. Designers add slots by editing the loadout asset —
 * no C++ change. The slot decides its own mode (in-hand vs passive) and which
 * items it accepts, so the equipment component never hardcodes a slot list.
 */
USTRUCT(BlueprintType, DisplayName = "Equipment Slot")
struct NEXUS_API FNexusEquipmentSlotDef
{
	GENERATED_BODY()

	/** Identity of the slot, e.g. Equipment.Slot.Primary. Used as the runtime key. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot",
		meta = (Categories = "Equipment.Slot"))
	FGameplayTag SlotTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot",
		meta = (AssetBundles = "UI"))
	TSoftObjectPtr<UTexture2D> Icon;

	/**
	 * Item category tags this slot accepts. An item is compatible when its
	 * definition's CategoryTags intersect this container (hierarchical match, so
	 * Item.Weapon.Primary matches an accepted Item.Weapon). Leave empty to accept
	 * any item of the slot's mode — the UI greys targets whose item category
	 * doesn't intersect this set during a drag.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot",
		meta = (Categories = "Item.Category"))
	FGameplayTagContainer AcceptedItemTags;

	/**
	 * true → passive (armor / charm) mode: assigning immediately applies the
	 * item's passive effects through the host ASC, with no in-world actor and no
	 * holster lifecycle. false → in-hand mode: assigning spawns the equipped
	 * actor and the slot participates in the unholster/holster state machine.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot")
	bool bIsPassive = false;

	/** UI ordering; lower sorts first. Also the order cycle-weapon stepping uses. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot")
	int32 SortOrder = 0;

	/** Advisory only — the real input binding lives in the input config, not here. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot")
	FName DefaultInputActionHint;
};


/**
 * Primary data asset defining the slots a character has. One asset per character
 * class — the controlled character, each enemy archetype — assigned on the
 * character's UNexusEquipmentComponent. The component reads its slot definitions from here;
 * adding a slot is a data edit (new tag + new entry + an input binding), never a
 * code change.
 */
UCLASS(BlueprintType)
class NEXUS_API UNexusEquipmentLoadout : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout",
		meta = (TitleProperty = "SlotTag"))
	TArray<FNexusEquipmentSlotDef> Slots;

	/** The slot definition for SlotTag, or null if this loadout doesn't expose it. */
	const FNexusEquipmentSlotDef* FindSlot(FGameplayTag SlotTag) const;

	bool HasSlot(FGameplayTag SlotTag) const { return FindSlot(SlotTag) != nullptr; }

	/** Slot tags in SortOrder (then declaration) order — a stable sequence for UI / cycling. */
	void GetSlotTagsSorted(TArray<FGameplayTag>& OutSlotTags) const;
};