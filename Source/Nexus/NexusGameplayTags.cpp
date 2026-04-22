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
}