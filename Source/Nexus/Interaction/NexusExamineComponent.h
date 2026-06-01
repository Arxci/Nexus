#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Nexus/Interaction/NexusExamineTypes.h"

#include "NexusExamineComponent.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class UNexusAbilitySystemComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExamineStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExamineEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExamineRevealed, FText, RevealText);


/**
 * The player-side Examine/Inspect sub-mode (the RE signature feature). A
 * BeginExamine effect on a focused interactable calls into this component on the
 * interactor pawn; it pulls the item's mesh in front of the camera, owns the
 * Character.State.Examining state tag (so other abilities gate off it), rotates
 * the mesh on look-input, reveals hidden details by orientation, and routes a
 * combine through UNexusItemCombinationSubsystem. Exit restores control.
 *
 * It is driven, never driving: the player's input handlers feed it look input
 * and ask it to exit; it never reaches back into the HUD or the interaction
 * ability (the HUD subscribes to its delegates + pure accessors).
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusExamineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNexusExamineComponent();

	/** Enter the sub-mode for Data. No-op if already examining or there's no mesh/camera. */
	UFUNCTION(BlueprintCallable, Category = "Examine")
	void BeginExamine(const FNexusExamineData& Data);

	/** Leave the sub-mode and restore control. */
	UFUNCTION(BlueprintCallable, Category = "Examine")
	void EndExamine();

	UFUNCTION(BlueprintPure, Category = "Examine")
	bool IsExamining() const { return bExamining; }

	/** Feed look input (from the player's Look handler while examining) to rotate the mesh; also tests reveals. */
	UFUNCTION(BlueprintCallable, Category = "Examine")
	void AddRotationInput(FVector2D LookInput);

	/** Craft the combine recipe at Index via UNexusItemCombinationSubsystem (if its inputs are held). */
	UFUNCTION(BlueprintCallable, Category = "Examine")
	bool TryCombine(int32 RecipeIndex);

	UFUNCTION(BlueprintPure, Category = "Examine")
	FText GetTitle() const { return CurrentData.Title; }

	UFUNCTION(BlueprintPure, Category = "Examine")
	FText GetDescription() const { return CurrentData.Description; }

	UPROPERTY(BlueprintAssignable, Category = "Examine")
	FOnExamineStarted OnExamineStarted;

	UPROPERTY(BlueprintAssignable, Category = "Examine")
	FOnExamineEnded OnExamineEnded;

	UPROPERTY(BlueprintAssignable, Category = "Examine")
	FOnExamineRevealed OnExamineRevealed;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool bExamining = false;

	UPROPERTY(Transient)
	FNexusExamineData CurrentData;

	UPROPERTY(Transient)
	TObjectPtr<UStaticMeshComponent> ExamineMesh;

	/** Parallel to CurrentData.Reveals — which have already fired (so each reveals once). */
	TArray<bool> RevealTriggered;

	/** Accumulated relative rotation applied to the examined mesh. */
	FRotator MeshRotation = FRotator::ZeroRotator;

	UNexusAbilitySystemComponent* GetASC() const;
	UCameraComponent* GetViewCamera() const;
	void CheckReveals();
};
