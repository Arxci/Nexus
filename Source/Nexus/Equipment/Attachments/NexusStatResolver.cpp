#include "Nexus/Equipment/Attachments/NexusStatResolver.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusAttachmentTypes.h"

void FNexusStatResolver::ApplyFold(
	TMap<FGameplayTag, float>& InOutValues,
	const TMap<FGameplayTag, FVector2D>& Clamps,
	const TArray<const UNexusAttachmentDefinition*>& AttachmentDefs,
	const TMap<FGameplayTag, float>& UpgradeStatTags)
{
	// Two-pass attachment fold so multiplicative modifiers always apply on top of
	// the fully-summed additive base — matches how AAA gunsmiths describe their
	// attachment math (flat bonus, then percentage).
	TMap<FGameplayTag, float> AddSum;
	TMap<FGameplayTag, float> MulProduct;

	for (const UNexusAttachmentDefinition* Def : AttachmentDefs)
	{
		if (!Def) continue;
		for (const FAttachmentStatModifier& Mod : Def->Modifiers)
		{
			if (!Mod.StatTag.IsValid()) continue;
			AddSum.FindOrAdd(Mod.StatTag, 0.0f)     += Mod.Add;
			MulProduct.FindOrAdd(Mod.StatTag, 1.0f) *= Mod.Mul;
		}
	}

	for (const TPair<FGameplayTag, float>& Add : AddSum)
	{
		// Only modify keys we actually seeded — modifiers against unknown stat
		// tags would otherwise silently invent values.
		if (float* Value = InOutValues.Find(Add.Key))
		{
			*Value += Add.Value;
		}
	}
	for (const TPair<FGameplayTag, float>& Mul : MulProduct)
	{
		if (float* Value = InOutValues.Find(Mul.Key))
		{
			*Value *= Mul.Value;
		}
	}

	// Persistent upgrade tier: merchant tune-ups fold in as a FINAL additive tier,
	// after the attachment multiplier. Filtered to seeded keys.
	for (const TPair<FGameplayTag, float>& Upgrade : UpgradeStatTags)
	{
		if (float* Value = InOutValues.Find(Upgrade.Key))
		{
			*Value += Upgrade.Value;
		}
	}

	// Final safety bound: clamp each resolved value to its authored [min,max].
	// An entry whose Max <= Min is treated as unbounded (the neutral default).
	for (const TPair<FGameplayTag, FVector2D>& Bound : Clamps)
	{
		if (Bound.Value.Y <= Bound.Value.X) continue;
		if (float* Value = InOutValues.Find(Bound.Key))
		{
			*Value = FMath::Clamp(*Value, Bound.Value.X, Bound.Value.Y);
		}
	}
}
