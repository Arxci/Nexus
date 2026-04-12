// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionRun.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionRun::UNexusAbility_LocomotionRun()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Run);
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
}

void UNexusAbility_LocomotionRun::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);
	
	if (CanCharacterRun())
	{
		if (!IsActive())
		{
			if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
			{
				Char->StartRunning();
			}
			if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
			{
				ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Run);
			}
			CommitAbility();
		}
	}
	else if (CanCharacterWalk())
	{
		if (IsActive())
		{
			if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
			{
				Char->StopRunning();
			}
			if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
			{
				ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk);
			}
			CommitAbilityEnd();
		}
	}
	else if (IsActive())
	{
		if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
		{
			Char->StopRunning();
		}
		if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
		{
			ASC->AddLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Run);
		}
		CommitAbilityEnd();
	}
}

bool UNexusAbility_LocomotionRun::RequestActivateAbility()
{
	if (!Super::RequestActivateAbility()) return false;
	
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->AddLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Run);
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk);
	}
	
	return true;
}

bool UNexusAbility_LocomotionRun::RequestDeactivateAbility(bool bForce)
{
	//Always clear run intent due to possibility of partially active  due to IsMovingForward logic checks.
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Run);
	}
	
	if (!Super::RequestDeactivateAbility(bForce)) return false;

	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		if (!ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk))
		{
			ASC->AddLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk);
		}
	}
	
	return true;
}

bool UNexusAbility_LocomotionRun::CanCharacterRun() const
{
	if (const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		if (!Char->GetNexusCharacterMovement()->IsGrounded()) return false;
	}

	if (!IsMovingForward()) return false;
	
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		const bool bRunningOrIntending =
			ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Run) ||
			ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Run);

		const bool bCancelTagSnapshot = ASC->HasAnyTags(CancelAbilitiesWithTags);
		const bool bWantingWalk = ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk);

		if (!bRunningOrIntending || bCancelTagSnapshot || bWantingWalk) return false;
	}

	return true;
}

bool UNexusAbility_LocomotionRun::CanCharacterWalk() const
{
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		if (!ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk)) return false;
	}

	if (IsActive()) return true;

	return false;
}

bool UNexusAbility_LocomotionRun::IsMovingForward() const
{
	const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner());
	if (!Char) return false;
	
	const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
	if (!MoveComp || !MoveComp->IsMovingOnGround()) return false;
	
	const FVector InputVector = MoveComp->GetLastInputVector();
	if (InputVector.IsNearlyZero()) return false;

	const FVector Forward = Char->GetActorForwardVector();
	return FVector::DotProduct(Forward, InputVector.GetSafeNormal()) > BoostThreshold;
}

bool UNexusAbility_LocomotionRun::CanTick()
{
	bool bCanTick = false;
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		bCanTick = ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Run) || ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk) || IsActive();
	}
	return bCanTick;
}