#include "NexusInputContext.h"

#include "InputAction.h"
#include "InputMappingContext.h"

#include "Nexus/Input/NexusInputConfig.h"

void UNexusInputContext::GatherBindings(TArray<FNexusTaggedInputAction>& OutBindings) const
{
	OutBindings.Reset();

	for (const UNexusInputConfig* Config : SharedConfigs)
	{
		if (Config)
		{
			OutBindings.Append(Config->Bindings);
		}
	}
	OutBindings.Append(Bindings);

	// Higher priority binds first so it wins an Input Action a lower row also references
	// (mirrors how a higher-priority IMC consumes a key in Enhanced Input). Stable so
	// equal-priority rows keep their authored order.
	OutBindings.StableSort([](const FNexusTaggedInputAction& A, const FNexusTaggedInputAction& B)
	{
		return A.Priority > B.Priority;
	});
}

UInputMappingContext* UNexusInputContext::ResolveMappingContext(ECommonInputType Device) const
{
	for (const FNexusDeviceMappingContext& Entry : DeviceMappingContexts)
	{
		if (Entry.Device == Device && Entry.MappingContext)
		{
			return Entry.MappingContext;
		}
	}
	return MappingContext;
}

#if WITH_EDITOR
#include "Misc/DataValidation.h"

#define LOCTEXT_NAMESPACE "NexusInputContext"

EDataValidationResult UNexusInputContext::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (!ContextTag.IsValid())
	{
		Context.AddError(LOCTEXT("MissingContextTag", "Context has no Context Tag (Input.Context.*)."));
		Result = EDataValidationResult::Invalid;
	}

	// A UI context hands its input mode to a Common UI widget; an in-world context needs an
	// IMC of its own to produce verbs. (A UI context legitimately ships none.)
	if (!bIsUIContext && !MappingContext && DeviceMappingContexts.Num() == 0 && Bindings.Num() > 0)
	{
		Context.AddWarning(LOCTEXT("NoMappingContext",
			"In-world context has bindings but no Input Mapping Context; its actions will never trigger."));
	}

	return Result;
}

#undef LOCTEXT_NAMESPACE
#endif // WITH_EDITOR
