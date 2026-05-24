#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "NexusLoadingGateSubsystem.generated.h"

class AActor;
class APlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNexusLoadingStateChanged, bool, bIsLoading);

/**
 * Ref-counted "hold the loading screen" authority, at GameInstance scope so it
 * survives level travel and is reachable from any system.
 *
 * Anything that needs to hide the world and block input while it finishes async
 * work pushes a named hold; the screen (camera fade to black + input suppression
 * on the local player) stays up until every hold is popped. This lets independent
 * sources — the level manifest preload, a save-game load, future sub-level
 * streaming — compose without fighting over the camera fade.
 *
 * Presentation is intentionally just the fade + input lock today. Bind
 * OnLoadingStateChanged from a UMG widget if you want a spinner / progress bar.
 */
UCLASS()
class NEXUS_API UNexusLoadingGateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Deinitialize() override;

	/** Add a hold under Reason. Ref-counted: N pushes require N pops. Shows the screen on the first hold. */
	UFUNCTION(BlueprintCallable, Category = "Loading")
	void PushHold(FName Reason);

	/** Remove one hold under Reason. Reveals the world once the last hold of any reason is gone. */
	UFUNCTION(BlueprintCallable, Category = "Loading")
	void PopHold(FName Reason);

	UFUNCTION(BlueprintPure, Category = "Loading")
	bool IsLoading() const { return Holds.Num() > 0; }

	/**
	 * Convenience for the save system: pushes a "SaveLoad" hold now and auto-pops it
	 * when EasyMultiSave finishes restoring level actors (UEMSObject::OnLevelLoaded).
	 * Call this right before you kick off an EMS load. If the load can fail without
	 * firing OnLevelLoaded, use the manual PushHold/PopHold pair instead so you can
	 * pop on your own failure path.
	 */
	UFUNCTION(BlueprintCallable, Category = "Loading")
	void HoldForSaveLoad();

	/** Re-apply the current screen state to a player controller. Call from its BeginPlay. */
	void SyncPlayerController(APlayerController* PC);

	UPROPERTY(BlueprintAssignable, Category = "Loading")
	FOnNexusLoadingStateChanged OnLoadingStateChanged;

private:
	void ApplyPresentation();
	void ApplyToPlayerController(APlayerController* PC);

	UFUNCTION()
	void HandleSaveLoadComplete(const TArray<TSoftObjectPtr<AActor>>& LoadedActors);

	/** Reason -> active hold count. An entry only exists while its count is > 0. */
	TMap<FName, int32> Holds;

	// Tracks what we last pushed onto the current PC so the engine's ref-counted
	// input-ignore flags stay balanced (one set on show, one clear on reveal) even
	// when the PC is synced multiple times or swapped across a travel.
	enum class EApplied : uint8 { None, Shown, Revealed };
	EApplied AppliedState = EApplied::None;
	TWeakObjectPtr<APlayerController> AppliedPC;

	bool bSaveLoadBound = false;
};