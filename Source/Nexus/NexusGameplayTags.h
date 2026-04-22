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
}