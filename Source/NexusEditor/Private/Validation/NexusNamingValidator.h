#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "NexusNamingValidator.generated.h"

/**
 * Content-hygiene validator for the Nexus data-asset types — the pipeline-discipline
 * checks AAA studios gate merges on, kept deliberately non-prescriptive so it never
 * fights your existing names:
 *
 *   - asset names with spaces or characters outside [A-Za-z0-9_] (warning) — these
 *     trip up some source-control / cooker / platform paths,
 *   - data assets sitting loose directly under /Game with no subfolder (warning).
 *
 * Everything is a WARNING, so it annotates without failing the build or cook (unlike
 * the cross-asset UNexusContentGraphValidator, which errors on broken content). Like
 * that validator, it's discovered by reflection — shipping the class in the loaded
 * editor module is the whole registration.
 *
 * Uses the UE 5.4+ validator signatures (FAssetData + context), matching
 * UNexusContentGraphValidator; see that file's header note for the 5.3-and-earlier form.
 */
UCLASS()
class UNexusNamingValidator : public UEditorValidatorBase
{
	GENERATED_BODY()

protected:
	virtual bool CanValidateAsset_Implementation(
		const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;

	virtual EDataValidationResult ValidateLoadedAsset_Implementation(
		const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;
};
