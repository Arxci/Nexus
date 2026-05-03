// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EMSActorSaveInterface.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"

#include "NexusCharacterBase.generated.h"

class UNexusAbilitySystemComponent;
class UNexusAbility;

class UNexusCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterLoaded);

UCLASS(PrioritizeCategories = ("Abilities"))
class NEXUS_API ANexusCharacterBase : public ACharacter, public INexusAbilitySystemInterface, public IEMSActorSaveInterface
{
	GENERATED_BODY()

public:
	ANexusCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusAbilitySystemComponent> NexusAbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusCharacterMovementComponent> NexusCharacterMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusInventoryComponent> NexusInventoryComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusEquipmentComponent> NexusEquipmentComponent;

public:
	//Movement
	UFUNCTION()
	void OnStartRun();
	UFUNCTION()
	void OnEndRun();
	UFUNCTION(BlueprintCallable, Category = "Character")
	void Run() const;
	UFUNCTION(BlueprintCallable, Category = "Character")
	void StopRun() const;

public:
	//Utility
	UFUNCTION(BlueprintPure)
	bool GetIsCrouched() const;
	UFUNCTION(BlueprintPure)
	bool GetIsRunning() const;
	UFUNCTION(BlueprintPure)
	bool GetIsGrounded() const;

	virtual UNexusAbilitySystemComponent* GetNexusAbilitySystemComponent() const override { return NexusAbilitySystemComponent; };
	UFUNCTION(BlueprintPure, Category = "Character")
	UNexusCharacterMovementComponent* GetNexusCharacterMovement() const { return NexusCharacterMovement; };
	UFUNCTION(BlueprintPure, Category = "Character")
	UNexusInventoryComponent* GetNexusInventoryComponent() const { return NexusInventoryComponent; }
	UFUNCTION(BlueprintPure, Category = "Character")
	UNexusEquipmentComponent* GetNexusEquipmentComponent() const { return NexusEquipmentComponent; }

public:
	//Delegates
	UPROPERTY(BlueprintAssignable)
	FOnCharacterLoaded OnCharacterLoaded;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

protected:
	//~Start save interface
	virtual void ActorPreSave_Implementation() override;
	virtual void ActorLoaded_Implementation() override;
	//~Stop save interface

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TArray<TSubclassOf<UNexusAbility>> DefaultAbilities;

private:
	UPROPERTY(SaveGame)
	FVector SavedPawnPosition;
	UPROPERTY(SaveGame)
	FRotator SavedPawnRotation;
};
