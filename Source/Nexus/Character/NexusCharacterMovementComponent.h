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

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Character Movement: Run")
	void StartRunning();

	UFUNCTION(BlueprintCallable, Category = "Character Movement: Run")
	void StopRunning();

	UFUNCTION(BlueprintPure, Category = "Character Movement: Run")
	bool IsRunning() const { return bIsRunning; }

	UFUNCTION(BlueprintPure, Category = "Character Movement: Run")
	bool IsGrounded() const { return MovementMode == MOVE_Walking || MovementMode == MOVE_NavWalking; }

	UFUNCTION(BlueprintPure, Category = "Character Movement")
	bool IsMovingForward(float Threshold = 0.2f) const;

	UFUNCTION(BlueprintPure, Category = "Character Movement: Crouch")
	bool CanStand() const;
	
	UPROPERTY(BlueprintAssignable, Category = "Character Movement: Run")
	FOnRunStateChanged OnRunStart;

	UPROPERTY(BlueprintAssignable, Category = "Character Movement: Run")
	FOnRunStateChanged OnRunEnd;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Run")
	float MaxWalkSpeedRun = 1000.0f;

private:
	bool bIsRunning = false;
	float StandingHalfHeight = 0.0f;
	float CachedWalkSpeed = 0.0f;
};