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

	int32 GetReserveAmmo() const;
	int32 ConsumeReserveAmmo(int32 Amount) const;

	UFUNCTION()
	void HandleNotifyBegin(const FName NotifyName, const FBranchingPointNotifyPayload& Payload);

private:
	FTimerHandle TimerHandle_ReloadFinish;

	TWeakObjectPtr<UAnimInstance> BoundAnimInstance;

	bool bAmmoTransferred = false;
};