#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "NexusInventoryQueryLibrary.generated.h"

class UNexusInventoryComponent;
class UNexusItemContainer;
class UNexusItemInstance;


/** Ordering applied to a query result. */
UENUM(BlueprintType)
enum class ENexusItemSortMode : uint8
{
	/** Keep inventory order (acquisition order; stable). */
	None              UMETA(DisplayName = "None (inventory order)"),
	NameAscending     UMETA(DisplayName = "Name (A-Z)"),
	NameDescending    UMETA(DisplayName = "Name (Z-A)"),
	/** Combined sell value (treasure sockets included), highest first — the merchant view. */
	ValueDescending   UMETA(DisplayName = "Value (high-low)"),
	ValueAscending    UMETA(DisplayName = "Value (low-high)"),
	/** Grid footprint area, largest first — useful for packing decisions. */
	FootprintDescending UMETA(DisplayName = "Size (large-small)"),
	/** Stack count, biggest stacks first. */
	StackDescending   UMETA(DisplayName = "Stack (high-low)"),
};


/**
 * A composable inventory search. Every field is optional and ANDed together; an empty
 * query matches every item. Bundled into a struct so a search UI can build one value and
 * adding a future criterion doesn't break call sites (mirrors FNexusAcquireParams).
 *
 * This is the "advanced search" surface — CategoryQuery is a full FGameplayTagQuery, so a
 * filter UI can express "weapons AND NOT broken", "consumables OR ammo", etc. over the
 * item's CategoryTags without any code change.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusItemQuery
{
	GENERATED_BODY()

	/**
	 * Advanced tag match against the definition's CategoryTags. An empty query passes
	 * everything; otherwise the item's CategoryTags must satisfy the expression
	 * (All/Any/None of …). The primary filter.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Query")
	FGameplayTagQuery CategoryQuery;

	/** Exact identity match (e.g. a specific item). Invalid = ignore. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Query",
		meta = (Categories = "Item.Identity"))
	FGameplayTag IdentityTag;

	/** Restrict to one section (grid / Key Items / Treasures). Invalid = all sections. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Query",
		meta = (Categories = "Item.Section"))
	FGameplayTag SectionTag;

	/** Case-insensitive substring of the display name. Empty = ignore. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Query")
	FText NameContains;

	/**
	 * Require the instance to carry this per-instance stat tag (e.g. Stat.Durability for
	 * "items with condition", or an upgrade tag for "upgraded weapons"). Invalid = ignore.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Query",
		meta = (Categories = "Stat"))
	FGameplayTag RequiresStatTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Query")
	ENexusItemSortMode SortMode = ENexusItemSortMode::None;
};


/**
 * Read-only search/sort over an inventory's items. A pure consumer of the public API
 * (GetItems / GetItemsInSection) — it holds no state and the inventory knows nothing about
 * it, so the component stays UI-shape-agnostic. Linear over the item list (the right cost
 * at this genre's scale); see the container's mutation choke points if an index is ever
 * needed.
 */
UCLASS()
class NEXUS_API UNexusInventoryQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Filtered + sorted items from a pawn's inventory component. */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Query")
	static TArray<UNexusItemInstance*> QueryInventory(const UNexusInventoryComponent* Inventory,
		const FNexusItemQuery& Query);

	/** Same query against a raw container (e.g. the item box from the container subsystem). */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Query")
	static TArray<UNexusItemInstance*> QueryContainer(const UNexusItemContainer* Container,
		const FNexusItemQuery& Query);

	/** Number of instances in Inventory matching Query (ignores SortMode). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Query")
	static int32 CountMatching(const UNexusInventoryComponent* Inventory, const FNexusItemQuery& Query);

	/**
	 * True if a single instance satisfies the query's filters (CategoryQuery, IdentityTag,
	 * NameContains, RequiresStatTag). SectionTag is not applied here — it needs a container
	 * for context — so a UI can use this to highlight/grey a known item.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Query")
	static bool MatchesFilters(const UNexusItemInstance* Instance, const FNexusItemQuery& Query);

	/** Sort a given item list by SortMode (returns a sorted copy; stable). */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Query")
	static TArray<UNexusItemInstance*> SortItems(const TArray<UNexusItemInstance*>& Items,
		ENexusItemSortMode SortMode);

private:
	/** Filter Items by the query's predicates (not section) then sort. */
	static TArray<UNexusItemInstance*> FilterAndSort(const TArray<UNexusItemInstance*>& Items,
		const FNexusItemQuery& Query);

	static void SortInPlace(TArray<UNexusItemInstance*>& Items, ENexusItemSortMode SortMode);
};
