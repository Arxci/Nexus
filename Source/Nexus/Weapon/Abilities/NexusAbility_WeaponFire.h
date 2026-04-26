// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Weapon/Abilities/NexusAbility_Weapon.h"
#include "NexusAbility_WeaponFire.generated.h"

UCLASS(Blueprintable)
class NEXUS_API UNexusAbility_WeaponFire : public UNexusAbility_Weapon
{
	GENERATED_BODY()

public:
	UNexusAbility_WeaponFire();

protected:
	virtual bool RequestActivateAbility() override;
	virtual void CommitAbility() override;
	virtual bool CanActivateAbility_Implementation() const override;
	
	/** Drives cooldown from the active weapon's RPM instead of mutating the SaveGame field on the base. */
	virtual float GetCooldownTotalDuration() const override;
	virtual bool  HasCooldown() const override;
	
	void FireShot();
	void FireOnePellet(const FVector& ViewLoc, const FRotator& ViewRot);
	class UAnimMontage* PlayMontageSafe(const TSoftObjectPtr<UAnimMontage>& Soft) const;
	void HandleDryFire();

	/** Computes the recoil impulse for the current shot, advancing the recoil pattern. */
	FVector ConsumeRecoilImpulse();

private:
	// Recoil pattern state — transient, intentionally not SaveGame.
	// LastFireTime is initialised low enough that the first shot in a fresh session
	// always passes the reset check.
	float LastFireTime = -1000.0f;
	int32 ShotIndex    = 0;
};