#include "NexusAbility_LocomotionCrouch.h"

#include "GameFramework/Character.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"


UNexusAbility_LocomotionCrouch::UNexusAbility_LocomotionCrouch()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Locomotion_Run);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Crouch);
	bCooldownOnActivation = true;
	bCooldownOnDeactivation = true;
}

void UNexusAbility_LocomotionCrouch::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);
	
	if (IsOnCooldown()) return;
	
	if (CanCharacterCrouch())
	{
		if (!IsActive())
		{
			CommitAbility();
		}
	}
	else if (CanCharacterUnCrouch())
	{
		if (IsActive())
		{
			CommitAbilityEnd();
		}
	}
}

bool UNexusAbility_LocomotionCrouch::RequestActivateAbility()
{
	if (!Super::RequestActivateAbility()) return false;
	
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->AddLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch);
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
	}
	
	return true;
}

bool UNexusAbility_LocomotionCrouch::RequestDeactivateAbility(bool bForce)
{
	if (!Super::RequestDeactivateAbility(bForce)) return false;
	
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		if (!ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch))
		{
			ASC->AddLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
		}
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch);
	}
	
	return true;
}

bool UNexusAbility_LocomotionCrouch::CanCharacterCrouch() const
{
	if (const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		if (!Char->GetNexusCharacterMovement()->IsGrounded()) return false;
	}
	
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		const bool bCrouchingOrIntending =
			ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Crouch) ||
			ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch);

		const bool bCancelTagSnapshot = ASC->HasAnyTags(CancelAbilitiesWithTags);
		const bool bWantingUncrouch = ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);

		if (!bCrouchingOrIntending || bCancelTagSnapshot || bWantingUncrouch) return false;
	}
	
	return true;
}

bool UNexusAbility_LocomotionCrouch::CanCharacterUnCrouch() const
{
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		if (!ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch)) return false;
	}

	if (const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		if (!Char->GetNexusCharacterMovement()->CanStand()) return false;
	}

	if (IsActive()) return true;

	return false;
}

bool UNexusAbility_LocomotionCrouch::CanTick()
{
	bool bCanTick = false;
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		bCanTick = ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch) || ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch) || IsActive();
	}
	return bCanTick;
}

void UNexusAbility_LocomotionCrouch::CommitAbility()
{
	Super::CommitAbility();
	
	if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		Char->Crouch();
	}
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch);
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
	}
}

void UNexusAbility_LocomotionCrouch::CommitAbilityEnd()
{
	Super::CommitAbilityEnd();

	if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		Char->UnCrouch();
	}
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch);
	}
}

void UNexusAbility_LocomotionCrouch::ForceEndAbility()
{
	if (IsActive())
	{
		ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner());
		UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent();
		const bool bCanStand = Char && Char->GetNexusCharacterMovement()
			&& Char->GetNexusCharacterMovement()->CanStand();

		if (!bCanStand)
		{
			if (ASC)
			{
				ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch);
				if (!ASC->HasTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch))
				{
					ASC->AddLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
				}
			}
			return;
		}

	CommitAbilityEnd();
	}
}


// Save/Restore
void UNexusAbility_LocomotionCrouch::OnSaveStateRestored()
{
	if (IsActive())
	{
		if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
		{
			Char->Crouch();
		}
	}
}

