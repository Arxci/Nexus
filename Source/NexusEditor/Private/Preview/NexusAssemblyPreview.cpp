#include "Preview/NexusAssemblyPreview.h"

#include "StructUtils/InstancedStruct.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusAttachmentTypes.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"
#include "Nexus/Equipment/Attachments/NexusStatResolver.h"

#include "Shared/NexusEditorUtils.h"

int32 FNexusAssemblyPreview::GetMaxUpgradeTier(const UNexusItemDefinition* Weapon)
{
	int32 Max = 0;
	if (const FNexusFragment_Weapon* WeaponFragment = NexusEditorUtil::FindWeaponFragment(Weapon))
	{
		for (const FNexusWeaponUpgradeTrack& Track : WeaponFragment->UpgradeTracks)
		{
			Max = FMath::Max(Max, Track.Tiers.Num());
		}
	}
	return Max;
}

TArray<FNexusResolvedStat> FNexusAssemblyPreview::Resolve(
	const UNexusItemDefinition* Weapon,
	const TArray<UNexusAttachmentDefinition*>& Attachments,
	int32 UpgradeTier)
{
	TArray<FNexusResolvedStat> Out;
	if (!Weapon)
	{
		return Out;
	}

	// 1. Base values and clamp bounds, straight from the item's own fragments.
	TMap<FGameplayTag, float> Base;
	TMap<FGameplayTag, FVector2D> Clamps;
	for (const TInstancedStruct<FNexusItemFragment>& Frag : Weapon->Fragments)
	{
		if (!Frag.IsValid()) { continue; }
		if (const FNexusItemFragment* Fragment = Frag.GetPtr<const FNexusItemFragment>())
		{
			Fragment->SeedStatTags(Base);
			Fragment->SeedStatClamps(Clamps);
		}
	}

	// 2. Attachment modifiers: ΣAdd and ΠMul per stat.
	TMap<FGameplayTag, float> SumAdd;
	TMap<FGameplayTag, float> ProductMul;
	for (const UNexusAttachmentDefinition* Attachment : Attachments)
	{
		if (!Attachment) { continue; }
		for (const FAttachmentStatModifier& Modifier : Attachment->Modifiers)
		{
			if (!Modifier.StatTag.IsValid()) { continue; }
			SumAdd.FindOrAdd(Modifier.StatTag) += Modifier.Add;
			if (!ProductMul.Contains(Modifier.StatTag)) { ProductMul.Add(Modifier.StatTag, 1.0f); }
			ProductMul[Modifier.StatTag] *= Modifier.Mul;
		}
	}

	// 3. Upgrade-tier additive delta (cumulative Value at the selected tier).
	TMap<FGameplayTag, float> UpgradeAdd;
	if (const FNexusFragment_Weapon* WeaponFragment = NexusEditorUtil::FindWeaponFragment(Weapon))
	{
		for (const FNexusWeaponUpgradeTrack& Track : WeaponFragment->UpgradeTracks)
		{
			if (!Track.StatTag.IsValid() || Track.Tiers.Num() == 0) { continue; }
			const int32 Tier = FMath::Clamp(UpgradeTier, 0, Track.Tiers.Num());
			if (Tier > 0)
			{
				UpgradeAdd.Add(Track.StatTag, Track.Tiers[Tier - 1].Value);
			}
		}
	}

	// 4. Final values come through the SAME fold the runtime uses (FNexusStatResolver),
	// so the headline number can't drift from in-game. The +Attach / +Upgrade columns are
	// an illustrative local breakdown of the steps.
	TArray<const UNexusAttachmentDefinition*> Defs;
	Defs.Reserve(Attachments.Num());
	for (const UNexusAttachmentDefinition* Attachment : Attachments) { Defs.Add(Attachment); }

	TMap<FGameplayTag, float> Resolved = Base;
	FNexusStatResolver::ApplyFold(Resolved, Clamps, Defs, UpgradeAdd);

	for (const TPair<FGameplayTag, float>& Pair : Base)
	{
		FNexusResolvedStat Stat;
		Stat.StatTag = Pair.Key;
		Stat.Base = Pair.Value;

		const float Add = SumAdd.FindRef(Pair.Key);
		const float* MulPtr = ProductMul.Find(Pair.Key);
		const float Mul = MulPtr ? *MulPtr : 1.0f;
		Stat.AfterAttachments = (Stat.Base + Add) * Mul;
		Stat.AfterUpgrade = Stat.AfterAttachments + UpgradeAdd.FindRef(Pair.Key);
		Stat.Final = Resolved.FindRef(Pair.Key);
		Stat.bClamped = !FMath::IsNearlyEqual(Stat.Final, Stat.AfterUpgrade);

		Out.Add(Stat);
	}

	Out.Sort([](const FNexusResolvedStat& A, const FNexusResolvedStat& B)
	{
		return A.StatTag.ToString() < B.StatTag.ToString();
	});
	return Out;
}
