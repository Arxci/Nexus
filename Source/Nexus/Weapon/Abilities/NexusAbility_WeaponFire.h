#pragma once

#include "CoreMinimal.h"

#include "Nexus/Weapon/Abilities/NexusAbility_Weapon.h"

#include "NexusAbility_WeaponFire.generated.h"

class UNexusHitDelivery;
struct FHitResult;
enum class ENexusWeaponFireMode : uint8;


UCLASS(Blueprintable)
class NEXUS_API UNexusAbility_WeaponFire : public UNexusAbility_Weapon
{
	GENERATED_BODY()

public:
	UNexusAbility_WeaponFire();

protected:
	virtual bool RequestActivateAbility() override;
	virtual bool RequestDeactivateAbility(bool bForce) override;
	virtual void CommitAbility() override;
	virtual void CommitAbilityEnd() override;
	virtual bool CanActivateAbility_Implementation() const override;

	virtual float GetCooldownTotalDuration() const override;
	virtual bool  HasCooldown() const override;

	// Full-auto / burst stay Active and re-fire from the tick at the RPM cadence; semi /
	// shotgun fire once and end immediately so they never tick.
	virtual void TickAbility(float DeltaTime) override;
	virtual bool CanTick() override;

	/** Mid-action save restores to a clean ready state (mirrors Reload). */
	virtual void OnSaveStateRestored() override;

protected:
	/** Consume ammo, build the delivery request from effective stats, run the strategy per pellet, present. */
	void FireShot() const;
	void HandleDryFire() const;

	/** The active ranged weapon's fire mode (SemiAuto when unresolved). */
	ENexusWeaponFireMode GetFireMode() const;

	/** True if the active weapon can fire another round now (ammoless models always can). */
	bool HasAmmoToFire() const;

	/** True while the wielder owns the Aiming state (tightens spread; later drives recoil control). */
	bool IsAiming() const;

	/** The chosen hit-delivery strategy CDO for the active ranged weapon (null field -> Hitscan default). */
	const UNexusHitDelivery* ResolveHitDelivery() const;

	/**
	 * Apply per-shot recoil from the effective Stat.Weapon.Recoil* keys to the player's
	 * control rotation (vertical kick + randomized horizontal). Aiming reduces the felt
	 * kick (steady-aim control). Player-only — AI has no camera to perturb.
	 */
	void ApplyRecoil() const;

	class UAnimMontage* PlayMontage(class UAnimMontage* Montage) const;

private:
	/** Rounds left to fire in the current burst (Burst mode only); 0 when not mid-burst. Transient. */
	int32 BurstRemaining = 0;
};