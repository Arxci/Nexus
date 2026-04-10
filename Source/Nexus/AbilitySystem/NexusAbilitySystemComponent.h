// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "NexusAbilitySystemComponent.generated.h"

class ACharacter;
class AController;
class UNexusAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStateChanged, UNexusAbility*, Ability);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTagChanged, FGameplayTag, Tag, bool, bAdded);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNexusAbilitySystemComponent();

	void InitAbilityActorInfo(ACharacter* InCharacter);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	ACharacter* GetCharacter() const { return CachedCharacter; }

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	AController* GetController() const { return CachedController; }

	UFUNCTION(BlueprintCallable, Category="Ability System")
	UNexusAbility* GiveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryActivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToActivate);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryDeactivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToDeactivate);

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityActivated;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityDeactivated;

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void SetAbilityEnabled(TSubclassOf<UNexusAbility> AbilityClass, bool bEnabled);
	
	void DeactivateAbility(UNexusAbility* Ability);

	/** Check whether the component currently has a specific tag */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Tags")
	bool HasTag(FGameplayTag Tag) const;

	/** Check whether the component currently has ALL of the specified tags */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Tags")
	bool HasAllTags(const FGameplayTagContainer& TagContainer) const;

	/** Check whether the component currently has ANY of the specified tags */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Tags")
	bool HasAnyTags(const FGameplayTagContainer& TagContainer) const;

	/** Get the current owned tags */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Tags")
	FGameplayTagContainer GetOwnedTags() const;

	/** Add a loose gameplay tag. Increments the tag's ref count. */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Tags")
	void AddLooseGameplayTag(FGameplayTag Tag);

	/** Remove a loose gameplay tag. Decrements the tag's ref count. */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Tags")
	void RemoveLooseGameplayTag(FGameplayTag Tag);

	UPROPERTY(BlueprintAssignable, Category = "Ability System|Tags")
	FOnTagChanged OnTagChanged;

protected:
	UPROPERTY(Transient)
	ACharacter* CachedCharacter = nullptr;

	UPROPERTY(Transient)
	AController* CachedController = nullptr;

	UPROPERTY()
	TMap<TSubclassOf<UNexusAbility>, UNexusAbility*> GrantedAbilities;

private:
	/** Authoritative tag presence: count > 0 means tag is owned */
	TMap<FGameplayTag, int32> TagRefCounts;

	/** Cached container rebuilt whenever TagRefCounts changes */
	FGameplayTagContainer OwnedTags;

	/** Add all tags from a container, incrementing ref counts */
	void AddTags(const FGameplayTagContainer& Tags);

	/** Remove all tags from a container, decrementing ref counts */
	void RemoveTags(const FGameplayTagContainer& Tags);

	/** Check required/blocked tag conditions for an ability */
	bool CheckTagRequirements(const UNexusAbility* Ability) const;

	/** Cancel active abilities whose AbilityTags overlap with the given tags */
	void CancelAbilitiesWithTags(const FGameplayTagContainer& Tags);
};
