#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NexusItemInstance.generated.h"

class UNexusItemDefinition;

/**
 * Per-pickup runtime state for an item.
 *
 * Two instances of the same definition (e.g. two pistols) differ only by
 * StatTags (current ammo, durability, ...) and StackCount. Mutable per-instance
 * data lives in StatTags so that fragments can stay shareable, side-effect-free
 * data classes.
 *
 * Persisted as instanced UObjects via UEMSFunctionLibrary::SaveRawObject by the
 * owning UNexusInventoryComponent — same pattern used by the ASC for granted
 * abilities (NexusAbilitySystemComponent.cpp:399).
 */
UCLASS(BlueprintType)
class NEXUS_API UNexusItemInstance : public UObject
{
	GENERATED_BODY()

public:
	UNexusItemInstance();

	/** One-time setup. Resolves Definition synchronously and runs fragment initializers. */
	void Initialize(UNexusItemDefinition* InDefinition, int32 InStackCount = 1);

	UFUNCTION(BlueprintPure, Category = "Item")
	UNexusItemDefinition* GetDefinition() const;

	UFUNCTION(BlueprintPure, Category = "Item")
	FGameplayTag GetIdentityTag() const;

	/**
	 * Stable identity assigned at Initialize-time, persisted in SaveGame.
	 * Used as the EMS save-key so this instance's StatTags survive save/load
	 * regardless of UObject auto-name churn.
	 */
	UFUNCTION(BlueprintPure, Category = "Item")
	FGuid GetInstanceGuid() const { return InstanceGuid; }

	// Stack
	UFUNCTION(BlueprintPure, Category = "Item|Stack")
	int32 GetStackCount() const { return StackCount; }

	/** Adds Delta (can be negative). Returns the actual delta applied (clamped to MaxStack and >=0). */
	int32 ModifyStack(int32 Delta, int32 MaxStack = MAX_int32);

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

protected:
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