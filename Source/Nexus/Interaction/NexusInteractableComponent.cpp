// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusInteractableComponent.h"
#include "Components/WidgetComponent.h"
#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/UI/World/NexusWorldMarkerWidget.h"


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
	ResolveInteractionTriggerComponent();
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

void UNexusInteractableComponent::OnGainedPlayerFocus_Implementation()
{
	InteractableState.AddTag(NexusGameplayTags::Interactable_State_HasPlayerFocus);
}

void UNexusInteractableComponent::OnLostPlayerFocus_Implementation()
{
	InteractableState.RemoveTag(NexusGameplayTags::Interactable_State_HasPlayerFocus);
}

//Indicator
void UNexusInteractableComponent::AddIndicator() 
{
	UNexusWorldMarkerWidget* Marker = GetMarkerWidget();
	if (bDisplayIndicator && IndicatorWidgetComponent)
	{
		Marker->AddStateTag(NexusGameplayTags::WorldMarker_State_Visible);
		
		IndicatorWidgetComponent->Activate();
	}
}

void UNexusInteractableComponent::RemoveIndicator()
{
	UNexusWorldMarkerWidget* Marker = GetMarkerWidget();
	if (bDisplayIndicator && Marker)
	{
		Marker->RemoveStateTag(NexusGameplayTags::WorldMarker_State_Visible);
		
		IndicatorWidgetComponent->Deactivate();
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

	IndicatorWidgetComponent = Cast<UWidgetComponent>(NewComp);

	if (!IndicatorWidgetComponent) return;

	IndicatorWidgetComponent->AttachToComponent(IndicatorTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	IndicatorWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	IndicatorWidgetComponent->SetDrawAtDesiredSize(true);
	IndicatorWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IndicatorWidgetComponent->SetWidgetClass(IndicatorWidgetClass);
	
	Owner->FinishAddComponent(IndicatorWidgetComponent, true, FTransform::Identity);

	if (UNexusWorldMarkerWidget* Marker = GetMarkerWidget())
	{
		Marker->SetContext(IndicatorTarget, Owner);
	}
	else
	{
		// Widget may not be instantiated yet; force it and retry.
		IndicatorWidgetComponent->InitWidget();
		if (UNexusWorldMarkerWidget* MarkerRetry = GetMarkerWidget())
		{
			MarkerRetry->SetContext(IndicatorTarget, Owner);
		}
	}
}

void UNexusInteractableComponent::ResolveInteractionTriggerComponent()
{
	InteractionTriggerTarget = InteractionTriggerComponent.GetComponent<UPrimitiveComponent>(this);

	if (InteractionTriggerTarget)
	{
		InteractionTriggerTarget->SetCollisionResponseToChannel(    NexusCollisionChannels::Interaction,
	ECR_Block);
		InteractionTriggerTarget->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

//Utility
bool UNexusInteractableComponent::IsPlayerInRange() const
{
	return InteractableState.HasTag(NexusGameplayTags::Interactable_Proximity_PlayerInRange);
}

UNexusWorldMarkerWidget* UNexusInteractableComponent::GetMarkerWidget() const
{
	return IndicatorWidgetComponent
	? Cast<UNexusWorldMarkerWidget>(IndicatorWidgetComponent->GetUserWidgetObject())
	: nullptr;
}


