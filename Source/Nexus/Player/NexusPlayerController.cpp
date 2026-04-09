// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusPlayerController.h"
#include "NexusPlayerCameraManager.h"

ANexusPlayerController::ANexusPlayerController()
{
	PlayerCameraManagerClass = ANexusPlayerCameraManager::StaticClass();
}