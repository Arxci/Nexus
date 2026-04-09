// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusPlayerCameraManager.h"

ANexusPlayerCameraManager::ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
{
	ViewPitchMin = -89.0f;
	ViewPitchMax = 89.0f;
	
	DefaultFOV = 80.0f;
}

void ANexusPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);


}