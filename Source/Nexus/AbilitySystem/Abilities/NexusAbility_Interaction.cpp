// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_Interaction.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/Util/NexusHeroPlayerUtility.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"

namespace
{
	// Cached CVar values — refreshed via per-CVar change callbacks so the hot path
	// reads plain ints/floats instead of going through atomic loads each frame.
	int32 GShowInteractionFocusReach = 0;
	int32 GShowInteractionAwareness = 0;
	float GAwarenessRadiusOverride = -1.0f;
	float GFocusReachOverride = -1.0f;

	TAutoConsoleVariable<int32> CVarShowInteractionFocusReach(
		TEXT("Nexus.Interaction.Show.FocusReach"),
		0,
		TEXT("0: Hide Interaction Show Focus Reach\n1: Show Interaction Show Focus Reach"),
		ECVF_Cheat
	);

	TAutoConsoleVariable<int32> CVarShowInteractionAwareness(
		TEXT("Nexus.Interaction.Show.Awareness"),
		0,
		TEXT("0: Hide Interaction Show Awareness\n1: Show Interaction Show Awareness"),
		ECVF_Cheat
	);

	TAutoConsoleVariable<float> CVarAwarenessRadiusOverride(
		TEXT("Nexus.Interaction.AwarenessRadiusOverride"),
		-1.0f,
		TEXT("Override the proximity detection radius. Set to -1 to use default."),
		ECVF_Cheat
	);

	TAutoConsoleVariable<float> CVarFocusReachOverride(
		TEXT("Nexus.Interaction.FocusReachOverride"),
		-1.0f,
		TEXT("Override the focus reach distance. Set to -1 to use default."),
		ECVF_Cheat
	);

	struct FInteractionCVarBinder
	{
		FInteractionCVarBinder()
		{
			// Seed cached values from initial defaults.
			GShowInteractionFocusReach = CVarShowInteractionFocusReach.GetValueOnGameThread();
			GShowInteractionAwareness  = CVarShowInteractionAwareness.GetValueOnGameThread();
			GAwarenessRadiusOverride   = CVarAwarenessRadiusOverride.GetValueOnGameThread();
			GFocusReachOverride        = CVarFocusReachOverride.GetValueOnGameThread();

			CVarShowInteractionFocusReach.AsVariable()->SetOnChangedCallback(
				FConsoleVariableDelegate::CreateLambda([](IConsoleVariable* V){ GShowInteractionFocusReach = V->GetInt(); }));
			CVarShowInteractionAwareness.AsVariable()->SetOnChangedCallback(
				FConsoleVariableDelegate::CreateLambda([](IConsoleVariable* V){ GShowInteractionAwareness = V->GetInt(); }));
			CVarAwarenessRadiusOverride.AsVariable()->SetOnChangedCallback(
				FConsoleVariableDelegate::CreateLambda([](IConsoleVariable* V){ GAwarenessRadiusOverride = V->GetFloat(); }));
			CVarFocusReachOverride.AsVariable()->SetOnChangedCallback(
				FConsoleVariableDelegate::CreateLambda([](IConsoleVariable* V){ GFocusReachOverride = V->GetFloat(); }));
		}
	};
	static FInteractionCVarBinder GInteractionCVarBinder;
}

UNexusAbility_Interaction::UNexusAbility_Interaction()
{
	FocusReachDistance = 150.0f;
	AwarenessRadius = 750.0f;
	AwarenessUpdateInterval= 0.1f;
}

void UNexusAbility_Interaction::InitializeAbility()
{
	StartAwarenessTimer();
}

void UNexusAbility_Interaction::OnDisableAbility()
{
	Super::OnDisableAbility();
	
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle_UpdateInteractables);
	}
	
	ClearAwarenessState();
}

void UNexusAbility_Interaction::OnEnableAbility()
{
	Super::OnEnableAbility();
	
	StartAwarenessTimer();
}

void UNexusAbility_Interaction::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);

	TraceForInteractables();
}

bool UNexusAbility_Interaction::CanTick()
{
	return IsEnabled() && NearbyInteractables.Num() > 0;
}

void UNexusAbility_Interaction::TraceForInteractables()
{
	const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner());
	if (!Char)
	{
		UpdateInteractionTarget(nullptr);
		return;
	}

	const EDrawDebugTrace::Type DebugTrace = GShowInteractionFocusReach != 0
		? EDrawDebugTrace::ForDuration
		: EDrawDebugTrace::None;

	float CurrentDistance = FocusReachDistance;
	if (GFocusReachOverride >= 0.f)
	{
		CurrentDistance = GFocusReachOverride;
	}
    
	FHitResult Hit;
	const bool bHit = UNexusHeroPlayerUtility::CameraForwardTrace(
		Char,
		CurrentDistance,
		UEngineTypes::ConvertToTraceType(NexusCollisionChannels::Interaction),
		Hit,
		DebugTrace,
		0.0f
	);

	UNexusInteractableComponent* NewTarget = nullptr;
    
	if (bHit)
	{
		if (AActor* Actor = Hit.GetActor())
		{
			// Gate focus on awareness: the focus trace originates at the camera and
			// can reach further than the awareness sphere (which is centered on the
			// actor). Requiring the actor to already be in NearbyInteractables keeps
			// the two stages consistent — you can only focus what you're near.
			if (NearbyInteractables.Contains(Actor))
			{
				const UPrimitiveComponent* HitComp = Hit.GetComponent();

				TInlineComponentArray<UNexusInteractableComponent*> Comps(Actor);
				for (UNexusInteractableComponent* Comp : Comps)
				{
					if (Comp && Comp->GetInteractionTriggerTarget() == HitComp)
					{
						NewTarget = Comp;
						break;
					}
				}
			}
		}
	}

	UpdateInteractionTarget(NewTarget);
}


void UNexusAbility_Interaction::UpdateInteractionTarget(UNexusInteractableComponent* NewInteractionTarget)
{
	UNexusInteractableComponent* Previous = InteractionTarget.Get();
	// IsStale is true when the weak ptr held a valid object that has since been
	// garbage-collected. In that case Get() returns null, so the Previous ==
	// NewInteractionTarget short-circuit would incorrectly suppress the focus-lost
	// notification.
	const bool bTargetWasDestroyed = InteractionTarget.IsStale();

	if (Previous == NewInteractionTarget && !bTargetWasDestroyed) return;

	if (Previous)
	{
		INexusInteractableInterface::Execute_OnLostPlayerFocus(Previous);
	}
	else if (bTargetWasDestroyed)
	{
		// Component is already dead — can't call into it. Broadcast the ability-level
		// event so listeners (HUD prompts, etc.) can clear focus-dependent state.
		OnInteractionFocusCleared.Broadcast();
	}

	InteractionTarget = NewInteractionTarget;

	if (NewInteractionTarget)
	{
		INexusInteractableInterface::Execute_OnGainedPlayerFocus(NewInteractionTarget);
	}
}


void UNexusAbility_Interaction::StartAwarenessTimer()
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			TimerHandle_UpdateInteractables, 
			this, 
			&UNexusAbility_Interaction::UpdateNearbyInteractables, 
			AwarenessUpdateInterval, 
			true
		);
	}
}

void UNexusAbility_Interaction::UpdateNearbyInteractables()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	const EDrawDebugTrace::Type DebugTrace = GShowInteractionAwareness  != 0 ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
	float CurrentRadius = AwarenessRadius;
	if (GAwarenessRadiusOverride >= 0.f)
	{
		CurrentRadius = GAwarenessRadiusOverride;
	}
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);
	TArray<FHitResult> Hits;
	const FVector Location = Owner->GetActorLocation();
	
	UKismetSystemLibrary::SphereTraceMulti(
		Owner,
		Location,
		Location,
		CurrentRadius,
		UEngineTypes::ConvertToTraceType(NexusCollisionChannels::Interaction),
		false,
		ActorsToIgnore,
		DebugTrace,
		Hits,
		true,
		FLinearColor::Red,
		FLinearColor::Green, 
		AwarenessUpdateInterval
	);

	TSet<TWeakObjectPtr<AActor>> NewNearbyInteractables;
	NewNearbyInteractables.Reserve(Hits.Num());

	auto FireOnComponents = [](AActor* Actor, bool bEntered)
	{
		TInlineComponentArray <UNexusInteractableComponent*> Comps;
		Actor->GetComponents(Comps);
		for (UNexusInteractableComponent* Comp : Comps)
		{
			if (!Comp) continue;
			if (bEntered)
				INexusInteractableInterface::Execute_OnEnteredPlayerRange(Comp);
			else
				INexusInteractableInterface::Execute_OnLeftPlayerRange(Comp);
		}
	};

	for (const FHitResult& Hit : Hits)
	{
		AActor* Actor = Hit.GetActor();
		if (!IsValid(Actor)) continue;

		// GetComponents skips actors with no interactable components, which
		// guards against a non-interactable primitive landing in the results
		// if someone ever configures a collision response that causes it.
		TInlineComponentArray<UNexusInteractableComponent*> Comps(Actor);
		if (Comps.Num() == 0) continue;

		bool bNewlyAdded = false;
		NewNearbyInteractables.Add(Actor, &bNewlyAdded);

		if (bNewlyAdded && !NearbyInteractables.Contains(Actor))
		{
			FireOnComponents(Actor, /*bEntered=*/true);
		}
	}
	
	for (const TWeakObjectPtr<AActor>& OldActor : NearbyInteractables)
	{
		if (OldActor.IsValid() && !NewNearbyInteractables.Contains(OldActor))
		{
			FireOnComponents(OldActor.Get(), /*bEntered=*/false);
		}
	}

	NearbyInteractables = MoveTemp(NewNearbyInteractables);
}

void UNexusAbility_Interaction::ClearAwarenessState()
{
	// Clear focus first so listeners see LostFocus before LeftRange.
	UpdateInteractionTarget(nullptr);

	for (const TWeakObjectPtr<AActor>& WeakActor : NearbyInteractables)
	{
		AActor* Actor = WeakActor.Get();
		if (!Actor) continue;

		TInlineComponentArray<UNexusInteractableComponent*> Comps(Actor);
		for (UNexusInteractableComponent* Comp : Comps)
		{
			if (Comp)
			{
				INexusInteractableInterface::Execute_OnLeftPlayerRange(Comp);
			}
		}
	}
	NearbyInteractables.Empty();
}