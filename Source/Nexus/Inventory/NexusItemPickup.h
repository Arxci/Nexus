// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EMSActorSaveInterface.h"
#include "GameplayTagContainer.h"
#include "Engine/StreamableManager.h"
#include "NexusItemPickup.generated.h"

class UNexusInteractableComponent;
class UNexusItemDefinition;
class UStaticMeshComponent;

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
	void HandleInteractionCompleted();
	
	class UNexusInventoryComponent* ResolveInventory(AActor* Interactor) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UNexusInteractableComponent> Interactable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	TObjectPtr<UNexusItemDefinition> Definition;

	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadOnly, Category = "Pickup", meta = (ClampMin = "1"))
	int32 InitialCount = 1;
	
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadOnly, Category = "Pickup")
	TMap<FGameplayTag, int32> InitialStatTags;

	UPROPERTY(SaveGame)
	bool bWasCollected = false;

	virtual void ActorLoaded_Implementation() override;

private:
	TSharedPtr<FStreamableHandle> PickupMeshHandle;
};