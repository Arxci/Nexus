#include "Audit/NexusContentAudit.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "StructUtils/InstancedStruct.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
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

	/** Report any identity tag shared by more than one asset in ByIdentity as an error. */
	template <typename T>
	void ReportDuplicateIdentities(FNexusAuditResult& Result, const TMap<FGameplayTag, TArray<T*>>& ByIdentity, const TCHAR* Kind)
	{
		for (const TPair<FGameplayTag, TArray<T*>>& Pair : ByIdentity)
		{
			if (Pair.Value.Num() <= 1)
			{
				continue;
			}

			TArray<FString> Names;
			for (const T* Asset : Pair.Value)
			{
				Names.Add(Asset->GetName());
			}

			AddFinding(Result, ENexusAuditSeverity::Error,
				FText::FromString(FString::Printf(
					TEXT("%s identity %s is shared by %d assets: %s"),
					Kind, *Pair.Key.ToString(), Pair.Value.Num(), *FString::Join(Names, TEXT(", ")))),
				Pair.Value[0]);
		}
	}
}

namespace
{
	// "Validate All" calls the validator once per asset, and each call used to rescan
	// the whole project — O(N^2). A short time-to-live cache collapses a batch run into a
	// single scan while still self-refreshing within a couple of seconds for interactive
	// single-asset validation. Editor-only, game thread; no locking needed.
	constexpr double GAuditCacheTTL = 2.0;
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

	TArray<UNexusItemDefinition*> Items;
	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Items);
	NexusEditorUtil::GatherAssets(Attachments);

	// --- Items ----------------------------------------------------------------
	TMap<FGameplayTag, TArray<UNexusItemDefinition*>> ItemsByIdentity;
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
		if (Item->DisplayName.IsEmptyOrWhitespace())
		{
			AddFinding(Result, ENexusAuditSeverity::Warning,
				FText::FromString(FString::Printf(TEXT("%s has no Display Name — UI text is missing."), *Item->GetName())), Item);
		}
		if (Item->Description.IsEmptyOrWhitespace())
		{
			AddFinding(Result, ENexusAuditSeverity::Info,
				FText::FromString(FString::Printf(TEXT("%s has no Description."), *Item->GetName())), Item);
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

		if (Item->IdentityTag.IsValid())
		{
			ItemsByIdentity.FindOrAdd(Item->IdentityTag).Add(Item);
		}
	}
	ReportDuplicateIdentities(Result, ItemsByIdentity, TEXT("Item"));

	// --- Attachments ----------------------------------------------------------
	const FGameplayTagContainer GlobalProvided = BuildGlobalProvided(Attachments);
	TMap<FGameplayTag, TArray<UNexusAttachmentDefinition*>> AttByIdentity;
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

		TArray<FString> Issues;

		if (Attachment->ProvidedTags.IsEmpty())
		{
			Issues.Add(TEXT("no ProvidedTags (fits no slot)"));
			AddFinding(Result, ENexusAuditSeverity::Error,
				FText::FromString(FString::Printf(TEXT("%s has no ProvidedTags — it can never be installed."),
					*Row->DisplayName)), Attachment);
		}

		if (!Row->bHasMesh)
		{
			Issues.Add(TEXT("no mesh (invisible)"));
			AddFinding(Result, ENexusAuditSeverity::Error,
				FText::FromString(FString::Printf(TEXT("%s has neither skeletal nor static mesh — it would be invisible."),
					*Row->DisplayName)), Attachment);
		}

		const FGameplayTagContainer Missing = GetUnsatisfiedRequirements(Attachment, GlobalProvided);
		if (!Missing.IsEmpty())
		{
			Issues.Add(FString::Printf(TEXT("unsatisfiable requires: %s"), *Missing.ToStringSimple()));
			AddFinding(Result, ENexusAuditSeverity::Error,
				FText::FromString(FString::Printf(TEXT("%s requires %s, which no attachment provides."),
					*Row->DisplayName, *Missing.ToStringSimple())), Attachment);
		}

		// Conflict tags nothing provides can never fire — usually a rename/typo. Low severity.
		FGameplayTagContainer DanglingConflicts;
		for (const FGameplayTag& Conflict : Attachment->ConflictTags)
		{
			if (!GlobalProvided.HasTag(Conflict))
			{
				DanglingConflicts.AddTag(Conflict);
			}
		}
		if (!DanglingConflicts.IsEmpty())
		{
			Issues.Add(FString::Printf(TEXT("inert conflicts: %s"), *DanglingConflicts.ToStringSimple()));
			AddFinding(Result, ENexusAuditSeverity::Info,
				FText::FromString(FString::Printf(TEXT("%s lists conflict tags no attachment provides: %s"),
					*Row->DisplayName, *DanglingConflicts.ToStringSimple())), Attachment);
		}

		if (Attachment->DisplayName.IsEmptyOrWhitespace())
		{
			AddFinding(Result, ENexusAuditSeverity::Warning,
				FText::FromString(FString::Printf(TEXT("%s has no Display Name — UI text is missing."), *Attachment->GetName())), Attachment);
		}
		if (Attachment->Description.IsEmptyOrWhitespace())
		{
			AddFinding(Result, ENexusAuditSeverity::Info,
				FText::FromString(FString::Printf(TEXT("%s has no Description."), *Attachment->GetName())), Attachment);
		}

		Row->Issues = FString::Join(Issues, TEXT("; "));
		Result.Attachments.Add(Row);

		if (Attachment->IdentityTag.IsValid())
		{
			AttByIdentity.FindOrAdd(Attachment->IdentityTag).Add(Attachment);
		}
	}
	ReportDuplicateIdentities(Result, AttByIdentity, TEXT("Attachment"));

	// --- Coverage -------------------------------------------------------------
	// Items reachable in no level manifest aren't preloaded, so their first equip
	// hitches on a cold load (the manifest is Nexus's Lyra-style residency set).
	TArray<UNexusLevelManifest*> Manifests;
	NexusEditorUtil::GatherAssets(Manifests);
	TSet<FSoftObjectPath> ManifestItemPaths;
	for (const UNexusLevelManifest* Manifest : Manifests)
	{
		if (!Manifest) { continue; }
		for (const TSoftObjectPtr<UNexusItemDefinition>& SoftItem : Manifest->Items)
		{
			if (!SoftItem.IsNull()) { ManifestItemPaths.Add(SoftItem.ToSoftObjectPath()); }
		}
	}
	for (UNexusItemDefinition* Item : Items)
	{
		if (Item && !ManifestItemPaths.Contains(FSoftObjectPath(Item)))
		{
			AddFinding(Result, ENexusAuditSeverity::Warning,
				FText::FromString(FString::Printf(
					TEXT("%s is in no level manifest — its first equip will hitch (cold load)."), *Item->GetName())),
				Item);
		}
	}
	// Attachments nothing references — no item slot defaults to one and no manifest lists it.
	for (UNexusAttachmentDefinition* Attachment : Attachments)
	{
		if (Attachment && GetReferencers(Attachment).IsEmpty())
		{
			AddFinding(Result, ENexusAuditSeverity::Info,
				FText::FromString(FString::Printf(
					TEXT("%s is unreferenced — nothing in the project points at it."), *Attachment->GetName())),
				Attachment);
		}
	}

	return Result;
}

#undef LOCTEXT_NAMESPACE
