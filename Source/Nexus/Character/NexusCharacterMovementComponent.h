// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NexusCharacterMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSprintStateChanged);

UCLASS()
class NEXUS_API UNexusCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UNexusCharacterMovementComponent();

	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StartSprinting();

	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StopSprinting();

	UFUNCTION(BlueprintPure, Category = "Sprint")
	bool IsSprinting() const { return bIsSprinting; }

	UPROPERTY(BlueprintAssignable, Category = "Sprint")
	FOnSprintStateChanged OnSprintStart;

	UPROPERTY(BlueprintAssignable, Category = "Sprint")
	FOnSprintStateChanged OnSprintEnd;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprint")
	float SprintSpeed = 600.0f;

private:
	bool bIsSprinting = false;
	float CachedWalkSpeed = 0.0f;
};