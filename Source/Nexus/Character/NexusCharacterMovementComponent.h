// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NexusCharacterMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRunStateChanged);

UCLASS()
class NEXUS_API UNexusCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UNexusCharacterMovementComponent();

	UFUNCTION(BlueprintCallable, Category = "Character Movement: Run")
	void StartRunning();

	UFUNCTION(BlueprintCallable, Category = "Character Movement: Run")
	void StopRunning();

	UFUNCTION(BlueprintPure, Category = "Character Movement: Run")
	bool IsRunning() const { return bIsRunning; }

	UPROPERTY(BlueprintAssignable, Category = "Character Movement: Run")
	FOnRunStateChanged OnRunStart;

	UPROPERTY(BlueprintAssignable, Category = "Character Movement: Run")
	FOnRunStateChanged OnRunEnd;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Run")
	float MaxWalkSpeedRun = 600.0f;

private:
	bool bIsRunning = false;
	float CachedWalkSpeed = 0.0f;
};