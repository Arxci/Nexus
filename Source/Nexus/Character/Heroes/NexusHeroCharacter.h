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
class UCameraComponent;

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	Hold   UMETA(DisplayName = "Hold"),
	Toggle UMETA(DisplayName = "Toggle"),
};

UCLASS(PrioritizeCategories = ("Abilities","Camera","Input"))
class NEXUS_API ANexusHeroCharacter : public ANexusCharacterBase
{
	GENERATED_BODY()

public:
	ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer  = FObjectInitializer::Get());

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	//Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	USceneComponent* ViewRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	USceneComponent* ViewSource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	UCameraComponent* FollowCamera;

	//Input
	UPROPERTY(EditAnywhere, Category = "Character|Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Input|Actions")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Sprint")
	EInputMode RunInputMode = EInputMode::Hold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Crouch")
	EInputMode CrouchInputMode = EInputMode::Hold;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnCrouchInputStarted(); 
	void OnCrouchInputCompleted();
	void OnRunInputStarted();
	void OnRunInputCompleted();

	void HandleToggleAbilityInput(FGameplayTag AbilityTag, FGameplayTag DeactivateIntentTag);
};
