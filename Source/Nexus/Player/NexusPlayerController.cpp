#include "NexusPlayerController.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "Engine/LocalPlayer.h"

#include "NexusPlayerCameraManager.h"
#include "Nexus/Loading/NexusLoadingGateSubsystem.h"
#include "Nexus/UI/Foundation/NexusUILayoutSubsystem.h"
#include "Nexus/Util/NexusUIUtility.h"
#include "Nexus/Cheats/NexusCheatManager.h"

ANexusPlayerController::ANexusPlayerController()
{
	PlayerCameraManagerClass = ANexusPlayerCameraManager::StaticClass();

	// Dev/QA console commands (Nexus_GiveItem, Nexus_AddCurrency, Nexus_MaxUpgradeEquipped, ...).
	// UCheatManager is only instantiated when cheats are enabled (PIE, or EnableCheats) and is
	// never created in a Shipping build, so this can't reach a shipping player.
	CheatClass = UNexusCheatManager::StaticClass();
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

	// Create the primary UI layout for this local player (no-op on a non-local / AI controller,
	// or if no layout class is configured).
	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UNexusUILayoutSubsystem* UI = UNexusUILayoutSubsystem::Get(LP))
		{
			UI->CreateLayout(this, RootLayoutClass, PanelMap);
		}
	}
}
