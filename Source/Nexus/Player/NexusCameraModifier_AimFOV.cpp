// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusCameraModifier_AimFOV.h"

void UNexusCameraModifier_AimFOV::StartBlend(float TargetDelta, float Duration)
{
	StartFOVDelta   = CurrentFOVDelta;
	TargetFOVDelta  = TargetDelta;
	BlendDuration   = FMath::Max(0.0f, Duration);
	BlendElapsed    = 0.0f;
	bBlendActive    = true;

	if (BlendDuration <= 0.0f)
	{
		CurrentFOVDelta = TargetFOVDelta;
		bBlendActive    = false;
	}
}

bool UNexusCameraModifier_AimFOV::ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV)
{
	if (bBlendActive)
	{
		BlendElapsed += DeltaTime;
		// Local name avoids shadowing UCameraModifier::Alpha (C4458 is treated as error in this build).
		const float BlendAlpha = FMath::Clamp(BlendElapsed / BlendDuration, 0.0f, 1.0f);
		CurrentFOVDelta        = FMath::Lerp(StartFOVDelta, TargetFOVDelta, BlendAlpha);
		if (BlendAlpha >= 1.0f)
		{
			CurrentFOVDelta = TargetFOVDelta;
			bBlendActive    = false;
		}
	}

	InOutPOV.FOV += CurrentFOVDelta;
	return false; // false = continue running other modifiers
}