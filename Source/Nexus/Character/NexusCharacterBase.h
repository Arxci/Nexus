// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "NexusCharacterBase.generated.h"

UCLASS(PrioritizeCategories = ("Abilities"))
class NEXUS_API ANexusCharacterBase : public ACharacter, public INexusAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANexusCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UNexusAbilitySystemComponent* GetNexusAbilityComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Character")
	UNexusCharacterMovementComponent* GetNexusCharacterMovement() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UNexusAbilitySystemComponent* NexusAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusCharacterMovementComponent> NexusCharacterMovement;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TArray<TSubclassOf<UNexusAbility>> DefaultAbilities;

};
