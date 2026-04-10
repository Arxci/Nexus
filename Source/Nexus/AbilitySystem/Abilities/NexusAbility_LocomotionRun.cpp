// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionRun.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"

UNexusAbility_LocomotionRun::UNexusAbility_LocomotionRun()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Locomotion.Run")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.State.Locomotion.Run")));
}

bool UNexusAbility_LocomotionRun::CanActivateAbility_Implementation() const
{
	const ACharacter* Char = Cast<ACharacter>(GetAvatarActor());
	if (!Char) return false;

	const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
	if (!MoveComp || !MoveComp->IsMovingOnGround()) return false;

	const FVector InputVector = MoveComp->GetLastInputVector();
	if (InputVector.IsNearlyZero()) return false;

	const FVector Forward = Char->GetActorForwardVector();
	return FVector::DotProduct(Forward, InputVector.GetSafeNormal()) > 0.0f;
}

void UNexusAbility_LocomotionRun::OnActivateAbility()
{
	if (const ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		if (UNexusCharacterMovementComponent* MoveComp = Cast<UNexusCharacterMovementComponent>(Char->GetCharacterMovement()))
		{
			MoveComp->StartSprinting();
		}
	}

	Super::OnActivateAbility();
}

void UNexusAbility_LocomotionRun::OnDeactivateAbility()
{
	if (const ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		if (UNexusCharacterMovementComponent* MoveComp = Cast<UNexusCharacterMovementComponent>(Char->GetCharacterMovement()))
		{
			MoveComp->StopSprinting();
		}
	}

	Super::OnDeactivateAbility();
}

void UNexusAbility_LocomotionRun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const ACharacter* Char = Cast<ACharacter>(GetAvatarActor());
	if (!Char) return;

	const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
	if (!MoveComp || !MoveComp->IsMovingOnGround())
	{
		EndAbility();
		return;
	}

	const FVector InputVector = MoveComp->GetLastInputVector();
	if (InputVector.IsNearlyZero())
	{
		EndAbility();
		return;
	}
	
	const FVector Forward = Char->GetActorForwardVector();
	const float ForwardDot = FVector::DotProduct(Forward, InputVector.GetSafeNormal());
	
	if (ForwardDot <= 0.0f)
	{
		EndAbility();
	}
}