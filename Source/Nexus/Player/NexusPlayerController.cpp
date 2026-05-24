#include "NexusPlayerController.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "NexusPlayerCameraManager.h"
#include "Nexus/Loading/NexusLoadingGateSubsystem.h"
#include "Nexus/Util/NexusUIUtility.h"

ANexusPlayerController::ANexusPlayerController()
{
	PlayerCameraManagerClass = ANexusPlayerCameraManager::StaticClass();
}

void ANexusPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// One-time warm-up of the Common Input key-icon textures. Runs behind the black
	// screen when a startup hold is active; a cheap no-op once the data is resident.
	UNexusUIUtility::PreloadInputBrushes();

	// The loading gate (GameInstance-scoped) owns the black screen + input lock now.
	// A pawn/PC that spawns while a hold is active needs to pick up that state — the
	// gate keeps its ref-counted input flags balanced across this sync.
	const UWorld* World = GetWorld();
	if (UGameInstance* GI = World ? World->GetGameInstance() : nullptr)
	{
		if (UNexusLoadingGateSubsystem* Gate = GI->GetSubsystem<UNexusLoadingGateSubsystem>())
		{
			Gate->SyncPlayerController(this);
		}
	}
}