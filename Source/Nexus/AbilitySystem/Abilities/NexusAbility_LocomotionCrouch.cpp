// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionCrouch.h"
#include "GameFramework/Character.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionCrouch::UNexusAbility_LocomotionCrouch()
{
	AbilityTag = NexusGameplayTags::Ability_Locomotion_Intent_Crouch;
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Locomotion_Run);
}

void UNexusAbility_LocomotionCrouch::HandleAbilityProgress()
{
	
}

void UNexusAbility_LocomotionCrouch::HandleAbilityStart()
{
	
}

void UNexusAbility_LocomotionCrouch::HandleAbilityStop()
{
	
}

bool UNexusAbility_LocomotionCrouch::CanActivateAbility_Implementation() const
{
	return true;
}


bool UNexusAbility_LocomotionCrouch::OnRequestActivateAbility()
{
	if (!Super::OnRequestActivateAbility()) return false;

	if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
	{
		Char->Crouch();
	}
	return true;
}

bool UNexusAbility_LocomotionCrouch::OnRequestDeactivateAbility(bool bForce)
{
	if (!Super::OnRequestDeactivateAbility(bForce)) return false;

	if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
	{
		Char->UnCrouch();
	}
	return true;
}