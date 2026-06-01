#pragma once

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Nexus/Weapon/Abilities/NexusAbility_Weapon.h"
#include "NexusAbility_WeaponReload.generated.h"

class UAnimMontage;

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

protected:
	void TransferAmmo();
	void FinishReload();

	UFUNCTION()
	void HandleNotifyBegin(const FName NotifyName, const FBranchingPointNotifyPayload& Payload);

private:
	FTimerHandle TimerHandle_ReloadFinish;

	TWeakObjectPtr<UAnimInstance> BoundAnimInstance;

	/**
	 * The specific montage we asked to play at reload start. The
	 * OnPlayMontageNotifyBegin delegate fires for any notify on any montage
	 * playing on the bound AnimInstance, so we additionally verify that the
	 * triggering montage is still our reload before consuming reserve ammo.
	 */
	TWeakObjectPtr<UAnimMontage> BoundReloadMontage;

	bool bAmmoTransferred = false;
};