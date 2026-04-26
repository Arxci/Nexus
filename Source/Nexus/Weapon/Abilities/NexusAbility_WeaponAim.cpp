// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_WeaponAim.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Player/NexusPlayerCameraManager.h"

UNexusAbility_WeaponAim::UNexusAbility_WeaponAim()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Weapon_Aim);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Aiming);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Reloading);
	bCooldownOnActivation   = false;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponAim::CanActivateAbility_Implementation() const
{
	return Super::CanActivateAbility_Implementation();
}

void UNexusAbility_WeaponAim::CommitAbility()
{
	Super::CommitAbility();
	ApplyAimEffects();
}

void UNexusAbility_WeaponAim::CommitAbilityEnd()
{
	RemoveAimEffects();
	Super::CommitAbilityEnd();
}

void UNexusAbility_WeaponAim::ForceEndAbility()
{
	Super::ForceEndAbility();
	RemoveAimEffects();
}

void UNexusAbility_WeaponAim::ApplyAimEffects()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ANexusPlayerCameraManager* CM = Cast<ANexusPlayerCameraManager>(PC->PlayerCameraManager))
		{
			CM->BlendToFOV(AimFOV, BlendInDuration);
		}
	}

	// Multiplicatively scale walk speed instead of caching the absolute value.
	// Composes correctly with crouch/run that may also be modifying speed.
	if (!bSpeedScaleApplied && AimWalkSpeedScale > 0.0f)
	{
		if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
		{
			if (UCharacterMovementComponent* CMC = Char->GetCharacterMovement())
			{
				CMC->MaxWalkSpeed *= AimWalkSpeedScale;
				bSpeedScaleApplied = true;
			}
		}
	}
}

void UNexusAbility_WeaponAim::RemoveAimEffects()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ANexusPlayerCameraManager* CM = Cast<ANexusPlayerCameraManager>(PC->PlayerCameraManager))
		{
			CM->EndAimFOVBlend(BlendOutDuration);
		}
	}

	if (bSpeedScaleApplied && AimWalkSpeedScale > 0.0f)
	{
		if (ACharacter* Char = Cast<ACharacter>(GetOwner()))
		{
			if (UCharacterMovementComponent* CMC = Char->GetCharacterMovement())
			{
				CMC->MaxWalkSpeed /= AimWalkSpeedScale;
			}
		}
		bSpeedScaleApplied = false;
	}
}

void UNexusAbility_WeaponAim::OnSaveStateRestored()
{
	if (IsActive())
	{
		ApplyAimEffects();
	}
}