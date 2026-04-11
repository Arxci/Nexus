// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NexusAbility.generated.h"


UENUM(BlueprintType)
enum class ENexusAbilityActivationState : uint8
{
	Idle    UMETA(DisplayName = "Idle"),
	Active  UMETA(DisplayName = "Active"),
	Ending  UMETA(DisplayName = "Ending"),
};

/**
 * Result returned from UNexusAbility::OnEndAbilityRequested.
 *
 * CommitNow              - Tear the ability down immediately. The ASC will
 *                          call CommitAbilityEnd as soon as the request
 *                          returns.
 * DeferUntilEndAbility   - Keep the ability in the Ending state. The ability
 *                          is responsible for calling EndAbility() on itself
 *                          once whatever it is waiting on has resolved
 *                          (capsule resize, montage finishing, tag drop, ...).
 */
UENUM(BlueprintType)
enum class ENexusEndRequestResult : uint8
{
	CommitNow             UMETA(DisplayName = "Commit Now"),
	DeferUntilEndAbility  UMETA(DisplayName = "Defer Until EndAbility"),
};

/**
 * Controls when the cooldown timer starts ticking.
 *
 * OnActivate - Cooldown begins the moment the ability activates. Use this
 *              for "this ability can re-fire every N seconds regardless of
 *              how long it runs."
 * OnEnd      - Cooldown begins when the ability finishes. Use this for
 *              "after this ability ends, wait N seconds before it can fire
 *              again."
 */
UENUM(BlueprintType)
enum class ENexusCooldownStartPolicy : uint8
{
	OnActivate  UMETA(DisplayName = "On Activate"),
	OnEnd       UMETA(DisplayName = "On End"),
};

/**
 * Controls what happens when TryActivate is called on an ability that is
 * already Active or Ending.
 *
 * OnceAtATime    - Activation fails with AlreadyActive. Use for toggle-style
 *                  abilities (crouch, run, aim).
 * Retrigger      - The running instance is force-ended and the ability is
 *                  re-activated from scratch. Use for "fire weapon"-style
 *                  abilities that should always respond to input.
 * IgnoreIfActive - Activation silently succeeds without disturbing the
 *                  running instance. Use when re-pressing the input should
 *                  be a no-op (e.g. a channelled ability that keeps going).
 */
UENUM(BlueprintType)
enum class ENexusAbilityInstancePolicy : uint8
{
	OnceAtATime     UMETA(DisplayName = "Once At A Time"),
	Retrigger       UMETA(DisplayName = "Retrigger"),
	IgnoreIfActive  UMETA(DisplayName = "Ignore If Active"),
};

UCLASS(Blueprintable)
class NEXUS_API UNexusAbility : public UObject
{
	GENERATED_BODY()

	friend class UNexusAbilitySystemComponent;

public:
	UNexusAbility();
	
	virtual void OnActivateAbility();

	/**
	 * Called when the ability has been asked to wind down (by input release,
	 * another ability cancelling it, or a forced teardown). Override this to
	 * defer actual teardown until some external state has caught up — for
	 * example, waiting for a capsule resize, an animation montage, or a
	 * gameplay tag transition.
	 *
	 * @param bForce  True when the ability is being torn down unconditionally
	 *                (EndPlay, RemoveAbility, death/respawn, SetAbilityEnabled
	 *                (false)). Synchronously unbind any listeners and abandon
	 *                pending waits — the ASC will commit the teardown as soon
	 *                as this returns, regardless of what you return.
	 * @return true to defer commit until the ability calls EndAbility() on
	 *         itself. false to let the ASC commit teardown immediately. When
	 *         bForce is true the return value is ignored.
	 */
	virtual ENexusEndRequestResult OnEndAbilityRequested(bool bForce);
	
	virtual void OnDeactivateAbility();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System|Abilities",
		meta = (DisplayName = "On Activate Ability", ScriptName = "OnActivateAbility"))
	void K2_OnAbilityActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System|Abilities",
		meta = (DisplayName = "On Deactivate Ability", ScriptName = "OnDeactivateAbility"))
	void K2_OnAbilityDeactivated();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability System|Abilities")
	bool CanActivateAbility() const;
	virtual bool CanActivateAbility_Implementation() const;

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	void EndAbility();

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	UNexusAbilitySystemComponent* GetNexusAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
    AActor* GetAvatarActor() const;

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	AController* GetController() const;

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	ENexusAbilityActivationState GetActivationState() const { return ActivationState; }

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	bool IsEnabled() const { return bIsEnabled; }

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	bool IsActive() const { return ActivationState == ENexusAbilityActivationState::Active; }

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	bool IsEnding() const { return ActivationState == ENexusAbilityActivationState::Ending; }

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	bool IsIdle() const { return ActivationState == ENexusAbilityActivationState::Idle; }


	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	bool IsOnCooldown() const;

	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	float GetCooldownRemaining() const;

	/** Returns 0.0 when cooldown just started, 1.0 when finished */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	float GetCooldownProgress() const;

	/** Manually start the cooldown timer. Called automatically by the component based on bStartCooldownOnEnd. */
	UFUNCTION(BlueprintCallable, Category = "Ability System|Abilities")
	void CommitCooldown();

	bool GetCanTick() const { return bCanTick; }

	ENexusAbilityInstancePolicy GetInstancePolicy() const { return InstancePolicy; }
	
protected:
	virtual void TickAbility(float DeltaTime) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities") bool bCanTick = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Ability System|Abilities")
	ENexusAbilityActivationState ActivationState = ENexusAbilityActivationState::Idle;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System|Abilities")
	bool bIsEnabled = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer AbilityTags;

	/** Tags applied to the owning actor while this ability is active */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer ActivationOwnedTags;

	/** Tags that must ALL be present on the owner for activation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer ActivationRequiredTags;

	/** Tags that must ALL be absent from the owner for activation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer ActivationBlockedTags;

	/** On activation, cancel any active abilities whose AbilityTags match any of these tags */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer CancelAbilitiesWithTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities", meta = (ClampMin = "0.0"))
	float CooldownDuration = 0.0f;

	/** If true, cooldown starts when the ability ends. If false, cooldown starts on activation. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	bool bStartCooldownOnEnd = true;

	/** When the cooldown timer begins relative to the ability's lifecycle. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	ENexusCooldownStartPolicy CooldownStartPolicy = ENexusCooldownStartPolicy::OnEnd;

	/** What happens when TryActivate is called while this ability is already Active or Ending. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	ENexusAbilityInstancePolicy InstancePolicy = ENexusAbilityInstancePolicy::OnceAtATime;
private:
	float CooldownEndTime = 0.0f;
};
