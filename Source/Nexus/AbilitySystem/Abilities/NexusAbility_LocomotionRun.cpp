// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_LocomotionRun.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_LocomotionRun::UNexusAbility_LocomotionRun()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Locomotion_Run);
	// NOTE: Character_State_Locomotion_Run is intentionally NOT in
	// ActivationOwnedTags. It is driven by NexusCharacterBase from the CMC's
	// OnRunStart/OnRunEnd delegates, so the tag reflects whether the CMC is
	// actually boost-running right now — not whether this ability happens to
	// be Active. ActivationBlockedTags below checks the Crouch state tag,
	// which is likewise character-driven, so Run cannot activate while the
	// capsule is physically at crouch height (even if the Crouch ability is
	// stuck in Ending because overhead geometry is blocking the uncrouch).
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Locomotion_Crouch);

	// Pressing Run while crouched should boot Crouch out. The activation will
	// still be refused on the first try (the crouch state tag is character-
	// driven and only drops after the CMC finishes resizing), but the ASC's
	// EvaluateHeldInputRetries will re-fire Run the moment the tag clears —
	// which is the same path that handles "hold Run while stuck under a ledge."
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Locomotion_Crouch);

	InputTag = NexusGameplayTags::InputTag_Run;
	bCanTick = true;
}

void UNexusAbility_LocomotionRun::OnActivateAbility()
{
	bIsBoostActive = false;
	Super::OnActivateAbility();
}

void UNexusAbility_LocomotionRun::OnDeactivateAbility()
{
	SetBoostActive(false);
	Super::OnDeactivateAbility();
}

void UNexusAbility_LocomotionRun::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);

	const bool bShould = ShouldBoostThisFrame();
	if (bShould != bIsBoostActive)
	{
		SetBoostActive(bShould);
	}
}

bool UNexusAbility_LocomotionRun::ShouldBoostThisFrame() const
{
	const ACharacter* Char = Cast<ACharacter>(GetAvatarActor());
	if (!Char) return false;

	const UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
	if (!MoveComp || !MoveComp->IsMovingOnGround()) return false;

	const FVector InputVector = MoveComp->GetLastInputVector();
	if (InputVector.IsNearlyZero()) return false;

	const FVector Forward = Char->GetActorForwardVector();
	return FVector::DotProduct(Forward, InputVector.GetSafeNormal()) > BoostThreshold;
}

void UNexusAbility_LocomotionRun::SetBoostActive(bool bNewActive)
{
	if (bIsBoostActive == bNewActive) return;

	// Route through the character, mirroring how Crouch goes through
	// ACharacter::Crouch(). The character forwards to the CMC and owns the
	// tag mirror via its OnRunStart/OnRunEnd delegate binding.
	ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetAvatarActor());
	if (!Char) return;

	bIsBoostActive = bNewActive;
	if (bNewActive)
	{
		Char->StartRunning();
	}
	else
	{
		Char->StopRunning();
	}
}