// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusPlayerCameraManager.h"
#include "GameFramework/Character.h"

ANexusPlayerCameraManager::ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
{
	ViewPitchMin = -80.0f;
	ViewPitchMax = 80.0f;
	DefaultFOV = 70.0f;
}

void ANexusPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);


}