// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NexusInteractableInterface.h"
#include "Components/ActorComponent.h"
#include "ComponentPicker.h"
#include "GameplayTagContainer.h"
#include "NexusInteractableComponent.generated.h"

class UWidgetComponent;
class UUserWidget;
class UNexusWorldMarkerWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionProgressed, float, ElapsedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionStarted, AActor*, Interactor);
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
	
	virtual void TryStartInteraction_Implementation(AActor* Interactor) override;
	virtual void TryStopInteraction_Implementation(AActor* Interactor) override;

	virtual void OnEnteredPlayerRange_Implementation() override;
	virtual void OnLeftPlayerRange_Implementation() override;

	virtual void OnGainedPlayerFocus_Implementation() override;
	virtual void OnLostPlayerFocus_Implementation() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractionProgress();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionDuration = 0.0f;

public:
	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionProgressed OnInteractionProgressed;
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEnded OnInteractionEnded;
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionStarted OnInteractionStarted;

//Indicator
protected:
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
	/** Runtime: world time when the current interaction started. */
	float InteractionStartTime = 0.0f;
	UPROPERTY()
	FGameplayTagContainer InteractableState;

	UPROPERTY(Transient)
	TObjectPtr<USceneComponent> IndicatorTarget;
	void ResolveIndicatorComponent();
	
	UPROPERTY(Transient)
	TObjectPtr<UPrimitiveComponent> InteractionTriggerTarget;
	void ResolveInteractionTriggerComponent();
};
