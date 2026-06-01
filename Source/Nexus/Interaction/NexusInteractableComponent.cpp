#include "NexusInteractableComponent.h"

#include "Components/WidgetComponent.h"

#include "Nexus/Nexus.h"
#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/UI/World/NexusWorldMarkerWidget.h"
#include "Nexus/Interaction/NexusInteractionContext.h"


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
	// Idempotent: a second Start without a Stop is a no-op so a chatty input
	// stream can't double-fire the lifecycle.
	if (CurrentInteractor) return;

	// Resolve which interaction to run. With authored entries we pick the best
	// ENABLED one for this interactor; if every entry is gated we surface the
	// reason and abort (never silently do nothing). With no entries we fall back
	// to the legacy single-hold path so pre-data interactables keep working.
	int32 ChosenIndex = INDEX_NONE;
	float Duration = InteractionDuration;
	if (Interactions.Num() > 0)
	{
		FText GatedReason;
		ChosenIndex = ResolveBestInteraction(Interactor, GatedReason);
		if (ChosenIndex == INDEX_NONE)
		{
			OnInteractionGateFailed.Broadcast(Interactor, GatedReason);
#if !UE_BUILD_SHIPPING
			UE_LOG(LogNexusInteraction, Verbose, TEXT("[Interact] %s blocked on %s (%s)."),
				*GetNameSafe(Interactor), *GetNameSafe(GetOwner()), *GatedReason.ToString());
#endif
			return;
		}
		Duration = Interactions[ChosenIndex].HoldDuration;
	}

	CurrentInteractor = Interactor;
	ActiveInteractionIndex = ChosenIndex;
	ActiveHoldDuration = Duration;
	if (const UWorld* World = GetWorld())
	{
		InteractionStartTime = World->GetTimeSeconds();
	}
	OnInteractionStarted.Broadcast(Interactor);

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInteraction, Verbose, TEXT("[Interact] %s started interaction on %s (duration=%.2fs)."),
		*GetNameSafe(Interactor), *GetNameSafe(GetOwner()), Duration);
#endif

	if (Duration <= 0.0f)
	{
		// Tap-to-interact: no hold required, complete on the same call so callers
		// who expect a synchronous interaction (instant lootables) get it.
		CompleteInteraction();
		return;
	}

	SetComponentTickEnabled(true);
}

void UNexusInteractableComponent::TryStopInteraction_Implementation(AActor* Interactor)
{
	// Stop is "cancel" — held below the duration. The auto-completion path is in
	// InteractionProgress, not here, so listeners can distinguish bail-out from
	// successful hold.
	if (!CurrentInteractor) return;
	if (CurrentInteractor != Interactor) return;

	CancelInteraction();
}

void UNexusInteractableComponent::InteractionProgress_Implementation()
{
	if (!CurrentInteractor) return;

	const float Elapsed = GetElapsedTime();
	OnInteractionProgressed.Broadcast(Elapsed);

	if (ActiveHoldDuration > 0.0f && Elapsed >= ActiveHoldDuration)
	{
		CompleteInteraction();
	}
}

void UNexusInteractableComponent::CompleteInteraction()
{
	AActor* Interactor = CurrentInteractor;
	const int32 Index = ActiveInteractionIndex;
	CurrentInteractor = nullptr;
	ActiveInteractionIndex = INDEX_NONE;
	SetComponentTickEnabled(false);

	// Run the resolved entry's effects in order BEFORE broadcasting completion, so
	// the world has changed (item acquired, flag set) by the time listeners — e.g.
	// a pickup that hides + tears itself down on OnInteractionCompleted — react.
	if (Interactions.IsValidIndex(Index))
	{
		const FNexusInteraction& Entry = Interactions[Index];
		RunEffects(Entry, Interactor);
		if (Entry.bOneShot)
		{
			MarkInteractionConsumed(Entry.GetStateKey());
		}
	}

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInteraction, Verbose, TEXT("[Interact] %s completed interaction on %s."),
		*GetNameSafe(Interactor), *GetNameSafe(GetOwner()));
#endif

	OnInteractionCompleted.Broadcast(Interactor);
	OnInteractionEnded.Broadcast(Interactor);
}

void UNexusInteractableComponent::CancelInteraction()
{
	AActor* Interactor = CurrentInteractor;
	CurrentInteractor = nullptr;
	ActiveInteractionIndex = INDEX_NONE;
	SetComponentTickEnabled(false);

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInteraction, Verbose, TEXT("[Interact] %s cancelled interaction on %s."),
		*GetNameSafe(Interactor), *GetNameSafe(GetOwner()));
#endif

	OnInteractionCancelled.Broadcast(Interactor);
	OnInteractionEnded.Broadcast(Interactor);
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


// Interaction resolution + effects

FNexusInteractionContext UNexusInteractableComponent::BuildContext(AActor* Interactor, FGameplayTag StateKey) const
{
	FNexusInteractionContext Context;
	Context.Interactor = Interactor;
	Context.Interactable = const_cast<UNexusInteractableComponent*>(this);
	Context.StateKey = StateKey;
	return Context;
}

bool UNexusInteractableComponent::IsInteractionEnabled(const FNexusInteraction& Entry, AActor* Interactor, FText& OutFailReason) const
{
	const FNexusInteractionContext Context = BuildContext(Interactor, Entry.GetStateKey());
	for (const TInstancedStruct<FNexusInteractionCondition>& ConditionStruct : Entry.Conditions)
	{
		const FNexusInteractionCondition* Condition = ConditionStruct.GetPtr<const FNexusInteractionCondition>();
		if (!Condition) continue;
		if (!Condition->IsMet(Context))
		{
			OutFailReason = Condition->GetFailReason(Context);
			return false;
		}
	}
	return true;
}

int32 UNexusInteractableComponent::ResolveBestInteraction(AActor* Interactor, FText& OutGatedReason) const
{
	int32 BestIndex = INDEX_NONE;
	int32 BestPriority = MIN_int32;
	bool bAnyGated = false;
	FText FirstGatedReason;

	for (int32 i = 0; i < Interactions.Num(); ++i)
	{
		const FNexusInteraction& Entry = Interactions[i];

		// A consumed one-shot is no longer offered.
		if (Entry.bOneShot && IsInteractionConsumed(Entry.GetStateKey())) continue;

		FText FailReason;
		if (IsInteractionEnabled(Entry, Interactor, FailReason))
		{
			// Highest Priority wins; on a tie, prefer the Primary slot.
			const bool bBetter =
				BestIndex == INDEX_NONE ||
				Entry.Priority > BestPriority ||
				(Entry.Priority == BestPriority &&
					static_cast<uint8>(Entry.Slot) < static_cast<uint8>(Interactions[BestIndex].Slot));
			if (bBetter)
			{
				BestIndex = i;
				BestPriority = Entry.Priority;
			}
		}
		else if (!bAnyGated)
		{
			bAnyGated = true;
			FirstGatedReason = FailReason;
		}
	}

	if (BestIndex == INDEX_NONE)
	{
		OutGatedReason = FirstGatedReason;
	}
	return BestIndex;
}

void UNexusInteractableComponent::RunEffects(const FNexusInteraction& Entry, AActor* Interactor)
{
	// Fresh result sink for this completion; effects report into it via the context.
	LastInteractionResult = FNexusInteractionResult();

	FNexusInteractionContext Context = BuildContext(Interactor, Entry.GetStateKey());
	Context.Result = &LastInteractionResult;

	for (const TInstancedStruct<FNexusInteractionEffect>& EffectStruct : Entry.Effects)
	{
		const FNexusInteractionEffect* Effect = EffectStruct.GetPtr<const FNexusInteractionEffect>();
		if (Effect)
		{
			Effect->Execute(Context);
		}
	}
}

void UNexusInteractableComponent::SetInteractions(TArray<FNexusInteraction> InInteractions)
{
	Interactions = MoveTemp(InInteractions);
}

void UNexusInteractableComponent::SetMarkerPrompt(const FText& PromptText)
{
	if (UNexusWorldMarkerWidget* Marker = GetMarkerWidget())
	{
		Marker->SetPromptText(PromptText);
	}
}

void UNexusInteractableComponent::MarkInteractionConsumed(FGameplayTag StateKey)
{
	if (StateKey.IsValid())
	{
		ConsumedInteractions.AddTag(StateKey);
	}
}

bool UNexusInteractableComponent::IsInteractionConsumed(FGameplayTag StateKey) const
{
	return StateKey.IsValid() && ConsumedInteractions.HasTag(StateKey);
}

void UNexusInteractableComponent::GetAvailableInteractions_Implementation(AActor* Interactor, TArray<FNexusResolvedInteraction>& OutInteractions)
{
	OutInteractions.Reset();

	// Legacy fallback: a single, always-enabled generic interaction with no verb.
	if (Interactions.Num() == 0)
	{
		FNexusResolvedInteraction Resolved;
		Resolved.HoldDuration = InteractionDuration;
		Resolved.bEnabled = true;
		Resolved.EntryIndex = INDEX_NONE;
		OutInteractions.Add(Resolved);
		return;
	}

	for (int32 i = 0; i < Interactions.Num(); ++i)
	{
		const FNexusInteraction& Entry = Interactions[i];

		// Consumed one-shots drop out of the prompt entirely.
		if (Entry.bOneShot && IsInteractionConsumed(Entry.GetStateKey())) continue;

		FNexusResolvedInteraction Resolved;
		Resolved.Verb = Entry.Verb;
		Resolved.HoldDuration = Entry.HoldDuration;
		Resolved.Slot = Entry.Slot;
		Resolved.Prompt = Entry.PromptOverride;
		Resolved.EntryIndex = i;

		FText FailReason;
		Resolved.bEnabled = IsInteractionEnabled(Entry, Interactor, FailReason);
		Resolved.FailReason = FailReason;

		OutInteractions.Add(Resolved);
	}
}


