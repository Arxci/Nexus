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
	
	AddTags(InAbility->ActivationOwnedTags);
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

void UNexusAbilitySystemComponent::ClearAbilities()
{
	for (const auto& Pair : GrantedAbilities)
	{
		if (UNexusAbility* Ability = Pair.Value)
		{
			Ability->OnActivated.Clear();
			Ability->OnDeactivated.Clear();
			Ability->ForceEndAbility();
		}
	}
	GrantedAbilities.Empty();
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

bool UNexusAbilitySystemComponent::ForceEndAbilityByTag(FGameplayTag InAbilityTag)
{
	if (!InAbilityTag.IsValid()) return false;

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->AbilityTags.HasTag(InAbilityTag))
		{
			Ability->ForceEndAbility();
			return true;
		}
	}
	return false;
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

TArray<UNexusAbility*> UNexusAbilitySystemComponent::GetGivenAbilities() const
{
	TArray<UNexusAbility*> Result;
	for (const auto& Pair : GrantedAbilities)
	{
		if (Pair.Value && Pair.Value->IsEnabled())
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

void UNexusAbilitySystemComponent::ComponentPreLoad_Implementation()
{
	OwnedTags.Reset();
	TagRefCounts.Empty();
	UE_LOG(LogTemp, Error, TEXT("Granted abilities pre clear:"));
	for (const auto& Pair : GrantedAbilities)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability: %s"), *Pair.Value->GetName());
	}
	ClearAbilities();
	UE_LOG(LogTemp, Error, TEXT("Granted abilities post clear:"));
	for (const auto& Pair : GrantedAbilities)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability: %s"), *Pair.Value->GetName());
	}
}


void UNexusAbilitySystemComponent::ComponentLoaded_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Loaded abilities (Expect: %d):"), SavedAbilityState.Num());
	for (const FNexusAbilitySaveData& Data : SavedAbilityState)
	{
		UNexusAbility* LoadedAbility = Data.Ability.Get();
		if (!LoadedAbility) continue;
		
		UE_LOG(LogTemp, Warning, TEXT("Ability: %s"), *LoadedAbility->GetName());
		GrantedAbilities.Add(LoadedAbility->GetClass(), LoadedAbility);
		LoadedAbility->OnActivated.AddDynamic(this, &UNexusAbilitySystemComponent::HandleAbilityActivated);
		LoadedAbility->OnDeactivated.AddDynamic(this, &UNexusAbilitySystemComponent::HandleAbilityDeactivated);

		RestoreAbilityState(LoadedAbility, Data);
	}
	UE_LOG(LogTemp, Error, TEXT("Owned tags:"));
	for (const FGameplayTag& Tag : OwnedTags)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tag: %s"), *Tag.ToString());
	}
	SavedAbilityState.Reset();
}

void UNexusAbilitySystemComponent::RestoreAbilityState(UNexusAbility* Ability, const FNexusAbilitySaveData& Data)
{
	if (Data.bIsOnCooldown)
	{
		if (Data.CooldownTotalDuration - Data.CooldownElapsed > KINDA_SMALL_NUMBER)
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

	Ability->bIsEnabled = Data.bIsEnabled;
	Ability->ActivationState = Data.ActivationState;
	
	if (Data.ActivationState == ENexusAbilityActivationState::Active)
	{
		AddTags(Ability->ActivationOwnedTags);
		AddTags(Ability->AbilityTags);
	}

	for (const FGameplayTag& Tag : Data.CustomTags)
	{
		AddLooseGameplayTag(Tag);
	}

	Ability->OnSaveStateRestored();
}
