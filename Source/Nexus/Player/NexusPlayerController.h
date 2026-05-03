// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EMSActorSaveInterface.h"

#include "GameFramework/PlayerController.h"

#include "NexusPlayerController.generated.h"


UCLASS()
class NEXUS_API ANexusPlayerController : public APlayerController, public IEMSActorSaveInterface
{
	GENERATED_BODY()

public:
	ANexusPlayerController();
};
