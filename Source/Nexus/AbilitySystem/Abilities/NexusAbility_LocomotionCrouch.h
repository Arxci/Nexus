// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "NexusAbility_LocomotionCrouch.generated.h"

UCLASS()
class NEXUS_API UNexusAbility_LocomotionCrouch : public UNexusAbility
{
	GENERATED_BODY()

protected:
	UNexusAbility_LocomotionCrouch();
	
	virtual void OnActivateAbility() override;
	virtual ENexusEndRequestResult OnEndAbilityRequested(bool bForce) override;
	virtual void OnDeactivateAbility() override;

private:
	/** Handler for UNexusAbilitySystemComponent::OnTagChanged. */
	UFUNCTION()
	void HandleAscTagChanged(FGameplayTag Tag, bool bAdded);

	/** True while we're in the Ending phase waiting on the CMC to actually uncrouch. */
	bool bAwaitingUncrouch = false;
};
