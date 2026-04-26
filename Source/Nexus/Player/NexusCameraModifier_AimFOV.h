// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "NexusCameraModifier_AimFOV.generated.h"

/**
 * Adds a delta to POV.FOV instead of overwriting it, so it composes cleanly
 * with crouch/run/cover modifiers that also adjust FOV. Driven by the weapon
 * aim ability via ANexusPlayerCameraManager::BlendToFOV.
 *
 * Negative TargetFOVDelta = narrower FOV (zooming in for ADS).
 */
UCLASS()
class NEXUS_API UNexusCameraModifier_AimFOV : public UCameraModifier
{
	GENERATED_BODY()

public:
	/**
	 * Blend toward TargetDelta over Duration seconds.
	 * @param TargetDelta Delta added to POV.FOV at the end of the blend.
	 *                    Pass 0 to blend back to neutral (i.e. unaim).
	 */
	void StartBlend(float TargetDelta, float Duration);
	void EndBlend(float Duration) { StartBlend(0.0f, Duration); }

	virtual bool ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV) override;

private:
	float StartFOVDelta    = 0.0f;
	float CurrentFOVDelta  = 0.0f;
	float TargetFOVDelta   = 0.0f;
	float BlendElapsed     = 0.0f;
	float BlendDuration    = 0.0f;
	bool  bBlendActive     = false;
};