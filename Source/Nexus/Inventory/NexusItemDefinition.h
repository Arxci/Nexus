#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "NexusItemFragment.h"
#include "NexusItemDefinition.generated.h"

class UTexture2D;
class UStaticMesh;

/**
 * Authoritative description of an item type. One asset per concrete item
 * (e.g. DA_Item_Pistol_M1911, DA_Item_Ammo_9mm, DA_Item_Herb_Green).
 *
 * Composition over inheritance: capabilities are added by appending fragments
 * to the Fragments array. A pistol has Equippable + Weapon. A herb has
 * Stackable + Consumable + Combinable. Adding a new capability never
 * requires touching the definition class itself.
 */
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Identity")
	TSoftObjectPtr<UTexture2D> Icon;

	// Inventory footprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Inventory", meta = (ClampMin = "0.0"))
	float Weight = 0.0f;

	/** If true, dropped on death into a pickup actor instead of being destroyed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Inventory")
	bool bDropOnDeath = true;

	// Pickup visuals (optional — used by the generic ANexusItemPickup actor)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Pickup")
	TSoftObjectPtr<UStaticMesh> PickupMesh;

	// Fragments
	/**
	 * Capabilities authored as data. Use TInstancedStruct so the editor surfaces a
	 * type picker. Query with FindFragment<T>() or FindFragmentMutable<T>().
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item|Fragments",
		meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FNexusItemFragment>> Fragments;

	/** First fragment of T, or nullptr. */
	template <typename T>
	const T* FindFragment() const
	{
		static_assert(TIsDerivedFrom<T, FNexusItemFragment>::IsDerived, "T must derive from FNexusItemFragment");
		for (const TInstancedStruct<FNexusItemFragment>& Frag : Fragments)
		{
			if (Frag.IsValid() && Frag.GetScriptStruct()->IsChildOf(T::StaticStruct()))
			{
				return Frag.template GetPtr<T>();
			}
		}
		return nullptr;
	}

	/** True if any fragment of T is present. */
	template <typename T>
	bool HasFragment() const
	{
		return FindFragment<T>() != nullptr;
	}
};