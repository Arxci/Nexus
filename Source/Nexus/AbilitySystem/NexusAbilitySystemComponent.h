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

UENUM(BlueprintType)
enum class ENexusAbilityActivationResult : uint8
{
	Success           UMETA(DisplayName = "Success"),
	InvalidClass      UMETA(DisplayName = "Invalid Class"),
	NotGranted        UMETA(DisplayName = "Not Granted"),
	Disabled          UMETA(DisplayName = "Disabled"),
	AlreadyActive     UMETA(DisplayName = "Already Active"),
	OnCooldown        UMETA(DisplayName = "On Cooldown"),
	TagsBlocked       UMETA(DisplayName = "Tags Blocked"),
	ConditionFailed   UMETA(DisplayName = "Condition Failed"),
};

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

	/**
	 * Avatar == Owner by design. The ASC lives on the Pawn, so ability state
	 * resets on death/respawn automatically. If you ever want state to outlive
	 * the Pawn (persistent buffs, XP, cross-respawn cooldowns), move the ASC
	 * to a PlayerState and split Avatar from Owner here.
	 */
    UFUNCTION(BlueprintCallable, Category = "Ability System")
    AActor* GetAvatarActor() const { return GetOwner(); }

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	AController* GetController() const { return CachedController; }

	// --- Ability Lifecycle ---

	UFUNCTION(BlueprintCallable, Category="Ability System")
	UNexusAbility* GiveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryActivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToActivate);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryDeactivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToDeactivate);

	/** Deactivate all active abilities whose AbilityTags contain the given tag */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	bool TryDeactivateAbilityByTag(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void SetAbilityEnabled(TSubclassOf<UNexusAbility> AbilityClass, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void DeactivateAllAbilities();
	
	void DeactivateAbility(UNexusAbility* Ability);
	
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

	/**
	 * Fired when a tag transitions on or off the ASC.
	 * Only broadcasts on the 0 → 1 add and the 1 → 0 removal.
	 * Redundant Adds/Removes (ref-count > 1) do NOT broadcast — this is
	 * intentional so listeners react once per "real" state change.
	 */
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

	UFUNCTION(BlueprintCallable, Category="Ability System")
	ENexusAbilityActivationResult TryActivateAbilityByClassWithResult(TSubclassOf<UNexusAbility> InAbilityToActivate);

private:
	/**
	 * Ref-counts per tag. Each AddTags call (from ability activation or
	 * AddLooseGameplayTag) increments; each RemoveTags decrements. The tag
	 * only leaves OwnedTags when the count hits zero. This lets two abilities
	 * apply the same tag simultaneously without one's deactivation stomping
	 * the other's state.
	 */
	TMap<FGameplayTag, int32> TagRefCounts;
	FGameplayTagContainer OwnedTags;
	
	void AddTags(const FGameplayTagContainer& Tags);
	void RemoveTags(const FGameplayTagContainer& Tags);
	bool CheckTagRequirements(const UNexusAbility* Ability) const;
	void CancelAbilitiesWithTags(const FGameplayTagContainer& Tags);
};
