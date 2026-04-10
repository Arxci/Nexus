// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "GameplayTagContainer.h"
#include "NexusAbility.generated.h"


UENUM(BlueprintType)
enum class ENexusAbilityActivationState : uint8
{
	Idle    UMETA(DisplayName = "Idle"),
	Active  UMETA(DisplayName = "Active"),
};

UCLASS()
class NEXUS_API UNexusAbility : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

	friend class UNexusAbilitySystemComponent;

public:
	UNexusAbility();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability System|Abilities")
	void ActivateAbility();
	virtual void ActivateAbility_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability System|Abilities")
	void DeactivateAbility();
	virtual void DeactivateAbility_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability System|Abilities")
	bool CanActivateAbility() const;
	virtual bool CanActivateAbility_Implementation() const;

	class UNexusAbilitySystemComponent* GetNexusComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	ACharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	AController* GetController() const;

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	ENexusAbilityActivationState GetActivationState() const { return ActivationState; }

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool IsEnabled() const { return bIsEnabled; }

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool IsActive() const { return ActivationState == ENexusAbilityActivationState::Active; }

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	ENexusAbilityActivationState ActivationState = ENexusAbilityActivationState::Idle;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	bool bIsEnabled = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Tags")
	FGameplayTagContainer AbilityTags;

	/** Tags applied to the owning actor while this ability is active */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Tags")
	FGameplayTagContainer ActivationOwnedTags;

	/** Tags that must ALL be present on the owner for activation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Tags")
	FGameplayTagContainer ActivationRequiredTags;

	/** Tags that must ALL be absent from the owner for activation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Tags")
	FGameplayTagContainer ActivationBlockedTags;

	/** On activation, cancel any active abilities whose AbilityTags match any of these tags */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System|Tags")
	FGameplayTagContainer CancelAbilitiesWithTags;
};
