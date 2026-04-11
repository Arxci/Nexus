#include "NexusCharacterMovementComponent.h"

UNexusCharacterMovementComponent::UNexusCharacterMovementComponent()
{

}

void UNexusCharacterMovementComponent::StartRunning()
{
	if (bIsRunning) return;

	bIsRunning = true;
	CachedWalkSpeed = MaxWalkSpeed;
	MaxWalkSpeed = MaxWalkSpeedRun;
	OnRunStart.Broadcast();
}

void UNexusCharacterMovementComponent::StopRunning()
{
	if (!bIsRunning) return;

	bIsRunning = false;
	MaxWalkSpeed = CachedWalkSpeed;
	OnRunEnd.Broadcast();
}