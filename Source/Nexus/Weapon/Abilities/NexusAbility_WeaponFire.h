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
	virtual bool RequestDeactivateAbility(bool bForce) override;
	virtual void CommitAbility() override;
	virtual void CommitAbilityEnd() override;
	virtual bool CanActivateAbility_Implementation() const override;

	virtual float GetCooldownTotalDuration() const override;
	virtual bool  HasCooldown() const override;

	virtual bool CanTick() override { return IsActive(); }
	virtual void TickAbility(float DeltaTime) override;

	void FireShot();
	void FireOnePellet(const FVector& ViewLoc, const FRotator& ViewRot);
	class UAnimMontage* PlayMontageSafe(const TSoftObjectPtr<UAnimMontage>& Soft) const;
	void HandleDryFire();

	FVector ConsumeRecoilImpulse();

	/** True if the player is still holding the fire input (intent tag on the ASC). */
	bool IsFireIntentHeld() const;

	/** True if reload/aim/etc. tags forbid firing right now. */
	bool IsBlockedByOwnedTags() const;

private:
	// Recoil pattern state — transient, intentionally not SaveGame.
	float LastFireTime = -1000.0f;
	int32 ShotIndex    = 0;

	/** Shots remaining in the current burst (FireMode::Burst only). */
	int32 BurstShotsRemaining = 0;
};