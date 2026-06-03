#include "Validation/NexusNamingValidator.h"

#include "Misc/DataValidation.h"
#include "Misc/PackageName.h"
#include "UObject/Package.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Equipment/NexusEquipmentLoadout.h"

#define LOCTEXT_NAMESPACE "NexusNamingValidator"

namespace
{
	bool IsNexusAuthoredAsset(const UObject* Asset)
	{
		return Asset
			&& (Asset->IsA<UNexusItemDefinition>()
			 || Asset->IsA<UNexusAttachmentDefinition>()
			 || Asset->IsA<UNexusCombinationRecipe>()
			 || Asset->IsA<UNexusLevelManifest>()
			 || Asset->IsA<UNexusEquipmentLoadout>());
	}

	/** Only [A-Za-z0-9_] is path-safe across every platform / source-control system. */
	bool HasUnsafeNameChars(const FString& Name)
	{
		for (const TCHAR Ch : Name)
		{
			if (!FChar::IsAlnum(Ch) && Ch != TEXT('_'))
			{
				return true;
			}
		}
		return false;
	}
}

bool UNexusNamingValidator::CanValidateAsset_Implementation(
	const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const
{
	return IsNexusAuthoredAsset(InAsset);
}

EDataValidationResult UNexusNamingValidator::ValidateLoadedAsset_Implementation(
	const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext)
{
	if (!IsNexusAuthoredAsset(InAsset))
	{
		return EDataValidationResult::NotValidated;
	}

	const FString Name = InAsset->GetName();
	if (HasUnsafeNameChars(Name))
	{
		InContext.AddWarning(FText::FromString(FString::Printf(
			TEXT("'%s' has characters outside [A-Za-z0-9_]. Rename it to stay path-safe across platforms and source control."),
			*Name)));
	}

	// A data asset directly under /Game (no subfolder) is clutter most studios avoid.
	const FString PackageName = InAsset->GetPackage() ? InAsset->GetPackage()->GetName() : FString();
	const FString PackagePath = FPackageName::GetLongPackagePath(PackageName); // e.g. /Game/Nexus/Weapons
	if (PackagePath.Equals(TEXT("/Game")))
	{
		InContext.AddWarning(FText::FromString(FString::Printf(
			TEXT("'%s' is saved directly in /Game. Move it into a subfolder (e.g. /Game/Nexus/...)."),
			*Name)));
	}

	// Warnings only — never fail the build/cook on a naming nit.
	AssetPasses(InAsset);
	return EDataValidationResult::Valid;
}

#undef LOCTEXT_NAMESPACE
