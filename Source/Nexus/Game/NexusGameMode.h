#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "NexusGameMode.generated.h"


/**
 * Project game mode. The pawn spawns normally (no deferral) so its lifecycle is
 * deterministic — BeginPlay always runs after possession, which keeps possession-
 * dependent setup (first-person rendering, ability grants) correct.
 *
 * The reason the spawn used to be deferred — stopping the player from looking
 * around / moving while the persistent-manifest load hitches the frame rate — is
 * now handled on the controller (black screen + frozen input until the load
 * completes); see ANexusPlayerController. Gating readiness there, rather than
 * withholding the pawn, gives the same player-facing result without making the
 * pawn spawn late (which ran BeginPlay before possession and left equipped actors
 * rendering in the wrong viewpoint).
 */
UCLASS()
class NEXUS_API ANexusGameMode : public AGameModeBase
{
	GENERATED_BODY()
};