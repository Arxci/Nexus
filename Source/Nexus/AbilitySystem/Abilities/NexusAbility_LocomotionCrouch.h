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
	
	virtual bool OnRequestActivateAbility() override;
	virtual bool OnRequestDeactivateAbility(bool bForce) override;
	virtual bool CanActivateAbility_Implementation() const override;
	virtual void HandleAbilityStart() override;
	virtual void HandleAbilityStop() override;
	virtual void HandleAbilityProgress() override;
	
private:
	
	bool CanCharacterStand();


};
