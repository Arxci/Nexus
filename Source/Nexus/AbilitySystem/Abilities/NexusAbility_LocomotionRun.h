// NexusAbility_Run.h
#pragma once

#include "CoreMinimal.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "NexusAbility_LocomotionRun.generated.h"

UCLASS(Blueprintable)
class NEXUS_API UNexusAbility_LocomotionRun : public UNexusAbility
{
	GENERATED_BODY()

protected:
	UNexusAbility_LocomotionRun();
	
	virtual bool OnRequestActivateAbility() override;
	virtual bool OnRequestDeactivateAbility(bool bForce) override;
	virtual void HandleAbilityStart() override;
	virtual void HandleAbilityStop() override;
	virtual void HandleAbilityProgress() override;

	float BoostThreshold = 0.2f;
	
private:
	bool bIsBoostActive = false;
	
	bool ShouldBoostThisFrame() const;
	void SetBoostActive(bool bNewActive);
};