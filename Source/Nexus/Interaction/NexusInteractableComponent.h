#pragma once

#include "CoreMinimal.h"

#include "UObject/PrimaryAssetId.h"

#include "Components/ActorComponent.h"

#include "ComponentPicker.h"

#include "GameplayTagContainer.h"

#include "NexusInteractableInterface.h"

#include "NexusInteractableComponent.generated.h"

class UWidgetComponent;
class UUserWidget;
class UNexusWorldMarkerWidget;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionProgressed, float, ElapsedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionStarted, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionCompleted, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionCancelled, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionEnded, AActor*, Interactor);


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusInteractableComponent : public UActorComponent, public INexusInteractableInterface
{
	GENERATED_BODY()

public:
	UNexusInteractableComponent();

	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetElapsedTime() const;

	UFUNCTION(BlueprintPure, Category = "Interaction")
	USceneComponent* GetIndicatorTarget() { return IndicatorTarget; }
	UFUNCTION(BlueprintPure, Category = "Interaction")
	UPrimitiveComponent* GetInteractionTriggerTarget() { return InteractionTriggerTarget; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//~Start interaction interface
	virtual void TryStartInteraction_Implementation(AActor* Interactor) override;
	virtual void TryStopInteraction_Implementation(AActor* Interactor) override;

	virtual void OnEnteredPlayerRange_Implementation() override;
	virtual void OnLeftPlayerRange_Implementation() override;

	virtual void OnGainedPlayerFocus_Implementation() override;
	virtual void OnLostPlayerFocus_Implementation() override;
	//~Stop interaction interface
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractionProgress();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionDuration = 0.0f;

public:
	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionProgressed OnInteractionProgressed;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionStarted OnInteractionStarted;

	/**
	 * Fires when the interaction was held for the full InteractionDuration (or
	 * immediately if Duration <= 0). This is the "success" signal — listeners
	 * like ANexusItemPickup that consume the world actor should bind here, NOT
	 * to OnInteractionEnded, so a player who taps-and-releases mid-hold doesn't
	 * accidentally trigger consumption.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionCompleted OnInteractionCompleted;

	/** Fires when the interactor released the input before InteractionDuration elapsed. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionCancelled OnInteractionCancelled;

	/**
	 * Fires after either Completed or Cancelled. Intended for UI listeners that
	 * don't care which way the interaction ended (hide the progress bar, etc.).
	 */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEnded OnInteractionEnded;

protected:
	//Indicator
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interaction|Indicator")
	bool bDisplayIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interaction|Indicator")
	FComponentPicker  IndicatorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|Indicator")
	TSubclassOf<UNexusWorldMarkerWidget> IndicatorWidgetClass;
	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> IndicatorWidgetComponent;
	
	UFUNCTION(BlueprintGetter)
	UNexusWorldMarkerWidget* GetMarkerWidget() const;
	
	void InitializeIndicatorWidget();

	UFUNCTION(BlueprintCallable)
	void ShowIndicator();
	UFUNCTION(BlueprintCallable)
	void HideIndicator();

//Utility	
protected:
	bool IsPlayerInRange() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interaction")
	FComponentPicker  InteractionTriggerComponent;

private:
	/**
	 * Runtime: actor whose TryStartInteraction call brought us into the in-progress
	 * state. Non-null while ticking; cleared on Complete or Cancel. Treat as the
	 * "is interaction in progress" flag — TryStartInteraction is a no-op when set.
	 */
	UPROPERTY(Transient)
	TObjectPtr<AActor> CurrentInteractor;

	/** Runtime: world time when the current interaction started. */
	float InteractionStartTime = 0.0f;

	void CompleteInteraction();
	void CancelInteraction();

	UPROPERTY()
	FGameplayTagContainer InteractableState;

	UPROPERTY(Transient)
	TObjectPtr<USceneComponent> IndicatorTarget;
	void ResolveIndicatorComponent();
	
	UPROPERTY(Transient)
	TObjectPtr<UPrimitiveComponent> InteractionTriggerTarget;
	void ResolveInteractionTriggerComponent();
};
