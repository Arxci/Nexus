#include "NexusInputConfig.h"

#include "InputAction.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"

#define LOCTEXT_NAMESPACE "NexusInputConfig"

EDataValidationResult UNexusInputConfig::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	for (int32 Index = 0; Index < Bindings.Num(); ++Index)
	{
		const FNexusTaggedInputAction& Binding = Bindings[Index];

		if (!Binding.InputTag.IsValid())
		{
			Context.AddError(FText::Format(
				LOCTEXT("MissingTag", "Binding {0} has no Input Tag."), FText::AsNumber(Index)));
			Result = EDataValidationResult::Invalid;
		}
		if (!Binding.InputAction)
		{
			Context.AddError(FText::Format(
				LOCTEXT("MissingAction", "Binding {0} ({1}) has no Input Action."),
				FText::AsNumber(Index), FText::FromName(Binding.InputTag.GetTagName())));
			Result = EDataValidationResult::Invalid;
		}
		// A declarative row must name the ability it activates; a listener row must not.
		const bool bDeclarative = Binding.ActivationStyle != ENexusInputActivationStyle::Listener;
		if (bDeclarative && !Binding.ActivateAbilityTag.IsValid() && !Binding.RequestUIPanelTag.IsValid())
		{
			Context.AddWarning(FText::Format(
				LOCTEXT("DeclarativeNoTarget", "Binding {0} ({1}) is declarative but names neither an ability nor a UI panel."),
				FText::AsNumber(Index), FText::FromName(Binding.InputTag.GetTagName())));
		}
	}

	return Result;
}

#undef LOCTEXT_NAMESPACE
#endif // WITH_EDITOR
