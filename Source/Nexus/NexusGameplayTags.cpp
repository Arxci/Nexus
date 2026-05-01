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

	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Weapon,     "Item.Category.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Ammo,       "Item.Category.Ammo");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Consumable, "Item.Category.Consumable");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Key,        "Item.Category.Key");
	UE_DEFINE_GAMEPLAY_TAG(Item_Category_Document,   "Item.Category.Document");

	UE_DEFINE_GAMEPLAY_TAG(Stat_Ammo_InMagazine, "Stat.Ammo.InMagazine");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Durability,      "Stat.Durability");
	UE_DEFINE_GAMEPLAY_TAG(Stat_Charges,         "Stat.Charges");
}