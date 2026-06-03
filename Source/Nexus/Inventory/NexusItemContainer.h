#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemInstance.h"

#include "NexusItemContainer.generated.h"

class UNexusItemDefinition;
class UNexusItemInstance;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChanged, UNexusItemInstance*, Instance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);


USTRUCT(BlueprintType)
struct NEXUS_API FNexusAddItemResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 AmountAdded = 0;

	/** Count that could not be placed (weight or slot limits). */
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 Remainder = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UNexusItemInstance*> AffectedInstances;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<UNexusItemInstance*> NewInstances;

	bool IsEmpty() const { return AmountAdded == 0; }
};


/** How a section stores its items. */
UENUM(BlueprintType)
enum class ENexusSectionPlacement : uint8
{
	/** The attaché "Tetris" grid — items occupy a rectangular footprint and are packed spatially. */
	Spatial UMETA(DisplayName = "Spatial Grid"),
	/** A non-spatial ordered list (Key Items, Treasures) that consumes zero grid cells. */
	List    UMETA(DisplayName = "List"),
};


/**
 * One section of a sectioned container. An item routes to the first section whose
 * AcceptedCategoryTags intersects its CategoryTags; a section with empty
 * AcceptedCategoryTags is the catch-all (place it last). The genre model: one Spatial
 * grid section (space is the scarcity) plus N List sections (Key Items, Treasures) that
 * cost no grid cells.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusInventorySectionConfig
{
	GENERATED_BODY()

	/** Identity key for UI queries and routing. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Section",
		meta = (Categories = "Item.Section"))
	FGameplayTag SectionTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Section")
	ENexusSectionPlacement Placement = ENexusSectionPlacement::Spatial;

	/**
	 * Item category tags this section accepts. Empty = catch-all (accepts anything not
	 * claimed by an earlier section); keep the catch-all section last in the list.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Section",
		meta = (Categories = "Item.Category"))
	FGameplayTagContainer AcceptedCategoryTags;
};


/**
 * The inventory's storage + placement core, extracted from UNexusInventoryComponent
 * so the *same* class backs both the player's actor-scoped attaché case (owned by the
 * component) and the subsystem-scoped item box (owned off any world actor by
 * UNexusItemContainerSubsystem). A plain UObject — never a UActorComponent — so it can
 * live wherever its owner does, which is exactly what the box's save/subsystem scope
 * needs.
 *
 * Owns the live UNexusItemInstance list, the attaché grid, the deferred-broadcast
 * scope, and the flat-descriptor save bridge. Every mutator runs inside an
 * FBroadcastScope and coalesces into per-item events plus exactly one aggregate
 * (see FlushPendingChanges); no mutator broadcasts mid-operation.
 *
 * Decoupling: a leaf. It references item definitions / instances / fragments only —
 * never equipment, merchant, attachment, or UI. Consumers observe the delegates and
 * call the public API; nothing reaches into Items. The owning component re-broadcasts
 * these delegates as its own, so external listeners keep binding to
 * UNexusInventoryComponent::OnItem* exactly as before.
 */
UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced)
class NEXUS_API UNexusItemContainer : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Set the capacity model. Called by the owner before the container is used
	 * (the component in BeginPlay, the box subsystem on init). Safe to re-call to
	 * re-tune; it never touches contents.
	 */
	void Configure(int32 InGridWidth, int32 InGridHeight, float InWeightCapacity,
		bool bInUnlimitedWeight, int32 InMaxItemsPerAddCall);

	/**
	 * Set the section layout. An empty list is normalized to a single Spatial catch-all
	 * (Item.Section.Grid) so an unconfigured container behaves like the old fixed grid.
	 * Safe to call before items exist (the owner does so on init).
	 */
	void ConfigureSections(const TArray<FNexusInventorySectionConfig>& InSections);

	// Add/Remove — see UNexusInventoryComponent for the per-method contract these back.
	FNexusAddItemResult AddItem(UNexusItemDefinition* Definition, int32 Count);
	bool AddInstance(UNexusItemInstance* Instance);
	bool RemoveInstance(UNexusItemInstance* Instance);
	void ClearAll();
	int32 RemoveFromInstance(UNexusItemInstance* Instance, int32 Count);

	// Utility
	const TArray<UNexusItemInstance*>& GetItems() const { return ObjectPtrDecay(Items); }
	int32 GetTotalCountForDefinition(const UNexusItemDefinition* Definition) const;
	int32 GetTotalCountForIdentityTag(FGameplayTag IdentityTag) const;
	int32 GetTotalCountForCategory(FGameplayTag CategoryTag) const;
	UNexusItemInstance* FindFirstByDefinition(const UNexusItemDefinition* Definition) const;
	UNexusItemInstance* FindFirstByIdentityTag(FGameplayTag IdentityTag) const;
	UNexusItemInstance* FindInstanceByGuid(FGuid InstanceGuid) const;

	template <typename T>
	void ForEachInstanceWithFragment(TFunctionRef<void(UNexusItemInstance*, const T&)> Fn) const;

	// Capacity
	float GetUsedWeight() const { return CachedUsedWeight; }
	float GetWeightCapacity() const { return WeightCapacity; }
	int32 GetSlotCount() const { return Items.Num(); }
	FIntPoint GetGridSize() const { return FIntPoint(GridWidth, GridHeight); }
	int32 GetRemainingCapacityForDefinition(const UNexusItemDefinition* Definition) const;

	// Sections
	const TArray<FNexusInventorySectionConfig>& GetSections() const { return Sections; }
	/** The section a definition / instance routes to (its SectionTag), or an invalid tag. */
	FGameplayTag GetSectionForDefinition(const UNexusItemDefinition* Definition) const;
	FGameplayTag GetSectionForInstance(const UNexusItemInstance* Instance) const;
	/** True if SectionTag is a configured Spatial-grid section. */
	bool IsSpatialSection(FGameplayTag SectionTag) const;
	/** Held items routed to SectionTag, in Items order (list sections are ordered/append). */
	void GetItemsInSection(FGameplayTag SectionTag, TArray<UNexusItemInstance*>& OutItems) const;

	// Grid (attaché model)
	bool CanPlaceAt(FIntPoint Footprint, FIntPoint TopLeft, const UNexusItemInstance* IgnoreInstance = nullptr) const;
	bool MoveItemTo(UNexusItemInstance* Instance, FIntPoint TopLeft, bool bRotated);
	UNexusItemInstance* GetItemAt(FIntPoint Cell) const;
	TArray<FIntPoint> GetOccupiedCells(const UNexusItemInstance* Instance) const;

	/**
	 * Repack every spatially-placed item via first-fit-decreasing (largest first), so the
	 * grid's free space coalesces. Computed on a scratch grid and applied only if every
	 * item still fits (it always should — same items, same grid), coalescing the moves
	 * into one broadcast batch. Returns false without mutating if the repack can't place
	 * an item. The attaché "Optimize" / auto-sort button.
	 */
	bool OptimizeSpatialSection();

	/** Set grid dimensions without re-laying-out (items keep their positions). Used on load. */
	void SetGridDimensions(int32 NewWidth, int32 NewHeight);

	/**
	 * Resize the spatial grid and re-pack every spatial item (first-fit-decreasing). Items
	 * that no longer fit are removed from this container (firing OnItemRemoved) and returned
	 * in OutOverflow for the caller to redeposit — the case-swap spill path (auto-send to
	 * the item box). List sections are untouched.
	 */
	void ResizeGrid(int32 NewWidth, int32 NewHeight, TArray<UNexusItemInstance*>& OutOverflow);

	// Save bridge — the owner persists these flat descriptors (the component through EMS,
	// the box through a custom save game). The live Items pointers never round-trip; these
	// descriptors do.
	void CaptureSaveData(TArray<FNexusItemSaveData>& OutSaved) const;
	void RestoreFromSaveData(const TArray<FNexusItemSaveData>& InSaved);

	// Delegates — the owning component binds these and re-broadcasts as its own, so the
	// external contract (UNexusInventoryComponent::OnItem*) is unchanged.
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemChanged;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

private:
	static int32 GetMaxStackForDefinition(const UNexusItemDefinition* Definition);

	/**
	 * First-fit free grid region for an item of UnrotatedSize cells, trying the
	 * unrotated orientation then the 90°-rotated one. Returns false if nothing fits.
	 */
	bool FindFreePlacement(FIntPoint UnrotatedSize, FIntPoint& OutTopLeft, bool& bOutRotated) const;

	/** Index into Sections an item of Definition routes to (first accepting / catch-all). */
	int32 ResolveSectionIndexForDefinition(const UNexusItemDefinition* Definition) const;
	bool IsDefinitionSpatial(const UNexusItemDefinition* Definition) const;

	/**
	 * First-fit a W×H rect on a scratch occupancy grid: scans row-major, and on the first
	 * free region marks it occupied and returns its top-left. Shared by the repack paths
	 * (Optimize / ResizeGrid). False if nothing fits.
	 */
	bool ScratchPlace(TArray<bool>& Occupied, int32 W, int32 H, FIntPoint& OutPos) const;

	UFUNCTION()
	void HandleInstanceChanged(UNexusItemInstance* Instance);
	void BindInstance(UNexusItemInstance* Instance);
	void UnbindInstance(UNexusItemInstance* Instance);

	/** Live container contents. Rebuilt from save descriptors on restore; not itself persisted. */
	UPROPERTY()
	TArray<TObjectPtr<UNexusItemInstance>> Items;

	/** Section layout, set by ConfigureSections(). Never empty after configure (catch-all grid). */
	TArray<FNexusInventorySectionConfig> Sections;

	// Capacity model, set by Configure(). Defaults mirror the historical component values
	// so a container queried before Configure behaves identically to the old fixed grid.
	int32 GridWidth = 8;
	int32 GridHeight = 6;
	float WeightCapacity = 0.0f;
	bool bUnlimitedWeight = true;
	int32 MaxItemsPerAddCall = 10000;

	float CachedUsedWeight = 0.0f;

#if !UE_BUILD_SHIPPING
	/** Dev-only: ensures the incrementally-maintained CachedUsedWeight has not drifted from
	 *  the true sum over Items. Catches a future mutator that forgets to update the cache. */
	void VerifyWeightInvariant() const;
#endif

	struct FPendingChange
	{
		TWeakObjectPtr<UNexusItemInstance> Instance;
		bool bAdded   = false;
		bool bRemoved = false;
	};
	TArray<FPendingChange> PendingChanges;
	int32 BroadcastDeferDepth = 0;
	bool bFlushInProgress = false;

	void EnqueueChange(UNexusItemInstance* Instance, bool bAdded, bool bRemoved);
	void FlushPendingChanges();

	/** RAII guard: defers broadcasts until the outermost guard exits. */
	struct FBroadcastScope
	{
		UNexusItemContainer* Owner;
		explicit FBroadcastScope(UNexusItemContainer* InOwner) : Owner(InOwner)
		{
			++Owner->BroadcastDeferDepth;
		}
		~FBroadcastScope()
		{
			if (--Owner->BroadcastDeferDepth == 0)
			{
				Owner->FlushPendingChanges();
			}
		}
	};
};

#if CPP
#include "Nexus/Inventory/NexusItemContainer.inl"
#endif
