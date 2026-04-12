// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionRun.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionRun::UNexusAbility_LocomotionRun()
{
	AbilityTag = NexusGameplayTags::Ability_Locomotion_Intent_Run;
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Crouch);
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
}

bool UNexusAbility_LocomotionRun::OnRequestActivateAbility()
{
	bIsBoostActive = false;
	return Super::OnRequestActivateAbility();
}

bool UNexusAbility_LocomotionRun::OnRequestDeactivateAbility(bool bForce)
{
	SetBoostActive(false);
	return Super::OnRequestDeactivateAbility(bForce);
}

void UNexusAbility_LocomotionRun::HandleAbilityProgress()
{
	Super::HandleAbilityProgress();

	const bool bShould = ShouldBoostThisFrame();
	if (bShould != bIsBoostActive)
	{
		SetBoostActive(bShould);
	}
}

void UNexusAbility_LocomotionRun::HandleAbilityStart()
{
	
}

void UNexusAbility_LocomotionRun::HandleAbilityStop()
{
	
}

bool UNexusAbility_LocomotionRun::ShouldBoostThisFrame() const
{
	const ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!Char) return false;

	const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
	if (!MoveComp || !MoveComp->IsMovingOnGround()) return false;

	const FVector InputVector = MoveComp->GetLastInputVector();
	if (InputVector.IsNearlyZero()) return false;

	const FVector Forward = Char->GetActorForwardVector();
	return FVector::DotProduct(Forward, InputVector.GetSafeNormal()) > BoostThreshold;
}

void UNexusAbility_LocomotionRun::SetBoostActive(bool bNewActive)
{
	if (bIsBoostActive == bNewActive) return;
	
	ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner());
	if (!Char) return;

	bIsBoostActive = bNewActive;
	if (bNewActive)
	{
		Char->StartRunning();
	}
	else
	{
		Char->StopRunning();
	}
}