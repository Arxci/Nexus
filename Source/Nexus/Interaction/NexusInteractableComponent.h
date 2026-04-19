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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionProgressed, float, ElapsedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionEnded);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusInteractableComponent : public UActorComponent, public INexusInteractableInterface
{
	GENERATED_BODY()

public:
	UNexusInteractableComponent();

	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetElapsedTime() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;
	
	virtual void TryStartInteraction_Implementation() override;
	virtual void TryStopInteraction_Implementation() override;

	virtual void OnEnteredPlayerRange_Implementation() override;
	virtual void OnLeftPlayerRange_Implementation() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractionProgress();

	/** Designer-configurable: delay before interaction fires, in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionDuration = 0.0f;

	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionProgressed OnInteractionProgressed;
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEnded OnInteractionEnded;
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionStarted OnInteractionStarted;

//Indicator
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interactable|Indicator")
	bool bDisplayIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interactable|Indicator")
	FComponentPicker  IndicatorComponent;
	UPROPERTY(Transient)
	TObjectPtr<USceneComponent> IndicatorTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable|Indicator")
	TSubclassOf<UUserWidget> IndicatorWidgetClass;
	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> IndicatorWidget;

	void InitializeIndicatorWidget();

	void AddIndicator() const;
	void RemoveIndicator() const;

//Utility	
protected:
	bool IsPlayerInRange() const;

private:
	/** Runtime: world time when the current interaction started. */
	float InteractionStartTime = 0.0f;

	UPROPERTY(SaveGame)
	FGameplayTagContainer InteractableState;
	
	void ResolveIndicatorComponent();
};
