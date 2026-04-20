// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "NexusAbility_Interaction.generated.h"

class UNexusInteractableComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFocusCleared);

UCLASS()
class NEXUS_API UNexusAbility_Interaction : public UNexusAbility
{
	GENERATED_BODY()
	
public:
	/**
	 * Broadcast when the previously focused interactable is destroyed between
	 * frames. No component pointer is provided (it's already dead); listeners
	 * should clear any focus-dependent state (HUD prompts, etc.).
	 */
	UPROPERTY(BlueprintAssignable)
	FOnInteractionFocusCleared OnInteractionFocusCleared;

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
	void ClearAwarenessState();
};
