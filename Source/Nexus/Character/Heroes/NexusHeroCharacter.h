// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "InputActionValue.h"

#include "NexusHeroCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USceneComponent;
class USpringArmComponent;

UCLASS(PrioritizeCategories = "Abilities|Camera|Input")
class NEXUS_API ANexusHeroCharacter : public ANexusCharacterBase
{
	GENERATED_BODY()

public:
	ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer  = FObjectInitializer::Get());

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

protected:
	virtual void BeginPlay() override;

	//Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USceneComponent* ViewRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USceneComponent* ViewSource;

	//Input
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	FGameplayTag SprintAbilityTag;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint();
	void StopSprint();
private:
	bool bWantsToSprint = false;
};
