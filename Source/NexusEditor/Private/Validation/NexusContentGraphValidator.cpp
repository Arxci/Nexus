#include "Validation/NexusContentGraphValidator.h"

#include "Audit/NexusContentAudit.h"
#include "Misc/DataValidation.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

#define LOCTEXT_NAMESPACE "NexusContentGraphValidator"

bool UNexusContentGraphValidator::CanValidateAsset_Implementation(
	const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const
{
	return InAsset != nullptr
		&& (InAsset->IsA<UNexusItemDefinition>() || InAsset->IsA<UNexusAttachmentDefinition>());
}

EDataValidationResult UNexusContentGraphValidator::ValidateLoadedAsset_Implementation(
	const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext)
{
	if (const UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(InAsset))
	{
		const TArray<UNexusItemDefinition*> Others = FNexusContentAudit::FindItemsSharingIdentity(Item);
		if (Others.Num() > 0)
		{
			TArray<FString> Names;
			for (const UNexusItemDefinition* Other : Others)
			{
				Names.Add(Other->GetName());
			}

			AssetFails(InAsset, FText::FromString(FString::Printf(
				TEXT("Identity tag %s is also used by: %s. Identity tags must be unique across items."),
				*Item->IdentityTag.ToString(), *FString::Join(Names, TEXT(", ")))));
			return EDataValidationResult::Invalid;
		}

		AssetPasses(InAsset);
		return EDataValidationResult::Valid;
	}

	if (const UNexusAttachmentDefinition* Attachment = Cast<UNexusAttachmentDefinition>(InAsset))
	{
		const FGameplayTagContainer GlobalProvided = FNexusContentAudit::GatherGlobalProvidedTags();
		const FGameplayTagContainer Missing = FNexusContentAudit::GetUnsatisfiedRequirements(Attachment, GlobalProvided);
		if (!Missing.IsEmpty())
		{
			AssetFails(InAsset, FText::FromString(FString::Printf(
				TEXT("Requires %s, which no attachment in the project provides — it could never be installed."),
				*Missing.ToStringSimple())));
			return EDataValidationResult::Invalid;
		}

		AssetPasses(InAsset);
		return EDataValidationResult::Valid;
	}

	return EDataValidationResult::NotValidated;
}

#undef LOCTEXT_NAMESPACE
