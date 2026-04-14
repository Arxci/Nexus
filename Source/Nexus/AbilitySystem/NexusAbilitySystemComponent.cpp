// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbilitySystemComponent.h"
#include "NexusAbilitySaveData.h"
#include "NexusAbility.h" 


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
		if (Ability && Ability->IsEnabled())
		{
			TickList.Add(Ability);
		}
	}
	for (UNexusAbility* Ability : TickList)
	{
		if (Ability->HasCooldown())
		{
			Ability->TickCooldown(DeltaTime);
		}
		if (Ability->CanTick())
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

void UNexusAbilitySystemComponent::HandleAbilityActivated(UNexusAbility* InAbility)
{
	if (!InAbility) return;

	if (!InAbility->ActivationOwnedTags.IsEmpty())
	{
		AddTags(InAbility->ActivationOwnedTags);
	}

	//CancelAbilitiesWithTags(InAbility->CancelAbilitiesWithTags);
	AddTags(InAbility->AbilityTags);
	
	OnAbilityActivated.Broadcast(InAbility);
}

void UNexusAbilitySystemComponent::HandleAbilityDeactivated(UNexusAbility* InAbility)
{
	if (!InAbility) return;

	if (!InAbility->ActivationOwnedTags.IsEmpty())
	{
		RemoveTags(InAbility->ActivationOwnedTags);
	}

	RemoveTags(InAbility->AbilityTags);
	
	OnAbilityDeactivated.Broadcast(InAbility);
}

//Ability Lifecycle
UNexusAbility* UNexusAbilitySystemComponent::GiveAbility(const TSubclassOf<UNexusAbility> AbilityClass)
{
	if (!AbilityClass) return nullptr;
	
	if (UNexusAbility* Existing = GrantedAbilities.FindRef(AbilityClass))
	{
		if (!Existing->IsEnabled())
		{
			Existing->OnEnableAbility();
		}
		return Existing;
	}

	if (UNexusAbility* NewAbility = NewObject<UNexusAbility>(this, AbilityClass))
	{
		GrantedAbilities.Add(AbilityClass, NewAbility);
		OnAbilityGiven.Broadcast(NewAbility);
		NewAbility->OnActivated.AddDynamic(this, &UNexusAbilitySystemComponent::HandleAbilityActivated);
		NewAbility->OnDeactivated.AddDynamic(this, &UNexusAbilitySystemComponent::HandleAbilityDeactivated);
		return NewAbility;
	}
	
	return nullptr;
}

bool UNexusAbilitySystemComponent::RemoveAbility(const TSubclassOf<UNexusAbility> AbilityClass)
{
	if (!AbilityClass) return false;
	
	if (UNexusAbility* Existing = GrantedAbilities.FindRef(AbilityClass))
	{
		if (Existing->IsEnabled())
		{
			Existing->OnDisableAbility();
			OnAbilityRemoved.Broadcast(Existing);
			return true;
		}
	}
	
	return false;
}

bool UNexusAbilitySystemComponent::TryActivateAbilityByClass(const TSubclassOf<UNexusAbility> InAbilityToActivate)
{
	if (!InAbilityToActivate) return false;
	
	UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToActivate);
	if (!FoundAbility) return false;
	
	if (!CheckTagRequirements(FoundAbility)) return false;
	
    if (!FoundAbility->RequestActivateAbility()) return false;

	//Attempt to cancel abilities
	CancelAbilitiesWithTags(FoundAbility->CancelAbilitiesWithTags);
	
	return true;
}

bool UNexusAbilitySystemComponent::TryDeactivateAbilityByClass(const TSubclassOf<UNexusAbility> InAbilityToDeactivate)
{
	if (!InAbilityToDeactivate) return false;

	UNexusAbility* FoundAbility = GrantedAbilities.FindRef(InAbilityToDeactivate);
	if (!FoundAbility) return false;

	return FoundAbility->RequestDeactivateAbility();
}

bool UNexusAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag InAbilityTag)
{
	if (!InAbilityTag.IsValid()) return false;

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->AbilityTags.HasTag(InAbilityTag))
		{
			return TryActivateAbilityByClass(Pair.Key);
		}
	}
	return false;
}

bool UNexusAbilitySystemComponent::TryDeactivateAbilityByTag(FGameplayTag InAbilityTag)
{
	if (!InAbilityTag.IsValid()) return false;
	
	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->AbilityTags.HasTag(InAbilityTag))
		{
			return TryDeactivateAbilityByClass(Pair.Key);
		}
	}
	return false;
}

void UNexusAbilitySystemComponent::DeactivateAllAbilities()
{
	for (const auto& Pair : GrantedAbilities)
	{
		if (Pair.Value)
		{
			TryDeactivateAbilityByClass(Pair.Key);
		}
	}
}

//Utility
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


//Tags
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
	for (const auto& tag : Tags)
	{
		TryDeactivateAbilityByTag(tag);
	}
}


// EMS Component Save Interface
void UNexusAbilitySystemComponent::ComponentPreSave_Implementation()
{
	SavedAbilityState.Reset();
	SavedAbilityState.Reserve(GrantedAbilities.Num());

	for (const auto& Pair : GrantedAbilities)
	{
		const UNexusAbility* Ability = Pair.Value;
		if (!Ability) continue;

		FNexusAbilitySaveData Data;
		Ability->CaptureSaveState(Data);
		SavedAbilityState.Add(MoveTemp(Data));
	}
}

void UNexusAbilitySystemComponent::ComponentLoaded_Implementation()
{
	// Phase 0: Reset current ability state to prevent tag ref-count double-counting.
	// On a mid-session load, abilities may already be active with their tags on the
	// ASC from normal gameplay. Without this cleanup, Phase 1 would AddTags again,
	// pushing the ref count to 2. A single deactivation would only decrement once,
	// leaving the tag stuck (e.g. Ability.Locomotion.Crouch can never be removed).
	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (!Ability) continue;

		if (Ability->IsActive())
		{
			RemoveTags(Ability->AbilityTags);
			if (!Ability->ActivationOwnedTags.IsEmpty())
			{
				RemoveTags(Ability->ActivationOwnedTags);
			}
		}

		Ability->ActivationState = ENexusAbilityActivationState::Idle;
		Ability->bIsOnCooldown = false;
		Ability->CooldownElapsed = 0.0f;
	}

	// Also clear any loose tags (e.g. intents) that will be re-added by ApplySaveState
	for (const FNexusAbilitySaveData& Data : SavedAbilityState)
	{
		for (const FGameplayTag& Tag : Data.CustomTags)
		{
			RemoveLooseGameplayTag(Tag);
		}
	}

	// Phase 1: Restore base state + custom state on each ability
	for (const FNexusAbilitySaveData& Data : SavedAbilityState)
	{
		if (!Data.AbilityClass) continue;

		UNexusAbility* Ability = GrantedAbilities.FindRef(Data.AbilityClass);
		if (!Ability)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("NexusASC: Saved ability class '%s' not found in GrantedAbilities. Skipping."),
				*Data.AbilityClass->GetName());
			continue;
		}

		RestoreAbilityState(Ability, Data);
	}

	// Phase 2: Side effects (after all abilities and tags are consistent)
	for (const FNexusAbilitySaveData& Data : SavedAbilityState)
	{
		if (!Data.AbilityClass) continue;

		if (UNexusAbility* Ability = GrantedAbilities.FindRef(Data.AbilityClass))
		{
			Ability->OnSaveStateRestored();
		}
	}

	SavedAbilityState.Reset();
}

void UNexusAbilitySystemComponent::RestoreAbilityState(UNexusAbility* Ability, const FNexusAbilitySaveData& Data)
{
	// 1. Restore enabled state
	Ability->bIsEnabled = Data.bIsEnabled;

	// 2. Restore cooldown with expiry check
	if (Data.bIsOnCooldown)
	{
		const float Remaining = Data.CooldownTotalDuration - Data.CooldownElapsed;
		if (Remaining > KINDA_SMALL_NUMBER)
		{
			Ability->bIsOnCooldown = true;
			Ability->CooldownElapsed = Data.CooldownElapsed;
		}
		else
		{
			Ability->bIsOnCooldown = false;
			Ability->CooldownElapsed = 0.0f;
		}
	}
	else
	{
		Ability->bIsOnCooldown = false;
		Ability->CooldownElapsed = 0.0f;
	}

	// 3. Restore activation state directly (bypass CommitAbility to avoid replaying events)
	Ability->ActivationState = Data.ActivationState;

	// 4. If the ability was active, replicate what HandleAbilityActivated does:
	//    add its tags to the ASC's ref-counted tag system.
	if (Data.ActivationState == ENexusAbilityActivationState::Active)
	{
		AddTags(Ability->AbilityTags);

		if (!Ability->ActivationOwnedTags.IsEmpty())
		{
			AddTags(Ability->ActivationOwnedTags);
		}
	}

	// 5. Let the subclass restore its custom state (intent tags, etc.)
	Ability->ApplySaveState(Data);
}
