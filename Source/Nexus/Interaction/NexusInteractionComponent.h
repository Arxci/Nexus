// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NexusInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UNexusInteractionComponent();
	
	UFUNCTION(BlueprintCallable)
	void TryInteract();
	
	UFUNCTION(BlueprintCallable)
	AActor* GetFocusedInteractable() const { return FocusedActor.Get(); }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float TraceDistance = 300.f;

	TWeakObjectPtr<AActor> FocusedActor;

	void PerformTrace();
	void CheckForNearbyInteractables();
};