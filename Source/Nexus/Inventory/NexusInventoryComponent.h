#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GameplayTagContainer.h"

#include "EMSCompSaveInterface.h"

#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/NexusItemContainer.h"

#include "NexusInventoryComponent.generated.h"

class UNexusItemDefinition;
class UNexusItemInstance;
class UNexusItemContainer;

// FNexusAddItemResult, FOnInventoryItemChanged and FOnInventoryChanged are declared in
// NexusItemContainer.h (the storage core). The component re-exposes them unchanged.


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusInventoryComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusInventoryComponent();

public:
	// Add/Remove
	//
	// To give an item to a pawn, prefer UNexusInventoryAcquireLibrary::AcquireItem —
	// it is the canonical entry point and also handles mark-seen, stat seeding, and
	// auto-equip. The methods below are the lower-level primitives it builds on:
	//   - AddItem        : create count-many of a definition, with stack-merging and
	//                      partial fill against capacity. The standard "spawn items".
	//   - AddItemSimple  : thin Blueprint convenience over AddItem returning only the
	//                      amount added. Identical rules to AddItem.
	//   - AddInstance    : adopt an existing instance (e.g. transfer from a stash /
	//                      item box). All-or-nothing, never stack-merges — the caller
	//                      owns an already-built instance and wants this exact object
	//                      placed. Do NOT use it as a substitute for AddItem.
	//
	// These forward to the owned UNexusItemContainer, which is the actual storage core.

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FNexusAddItemResult AddItem(UNexusItemDefinition* Definition, int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory", meta = (DisplayName = "Add Item (Simple)"))
	int32 AddItemSimple(UNexusItemDefinition* Definition, const int32 Count)
	{
		return AddItem(Definition, Count).AmountAdded;
	}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddInstance(UNexusItemInstance* Instance);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveInstance(UNexusItemInstance* Instance);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearAll();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 RemoveFromInstance(UNexusItemInstance* Instance, int32 Count);

public:
	// Utility
	UFUNCTION(BlueprintPure, Category = "Inventory")
	const TArray<UNexusItemInstance*>& GetItems() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalCountForDefinition(const UNexusItemDefinition* Definition) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalCountForIdentityTag(FGameplayTag IdentityTag) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetTotalCountForCategory(FGameplayTag CategoryTag) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UNexusItemInstance* FindFirstByDefinition(const UNexusItemDefinition* Definition) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UNexusItemInstance* FindFirstByIdentityTag(FGameplayTag IdentityTag) const;

	/**
	 * Find a held instance by its stable GUID. Used by other save-aware systems
	 * (e.g. the equipment component) to re-resolve their references to specific
	 * instances after a load, since the GUID survives the save round-trip but the
	 * runtime pointer does not.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UNexusItemInstance* FindInstanceByGuid(FGuid InstanceGuid) const;

	template <typename T>
	void ForEachInstanceWithFragment(TFunctionRef<void(UNexusItemInstance*, const T&)> Fn) const;

	// First-pickup ceremony tracking
	/**
	 * Per-save record of which item definitions the player has ever picked up
	 * from the world. Pickup actors gate their first-time-ceremony anim on this —
	 * the long, cinematic pickup montage only plays the first time. Subsequent
	 * pickups (debug spawns, dropped copies, loot from a body) skip the
	 * ceremony so it doesn't feel intrusive once the player has seen it.
	 *
	 * This is player-inventory bookkeeping, not container contents, so it stays on
	 * the component rather than the shared storage core.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|FirstPickup")
	bool HasSeenItemDefinition(const UNexusItemDefinition* Definition) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory|FirstPickup")
	void MarkItemDefinitionSeen(const UNexusItemDefinition* Definition);

public:
	//Capacity
	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	float GetUsedWeight() const;

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	float GetWeightCapacity() const;

	/** Number of distinct items/stacks held (not cells occupied). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	int32 GetSlotCount() const;

	/** Grid dimensions in cells (Width, Height). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	FIntPoint GetGridSize() const;

	/**
	 * How many more of Definition AddItem could place right now: stack room on
	 * existing mergeable stacks plus first-fit packing into free cells, clamped by
	 * weight if enforced. Mirrors AddItem's merge-then-place rule, so
	 * AddItem(Definition, GetRemainingCapacityForDefinition(Definition)) places
	 * everything and leaves no remainder. 0 means a pickup would be fully rejected —
	 * UI can grey it out. Result is exact, not an estimate; it runs the same
	 * first-fit placement AddItem uses on a scratch occupancy grid.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	int32 GetRemainingCapacityForDefinition(const UNexusItemDefinition* Definition) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "1"))
	int32 MaxItemsPerAddCall = 10000;

public:
	// Grid (attaché model)
	/**
	 * True if an item of Footprint cells placed with its top-left at TopLeft fits
	 * in-bounds and overlaps no other placed item. IgnoreInstance is excluded from
	 * the overlap test — pass the instance being moved so it doesn't collide with
	 * its own current cells.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Grid")
	bool CanPlaceAt(FIntPoint Footprint, FIntPoint TopLeft, const UNexusItemInstance* IgnoreInstance = nullptr) const;

	/**
	 * Move/rotate an already-held item to a new grid position (the manual-rearrange
	 * path for the attaché UI). Returns false if the item isn't held or the target
	 * region is out of bounds or occupied.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Grid")
	bool MoveItemTo(UNexusItemInstance* Instance, FIntPoint TopLeft, bool bRotated);

	/**
	 * The item occupying Cell, or null if the cell is empty or out of bounds. The
	 * grid UI's primary query — hover, drag-target, right-click all start here so
	 * callers don't re-implement the footprint overlap test.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Grid")
	UNexusItemInstance* GetItemAt(FIntPoint Cell) const;

	/** Every grid cell Instance currently occupies. Empty if it isn't held or isn't placed. */
	UFUNCTION(BlueprintPure, Category = "Inventory|Grid")
	TArray<FIntPoint> GetOccupiedCells(const UNexusItemInstance* Instance) const;

	/**
	 * Repack the spatial section via first-fit-decreasing so free cells coalesce (the
	 * attaché "Optimize" button). No-op-safe; returns false only if a repack somehow
	 * can't fit the current items, in which case the layout is left untouched.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Grid")
	bool OptimizeSpatialSection();

public:
	// Sections (grid vs Key Items / Treasures lists)
	/** The section SectionTag a held instance routes to, or an invalid tag. */
	UFUNCTION(BlueprintPure, Category = "Inventory|Sections")
	FGameplayTag GetSectionForInstance(const UNexusItemInstance* Instance) const;

	/** True if SectionTag is a configured spatial-grid section (vs a non-spatial list). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Sections")
	bool IsSpatialSection(FGameplayTag SectionTag) const;

	/** Held items routed to SectionTag, in order. The section-aware UI query (grid vs lists). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Sections")
	TArray<UNexusItemInstance*> GetItemsInSection(FGameplayTag SectionTag) const;

public:
	// Case & charms
	/** The equipped case instance (drives grid size + charm slots), or null. */
	UFUNCTION(BlueprintPure, Category = "Inventory|Case")
	UNexusItemInstance* GetEquippedCase() const { return EquippedCase; }

	UFUNCTION(BlueprintPure, Category = "Inventory|Case")
	UNexusItemDefinition* GetEquippedCaseDefinition() const;

	/**
	 * Equip CaseDef as the attaché case: re-sizes the spatial grid to the case's GridSize
	 * and re-packs. Items that no longer fit are returned (the caller — the container
	 * subsystem's SwapCase — redeposits them into the item box, per the spill policy).
	 * Equipping a different case starts with empty charm slots. Returns the overflow.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Case")
	TArray<UNexusItemInstance*> SetEquippedCase(UNexusItemDefinition* CaseDef);

	/** Charm slots the equipped case exposes (empty if no case / no slots). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Case")
	FGameplayTagContainer GetCaseCharmSlots() const;

	/**
	 * Socket CharmDef into SlotTag on the equipped case. Rejected if there's no case, the
	 * slot isn't one the case exposes, or CharmDef has no Charm fragment. Persists per
	 * case instance; the effect is applied by the case-charm consumer (later phase).
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Case")
	bool SocketCharm(FGameplayTag SlotTag, UNexusItemDefinition* CharmDef);

	UFUNCTION(BlueprintCallable, Category = "Inventory|Case")
	bool UnsocketCharm(FGameplayTag SlotTag);

	UFUNCTION(BlueprintPure, Category = "Inventory|Case")
	UNexusItemDefinition* GetSocketedCharm(FGameplayTag SlotTag) const;

public:
	//Delegates — re-broadcast from the owned container so external listeners keep
	// binding to the component exactly as before (the equipment component depends on
	// OnItemRemoved firing on inventory removal).
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemChanged;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

	/**
	 * Fires when the equipped case or its charm sockets change (case swap, socket/unsocket,
	 * save-restore). The charm consumer (the equipment component) listens and re-applies the
	 * socketed charms' passive effects through the host ASC — the same path armor uses.
	 * Inventory stays a leaf: it announces the change and is done.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Inventory|Case")
	FOnInventoryChanged OnEquippedCaseChanged;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//~Start save interface
	virtual void ComponentPreSave_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;
	//~End save interface

protected:
	/**
	 * Inventory grid dimensions in cells (the attaché-case capacity model). Items
	 * occupy a rectangular footprint and the player packs them spatially; total
	 * capacity is GridWidth * GridHeight cells. Tune per design — a tighter grid is
	 * more tension. These are the primary scarcity axis (weight is optional/off).
	 *
	 * These authoring values seed the storage container's grid in BeginPlay.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "1"))
	int32 GridWidth = 8;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "1"))
	int32 GridHeight = 6;

	/**
	 * Maximum carried weight. Authoritative only when bUnlimitedWeight is false.
	 * Weight is the genre's *secondary* axis — RE7/Village gate on space, not weight —
	 * so it defaults OFF. Opt in by setting bUnlimitedWeight = false AND a positive
	 * WeightCapacity. (Leaving bUnlimitedWeight true while setting a capacity is a
	 * no-op and is warned about at BeginPlay.)
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "0.0", EditCondition = "!bUnlimitedWeight"))
	float WeightCapacity = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity")
	bool bUnlimitedWeight = true;

	/**
	 * Section layout, routed by item CategoryTags. Seeds the container in BeginPlay.
	 * Defaults (set in the constructor) to the player-case layout: a Key Items list +
	 * a Treasures list (both zero grid cells) + the spatial grid catch-all, in that
	 * order. NPC / loot / box containers can override to a single section. Leave empty
	 * for an implicit single spatial catch-all.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Sections")
	TArray<FNexusInventorySectionConfig> Sections;

	/**
	 * Optional starting case. When set, it is equipped in BeginPlay and its FNexusFragment_Case
	 * GridSize drives the spatial grid (overriding GridWidth/GridHeight, which then act only
	 * as the no-case fallback). Leave unset to keep the fixed GridWidth x GridHeight grid.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Case")
	TSoftObjectPtr<UNexusItemDefinition> DefaultCaseDefinition;

	/** The equipped case instance — drives grid size + charm slots. Not part of the grid contents. */
	UPROPERTY()
	TObjectPtr<UNexusItemInstance> EquippedCase;

	/** Persisted snapshot of the equipped case (definition + charm sockets). */
	UPROPERTY(SaveGame)
	FNexusItemSaveData SavedCase;

	/**
	 * Serialized snapshot of the inventory. Populated in ComponentPreSave from the
	 * container and consumed in ComponentLoaded to restore it; transient otherwise.
	 * The container's live Items hold runtime subobjects whose pointers cannot
	 * round-trip through EMS (it serializes a UObject* as a path and
	 * LoadSynchronous-resolves it, which is null for a transient per-item subobject) —
	 * so persistence goes through these flat descriptors instead.
	 */
	UPROPERTY(SaveGame)
	TArray<FNexusItemSaveData> SavedItems;

	/**
	 * PrimaryAssetIds of every item definition the player has ever picked up.
	 * Saved with the inventory so the first-pickup ceremony only fires once per
	 * save. Keyed by PrimaryAssetId (not raw definition pointer) so the set
	 * survives asset moves/renames as long as the asset registry path stays.
	 */
	UPROPERTY(SaveGame)
	TSet<FPrimaryAssetId> SeenItemDefinitions;

	/**
	 * The storage + placement core (Items, grid, broadcast scope, save descriptors).
	 * A plain UObject so the same class can also back the off-actor item box. The
	 * component is a thin actor-side wrapper: it forwards the public API, bridges EMS
	 * save/load, and re-broadcasts the container's events as its own.
	 *
	 * MUST be Instanced: without it the engine pointer-copies the CDO's container
	 * subobject into every spawned instance, so every Hero across every PIE writes
	 * into the same CDO-owned Items array. Instanced tells UE to deep-copy the CDO
	 * subobject per outer instance — pairs with UCLASS(EditInlineNew,
	 * DefaultToInstanced) on UNexusItemContainer.
	 */
	UPROPERTY(Instanced)
	TObjectPtr<UNexusItemContainer> Container;

private:
	// Re-broadcast the container's coalesced events as the component's own delegates.
	UFUNCTION()
	void HandleContainerItemAdded(UNexusItemInstance* Instance);
	UFUNCTION()
	void HandleContainerItemRemoved(UNexusItemInstance* Instance);
	UFUNCTION()
	void HandleContainerItemChanged(UNexusItemInstance* Instance);
	UFUNCTION()
	void HandleContainerInventoryChanged();

	/** Rebuild EquippedCase from SavedCase on load and size the grid to it; no-op if none saved. */
	void RestoreEquippedCaseFromSave();
};

#if CPP
#include "Nexus/Inventory/NexusInventoryComponent.inl"
#endif
