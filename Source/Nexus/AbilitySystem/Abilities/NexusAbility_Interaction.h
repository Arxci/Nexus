// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "NexusAbility_Interaction.generated.h"

class UNexusInteractableComponent;
static TAutoConsoleVariable CVarShowInteractionFocusReach(
	TEXT("nexus.Interaction.Show.FocusReach"), 
	0,                               
	TEXT("0: Hide Interaction Show Focus Reach\n1: Show Interaction Show Focus Reach"), 
	ECVF_Cheat                       
);

static TAutoConsoleVariable CVarShowInteractionAwareness(
	TEXT("nexus.Interaction.Show.Awareness"), 
	0,                               
	TEXT("0: Hide Interaction Show Awareness\n1: Show Interaction Show Awareness"), 
	ECVF_Cheat                       
);

static TAutoConsoleVariable CVarAwarenessRadiusOverride(
	TEXT("nexus.Interaction.AwarenessRadiusOverride"),
	-1.0f, 
	TEXT("Override the proximity detection radius. Set to -1 to use default."),
	ECVF_Cheat
);

static TAutoConsoleVariable CVarFocusReachOverride(
	TEXT("nexus.Interaction.FocusReachOverride"),
	-1.0f, 
	TEXT("Override the focus reach distance. Set to -1 to use default."),
	ECVF_Cheat
);

UCLASS()
class NEXUS_API UNexusAbility_Interaction : public UNexusAbility
{
	GENERATED_BODY()

protected:
	UNexusAbility_Interaction();

	virtual void OnDisableAbility() override;
	virtual void OnEnableAbility() override;

	virtual void InitializeAbility() override;
	virtual void TickAbility(float DeltaTime) override;
	virtual bool CanTick() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FocusReachDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AwarenessRadius;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AwarenessUpdateInterval;

	FTimerHandle TimerHandle_UpdateInteractables;

private:
	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> NearbyInteractables;

	UPROPERTY()
	TWeakObjectPtr<UNexusInteractableComponent> InteractionTarget;

	void TraceForInteractables();
	void UpdateInteractionTarget(UNexusInteractableComponent* NewInteractionTarget);
	void UpdateNearbyInteractables();
	void StartAwarenessTimer();
};
