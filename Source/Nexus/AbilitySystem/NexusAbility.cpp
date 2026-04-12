// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility.h"
#include "NexusAbilitySystemComponent.h"

UNexusAbility::UNexusAbility()
{
	bIsEnabled = true;
}

void UNexusAbility::CommitAbility()
{
	if (!IsActive())
	{
		ActivationState = ENexusAbilityActivationState::Active;
		OnActivated.Broadcast(this);
		if (bCooldownOnActivation) StartCooldown();
	}
}

void UNexusAbility::CommitAbilityEnd()
{
	if (IsActive())
	{
		ActivationState = ENexusAbilityActivationState::Idle;
		OnDeactivated.Broadcast(this);
		if (bCooldownOnDeactivation) StartCooldown();
	}
}

bool UNexusAbility::RequestActivateAbility()
{
	if (IsOnCooldown()) return false;
	if (!CanActivateAbility_Implementation()) return false;
	
	K2_OnAbilityActivate();
	return true;
}

bool UNexusAbility::RequestDeactivateAbility(bool bForce)
{
	if (!bForce)
	{
		if (!IsActive()) return false;
	}
	
	K2_OnAbilityDeactivate();
	return true;
}

void UNexusAbility::OnEnableAbility()
{
	bIsEnabled = true;
	OnAbilityEnabled.Broadcast();
	
	K2_OnAbilityEnabled();
}

void UNexusAbility::OnDisableAbility()
{
	RequestDeactivateAbility(true);
	bIsEnabled = false;
	OnAbilityDisabled.Broadcast();
	
	K2_OnAbilityDisabled();
}


bool UNexusAbility::CanActivateAbility_Implementation() const
{
	return IsEnabled();
}


// Ability utility
UNexusAbilitySystemComponent* UNexusAbility::GetNexusAbilitySystemComponent() const
{
	return Cast<UNexusAbilitySystemComponent>(GetOuter());
}

AActor* UNexusAbility::GetOwner() const
{
	if (const UNexusAbilitySystemComponent* Comp = GetNexusAbilitySystemComponent())
	{
		return Comp->GetOwner();
	}
	return nullptr;
}

AController* UNexusAbility::GetController() const
{
	if (const UNexusAbilitySystemComponent* Comp = GetNexusAbilitySystemComponent())
	{
		return Comp->GetController(); 
	}
	return nullptr;
}


// Cooldown
bool UNexusAbility::HasCooldown() const
{
	return CooldownDuration > 0.0f;
}

float UNexusAbility::GetCooldownTotalDuration() const
{
	return FMath::Max(0.0f, CooldownDuration);
}

float UNexusAbility::GetCooldownTimeRemaining() const
{
	if (!bIsOnCooldown) return 0.0f;
	return FMath::Max(0.0f, GetCooldownTotalDuration() - CooldownElapsed);
}

float UNexusAbility::GetCooldownProgress() const
{
	if (!bIsOnCooldown) return 0.0f;
	const float Total = GetCooldownTotalDuration();
	if (Total <= 0.0f) return 0.0f;
	return FMath::Clamp(CooldownElapsed / Total, 0.0f, 1.0f);
}

void UNexusAbility::StartCooldown()
{
	const float Duration = GetCooldownTotalDuration();
	if (Duration > 0.0f)
	{
		bIsOnCooldown = true;
		CooldownElapsed = 0.0f;
	}
}

void UNexusAbility::TickCooldown(float DeltaTime)
{
	if (!bIsOnCooldown) return;

	CooldownElapsed += DeltaTime;
	if (CooldownElapsed >= GetCooldownTotalDuration())
	{
		bIsOnCooldown = false;
		CooldownElapsed = 0.0f;
	}
}