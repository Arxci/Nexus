

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "InputActionValue.h"
#include "Curves/CurveVector.h"
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

	//Utility
	UFUNCTION(BlueprintPure)
	bool GetIsCrouched() const;
	UFUNCTION(BlueprintPure)
	bool GetIsGrounded() const;
	UFUNCTION(BlueprintPure)
	bool GetIsTurning() const;
	UFUNCTION(BlueprintPure)
	FVector GetRelativeAcceleration() const;
	UFUNCTION(BlueprintPure)
	FVector GetAcceleration() const;
	UFUNCTION(BlueprintPure)
	float GetSpeed() const;
	
	UFUNCTION(BlueprintPure)
	FVector2D GetLookInput() const;
	UFUNCTION(BlueprintPure)
	FVector2D GetMoveInput() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	//Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<USceneComponent> ViewRoot;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<USceneComponent> ViewSource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	//Input
	UPROPERTY(EditAnywhere, Category = "Character|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> SprintAction;
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Sprint")
	EInputMode RunInputMode = EInputMode::Hold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Crouch")
	EInputMode CrouchInputMode = EInputMode::Hold;

	//Utility
	UEnhancedInputComponent* GetEnhancedInputComponent() const { return EnhancedInputComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
	TObjectPtr<UCurveVector> AccelerationCurve;

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnCrouchInputStarted(); 
	void OnCrouchInputCompleted();
	void OnRunInputStarted();
	void OnRunInputCompleted();

	void HandleToggleAbilityInput(FGameplayTag AbilityTag, FGameplayTag DeactivateIntentTag);

	void UpdateMovementVariables();
	float GetMappedSpeed() const;
};
