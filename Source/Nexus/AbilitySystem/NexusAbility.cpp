// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility.h"
#include "NexusAbilitySystemComponent.h"

UNexusAbility::UNexusAbility()
{
	bIsEnabled = true;
	bCanTick = true;
}

void  UNexusAbility::TickAbility(float DeltaTime)
{
	HandleAbilityProgress();
}

bool UNexusAbility::OnRequestActivateAbility()
{
	if (!CanActivateAbility_Implementation() || IsActive() || !IsEnabled()) return false;

	UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent();
	if (!ASC || !ASC->CheckTagRequirements(this)) return false;
	
	ActivationState = ENexusAbilityActivationState::Active;
	OnActivated.Broadcast(this);

	K2_OnAbilityActivated();
	return true;
}

bool UNexusAbility::OnRequestDeactivateAbility(bool bForce)
{
	if (!bForce)
	{
		if (!IsActive()) return false;
	}
	
	ActivationState = ENexusAbilityActivationState::Idle;
	OnDeactivated.Broadcast(this);
	
	K2_OnAbilityDeactivated();
	return true;
}

void UNexusAbility::OnEnableAbility()
{
	bIsEnabled = true;
	bCanTick = true;
	OnAbilityEnabled.Broadcast();
	
	K2_OnAbilityEnabled();
}

void UNexusAbility::OnDisableAbility()
{
	OnRequestDeactivateAbility(true);
	bIsEnabled = false;
	bCanTick = false;
	OnAbilityDisabled.Broadcast();
	
	K2_OnAbilityDisabled();
}


bool UNexusAbility::CanActivateAbility_Implementation() const
{
	return true;
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