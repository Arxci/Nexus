#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR

#include "GameplayTagContainer.h"
#include "Misc/DataValidation.h"
#include "StructUtils/InstancedStruct.h"

/**
 * Reusable building blocks for UObject::IsDataValid overrides on Nexus data
 * assets. Each helper appends one human-readable message to the validation
 * context and folds its own pass/fail into a running EDataValidationResult, so a
 * concrete asset's IsDataValid reads as a flat checklist instead of a wall of
 * if / AddError / Combine triples:
 *
 *     EDataValidationResult Result = Super::IsDataValid(Context);
 *     NexusDataValidation::RequireTag (Context, Result, IdentityTag, TEXT("Identity Tag"));
 *     NexusDataValidation::RequireText(Context, Result, DisplayName, TEXT("Display Name"));
 *     return Result;
 *
 * The Result reference is updated in place via CombineDataValidationResults, so a
 * single failure leaves the asset Invalid no matter how many checks follow, and
 * an all-pass asset stays at the engine's NotValidated floor (treated as "no
 * problems"). Errors flip the result; warnings only annotate.
 *
 * Everything here is WITH_EDITOR only and never compiles into a cooked build.
 * These are deliberately per-asset checks (the kind UE's "Validate Assets" and
 * the cook run for free). Cross-asset rules — duplicate identity tags across
 * items, attachment RequiredTags no other attachment provides — need a project
 * validator that scans the asset registry and are intentionally out of scope
 * here.
 */
namespace NexusDataValidation
{
	/** Fold one step's outcome into the running result (Invalid is sticky). */
	inline void Accumulate(EDataValidationResult& InOutResult, const EDataValidationResult Step)
	{
		InOutResult = CombineDataValidationResults(InOutResult, Step);
	}

	/** Error: this gameplay tag must be set (it identifies or keys the asset). */
	inline void RequireTag(FDataValidationContext& Context, EDataValidationResult& InOutResult,
		const FGameplayTag& Tag, const TCHAR* Field)
	{
		if (!Tag.IsValid())
		{
			Context.AddError(FText::FromString(FString::Printf(
				TEXT("%s is not set — this field is a gameplay tag and must be authored."), Field)));
			Accumulate(InOutResult, EDataValidationResult::Invalid);
		}
	}

	/**
	 * Error: when set, Tag must live under RootName (e.g. "Stat"). A tag that is
	 * unset is left alone here — pair this with RequireTag when the tag is also
	 * mandatory, or use it standalone when an empty tag is acceptable.
	 */
	inline void RequireTagUnder(FDataValidationContext& Context, EDataValidationResult& InOutResult,
		const FGameplayTag& Tag, const TCHAR* RootName, const TCHAR* Field)
	{
		if (Tag.IsValid() && !Tag.ToString().StartsWith(FString::Printf(TEXT("%s."), RootName)))
		{
			Context.AddError(FText::FromString(FString::Printf(
				TEXT("%s (%s) must be a %s.* tag."), Field, *Tag.ToString(), RootName)));
			Accumulate(InOutResult, EDataValidationResult::Invalid);
		}
	}

	/** Error: this text must carry non-whitespace content. */
	inline void RequireText(FDataValidationContext& Context, EDataValidationResult& InOutResult,
		const FText& Value, const TCHAR* Field)
	{
		if (Value.IsEmptyOrWhitespace())
		{
			Context.AddError(FText::FromString(FString::Printf(TEXT("%s is empty."), Field)));
			Accumulate(InOutResult, EDataValidationResult::Invalid);
		}
	}

	/** Warning: a soft reference that names no asset. Used for non-fatal omissions (a missing icon). */
	inline void WarnIfUnset(FDataValidationContext& Context, const FSoftObjectPath& Path, const TCHAR* Field)
	{
		if (Path.IsNull())
		{
			Context.AddWarning(FText::FromString(FString::Printf(TEXT("%s is not assigned."), Field)));
		}
	}

	/** Error: every entry of an instanced-struct fragment array must have a chosen type. */
	template <typename FragmentType>
	void RequireNoEmptyFragments(FDataValidationContext& Context, EDataValidationResult& InOutResult,
		const TArray<TInstancedStruct<FragmentType>>& Fragments, const TCHAR* Field)
	{
		for (int32 Index = 0; Index < Fragments.Num(); ++Index)
		{
			if (!Fragments[Index].IsValid())
			{
				Context.AddError(FText::FromString(FString::Printf(
					TEXT("%s[%d] is empty — a fragment row with no type chosen resolves to nothing at runtime."),
					Field, Index)));
				Accumulate(InOutResult, EDataValidationResult::Invalid);
			}
		}
	}
}

#endif // WITH_EDITOR
