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

	// Weapon input
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Fire);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Reload);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Aim);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Melee);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_SwapNext);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_SwapPrev);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Slot1);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Weapon_Slot2);

	// Equipment slots (used as keys in EquipmentComponent::EquippedSlots)
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

	// Item identity roots (children authored as data-driven tags per item)
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Weapon);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Ammo);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Consumable);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Key);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Category_Document);

	// Stat tag roots stored on UNexusItemInstance::StatTags
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Ammo_InMagazine);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Durability);
	NEXUS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stat_Charges);
}