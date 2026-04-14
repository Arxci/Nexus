// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NexusAbility.generated.h"

struct FNexusAbilitySaveData;

UENUM(BlueprintType)
enum class ENexusAbilityActivationState : uint8
{
	Idle    UMETA(DisplayName = "Idle"),
	Active  UMETA(DisplayName = "Active"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivationStateChanged, UNexusAbility*, Ability);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnabledStateChanged);

UCLASS(Blueprintable)
class NEXUS_API UNexusAbility : public UObject
{
	GENERATED_BODY()

	friend class UNexusAbilitySystemComponent;

public:
	UNexusAbility();

	//Ability life cycle
	virtual bool RequestActivateAbility();
	virtual bool RequestDeactivateAbility(bool bForce=false);
	
	virtual void OnEnableAbility();
	virtual void OnDisableAbility();

	/**
	* Override if you need custom activation checks. EX: checking if ammo is greater than 0.
	* Defaults to true.
	**/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Nexus Ability|Lifecycle")
	bool CanActivateAbility() const;
	virtual bool CanActivateAbility_Implementation() const;


	//Ability utility
	/**
	* Returns a reference to the NexusAbilitySystemComponent that manages this ability instance.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Util")
	UNexusAbilitySystemComponent* GetNexusAbilitySystemComponent() const;

	/**
	* Returns the actor that owns the NexusAbilitySystemComponent.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Util")
    AActor* GetOwner() const;

	/**
	* Returns the controller that owns the NexusAbilitySystemComponent.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Util")
	AController* GetController() const;


	// Ability state
	/**
	* Get the current activation state.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|State")
	ENexusAbilityActivationState GetActivationState() const { return ActivationState; }

	/**
	* Returns true if activation state == ACTIVE.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|State")
	bool IsActive() const { return ActivationState == ENexusAbilityActivationState::Active; }

	/**
	* Returns true if activation state == IDLE.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|State")
	bool IsIdle() const { return ActivationState == ENexusAbilityActivationState::Idle; }

	/**
	* Returns whether this ability is enabled.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|State")
	bool IsEnabled() const { return bIsEnabled; }

	
	// Cooldown
	/**
	* Returns true if this ability is currently on cooldown.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Cooldown")
	bool IsOnCooldown() const { return bIsOnCooldown; }

	/**
	* Returns true if this ability has a cooldown configured (flat duration > 0).
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Cooldown")
	bool HasCooldown() const;
	
	/**
	* Returns the total cooldown duration in seconds.
	* Uses the curve's max time if set, otherwise the flat CooldownDuration.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Cooldown")
	float GetCooldownTotalDuration() const;

	/**
	* Returns the remaining cooldown time in seconds. 0 if not on cooldown.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Cooldown")
	float GetCooldownTimeRemaining() const;

	/**
	* Returns normalized cooldown progress from 0.0 (just started) to 1.0 (complete).
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Cooldown")
	float GetCooldownProgress() const;

	
	//Delegates
	UPROPERTY(BlueprintAssignable)
	FActivationStateChanged OnActivated;

	UPROPERTY(BlueprintAssignable)
	FActivationStateChanged OnDeactivated;

	UPROPERTY(BlueprintAssignable)
	FEnabledStateChanged OnAbilityDisabled;

	UPROPERTY(BlueprintAssignable)
	FEnabledStateChanged OnAbilityEnabled;
	
protected:
	virtual void TickAbility(float DeltaTime) { K2_OnTickAbility(); }
	virtual bool CanTick() { return false; }
	
	/**
	* Called if an ability is enabled and active
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability",
		meta = (DisplayName = "On Tick Ability", ScriptName = "OnTickAbility"))
	void K2_OnTickAbility();

	//Ability life cycle
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Lifecycle")
	void CommitAbility();
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|Lifecycle")
	void CommitAbilityEnd();
	
	/**
	* Called once the ability has committed and is now active (state changed to Active).
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
	meta = (DisplayName = "On Ability Committed", ScriptName = "OnAbilityCommitted"))
	void K2_OnAbilityCommitted();
	/**
	* Called once the ability has ended and is now idle (state changed to Idle).
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
		meta = (DisplayName = "On Ability Ended", ScriptName = "OnAbilityEnded"))
	void K2_OnAbilityEnded();

	/**
	* Called once an ability activation request has been received from ASC. Expects CommitAbility to be called.
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
	meta = (DisplayName = "On Ability Activate", ScriptName = "OnAbilityActivate"))
	void K2_OnAbilityActivate();
	/**
	* Called once an ability deactivation request has been received from ASC. Expects CommitAbilityEnd to be called.
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
		meta = (DisplayName = "On Ability Deactivate", ScriptName = "OnAbilityDeactivate"))
	void K2_OnAbilityDeactivate();

	/**
	* Called once an ability has been enabled.
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
		meta = (DisplayName = "On Ability Enabled", ScriptName = "OnActivateEnabled"))
	void K2_OnAbilityEnabled();
	/**
	* Called once an ability has been disabled.
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
		meta = (DisplayName = "On Ability Disabled", ScriptName = "OnDeactivateDisabled"))
	void K2_OnAbilityDisabled();

	UPROPERTY(BlueprintReadOnly, Category = "Ability System|Abilities")
	bool bIsEnabled = true;

	
	//Tags
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer AbilityTags;

	/** Tags applied to the owning actor while this ability is active */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer ActivationOwnedTags;

	/** Tags that must ALL be present on the owning actor for activation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer ActivationRequiredTags;

	/** Tags that must ALL be absent from the owning actor for activation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer ActivationBlockedTags;

	/** On activation, cancel any active abilities whose AbilityTags match any of these tags */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTagContainer CancelAbilitiesWithTags;
	

	//Cooldown
	/** Flat cooldown duration in seconds. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Cooldown", meta = (ClampMin = "0.0"))
	float CooldownDuration = 0.0f;

	/** Start cooldown when the ability activates (CommitAbility). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Cooldown")
	bool bCooldownOnActivation = false;

	/** Start cooldown when the ability deactivates (CommitAbilityEnd). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Cooldown")
	bool bCooldownOnDeactivation = true;

	
	//Save/Restore
	/**
	 * Populates OutData with this ability's current state.
	 * Base implementation fills ActivationState, bIsEnabled, bIsOnCooldown,
	 * CooldownElapsed, and CooldownTotalDuration.
	 * Subclasses override to append custom state to OutData.CustomTags.
	 */
	virtual void CaptureSaveState(FNexusAbilitySaveData& OutData) const;

	/**
	 * Restores custom per-ability state from saved data.
	 * Called by the ASC after it has already restored base state
	 * (ActivationState, bIsEnabled, cooldown).
	 * Subclasses override to restore intent tags or other custom state.
	 */
	virtual void ApplySaveState(const FNexusAbilitySaveData& InData);

	/**
	 * Called after all abilities have had their state restored and ASC tags
	 * are consistent. Subclasses override to apply physical side effects
	 * (e.g. calling Char->Crouch()).
	 */
	virtual void OnSaveStateRestored();

private:
	ENexusAbilityActivationState ActivationState = ENexusAbilityActivationState::Idle;

	bool bIsOnCooldown = false;
	float CooldownElapsed = 0.0f;

	void StartCooldown();
	void TickCooldown(float DeltaTime);
};
