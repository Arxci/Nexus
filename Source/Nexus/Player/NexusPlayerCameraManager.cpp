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

void ANexusPlayerCameraManager::StartCameraFadeWithDelay(const float FromAlpha, const float ToAlpha, const float InFadeTime, const float InDelayTime, const FLinearColor InFadeColor, const bool bInFadeAudio, const bool bInHoldWhenFinished)
{
	GetWorldTimerManager().SetTimer(CameraFadeDelayHandle, FTimerDelegate::CreateLambda([this, FromAlpha, ToAlpha, InFadeTime, InFadeColor, bInFadeAudio, bInHoldWhenFinished]()
	{
		StartCameraFade(FromAlpha, ToAlpha, InFadeTime, InFadeColor,bInFadeAudio, bInHoldWhenFinished);
	}), InDelayTime, false);
}