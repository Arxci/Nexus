#include "NexusGameplayTags.h"

namespace NexusGameplayTags
{
	// Ability identity tags
	UE_DEFINE_GAMEPLAY_TAG(Ability_Locomotion_Run,         "Ability.Locomotion.Run");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Locomotion_Crouch,         "Ability.Locomotion.Crouch");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Locomotion_Intent_Crouch,         "Ability.Locomotion.Intent.Crouch");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Locomotion_Intent_UnCrouch,         "Ability.Locomotion.Intent.UnCrouch");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Locomotion_Intent_Run,         "Ability.Locomotion.Intent.Run");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Locomotion_Intent_Walk,         "Ability.Locomotion.Intent.Walk");

	// Owned state tags (applied to the ASC while the ability is active)
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Locomotion_Run, "Character.State.Locomotion.Run");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Locomotion_Crouch, "Character.State.Locomotion.Crouch");

	//Input-ID tags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Run,   "Input.Run");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch,   "Input.Crouch");

	//Interaction
	UE_DEFINE_GAMEPLAY_TAG(Interactable_Proximity_PlayerInRange,   "Interactable.Proximity.PlayerInRange");
	UE_DEFINE_GAMEPLAY_TAG(Interactable_State_HasPlayerFocus,   "Interactable.State.HasPlayerFocus");

	// Interaction verbs
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_PickUp,   "Interaction.Verb.PickUp");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Open,     "Interaction.Verb.Open");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Close,    "Interaction.Verb.Close");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Use,      "Interaction.Verb.Use");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Unlock,   "Interaction.Verb.Unlock");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Read,     "Interaction.Verb.Read");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Search,   "Interaction.Verb.Search");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Examine,  "Interaction.Verb.Examine");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Talk,     "Interaction.Verb.Talk");
	UE_DEFINE_GAMEPLAY_TAG(Interaction_Verb_Finisher, "Interaction.Verb.Finisher");

	UE_DEFINE_GAMEPLAY_TAG(Character_State_Examining, "Character.State.Examining");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Staggered, "Character.State.Staggered");
	
	//World Marker
	UE_DEFINE_GAMEPLAY_TAG(WorldMarker_State_Visible,   "WorldMarker.State.Visible");
	UE_DEFINE_GAMEPLAY_TAG(WorldMarker_State_IsFacingCamera,   "WorldMarker.State.IsFacingCamera");
	UE_DEFINE_GAMEPLAY_TAG(WorldMarker_State_HasPlayerFocus,   "WorldMarker.State.HasPlayerFocus");

	// Weapon ability identity
	UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Fire,          "Ability.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Reload,        "Ability.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Aim,           "Ability.Weapon.Aim");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Melee,         "Ability.Weapon.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Inspect,       "Ability.Weapon.Inspect");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Intent_Aim,    "Ability.Weapon.Intent.Aim");
	UE_DEFINE_GAMEPLAY_TAG(Ability_Weapon_Intent_Unaim,  "Ability.Weapon.Intent.Unaim");

	UE_DEFINE_GAMEPLAY_TAG(Character_State_Weapon_Equipped,  "Character.State.Weapon.Equipped");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Weapon_Firing,    "Character.State.Weapon.Firing");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Weapon_Reloading, "Character.State.Weapon.Reloading");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Weapon_Aiming,    "Character.State.Weapon.Aiming");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Weapon_Swapping,  "Character.State.Weapon.Swapping");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Weapon_Meleeing,  "Character.State.Weapon.Meleeing");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Fire,     "Input.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Reload,   "Input.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Aim,      "Input.Weapon.Aim");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Melee,    "Input.Weapon.Melee");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_SwapNext, "Input.Weapon.SwapNext");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_SwapPrev, "Input.Weapon.SwapPrev");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Slot1,    "Input.Weapon.Slot1");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Weapon_Slot2,    "Input.Weapon.Slot2");

	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Primary,   "Equipment.Slot.Primary");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Secondary, "Equipment.Slot.Secondary");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Utility,   "Equipment.Slot.Utility");
	UE_DEFINE_GAMEPLAY_TAG(Equipment_Slot_Body,      "Equipment.Slot.Body");

	UE_DEFINE_GAMEPLAY_TAG(Damage_Type_Ballistic, "Damage.Type.Ballistic");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Type_Shotgun,   "Damage.Type.Shotgun");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Type_Melee,     "Damage.Type.Melee");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Type_Fire,      "Damage.Type.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Type_Explosive, "Damage.Type.Explosive");

	UE_DEFINE_GAMEPLAY_TAG(Damage_Context_Headshot, "Damage.Context.Headshot");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Context_Critical, "Damage.Context.Critical");
	UE_DEFINE_GAMEPLAY_TAG(Damage_Context_Stagger,  "Damage.Context.Stagger");

	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Weapon,     "Item.Category.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Ammo,       "Item.Category.Ammo");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Consumable, "Item.Category.Consumable");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Key,        "Item.Category.Key");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Document,   "Item.Category.Document");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Armor,      "Item.Category.Armor");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Treasure,   "Item.Category.Treasure");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Charm,      "Item.Category.Charm");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Gem,        "Item.Category.Gem");

	UE_DEFINE_GAMEPLAY_TAG(Charm_Slot_1,             "Charm.Slot.1");
	UE_DEFINE_GAMEPLAY_TAG(Charm_Slot_2,             "Charm.Slot.2");
	UE_DEFINE_GAMEPLAY_TAG(Charm_Slot_3,             "Charm.Slot.3");

	UE_DEFINE_GAMEPLAY_TAG(Item_Section_Grid,        "Item.Section.Grid");
	UE_DEFINE_GAMEPLAY_TAG(Item_Section_KeyItems,    "Item.Section.KeyItems");
	UE_DEFINE_GAMEPLAY_TAG(Item_Section_Treasures,   "Item.Section.Treasures");
	UE_DEFINE_GAMEPLAY_TAG(Item_Section_Box,         "Item.Section.Box");

	UE_DEFINE_GAMEPLAY_TAG(Stat_Ammo_InMagazine, "Stat.Ammo.InMagazine");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Durability,      "Stat.Durability");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Charges,         "Stat.Charges");

	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_Damage,           "Stat.Weapon.Damage");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_RPM,              "Stat.Weapon.RPM");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_MagazineSize,     "Stat.Weapon.MagazineSize");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_MaxRange,         "Stat.Weapon.MaxRange");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_RecoilVertical,   "Stat.Weapon.RecoilVertical");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_RecoilHorizontal, "Stat.Weapon.RecoilHorizontal");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_SpreadHip,        "Stat.Weapon.SpreadHip");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_SpreadADS,        "Stat.Weapon.SpreadADS");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_ADSTime,          "Stat.Weapon.ADSTime");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Weapon_ReloadDuration,   "Stat.Weapon.ReloadDuration");

	UE_DEFINE_GAMEPLAY_TAG(Stat_Melee_Damage,      "Stat.Melee.Damage");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Melee_Range,       "Stat.Melee.Range");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Melee_SwingRate,   "Stat.Melee.SwingRate");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Melee_StaminaCost, "Stat.Melee.StaminaCost");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Melee_Knockback,   "Stat.Melee.Knockback");

	UE_DEFINE_GAMEPLAY_TAG(Attachment_Slot_Slide,       "Attachment.Slot.Slide");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Slot_Sight,       "Attachment.Slot.Sight");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Slot_Magazine,    "Attachment.Slot.Magazine");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Slot_Barrel,      "Attachment.Slot.Barrel");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Slot_Trigger,     "Attachment.Slot.Trigger");

	UE_DEFINE_GAMEPLAY_TAG(Attachment_Type_Slide,     "Attachment.Type.Slide");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Type_Sight,     "Attachment.Type.Sight");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Type_Magazine,  "Attachment.Type.Magazine");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Type_Barrel,    "Attachment.Type.Barrel");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Type_Trigger,   "Attachment.Type.Trigger");

	UE_DEFINE_GAMEPLAY_TAG(Attachment_Identity_Slide_Standard,    "Attachment.Identity.Slide.Standard");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Identity_Sight_Standard,    "Attachment.Identity.Sight.Standard");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Identity_Magazine_Standard, "Attachment.Identity.Magazine.Standard");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Identity_Barrel_Standard,   "Attachment.Identity.Barrel.Standard");
	UE_DEFINE_GAMEPLAY_TAG(Attachment_Identity_Trigger_Standard,   "Attachment.Identity.Trigger.Standard");
	
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Unholster,           "Action.Equipment.Unholster");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Holster,             "Action.Equipment.Holster");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Inspect,             "Action.Equipment.Inspect");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Ceremony,            "Action.Equipment.Ceremony");

	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_Fire,         "Action.Equipment.Weapon.Fire");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_DryFire,      "Action.Equipment.Weapon.DryFire");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_Reload,       "Action.Equipment.Weapon.Reload");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_Reload_Empty, "Action.Equipment.Weapon.Reload.Empty");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_MagOut,       "Action.Equipment.Weapon.MagOut");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_MagIn,        "Action.Equipment.Weapon.MagIn");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_SlideRack,    "Action.Equipment.Weapon.SlideRack");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_BoltClose,    "Action.Equipment.Weapon.BoltClose");

	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_MeleeLight,   "Action.Equipment.Weapon.MeleeLight");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_MeleeHeavy,   "Action.Equipment.Weapon.MeleeHeavy");
	UE_DEFINE_GAMEPLAY_TAG(Action_Equipment_Weapon_Bash,         "Action.Equipment.Weapon.Bash");
}

