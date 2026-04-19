// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "NexusAbility_Interaction.generated.h"


UCLASS()
class NEXUS_API UNexusAbility_Interaction : public UNexusAbility
{
	GENERATED_BODY()

protected:
	UNexusAbility_Interaction();

	virtual void TickAbility(float DeltaTime) override;
	virtual bool CanTick() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionTraceDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionRadius;
	

private:
	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> NearbyInteractables;

	void UpdateNearbyInteractables();
};
