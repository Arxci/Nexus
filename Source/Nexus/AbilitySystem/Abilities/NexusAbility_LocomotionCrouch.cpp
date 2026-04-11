// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionCrouch.h"
#include "GameFramework/Character.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionCrouch::UNexusAbility_LocomotionCrouch()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Crouch);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Run);
	InputTag = NexusGameplayTags::InputTag_Crouch;
}

void UNexusAbility_LocomotionCrouch::OnActivateAbility()
{
	Super::OnActivateAbility();
	
	if (ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		Char->Crouch();
	}
}

void UNexusAbility_LocomotionCrouch::OnDeactivateAbility() 
{
	Super::OnDeactivateAbility();
	if (ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		Char->UnCrouch();
	}
}


