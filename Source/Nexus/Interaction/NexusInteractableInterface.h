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


protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	void TryStartInteraction();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	void TryStopInteraction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	void OnEnteredPlayerRange();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	void OnLeftPlayerRange();
};
