#include "NexusInteractionContext.h"

#include "GameFramework/Pawn.h"

#include "Kismet/GameplayStatics.h"

#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"

AActor* FNexusInteractionContext::GetInteractor() const
{
	return Interactor.Get();
}

AActor* FNexusInteractionContext::GetInteractableOwner() const
{
	const UNexusInteractableComponent* Comp = Interactable.Get();
	return Comp ? Comp->GetOwner() : nullptr;
}

UObject* FNexusInteractionContext::GetWorldContextObject() const
{
	if (AActor* Owner = GetInteractableOwner())
	{
		return Owner;
	}
	return GetInteractor();
}

UWorld* FNexusInteractionContext::GetWorld() const
{
	if (const UObject* WorldContext = GetWorldContextObject())
	{
		return WorldContext->GetWorld();
	}
	return nullptr;
}

APawn* FNexusInteractionContext::GetInteractorPawn() const
{
	if (APawn* Pawn = Cast<APawn>(GetInteractor()))
	{
		return Pawn;
	}
	// Fall back to the local player pawn — the interaction system passes a hero
	// character today, but a future AI-driven interaction might pass something
	// that isn't a pawn. Matches ANexusItemPickup::HandleInteractionCompleted.
	if (UWorld* World = GetWorld())
	{
		return UGameplayStatics::GetPlayerPawn(World, 0);
	}
	return nullptr;
}

UNexusInventoryComponent* FNexusInteractionContext::GetInteractorInventory() const
{
	APawn* Pawn = GetInteractorPawn();
	return Pawn ? Pawn->FindComponentByClass<UNexusInventoryComponent>() : nullptr;
}
