// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_Interaction.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/Util/NexusHeroPlayerUtility.h"
#include "Nexus/Character/NexusCharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"

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
	return IsEnabled();
}

void UNexusAbility_Interaction::TraceForInteractables()
{
	const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner());
	if (!Char)
	{
		UpdateInteractionTarget(nullptr);
		return;
	}

	const EDrawDebugTrace::Type DebugTrace = CVarShowInteractionFocusReach.GetValueOnGameThread() != 0
		? EDrawDebugTrace::ForDuration
		: EDrawDebugTrace::None;
    
	float CurrentDistance = FocusReachDistance;
	const float DistanceOverride = CVarFocusReachOverride.GetValueOnGameThread();
	if (DistanceOverride >= 0.f)
	{
		CurrentDistance = DistanceOverride;
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
		if (const AActor* Actor = Hit.GetActor())
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

	UpdateInteractionTarget(NewTarget);
}


void UNexusAbility_Interaction::UpdateInteractionTarget(UNexusInteractableComponent* NewInteractionTarget)
{
	UNexusInteractableComponent* Previous = InteractionTarget.Get();
	if (Previous == NewInteractionTarget) return;

	if (Previous)
	{
		INexusInteractableInterface::Execute_OnLostPlayerFocus(Previous);
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

	const EDrawDebugTrace::Type DebugTrace = CVarShowInteractionAwareness.GetValueOnGameThread() != 0 ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
	float CurrentRadius = AwarenessRadius;
	const float RadiusOverride = CVarAwarenessRadiusOverride.GetValueOnGameThread();

	if (RadiusOverride >= 0.f)
	{
		CurrentRadius = RadiusOverride;
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
		if (IsValid(Actor))
		{
			NewNearbyInteractables.Add(Actor);
			
			if (!NearbyInteractables.Contains(Actor))
			{
				FireOnComponents(Actor, /*bEntered=*/true);
			}
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

