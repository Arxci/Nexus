#pragma once

#include "CoreMinimal.h"

#include "Engine/TimerHandle.h"

#include "Nexus/Weapon/Abilities/NexusAbility_Weapon.h"
#include "Nexus/Weapon/HitDelivery/NexusHitDelivery.h" // FNexusHitDeliveryResult member

#include "NexusAbility_WeaponMelee.generated.h"

class UNexusHitDelivery;
class UNexusStaminaComponent;
struct FNexusFragment_Weapon;


/**
 * The single, universal melee verb (capability-composed, not a weapon subclass): a
 * knife's primary swing AND a ranged weapon's contextual bash are the same ability,
 * differing only by data + the swing montage. It plays a light / heavy swing, opens a
 * hit window via the swing montage's Melee Hit Window notify-state, sweeps a capsule
 * through the MeleeSweep delivery during that window (single or cleave, de-duped per
 * swing), costs stamina, and ticks durability — breaking (removing) the weapon at zero.
 *
 * Every connecting hit ends in one FNexusDamageContext routed to INexusDamageReceiver,
 * exactly like a gunshot: a knife and a pistol differ by data + a delivery strategy.
 */
UCLASS(Blueprintable)
class NEXUS_API UNexusAbility_WeaponMelee : public UNexusAbility_Weapon
{
	GENERATED_BODY()

public:
	UNexusAbility_WeaponMelee();

	/** Choose the next swing's weight before activating (light by default; heavy costs/hits more). */
	UFUNCTION(BlueprintCallable, Category = "Weapon Ability|Melee")
	void SetHeavyNext(bool bHeavy) { bHeavyNext = bHeavy; }

	/** Opened / closed by the swing montage's Melee Hit Window notify-state (anim-notify-driven timing). */
	void OpenHitWindow();
	void CloseHitWindow();

protected:
	virtual bool RequestActivateAbility() override;
	virtual bool RequestDeactivateAbility(bool bForce) override;
	virtual void CommitAbility() override;
	virtual void CommitAbilityEnd() override;
	virtual bool CanActivateAbility_Implementation() const override;

	virtual float GetCooldownTotalDuration() const override;
	virtual bool  HasCooldown() const override;

	// Sweep runs each tick the hit window is open.
	virtual void TickAbility(float DeltaTime) override;
	virtual bool CanTick() override;

	virtual void OnSaveStateRestored() override;

private:
	void FinishSwing();
	void DoSweep();
	const UNexusHitDelivery* ResolveMeleeDelivery() const;

	UNexusStaminaComponent* GetStamina() const;

	/** Effective melee stamina cost for the pending swing (light, scaled for heavy). */
	float GetSwingStaminaCost(bool bHeavy) const;

	/** Decrement durability for the completed swing; break (remove) the weapon at zero. Returns true if it broke. */
	bool TickDurabilityAndMaybeBreak();

	bool bHeavyNext  = false; // intent for the NEXT activation
	bool bSwingHeavy = false; // weight of the swing currently in progress
	bool bWindowOpen = false;

	/** Per-swing de-dupe accumulator (DamagedActors), reset when the hit window opens. */
	FNexusHitDeliveryResult SwingResult;

	FTimerHandle TimerHandle_SwingEnd;
};
