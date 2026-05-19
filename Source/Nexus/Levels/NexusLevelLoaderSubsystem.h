#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "Subsystems/WorldSubsystem.h"

#include "NexusLevelLoaderSubsystem.generated.h"

class UNexusLevelManifest;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNexusLevelLoadComplete);


/**
 * Resolves the active world's UNexusLevelManifest (via ANexusWorldSettings)
 * and preloads the "Equipped" bundle for every item/attachment listed in it.
 * Memory is scoped to the world: leaving the level releases the streamable
 * handle and the bundles become GC-eligible.
 *
 * Canonical Lyra Experience pattern, scaled down: load only what the current
 * gameplay scope can reach, not the full game roster. Memory grows with
 * chapter complexity, not project size.
 *
 * Loading-screen sync: bind OnLoadComplete or poll IsLoadComplete from the
 * player controller / HUD. The delegate fires exactly once per world load,
 * after every manifest entry's Equipped bundle has finished deserialising.
 */
UCLASS()
class NEXUS_API UNexusLevelLoaderSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Levels|Preload")
	bool IsLoadComplete() const { return bLoadComplete; }

	UPROPERTY(BlueprintAssignable, Category = "Levels|Preload")
	FOnNexusLevelLoadComplete OnLoadComplete;

private:
	UNexusLevelManifest* ResolveManifest() const;
	void HandleLoadFinished();

	TSharedPtr<FStreamableHandle> LevelLoadHandle;
	bool bLoadComplete = false;
};