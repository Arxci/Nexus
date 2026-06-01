#pragma once

#include "NativeGameplayTags.h"

namespace NexusGameplayTags
{

	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Locomotion_Run);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Locomotion_Crouch);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Locomotion_Intent_Crouch);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Locomotion_Intent_UnCrouch);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Locomotion_Intent_Run);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Locomotion_Intent_Walk);

	// Owned state tags (applied to the ASC while the ability is active)
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Locomotion_Run);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Locomotion_Crouch);

	//Input-ID tags
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Run);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);

	//Interaction
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interactable_Proximity_PlayerInRange);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Interactable_State_HasPlayerFocus);


	//World Marker
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WorldMarker_State_Visible);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WorldMarker_State_IsFacingCamera);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WorldMarker_State_HasPlayerFocus);

	// Weapon ability identity
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Fire);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Reload);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Aim);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Melee);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Inspect);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Intent_Aim);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Weapon_Intent_Unaim);

	// Weapon owned-state tags
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Weapon_Equipped);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Weapon_Firing);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Weapon_Reloading);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Weapon_Aiming);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Weapon_Swapping);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Character_State_Weapon_Meleeing);

	// Weapon input
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Fire);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Reload);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Aim);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Melee);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_SwapNext);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_SwapPrev);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Slot1);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Slot2);

	// Equipment slot identity. Slots are data-driven (UNexusEquipmentLoadout); these
	// are common roots shipped in C++ and used as runtime keys by the equipment component.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Slot_Primary);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Slot_Secondary);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Slot_Utility);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Equipment_Slot_Body);

	// Damage type taxonomy (parent: Damage.Type)
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Ballistic);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Shotgun);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Melee);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Fire);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Explosive);

	// Damage context taxonomy (parent: Damage.Context). Branchable per-hit context the
	// SOURCE computes (weak-point / headshot / stagger) so AI, FX and HUD can react.
	// Conveyed on FNexusDamageContext::ContextTags; the receiver still owns the numeric
	// bone / resistance multipliers — these tags only classify the hit, never apply damage.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Context_Headshot);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Context_Critical);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Context_Stagger);

	// Item identity roots (children authored as data-driven tags per item)
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Weapon);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Ammo);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Consumable);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Key);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Document);
	// Passive-equipment category (armor / charms). Slotted into a bIsPassive slot
	// whose AcceptedItemTags include this; carried by items with a PassiveEquipment fragment.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Armor);
	// Sellable valuables (gems / idols / RE-style treasures). Routed to the Treasures
	// list section; carried by items with a Treasure fragment.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Treasure);
	// Charm items — slotted into the equipped case's charm slots; grant passive bonuses
	// via the same PassiveEquipment path as armor. Carried by items with a Charm fragment.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Charm);
	// Gems — sellable valuables that also socket into treasures. A gem typically carries
	// both Item.Category.Treasure (routes to the Treasures list) and Item.Category.Gem
	// (a treasure socket's AcceptedGemCategory accepts it).
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Gem);

	// Charm slot identity exposed by a case (FNexusFragment_Case::CharmSlots). Common roots
	// shipped in C++; cases pick which they expose and charms socket into them by tag.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Charm_Slot_1);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Charm_Slot_2);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Charm_Slot_3);

	// Inventory section identity. A sectioned container routes items to one of these by
	// CategoryTags: the spatial attaché grid, or the non-spatial Key Items / Treasures
	// lists that consume zero grid cells. Used as section keys by UI and the container.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Section_Grid);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Section_KeyItems);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Section_Treasures);
	// The item box's single non-spatial storage section (unlimited stash).
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Section_Box);

	// Stat tag roots stored on UNexusItemInstance::StatTags
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Ammo_InMagazine);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Durability);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Charges);

	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_Damage);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_RPM);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_MagazineSize);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_MaxRange);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_RecoilVertical);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_RecoilHorizontal);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_SpreadHip);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_SpreadADS);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_ADSTime);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Weapon_ReloadDuration);

	// Melee effective-stat keys (parent: Stat.Melee). Seeded by FWeaponMeleeSpec and
	// folded through the SAME assembly resolution as Stat.Weapon.*, so a melee attachment
	// or merchant tune-up applies for free. Durability persists on the instance as the
	// shared Stat.Durability key, not here (it's per-instance state, not a resolved stat).
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Melee_Damage);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Melee_Range);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Melee_SwingRate);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Melee_StaminaCost);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Melee_Knockback);

	// Attachment slot identity (used as keys in FAssemblySlotDefinition::SlotID).
	// Slot identity is data-driven — these are common roots shipped in C++.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Slot_Slide);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Slot_Sight);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Slot_Magazine);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Slot_Barrel);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Slot_Trigger);

	// Attachment type taxonomy (used for AcceptedTags / ProvidedTags compatibility).
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Type_Slide);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Type_Sight);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Type_Magazine);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Type_Barrel);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Type_Trigger);

	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Identity_Slide_Standard);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Identity_Sight_Standard);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Identity_Magazine_Standard);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Identity_Barrel_Standard);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attachment_Identity_Trigger_Standard);

	// Equipment-side action tags. Used as keys in FEquippableAnimationSet::Actions
	// (where each entry pairs an arms montage with an item-mesh montage) and on
	// UNexusAttachmentDefinition::ActionOverrides so attachments can override
	// either stream. Also used by UNexusAnimNotify_EquipmentAction to drive
	// item-mesh playback from the arms montage at the correct frame.
	//
	// All actions live under Action.Equipment.* so the notify's tag picker has
	// a single root. Generic actions (Unholster, Holster, Ceremony, Inspect)
	// apply to any modular equippable; the Action.Equipment.Weapon.* subspace
	// holds actions that only make sense on a weapon (Fire / Reload / MagOut /
	// etc). Future equippable categories — flashlight, radio, tome — can
	// claim their own subspace (Action.Equipment.Flashlight.ToggleBeam, etc.)
	// without touching this list.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Unholster);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Holster);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Inspect);

	/**
	 * First-acquire flourish authored on FEquippableAnimationSet::Actions.
	 * UNexusInventoryAcquireLibrary::AcquireItem routes the draw phase through
	 * this action tag the first time an equippable definition enters inventory;
	 * subsequent activations use Action.Equipment.Unholster. UNexusEquipmentComponent
	 * falls back to Action.Equipment.Unholster if the ceremony stream isn't authored,
	 * so leaving the slot blank just means "no special intro for this item."
	 */
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Ceremony);

	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_Fire);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_DryFire);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_Reload);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_Reload_Empty);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_MagOut);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_MagIn);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_SlideRack);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_BoltClose);

	// Melee swing actions (parent: Action.Equipment.Weapon). Resolved through the SAME
	// assembly override-then-fallback walk as Fire/Reload, so an attachment (e.g. a
	// bayonet) can override a weapon's bash animation with no weapon-side branch. Bash is
	// the contextual melee on a ranged weapon; MeleeLight/Heavy are a melee weapon's swings.
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_MeleeLight);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_MeleeHeavy);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Action_Equipment_Weapon_Bash);
}