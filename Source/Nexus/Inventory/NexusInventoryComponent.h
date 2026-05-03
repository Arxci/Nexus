#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GameplayTagContainer.h"

#include "EMSCompSaveInterface.h"

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

	template <typename T>
	void ForEachInstanceWithFragment(TFunctionRef<void(UNexusItemInstance*, const T&)> Fn) const;

public:
	//Capacity
	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	float GetUsedWeight() const;

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	float GetWeightCapacity() const { return WeightCapacity; }

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	int32 GetSlotCount() const { return Items.Num(); }

	UFUNCTION(BlueprintPure, Category = "Inventory|Capacity")
	int32 GetSlotCapacity() const { return SlotCapacity; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "1"))
	int32 MaxItemsPerAddCall = 10000;

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
	//~Start save interface
	virtual void ComponentSaved_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;
	//~End save interface

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "0"))
	int32 SlotCapacity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Capacity", meta = (ClampMin = "0.0"))
	float WeightCapacity = 0.0f;

	UPROPERTY(SaveGame)
	TArray<TObjectPtr<UNexusItemInstance>> Items;

private:
	static int32 GetMaxStackForDefinition(const UNexusItemDefinition* Definition);

	UFUNCTION()
	void HandleInstanceChanged(UNexusItemInstance* Instance);
	void BindInstance(UNexusItemInstance* Instance);
	void UnbindInstance(UNexusItemInstance* Instance);
	
	float CachedUsedWeight = 0.0f;

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