// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Weapon/Abilities/NexusAbility_Weapon.h"
#include "NexusAbility_WeaponReload.generated.h"

UCLASS(Blueprintable)
class NEXUS_API UNexusAbility_WeaponReload : public UNexusAbility_Weapon
{
	GENERATED_BODY()

public:
	UNexusAbility_WeaponReload();

protected:
	virtual bool RequestActivateAbility() override;
	virtual bool RequestDeactivateAbility(bool bForce) override;
	virtual void CommitAbility() override;
	virtual void CommitAbilityEnd() override;
	virtual bool CanActivateAbility_Implementation() const override;
	virtual void OnSaveStateRestored() override;

	void FinishReload();
	int32 GetReserveAmmo() const;
	int32 ConsumeReserveAmmo(int32 Amount);

	FTimerHandle TimerHandle_ReloadFinish;
};