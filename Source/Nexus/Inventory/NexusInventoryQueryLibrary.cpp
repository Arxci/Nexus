#include "NexusInventoryQueryLibrary.h"

#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemContainer.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/NexusItemEconomyLibrary.h"

namespace
{
	FString DisplayNameOf(const UNexusItemInstance& Instance)
	{
		const UNexusItemDefinition* Def = Instance.GetDefinition();
		return Def ? Def->DisplayName.ToString() : FString();
	}

	int32 FootprintAreaOf(const UNexusItemInstance& Instance)
	{
		const FIntPoint Foot = Instance.GetGridFootprint();
		return Foot.X * Foot.Y;
	}
}

TArray<UNexusItemInstance*> UNexusInventoryQueryLibrary::QueryInventory(const UNexusInventoryComponent* Inventory,
	const FNexusItemQuery& Query)
{
	if (!Inventory) return TArray<UNexusItemInstance*>();

	// Scope to a section first when asked (cheaper, and the section is its own concept);
	// the remaining predicates + sort run over that subset.
	const TArray<UNexusItemInstance*> Source = Query.SectionTag.IsValid()
		? Inventory->GetItemsInSection(Query.SectionTag)
		: Inventory->GetItems();

	return FilterAndSort(Source, Query);
}

TArray<UNexusItemInstance*> UNexusInventoryQueryLibrary::QueryContainer(const UNexusItemContainer* Container,
	const FNexusItemQuery& Query)
{
	if (!Container) return TArray<UNexusItemInstance*>();

	TArray<UNexusItemInstance*> Source;
	if (Query.SectionTag.IsValid())
	{
		Container->GetItemsInSection(Query.SectionTag, Source);
	}
	else
	{
		Source = Container->GetItems();
	}

	return FilterAndSort(Source, Query);
}

int32 UNexusInventoryQueryLibrary::CountMatching(const UNexusInventoryComponent* Inventory, const FNexusItemQuery& Query)
{
	if (!Inventory) return 0;

	const TArray<UNexusItemInstance*> Source = Query.SectionTag.IsValid()
		? Inventory->GetItemsInSection(Query.SectionTag)
		: Inventory->GetItems();

	int32 Count = 0;
	for (const UNexusItemInstance* Instance : Source)
	{
		if (Instance && MatchesFilters(Instance, Query))
		{
			++Count;
		}
	}
	return Count;
}

bool UNexusInventoryQueryLibrary::MatchesFilters(const UNexusItemInstance* Instance, const FNexusItemQuery& Query)
{
	if (!Instance) return false;
	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return false;

	// Advanced category match (empty query passes everything).
	if (!Query.CategoryQuery.IsEmpty() && !Query.CategoryQuery.Matches(Definition->CategoryTags))
	{
		return false;
	}

	if (Query.IdentityTag.IsValid() && !Definition->IdentityTag.MatchesTagExact(Query.IdentityTag))
	{
		return false;
	}

	if (!Query.NameContains.IsEmpty())
	{
		const FString Haystack = Definition->DisplayName.ToString();
		if (!Haystack.Contains(Query.NameContains.ToString(), ESearchCase::IgnoreCase))
		{
			return false;
		}
	}

	if (Query.RequiresStatTag.IsValid() && !Instance->HasStat(Query.RequiresStatTag))
	{
		return false;
	}

	return true;
}

TArray<UNexusItemInstance*> UNexusInventoryQueryLibrary::SortItems(const TArray<UNexusItemInstance*>& Items,
	ENexusItemSortMode SortMode)
{
	TArray<UNexusItemInstance*> Result = Items;
	SortInPlace(Result, SortMode);
	return Result;
}

TArray<UNexusItemInstance*> UNexusInventoryQueryLibrary::FilterAndSort(const TArray<UNexusItemInstance*>& Items,
	const FNexusItemQuery& Query)
{
	TArray<UNexusItemInstance*> Result;
	Result.Reserve(Items.Num());
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && MatchesFilters(Instance, Query))
		{
			Result.Add(Instance);
		}
	}

	SortInPlace(Result, Query.SortMode);
	return Result;
}

void UNexusInventoryQueryLibrary::SortInPlace(TArray<UNexusItemInstance*>& Items, ENexusItemSortMode SortMode)
{
	if (SortMode == ENexusItemSortMode::None || Items.Num() < 2) return;

	// Sell value can sync-load socketed gems, so precompute it once per item rather than
	// re-evaluating it inside every comparison.
	TMap<const UNexusItemInstance*, int64> ValueKeys;
	if (SortMode == ENexusItemSortMode::ValueDescending || SortMode == ENexusItemSortMode::ValueAscending)
	{
		ValueKeys.Reserve(Items.Num());
		for (const UNexusItemInstance* Instance : Items)
		{
			ValueKeys.Add(Instance, UNexusItemEconomyLibrary::GetSellValue(Instance));
		}
	}

	// Likewise precompute display names once: DisplayName.ToString() heap-allocates an
	// FString, and comparing at sort time would do it twice per comparison — O(N log N)
	// allocations across the sort. Mirrors the value-key precompute above.
	TMap<const UNexusItemInstance*, FString> NameKeys;
	if (SortMode == ENexusItemSortMode::NameAscending || SortMode == ENexusItemSortMode::NameDescending)
	{
		NameKeys.Reserve(Items.Num());
		for (const UNexusItemInstance* Instance : Items)
		{
			if (Instance) NameKeys.Add(Instance, DisplayNameOf(*Instance));
		}
	}

	// StableSort preserves acquisition order among equal keys. TArray::StableSort
	// dereferences the pointers, so the predicate takes instances by reference.
	Items.StableSort([SortMode, &ValueKeys, &NameKeys](const UNexusItemInstance& A, const UNexusItemInstance& B) -> bool
	{
		switch (SortMode)
		{
		case ENexusItemSortMode::NameAscending:
		case ENexusItemSortMode::NameDescending:
		{
			// Compare cached strings by pointer — no per-comparison ToString() allocation.
			const FString* NA = NameKeys.Find(&A);
			const FString* NB = NameKeys.Find(&B);
			const int32 Cmp = (NA && NB) ? NA->Compare(*NB, ESearchCase::IgnoreCase) : 0;
			return SortMode == ENexusItemSortMode::NameAscending ? Cmp < 0 : Cmp > 0;
		}
		case ENexusItemSortMode::ValueDescending:    return ValueKeys.FindRef(&A) > ValueKeys.FindRef(&B);
		case ENexusItemSortMode::ValueAscending:     return ValueKeys.FindRef(&A) < ValueKeys.FindRef(&B);
		case ENexusItemSortMode::FootprintDescending: return FootprintAreaOf(A) > FootprintAreaOf(B);
		case ENexusItemSortMode::StackDescending:    return A.GetStackCount() > B.GetStackCount();
		default:                                     return false;
		}
	});
}
