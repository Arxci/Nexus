// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "GameplayTagContainer.h"

#include "Engine/StreamableManager.h"

#include "EMSActorSaveInterface.h"

#include "NexusItemPickup.generated.h"

class UNexusInteractableComponent;
class UNexusItemDefinition;
class UStaticMeshComponent;


/**
 * Placeable world actor that hands a single item definition to whoever interacts
 * with it. Intentionally thin: it owns a mesh, an interactable, and the data
 * needed to call UNexusInventoryAcquireLibrary::AcquireItem — nothing else.
 *
 * All acquire-side concerns (AddItem, mark-seen, auto-equip choice, ceremony
 * routing) live in the library, so a debug spawn, a quest reward, or a loot
 * drop can deliver the same item with the same behaviour without going through
 * a pickup actor.
 *
 * Visual lifecycle on a successful pickup:
 *   1. The acquire library runs (synchronous AddItem + queued AssignAndActivate).
 *   2. The pickup hides itself + disables collision so the player reads
 *      "the world model became my item" immediately.
 *   3. Destruction is deferred by TeardownDelaySeconds to cover the (possibly
 *      cold) Equipped-bundle load and the ceremony arms montage. Without this
 *      delay, first-acquire pickups show a visible gap between the world model
 *      vanishing and the gun materialising in the player's hands.
 */
UCLASS(Blueprintable, PrioritizeCategories = ("Pickup"))
class NEXUS_API ANexusItemPickup : public AActor, public IEMSActorSaveInterface
{
	GENERATED_BODY()

public:
	ANexusItemPickup();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void ConfigurePickup(UNexusItemDefinition* InDefinition, int32 InCount);

	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void HandleInteractionCompleted(AActor* Interactor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UNexusInteractableComponent> Interactable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UNexusItemDefinition> Definition;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadOnly, Category = "Pickup", meta = (ClampMin = "1"))
	int32 InitialCount = 1;

	/**
	 * Per-pickup-actor decision: should the acquired item be slotted into the
	 * player's equipment if a compatible slot is free? Lives on the pickup
	 * instance, not the item definition, because the same gun spawned by a
	 * quest reward vs a loot crate vs a hidden secret might want different
	 * defaults. UNexusInventoryAcquireLibrary::AcquireItem honours the flag.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bAutoEquipOnPickup = true;

	/**
	 * Force-skip the first-acquire ceremony even when the equippable authors one.
	 * Useful for "given as a tutorial" pickups where the player is already in a
	 * scripted sequence and the cinematic intro would step on it. Has no effect
	 * if the definition has already been seen (ceremony wouldn't fire anyway).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bSkipCeremony = false;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadOnly, Category = "Pickup")
	TMap<FGameplayTag, int32> InitialStatTags;

	/**
	 * Seconds between AddItem success and actor destruction. The pickup hides
	 * its mesh + drops collision immediately so the world model "vanishes" on
	 * the player's input, but the actor stays alive briefly so the equipped
	 * actor has time to spawn through the async Equipped-bundle load and play
	 * its draw / ceremony anim. Tune longer for definitions that author long
	 * ceremony montages; 0 destroys synchronously (good for ammo / consumables
	 * where there's no equipment hand-off).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (ClampMin = "0.0"))
	float TeardownDelaySeconds = 1.5f;

	UPROPERTY(SaveGame)
	bool bWasCollected = false;

protected:
	//~Start save interface
	virtual void ActorLoaded_Implementation() override;
	//~End save interface

private:
	TSharedPtr<FStreamableHandle> PickupMeshHandle;

	void RequestPickupMeshLoad();

	FTimerHandle PickupTeardownTimer;
	void HandleTeardownComplete();
};
