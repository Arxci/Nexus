// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility.h"
#include "NexusAbilitySystemComponent.h"
#include "GameFramework/Character.h"

UNexusAbility::UNexusAbility()
{
	CurrentState = ENexusAbilityState::Inactive;
}

void UNexusAbility::ActivateAbility_Implementation()
{
	if (CurrentState == ENexusAbilityState::Active) return; 
    
	CurrentState = ENexusAbilityState::Active;
}

void UNexusAbility::DeactivateAbility_Implementation()
{
	if (CurrentState == ENexusAbilityState::Inactive) return;
	
	CurrentState = ENexusAbilityState::Inactive;
}

void UNexusAbility::Tick(float DeltaTime)
{

}

bool UNexusAbility::IsTickable() const
{
	return CurrentState == ENexusAbilityState::Active && !HasAnyFlags(RF_ClassDefaultObject);
}

TStatId UNexusAbility::GetStatId() const
{
	// Required for Unreal's profiler. 
	RETURN_QUICK_DECLARE_CYCLE_STAT(UNexusAbility, STATGROUP_Tickables);
}

UNexusAbilitySystemComponent* UNexusAbility::GetNexusComponent() const
{
	// The component created us, so it is our Outer object
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