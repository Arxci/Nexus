// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionCrouch.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"

UNexusAbility_LocomotionCrouch::UNexusAbility_LocomotionCrouch()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Locomotion_Run);

	if (const ACharacter* Char = Cast<ACharacter>(GetOwner()))
	{
		StandingHalfHeight = Char->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	}
}

void UNexusAbility_LocomotionCrouch::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);
	
	if (CanCharacterCrouch())
	{
		if (!IsActive())
		{
			if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
			{
				Char->Crouch();
			}
			if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
			{
				ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_Crouch);
			}
			CommitAbility();
		}
	}
	else if (CanCharacterUnCrouch())
	{
		if (IsActive())
		{
			if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
			{
				Char->UnCrouch();
			}
			if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
			{
				ASC->RemoveLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
			}
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
		ASC->AddLooseGameplayTag(NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
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

	if (IsActive() && CanCharacterStand()) return true;

	return false;
}

bool UNexusAbility_LocomotionCrouch::CanCharacterStand() const
{
	if (ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		const UCapsuleComponent* Capsule = Char->GetCapsuleComponent();
		const float Radius = Capsule->GetScaledCapsuleRadius();
		const FVector Location = Char->GetActorLocation();

		const float CurrentHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
		const FVector TraceLocation = Location + FVector(0.f, 0.f, StandingHalfHeight - CurrentHalfHeight);

		TArray<FHitResult> Hits;
		UKismetSystemLibrary::CapsuleTraceMulti(
			Char->GetWorld(),
			TraceLocation,
			TraceLocation,
			Radius,
			StandingHalfHeight,
			UEngineTypes::ConvertToTraceType(ECC_Pawn),
			false,
			{Char},
			EDrawDebugTrace::None,
			Hits,
			true,
			FLinearColor::Green,  
			FLinearColor::Red,    
			0.f  
		);

		return Hits.IsEmpty();
	}
	return true;
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