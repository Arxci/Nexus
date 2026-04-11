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

UENUM(BlueprintType)
enum class ERunInputMode : uint8
{
	Hold   UMETA(DisplayName = "Hold to Run"),
	Toggle UMETA(DisplayName = "Toggle Run"),
};

UENUM(BlueprintType)
enum class ECrouchInputMode : uint8
{
	Hold   UMETA(DisplayName = "Hold to Crouch"),
	Toggle UMETA(DisplayName = "Toggle Crouch"),
};

UCLASS(PrioritizeCategories = ("Abilities","Camera","Input"))
class NEXUS_API ANexusHeroCharacter : public ANexusCharacterBase
{
	GENERATED_BODY()

public:
	ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer  = FObjectInitializer::Get());

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

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
	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, Category = "Input|Actions")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Sprint")
	ERunInputMode RunInputMode = ERunInputMode::Hold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Crouch")
	ECrouchInputMode CrouchInputMode = ECrouchInputMode::Hold;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnCrouchInputStarted(); 
	void OnCrouchInputCompleted();
	void OnRunInputStarted();
	void OnRunInputCompleted();
};
