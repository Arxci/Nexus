#include "Misc/AutomationTest.h"

#include "GameplayTagContainer.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Equipment/Attachments/NexusStatResolver.h"

#include "Audit/NexusContentAudit.h"

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
