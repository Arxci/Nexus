#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "EMSCustomSaveGame.h"

#include "NexusWorldStateSubsystem.generated.h"


/**
 * Per-save-slot persistence blob for the flat world-state map. Stored through
 * EMS's custom-save system (UEMSObject::SaveCustom), scoped to the current save
 * slot (bUseSaveSlot) so it survives level transitions and is shared across every
 * save room — the same model UNexusItemBoxSaveGame uses for the item box.
 */
UCLASS()
class NEXUS_API UNexusWorldStateSaveGame : public UEMSCustomSaveGame
{
	GENERATED_BODY()

public:
	UNexusWorldStateSaveGame()
	{
		SaveGameName = TEXT("NexusWorldState");
		bUseSaveSlot = true; // one world-state per save slot
	}

	/** The persisted flat key→value facts (a key absent or 0 means "unset"). */
	UPROPERTY()
	TMap<FGameplayTag, int32> States;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWorldStateChanged, FGameplayTag, Key, int32, Value);


/**
 * The saveable, flat key→value store for "has the world changed" facts: a door
 * opened, a lever pulled, a valve turned, a puzzle solved, a one-shot triggered.
 * Interaction conditions READ it (RequiresWorldState) and effects WRITE it
 * (SetWorldState); the quest system can layer on top. One source of truth,
 * persisted per save slot via EMS — the exact pattern the item box uses.
 *
 * A pure leaf: interaction (and quests, later) depend on this; it depends on
 * none of them. A key that has never been set reads as 0.
 */
UCLASS()
class NEXUS_API UNexusWorldStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UNexusWorldStateSubsystem* Get(const UObject* WorldContext);

	/** Current value for Key, or 0 if it has never been set. */
	UFUNCTION(BlueprintPure, Category = "World State")
	int32 GetValue(FGameplayTag Key);

	/** Convenience: GetValue(Key) != 0. */
	UFUNCTION(BlueprintPure, Category = "World State")
	bool GetFlag(FGameplayTag Key);

	/** True if Key has a non-zero value recorded. */
	UFUNCTION(BlueprintPure, Category = "World State")
	bool HasValue(FGameplayTag Key);

	/** Set Key to Value (0 clears it). No-op if unchanged; otherwise persists + broadcasts. */
	UFUNCTION(BlueprintCallable, Category = "World State")
	void SetValue(FGameplayTag Key, int32 Value);

	UFUNCTION(BlueprintCallable, Category = "World State")
	void SetFlag(FGameplayTag Key, bool bValue);

	/** Flip a 0/1 flag (door open↔close) and return the new value. */
	UFUNCTION(BlueprintCallable, Category = "World State")
	int32 ToggleFlag(FGameplayTag Key);

	UPROPERTY(BlueprintAssignable, Category = "World State")
	FOnWorldStateChanged OnWorldStateChanged;

private:
	/** The live map, lazily (re)loaded for the current save slot via EMS. */
	UPROPERTY(Transient)
	TMap<FGameplayTag, int32> States;

	bool bLoaded = false;
	FString LoadedSlotName;

	/** Reload from EMS if the save slot changed since the last access (mirrors the box's EnsureBoxCurrent). */
	void EnsureCurrent();
	FString GetCurrentSlotName() const;
	void Load();
	void Save();
};
