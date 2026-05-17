// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "GameplayTagContainer.h"

#include "Engine/StreamableManager.h"

#include "EMSActorSaveInterface.h"

#include "NexusItemPickup.generated.h"

class UAnimMontage;
class ANexusEquippedActor;
class UNexusEquipmentComponent;
class UNexusInteractableComponent;
class UNexusInventoryComponent;
class UNexusItemDefinition;
class UNexusItemInstance;
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
    void HandleInteractionCompleted(AActor* Interactor);

    /**
     * Commit the pickup synchronously: AddItem, optionally auto-assign +
     * activate the slot, and destroy the actor. Used when there's no ceremony
     * to play.
     */
    void FinishPickup(UNexusInventoryComponent* Inventory, AActor* Interactor);

    /**
     * Ceremony entry point. Does AddItem + stat tags + seen-marking first
     * (so the item is in inventory even if the ceremony interrupts), then
     * branches:
     *   - If any picked-up instance has bAutoAssignOnPickup with a free
     *     compatible slot, drive the equip + ceremony flow through
     *     OnSlotAssigned, suppressing the standard unholster.
     *   - Otherwise play arms-only ceremony (e.g. key items, consumables).
     * Returns true if a ceremony or auto-equip flow was successfully kicked
     * off; false to fall back to the immediate path.
     */
    bool BeginCeremony(UNexusInventoryComponent* Inventory, AActor* Interactor);

    /**
     * Honor FNexusFragment_Equippable::bAutoAssignOnPickup. Resolves the
     * interactor's equipment component, picks PreferredSlot when free (else
     * the first compatible free slot), assigns, and activates. No-op if the
     * item isn't equippable, the flag isn't set, or no free slot exists.
     */
    void AutoEquipIfRequested(UNexusItemInstance* Instance, AActor* Interactor) const;

    /**
     * Pick the slot a freshly picked-up Instance should auto-assign into:
     * PreferredSlot when valid and free, else the first compatible free slot
     * the Equipment exposes. Returns an invalid tag when nothing's free or
     * the item isn't slot-compatible. Shared by the immediate and ceremony
     * auto-equip paths so both make the same selection.
     */
    FGameplayTag PickAutoEquipSlot(const UNexusEquipmentComponent* Equipment,
        const UNexusItemInstance* Instance, const struct FNexusFragment_Equippable* Eq) const;

    /**
     * Play the authored ceremony montages: arms on the interactor's arms mesh,
     * item on the equipped actor's mesh (when one exists). Returns the longer
     * of the two play lengths so the caller can schedule completion. Returns
     * 0 when neither stream could play.
     */
    float PlayCeremonyMontages(AActor* Interactor, ANexusEquippedActor* EquippedActor) const;

    UFUNCTION()
    void HandleSlotAssignedForCeremony(FGameplayTag SlotTag, UNexusItemInstance* Instance);

    void OnCeremonyFinished();

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

    /**
     * First-time pickup ceremony — the arms-side montage played on the
     * interactor's arms mesh the first time they pick up this item definition
     * (per-save state via UNexusInventoryComponent::HasSeenItemDefinition).
     * Leave null for mundane loot; author for legendary/quest items where the
     * pickup deserves a beat. Subsequent pickups of the same def — even from
     * a different pickup actor — skip the ceremony.
     *
     * In the Pickup asset bundle so it's already loaded by the time the
     * player triggers the ceremony — same handle that streamed the pickup
     * mesh during BeginPlay covers this.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Ceremony",
        meta = (AssetBundles = "Pickup"))
    TSoftObjectPtr<UAnimMontage> CeremonyArmsMontage;

    /**
     * First-time pickup ceremony — the item-side montage played on the
     * equipped actor's mesh (the gun's own slide/bolt/handle animation)
     * during the ceremony. Only plays when the picked-up item is being
     * auto-equipped (otherwise there's no item mesh to animate). Optional
     * even on auto-equip pickups — e.g. a flashlight ceremony might only
     * author arms.
     *
     * When this stream is present alongside the arms montage, the equipment
     * component's standard unholster is suppressed for this activation so
     * the two ceremony anims aren't fighting the draw-phase unholster on
     * the same anim instance. Subsequent equip-from-slot calls use the
     * normal unholster path — the suppression is one-shot.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Ceremony",
        meta = (AssetBundles = "Pickup"))
    TSoftObjectPtr<UAnimMontage> CeremonyItemMontage;

    UPROPERTY(SaveGame)
    bool bWasCollected = false;

protected:
	//~Start save interface
	virtual void ActorLoaded_Implementation() override;
	//~End save interface

private:
	TSharedPtr<FStreamableHandle> PickupMeshHandle;

	void RequestPickupMeshLoad();

	/** Timer that fires OnCeremonyFinished after the max ceremony duration elapses. */
	FTimerHandle PickupCeremonyTimer;

	/**
	 * Set when an auto-equip ceremony is mid-flight, so HandleSlotAssignedForCeremony
	 * can finish wiring up the activation + montage playback once the async
	 * AssignToSlot completes. Weak so we don't keep the player's equipment
	 * component alive past its actor.
	 */
	TWeakObjectPtr<UNexusEquipmentComponent> PendingCeremonyEquipment;
	FGameplayTag                              PendingCeremonySlot;

	/**
	 * Captured at HandleInteractionCompleted time so the OnSlotAssigned handler
	 * + ceremony-finish timer know whose arms mesh and ASC to target. Weak so
	 * the pickup doesn't pin the player after the ceremony begins.
	 */
	TWeakObjectPtr<AActor> PendingFinishInteractor;
};