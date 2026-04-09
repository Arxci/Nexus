// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "NexusPlayerCameraManager.generated.h"


UCLASS()
class NEXUS_API ANexusPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	virtual void UpdateCamera(float DeltaTime) override;
};
