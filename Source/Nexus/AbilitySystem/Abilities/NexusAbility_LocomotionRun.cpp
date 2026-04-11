// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionRun.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionRun::UNexusAbility_LocomotionRun()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Run);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Run);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Crouch);
	InputTag = NexusGameplayTags::InputTag_Run;
	bCanTick = true;
}

void UNexusAbility_LocomotionRun::OnActivateAbility()
{
	bIsBoostActive = false;
	Super::OnActivateAbility();
}

void UNexusAbility_LocomotionRun::OnDeactivateAbility()
{
	SetBoostActive(false);
	Super::OnDeactivateAbility();
}

void UNexusAbility_LocomotionRun::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);

	const bool bShould = ShouldBoostThisFrame();
	if (bShould != bIsBoostActive)
	{
		SetBoostActive(bShould);
	}
}

bool UNexusAbility_LocomotionRun::ShouldBoostThisFrame() const
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

void UNexusAbility_LocomotionRun::SetBoostActive(bool bNewActive)
{
	if (bIsBoostActive == bNewActive) return;

	const ACharacter* Char = Cast<ACharacter>(GetAvatarActor());
	if (!Char) return;

	UNexusCharacterMovementComponent* MoveComp =
		Cast<UNexusCharacterMovementComponent>(Char->GetCharacterMovement());
	if (!MoveComp) return;

	bIsBoostActive = bNewActive;
	if (bNewActive)
	{
		MoveComp->StartRunning();
	}
	else
	{
		MoveComp->StopRunning();
	}
}