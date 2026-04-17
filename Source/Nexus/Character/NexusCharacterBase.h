// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EMSActorSaveInterface.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "NexusCharacterBase.generated.h"

class UNexusCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLoaded);

UCLASS(PrioritizeCategories = ("Abilities"))
class NEXUS_API ANexusCharacterBase : public ACharacter, public INexusAbilitySystemInterface, public IEMSActorSaveInterface
{
	GENERATED_BODY()

public:
	ANexusCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UNexusAbilitySystemComponent* GetNexusAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Character")
	UNexusCharacterMovementComponent* GetNexusCharacterMovement() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusAbilitySystemComponent> NexusAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusCharacterMovementComponent> NexusCharacterMovement;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	UFUNCTION()
	void OnStartRun();
	UFUNCTION()
	void OnEndRun();
	
	UFUNCTION(BlueprintCallable, Category = "Character")
	void StartRunning();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void StopRunning();

	UPROPERTY(BlueprintAssignable)
	FEnabledStateChanged OnGameLoaded;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
	virtual void ActorPreSave_Implementation() override;
	virtual void ActorLoaded_Implementation() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TArray<TSubclassOf<UNexusAbility>> DefaultAbilities;

private:
	UPROPERTY(SaveGame)
	FVector SavedPawnPosition;
	UPROPERTY(SaveGame)
	FRotator SavedPawnRotation;
};
