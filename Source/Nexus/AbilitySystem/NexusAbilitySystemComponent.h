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

	void InitAbilityActorInfo(AController* InController);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

	// --- Getters ---

    UFUNCTION(BlueprintCallable, Category = "Ability System")
    AActor* GetAvatarActor() const { return GetOwner(); }

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	AController* GetController() const { return CachedController; }

	// --- Ability Lifecycle ---

	UFUNCTION(BlueprintCallable, Category="Ability System")
	UNexusAbility* GiveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryActivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToActivate);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryDeactivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToDeactivate);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void SetAbilityEnabled(TSubclassOf<UNexusAbility> AbilityClass, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void DeactivateAllAbilities();
	
	void DeactivateAbility(UNexusAbility* Ability);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTag);

	/** Deactivate all active abilities whose AbilityTags contain the given tag */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool TryDeactivateAbilityByTag(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool RemoveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	// --- Ability Queries ---
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	UNexusAbility* FindAbilityByClass(TSubclassOf<UNexusAbility> AbilityClass) const;
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool IsAbilityActive(TSubclassOf<UNexusAbility> AbilityClass) const;

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool IsAbilityActiveByTag(FGameplayTag AbilityTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	TArray<UNexusAbility*> GetActiveAbilities() const;

	// --- Delegates ---

	UPROPERTY(BlueprintAssignable)
    FOnAbilityStateChanged OnAbilityActivated;

    UPROPERTY(BlueprintAssignable)
    FOnAbilityStateChanged OnAbilityDeactivated;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityGiven;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityRemoved;

	// --- Tags ---

	/** Check whether the component currently has a specific tag */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool HasTag(FGameplayTag Tag) const;

	/** Check whether the component currently has ALL the specified tags */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool HasAllTags(const FGameplayTagContainer& TagContainer) const;

	/** Check whether the component currently has ANY of the specified tags */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool HasAnyTags(const FGameplayTagContainer& TagContainer) const;

	/** Get the current owned tags */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	FGameplayTagContainer GetOwnedTags() const;

	/** Add a loose gameplay tag. Increments the tag's ref count. */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void AddLooseGameplayTag(FGameplayTag Tag);

	/** Remove a loose gameplay tag. Decrements the tag's ref count. */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void RemoveLooseGameplayTag(FGameplayTag Tag);

	UPROPERTY(BlueprintAssignable, Category = "Ability System")
	FOnTagChanged OnTagChanged;

	// Input Routing

	UFUNCTION(BlueprintCallable, Category = "Ability System|Input")
	void AbilityInputPressed(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable, Category = "Ability System|Input")
	void AbilityInputReleased(FGameplayTag InputTag);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(Transient)
	AController* CachedController = nullptr;

	UPROPERTY()
	TMap<TSubclassOf<UNexusAbility>, TObjectPtr<UNexusAbility>> GrantedAbilities;

private:
	TMap<FGameplayTag, int32> TagRefCounts;
	FGameplayTagContainer OwnedTags;


	void AddTags(const FGameplayTagContainer& Tags);
	void RemoveTags(const FGameplayTagContainer& Tags);
	bool CheckTagRequirements(const UNexusAbility* Ability) const;
	void CancelAbilitiesWithTags(const FGameplayTagContainer& Tags);
};
