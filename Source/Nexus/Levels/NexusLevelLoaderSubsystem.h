#pragma once

#include "CoreMinimal.h"

#include "Engine/LevelStreaming.h"
#include "Engine/StreamableManager.h"

#include "Subsystems/WorldSubsystem.h"

#include "NexusLevelLoaderSubsystem.generated.h"

class ULevelStreaming;
class UNexusLevelManifest;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNexusLevelLoadComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNexusSubLevelLoaded, ULevelStreaming*, StreamingLevel);
DECLARE_DYNAMIC_DELEGATE(FOnNexusPersistentLoadCallback);


UCLASS()
class NEXUS_API UNexusLevelLoaderSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Levels|Preload")
	bool IsPersistentLoadComplete() const { return bPersistentLoadComplete; }

	UPROPERTY(BlueprintAssignable, Category = "Levels|Preload")
	FOnNexusLevelLoadComplete OnPersistentLoadComplete;

	/**
	 * Lyra-style "call now if already complete, otherwise register and fire on
	 * completion." Use this from UMG widgets / player controllers that might
	 * spawn after the persistent load has already finished — the multicast
	 * above won't fire for late binders.
	 */
	UFUNCTION(BlueprintCallable, Category = "Levels|Preload",
		meta = (AutoCreateRefTerm = "Callback"))
	void CallOrRegisterOnPersistentLoadComplete(const FOnNexusPersistentLoadCallback& Callback);

	UFUNCTION(BlueprintPure, Category = "Levels|Preload")
	bool IsSubLevelLoaded(const ULevelStreaming* StreamingLevel) const;

	/** Fires when a specific sub-level's bundle finishes loading. */
	UPROPERTY(BlueprintAssignable, Category = "Levels|Preload")
	FOnNexusSubLevelLoaded OnSubLevelLoaded;

private:
	void LoadPersistentManifest();
	void MarkPersistentLoadComplete();

	void HandleLevelStreamingStateChanged(
		UWorld* StreamingWorld,
		const ULevelStreaming* StreamingLevel,
		ULevel* LevelIfLoaded,
		ELevelStreamingState PreviousState,
		ELevelStreamingState NewState);

	void LoadManifestForSubLevel(const ULevelStreaming* StreamingLevel, ULevel* Level);
	void ReleaseManifestForSubLevel(const ULevelStreaming* StreamingLevel);

	/**
	 * Walk SubLevelHandles and drop any entry whose ULevelStreaming has been
	 * GC'd. Defensive against ReleaseManifestForSubLevel never being called
	 * (engine never fires the state-change event during a hard world teardown,
	 * PIE shutdown, or programmatic RemoveFromWorld).
	 */
	void PruneStaleSubLevelHandles();

	TSharedPtr<FStreamableHandle> PersistentHandle;
	bool bPersistentLoadComplete = false;

	/** True while we hold the loading gate for the persistent manifest load. */
	bool bGateHeldForPersistentLoad = false;

	/** Callbacks waiting on the persistent load. Drained when it completes. */
	TArray<FOnNexusPersistentLoadCallback> PendingPersistentLoadCallbacks;

	TMap<TWeakObjectPtr<const ULevelStreaming>, TSharedPtr<FStreamableHandle>> SubLevelHandles;

	FDelegateHandle StreamingStateHandle;
};