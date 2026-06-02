#include "NexusLevelManifest.h"

#include "Nexus/NexusAssetManager.h"

FPrimaryAssetId UNexusLevelManifest::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UNexusAssetManager::TypeLevelManifest, GetFName());
}

#if WITH_EDITOR

#include "Misc/DataValidation.h"

EDataValidationResult UNexusLevelManifest::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	// Empty rows preload nothing; they're almost always a half-added entry the author
	// meant to fill in. Flag both lists so the manifest stays an accurate residency set.
	for (int32 Index = 0; Index < Items.Num(); ++Index)
	{
		if (Items[Index].IsNull())
		{
			Context.AddError(FText::FromString(FString::Printf(TEXT("Items[%d] is an empty reference."), Index)));
			Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		}
	}
	for (int32 Index = 0; Index < Attachments.Num(); ++Index)
	{
		if (Attachments[Index].IsNull())
		{
			Context.AddError(FText::FromString(FString::Printf(TEXT("Attachments[%d] is an empty reference."), Index)));
			Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		}
	}

	return Result;
}

#endif // WITH_EDITOR
