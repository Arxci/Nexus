#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GameplayTagContainer.h"

#include "EMSCompSaveInterface.h"

#include "Nexus/Inventory/NexusItemInstance.h"

#include "NexusInventoryComponent.generated.h"

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
	const TArray<UNexusItemInstance*>& GetItems() const
	{
		return ObjectPtrDecay(Items);
	}

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
	float GetWeightCapacity() const { return WeightCapacity; }

	/** Number of distinct items/stacks held (not cells occupied). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	int32 GetSlotCount() const { return Items.Num(); }

	/** Grid dimensions in cells (Width, Height). */
	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	FIntPoint GetGridSize() const { return FIntPoint(GridWidth, GridHeight); }

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

public:
	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryItemChanged OnItemChanged;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

protected:
	virtual void BeginPlay() override;

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

	/** Live inventory contents. Rebuilt from SavedItems on load; not itself persisted. */
	UPROPERTY()
	TArray<TObjectPtr<UNexusItemInstance>> Items;

	/**
	 * Serialized snapshot of the inventory. Populated in ComponentPreSave and consumed
	 * in ComponentLoaded; transient at all other times. The live Items array holds
	 * runtime subobjects whose pointers cannot round-trip through EMS (it serializes a
	 * UObject* as a path and LoadSynchronous-resolves it, which is null for a transient
	 * per-item subobject) — so persistence goes through these flat descriptors instead.
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

private:
	static int32 GetMaxStackForDefinition(const UNexusItemDefinition* Definition);

	/**
	 * First-fit free grid region for an item of UnrotatedSize cells, trying the
	 * unrotated orientation then the 90°-rotated one. Returns false if nothing fits.
	 */
	bool FindFreePlacement(FIntPoint UnrotatedSize, FIntPoint& OutTopLeft, bool& bOutRotated) const;

	UFUNCTION()
	void HandleInstanceChanged(UNexusItemInstance* Instance);
	void BindInstance(UNexusItemInstance* Instance);
	void UnbindInstance(UNexusItemInstance* Instance);

	float CachedUsedWeight = 0.0f;

#if !UE_BUILD_SHIPPING
	/** Dev-only: ensures the incrementally-maintained CachedUsedWeight has not
	 *  drifted from the true sum over Items. Catches a future mutator that forgets
	 *  to update the cache. Compiled out of shipping. */
	void VerifyWeightInvariant() const;
#endif

private:
	struct FPendingChange
	{
		TWeakObjectPtr<UNexusItemInstance> Instance;
		bool bAdded   = false;
		bool bRemoved = false;
	};
	TArray<FPendingChange> PendingChanges;
	int32 BroadcastDeferDepth = 0;
	bool bFlushInProgress = false;

	void EnqueueChange(UNexusItemInstance* Instance, const bool bAdded, const bool bRemoved);
	void FlushPendingChanges();

	/** RAII guard: defers broadcasts until the outermost guard exits. */
	struct FBroadcastScope
	{
		UNexusInventoryComponent* Owner;
		explicit FBroadcastScope(UNexusInventoryComponent* InOwner) : Owner(InOwner)
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
#include "Nexus/Inventory/NexusInventoryComponent.inl"
#endif