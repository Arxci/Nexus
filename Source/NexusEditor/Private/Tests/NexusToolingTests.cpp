#include "Misc/AutomationTest.h"

#include "GameplayTagContainer.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Equipment/Attachments/NexusStatResolver.h"
#include "Nexus/Inventory/Fragments/Case/NexusFragment_Case.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"

#include "Audit/NexusContentAudit.h"
#include "Preview/NexusAssemblyPreview.h"
#include "Shared/NexusEditorUtils.h"

/**
 * Automation specs for the two pieces of Nexus tooling logic worth pinning down:
 *
 *  1. FNexusStatResolver::ApplyFold — the shared runtime/preview stat fold. This is the
 *     safety-critical one: the Assembly Preview promises "what you see is what you get",
 *     which only holds if this fold behaves exactly as documented. A regression here
 *     silently mis-balances every weapon.
 *  2. FNexusContentAudit::GetUnsatisfiedRequirements — the cross-asset check the validator
 *     and dashboard both rely on.
 *
 * Run from Tools → Test Automation (or `Automation RunTests Nexus.` on the command line).
 */

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusStatFoldTest, "Nexus.Tooling.StatFold",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusStatFoldTest::RunTest(const FString& Parameters)
{
	const FGameplayTag Damage = NexusGameplayTags::Stat_Weapon_Damage;

	// One attachment: +20 then x1.5 on Damage.
	UNexusAttachmentDefinition* Attachment = NewObject<UNexusAttachmentDefinition>();
	FAttachmentStatModifier Modifier;
	Modifier.StatTag = Damage;
	Modifier.Add = 20.0f;
	Modifier.Mul = 1.5f;
	Attachment->Modifiers.Add(Modifier);

	const TArray<const UNexusAttachmentDefinition*> Defs = { Attachment };

	TMap<FGameplayTag, float> Upgrade;
	Upgrade.Add(Damage, 10.0f); // +10 persistent upgrade tier

	// (100 + 20) * 1.5 = 180, + 10 upgrade = 190.
	// Case A — clamped to [0, 150] → 150.
	{
		TMap<FGameplayTag, float> Values; Values.Add(Damage, 100.0f);
		TMap<FGameplayTag, FVector2D> Clamps; Clamps.Add(Damage, FVector2D(0.0f, 150.0f));
		FNexusStatResolver::ApplyFold(Values, Clamps, Defs, Upgrade);
		TestEqual(TEXT("Clamped fold pins Damage at the 150 ceiling"), Values.FindRef(Damage), 150.0f);
	}

	// Case B — unbounded clamp (Max <= Min is treated as no bound) → full 190.
	{
		TMap<FGameplayTag, float> Values; Values.Add(Damage, 100.0f);
		TMap<FGameplayTag, FVector2D> Clamps; Clamps.Add(Damage, FVector2D(0.0f, 0.0f));
		FNexusStatResolver::ApplyFold(Values, Clamps, Defs, Upgrade);
		TestEqual(TEXT("Unbounded fold yields (100+20)*1.5+10 = 190"), Values.FindRef(Damage), 190.0f);
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusUnsatisfiedRequirementsTest, "Nexus.Tooling.UnsatisfiedRequirements",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusUnsatisfiedRequirementsTest::RunTest(const FString& Parameters)
{
	const FGameplayTag Sight  = NexusGameplayTags::Attachment_Type_Sight;
	const FGameplayTag Barrel = NexusGameplayTags::Attachment_Type_Barrel;

	// An attachment that requires both a Sight mount and a Barrel mount.
	UNexusAttachmentDefinition* Attachment = NewObject<UNexusAttachmentDefinition>();
	Attachment->RequiredTags.AddTag(Sight);
	Attachment->RequiredTags.AddTag(Barrel);

	// The project only provides Sight anywhere.
	FGameplayTagContainer Provided;
	Provided.AddTag(Sight);

	const FGameplayTagContainer Missing =
		FNexusContentAudit::GetUnsatisfiedRequirements(Attachment, Provided);

	TestEqual(TEXT("Exactly one requirement is unsatisfied"), Missing.Num(), 1);
	TestTrue(TEXT("Barrel is reported missing"), Missing.HasTagExact(Barrel));
	TestFalse(TEXT("Sight (which is provided) is not reported"), Missing.HasTagExact(Sight));

	return true;
}

/**
 * Golden content tests — these run against the project's REAL item/recipe/attachment assets,
 * not synthetic fixtures, so a designer who ships broken content fails the automation suite
 * (and CI) the same way the validate-content commandlet does. They are deliberately tolerant
 * of an empty project (a fresh checkout with no content passes vacuously).
 *
 * Each test forces a synchronous asset-registry scan first, because an automation run can
 * start before the registry has finished its background discovery.
 */
namespace
{
	void NexusForceContentScan()
	{
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get()
			.SearchAllAssets(/*bSynchronousSearch=*/ true);
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusGoldenRecipesResolveTest, "Nexus.Content.RecipesResolve",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusGoldenRecipesResolveTest::RunTest(const FString& Parameters)
{
	NexusForceContentScan();

	TArray<UNexusCombinationRecipe*> Recipes;
	NexusEditorUtil::GatherAssets(Recipes);

	for (const UNexusCombinationRecipe* Recipe : Recipes)
	{
		if (!Recipe)
		{
			continue;
		}
		const FString Name = Recipe->GetName();
		// TObjectPtr -> raw pointer: TestNotNull deduces ValueType from a const ValueType*.
		TestNotNull(*FString::Printf(TEXT("%s has an Output"), *Name), Recipe->Output.Get());
		TestTrue(*FString::Printf(TEXT("%s OutputCount >= 1"), *Name), Recipe->OutputCount >= 1);
		TestTrue(*FString::Printf(TEXT("%s has at least one input"), *Name), Recipe->Inputs.Num() > 0);

		for (int32 Index = 0; Index < Recipe->Inputs.Num(); ++Index)
		{
			const FNexusRecipeInput& Input = Recipe->Inputs[Index];
			TestNotNull(*FString::Printf(TEXT("%s input %d has a Definition"), *Name, Index), Input.Definition.Get());
			TestTrue(*FString::Printf(TEXT("%s input %d Count >= 1"), *Name, Index), Input.Count >= 1);
		}
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusGoldenWeaponsAssembleTest, "Nexus.Content.WeaponsAssemble",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusGoldenWeaponsAssembleTest::RunTest(const FString& Parameters)
{
	NexusForceContentScan();

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);

	const TArray<UNexusAttachmentDefinition*> NoAttachments;

	for (const UNexusItemDefinition* Item : Items)
	{
		const FNexusFragment_Weapon* Weapon = NexusEditorUtil::FindWeaponFragment(Item);
		if (!Weapon)
		{
			continue;
		}
		const FString Name = Item->GetName();
		TestTrue(*FString::Printf(TEXT("%s is ranged or melee (a usable weapon)"), *Name),
			Weapon->bHasRanged || Weapon->bHasMelee);

		// "Assembles" = the author-time fold runs at every upgrade tier and yields only
		// finite stats (no NaN/Inf from a bad clamp or modifier), at the bare weapon.
		const int32 MaxTier = FNexusAssemblyPreview::GetMaxUpgradeTier(Item);
		for (int32 Tier = 0; Tier <= MaxTier; ++Tier)
		{
			const TArray<FNexusResolvedStat> Stats = FNexusAssemblyPreview::Resolve(Item, NoAttachments, Tier);
			for (const FNexusResolvedStat& Stat : Stats)
			{
				TestTrue(*FString::Printf(TEXT("%s stat %s is finite at tier %d"),
					*Name, *Stat.StatTag.ToString(), Tier), FMath::IsFinite(Stat.Final));
			}
		}
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusGoldenItemsFitCaseTest, "Nexus.Content.ItemsFitDefaultCase",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusGoldenItemsFitCaseTest::RunTest(const FString& Parameters)
{
	NexusForceContentScan();

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);

	// Default case: prefer the one flagged bDefaultCase, else fall back to any case item.
	const UNexusItemDefinition* CaseItem = nullptr;
	FIntPoint CaseSize(0, 0);
	for (const UNexusItemDefinition* Item : Items)
	{
		if (const FNexusFragment_Case* Case = NexusEditorUtil::FindCaseFragment(Item))
		{
			if (Case->bDefaultCase)
			{
				CaseItem = Item;
				CaseSize = Case->GridSize;
				break;
			}
			if (!CaseItem)
			{
				CaseItem = Item;
				CaseSize = Case->GridSize;
			}
		}
	}

	if (!CaseItem)
	{
		AddInfo(TEXT("No case item in the project — nothing to size items against; skipping."));
		return true;
	}

	const int32 CaseW = FMath::Max(1, CaseSize.X);
	const int32 CaseH = FMath::Max(1, CaseSize.Y);

	for (const UNexusItemDefinition* Item : Items)
	{
		// A case isn't stored inside a case, so don't size cases against the case.
		if (!Item || NexusEditorUtil::HasCaseFragment(Item))
		{
			continue;
		}
		const int32 W = FMath::Max(1, Item->GridSize.X);
		const int32 H = FMath::Max(1, Item->GridSize.Y);
		// Either orientation fits, since the grid can rotate items.
		const bool bFits = (W <= CaseW && H <= CaseH) || (H <= CaseW && W <= CaseH);
		TestTrue(*FString::Printf(TEXT("%s (%dx%d) fits the default case '%s' (%dx%d)"),
			*Item->GetName(), W, H, *CaseItem->GetName(), CaseW, CaseH), bFits);
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusGoldenNoDuplicateIdentityTest, "Nexus.Content.NoDuplicateIdentity",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusGoldenNoDuplicateIdentityTest::RunTest(const FString& Parameters)
{
	NexusForceContentScan();

	auto CheckUnique = [this](const TMap<FGameplayTag, TArray<FString>>& ByIdentity, const TCHAR* Kind)
	{
		for (const TPair<FGameplayTag, TArray<FString>>& Pair : ByIdentity)
		{
			TestTrue(*FString::Printf(TEXT("%s identity %s is unique (carried by: %s)"),
				Kind, *Pair.Key.ToString(), *FString::Join(Pair.Value, TEXT(", "))),
				Pair.Value.Num() <= 1);
		}
	};

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	TMap<FGameplayTag, TArray<FString>> ItemsByIdentity;
	for (const UNexusItemDefinition* Item : Items)
	{
		if (Item && Item->IdentityTag.IsValid())
		{
			ItemsByIdentity.FindOrAdd(Item->IdentityTag).Add(Item->GetName());
		}
	}
	CheckUnique(ItemsByIdentity, TEXT("Item"));

	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Attachments);
	TMap<FGameplayTag, TArray<FString>> AttachmentsByIdentity;
	for (const UNexusAttachmentDefinition* Attachment : Attachments)
	{
		if (Attachment && Attachment->IdentityTag.IsValid())
		{
			AttachmentsByIdentity.FindOrAdd(Attachment->IdentityTag).Add(Attachment->GetName());
		}
	}
	CheckUnique(AttachmentsByIdentity, TEXT("Attachment"));

	return true;
}
