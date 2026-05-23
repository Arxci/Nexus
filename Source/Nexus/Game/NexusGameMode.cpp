#include "NexusGameMode.h"

#include "Engine/World.h"

#include "GameFramework/PlayerController.h"

#include "Nexus/Levels/NexusLevelLoaderSubsystem.h"

void ANexusGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UNexusLevelLoaderSubsystem* Sub = GetWorld() ? GetWorld()->GetSubsystem<UNexusLevelLoaderSubsystem>() : nullptr;
	if (!Sub)
	{
		// No subsystem — fail open so we don't strand the player.
		bPersistentLoadComplete = true;
		return;
	}

	if (Sub->IsPersistentLoadComplete())
	{
		bPersistentLoadComplete = true;
		return;
	}

	Sub->OnPersistentLoadComplete.AddDynamic(this, &ANexusGameMode::HandlePersistentLoadComplete);
}

void ANexusGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (bPersistentLoadComplete)
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
		return;
	}

	// Defer: do NOT call Super. RestartPlayer therefore never runs and no
	// pawn is spawned for this controller. The controller exists, but it has
	// no pawn — so no character ticks, no input target, no camera attached
	// to a pawn. HandlePersistentLoadComplete drains the list when the load
	// finishes and Super:: is finally called for each.
	PendingPlayers.AddUnique(NewPlayer);
}

void ANexusGameMode::HandlePersistentLoadComplete()
{
	if (bPersistentLoadComplete) return;
	bPersistentLoadComplete = true;

	// Move-swap so a re-entrant call from inside Super doesn't iterate the
	// same array we're appending to.
	TArray<TObjectPtr<APlayerController>> Drain = MoveTemp(PendingPlayers);
	for (APlayerController* PC : Drain)
	{
		if (IsValid(PC))
		{
			Super::HandleStartingNewPlayer_Implementation(PC);
		}
	}
}