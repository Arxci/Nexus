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

UCLASS(Blueprintable)
class NEXUS_API UNexusAbility : public UObject
{
	GENERATED_BODY()

	friend class UNexusAbilitySystemComponent;

public:
	UNexusAbility();
	
	virtual void OnActivateAbility();
	virtual void OnDeactivateAbility();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System|Abilities",
		meta = (DisplayName = "On Activate Ability", ScriptName = "OnActivateAbility"))
	void K2_OnActivateAbility();

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability System|Abilities",
		meta = (DisplayName = "On Deactivate Ability", ScriptName = "OnDeactivateAbility"))
	void K2_OnDeactivateAbility();

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

private:
	float CooldownEndTime = 0.0f;
};
