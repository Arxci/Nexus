// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility.h"
#include "NexusAbilitySystemComponent.h"
#include "GameFramework/Character.h"

UNexusAbility::UNexusAbility()
{
	ActivationState = ENexusAbilityActivationState::Idle;
	bIsEnabled = true;
}

void UNexusAbility::ActivateAbility_Implementation()
{

}

void UNexusAbility::DeactivateAbility_Implementation()
{
	
}

bool UNexusAbility::CanActivateAbility_Implementation() const
{

	return true;
}

void UNexusAbility::Tick(float DeltaTime)
{

}

bool UNexusAbility::IsTickable() const
{
	return bIsEnabled
		&& ActivationState == ENexusAbilityActivationState::Active
		&& !HasAnyFlags(RF_ClassDefaultObject);
}

TStatId UNexusAbility::GetStatId() const
{
	// Required for Unreal's profiler. 
	RETURN_QUICK_DECLARE_CYCLE_STAT(UNexusAbility, STATGROUP_Tickables);
}

UNexusAbilitySystemComponent* UNexusAbility::GetNexusComponent() const
{
	return Cast<UNexusAbilitySystemComponent>(GetOuter());
}

ACharacter* UNexusAbility::GetCharacter() const
{
	if (UNexusAbilitySystemComponent* Comp = GetNexusComponent())
	{
		return Comp->GetCharacter(); 
	}
	return nullptr;
}

AController* UNexusAbility::GetController() const
{
	if (UNexusAbilitySystemComponent* Comp = GetNexusComponent())
	{
		return Comp->GetController(); 
	}
	return nullptr;
}

UWorld* UNexusAbility::GetWorld() const
{
	if (const ACharacter* Char = GetCharacter())
	{
		return Char->GetWorld();
	}
	return nullptr;
}