#include "NexusCombinationRecipe.h"

#if WITH_EDITOR

#include "Misc/DataValidation.h"

EDataValidationResult UNexusCombinationRecipe::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	// The combination subsystem consumes Inputs and produces Output through the
	// inventory API; a null on either side makes the recipe craft from — or into —
	// nothing, which reads at runtime as a craft that silently does nothing.
	if (Inputs.Num() == 0)
	{
		Context.AddError(INVTEXT("Recipe has no Inputs — it would craft from nothing."));
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
	}

	for (int32 Index = 0; Index < Inputs.Num(); ++Index)
	{
		if (Inputs[Index].Definition == nullptr)
		{
			Context.AddError(FText::FromString(FString::Printf(
				TEXT("Inputs[%d] has no item Definition assigned."), Index)));
			Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		}
		if (Inputs[Index].Count < 1)
		{
			Context.AddError(FText::FromString(FString::Printf(
				TEXT("Inputs[%d] Count is below 1."), Index)));
			Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
		}
	}

	if (Output == nullptr)
	{
		Context.AddError(INVTEXT("Output is not assigned — the craft would produce nothing."));
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
	}

	if (OutputCount < 1)
	{
		Context.AddError(INVTEXT("Output Count is below 1."));
		Result = CombineDataValidationResults(Result, EDataValidationResult::Invalid);
	}

	return Result;
}

#endif // WITH_EDITOR
