// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EMSActorSaveInterface.h"
#include "GameplayTagContainer.h"
#include "NexusItemPickup.generated.h"

class UNexusInteractableComponent;
class UNexusItemDefinition;
class UStaticMeshComponent;

/**
 * Generic world pickup. One actor type covers every pickup in the game; the
 * specific item is data-driven by Definition + InitialCount + InitialStatTags.
 *
 * Hooks into UNexusInteractableComponent::OnInteractionEnded — picking up an
 * item is just a completed interaction. The pickup destroys itself once the
 * full count has been transferred to the player's inventory.
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

	UFUNCTION()
	void HandleInteractionCompleted();

	/** Resolves the inventory component on the interactor (typically the player pawn). */
	class UNexusInventoryComponent* ResolveInventory(AActor* Interactor) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UNexusInteractableComponent> Interactable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UNexusItemDefinition> Definition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (ClampMin = "1"))
	int32 InitialCount = 1;

	/** Optional: seed initial stat tags (e.g. AmmoInMag for a half-empty pickup). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TMap<FGameplayTag, int32> InitialStatTags;

	UPROPERTY(SaveGame)
	bool bWasCollected = false;

	virtual void ActorLoaded_Implementation() override;
};