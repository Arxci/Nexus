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
	virtual void OnActivateAbility() override;
	virtual void OnDeactivateAbility() override;
	virtual bool CanActivateAbility_Implementation() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Locomotion")
	float SprintSpeed = 600.0f;

private:
	float CachedWalkSpeed = 0.0f;
};