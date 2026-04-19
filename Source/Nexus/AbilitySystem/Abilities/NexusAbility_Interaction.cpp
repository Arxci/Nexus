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


void UNexusAbility_Interaction::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);

	if (const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(GetOwner()))
	{
		FHitResult Hit;
		if (UNexusHeroPlayerUtility::CameraForwardTrace(Char, FocusReachDistance, UEngineTypes::ConvertToTraceType(NexusCollisionChannels::Interaction), Hit, EDrawDebugTrace::ForDuration, 0.0f))
		{
			// ...
		}
	}
}

bool UNexusAbility_Interaction::CanTick()
{
	return IsEnabled();
}

void UNexusAbility_Interaction::UpdateNearbyInteractables()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);
	TArray<AActor*> Overlapped;
	
	UKismetSystemLibrary::SphereOverlapActors(
		Owner,
		Owner->GetActorLocation(),
		AwarenessRadius,
		{ UEngineTypes::ConvertToObjectType(NexusCollisionChannels::Interaction) },
		AActor::StaticClass(),
		ActorsToIgnore,
		Overlapped
	);

	TSet<TWeakObjectPtr<AActor>> NewNearbyInteractables;
	NewNearbyInteractables.Reserve(Overlapped.Num());

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

	for (AActor* Actor : Overlapped)
	{
		if (IsValid(Actor))
		{
			NewNearbyInteractables.Add(Actor);
			
			DrawDebugPoint(GetWorld(), Actor->GetActorLocation(), 10.f, FColor::Cyan, false, -1.f);
			
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

