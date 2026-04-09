// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusInteractionComponent.h"
#include "AbilitySystemComponent.h"


void UNexusInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckForNearbyInteractables();
}

void UNexusInteractionComponent::PerformTrace()
{

}

void UNexusInteractionComponent::TryInteract()
{

}

void UNexusInteractionComponent::CheckForNearbyInteractables()
{
	
}
