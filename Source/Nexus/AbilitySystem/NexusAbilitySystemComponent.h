// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMSCompSaveInterface.h"
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

USTRUCT()
struct FNexusAbilitySaveEntry
{
	GENERATED_BODY()

	/** The ability class that was granted. Soft so saves survive class moves / renames. */
	UPROPERTY(SaveGame)
	TSoftClassPtr<UNexusAbility> AbilityClass;

	/** Mirrors UNexusAbility::bIsEnabled at the moment of save. */
	UPROPERTY(SaveGame)
	bool bEnabled = true;

	/**
	 * How many seconds of cooldown were left at save time. On restore we
	 * rebuild CooldownEndTime = WorldTime + this value, so reloading resumes
	 * the cooldown from where it was.
	 */
	UPROPERTY(SaveGame)
	float CooldownTimeRemaining = 0.0f;
};

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

	/**
	 * Enable or disable an already-granted ability. Disabling an ability
	 * forcibly ends it if it is currently Active or Ending. Abilities in this
	 * system are pooled for the lifetime of the ASC — there is no true
	 * "remove" operation; use this instead.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void SetAbilityEnabled(TSubclassOf<UNexusAbility> AbilityClass, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	void DeactivateAllAbilities(bool bForce = false);
	
	/**
	 * Request deactivation of an ability.
	 *
	 * When bForce is false (the default), the ability is given a chance to
	 * wind down gracefully: it transitions to Ending, OnEndAbilityRequested
	 * fires, and the commit is deferred if the ability wants to wait on an
	 * external state. When bForce is true the ability is torn down
	 * unconditionally — use this for EndPlay, death/respawn,
	 * SetAbilityEnabled(false), and anywhere else you cannot tolerate an
	 * ability refusing to end.
	 */
	void DeactivateAbility(UNexusAbility* Ability, bool bForce = false);

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

	/** Broadcast only on the first-time grant of an ability class. Re-enabling via SetAbilityEnabled does not re-broadcast. */
	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityGiven;

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

	/** Route a "pressed" input event. Activates all granted abilities whose InputTag matches. */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Input")
	void AbilityInputPressed(FGameplayTag InputTag);

	/** Route a "released" input event. Deactivates any active abilities whose InputTag matches. */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Input")
	void AbilityInputReleased(FGameplayTag InputTag);

	/**
	 * Route a "toggle" input event. For each granted ability whose InputTag
	 * matches: if the ability is currently Active or Ending it is
	 * deactivated, otherwise it is activated. Use this when input routing
	 * should flip an ability's state on a single input event instead of
	 * requiring a matching release.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Input")
	void AbilityInputToggled(FGameplayTag InputTag);

	// --- Easy Multi Save integration ---

	/**
	 * Captures per-ability state into SavedAbilityState so EMS can serialize
	 * it. Fired automatically from ComponentPreSave; exposed for tests and
	 * for any code path that wants a manual snapshot.
	 */
	void CaptureSaveState();

	/**
	 * Restores per-ability state from SavedAbilityState. Called automatically
	 * from ComponentLoaded. Safe to call more than once — abilities are
	 * granted idempotently via GiveAbility().
	 */
	void RestoreSaveState();

	// --- IEMSCompSaveInterface ---

	virtual void ComponentPreSave_Implementation() override;
	virtual void ComponentLoaded_Implementation() override;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(Transient)
	AController* CachedController = nullptr;

	UPROPERTY()
	TMap<TSubclassOf<UNexusAbility>, TObjectPtr<UNexusAbility>> GrantedAbilities;

	UFUNCTION(BlueprintCallable, Category="Ability System")
	ENexusAbilityActivationResult TryActivateAbilityByClassWithResult(TSubclassOf<UNexusAbility> InAbilityToActivate);

	/**
	 * Persisted ability state, one entry per granted ability class. Populated
	 * by CaptureSaveState(), consumed by RestoreSaveState(). EMS writes this
	 * to disk because of the SaveGame property flag.
	 */
	UPROPERTY(SaveGame)
	TArray<FNexusAbilitySaveEntry> SavedAbilityState;
	
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

	/**
	 * Commits final teardown of an ability: flips state to Idle, removes
	 * owned tags, fires OnDeactivateAbility, broadcasts, and starts the
	 * cooldown if applicable. Called by the ability itself via EndAbility()
	 * when it is ready to actually end, and by DeactivateAbility() when a
	 * forced or non-deferred deactivation has been requested.
	 *
	 * This is an internal path — only UNexusAbility (friend) and the ASC
	 * itself should call it. Gameplay code should call DeactivateAbility /
	 * TryDeactivateAbilityByClass instead.
	 */
	void CommitAbilityEnd(UNexusAbility* Ability);
	
	void AddTags(const FGameplayTagContainer& Tags);
	void RemoveTags(const FGameplayTagContainer& Tags);
	bool CheckTagRequirements(const UNexusAbility* Ability) const;
	void CancelAbilitiesWithTags(const FGameplayTagContainer& Tags);
};
