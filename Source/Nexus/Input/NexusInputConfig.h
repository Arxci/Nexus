#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "Nexus/Input/NexusInputTypes.h"

#include "NexusInputConfig.generated.h"


/**
 * A reusable set of tagged bindings, shared across contexts. Optional — a context can
 * inline its own bindings — but a config lets several contexts pull from one authored
 * list (e.g. a shared "weapon verbs" set referenced by both Gameplay and a future
 * Vehicle context). Mirrors Lyra's ULyraInputConfig as a binding-set, with the
 * native/ability split expressed per-row by ActivationStyle instead of two arrays.
 */
UCLASS(BlueprintType)
class NEXUS_API UNexusInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/** The tagged bindings this config contributes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input",
		meta = (TitleProperty = "InputTag"))
	TArray<FNexusTaggedInputAction> Bindings;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
};
