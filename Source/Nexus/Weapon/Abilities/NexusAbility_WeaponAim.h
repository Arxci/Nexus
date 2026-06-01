#pragma once

#include "CoreMinimal.h"

#include "Nexus/Weapon/Abilities/NexusAbility_Weapon.h"

#include "NexusAbility_WeaponAim.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAimProgress, float, AimAlpha);


/**
 * Over-the-shoulder steady-aim (the RE4R model — no FOV zoom). A held ability that,
 * while active, owns Character.State.Weapon.Aiming — which tightens the Fire spread
 * and engages recoil control (both already read the tag) — and ramps an aim alpha
 * 0 -> 1 over the effective Stat.Weapon.ADSTime so the camera, arms anim, reticle and
 * laser can ease in. It does NOT block Fire: you can shoot while aiming, and aiming
 * can begin while firing.
 *
 * The reticle / laser is driven off the Aiming state tag + OnAimProgress, so a HUD or
 * a laser-beam component subscribes without this ability knowing any UI shape.
 */
UCLASS(Blueprintable)
class NEXUS_API UNexusAbility_WeaponAim : public UNexusAbility_Weapon
{
	GENERATED_BODY()

public:
	UNexusAbility_WeaponAim();

	/** 0 = hip, 1 = fully aimed. Ramps over Stat.Weapon.ADSTime while held. */
	UFUNCTION(BlueprintPure, Category = "Weapon Ability|Aim")
	float GetAimAlpha() const { return AimAlpha; }

	/** Broadcasts the aim alpha as it ramps (camera / reticle / laser ease-in). */
	UPROPERTY(BlueprintAssignable, Category = "Weapon Ability|Aim")
	FOnWeaponAimProgress OnAimProgress;

protected:
	virtual bool RequestActivateAbility() override;
	virtual bool RequestDeactivateAbility(bool bForce) override;
	virtual void CommitAbility() override;
	virtual void CommitAbilityEnd() override;
	virtual bool CanActivateAbility_Implementation() const override;

	virtual void TickAbility(float DeltaTime) override;
	virtual bool CanTick() override;

	virtual void OnSaveStateRestored() override;

private:
	/** Effective ADS ramp time (seconds) from Stat.Weapon.ADSTime; 0 = instant. */
	float GetADSTime() const;

	void SetAimAlpha(float NewAlpha);

	float AimAlpha = 0.0f;
};
