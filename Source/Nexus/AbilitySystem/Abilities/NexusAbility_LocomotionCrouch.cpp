// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionCrouch.h"
#include "GameFramework/Character.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionCrouch::UNexusAbility_LocomotionCrouch()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Crouch);
	InputTag = NexusGameplayTags::InputTag_Crouch;
}

void UNexusAbility_LocomotionCrouch::OnActivateAbility()
{
	Super::OnActivateAbility();
	
	if (const ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		if (UNexusCharacterMovementComponent* MoveComp = Cast<UNexusCharacterMovementComponent>(Char->GetCharacterMovement()))
		{
			MoveComp->Crouch();
		}
	}
}

void UNexusAbility_LocomotionCrouch::OnDeactivateAbility() 
{
	Super::OnDeactivateAbility();
	
	if (const ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		if (UNexusCharacterMovementComponent* MoveComp = Cast<UNexusCharacterMovementComponent>(Char->GetCharacterMovement()))
		{
			MoveComp->UnCrouch();
		}
	}
}

bool UNexusAbility_LocomotionCrouch::CanActivateAbility_Implementation() const
{
	return Super::CanActivateAbility_Implementation();
}

