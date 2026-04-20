// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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
	void TryStartInteraction();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void TryStopInteraction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnEnteredPlayerRange();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnLeftPlayerRange();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnGainedPlayerFocus();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnLostPlayerFocus();
};
