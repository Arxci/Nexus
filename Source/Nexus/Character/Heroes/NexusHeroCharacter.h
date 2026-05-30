

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
class USkeletalMeshComponent;
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
	
	virtual USkeletalMeshComponent* GetEquipmentAttachMesh() const override { return FirstPersonArms ? FirstPersonArms.Get() : Super::GetEquipmentAttachMesh(); }

	virtual UAnimInstance* GetAnimInstance() const override { return FirstPersonArms ? FirstPersonArms->GetAnimInstance() : nullptr; };
	
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

	// Sibling of the camera under the spring arm. Hosts the view-model arms so they
	// inherit only the shared control rotation, never the camera-only view offset.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Camera")
	TObjectPtr<USceneComponent> ViewModelRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character|Arms")
	TObjectPtr<USkeletalMeshComponent> FirstPersonArms;

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
	UPROPERTY(EditAnywhere, Category = "Character|Input|Actions|")
	TObjectPtr<UInputAction> InteractAction;

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

	/**
	 * Hold duration (seconds) that upgrades a slot activation from a normal
	 * unholster to the ceremony (inspect / flourish) variant. A tap draws normally;
	 * holding past this plays the ceremony draw. Distinguished from the Enhanced
	 * Input action's processed elapsed time on release.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Input|Weapon", meta = (ClampMin = "0.0"))
	float SlotCeremonyHoldThreshold = 0.3f;

	UEnhancedInputComponent* GetEnhancedInputComponent() const { return EnhancedInputComponent; }

protected:
	//~Start save interface
	virtual void ActorPreLoad_Implementation() override;
	virtual void ActorLoaded_Implementation() override;
	//~Stop save interface

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
	
	class UNexusInteractableComponent* GetFocusedInteractable() const;
	/**
	 * The interactable we last called TryStartInteraction on. Used on release
	 * so a player who starts holding on A and looks away to B before releasing
	 * still cancels A — without this, A would keep ticking toward auto-complete
	 * unattended because Release reads the *current* focused target.
	 */
	TWeakObjectPtr<class UNexusInteractableComponent> ActiveInteractable;
	
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
	void OnInteractInputStarted();
	void OnInteractInputCompleted();
	
	// Slot inputs use a single Hold trigger per action: a tap cancels the hold
	// (Canceled → Normal draw); holding past the trigger's threshold fires Triggered
	// (→ Ceremony draw). The threshold lives on the Input Action asset, not here.
	void OnSlotPrimaryTap();
	void OnSlotPrimaryHold();
	void OnSlotSecondaryTap();
	void OnSlotSecondaryHold();
	void HandleSlotInput(FGameplayTag SlotTag, EUnholsterStyle Style);

	void HandleToggleAbilityInput(const FGameplayTag AbilityTag, const FGameplayTag DeactivateIntentTag);

	UFUNCTION()
	void HandleActiveSlotChanged(FGameplayTag SlotTag, UNexusItemInstance* Instance);
	void UpdateArmsVisibility();
};