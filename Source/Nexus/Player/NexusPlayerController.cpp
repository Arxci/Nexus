#include "NexusPlayerController.h"

#include "NexusPlayerCameraManager.h"

ANexusPlayerController::ANexusPlayerController()
{
	PlayerCameraManagerClass = ANexusPlayerCameraManager::StaticClass();
}