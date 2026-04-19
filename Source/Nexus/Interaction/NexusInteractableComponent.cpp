// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusInteractableComponent.h"

#include "Nexus/NexusGameplayTags.h"


UNexusInteractableComponent::UNexusInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true; 
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bWantsInitializeComponent = true;
	bDisplayIndicator = true;
}

void UNexusInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	ResolveIndicatorComponent();
}

void UNexusInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InteractionProgress();
}

void UNexusInteractableComponent::InitializeComponent()
{
	Super::InitializeComponent();

	
}

float UNexusInteractableComponent::GetElapsedTime() const
{
	if (const UWorld* World = GetWorld())
	{
		return World->GetTimeSeconds() - InteractionStartTime;
	}
	return 0.0f;
}

void UNexusInteractableComponent::TryStartInteraction_Implementation()
{
	if (const UWorld* World = GetWorld())
	{
		InteractionStartTime = World->GetTimeSeconds();
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

void UNexusInteractableComponent::OnEnteredPlayerRange_Implementation()
{
	InteractableState.AddTag(NexusGameplayTags::Interactable_Proximity_PlayerInRange);
	AddIndicator();
}

void UNexusInteractableComponent::OnLeftPlayerRange_Implementation()
{
	InteractableState.RemoveTag(NexusGameplayTags::Interactable_Proximity_PlayerInRange);
	RemoveIndicator();
}

//Indicator
void UNexusInteractableComponent::AddIndicator() const
{
	if (bDisplayIndicator && IndicatorWidget)
	{
		IndicatorWidget->Activate();
	}
}

void UNexusInteractableComponent::RemoveIndicator() const
{
	if (bDisplayIndicator && IndicatorWidget)
	{
		IndicatorWidget->Deactivate();
	}
}
void UNexusInteractableComponent::ResolveIndicatorComponent()
{
	IndicatorTarget = IndicatorComponent.GetComponent<USceneComponent>(this);
	if (bDisplayIndicator && IndicatorTarget)
	{
		InitializeIndicatorWidget();
	}

	if (IsPlayerInRange()) AddIndicator();
}

void UNexusInteractableComponent::InitializeIndicatorWidget()
{
	if (!IndicatorWidgetClass) return;
	
	AActor* Owner = GetOwner();
	if (!Owner) return;
	
	UActorComponent* NewComp = Owner->AddComponentByClass(
			UWidgetComponent::StaticClass(),
			/* bManualAttachment */ true,
			FTransform::Identity,
			/* bDeferredFinish */ true);

	IndicatorWidget = Cast<UWidgetComponent>(NewComp);

	if (!IndicatorWidget) return;

	IndicatorWidget->AttachToComponent(IndicatorTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	IndicatorWidget->SetupAttachment(IndicatorTarget);
	IndicatorWidget->SetWidgetSpace(EWidgetSpace::Screen);
	IndicatorWidget->SetDrawAtDesiredSize(true);
	IndicatorWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IndicatorWidget->SetWidgetClass(IndicatorWidgetClass);
	
	Owner->FinishAddComponent(IndicatorWidget, true, FTransform::Identity);
}


//Utility
bool UNexusInteractableComponent::IsPlayerInRange() const
{
	return InteractableState.HasTag(NexusGameplayTags::Interactable_Proximity_PlayerInRange);
}

