#pragma once

#include "CoreMinimal.h"

#include "GameFramework/WorldSettings.h"

#include "NexusWorldSettings.generated.h"

class UNexusLevelManifest;


/**
 * Per-level settings carrier. The one field that matters is LevelManifest —
 * a hard reference so UNexusLevelLoaderSubsystem can read it the moment
 * OnWorldBeginPlay fires (no async needed for the manifest itself; the heavy
 * payload is the items it references).
 *
 * Activated via DefaultEngine.ini ([/Script/Engine.Engine] WorldSettingsClass).
 * Once active, each level shows a "Level Manifest" property in its World
 * Settings panel.
 */
UCLASS()
class NEXUS_API ANexusWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Nexus")
	TObjectPtr<UNexusLevelManifest> LevelManifest;
};