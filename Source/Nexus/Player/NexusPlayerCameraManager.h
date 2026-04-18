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

	void StartCameraFadeWithHold(const float InFadeTime, const float HoldTime, const float OutFadeTime, const FLinearColor InFadeColor, const bool bInFadeAudio);

private:
	UFUNCTION()
	void CameraFadeHoldEnd(const float OutFadeTime, const FLinearColor InFadeColor, const bool bInFadeAudio);

	FTimerHandle CameraFadeHandle;
	FTimerDelegate OnCameraFadeCompleted;
};

