#include "NexusPlayerCameraManager.h"

#include "GameFramework/PlayerController.h"

ANexusPlayerCameraManager::ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ViewPitchMin = -80.0f;
	ViewPitchMax = 80.0f;
	DefaultFOV   = 70.0f;
}

void ANexusPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void ANexusPlayerCameraManager::StartCameraFadeWithDelay(const float FromAlpha, const float ToAlpha, const float InFadeTime, const float InDelayTime, const FLinearColor InFadeColor, const bool bInFadeAudio, const bool bInHoldWhenFinished)
{
	GetWorldTimerManager().SetTimer(CameraFadeDelayHandle, FTimerDelegate::CreateLambda([this, FromAlpha, ToAlpha, InFadeTime, InFadeColor, bInFadeAudio, bInHoldWhenFinished]()
	{
		StartCameraFade(FromAlpha, ToAlpha, InFadeTime, InFadeColor, bInFadeAudio, bInHoldWhenFinished);
	}), InDelayTime, false);
}