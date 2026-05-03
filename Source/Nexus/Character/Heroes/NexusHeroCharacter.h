

#pragma once

#include "CoreMinimal.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "GameplayTagContainer.h"

#include "Nexus/Character/NexusCharacterBase.h"

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
	
public:
	// Utility
	UFUNCTION(BlueprintPure)
	bool GetIsTurning() const;
	UFUNCTION(BlueprintPure)
	FVector GetRelativeAcceleration() const;
	UFUNCTION(BlueprintPure)
	FVector GetAcceleration() const;

	// Input
	UFUNCTION(BlueprintPure)
	FVector2D GetLookInput() const;
	UFUNCTION(BlueprintPure)
	FVector2D GetMoveInput() const;
	UFUNCTION(BlueprintPure)
	bool GetRunInput() const;
	UFUNCTION(BlueprintPure)
	bool GetCrouchInput() const;

protected:
	virtual void BeginPlay() override;

protected:
	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<USceneComponent> ViewRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<USceneComponent> ViewSource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

protected:
	// Input
	UPROPERTY(EditAnywhere, Category = "Character|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> RunAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions|Weapon")
	TObjectPtr<UInputAction> FireAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions|Weapon")
	TObjectPtr<UInputAction> ReloadAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions|Weapon")
	TObjectPtr<UInputAction> AimAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions|Weapon")
	TObjectPtr<UInputAction> SlotPrimaryAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions|Weapon")
	TObjectPtr<UInputAction> SlotSecondaryAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Sprint")
	EInputMode RunInputMode = EInputMode::Hold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Crouch")
	EInputMode CrouchInputMode = EInputMode::Hold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Aim")
	EInputMode AimInputMode = EInputMode::Hold;

	UEnhancedInputComponent* GetEnhancedInputComponent() const { return EnhancedInputComponent; }

protected:
	//~Start save interface
	virtual void ActorPreLoad_Implementation() override;
	virtual void ActorLoaded_Implementation() override;
	//~Stop save interface

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

private:
	// Input
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnCrouchInputStarted();
	void OnCrouchInputCompleted();
	void OnRunInputStarted();
	void OnRunInputCompleted();
	void OnFireInputStarted();
	void OnReloadInputStarted();
	void OnAimInputStarted();
	void OnAimInputCompleted();
	void OnSlotPrimaryInputStarted();
	void OnSlotSecondaryInputStarted();
	void HandleSlotInput(FGameplayTag SlotTag);

	void HandleToggleAbilityInput(const FGameplayTag AbilityTag, const FGameplayTag DeactivateIntentTag);

	const FEnhancedInputActionValueBinding* FireBinding   = nullptr;
	const FEnhancedInputActionValueBinding* AimBinding    = nullptr;
	const FEnhancedInputActionValueBinding* LookBinding   = nullptr;
	const FEnhancedInputActionValueBinding* MoveBinding   = nullptr;
	const FEnhancedInputActionValueBinding* RunBinding    = nullptr;
	const FEnhancedInputActionValueBinding* CrouchBinding = nullptr;
};