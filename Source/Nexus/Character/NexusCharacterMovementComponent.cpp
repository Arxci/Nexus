#include "NexusCharacterMovementComponent.h"

UNexusCharacterMovementComponent::UNexusCharacterMovementComponent()
{
}

void UNexusCharacterMovementComponent::StartSprinting()
{
	if (bIsSprinting) return;

	bIsSprinting = true;
	CachedWalkSpeed = MaxWalkSpeed;
	MaxWalkSpeed = SprintSpeed;
	OnSprintStart.Broadcast();
}

void UNexusCharacterMovementComponent::StopSprinting()
{
	if (!bIsSprinting) return;

	bIsSprinting = false;
	MaxWalkSpeed = CachedWalkSpeed;
	OnSprintEnd.Broadcast();
}