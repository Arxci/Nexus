// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NexusInteractableInterface.generated.h"


UINTERFACE(MinimalAPI)
class UNexusInteractableInterface : public UInterface
{
	GENERATED_BODY()
};


class NEXUS_API INexusInteractableInterface
{
	GENERATED_BODY()


protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void TryStartInteraction();
	virtual void TryStartInteraction_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void TryStopInteraction();
	virtual void TryStopInteraction_Implementation();
};
