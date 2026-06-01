// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "Nexus/Interaction/NexusInteraction.h"

#include "NexusInteractableInterface.generated.h"


UINTERFACE(MinimalAPI, BlueprintType)
class UNexusInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class NEXUS_API INexusInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void TryStartInteraction(AActor* Interactor);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void TryStopInteraction(AActor* Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnEnteredPlayerRange();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnLeftPlayerRange();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnGainedPlayerFocus();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnLostPlayerFocus();

	/**
	 * Query the interactions this object offers a given interactor and whether
	 * each is currently enabled (with a fail reason when not). The HUD / ability
	 * read this to resolve the prompt — verb, hold-vs-tap, gate reason — without
	 * the interactable pushing any UI. Host-agnostic: the Interactor is any actor.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void GetAvailableInteractions(AActor* Interactor, TArray<FNexusResolvedInteraction>& OutInteractions);
};
