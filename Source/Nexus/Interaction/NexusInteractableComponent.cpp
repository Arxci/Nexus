// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusInteractableComponent.h"


UNexusInteractableComponent::UNexusInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true; 
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UNexusInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNexusInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InteractionProgress();
}

float UNexusInteractableComponent::GetElapsedTime() const
{
	if (UWorld* World = GetWorld())
	{
		return World->GetTimeSeconds() - InitialInteractTime;
	}

	return 0.0f;
}

void UNexusInteractableComponent::TryStartInteraction_Implementation()
{
	if (UWorld* World = GetWorld())
	{
		InitialInteractTime = World->GetTimeSeconds();
	}

	OnInteractionStarted.Broadcast();

	SetComponentTickEnabled(true);
}

void UNexusInteractableComponent::TryStopInteraction_Implementation()
{
	OnInteractionEnded.Broadcast();

	SetComponentTickEnabled(false);
}

void UNexusInteractableComponent::InteractionProgress_Implementation()
{
	OnInteractionProgressed.Broadcast(GetElapsedTime());
}

