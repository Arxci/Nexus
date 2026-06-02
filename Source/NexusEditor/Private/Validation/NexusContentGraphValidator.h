#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"
#include "NexusContentGraphValidator.generated.h"

/**
 * Cross-asset validator for the content graph — the checks a single asset's
 * IsDataValid can't make because they depend on every OTHER asset:
 *
 *   - an item / attachment whose IdentityTag collides with another asset's, and
 *   - an attachment whose RequiredTags name a prerequisite no attachment provides.
 *
 * The editor's validation subsystem discovers UEditorValidatorBase subclasses by
 * reflection, so simply shipping this class in a loaded editor module wires it
 * into right-click "Validate Assets", validate-on-save, and the cook-time check —
 * no manual registration. The heavy lifting lives in FNexusContentAudit so the
 * dashboard and this validator stay in agreement.
 *
 * NOTE ON ENGINE VERSION: these are the UE 5.4+ signatures (FAssetData + context).
 * On UE 5.3 and earlier the overrides are instead:
 *     bool CanValidateAsset_Implementation(UObject* InAsset) const;
 *     EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors);
 * and AssetFails takes a trailing TArray<FText>&. Adjust the two overrides if you
 * see a "marked override but does not override" error on build.
 */
UCLASS()
class UNexusContentGraphValidator : public UEditorValidatorBase
{
	GENERATED_BODY()

protected:
	virtual bool CanValidateAsset_Implementation(
		const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;

	virtual EDataValidationResult ValidateLoadedAsset_Implementation(
		const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;
};
