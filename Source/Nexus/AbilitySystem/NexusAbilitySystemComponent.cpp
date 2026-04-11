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
	// Force: the owner is going away. We cannot afford any ability to refuse
	// to end or defer its wind-down past this point.
	DeactivateAllAbilities(/*bForce=*/true);
	Super::EndPlay(EndPlayReason);
}

// --- Ability Lifecycle ---

UNexusAbility* UNexusAbilitySystemComponent::GiveAbility(const TSubclassOf<UNexusAbility> AbilityClass)
{
	if (!AbilityClass) return nullptr;
	
	if (UNexusAbility* Existing = GrantedAbilities.FindRef(AbilityClass))
	{
		// Already granted. Re-enable if needed, but do not re-broadcast
		// OnAbilityGiven — that delegate is reserved for first-time grants.
		if (!Existing->IsEnabled())
		{
			SetAbilityEnabled(AbilityClass, true);
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

    if (FoundAbility->IsActive() || FoundAbility->IsEnding())
    {
        // Already running. How we respond is governed by the ability's
        // InstancePolicy — toggle-style abilities reject re-activation,
        // retrigger abilities force-end first and then re-activate, and
        // ignore-if-active abilities silently succeed.
        switch (FoundAbility->GetInstancePolicy())
        {
        case ENexusAbilityInstancePolicy::OnceAtATime:
            UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] FAILED: already active (state=%s)"),
                *InAbilityToActivate->GetName(),
                FoundAbility->IsEnding() ? TEXT("Ending") : TEXT("Active"));
            return ENexusAbilityActivationResult::AlreadyActive;

        case ENexusAbilityInstancePolicy::IgnoreIfActive:
            UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] SUCCESS (no-op: IgnoreIfActive)"),
                *InAbilityToActivate->GetName());
            return ENexusAbilityActivationResult::Success;

        case ENexusAbilityInstancePolicy::Retrigger:
            UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("TryActivate [%s] retrigger: force-ending running instance"),
                *InAbilityToActivate->GetName());
            DeactivateAbility(FoundAbility, /*bForce=*/true);
            // Fall through to activation below.
            break;
        }
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

    	// Even though we can't activate right now, give the ability a chance
    	// to kick its declared blockers into wind-down. They may defer (e.g.
    	// Crouch waiting on overhead clearance), but the moment their state
    	// tag drops, EvaluateHeldInputRetries will re-fire us — as long as
    	// the player is still holding the input.
    	if (!FoundAbility->CancelAbilitiesWithTags.IsEmpty())
    	{
    		CancelAbilitiesWithTags(FoundAbility->CancelAbilitiesWithTags);
    	}

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

    if (FoundAbility->CooldownStartPolicy == ENexusCooldownStartPolicy::OnActivate)
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

	// Allow kicking off wind-down even if a previous request is still pending —
	// the ability's OnEndAbilityRequested won't be re-entered in that case.
	if (!FoundAbility->IsActive() && !FoundAbility->IsEnding()) return false;

	DeactivateAbility(FoundAbility);

	return true;
}

void UNexusAbilitySystemComponent::DeactivateAbility(UNexusAbility* Ability, bool bForce)
{
	if (!Ability) return;
	if (Ability->IsIdle()) return;

	if (Ability->IsEnding())
	{
		// Already winding down. A soft re-cancel is a no-op (the ability is
		// still waiting on its original deferral). A force upgrades the wait
		// to an immediate teardown: notify the ability so it can unbind any
		// listeners, then commit.
		if (bForce)
		{
			Ability->OnEndAbilityRequested(/*bForce=*/true);
			CommitAbilityEnd(Ability);
		}
		return;
	}

	// First-time transition into Ending. The ability still holds its owned
	// tags and cannot be re-activated while in this state.
	Ability->ActivationState = ENexusAbilityActivationState::Ending;

	const ENexusEndRequestResult EndResult = Ability->OnEndAbilityRequested(bForce);

	// A forced deactivation always commits. A soft deactivation commits only
	// if the ability did not ask to defer. Note that if the ability called
	// EndAbility() synchronously inside OnEndAbilityRequested, the state is
	// already Idle and CommitAbilityEnd will early-out.
	if (bForce || EndResult == ENexusEndRequestResult::CommitNow)
	{
		CommitAbilityEnd(Ability);
	}
}

void UNexusAbilitySystemComponent::CommitAbilityEnd(UNexusAbility* Ability)
{
	if (!Ability || Ability->IsIdle()) return;

	Ability->ActivationState = ENexusAbilityActivationState::Idle;

	if (!Ability->ActivationOwnedTags.IsEmpty())
	{
		RemoveTags(Ability->ActivationOwnedTags);
	}

	Ability->OnDeactivateAbility();
	OnAbilityDeactivated.Broadcast(Ability);

	if (Ability->CooldownStartPolicy == ENexusCooldownStartPolicy::OnEnd)
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

		if (!bEnabled && (FoundAbility->IsActive() || FoundAbility->IsEnding()))
		{
			// Disabling an ability must not leave it lingering in an Ending
			// state that can never commit (the ability is gone — no one is
			// listening to its wait condition anymore).
			DeactivateAbility(FoundAbility, /*bForce=*/true);
		}
	}
}

void UNexusAbilitySystemComponent::DeactivateAllAbilities(bool bForce)
{
	TArray<UNexusAbility*, TInlineAllocator<8>> ToDeactivate;
	for (const auto& Pair : GrantedAbilities)
	{
		if (Pair.Value && (Pair.Value->IsActive() || Pair.Value->IsEnding()))
		{
			ToDeactivate.Add(Pair.Value);
		}
	}
	for (UNexusAbility* Ability : ToDeactivate)
	{
		DeactivateAbility(Ability, bForce);
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
		if (Ability && (Ability->IsActive() || Ability->IsEnding()) && Ability->AbilityTags.HasTag(AbilityTag))
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
	bool bAnyRemoved = false;
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
				bAnyRemoved = true;
			}
		}
	}

	// One retry pass after the whole container has been processed — not per
	// tag — so a multi-tag removal only re-evaluates held inputs once.
	if (bAnyRemoved)
	{
		EvaluateHeldInputRetries();
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
			EvaluateHeldInputRetries();
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
		if (Ability && (Ability->IsActive() || Ability->IsEnding()))
		{
			if (Ability->AbilityTags.HasAny(Tags))
			{
				AbilitiesToCancel.Add(Ability);
			}
		}
	}

	// Soft cancel: the cancelled ability is allowed to defer teardown if it
	// needs to wait on external state. Callers that depend on the cancelled
	// ability being *actually* gone before they proceed should not rely on
	// this alone — gate your activation via ActivationBlockedTags against a
	// state tag that only drops when the cancelled ability has truly ended.
	for (UNexusAbility* Ability : AbilitiesToCancel)
	{
		DeactivateAbility(Ability);
	}
}

void UNexusAbilitySystemComponent::EvaluateHeldInputRetries()
{
	// Re-entrancy guard: activating an ability from inside this function
	// can synchronously drop tags (via CommitAbilityEnd → RemoveTags), which
	// would otherwise re-enter us mid-iteration.
	if (bEvaluatingHeldInputRetries) return;
	if (HeldInputTags.IsEmpty()) return;

	bEvaluatingHeldInputRetries = true;

	// Snapshot the held inputs. Activation can mutate ASC state, and we
	// don't want to iterate HeldInputTags directly while that's happening.
	TArray<FGameplayTag, TInlineAllocator<4>> InputSnapshot;
	for (const FGameplayTag& Tag : HeldInputTags)
	{
		InputSnapshot.Add(Tag);
	}

	for (const FGameplayTag& InputTag : InputSnapshot)
	{
		// Snapshot the candidate classes too — TryActivate can synchronously
		// deactivate other abilities, and while GrantedAbilities itself is
		// pool-stable, we'd rather not rely on that invariant here.
		TArray<TSubclassOf<UNexusAbility>, TInlineAllocator<4>> Candidates;
		for (const auto& Pair : GrantedAbilities)
		{
			const UNexusAbility* Ability = Pair.Value;
			if (!Ability) continue;
			if (Ability->InputTag != InputTag) continue;
			if (!Ability->IsIdle()) continue;      // Already running or ending — don't disturb.
			if (!Ability->IsEnabled()) continue;
			Candidates.Add(Pair.Key);
		}

		for (const TSubclassOf<UNexusAbility>& AbilityClass : Candidates)
		{
			TryActivateAbilityByClassWithResult(AbilityClass);
		}
	}

	bEvaluatingHeldInputRetries = false;
}

// Input Routing

void UNexusAbilitySystemComponent::AbilityInputPressed(FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	// Latch the press. Even if none of the matching abilities can activate
	// right now, EvaluateHeldInputRetries will retry the moment any blocking
	// tag is removed — which is what lets "hold Run while Crouch is stuck
	// under a ceiling" auto-start Run the instant the capsule clears.
	HeldInputTags.AddTag(InputTag);

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

	// Drop the latch first — if the retry path runs between here and the
	// deactivation loop (e.g. because a deactivation synchronously commits
	// and drops a state tag), we don't want to immediately re-activate the
	// ability the player just released.
	HeldInputTags.RemoveTag(InputTag);

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (Ability && Ability->IsActive() && Ability->InputTag == InputTag)
		{
			DeactivateAbility(Ability);
		}
	}
}

void UNexusAbilitySystemComponent::AbilityInputToggled(FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	// Snapshot the classes we want to touch before dispatching, because
	// activation / deactivation can mutate GrantedAbilities indirectly
	// (future instance-policy work, tag-driven cancel lists, etc.).
	TArray<TSubclassOf<UNexusAbility>, TInlineAllocator<4>> ToActivate;
	TArray<UNexusAbility*, TInlineAllocator<4>> ToDeactivate;

	for (const auto& Pair : GrantedAbilities)
	{
		UNexusAbility* Ability = Pair.Value;
		if (!Ability || Ability->InputTag != InputTag) continue;

		if (Ability->IsActive() || Ability->IsEnding())
		{
			ToDeactivate.Add(Ability);
		}
		else
		{
			ToActivate.Add(Pair.Key);
		}
	}

	for (UNexusAbility* Ability : ToDeactivate)
	{
		DeactivateAbility(Ability);
	}
	for (const TSubclassOf<UNexusAbility>& AbilityClass : ToActivate)
	{
		TryActivateAbilityByClass(AbilityClass);
	}
}

// --- Easy Multi Save integration ---

void UNexusAbilitySystemComponent::ComponentPreSave_Implementation()
{
	CaptureSaveState();
}

void UNexusAbilitySystemComponent::ComponentLoaded_Implementation()
{
	RestoreSaveState();
}

void UNexusAbilitySystemComponent::CaptureSaveState()
{
	SavedAbilityState.Reset();
	SavedAbilityState.Reserve(GrantedAbilities.Num());

	for (const auto& Pair : GrantedAbilities)
	{
		const UNexusAbility* Ability = Pair.Value;
		if (!Ability) continue;

		FNexusAbilitySaveEntry Entry;
		Entry.AbilityClass = TSoftClassPtr<UNexusAbility>(Pair.Key.Get());
		Entry.bEnabled = Ability->IsEnabled();
		Entry.CooldownTimeRemaining = Ability->GetCooldownRemaining();
		SavedAbilityState.Add(MoveTemp(Entry));
	}

	UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("CaptureSaveState: %d abilities"),
		SavedAbilityState.Num());
}

void UNexusAbilitySystemComponent::RestoreSaveState()
{
	const UWorld* World = GetWorld();
	const float WorldTime = World ? World->GetTimeSeconds() : 0.0f;

	for (const FNexusAbilitySaveEntry& Entry : SavedAbilityState)
	{
		UClass* ResolvedClass = Entry.AbilityClass.LoadSynchronous();
		if (!ResolvedClass)
		{
			UE_LOG(LogNexusAbilitySystem, Warning,
				TEXT("RestoreSaveState: failed to resolve ability class '%s' — skipping. "
				     "Was the class deleted or moved since the save was taken?"),
				*Entry.AbilityClass.ToString());
			continue;
		}

		// GiveAbility is idempotent — if the class was already granted via
		// ANexusCharacterBase::PossessedBy (DefaultAbilities), this returns
		// the existing instance without re-broadcasting OnAbilityGiven.
		UNexusAbility* Ability = GiveAbility(ResolvedClass);
		if (!Ability)
		{
			UE_LOG(LogNexusAbilitySystem, Warning,
				TEXT("RestoreSaveState: GiveAbility returned null for class '%s'"),
				*ResolvedClass->GetName());
			continue;
		}

		// Enable/disable without going through SetAbilityEnabled's
		// force-deactivate branch — restoration happens on a cold ASC whose
		// abilities are all Idle, so there's nothing to tear down.
		Ability->bIsEnabled = Entry.bEnabled;

		// Rebuild CooldownEndTime from the saved remaining time. We only
		// write a non-zero end time if the ability had cooldown left at
		// save time; a fully-cooled ability gets a zero, which IsOnCooldown
		// correctly reads as "not on cooldown."
		if (Entry.CooldownTimeRemaining > 0.0f && World)
		{
			Ability->CooldownEndTime = WorldTime + Entry.CooldownTimeRemaining;
		}
		else
		{
			Ability->CooldownEndTime = 0.0f;
		}
	}

	UE_LOG(LogNexusAbilitySystem, Verbose, TEXT("RestoreSaveState: restored %d abilities"),
		SavedAbilityState.Num());

	// We don't clear SavedAbilityState here — it gets overwritten on the
	// next CaptureSaveState, and leaving it intact lets debug tools inspect
	// "what did EMS last hand us?" after a load.
}