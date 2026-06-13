#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Character/NexusCharacterBase.h"

#include "NexusHeroCharacter.generated.h"

class USceneComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UNexusExamineComponent;
class UNexusInputHostComponent;
class UNexusLocomotionInputComponent;


UCLASS(PrioritizeCategories = ("Abilities","Camera","Input"))
class NEXUS_API ANexusHeroCharacter : public ANexusCharacterBase
{
	GENERATED_BODY()

public:
	ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer  = FObjectInitializer::Get());

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

	// Input — the Anim BP contract. The signatures are unchanged; the data source moved from
	// the (deleted) hero-owned EnhancedInputComponent to the per-verb cache on
	// UNexusInputManager, so the values still track Move / Look / Run / Crouch.
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

	// The first-person Examine/Inspect sub-mode. A BeginExamine effect on a focused
	// interactable drives it; while it is active it pushes the modal Examine input context
	// (Look becomes Input.Examine.Rotate, combat/locomotion suppressed) — the hero no longer
	// reroutes look or gates on IsExamining().
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Interaction")
	TObjectPtr<UNexusExamineComponent> ExamineComponent;

	// The hero's ONLY input member: it creates the binder, registers the pawn with the input
	// manager, and pushes the pawn's default contexts. The hero binds nothing itself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Input")
	TObjectPtr<UNexusInputHostComponent> InputHostComponent;

	// Move / Look listener. A dedicated component so an AI pawn omits it cleanly.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character|Input")
	TObjectPtr<UNexusLocomotionInputComponent> LocomotionInputComponent;

protected:
	//~Start save interface
	virtual void ActorPreLoad_Implementation() override;
	virtual void ActorLoaded_Implementation() override;
	//~Stop save interface

private:
	UFUNCTION()
	void HandleActiveSlotChanged(FGameplayTag SlotTag, UNexusItemInstance* Instance);
	void UpdateArmsVisibility();
};
