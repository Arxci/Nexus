// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionRun.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UNexusAbility_LocomotionRun::CanActivateAbility_Implementation() const
{
	const ACharacter* Char = Cast<ACharacter>(GetAvatarActor());
	if (!Char) return false;

	const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
	return MoveComp && MoveComp->IsMovingOnGround();
}

void UNexusAbility_LocomotionRun::OnActivateAbility()
{
	if (ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		if (UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
		{
			CachedWalkSpeed = MoveComp->MaxWalkSpeed;
			MoveComp->MaxWalkSpeed = SprintSpeed;
		}
	}

	Super::OnActivateAbility();
}

void UNexusAbility_LocomotionRun::OnDeactivateAbility()
{
	if (ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		if (UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement())
		{
			MoveComp->MaxWalkSpeed = CachedWalkSpeed;
		}
	}

	Super::OnDeactivateAbility();
}