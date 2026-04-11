// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbilitySystemComponent.h"
#include "NexusAbility.h" 
#include "Nexus/Nexus.h"


UNexusAbilitySystemComponent::UNexusAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNexusAbilitySystemComponent::InitAbilityActorInfo(AController* InController)
{
	CachedController = InController; 
}

void UNexusAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	TArray<UNexusAbility*, TInlineAllocator<8>> TickList;
	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->GetCanTick() && Ability->IsActive() && Ability->IsEnabled())
		{
			TickList.Add(Ability);
		}
	}
	for (UNexusAbility* Ability : TickList)
	{
		if (Ability->IsActive())
		{
			Ability->TickAbility(DeltaTime);
		}
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
	if (!AbilityClass) return nullptr;
	
	if (UNexusAbility* Existing = GrantedAbilities.FindRef(AbilityClass))
	{
		if (!Existing->IsEnabled())
		{
			SetAbilityEnabled(AbilityClass, true);
			OnAbilityGiven.Broadcast(Existing);
		}
		return Existing;
	}

	if (UNexusAbility* NewAbility = NewObject<UNexusAbility>(this, AbilityClass))
	{
		GrantedAbilities.Add(AbilityClass, NewAbility);
		OnAbilityGiven.Broadcast(NewAbility);
		return NewAbility;
	}
	return nullptr;
}

bool UNexusAbilitySystemComponent::RemoveAbility(const TSubclassOf<UNexusAbility> AbilityClass)
{
	if (!AbilityClass) return false;

	UNexusAbility* FoundAbility = GrantedAbilities.FindRef(AbilityClass);
	if (!FoundAbility)
	{
		UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("RemoveAbility [%s] FAILED: not granted"),
			*AbilityClass->GetName());
		return false;
	}
	if (!FoundAbility->IsEnabled())
	{
		return true; 
	}

	SetAbilityEnabled(AbilityClass, false); 
	OnAbilityRemoved.Broadcast(FoundAbility);

	UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("RemoveAbility [%s] SUCCESS"),
		*AbilityClass->GetName());
	return true;
}

ENexusAbilityActivationResult UNexusAbilitySystemComponent::TryActivateAbilityByClassWithResult(const TSubclassOf<UNexusAbility> InAbilityToActivate)
{
    if (!InAbilityToActivate)
    {
        return ENexusAbilityActivationResult::InvalidClass;
    }

    UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToActivate);
    if (!FoundAbility)
    {
        UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: not granted"),
            *InAbilityToActivate->GetName());
        return ENexusAbilityActivationResult::NotGranted;
    }

    if (!FoundAbility->IsEnabled())
    {
        UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: disabled"),
            *InAbilityToActivate->GetName());
        return ENexusAbilityActivationResult::Disabled;
    }

    if (FoundAbility->IsActive())
    {
        UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: already active"),
            *InAbilityToActivate->GetName());
        return ENexusAbilityActivationResult::AlreadyActive;
    }

    if (FoundAbility->IsOnCooldown())
    {
        UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: on cooldown (%.2fs remaining)"),
            *InAbilityToActivate->GetName(), FoundAbility->GetCooldownRemaining());
        return ENexusAbilityActivationResult::OnCooldown;
    }

    if (!CheckTagRequirements(FoundAbility))
    {
        UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: tag requirements not met"),
            *InAbilityToActivate->GetName());
        return ENexusAbilityActivationResult::TagsBlocked;
    }

    if (!FoundAbility->CanActivateAbility())
    {
        UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: CanActivateAbility returned false"),
            *InAbilityToActivate->GetName());
        return ENexusAbilityActivationResult::ConditionFailed;
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

    FoundAbility->OnActivateAbility();
    OnAbilityActivated.Broadcast(FoundAbility);

    if (!FoundAbility->bStartCooldownOnEnd)
    {
        FoundAbility->CommitCooldown();
    }

    UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] SUCCESS"), *InAbilityToActivate->GetName());

    return ENexusAbilityActivationResult::Success;
}

bool UNexusAbilitySystemComponent::TryActivateAbilityByClass(const TSubclassOf<UNexusAbility> InAbilityToActivate)
{
    return TryActivateAbilityByClassWithResult(InAbilityToActivate) == ENexusAbilityActivationResult::Success;
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
	
	Ability->OnDeactivateAbility();
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
	TArray<UNexusAbility*, TInlineAllocator<8>> ToDeactivate;
	for (const auto& Pair : GrantedAbilities)
	{
		if (Pair.Value && Pair.Value->IsActive())
		{
			ToDeactivate.Add(Pair.Value);
		}
	}
	for (UNexusAbility* Ability : ToDeactivate)
	{
		if (Ability->IsActive())
		{
			DeactivateAbility(Ability);
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

bool UNexusAbilitySystemComponent::IsAbilityActiveByTag(FGameplayTag AbilityTag) const
{
	if (!AbilityTag.IsValid()) return false;
	for (const auto& Pair : GrantedAbilities)
	{
		const UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->IsActive() && Ability->AbilityTags.HasTag(AbilityTag))
		{
			return true;
		}
	}
	return false;
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

// Input Routing

void UNexusAbilitySystemComponent::AbilityInputPressed(FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->InputTag == InputTag)
		{
			TryActivateAbilityByClass(Pair.Key);
		}
	}
}

void UNexusAbilitySystemComponent::AbilityInputReleased(FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->IsActive() && Ability->InputTag == InputTag)
		{
			DeactivateAbility(Ability);
		}
	}
}