// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "NexusAbility.generated.h"

UENUM(BlueprintType)
enum class ENexusAbilityState : uint8
{
	Inactive    UMETA(DisplayName = "Inactive"),
	Active      UMETA(DisplayName = "Active"),
};

UCLASS()
class NEXUS_API UNexusAbility : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability System|Abilities")
	void ActivateAbility();
	virtual void ActivateAbility_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability System|Abilities")
	void DeactivateAbility();
	virtual void DeactivateAbility_Implementation();

	class UNexusAbilitySystemComponent* GetNexusComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	ACharacter* GetCharacter() const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	AController* GetController() const;

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	ENexusAbilityState GetState() const { return CurrentState; }

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	ENexusAbilityState CurrentState = ENexusAbilityState::Inactive;
	
	
};
