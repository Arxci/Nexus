#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "NexusInputUserOptions.generated.h"


/**
 * Per-player input preferences that persist independently of the gameplay save — the
 * per-verb hold/toggle choice (Aim / Run / Crouch) and the repeated-input-as-hold
 * accessibility option. A global preference slot (GameUserSettings ini), so it survives
 * across save files, matching how rebindings persist. Keyed by verb tag name.
 *
 * Stored as a config object rather than threaded through the gameplay save; the manager
 * mirrors it into its runtime override maps and writes back on change.
 */
UCLASS(config = GameUserSettings, defaultconfig)
class NEXUS_API UNexusInputUserOptions : public UObject
{
	GENERATED_BODY()

public:
	/** The shared config instance (the CDO; config auto-loads at startup). */
	static UNexusInputUserOptions* Get();

	/** Verb tag name -> ENexusHoldToggleMode (stored as uint8 for config robustness). */
	UPROPERTY(config)
	TMap<FName, uint8> VerbHoldToggleModes;

	/** Verb tag name -> repeated-input-as-hold enabled. */
	UPROPERTY(config)
	TMap<FName, bool> VerbRepeatedAsHold;
};
