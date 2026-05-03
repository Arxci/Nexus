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
	virtual bool CanActivateAbility_Implementation() const override;

	virtual float GetCooldownTotalDuration() const override;
	virtual bool  HasCooldown() const override;

protected:
	void FireShot() const;
	void FireOnePellet(const FVector& ViewLoc, const FRotator& ViewRot) const;
	void HandleDryFire() const;

	class UAnimMontage* PlayMontage(class UAnimMontage* Montage) const;
};