#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NexusItemInstance.generated.h"

class UNexusItemDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemInstanceChanged, UNexusItemInstance*, Instance);

UCLASS(BlueprintType)
class NEXUS_API UNexusItemInstance : public UObject
{
	GENERATED_BODY()

public:
	UNexusItemInstance();
	
	void Initialize(UNexusItemDefinition* InDefinition, int32 InStackCount = 1);

	UFUNCTION(BlueprintPure, Category = "Item")
	UNexusItemDefinition* GetDefinition() const;

	UFUNCTION(BlueprintPure, Category = "Item")
	FGameplayTag GetIdentityTag() const;
	
	void RestoreLoadedState();
	
	UFUNCTION(BlueprintPure, Category = "Item")
	FGuid GetInstanceGuid() const { return InstanceGuid; }

	// Stack
	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	int32 GetStackCount() const { return StackCount; }

	/** Adds Delta (can be negative). Returns the actual delta applied (clamped to MaxStack and >=0). */
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


	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Item")
	FOnItemInstanceChanged OnInstanceChanged;

protected:
	void BroadcastChanged();
	bool bInitialized = false;
	
	/** Soft so the asset path is what's actually serialized — survives reorgs and partial loads. */
	UPROPERTY(SaveGame)
	TSoftObjectPtr<UNexusItemDefinition> DefinitionRef;

	UPROPERTY(SaveGame)
	FGuid InstanceGuid;

	UPROPERTY(SaveGame)
	int32 StackCount = 1;

	UPROPERTY(SaveGame)
	TMap<FGameplayTag, int32> StatTags;

	/** Hard ref kept while the instance is live; rehydrated on load via DefinitionRef. */
	UPROPERTY(Transient)
	TObjectPtr<UNexusItemDefinition> CachedDefinition;
};