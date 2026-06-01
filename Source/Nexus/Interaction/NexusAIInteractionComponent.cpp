#include "NexusAIInteractionComponent.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/Interaction/NexusInteractableInterface.h"
#include "Nexus/NexusCollisionChannels.h"

UNexusInteractableComponent* UNexusAIInteractionComponent::GetInteractable(AActor* Target)
{
	return Target ? Target->FindComponentByClass<UNexusInteractableComponent>() : nullptr;
}

bool UNexusAIInteractionComponent::TryInteract(AActor* Target)
{
	UNexusInteractableComponent* Interactable = GetInteractable(Target);
	AActor* Interactor = GetOwner();
	if (!Interactable || !Interactor) return false;

	// Only start if at least one interaction is enabled for this AI interactor —
	// the same host-agnostic gate the player goes through.
	TArray<FNexusResolvedInteraction> Resolved;
	INexusInteractableInterface::Execute_GetAvailableInteractions(Interactable, Interactor, Resolved);

	bool bAnyEnabled = false;
	for (const FNexusResolvedInteraction& Entry : Resolved)
	{
		if (Entry.bEnabled) { bAnyEnabled = true; break; }
	}
	if (!bAnyEnabled) return false;

	INexusInteractableInterface::Execute_TryStartInteraction(Interactable, Interactor);
	return true;
}

void UNexusAIInteractionComponent::StopInteract(AActor* Target)
{
	UNexusInteractableComponent* Interactable = GetInteractable(Target);
	AActor* Interactor = GetOwner();
	if (!Interactable || !Interactor) return;

	INexusInteractableInterface::Execute_TryStopInteraction(Interactable, Interactor);
}

AActor* UNexusAIInteractionComponent::FindNearestInteractable(float Radius)
{
	AActor* Owner = GetOwner();
	if (!Owner) return nullptr;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);

	TArray<FHitResult> Hits;
	const FVector Location = Owner->GetActorLocation();

	UKismetSystemLibrary::SphereTraceMulti(
		Owner, Location, Location, Radius,
		UEngineTypes::ConvertToTraceType(NexusCollisionChannels::Interaction),
		false, ActorsToIgnore, EDrawDebugTrace::None, Hits, true);

	AActor* Best = nullptr;
	float BestDistSq = TNumericLimits<float>::Max();
	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!IsValid(HitActor)) continue;
		if (!HitActor->FindComponentByClass<UNexusInteractableComponent>()) continue;

		const float DistSq = FVector::DistSquared(Location, HitActor->GetActorLocation());
		if (DistSq < BestDistSq)
		{
			BestDistSq = DistSq;
			Best = HitActor;
		}
	}
	return Best;
}

AActor* UNexusAIInteractionComponent::TryInteractNearest(float Radius)
{
	AActor* Target = FindNearestInteractable(Radius);
	if (Target && TryInteract(Target))
	{
		return Target;
	}
	return nullptr;
}
