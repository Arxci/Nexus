// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusPlayerCameraManager.h"
#include "GameFramework/Character.h"

ANexusPlayerCameraManager::ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ViewPitchMin = -80.0f;
	ViewPitchMax = 80.0f;
	DefaultFOV = 70.0f;
}

void ANexusPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
}

void ANexusPlayerCameraManager::StartCameraFadeWithHold(const float InFadeTime, const float HoldTime, const float OutFadeTime, const FLinearColor InFadeColor, const bool bInFadeAudio)
{
	OnCameraFadeCompleted.BindUFunction(this, FName("CameraFadeHoldEnd"), OutFadeTime, InFadeColor, bInFadeAudio);

	StartCameraFade(0, 1, InFadeTime, InFadeColor,bInFadeAudio, true);
	
	GetWorldTimerManager().SetTimer(CameraFadeHandle, OnCameraFadeCompleted, HoldTime, false);
}

void ANexusPlayerCameraManager::CameraFadeHoldEnd(const float OutFadeTime, const FLinearColor InFadeColor, const bool bInFadeAudio)
{
	OnCameraFadeCompleted.Unbind();

	StartCameraFade(1, 0, OutFadeTime, InFadeColor,bInFadeAudio, true);
}