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
	
	virtual bool RequestActivateAbility() override;
	virtual bool RequestDeactivateAbility(bool bForce) override;
	virtual void ForceEndAbility() override;
	
	virtual void TickAbility(float DeltaTime) override;
	virtual bool CanTick() override;

	float BoostThreshold = 0.2f;
	
	// Save/Restore
	virtual void CaptureSaveState(FNexusAbilitySaveData& OutData) const override;
	virtual void OnSaveStateRestored() override;
	
private:
	bool CanCharacterRun() const;
	bool CanCharacterWalk() const;
};