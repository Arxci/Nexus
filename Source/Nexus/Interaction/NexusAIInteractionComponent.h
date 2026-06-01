#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "NexusAIInteractionComponent.generated.h"

class UNexusInteractableComponent;


/**
 * The AI-side parallel to UNexusAbility_Interaction: it lets a non-player pawn
 * drive interactions through the very same INexusInteractableInterface, passing
 * itself as the Interactor. No special interactable code — a door, lever or
 * switch an AI uses is the exact same data-driven interactable the player uses.
 *
 * Because the model is host-agnostic, the conditions still apply to the AI
 * interactor: an AI with no inventory can open a world-state door or hit a switch
 * (its effects/gates read world state), but a RequiresItem/RequiresFreeSpace gate
 * naturally fails for it — exactly as intended.
 *
 * Driven externally (a Behavior Tree task calls TryInteract on a chosen actor) or
 * autonomously (TryInteractNearest scans the Interaction channel). The hold
 * resolves itself: TryStartInteraction enables the interactable's own tick, which
 * progresses to completion; the AI need not hold anything.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusAIInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Start an interaction on Target's interactable with this component's owner as the interactor. True if an enabled interaction was started. */
	UFUNCTION(BlueprintCallable, Category = "AI|Interaction")
	bool TryInteract(AActor* Target);

	/** Cancel an in-progress interaction this AI started on Target. */
	UFUNCTION(BlueprintCallable, Category = "AI|Interaction")
	void StopInteract(AActor* Target);

	/** Nearest interactable actor within Radius on the Interaction channel (autonomous detection). */
	UFUNCTION(BlueprintCallable, Category = "AI|Interaction")
	AActor* FindNearestInteractable(float Radius);

	/** Find the nearest interactable within Radius and interact with it; returns the chosen target or null. */
	UFUNCTION(BlueprintCallable, Category = "AI|Interaction")
	AActor* TryInteractNearest(float Radius);

private:
	static UNexusInteractableComponent* GetInteractable(AActor* Target);
};
