// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Weapon/Abilities/NexusAbility_Weapon.h"
#include "NexusAbility_WeaponAim.generated.h"

UCLASS(Blueprintable)
class NEXUS_API UNexusAbility_WeaponAim : public UNexusAbility_Weapon
{
	GENERATED_BODY()

public:
	UNexusAbility_WeaponAim();

protected:
	virtual void CommitAbility() override;
	virtual void CommitAbilityEnd() override;
	virtual void ForceEndAbility() override;
	virtual bool CanActivateAbility_Implementation() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aim", meta = (ClampMin = "10.0", ClampMax = "120.0"))
	float AimFOV = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aim", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AimWalkSpeedScale = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aim", meta = (ClampMin = "0.0"))
	float BlendInDuration = 0.18f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aim", meta = (ClampMin = "0.0"))
	float BlendOutDuration = 0.14f;

	virtual void OnSaveStateRestored() override;

private:
	void ApplyAimEffects();
	void RemoveAimEffects();

	/** True while we have an active speed multiplier applied — guards against double-apply / double-remove. */
	bool bSpeedScaleApplied = false;
};