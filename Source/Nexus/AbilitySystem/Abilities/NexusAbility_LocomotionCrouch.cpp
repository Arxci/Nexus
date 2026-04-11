// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionCrouch.h"
#include "GameFramework/Character.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionCrouch::UNexusAbility_LocomotionCrouch()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);
	// NOTE: Character_State_Locomotion_Crouch is intentionally NOT in
	// ActivationOwnedTags. It is driven by NexusCharacterBase::OnStartCrouch/
	// OnEndCrouch as a loose ASC tag, so the tag reflects the capsule's real
	// size rather than this ability's lifecycle. That is what lets this ability
	// refuse to end (and keep Run blocked) when overhead geometry prevents the
	// character from standing up.
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Run);
	InputTag = NexusGameplayTags::InputTag_Crouch;
}

void UNexusAbility_LocomotionCrouch::OnActivateAbility()
{
	Super::OnActivateAbility();

	bAwaitingUncrouch = false;

	// Listen for the crouch state tag dropping. We only act on this while
	// we're in the Ending phase (bAwaitingUncrouch) — adds and unrelated
	// tag changes are ignored.
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->OnTagChanged.AddDynamic(this, &UNexusAbility_LocomotionCrouch::HandleAscTagChanged);
	}

	if (ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		Char->Crouch();
	}
}

bool UNexusAbility_LocomotionCrouch::OnEndAbilityRequested(bool bForce)
{
	if (bForce)
	{
		// Forced teardown (EndPlay, death, ability disabled). Unbind synchronously
		// and let the ASC commit — we cannot afford to wait on a physics state
		// that may never transition because the owner is going away.
		if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
		{
			ASC->OnTagChanged.RemoveDynamic(this, &UNexusAbility_LocomotionCrouch::HandleAscTagChanged);
		}
		bAwaitingUncrouch = false;
		return false;
	}

	// Soft request: ask the character to stand up. The CMC will only succeed
	// when there is vertical clearance; if blocked, it will keep retrying on
	// subsequent ticks. We defer commit until OnEndCrouch eventually fires on
	// the character, which removes the loose tag and triggers our listener.
	bAwaitingUncrouch = true;

	if (ACharacter* Char = Cast<ACharacter>(GetAvatarActor()))
	{
		Char->UnCrouch();
	}

	// Edge case: if we somehow ended up Active without the crouch state tag
	// (e.g., Char->Crouch() silently failed during activation), there is
	// nothing to wait for — commit immediately.
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		if (!ASC->HasTag(NexusGameplayTags::Character_State_Locomotion_Crouch))
		{
			ASC->OnTagChanged.RemoveDynamic(this, &UNexusAbility_LocomotionCrouch::HandleAscTagChanged);
			bAwaitingUncrouch = false;
			return false;
		}
	}

	return true; // Defer — HandleAscTagChanged will call EndAbility() when ready.
}

void UNexusAbility_LocomotionCrouch::OnDeactivateAbility()
{
	Super::OnDeactivateAbility();

	// Safety net: guarantee the listener is gone regardless of which path
	// reached commit (deferred uncrouch, forced teardown, or early-out).
	if (UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		ASC->OnTagChanged.RemoveDynamic(this, &UNexusAbility_LocomotionCrouch::HandleAscTagChanged);
	}

	bAwaitingUncrouch = false;
}

void UNexusAbility_LocomotionCrouch::HandleAscTagChanged(FGameplayTag Tag, bool bAdded)
{
	// We only care about the crouch state tag dropping, and only once the
	// ability has been asked to wind down. Adds (including the initial add
	// from Char->Crouch() in OnActivateAbility) are ignored.
	if (!bAwaitingUncrouch) return;
	if (bAdded) return;
	if (Tag != NexusGameplayTags::Character_State_Locomotion_Crouch) return;

	// The CMC has finished resizing the capsule back to stand height. Commit.
	EndAbility();
}
