// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "NexusAbility_LocomotionCrouch.generated.h"

/**
 * 
 */
UCLASS()
class NEXUS_API UNexusAbility_LocomotionCrouch : public UNexusAbility
{
	GENERATED_BODY()

protected:
	UNexusAbility_LocomotionCrouch();
	
	virtual void OnActivateAbility() override;
	virtual void OnDeactivateAbility() override;
};
