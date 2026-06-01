#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Treasure.generated.h"


/**
 * One gem socket on a treasure. A gem whose CategoryTags include AcceptedGemCategory may be
 * socketed into SocketTag; the socketed gem's identity is stored per-instance (in the item's
 * SocketedItems map, keyed by SocketTag) and its value adds to the treasure's sell value.
 */
USTRUCT(BlueprintType, DisplayName = "Treasure Socket")
struct NEXUS_API FNexusTreasureSocket
{
	GENERATED_BODY()

	/** Identity of this socket on the treasure (the per-instance SocketedItems key). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket",
		meta = (Categories = "Treasure.Socket"))
	FGameplayTag SocketTag;

	/** Gem category this socket accepts (e.g. Item.Category.Gem). Empty = accepts any item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Socket",
		meta = (Categories = "Item.Category"))
	FGameplayTag AcceptedGemCategory;
};


/**
 * Marks an item as a treasure — a sellable valuable routed to the Treasures list section
 * (via Item.Category.Treasure on the definition). Its base value is the definition's
 * BaseValue; this fragment adds optional gem sockets and a set-bonus tag.
 *
 * Socketing a gem raises the treasure's combined sell value and persists per-instance; the
 * value is computed on demand from the definition base plus the socketed gems (see
 * UNexusItemEconomyLibrary::GetSellValue), so there is no cached value to drift. A socketed
 * treasure carries per-instance state and therefore never auto-merges (IsMergeableStack).
 */
USTRUCT(BlueprintType, DisplayName = "Treasure")
struct NEXUS_API FNexusFragment_Treasure : public FNexusItemFragment
{
	GENERATED_BODY()

	/** Gem sockets this treasure exposes. Empty = a plain treasure with no sockets. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Treasure")
	TArray<FNexusTreasureSocket> Sockets;

	/** Bonus added to the sell value when every socket is filled (RE-style completion bonus). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Treasure", meta = (ClampMin = "0"))
	int32 FullSocketBonus = 0;

	/** Optional set membership for a future set-bonus system. Data only in v1. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Treasure",
		meta = (Categories = "Treasure.Set"))
	FGameplayTag SetBonusTag;
};
