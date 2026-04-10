// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbilitySystemComponent.h"
#include "NexusAbility.h" 
#include "GameFramework/Character.h" 
#include "Nexus/Nexus.h"


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

void UNexusAbilitySystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DeactivateAllAbilities();
	Super::EndPlay(EndPlayReason);
}

// --- Ability Lifecycle ---

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
	if (!FoundAbility)
	{
		UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: not granted"),
			*InAbilityToActivate->GetName());
		return false;
	}
	
	if (!FoundAbility->IsEnabled())
	{
		UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: disabled"),
			*InAbilityToActivate->GetName());
		return false;
	}
	
	if (FoundAbility->IsActive())
	{
		UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: already active"),
			*InAbilityToActivate->GetName());
		return false;
	}

	if (FoundAbility->IsOnCooldown())
	{
		UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: on cooldown (%.2fs remaining)"),
			*InAbilityToActivate->GetName(), FoundAbility->GetCooldownRemaining());
		return false;
	}
	
	if (!CheckTagRequirements(FoundAbility))
	{
		UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: tag requirements not met"),
			*InAbilityToActivate->GetName());
		return false;
	}
	
	if (!FoundAbility->CanActivateAbility())
	{
		UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: CanActivateAbility returned false"),
			*InAbilityToActivate->GetName());
		return false;
	}
	
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

	if (!FoundAbility->bStartCooldownOnEnd)
	{
		FoundAbility->CommitCooldown();
	}

	UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] SUCCESS"), *InAbilityToActivate->GetName());

	return true;
}

bool UNexusAbilitySystemComponent::TryDeactivateAbilityByClass(const TSubclassOf<UNexusAbility> InAbilityToDeactivate)
{
	if (!InAbilityToDeactivate) return false;

	UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToDeactivate);
	if (!FoundAbility) return false;

	if (!FoundAbility->IsActive()) return false;

	DeactivateAbility(FoundAbility);
	
	return true;
}

void UNexusAbilitySystemComponent::DeactivateAbility(UNexusAbility* Ability)
{
	if (!Ability || !Ability->IsActive()) return;

	Ability->ActivationState = ENexusAbilityActivationState::Idle;
	
	if (!Ability->ActivationOwnedTags.IsEmpty())
	{
		RemoveTags(Ability->ActivationOwnedTags);
	}
	
	Ability->DeactivateAbility();
	OnAbilityDeactivated.Broadcast(Ability);

	if (Ability->bStartCooldownOnEnd)
	{
		Ability->CommitCooldown();
	}
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

void UNexusAbilitySystemComponent::DeactivateAllAbilities()
{
	for (const auto& Pair : GrantedAbilities)
	{
		if (Pair.Value && Pair.Value->IsActive())
		{
			DeactivateAbility(Pair.Value);
		}
	}
}

bool UNexusAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTag)
{
	if (!AbilityTag.IsValid()) return false;

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->AbilityTags.HasTag(AbilityTag))
		{
			if (TryActivateAbilityByClass(Pair.Key))
			{
				return true;
			}
		}
	}
	return false;
}

bool UNexusAbilitySystemComponent::TryDeactivateAbilityByTag(FGameplayTag AbilityTag)
{
	if (!AbilityTag.IsValid()) return false;

	bool bDeactivatedAny = false;
	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->IsActive() && Ability->AbilityTags.HasTag(AbilityTag))
		{
			DeactivateAbility(Ability);
			bDeactivatedAny = true;
		}
	}
	return bDeactivatedAny;
}

// --- Ability Queries ---

UNexusAbility* UNexusAbilitySystemComponent::FindAbilityByClass(TSubclassOf<UNexusAbility> AbilityClass) const
{
	return GrantedAbilities.FindRef(AbilityClass);
}

bool UNexusAbilitySystemComponent::IsAbilityActive(TSubclassOf<UNexusAbility> AbilityClass) const
{
	if (const UNexusAbility* Ability = GrantedAbilities.FindRef(AbilityClass))
	{
		return Ability->IsActive();
	}
	return false;
}

TArray<UNexusAbility*> UNexusAbilitySystemComponent::GetActiveAbilities() const
{
	TArray<UNexusAbility*> Result;
	for (const auto& Pair : GrantedAbilities)
	{
		if (Pair.Value && Pair.Value->IsActive())
		{
			Result.Add(Pair.Value);
		}
	}
	return Result;
}

// --- Tags ---

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
	if (!Tag.IsValid()) return;

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
	if (!Tag.IsValid()) return;

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

