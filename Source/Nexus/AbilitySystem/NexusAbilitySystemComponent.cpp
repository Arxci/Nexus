// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbilitySystemComponent.h"
#include "NexusAbility.h" 
#include "GameFramework/Character.h" 


UNexusAbilitySystemComponent::UNexusAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusAbilitySystemComponent::InitAbilityActorInfo(ACharacter* InCharacter)
{
	if (InCharacter)
	{
		CachedCharacter = InCharacter;
		CachedController = InCharacter->GetController();
	}
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

	UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToActivate);
	if (!FoundAbility) return false;
	
	if (!FoundAbility->IsEnabled()) return false;
	
	if (FoundAbility->IsActive()) return false;
	
	if (!CheckTagRequirements(FoundAbility)) return false;
	
	if (!FoundAbility->CanActivateAbility()) return false;
	
	if (!FoundAbility->CancelAbilitiesWithTags.IsEmpty())
	{
		CancelAbilitiesWithTags(FoundAbility->CancelAbilitiesWithTags);
	}
	
	if (!FoundAbility->ActivationOwnedTags.IsEmpty())
	{
		AddTags(FoundAbility->ActivationOwnedTags);
	}

	FoundAbility->ActivationState = ENexusAbilityActivationState::Active;
	
	FoundAbility->ActivateAbility();
	OnAbilityActivated.Broadcast(FoundAbility);

	return true;
}

bool UNexusAbilitySystemComponent::TryDeactivateAbilityByClass(const TSubclassOf<UNexusAbility> InAbilityToDeactivate)
{
	if (!InAbilityToDeactivate) return false;

	UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToDeactivate);
	if (!FoundAbility) return false;

	if (!FoundAbility->IsActive()) return false;

	FoundAbility->ActivationState = ENexusAbilityActivationState::Idle;

	DeactivateAbility(FoundAbility);
	
	return true;
}

void UNexusAbilitySystemComponent::DeactivateAbility(UNexusAbility* Ability)
{
	if (!Ability || !Ability->IsActive()) return;
	
	if (!Ability->ActivationOwnedTags.IsEmpty())
	{
		RemoveTags(Ability->ActivationOwnedTags);
	}
	
	Ability->DeactivateAbility();
	OnAbilityDeactivated.Broadcast(Ability);
}

void UNexusAbilitySystemComponent::SetAbilityEnabled(TSubclassOf<UNexusAbility> AbilityClass, bool bEnabled)
{
	if (UNexusAbility* FoundAbility = GrantedAbilities.FindRef(AbilityClass))
	{
		if (FoundAbility->IsEnabled() == bEnabled) return;

		FoundAbility->bIsEnabled = bEnabled;
		
		if (!bEnabled && FoundAbility->IsActive())
		{
			DeactivateAbility(FoundAbility);
		}
	}
}

void UNexusAbilitySystemComponent::AddTags(const FGameplayTagContainer& Tags)
{
	for (const FGameplayTag& Tag : Tags)
	{
		int32& Count = TagRefCounts.FindOrAdd(Tag, 0);
		Count++;
		if (Count == 1)
		{
			OwnedTags.AddTag(Tag);
			OnTagChanged.Broadcast(Tag, true);
		}
	}
}


void UNexusAbilitySystemComponent::RemoveTags(const FGameplayTagContainer& Tags)
{
	for (const FGameplayTag& Tag : Tags)
	{
		if (int32* Count = TagRefCounts.Find(Tag))
		{
			(*Count)--;
			if (*Count <= 0)
			{
				OwnedTags.RemoveTag(Tag);
				TagRefCounts.Remove(Tag);
				OnTagChanged.Broadcast(Tag, false);
			}
		}
	}
}


bool UNexusAbilitySystemComponent::HasTag(FGameplayTag Tag) const
{
	return OwnedTags.HasTag(Tag);
}

bool UNexusAbilitySystemComponent::HasAllTags(const FGameplayTagContainer& TagContainer) const
{
	return OwnedTags.HasAll(TagContainer);
}

bool UNexusAbilitySystemComponent::HasAnyTags(const FGameplayTagContainer& TagContainer) const
{
	return OwnedTags.HasAny(TagContainer);
}

FGameplayTagContainer UNexusAbilitySystemComponent::GetOwnedTags() const
{
	return OwnedTags;
}

void UNexusAbilitySystemComponent::AddLooseGameplayTag(FGameplayTag Tag)
{
	int32& Count = TagRefCounts.FindOrAdd(Tag, 0);
	Count++;
	if (Count == 1)
	{
		OwnedTags.AddTag(Tag);
		OnTagChanged.Broadcast(Tag, true);
	}
}


void UNexusAbilitySystemComponent::RemoveLooseGameplayTag(FGameplayTag Tag)
{
	if (int32* Count = TagRefCounts.Find(Tag))
	{
		(*Count)--;
		if (*Count <= 0)
		{
			OwnedTags.RemoveTag(Tag);
			TagRefCounts.Remove(Tag);
			OnTagChanged.Broadcast(Tag, false);
		}
	}
}


bool UNexusAbilitySystemComponent::CheckTagRequirements(const UNexusAbility* Ability) const
{
	if (!Ability->ActivationRequiredTags.IsEmpty())
	{
		if (!OwnedTags.HasAll(Ability->ActivationRequiredTags))
		{
			return false;
		}
	}
	
	if (!Ability->ActivationBlockedTags.IsEmpty())
	{
		if (OwnedTags.HasAny(Ability->ActivationBlockedTags))
		{
			return false;
		}
	}

	return true;
}

void UNexusAbilitySystemComponent::CancelAbilitiesWithTags(const FGameplayTagContainer& Tags)
{
	TArray<UNexusAbility*> AbilitiesToCancel;

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->IsActive())
		{
			if (Ability->AbilityTags.HasAny(Tags))
			{
				AbilitiesToCancel.Add(Ability);
			}
		}
	}

	for (UNexusAbility* Ability : AbilitiesToCancel)
	{
		DeactivateAbility(Ability);
	}
}

