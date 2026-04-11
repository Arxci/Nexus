// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "NexusCharacterBase.generated.h"

UCLASS(PrioritizeCategories = ("Abilities"))
class NEXUS_API ANexusCharacterBase : public ACharacter, public INexusAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANexusCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UNexusAbilitySystemComponent* GetNexusAbilityComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Character")
	UNexusCharacterMovementComponent* GetNexusCharacterMovement() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UNexusAbilitySystemComponent* NexusAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UNexusCharacterMovementComponent> NexusCharacterMovement;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	/**
	 * Request that the character start boost-running. Thin wrapper around the
	 * CMC's StartRunning(), modelled on ACharacter::Crouch() so gameplay code
	 * has a single entry point on the pawn. Abilities should prefer this over
	 * talking to the CMC directly.
	 */
	UFUNCTION(BlueprintCallable, Category = "Character")
	void StartRunning();

	/** Companion to StartRunning(). Mirrors ACharacter::UnCrouch(). */
	UFUNCTION(BlueprintCallable, Category = "Character")
	void StopRunning();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TArray<TSubclassOf<UNexusAbility>> DefaultAbilities;
	
private:
	/** Bound to NexusCharacterMovement::OnRunStart; mirrors run state as a loose ASC tag. */
	UFUNCTION()
	void OnStartRun();

	/** Bound to NexusCharacterMovement::OnRunEnd; mirrors run state as a loose ASC tag. */
	UFUNCTION()
	void OnEndRun();
};
