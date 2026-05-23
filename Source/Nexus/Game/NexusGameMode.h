#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "NexusGameMode.generated.h"


/**
 * Gates player pawn spawning on the level loader subsystem's persistent
 * manifest load. Until OnPersistentLoadComplete fires, incoming PlayerControllers
 * are stashed without calling Super::HandleStartingNewPlayer, so RestartPlayer
 * never runs and no pawn is spawned. Once the load completes, every stashed
 * controller is drained through Super, which spawns their pawns normally.
 */
UCLASS()
class NEXUS_API ANexusGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:
	UFUNCTION()
	void HandlePersistentLoadComplete();

	UPROPERTY()
	TArray<TObjectPtr<APlayerController>> PendingPlayers;

	bool bPersistentLoadComplete = false;
};