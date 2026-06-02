#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "GameplayTagContainer.h"
#include "UObject/WeakObjectPtr.h"

class UNexusItemDefinition;
class UNexusAttachmentDefinition;

/** Severity of a single audit finding; drives colour and the error/warning tallies. */
enum class ENexusAuditSeverity : uint8
{
	Info,
	Warning,
	Error,
};

/** One issue the audit turned up, paired with the asset it concerns (for select / open). */
struct FNexusAuditFinding
{
	ENexusAuditSeverity Severity = ENexusAuditSeverity::Info;
	FText Message;
	TWeakObjectPtr<UObject> Asset;
};

/** One row in the items table — identity, footprint, economy and resolved base stats. */
struct FNexusItemRow
{
	TWeakObjectPtr<UNexusItemDefinition> Item;
	FString DisplayName;
	FString IdentityTag;
	FString Category;
	FIntPoint Grid = FIntPoint(1, 1);
	int32 BaseValue = 0;
	/** Stat.* base values seeded by the item's fragments, before any attachment fold. */
	TMap<FGameplayTag, float> BaseStats;
	/** Headline stats pulled into their own scannable columns (empty when the item has none). */
	FString Damage;
	FString RPM;
	FString Mag;
	/** Full "Damage 25, RPM 300, ..." breakdown, shown as the stat columns' tooltip. */
	FString StatsTooltip;
};

/** One row in the attachments table, including a precomputed per-row issue summary. */
struct FNexusAttachmentRow
{
	TWeakObjectPtr<UNexusAttachmentDefinition> Attachment;
	FString DisplayName;
	FString IdentityTag;
	FString Provided;
	FString Required;
	FString Conflict;
	bool bHasMesh = false;
	/** Empty when the attachment is clean; otherwise a human summary of its problems. */
	FString Issues;
};

/** Everything one audit pass produces: the table models plus the flat findings list. */
struct FNexusAuditResult
{
	TArray<TSharedPtr<FNexusItemRow>> Items;
	TArray<TSharedPtr<FNexusAttachmentRow>> Attachments;
	TArray<TSharedPtr<FNexusAuditFinding>> Findings;
	int32 NumErrors = 0;
	int32 NumWarnings = 0;
};

/**
 * The cross-asset content audit. Scans every UNexusItemDefinition and
 * UNexusAttachmentDefinition in the project (via the asset registry), then
 * reports the problems a single asset can't see on its own — duplicate identity
 * tags, attachment requirements no other attachment can satisfy — alongside the
 * per-asset issues already covered by IsDataValid, so the dashboard is a single
 * place to read content health.
 *
 * This is the shared brain: SNexusContentDashboard calls Run() for the full
 * picture, and UNexusContentGraphValidator calls the focused helpers to validate
 * one asset at a time inside the editor's Validate Assets flow.
 */
class FNexusContentAudit
{
public:
	/** Full project scan: loads all items/attachments and builds tables + findings. */
	static FNexusAuditResult Run();

	/** Union of every attachment's ProvidedTags — the set a RequiredTag can match against. */
	static FGameplayTagContainer GatherGlobalProvidedTags();

	/**
	 * RequiredTags on Attachment that nothing in GlobalProvided supplies, i.e. the
	 * attachment could never be installed because a prerequisite has no provider.
	 * Pass the result of GatherGlobalProvidedTags() so a batch caller scans once.
	 */
	static FGameplayTagContainer GetUnsatisfiedRequirements(
		const UNexusAttachmentDefinition* Attachment, const FGameplayTagContainer& GlobalProvided);

	/**
	 * Other item definitions that share This item's IdentityTag (which is meant to be
	 * unique). Empty when the identity is unique or unset.
	 */
	static TArray<UNexusItemDefinition*> FindItemsSharingIdentity(const UNexusItemDefinition* This);

	/** Assets that reference Asset (its package's referencers, hard + soft) — a "where used" view. */
	static TArray<FAssetData> GetReferencers(const UObject* Asset);
};
