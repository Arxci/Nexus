// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EMSCompSaveInterface.h"
#include "NexusAbilitySystemComponent.generated.h"

class ACharacter;
class AController;
class UNexusAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStateChanged, UNexusAbility*, Ability);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTagChanged, FGameplayTag, Tag, bool, bAdded);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusAbilitySystemComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()
	
	friend class UNexusAbility;

public:
	UNexusAbilitySystemComponent();

	void InitAbilityActorInfo(AController* InController);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;

	
	//Ability Lifecycle
	/**
	* Grant an ability to the owner of this ASC. Necessary to call before activating an ability
	* @param AbilityClass the class reference for the NexusAbility to give.
	**/
	UFUNCTION(BlueprintCallable, Category="Ability System")
	UNexusAbility* GiveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	/**
	* Removes a granted ability from this ASC. Force-ends it if active, broadcasts
	* OnAbilityRemoved, and erases the instance from the granted-abilities map so a
	* later GiveAbility of the same class produces a fresh instance (no stale
	* cooldown / activation state carried over from the previous grant).
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool RemoveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void ClearAbilities();

	/**
	* Activate a granted ability using the abilities class reference
	* @param InAbilityToActivate the class reference for the NexusAbility to activate
	* @return True if the ability was granted successfully.
	**/
	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryActivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToActivate);

	/**
	* Activate a granted ability using an associated InAbilityTag. Useful for avoiding a direct reference to an ability.
	* @param InAbilityTag the tag reference for the NexusAbility to activate
	* @return True if the ability was activated successfully.
	**/
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool TryActivateAbilityByTag(FGameplayTag InAbilityTag);

	/**
	* Deactivate a granted ability using the abilities class reference
	* @param InAbilityToDeactivate the class reference for the NexusAbility to deactivate
	* @return True if the ability was deactivated successfully.
	**/
	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryDeactivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToDeactivate);

	/**
	* Deactivate a granted ability using an associated InAbilityTag. Useful for avoiding a direct reference to an ability.
	* @param InAbilityTag the tag reference for the NexusAbility to deactivate
	* @return True if the ability was deactivated successfully.
	**/
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool TryDeactivateAbilityByTag(FGameplayTag InAbilityTag);

	/**
	* Deactivates all active abilities.
	**/
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void DeactivateAllAbilities();

	/**
	 * Force-end an active ability by tag via CommitAbilityEnd (not Request flow).
	 * Intended for load-time reconciliation where we need a guaranteed synchronous end.
	 * * @param InAbilityTag the tag reference for the NexusAbility to end.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool ForceEndAbilityByTag(FGameplayTag InAbilityTag);
	

	//Utility
	/**
	* Returns a reference to the controller that possessed the owning pawn.
	**/
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	AController* GetController() const { return CachedController; }
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	UNexusAbility* FindAbilityByClass(TSubclassOf<UNexusAbility> AbilityClass) const;
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool IsAbilityActive(TSubclassOf<UNexusAbility> AbilityClass) const;

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool IsAbilityActiveByTag(FGameplayTag AbilityTag) const;
	
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	TArray<UNexusAbility*> GetActiveAbilities() const;

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	TArray<UNexusAbility*> GetGivenAbilities() const;

	
	//Delegates
	UPROPERTY(BlueprintAssignable)
    FOnAbilityStateChanged OnAbilityActivated;

    UPROPERTY(BlueprintAssignable)
    FOnAbilityStateChanged OnAbilityDeactivated;

	/** Broadcast only on the first-time grant of an ability class. Re-enabling via SetAbilityEnabled does not re-broadcast. */
	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityGiven;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Ability System")
	FOnTagChanged OnTagChanged;

	
	//Tags
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

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// EMS Component Save Interface
	virtual void ComponentPreSave_Implementation() override;
	virtual void ComponentSaved_Implementation() override;
	virtual void ComponentPreLoad_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;

	UPROPERTY(Transient)
	AController* CachedController = nullptr;

	UPROPERTY(SaveGame)
	TMap<TSubclassOf<UNexusAbility>, TObjectPtr<UNexusAbility>> GrantedAbilities;

	/**
	 * Per-class grant counts. Each GiveAbility increments; each RemoveAbility
	 * decrements. The instance only leaves GrantedAbilities at zero. This lets
	 * two independent sources (e.g. two equipped slots) both grant Fire without
	 * the first one's unequip stripping the ability the second still needs.
	 */
	UPROPERTY(Transient)
	TMap<TSubclassOf<UNexusAbility>, int32> AbilityGrantCounts;

	UFUNCTION()
	void HandleAbilityActivated(UNexusAbility* InAbility);
	UFUNCTION()
	void HandleAbilityDeactivated(UNexusAbility* InAbility);
	
private:
	/**
	 * Ref-counts per tag. Each AddTags call (from ability activation or
	 * AddLooseGameplayTag) increments; each RemoveTags decrements. The tag
	 * only leaves OwnedTags when the count hits zero. This lets two abilities
	 * apply the same tag simultaneously without one's deactivation stomping
	 * the other's state.
	 */
	UPROPERTY(SaveGame)
	TMap<FGameplayTag, int32> TagRefCounts;
	UPROPERTY(SaveGame)
	FGameplayTagContainer OwnedTags;

	void CancelAbilitiesWithTags(const FGameplayTagContainer& Tags);
	void AddTags(const FGameplayTagContainer& Tags);
	void RemoveTags(const FGameplayTagContainer& Tags);
	bool CheckTagRequirements(const UNexusAbility* Ability) const;
};
