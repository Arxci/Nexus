#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "GameplayTagContainer.h"

#include "NexusItemInstance.generated.h"

class UNexusAttachmentDefinition;
class UNexusItemDefinition;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemInstanceChanged, UNexusItemInstance*, Instance);

UCLASS(BlueprintType)
class NEXUS_API UNexusItemInstance : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UNexusItemDefinition* InDefinition, int32 InStackCount = 1);

	void RestoreLoadedState();

	UFUNCTION(BlueprintPure, Category = "Item")
	UNexusItemDefinition* GetDefinition() const;

	UFUNCTION(BlueprintPure, Category = "Item")
	FGameplayTag GetIdentityTag() const;
	
	UFUNCTION(BlueprintPure, Category = "Item")
	FGuid GetInstanceGuid() const { return InstanceGuid; }

	
	// Stack
	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	int32 GetStackCount() const { return StackCount; }
	
	int32 ModifyStack(int32 Delta, int32 MaxStack = MAX_int32);

	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	bool CanStackWith(const UNexusItemInstance* Other) const;

	const TMap<FGameplayTag, int32>& GetStatTags() const { return StatTags; }

	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	bool IsEmpty() const { return StackCount <= 0; }

	
	// Stat tags
	UFUNCTION(BlueprintPure, Category = "Item|Stats")
	int32 GetStat(FGameplayTag StatTag, int32 Default = 0) const;

	UFUNCTION(BlueprintCallable, Category = "Item|Stats")
	void SetStat(FGameplayTag StatTag, int32 Value);

	UFUNCTION(BlueprintCallable, Category = "Item|Stats")
	int32 ModifyStat(FGameplayTag StatTag, int32 Delta);

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

	UPROPERTY(SaveGame)
	TMap<FGameplayTag, int32> StatTags;

	UPROPERTY(SaveGame)
	TMap<FGameplayTag, TSoftObjectPtr<UNexusAttachmentDefinition>> Attachments;

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