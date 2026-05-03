#include "NexusInteractableComponent.h"

#include "Components/WidgetComponent.h"

#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/UI/World/NexusWorldMarkerWidget.h"


UNexusInteractableComponent::UNexusInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true; 
	PrimaryComponentTick.bStartWithTickEnabled = false;
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

float UNexusInteractableComponent::GetElapsedTime() const
{
	if (const UWorld* World = GetWorld())
	{
		return World->GetTimeSeconds() - InteractionStartTime;
	}
	return 0.0f;
}

void UNexusInteractableComponent::TryStartInteraction_Implementation(AActor* Interactor)
{
	if (const UWorld* World = GetWorld())
	{
		InteractionStartTime = World->GetTimeSeconds();
	}
	OnInteractionStarted.Broadcast(Interactor);
	SetComponentTickEnabled(true);
}

void UNexusInteractableComponent::TryStopInteraction_Implementation(AActor* Interactor)
{
	OnInteractionEnded.Broadcast(Interactor);

	SetComponentTickEnabled(false);
}

void UNexusInteractableComponent::InteractionProgress_Implementation()
{
	OnInteractionProgressed.Broadcast(GetElapsedTime());
}

void UNexusInteractableComponent::OnEnteredPlayerRange_Implementation()
{
	InteractableState.AddTag(NexusGameplayTags::Interactable_Proximity_PlayerInRange);
	ShowIndicator();
}

void UNexusInteractableComponent::OnLeftPlayerRange_Implementation()
{
	InteractableState.RemoveTag(NexusGameplayTags::Interactable_Proximity_PlayerInRange);
	HideIndicator();
}

void UNexusInteractableComponent::OnGainedPlayerFocus_Implementation()
{
	InteractableState.AddTag(NexusGameplayTags::Interactable_State_HasPlayerFocus);
	UNexusWorldMarkerWidget* Marker = GetMarkerWidget();
	if (bDisplayIndicator && Marker)
	{
		Marker->AddStateTag(NexusGameplayTags::WorldMarker_State_HasPlayerFocus);
	}
}

void UNexusInteractableComponent::OnLostPlayerFocus_Implementation()
{
	InteractableState.RemoveTag(NexusGameplayTags::Interactable_State_HasPlayerFocus);
	UNexusWorldMarkerWidget* Marker = GetMarkerWidget();
	if (bDisplayIndicator && Marker)
	{
		Marker->RemoveStateTag(NexusGameplayTags::WorldMarker_State_HasPlayerFocus);
	}
}

//Indicator
void UNexusInteractableComponent::ShowIndicator() 
{
	UNexusWorldMarkerWidget* Marker = GetMarkerWidget();
	if (bDisplayIndicator && Marker)
	{
		Marker->AddStateTag(NexusGameplayTags::WorldMarker_State_Visible);
		
		IndicatorWidgetComponent->Activate();
	}
}

void UNexusInteractableComponent::HideIndicator()
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

	if (IsPlayerInRange()) ShowIndicator();
}

void UNexusInteractableComponent::InitializeIndicatorWidget()
{
	if (!IndicatorWidgetClass) return;
	
	AActor* Owner = GetOwner();
	if (!Owner) return;
	
	UActorComponent* NewComp = Owner->AddComponentByClass(
			UWidgetComponent::StaticClass(),
			true,
			FTransform::Identity,
			true);

	IndicatorWidgetComponent = Cast<UWidgetComponent>(NewComp);

	if (!IndicatorWidgetComponent) return;

	IndicatorWidgetComponent->AttachToComponent(IndicatorTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	IndicatorWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	IndicatorWidgetComponent->SetDrawAtDesiredSize(true);
	IndicatorWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IndicatorWidgetComponent->SetWidgetClass(IndicatorWidgetClass);
	IndicatorWidgetComponent->PrimaryComponentTick.TickGroup = TG_PostUpdateWork;
	
	Owner->FinishAddComponent(IndicatorWidgetComponent, true, FTransform::Identity);
	
	// Widget may not be instantiated yet; force it.
	IndicatorWidgetComponent->InitWidget();
	if (UNexusWorldMarkerWidget* MarkerRetry = GetMarkerWidget())
	{
		MarkerRetry->SetContext(IndicatorTarget, Owner);
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


