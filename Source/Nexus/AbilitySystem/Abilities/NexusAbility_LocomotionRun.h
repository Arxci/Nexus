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
	
	virtual void OnActivateAbility() override;
	virtual void OnDeactivateAbility() override;
	virtual void TickAbility(float DeltaTime) override;
	
private:
	bool bIsBoostActive = false;

	bool ShouldBoostThisFrame() const;
	void SetBoostActive(bool bNewActive);
};