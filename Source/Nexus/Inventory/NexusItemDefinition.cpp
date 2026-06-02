#include "NexusItemDefinition.h"

#include "Nexus/NexusAssetManager.h"

#if WITH_EDITOR
#include "Nexus/Validation/NexusDataValidation.h"
#endif

FPrimaryAssetId UNexusItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UNexusAssetManager::TypeItemDefinition, GetFName());
}

#if WITH_EDITOR

EDataValidationResult UNexusItemDefinition::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	NexusDataValidation::RequireTag (Context, Result, IdentityTag, TEXT("Identity Tag"));
	NexusDataValidation::RequireText(Context, Result, DisplayName, TEXT("Display Name"));
	NexusDataValidation::WarnIfUnset(Context, Icon.ToSoftObjectPath(), TEXT("Icon"));
	NexusDataValidation::RequireNoEmptyFragments(Context, Result, Fragments, TEXT("Fragments"));

	// The inventory clamps GridSize to a 1x1 minimum at read sites; a sub-1 authored
	// value would therefore be silently corrected at runtime, masking the mistake here.
	if (GridSize.X < 1 || GridSize.Y < 1)
	{
		Context.AddError(FText::FromString(FString::Printf(
			TEXT("Grid Size %dx%d is below the 1x1 minimum."), GridSize.X, GridSize.Y)));
		NexusDataValidation::Accumulate(Result, EDataValidationResult::Invalid);
	}

	// Priced for trade but worth nothing — the merchant would buy/sell it for 0 currency.
	if ((bSellable || bBuyable) && BaseValue <= 0)
	{
		Context.AddWarning(INVTEXT("Item is Sellable/Buyable but Base Value is 0 — the merchant would price it at nothing."));
	}

	return Result;
}

#endif // WITH_EDITOR
