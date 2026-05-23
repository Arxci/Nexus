#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "StructUtils/InstancedStruct.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusItemDefinition.generated.h"

class UTexture2D;
class UStaticMesh;


UCLASS(BlueprintType)
class NEXUS_API UNexusItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
	// Identity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Identity",
		meta = (Categories = "Item.Identity"))
	FGameplayTag IdentityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Identity",
		meta = (Categories = "Item.Category"))
	FGameplayTagContainer CategoryTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Identity")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Identity", meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Identity",
		meta = (AssetBundles = "UI"))
	TSoftObjectPtr<UTexture2D> Icon;

	// Inventory footprint
	/**
	 * Grid footprint in cells (Width x Height), unrotated — the attaché-case model.
	 * Most consumables/ammo are 1x1; long guns are larger (e.g. 1x3). The inventory
	 * packs items spatially against this; a stack occupies one footprint regardless
	 * of stack count. Clamped to a minimum of 1x1 at read sites.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Inventory")
	FIntPoint GridSize = FIntPoint(1, 1);

	/** Optional secondary scarcity axis; off unless the inventory enforces weight. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Inventory", meta = (ClampMin = "0.0"))
	float Weight = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Inventory")
	bool bDropOnDeath = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Pickup",
		meta = (AssetBundles = "Pickup"))
	TSoftObjectPtr<UStaticMesh> PickupMesh;

	// Fragments
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Fragments",
		meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FNexusItemFragment>> Fragments;

	template <typename T>
	const T* FindFragment() const
	{
		static_assert(TIsDerivedFrom<T, FNexusItemFragment>::IsDerived,
			"T must derive from FNexusItemFragment");

		const UScriptStruct* Target = T::StaticStruct();
		for (const TInstancedStruct<FNexusItemFragment>& Frag : Fragments)
		{
			if (!Frag.IsValid()) continue;
			const UScriptStruct* Type = Frag.GetScriptStruct();
			if (Type && Type->IsChildOf(Target))
			{
				return Frag.GetPtr<const T>();
			}
		}
		return nullptr;
	}

	template <typename T>
	bool HasFragment() const
	{
		return FindFragment<T>() != nullptr;
	}
};