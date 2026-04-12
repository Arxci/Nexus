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
	}
}

void UNexusAbility::CommitAbilityEnd()
{
	if (IsActive())
	{
		ActivationState = ENexusAbilityActivationState::Idle;
		OnDeactivated.Broadcast(this);
	}
}

bool UNexusAbility::RequestActivateAbility()
{
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
	UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent();
	
	if (ASC && !ASC->CheckTagRequirements(this)) return false;
	
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