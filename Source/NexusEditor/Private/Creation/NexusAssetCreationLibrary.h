#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UNexusItemDefinition;
class UNexusAttachmentDefinition;
class UNexusCombinationRecipe;
class UNexusLevelManifest;
class UNexusEquipmentLoadout;

/**
 * Which kind of item to stamp out. Each template decides the category tag, grid
 * footprint, and the fragments pre-added to the new UNexusItemDefinition, so a
 * freshly created asset is already a working skeleton the designer only has to
 * name + tweak — not an empty asset they have to assemble fragment by fragment.
 */
enum class ENexusItemTemplate : uint8
{
	RangedWeapon,
	MeleeWeapon,
	Consumable,
	Ammo,
	Treasure,
	KeyItem,
	Charm,
	Generic,
};

/** Outcome of trying to slot a freshly created attachment onto an item. */
enum class ENexusAttachResult : uint8
{
	Assigned,     // dropped into an existing empty slot
	CreatedSlot,  // the item had no slot of this type, so one was added
	AllFilled,    // matching slot(s) exist but every one is already filled
	NoEquippable, // the item has no equippable fragment to attach to
};

/**
 * Asset-stamping helpers behind the Nexus Asset Creator window (and reusable by a
 * future right-click factory). Each Create* call makes a real, unsaved asset in a
 * package under PackagePath, pre-fills it for its template, registers it with the
 * asset registry, and marks it dirty — the caller then edits it in a details panel
 * and saves through the normal editor flow.
 *
 * Editor-only; never compiled into a cooked build (it lives in NexusEditor).
 */
struct FNexusAssetCreation
{
	/** A pre-filled item asset (correct category tag, grid, and fragments). Null + OutError on failure. */
	static UNexusItemDefinition* CreateItem(
		ENexusItemTemplate Template, const FString& PackagePath, const FString& DesiredName, FText& OutError);

	/** A pre-filled attachment whose ProvidedTags include TypeTag (e.g. Attachment.Type.Sight). */
	static UNexusAttachmentDefinition* CreateAttachment(
		const FGameplayTag& TypeTag, const FString& PackagePath, const FString& DesiredName, FText& OutError);

	/**
	 * Slot Attachment onto Weapon's equippable fragment: fill the first empty slot that
	 * accepts TypeTag, or — if the item has no slot of that type — add one and fill it.
	 * OutSlotName gets the slot's short name. See ENexusAttachResult for the outcomes.
	 * Marks Weapon dirty.
	 */
	static ENexusAttachResult AssignOrCreateSlot(
		UNexusItemDefinition* Weapon, UNexusAttachmentDefinition* Attachment,
		const FGameplayTag& TypeTag, FString& OutSlotName);

	/** Human label + default asset name for a template (used by the window's buttons). */
	static FText TemplateLabel(ENexusItemTemplate Template);
	static FString TemplateDefaultName(ENexusItemTemplate Template);

	/** Per-type destination subfolder for routing, e.g. RangedWeapon -> "Weapons". */
	static FString SubfolderForTemplate(ENexusItemTemplate Template);

	/** Duplicate an existing item/attachment asset into PackagePath. Null + OutError on failure. */
	static UObject* DuplicateAsset(UObject* Source, const FString& PackagePath, FText& OutError);

	/**
	 * Derive a unique IdentityTag from the asset's name (e.g. Item.Identity.Weapon.MyPistol),
	 * register it as a project gameplay tag, and assign it to the asset. Returns the tag, or an
	 * invalid tag + OutError if the asset isn't a Nexus item/attachment.
	 */
	static FGameplayTag DeriveAndAssignIdentityTag(UObject* Asset, FText& OutError);

	/** A blank combination recipe; if Output is set, seeds the recipe's Output with it. */
	static UNexusCombinationRecipe* CreateRecipe(
		const FString& PackagePath, const FString& DesiredName, UNexusItemDefinition* Output, FText& OutError);

	/** A blank level manifest (the populated-from-level version is FNexusManifestBuilder). */
	static UNexusLevelManifest* CreateManifest(
		const FString& PackagePath, const FString& DesiredName, FText& OutError);

	/** A blank equipment loadout (a character's slot definitions). */
	static UNexusEquipmentLoadout* CreateLoadout(
		const FString& PackagePath, const FString& DesiredName, FText& OutError);
};
