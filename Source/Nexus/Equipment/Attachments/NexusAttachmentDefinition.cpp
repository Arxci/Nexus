#include "NexusAttachmentDefinition.h"

#include "Nexus/NexusAssetManager.h"

#if WITH_EDITOR
#include "Nexus/Validation/NexusDataValidation.h"
#endif

FPrimaryAssetId UNexusAttachmentDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UNexusAssetManager::TypeAttachmentDefinition, GetFName());
}

#if WITH_EDITOR

EDataValidationResult UNexusAttachmentDefinition::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	NexusDataValidation::RequireTag (Context, Result, IdentityTag, TEXT("Identity Tag"));
	NexusDataValidation::RequireText(Context, Result, DisplayName, TEXT("Display Name"));
	NexusDataValidation::WarnIfUnset(Context, Icon.ToSoftObjectPath(), TEXT("Icon"));
	NexusDataValidation::RequireNoEmptyFragments(Context, Result, Fragments, TEXT("Fragments"));

	// FitsSlot() returns ProvidedTags.HasAny(SlotAcceptedTags); with no ProvidedTags it
	// matches no slot, so the attachment could never be installed anywhere.
	if (ProvidedTags.IsEmpty())
	{
		Context.AddError(INVTEXT("Provided Tags is empty — no slot's AcceptedTags can match, so this attachment can never be installed."));
		NexusDataValidation::Accumulate(Result, EDataValidationResult::Invalid);
	}

	// The class contract is "author EITHER SkeletalMesh OR StaticMesh"; with neither, an
	// installed attachment spawns no visible mesh.
	if (SkeletalMesh.IsNull() && StaticMesh.IsNull())
	{
		Context.AddError(INVTEXT("Neither Skeletal Mesh nor Static Mesh is set — an installed attachment would be invisible."));
		NexusDataValidation::Accumulate(Result, EDataValidationResult::Invalid);
	}

	// Each modifier folds into the assembly's stat map by StatTag; a tag outside Stat.*
	// (or an unset one) keys nothing and silently contributes no modifier.
	for (int32 Index = 0; Index < Modifiers.Num(); ++Index)
	{
		const FString Field = FString::Printf(TEXT("Modifiers[%d].Stat Tag"), Index);
		NexusDataValidation::RequireTag     (Context, Result, Modifiers[Index].StatTag, *Field);
		NexusDataValidation::RequireTagUnder(Context, Result, Modifiers[Index].StatTag, TEXT("Stat"), *Field);
	}

	return Result;
}

#endif // WITH_EDITOR
