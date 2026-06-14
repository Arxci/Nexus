#include "Audit/NexusContentAudit.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "StructUtils/InstancedStruct.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Levels/NexusLevelManifest.h"

#include "Shared/NexusEditorUtils.h"

#define LOCTEXT_NAMESPACE "NexusContentAudit"

namespace
{
	/** "Damage 12, RPM 450" — sorted for stable display. Sorts Stats in place. */
	FString CompactStats(TMap<FGameplayTag, float>& Stats)
	{
		Stats.KeySort([](const FGameplayTag& A, const FGameplayTag& B) { return A.ToString() < B.ToString(); });

		TArray<FString> Parts;
		Parts.Reserve(Stats.Num());
		for (const TPair<FGameplayTag, float>& Pair : Stats)
		{
			Parts.Add(FString::Printf(TEXT("%s %g"), *NexusEditorUtil::TagLeaf(Pair.Key), Pair.Value));
		}
		return FString::Join(Parts, TEXT(", "));
	}

	/** Union of ProvidedTags across the given attachments. */
	FGameplayTagContainer BuildGlobalProvided(const TArray<UNexusAttachmentDefinition*>& Attachments)
	{
		FGameplayTagContainer All;
		for (const UNexusAttachmentDefinition* Attachment : Attachments)
		{
			if (Attachment)
			{
				All.AppendTags(Attachment->ProvidedTags);
			}
		}
		return All;
	}

	/** Append a finding and keep the running error/warning tallies in sync. */
	void AddFinding(FNexusAuditResult& Result, ENexusAuditSeverity Severity, const FText& Message, UObject* Asset)
	{
		TSharedPtr<FNexusAuditFinding> Finding = MakeShared<FNexusAuditFinding>();
		Finding->Severity = Severity;
		Finding->Message = Message;
		Finding->Asset = Asset;
		Result.Findings.Add(Finding);

		if (Severity == ENexusAuditSeverity::Error) { ++Result.NumErrors; }
		else if (Severity == ENexusAuditSeverity::Warning) { ++Result.NumWarnings; }
	}

	/** Push one per-asset finding onto the accumulator AuditItem/AuditAttachment fill. */
	void Emit(TArray<FNexusAuditFinding>& Out, ENexusAuditSeverity Severity, FString&& Message, UObject* Asset)
	{
		FNexusAuditFinding Finding;
		Finding.Severity = Severity;
		Finding.Message = FText::FromString(MoveTemp(Message));
		Finding.Asset = Asset;
		Out.Add(MoveTemp(Finding));
	}

	/** Names sharing Identity in NamesByIdentity, minus Self — empty when the identity is unique. */
	TArray<FString> OtherNamesSharing(
		const TMap<FGameplayTag, TArray<FString>>& NamesByIdentity, const FGameplayTag& Identity, const FString& Self)
	{
		TArray<FString> Others;
		if (const TArray<FString>* Names = NamesByIdentity.Find(Identity))
		{
			for (const FString& Name : *Names)
			{
				if (Name != Self)
				{
					Others.Add(Name);
				}
			}
		}
		return Others;
	}

	// "Validate All" calls the validator once per asset; a short time-to-live cache collapses a
	// batch run into a single project scan while still self-refreshing within a couple of seconds
	// for interactive single-asset validation. Editor-only, game thread; no locking needed.
	constexpr double GAuditCacheTTL = 2.0;
}

FNexusAuditContext FNexusAuditContext::Build()
{
	FNexusAuditContext Context;

	TArray<UNexusItemDefinition*> Items;
	TArray<UNexusAttachmentDefinition*> Attachments;
	TArray<UNexusLevelManifest*> Manifests;
	TArray<UNexusCombinationRecipe*> Recipes;
	NexusEditorUtil::GatherAssets(Items);
	NexusEditorUtil::GatherAssets(Attachments);
	NexusEditorUtil::GatherAssets(Manifests);
	NexusEditorUtil::GatherAssets(Recipes);

	Context.GlobalProvided = BuildGlobalProvided(Attachments);

	// Identity -> names indices, so a per-asset collision can name its partners.
	for (const UNexusItemDefinition* Item : Items)
	{
		if (Item && Item->IdentityTag.IsValid())
		{
			Context.ItemIdentityNames.FindOrAdd(Item->IdentityTag).Add(Item->GetName());
		}
	}
	for (const UNexusAttachmentDefinition* Attachment : Attachments)
	{
		if (Attachment && Attachment->IdentityTag.IsValid())
		{
			Context.AttachmentIdentityNames.FindOrAdd(Attachment->IdentityTag).Add(Attachment->GetName());
		}
	}

	// Manifest residency set + the reachability seed.
	TSet<const UNexusItemDefinition*> Reachable;
	for (const UNexusLevelManifest* Manifest : Manifests)
	{
		if (!Manifest) { continue; }
		for (const TSoftObjectPtr<UNexusItemDefinition>& Soft : Manifest->Items)
		{
			if (Soft.IsNull()) { continue; }
			Context.ManifestItemPaths.Add(Soft.ToSoftObjectPath());
			if (UNexusItemDefinition* Item = Soft.LoadSynchronous())
			{
				Reachable.Add(Item);
			}
		}
	}

	// Fixpoint: add any recipe output whose every input is already reachable.
	bool bGrew = true;
	while (bGrew)
	{
		bGrew = false;
		for (const UNexusCombinationRecipe* Recipe : Recipes)
		{
			if (!Recipe || !Recipe->Output || Reachable.Contains(Recipe->Output))
			{
				continue;
			}
			bool bAllInputs = true;
			for (const FNexusRecipeInput& Input : Recipe->Inputs)
			{
				if (!Input.Definition || !Reachable.Contains(Input.Definition))
				{
					bAllInputs = false;
					break;
				}
			}
			if (bAllInputs)
			{
				Reachable.Add(Recipe->Output);
				bGrew = true;
			}
		}
	}
	for (const UNexusItemDefinition* Item : Reachable)
	{
		Context.ReachableItemPaths.Add(FSoftObjectPath(Item));
	}

	// Footprint-area median: the baseline the mis-size outlier rule compares against. Only
	// meaningful once there are a few items to form a roster (matches the Grid Preview tool).
	TArray<int32> Areas;
	Areas.Reserve(Items.Num());
	for (const UNexusItemDefinition* Item : Items)
	{
		if (Item)
		{
			Areas.Add(FMath::Max(1, Item->GridSize.X * Item->GridSize.Y));
		}
	}
	if (Areas.Num() >= 4)
	{
		Areas.Sort();
		Context.FootprintMedianArea = Areas[Areas.Num() / 2];
	}

	return Context;
}

const FNexusAuditContext& FNexusContentAudit::GetCachedContext()
{
	static double CacheTime = 0.0;
	static FNexusAuditContext Cache;
	static bool bHasCache = false;

	const double Now = FPlatformTime::Seconds();
	if (!bHasCache || (Now - CacheTime) >= GAuditCacheTTL)
	{
		Cache = FNexusAuditContext::Build();
		CacheTime = Now;
		bHasCache = true;
	}
	return Cache;
}

ENexusFootprintFlag FNexusContentAudit::ClassifyFootprint(FIntPoint GridSize, int32 MedianArea, FString& OutReason)
{
	// A non-positive dimension is always wrong, regardless of the roster.
	if (GridSize.X < 1 || GridSize.Y < 1)
	{
		OutReason = FString::Printf(
			TEXT("GridSize has a non-positive dimension (%dx%d) — clamped to 1 at runtime."), GridSize.X, GridSize.Y);
		return ENexusFootprintFlag::Degenerate;
	}

	if (MedianArea <= 0)
	{
		return ENexusFootprintFlag::Ok;   // roster too small to judge outliers
	}

	// Generous factor — footprints legitimately vary a lot; we only want the gross typos.
	constexpr float Factor = 4.0f;
	const int32 Area = FMath::Max(1, GridSize.X * GridSize.Y);
	if (Area > MedianArea * Factor)
	{
		OutReason = FString::Printf(
			TEXT("Footprint area %d is far above the roster median of %d — check for a typo."), Area, MedianArea);
		return ENexusFootprintFlag::AreaOutlier;
	}
	if (Area < MedianArea / Factor)
	{
		OutReason = FString::Printf(
			TEXT("Footprint area %d is far below the roster median of %d — check for a typo."), Area, MedianArea);
		return ENexusFootprintFlag::AreaOutlier;
	}
	return ENexusFootprintFlag::Ok;
}

void FNexusContentAudit::AuditItem(
	const UNexusItemDefinition* Item, const FNexusAuditContext& Context, TArray<FNexusAuditFinding>& Out)
{
	if (!Item)
	{
		return;
	}
	UObject* Asset = const_cast<UNexusItemDefinition*>(Item);
	const FString Name = Item->GetName();

	// Duplicate identity (gate) — identity tags must be unique across items.
	if (Item->IdentityTag.IsValid())
	{
		const TArray<FString> Others = OtherNamesSharing(Context.ItemIdentityNames, Item->IdentityTag, Name);
		if (Others.Num() > 0)
		{
			Emit(Out, ENexusAuditSeverity::Error, FString::Printf(
				TEXT("%s shares identity %s with: %s. Identity tags must be unique across items."),
				*Name, *Item->IdentityTag.ToString(), *FString::Join(Others, TEXT(", "))), Asset);
		}
	}

	// Footprint: degenerate dimension gates; the heuristic area-outlier only warns.
	FString FootprintReason;
	switch (ClassifyFootprint(Item->GridSize, Context.FootprintMedianArea, FootprintReason))
	{
	case ENexusFootprintFlag::Degenerate:
		Emit(Out, ENexusAuditSeverity::Error, FString::Printf(TEXT("%s: %s"), *Name, *FootprintReason), Asset);
		break;
	case ENexusFootprintFlag::AreaOutlier:
		Emit(Out, ENexusAuditSeverity::Warning, FString::Printf(TEXT("%s: %s"), *Name, *FootprintReason), Asset);
		break;
	default:
		break;
	}

	// Localization (gate on DisplayName, info on Description).
	if (Item->DisplayName.IsEmptyOrWhitespace())
	{
		Emit(Out, ENexusAuditSeverity::Error,
			FString::Printf(TEXT("%s has no Display Name — required user-facing text."), *Name), Asset);
	}
	if (Item->Description.IsEmptyOrWhitespace())
	{
		Emit(Out, ENexusAuditSeverity::Info,
			FString::Printf(TEXT("%s has no Description."), *Name), Asset);
	}

	// Reachability — a soft-lock gates; a craftable-but-unplaced item only warns (cold load).
	// A case is the container itself (equipped via DefaultCaseDefinition, not placed/crafted),
	// so it's exempt from the reachability rule.
	if (!NexusEditorUtil::HasCaseFragment(Item))
	{
		const FSoftObjectPath Path(Item);
		const bool bReachable = Context.ReachableItemPaths.Contains(Path);
		const bool bInManifest = Context.ManifestItemPaths.Contains(Path);
		if (!bReachable)
		{
			Emit(Out, ENexusAuditSeverity::Error, FString::Printf(
				TEXT("%s is unreachable — not placed in any manifest and not craftable from reachable inputs (soft-lock)."),
				*Name), Asset);
		}
		else if (!bInManifest)
		{
			Emit(Out, ENexusAuditSeverity::Warning, FString::Printf(
				TEXT("%s is craftable but in no manifest — its first equip may hitch (cold load)."), *Name), Asset);
		}
	}
}

void FNexusContentAudit::AuditAttachment(
	const UNexusAttachmentDefinition* Attachment, const FNexusAuditContext& Context, TArray<FNexusAuditFinding>& Out)
{
	if (!Attachment)
	{
		return;
	}
	UObject* Asset = const_cast<UNexusAttachmentDefinition*>(Attachment);
	const FString Name = Attachment->DisplayName.IsEmpty() ? Attachment->GetName() : Attachment->DisplayName.ToString();

	// No ProvidedTags (gate) — fits no slot, can never be installed.
	if (Attachment->ProvidedTags.IsEmpty())
	{
		Emit(Out, ENexusAuditSeverity::Error,
			FString::Printf(TEXT("%s has no ProvidedTags — it can never be installed."), *Name), Asset);
	}

	// No mesh (gate) — it would be invisible.
	const bool bHasMesh = !Attachment->SkeletalMesh.IsNull() || !Attachment->StaticMesh.IsNull();
	if (!bHasMesh)
	{
		Emit(Out, ENexusAuditSeverity::Error,
			FString::Printf(TEXT("%s has neither skeletal nor static mesh — it would be invisible."), *Name), Asset);
	}

	// Unsatisfiable requirements (gate) — a prerequisite no attachment provides.
	const FGameplayTagContainer Missing = GetUnsatisfiedRequirements(Attachment, Context.GlobalProvided);
	if (!Missing.IsEmpty())
	{
		Emit(Out, ENexusAuditSeverity::Error, FString::Printf(
			TEXT("%s requires %s, which no attachment provides — it could never be installed."),
			*Name, *Missing.ToStringSimple()), Asset);
	}

	// Duplicate identity (gate).
	if (Attachment->IdentityTag.IsValid())
	{
		const TArray<FString> Others = OtherNamesSharing(Context.AttachmentIdentityNames, Attachment->IdentityTag, Attachment->GetName());
		if (Others.Num() > 0)
		{
			Emit(Out, ENexusAuditSeverity::Error, FString::Printf(
				TEXT("%s shares identity %s with: %s. Identity tags must be unique across attachments."),
				*Name, *Attachment->IdentityTag.ToString(), *FString::Join(Others, TEXT(", "))), Asset);
		}
	}

	// Localization (gate on DisplayName, info on Description).
	if (Attachment->DisplayName.IsEmptyOrWhitespace())
	{
		Emit(Out, ENexusAuditSeverity::Error,
			FString::Printf(TEXT("%s has no Display Name — required user-facing text."), *Attachment->GetName()), Asset);
	}
	if (Attachment->Description.IsEmptyOrWhitespace())
	{
		Emit(Out, ENexusAuditSeverity::Info,
			FString::Printf(TEXT("%s has no Description."), *Attachment->GetName()), Asset);
	}

	// Conflict tags nothing provides can never fire — usually a rename/typo. Low severity.
	FGameplayTagContainer DanglingConflicts;
	for (const FGameplayTag& Conflict : Attachment->ConflictTags)
	{
		if (!Context.GlobalProvided.HasTag(Conflict))
		{
			DanglingConflicts.AddTag(Conflict);
		}
	}
	if (!DanglingConflicts.IsEmpty())
	{
		Emit(Out, ENexusAuditSeverity::Info, FString::Printf(
			TEXT("%s lists conflict tags no attachment provides: %s"), *Name, *DanglingConflicts.ToStringSimple()), Asset);
	}

	// Unreferenced — no item slot defaults to it and no manifest lists it.
	if (GetReferencers(Attachment).IsEmpty())
	{
		Emit(Out, ENexusAuditSeverity::Info,
			FString::Printf(TEXT("%s is unreferenced — nothing in the project points at it."), *Attachment->GetName()), Asset);
	}
}

FGameplayTagContainer FNexusContentAudit::GatherGlobalProvidedTags()
{
	static double CacheTime = 0.0;
	static FGameplayTagContainer Cache;
	static bool bHasCache = false;

	const double Now = FPlatformTime::Seconds();
	if (bHasCache && (Now - CacheTime) < GAuditCacheTTL)
	{
		return Cache;
	}

	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Attachments);
	Cache = BuildGlobalProvided(Attachments);
	CacheTime = Now;
	bHasCache = true;
	return Cache;
}

FGameplayTagContainer FNexusContentAudit::GetUnsatisfiedRequirements(
	const UNexusAttachmentDefinition* Attachment, const FGameplayTagContainer& GlobalProvided)
{
	FGameplayTagContainer Missing;
	if (!Attachment)
	{
		return Missing;
	}

	// A requirement is satisfiable if any attachment provides it. GlobalProvided
	// includes the attachment's own ProvidedTags, so the rare "only this part
	// provides the tag it also requires" case is not flagged — the common typo /
	// nothing-provides-it case is.
	for (const FGameplayTag& Required : Attachment->RequiredTags)
	{
		if (!GlobalProvided.HasTag(Required))
		{
			Missing.AddTag(Required);
		}
	}
	return Missing;
}

TArray<UNexusItemDefinition*> FNexusContentAudit::FindItemsSharingIdentity(const UNexusItemDefinition* This)
{
	TArray<UNexusItemDefinition*> Out;
	if (!This || !This->IdentityTag.IsValid())
	{
		return Out;
	}

	// Identity -> items index, cached with the same short TTL so "Validate All" builds
	// it once. Weak pointers so a GC between calls can't dangle.
	static double CacheTime = 0.0;
	static TMap<FGameplayTag, TArray<TWeakObjectPtr<UNexusItemDefinition>>> ByIdentity;

	const double Now = FPlatformTime::Seconds();
	if (ByIdentity.Num() == 0 || (Now - CacheTime) >= GAuditCacheTTL)
	{
		ByIdentity.Reset();
		TArray<UNexusItemDefinition*> All;
		NexusEditorUtil::GatherAssets(All);
		for (UNexusItemDefinition* Item : All)
		{
			if (Item && Item->IdentityTag.IsValid())
			{
				ByIdentity.FindOrAdd(Item->IdentityTag).Add(Item);
			}
		}
		CacheTime = Now;
	}

	if (const TArray<TWeakObjectPtr<UNexusItemDefinition>>* Bucket = ByIdentity.Find(This->IdentityTag))
	{
		for (const TWeakObjectPtr<UNexusItemDefinition>& Weak : *Bucket)
		{
			UNexusItemDefinition* Other = Weak.Get();
			if (Other && Other != This && Other->IdentityTag.MatchesTagExact(This->IdentityTag))
			{
				Out.Add(Other);
			}
		}
	}
	return Out;
}

TArray<FAssetData> FNexusContentAudit::GetReferencers(const UObject* Asset)
{
	TArray<FAssetData> Out;
	if (!Asset)
	{
		return Out;
	}

	const IAssetRegistry& AssetRegistry =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	const FName PackageName = Asset->GetOutermost()->GetFName();

	TArray<FName> ReferencerPackages;
	AssetRegistry.GetReferencers(PackageName, ReferencerPackages, UE::AssetRegistry::EDependencyCategory::Package);

	for (const FName ReferencerPackage : ReferencerPackages)
	{
		if (ReferencerPackage == PackageName)
		{
			continue;
		}
		TArray<FAssetData> Assets;
		AssetRegistry.GetAssetsByPackageName(ReferencerPackage, Assets);
		Out.Append(Assets);
	}
	return Out;
}

FNexusAuditResult FNexusContentAudit::Run()
{
	FNexusAuditResult Result;

	// Fresh scan every Run — the commandlet has just forced a synchronous asset-registry
	// search and wants the current picture, not a TTL-cached one.
	const FNexusAuditContext Context = FNexusAuditContext::Build();

	TArray<UNexusItemDefinition*> Items;
	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Items);
	NexusEditorUtil::GatherAssets(Attachments);

	// --- Items ----------------------------------------------------------------
	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item)
		{
			continue;
		}

		TSharedPtr<FNexusItemRow> Row = MakeShared<FNexusItemRow>();
		Row->Item = Item;
		Row->DisplayName = Item->DisplayName.IsEmpty() ? Item->GetName() : Item->DisplayName.ToString();
		Row->IdentityTag = Item->IdentityTag.IsValid() ? Item->IdentityTag.ToString() : TEXT("(none)");
		Row->Category = Item->CategoryTags.ToStringSimple();
		Row->Grid = Item->GridSize;
		Row->BaseValue = Item->BaseValue;

		// Reuse the game's own resolution: every fragment seeds its base Stat.* keys,
		// so the table shows exactly the pre-attachment stats the assembly would start from.
		for (const TInstancedStruct<FNexusItemFragment>& Fragment : Item->Fragments)
		{
			if (!Fragment.IsValid())
			{
				continue;
			}
			if (const FNexusItemFragment* Base = Fragment.GetPtr<const FNexusItemFragment>())
			{
				Base->SeedStatTags(Row->BaseStats);
			}
		}

		Row->StatsTooltip = CompactStats(Row->BaseStats);

		// Headline stats for their own columns; fall back to the melee damage key so a knife
		// still shows a Dmg value.
		auto StatString = [&Row](const FGameplayTag& Tag) -> FString
		{
			const float* Value = Row->BaseStats.Find(Tag);
			return Value ? FString::Printf(TEXT("%g"), *Value) : FString();
		};
		Row->Damage = StatString(NexusGameplayTags::Stat_Weapon_Damage);
		if (Row->Damage.IsEmpty())
		{
			Row->Damage = StatString(NexusGameplayTags::Stat_Melee_Damage);
		}
		Row->RPM = StatString(NexusGameplayTags::Stat_Weapon_RPM);
		Row->Mag = StatString(NexusGameplayTags::Stat_Weapon_MagazineSize);

		Result.Items.Add(Row);

		TArray<FNexusAuditFinding> ItemFindings;
		AuditItem(Item, Context, ItemFindings);
		for (const FNexusAuditFinding& Finding : ItemFindings)
		{
			AddFinding(Result, Finding.Severity, Finding.Message, Finding.Asset.Get());
		}
	}

	// --- Attachments ----------------------------------------------------------
	for (UNexusAttachmentDefinition* Attachment : Attachments)
	{
		if (!Attachment)
		{
			continue;
		}

		TSharedPtr<FNexusAttachmentRow> Row = MakeShared<FNexusAttachmentRow>();
		Row->Attachment = Attachment;
		Row->DisplayName = Attachment->DisplayName.IsEmpty() ? Attachment->GetName() : Attachment->DisplayName.ToString();
		Row->IdentityTag = Attachment->IdentityTag.IsValid() ? Attachment->IdentityTag.ToString() : TEXT("(none)");
		Row->Provided = Attachment->ProvidedTags.ToStringSimple();
		Row->Required = Attachment->RequiredTags.ToStringSimple();
		Row->Conflict = Attachment->ConflictTags.ToStringSimple();
		Row->bHasMesh = !Attachment->SkeletalMesh.IsNull() || !Attachment->StaticMesh.IsNull();

		TArray<FNexusAuditFinding> AttFindings;
		AuditAttachment(Attachment, Context, AttFindings);

		// The dashboard's per-row Issues column: the human summary of this attachment's
		// problems (errors + warnings; info-level notes stay out of the at-a-glance cell).
		TArray<FString> Issues;
		for (const FNexusAuditFinding& Finding : AttFindings)
		{
			AddFinding(Result, Finding.Severity, Finding.Message, Finding.Asset.Get());
			if (Finding.Severity != ENexusAuditSeverity::Info)
			{
				Issues.Add(Finding.Message.ToString());
			}
		}
		Row->Issues = FString::Join(Issues, TEXT("; "));
		Result.Attachments.Add(Row);
	}

	return Result;
}

#undef LOCTEXT_NAMESPACE
