#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/AssetData.h"
#include "GameplayTagContainer.h"
#include "UObject/SoftObjectPath.h"
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

/** How an item's authored GridSize reads against the roster — drives the mis-size flag. */
enum class ENexusFootprintFlag : uint8
{
	/** Plausible footprint. */
	Ok,
	/** A dimension < 1 — always wrong (clamped to 1 at runtime), regardless of the roster. */
	Degenerate,
	/** Area sits far off the roster median — the likely typo (heuristic; needs a roster to judge). */
	AreaOutlier,
};

/**
 * Project-wide facts an individual asset can't compute on its own, gathered once so the
 * per-asset audit (AuditItem / AuditAttachment) is cheap. A batch run (Run, "Validate All")
 * builds this a single time and reuses it across every asset — the same collapse-the-O(N^2)
 * idea the per-helper TTL caches already use, made explicit and shared.
 */
struct FNexusAuditContext
{
	/** Union of every attachment's ProvidedTags — the set a RequiredTag can match against. */
	FGameplayTagContainer GlobalProvided;

	/** Items any level manifest places (the cold-load residency set). */
	TSet<FSoftObjectPath> ManifestItemPaths;

	/**
	 * Items reachable in normal play: seeded with everything a manifest places, then the
	 * fixpoint closure over recipes (an output is reachable once every input is). An item
	 * outside this set is a soft-lock — neither placed nor craftable.
	 */
	TSet<FSoftObjectPath> ReachableItemPaths;

	/** Identity tag -> the asset names that carry it (so a collision can name its partners). */
	TMap<FGameplayTag, TArray<FString>> ItemIdentityNames;
	TMap<FGameplayTag, TArray<FString>> AttachmentIdentityNames;

	/** Median footprint area across the item roster; 0 when the roster is too small to judge. */
	int32 FootprintMedianArea = 0;

	/** One project scan that fills every field above. */
	static FNexusAuditContext Build();
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

	/**
	 * The audit context, rebuilt at most once every couple of seconds. The per-asset
	 * validator calls this so a "Validate All" pass scans the project a single time;
	 * Run() builds a fresh context directly (the commandlet wants no stale data).
	 */
	static const FNexusAuditContext& GetCachedContext();

	/**
	 * Findings for ONE item, the single source of truth shared by Run(), the per-asset
	 * UNexusContentGraphValidator, and the live windows. Appends to Out (never clears it)
	 * so a caller can accumulate. Severity drives gating: Error fails "Validate Assets" /
	 * CI, Warning surfaces non-blocking, Info is log-only.
	 */
	static void AuditItem(const UNexusItemDefinition* Item, const FNexusAuditContext& Context, TArray<FNexusAuditFinding>& Out);

	/** Findings for ONE attachment — the attachment counterpart to AuditItem. */
	static void AuditAttachment(const UNexusAttachmentDefinition* Attachment, const FNexusAuditContext& Context, TArray<FNexusAuditFinding>& Out);

	/**
	 * Classify an authored GridSize against the roster median (0 = roster too small).
	 * Fills OutReason with a human explanation when the result isn't Ok. The one place
	 * the mis-size rule lives, shared by the audit and the Grid Preview tool.
	 */
	static ENexusFootprintFlag ClassifyFootprint(FIntPoint GridSize, int32 MedianArea, FString& OutReason);

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
