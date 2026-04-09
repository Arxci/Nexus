// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NexusInteractableInterface.h"
#include "Components/ActorComponent.h"
#include "NexusInteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionProgressed, float, ElapsedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionEnded);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusInteractableComponent : public UActorComponent, public INexusInteractableInterface
{
	GENERATED_BODY()

public:
	UNexusInteractableComponent();

protected:
	virtual void BeginPlay() override;
	
	virtual void TryStartInteraction_Implementation() override;
	virtual void TryStopInteraction_Implementation() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractionProgress();
	
	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetElapsedTime() const;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float InitialInteractTime = 0.0f;
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionProgressed OnInteractionProgressed;
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEnded OnInteractionEnded;
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionStarted OnInteractionStarted;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
