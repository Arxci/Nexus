#pragma once

#include "CoreMinimal.h"

#include "InputCoreTypes.h"

#include "NexusInputRebindFacade.generated.h"

class ULocalPlayer;
class UInputMappingContext;
class UEnhancedInputUserSettings;


/**
 * The single seam through which rebinding touches Enhanced Input User Settings. The
 * settings screen talks only to this facade; no system writes user settings directly.
 * A thin wrapper — register a player-mappable IMC, apply/persist a key, list the
 * mappable names — that no-ops safely when the project hasn't enabled user settings
 * (GetUserSettings() returns null).
 *
 * Owned by UNexusInputManager (one per local player).
 */
UCLASS()
class NEXUS_API UNexusInputRebindFacade : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(ULocalPlayer* InLocalPlayer);

	/** True when Enhanced Input User Settings are available (project setting enabled). */
	UFUNCTION(BlueprintPure, Category = "Input|Rebind")
	bool IsAvailable() const;

	/** Register a context's player-mappable keys with user settings (call once per IMC). */
	UFUNCTION(BlueprintCallable, Category = "Input|Rebind")
	void RegisterContext(const UInputMappingContext* MappingContext);

	/** Rebind the player-mappable mapping named MappingName to NewKey, then apply + persist. */
	UFUNCTION(BlueprintCallable, Category = "Input|Rebind")
	bool ApplyKey(FName MappingName, FKey NewKey);

	/** Every player-mappable mapping name in the current key profile (for a settings list). */
	UFUNCTION(BlueprintPure, Category = "Input|Rebind")
	TArray<FName> ListMappingNames() const;

	/** Apply pending changes and asynchronously persist the settings. */
	UFUNCTION(BlueprintCallable, Category = "Input|Rebind")
	void Save();

private:
	UEnhancedInputUserSettings* GetUserSettings() const;

	UPROPERTY(Transient)
	TWeakObjectPtr<ULocalPlayer> LocalPlayer;
};
