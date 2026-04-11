// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility.h"
#include "NexusAbilitySystemComponent.h"

UNexusAbility::UNexusAbility()
{
	bIsEnabled = true;
}

void UNexusAbility::OnActivateAbility()
{
	K2_OnAbilityActivated();
}

void UNexusAbility::OnDeactivateAbility()
{
	K2_OnAbilityDeactivated();
}

bool UNexusAbility::CanActivateAbility_Implementation() const
{
	return true;
}

void UNexusAbility::EndAbility()
{
	if (UNexusAbilitySystemComponent* Comp = GetNexusAbilitySystemComponent())
	{
		Comp->DeactivateAbility(this);
	}
}

bool UNexusAbility::IsOnCooldown() const
{
	if (CooldownDuration <= 0.0f) return false;
	const UWorld* World = GetWorld();
	return World && World->GetTimeSeconds() < CooldownEndTime;
}

float UNexusAbility::GetCooldownRemaining() const
{
	if (CooldownDuration <= 0.0f) return 0.0f;
	const UWorld* World = GetWorld();
	if (!World) return 0.0f;
	return FMath::Max(0.0f, CooldownEndTime - World->GetTimeSeconds());
}

float UNexusAbility::GetCooldownProgress() const
{
	if (CooldownDuration <= 0.0f) return 1.0f;
	const float Remaining = GetCooldownRemaining();
	if (Remaining <= 0.0f) return 1.0f;
	return 1.0f - Remaining / CooldownDuration;
}

void UNexusAbility::CommitCooldown()
{
	if (CooldownDuration > 0.0f)
	{
		if (const UWorld* World = GetWorld())
		{
			CooldownEndTime = World->GetTimeSeconds() + CooldownDuration;
		}
	}
}

UNexusAbilitySystemComponent* UNexusAbility::GetNexusAbilitySystemComponent() const
{
	return Cast<UNexusAbilitySystemComponent>(GetOuter());
}

AActor* UNexusAbility::GetAvatarActor() const
{
	if (const UNexusAbilitySystemComponent* Comp = GetNexusAbilitySystemComponent())
	{
		return Comp->GetAvatarActor();
	}
	return nullptr;
}

AController* UNexusAbility::GetController() const
{
	if (const UNexusAbilitySystemComponent* Comp = GetNexusAbilitySystemComponent())
	{
		return Comp->GetController(); 
	}
	return nullptr;
}

UWorld* UNexusAbility::GetWorld() const
{
	if (const AActor* Actor = GetAvatarActor())
	{
		return Actor->GetWorld();
	}
	return nullptr;
}