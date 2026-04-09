// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "NexusHeroCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USceneComponent;
class USpringArmComponent;

UCLASS()
class NEXUS_API ANexusHeroCharacter : public ANexusCharacterBase
{
	GENERATED_BODY()

public:
	ANexusHeroCharacter(const class FObjectInitializer& ObjectInitializer  = FObjectInitializer::Get());

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

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

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
