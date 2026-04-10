// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbilitySystemComponent.h"
#include "NexusAbility.h" 
#include "GameFramework/Character.h" 
#include "GameFramework/Controller.h"


UNexusAbilitySystemComponent::UNexusAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UNexusAbility* UNexusAbilitySystemComponent::GiveAbility(const TSubclassOf<UNexusAbility> AbilityClass)
{
	if (!AbilityClass || GrantedAbilities.Contains(AbilityClass)) return nullptr;	
	
	if (UNexusAbility* NewAbility = NewObject<UNexusAbility>(this, AbilityClass))
	{
		GrantedAbilities.Add(AbilityClass, NewAbility);
		return NewAbility;
	}

	return nullptr;
}

bool UNexusAbilitySystemComponent::TryActivateAbilityByClass(const TSubclassOf<UNexusAbility> InAbilityToActivate)
{
	if (!InAbilityToActivate) return false;
	
	if (UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToActivate))
	{
		FoundAbility->ActivateAbility();
		return true;
	}

	return false;
}

bool UNexusAbilitySystemComponent::TryDeactivateAbilityByClass(const TSubclassOf<UNexusAbility> InAbilityToDeactivate)
{
	if (!InAbilityToDeactivate) return false;

	if (UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToDeactivate))
	{
		FoundAbility->DeactivateAbility();
		return true;
	}
	
	return false;
}

void UNexusAbilitySystemComponent::InitAbilityActorInfo(ACharacter* InCharacter)
{
	if (InCharacter)
	{
		CachedCharacter = InCharacter;
		CachedController = InCharacter->GetController();
	}
}
