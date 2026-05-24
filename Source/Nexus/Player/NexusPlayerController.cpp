#include "NexusPlayerController.h"

#include "Engine/World.h"

#include "NexusPlayerCameraManager.h"
#include "Nexus/Util/NexusUIUtility.h"
#include "Nexus/Levels/NexusLevelLoaderSubsystem.h"

ANexusPlayerController::ANexusPlayerController()
{
	PlayerCameraManagerClass = ANexusPlayerCameraManager::StaticClass();
}

void ANexusPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UNexusLevelLoaderSubsystem* Sub = GetWorld() ? GetWorld()->GetSubsystem<UNexusLevelLoaderSubsystem>() : nullptr;
	if (!Sub || Sub->IsPersistentLoadComplete())
	{
		return; // manifest already resident (warm run / no subsystem) — nothing to gate
	}

	// The pawn now spawns normally, so it exists and is possessed during the manifest
	// load hitch. Hold solid black and freeze look/move so the player can't look
	// around or move while the frame rate tanks — the reason the spawn used to be
	// deferred, but without the deferral's lifecycle fragility. Revealed in
	// HandleManifestLoadComplete.
	if (PlayerCameraManager)
	{
		PlayerCameraManager->StartCameraFade(1.f, 1.f, 0.01f, FLinearColor::Black, /*bFadeAudio*/ false, /*bHoldWhenFinished*/ true);
	}
	UNexusUIUtility::PreloadInputBrushes();
	
	SetIgnoreLookInput(true);
	SetIgnoreMoveInput(true);

	FOnNexusPersistentLoadCallback Cb;
	Cb.BindDynamic(this, &ANexusPlayerController::HandleManifestLoadComplete);
	Sub->CallOrRegisterOnPersistentLoadComplete(Cb);
}

void ANexusPlayerController::HandleManifestLoadComplete()
{
	// Clear exactly the holds we set (these flags are ref-counted).
	SetIgnoreLookInput(false);
	SetIgnoreMoveInput(false);

	if (PlayerCameraManager)
	{
		PlayerCameraManager->StartCameraFade(1.f, 0.f, 0.6f, FLinearColor::Black, /*bFadeAudio*/ true, /*bHoldWhenFinished*/ false);
	}
	
}