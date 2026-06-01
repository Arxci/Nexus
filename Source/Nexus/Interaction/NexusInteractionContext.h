#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "UObject/WeakObjectPtr.h"

class AActor;
class APawn;
class UNexusInteractableComponent;
class UNexusInventoryComponent;
struct FNexusInteractionResult;


/**
 * Lightweight, transient bundle passed to every condition's IsMet and every
 * effect's Execute. It identifies who is interacting and what they are
 * interacting with, plus a few resolved accessors (interactor pawn, inventory,
 * world) so conditions/effects don't each re-derive them.
 *
 * Deliberately NOT a USTRUCT: the verb/condition/effect model is resolved in
 * C++ (per the locked design decision), so this never needs reflection. It is a
 * pure runtime helper with no UPROPERTYs and no save footprint.
 */
struct FNexusInteractionContext
{
	/** The actor that initiated the interaction (host-agnostic — player pawn, AI, turret…). */
	TWeakObjectPtr<AActor> Interactor;

	/** The interactable component being driven. */
	TWeakObjectPtr<UNexusInteractableComponent> Interactable;

	/** The active entry's state key (its Verb by default) — used by consumed-state conditions/effects. */
	FGameplayTag StateKey;

	/**
	 * Optional sink the component owns for effects to report outcomes into (e.g.
	 * GiveItem records what it placed). Null during condition evaluation; set only
	 * while effects run on completion. Effects must null-check it.
	 */
	FNexusInteractionResult* Result = nullptr;

	AActor* GetInteractor() const;
	AActor* GetInteractableOwner() const;

	/** A UObject safe to pass as a world-context (the interactable owner, else the interactor). */
	UObject* GetWorldContextObject() const;
	UWorld*  GetWorld() const;

	/** The interactor as a pawn, falling back to the local player pawn (mirrors the pickup's rule). */
	APawn* GetInteractorPawn() const;

	/** The interactor pawn's inventory component, or null. */
	UNexusInventoryComponent* GetInteractorInventory() const;
};
