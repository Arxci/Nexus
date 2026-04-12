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
	virtual bool OnRequestActivateAbility();
	virtual bool OnRequestDeactivateAbility(bool bForce=false);
	/**
	* Called once an ability has been activated.
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
		meta = (DisplayName = "On Ability Activated", ScriptName = "OnAbilityActivated"))
	void K2_OnAbilityActivated();
	/**
	* Called once an ability has been deactivated.
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability|Lifecycle",
		meta = (DisplayName = "On Ability Deactivated", ScriptName = "OnAbilityDeactivated"))
	void K2_OnAbilityDeactivated();

	virtual void OnEnableAbility();
	virtual void OnDisableAbility();
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

	/**
	* Returns whether this ability can or uses tick.
	**/
	UFUNCTION(BlueprintCallable, Category = "Nexus Ability|State")
	bool GetCanTick() const { return bCanTick; }


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
	void TickAbility(float DeltaTime);
	virtual void HandleAbilityStart() {};
	virtual void HandleAbilityStop() {};
	virtual void HandleAbilityProgress() {};
	/**
	* Called if bCanTick is true
	**/
	UFUNCTION(BlueprintImplementableEvent, Category = "Nexus Ability",
		meta = (DisplayName = "On Tick Ability", ScriptName = "OnTickAbility"))
	void K2_OnTickAbility();

	UPROPERTY(BlueprintReadOnly, Category = "Ability System|Abilities")
	bool bIsEnabled = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Abilities")
	FGameplayTag AbilityTag;

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

private:
	ENexusAbilityActivationState ActivationState = ENexusAbilityActivationState::Idle;
	bool bCanTick = true;
};
