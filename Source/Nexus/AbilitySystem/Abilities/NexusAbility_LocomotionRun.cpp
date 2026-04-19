// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionRun.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionRun::UNexusAbility_LocomotionRun()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Run);
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Run);
	bCooldownOnDeactivation = false;
}

void UNexusAbility_LocomotionRun::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);

	if (IsOnCooldown()) return;
	
	if (CanCharacterRun())
	{
		if (!IsActive())
		{
			CommitAbility();
		}
	}
	else if (CanCharacterWalk())
	{
		if (IsActive())
		{
			if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
			{
				ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk);
			}
			CommitAbilityEnd();
		}
	}
	else if (IsActive())
	{
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
	//Always clear run intent due to possibility of partially active due to IsMovingForward logic checks.
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
		if (!Char->GetNexusCharacterMovement()->IsMovingForward(BoostThreshold)) return false;
	}
	
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

bool UNexusAbility_LocomotionRun::CanTick()
{
	bool bCanTick = false;
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		bCanTick = ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Run) || ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk) || IsActive();
	}
	return bCanTick;
}

void UNexusAbility_LocomotionRun::CommitAbility()
{
	Super::CommitAbility();
	
	if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		Char->Run();
	}
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Run);
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk);
	}
}

void UNexusAbility_LocomotionRun::CommitAbilityEnd()
{
	Super::CommitAbilityEnd();
	
	if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		Char->StopRun();
	}
}

void UNexusAbility_LocomotionRun::ForceEndAbility()
{
	Super::ForceEndAbility();
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Run);
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Walk);
	}

	if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		Char->StopRun();
	}
}

void UNexusAbility_LocomotionRun::OnSaveStateRestored()
{
	if (IsActive())
	{
		if (const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
		{
			Char->Run();
		}
	}
}