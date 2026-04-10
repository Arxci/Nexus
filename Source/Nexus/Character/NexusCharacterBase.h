// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "NexusCharacterBase.generated.h"

UCLASS()
class NEXUS_API ANexusCharacterBase : public ACharacter, public INexusAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANexusCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UNexusAbilitySystemComponent* GetNexusAbilityComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nexus|Character")
	UNexusAbilitySystemComponent* NexusAbilitySystemComponent;

protected:
	virtual void PossessedBy(AController* NewController) override;

};
