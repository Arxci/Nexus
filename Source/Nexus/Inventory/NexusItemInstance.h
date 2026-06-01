#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "GameplayTagContainer.h"

#include "NexusItemInstance.generated.h"

class UNexusAttachmentDefinition;
class UNexusItemDefinition;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemInstanceChanged, UNexusItemInstance*, Instance);


/**
 * Stable, location-independent reference to an item instance: just its persistent GUID.
 * Cross-system links (equipment slot, quest, hotbar, a charm socketed in a case, a gem
 * socketed in a treasure) hold a handle rather than a raw UNexusItemInstance* — the GUID
 * survives the save round-trip and a transfer between containers, where a raw pointer does
 * not. Resolve it back to the live instance via UNexusItemContainerSubsystem (added with
 * the item box) or a known container's FindInstanceByGuid.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusItemHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = "Item")
	FGuid InstanceId;

	FNexusItemHandle() = default;
	explicit FNexusItemHandle(const FGuid& InInstanceId) : InstanceId(InInstanceId) {}

	bool IsValid() const { return InstanceId.IsValid(); }
	void Reset() { InstanceId.Invalidate(); }

	bool operator==(const FNexusItemHandle& Other) const { return InstanceId == Other.InstanceId; }
	bool operator!=(const FNexusItemHandle& Other) const { return !(*this == Other); }

	friend uint32 GetTypeHash(const FNexusItemHandle& Handle) { return GetTypeHash(Handle.InstanceId); }
};


/**
 * Flat, fully-serializable snapshot of a single item instance's persistent state.
 * This — not the live UNexusItemInstance pointer — is what the inventory writes to
 * its SaveGame data. EMS serializes a UObject* as a path and resolves it via
 * LoadSynchronous on load; a transient per-item subobject has no loadable path, so
 * persisting the live pointers would restore nothing. Instead we persist these
 * descriptors and rebuild the instances in ComponentLoaded (see
 * UNexusInventoryComponent::ComponentLoaded_Implementation).
 *
 * Every field is SaveGame-flagged because EMS serializes with a SaveGame-only
 * archive that filters per-property at each nesting level. The soft DefinitionRef
 * is run through the redirector resolver on load, so a renamed/moved definition
 * asset with a redirector still resolves.
 */
USTRUCT()
struct NEXUS_API FNexusItemSaveData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	TSoftObjectPtr<UNexusItemDefinition> DefinitionRef;

	UPROPERTY(SaveGame)
	FGuid InstanceGuid;

	UPROPERTY(SaveGame)
	int32 StackCount = 1;

	UPROPERTY(SaveGame)
	TMap<FGameplayTag, float> StatTags;

	UPROPERTY(SaveGame)
	TMap<FGameplayTag, TSoftObjectPtr<UNexusAttachmentDefinition>> Attachments;

	/**
	 * Items socketed into this instance's slots: charm slot tag -> charm definition on a
	 * case, gem socket tag -> gem definition on a treasure. Soft pointers so a non-active
	 * item doesn't pin its socketed assets.
	 */
	UPROPERTY(SaveGame)
	TMap<FGameplayTag, TSoftObjectPtr<UNexusItemDefinition>> SocketedItems;

	/** Top-left grid cell; (-1,-1) = not yet placed. */
	UPROPERTY(SaveGame)
	FIntPoint GridPosition = FIntPoint(-1, -1);

	UPROPERTY(SaveGame)
	bool bRotated = false;
};

UCLASS(BlueprintType)
class NEXUS_API UNexusItemInstance : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UNexusItemDefinition* InDefinition, int32 InStackCount = 1);

	/** Capture this instance's persistent state for the inventory's SaveGame data. */
	FNexusItemSaveData ToSaveData() const;

	/**
	 * Rebuild this instance from a saved snapshot during save-restore. Sync-loads
	 * the definition (safe — restore always runs behind a loading screen) and marks
	 * the instance live so subsequent mutations broadcast. Returns false if the
	 * saved definition asset no longer exists in the build; the caller drops the
	 * item from the restored inventory rather than carrying a defless instance.
	 */
	bool LoadFromSaveData(const FNexusItemSaveData& SaveData);

	UFUNCTION(BlueprintPure, Category = "Item")
	UNexusItemDefinition* GetDefinition() const;

	UFUNCTION(BlueprintPure, Category = "Item")
	FGameplayTag GetIdentityTag() const;
	
	UFUNCTION(BlueprintPure, Category = "Item")
	FGuid GetInstanceGuid() const { return InstanceGuid; }

	/** Stable, location-independent handle for cross-system references (see FNexusItemHandle). */
	UFUNCTION(BlueprintPure, Category = "Item")
	FNexusItemHandle GetHandle() const { return FNexusItemHandle(InstanceGuid); }


	// Grid placement (attaché model)
	UFUNCTION(BlueprintPure, Category = "Item|Grid")
	FIntPoint GetGridPosition() const { return GridPosition; }

	UFUNCTION(BlueprintPure, Category = "Item|Grid")
	bool IsRotated() const { return bRotated; }

	/** Effective footprint in cells, accounting for rotation (swaps W/H). Min 1x1. */
	UFUNCTION(BlueprintPure, Category = "Item|Grid")
	FIntPoint GetGridFootprint() const;

	/**
	 * Set by the owning inventory during placement / move. Intentionally does not
	 * broadcast — the inventory enqueues the change so a grid move coalesces with
	 * other inventory events through the broadcast scope.
	 */
	void SetGridPlacement(FIntPoint InPosition, bool bInRotated);


	// Stack
	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	int32 GetStackCount() const { return StackCount; }
	
	int32 ModifyStack(int32 Delta, int32 MaxStack = MAX_int32);

	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	bool CanStackWith(const UNexusItemInstance* Other) const;

	/**
	 * True when this instance carries no per-instance customization (no stat tags,
	 * no attachments) and may therefore merge into a like stack. The single source
	 * of truth for "is this a fungible stack" — used by both the inventory's merge
	 * path and CanStackWith so the two can never disagree.
	 */
	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	bool IsMergeableStack() const;

	const TMap<FGameplayTag, float>& GetStatTags() const { return StatTags; }

	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	bool IsEmpty() const { return StackCount <= 0; }


	// Stat tags
	UFUNCTION(BlueprintPure, Category = "Item|Stats")
	float GetStat(FGameplayTag StatTag, float Default = 0.0f) const;

	UFUNCTION(BlueprintCallable, Category = "Item|Stats")
	void SetStat(FGameplayTag StatTag, float Value);

	UFUNCTION(BlueprintCallable, Category = "Item|Stats")
	float ModifyStat(FGameplayTag StatTag, float Delta);

	UFUNCTION(BlueprintPure, Category = "Item|Stats")
	bool HasStat(FGameplayTag StatTag) const;


	// Attachments
	/**
	 * Persisted attachment configuration. Keyed by FAssemblySlotDefinition::SlotID
	 * (resolved against the equippable's slot tree). Soft pointers so non-equipped
	 * inventory items don't pin their attachment assets in memory; the
	 * UNexusAssemblyComponent loads them via the Asset Manager when the
	 * item is equipped.
	 *
	 * Nested attachments use dotted slot paths
	 * (e.g. "Attachment.Slot.UnderBarrel.Laser") so a single flat map can
	 * persist arbitrarily deep trees.
	 */
	UFUNCTION(BlueprintPure, Category = "Item|Attachments")
	TSoftObjectPtr<UNexusAttachmentDefinition> GetAttachmentForSlot(FGameplayTag SlotPath) const;

	UFUNCTION(BlueprintCallable, Category = "Item|Attachments")
	void SetAttachmentForSlot(FGameplayTag SlotPath, TSoftObjectPtr<UNexusAttachmentDefinition> Attachment);

	UFUNCTION(BlueprintCallable, Category = "Item|Attachments")
	void ClearAttachmentForSlot(FGameplayTag SlotPath);

	const TMap<FGameplayTag, TSoftObjectPtr<UNexusAttachmentDefinition>>& GetAttachmentMap() const
	{
		return Attachments;
	}

	// Sockets (charm slots on a case, gem sockets on a treasure)
	/**
	 * The item definition socketed in SlotTag, or null. The socketed item's identity is
	 * persisted per-instance, so a socketed treasure never auto-merges (IsMergeableStack)
	 * and the socket survives save/load.
	 */
	UFUNCTION(BlueprintPure, Category = "Item|Sockets")
	TSoftObjectPtr<UNexusItemDefinition> GetSocketedItem(FGameplayTag SlotTag) const;

	UFUNCTION(BlueprintCallable, Category = "Item|Sockets")
	void SetSocketedItem(FGameplayTag SlotTag, TSoftObjectPtr<UNexusItemDefinition> ItemDef);

	UFUNCTION(BlueprintCallable, Category = "Item|Sockets")
	void ClearSocketedItem(FGameplayTag SlotTag);

	const TMap<FGameplayTag, TSoftObjectPtr<UNexusItemDefinition>>& GetSocketedItemMap() const
	{
		return SocketedItems;
	}

	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Item")
	FOnItemInstanceChanged OnInstanceChanged;

protected:
	void BroadcastChanged();
	bool bInitialized = false;
	
	UPROPERTY(SaveGame)
	TSoftObjectPtr<UNexusItemDefinition> DefinitionRef;
	UPROPERTY(Transient)
	TObjectPtr<UNexusItemDefinition> CachedDefinition;

	UPROPERTY(SaveGame)
	FGuid InstanceGuid;

	UPROPERTY(SaveGame)
	int32 StackCount = 1;

	/**
	 * Mutable per-instance numeric state that persists with the item: ammo in the
	 * magazine today, weapon condition / durability in future. Float (not int) to
	 * match the GAS attribute convention and to allow continuous values; integer
	 * counts like ammo are stored as whole-number floats and rounded at read sites.
	 */
	UPROPERTY(SaveGame)
	TMap<FGameplayTag, float> StatTags;

	UPROPERTY(SaveGame)
	TMap<FGameplayTag, TSoftObjectPtr<UNexusAttachmentDefinition>> Attachments;

	/** Items socketed into this instance (charm slot -> charm def, gem socket -> gem def). */
	UPROPERTY(SaveGame)
	TMap<FGameplayTag, TSoftObjectPtr<UNexusItemDefinition>> SocketedItems;

	/** Top-left grid cell; (-1,-1) = not yet placed by the owning inventory. */
	UPROPERTY(SaveGame)
	FIntPoint GridPosition = FIntPoint(-1, -1);

	UPROPERTY(SaveGame)
	bool bRotated = false;

private:
	/**
	 * Held while this instance is alive. Keeps the Equipped bundle resident
	 * for as long as the player owns the item — covers carryover across
	 * chapters where the level manifest no longer lists this item. Released
	 * when the instance is GC'd (item removed from inventory or dropped).
	 *
	 * Only acquired for definitions with FNexusFragment_Equippable — ammo and
	 * consumables don't have an Equipped-bundle payload to load.
	 */
	TSharedPtr<FStreamableHandle> EquippedBundleHandle;

	void RequestEquippedBundleLoad();
};