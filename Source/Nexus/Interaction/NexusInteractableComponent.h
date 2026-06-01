#pragma once

#include "CoreMinimal.h"

#include "UObject/PrimaryAssetId.h"

#include "Components/ActorComponent.h"

#include "ComponentPicker.h"

#include "GameplayTagContainer.h"

#include "EMSCompSaveInterface.h"

#include "NexusInteractableInterface.h"

#include "NexusInteraction.h"

#include "NexusInteractableComponent.generated.h"

class UWidgetComponent;
class UUserWidget;
class UNexusWorldMarkerWidget;
struct FNexusInteractionContext;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionProgressed, float, ElapsedTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionStarted, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionCompleted, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionCancelled, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionEnded, AActor*, Interactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionGateFailed, AActor*, Interactor, FText, Reason);


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusInteractableComponent : public UActorComponent, public INexusInteractableInterface, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusInteractableComponent();

	UFUNCTION(BlueprintPure, Category = "Interaction")
	float GetElapsedTime() const;

	UFUNCTION(BlueprintPure, Category = "Interaction")
	USceneComponent* GetIndicatorTarget() { return IndicatorTarget; }
	UFUNCTION(BlueprintPure, Category = "Interaction")
	UPrimitiveComponent* GetInteractionTriggerTarget() { return InteractionTriggerTarget; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//~Start interaction interface
	virtual void TryStartInteraction_Implementation(AActor* Interactor) override;
	virtual void TryStopInteraction_Implementation(AActor* Interactor) override;

	virtual void OnEnteredPlayerRange_Implementation() override;
	virtual void OnLeftPlayerRange_Implementation() override;

	virtual void OnGainedPlayerFocus_Implementation() override;
	virtual void OnLostPlayerFocus_Implementation() override;

	virtual void GetAvailableInteractions_Implementation(AActor* Interactor, TArray<FNexusResolvedInteraction>& OutInteractions) override;
	//~Stop interaction interface
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractionProgress();
	
	/**
	 * The interactions this object offers (verb + conditions + effects). On
	 * TryStartInteraction the component resolves the best ENABLED entry for the
	 * interactor, holds for that entry's HoldDuration, and runs its effects in
	 * order on completion. This is the data-driven model — a door, note, lever,
	 * safe or merchant differ only by the entries authored here, not by a C++
	 * actor subclass.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	TArray<FNexusInteraction> Interactions;

	/**
	 * Legacy single-hold fallback, used ONLY when Interactions is empty: the
	 * component holds for this duration and fires the delegates with no effects,
	 * so pre-data interactables (and listeners hand-bound to OnInteractionCompleted,
	 * like an un-migrated pickup) keep working. Author Interactions instead.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractionDuration = 0.0f;

public:
	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionProgressed OnInteractionProgressed;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionStarted OnInteractionStarted;

	/**
	 * Fires when the interaction was held for the full InteractionDuration (or
	 * immediately if Duration <= 0). This is the "success" signal — listeners
	 * like ANexusItemPickup that consume the world actor should bind here, NOT
	 * to OnInteractionEnded, so a player who taps-and-releases mid-hold doesn't
	 * accidentally trigger consumption.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionCompleted OnInteractionCompleted;

	/** Fires when the interactor released the input before InteractionDuration elapsed. */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionCancelled OnInteractionCancelled;

	/**
	 * Fires after either Completed or Cancelled. Intended for UI listeners that
	 * don't care which way the interaction ended (hide the progress bar, etc.).
	 */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionEnded OnInteractionEnded;

	/**
	 * Fires when a press resolves to no enabled interaction because every offered
	 * entry is gated (e.g. "Locked — needs Square Crank"). Carries the best gated
	 * entry's fail reason so the HUD can flash it. No hold is started.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionGateFailed OnInteractionGateFailed;

	// Per-interactable "already used" state, keyed by an interaction's StateKey
	// (its Verb by default). Marked SaveGame so it round-trips with the owning
	// actor's EMS save (the save wiring lands in a later phase); a consumed
	// one-shot entry is never offered again.
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void MarkInteractionConsumed(FGameplayTag StateKey);

	UFUNCTION(BlueprintPure, Category = "Interaction")
	bool IsInteractionConsumed(FGameplayTag StateKey) const;

	/** Aggregate result of the most recently completed interaction's effects (e.g. how much GiveItem placed). */
	UFUNCTION(BlueprintPure, Category = "Interaction")
	FNexusInteractionResult GetLastInteractionResult() const { return LastInteractionResult; }

	/** Replace the authored interactions at runtime — e.g. a pickup building its Take entry from its item definition. */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractions(TArray<FNexusInteraction> InInteractions);

	/** Push the resolved prompt line onto this interactable's world marker (called by the focus ability). */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetMarkerPrompt(const FText& PromptText);

protected:
	//Indicator
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interaction|Indicator")
	bool bDisplayIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interaction|Indicator")
	FComponentPicker  IndicatorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|Indicator")
	TSubclassOf<UNexusWorldMarkerWidget> IndicatorWidgetClass;
	UPROPERTY(Transient)
	TObjectPtr<UWidgetComponent> IndicatorWidgetComponent;
	
	UFUNCTION(BlueprintGetter)
	UNexusWorldMarkerWidget* GetMarkerWidget() const;
	
	void InitializeIndicatorWidget();

	UFUNCTION(BlueprintCallable)
	void ShowIndicator();
	UFUNCTION(BlueprintCallable)
	void HideIndicator();

//Utility	
protected:
	bool IsPlayerInRange() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintReadOnly, Category = "Interaction")
	FComponentPicker  InteractionTriggerComponent;

private:
	/**
	 * Runtime: actor whose TryStartInteraction call brought us into the in-progress
	 * state. Non-null while ticking; cleared on Complete or Cancel. Treat as the
	 * "is interaction in progress" flag — TryStartInteraction is a no-op when set.
	 */
	UPROPERTY(Transient)
	TObjectPtr<AActor> CurrentInteractor;

	/** Runtime: world time when the current interaction started. */
	float InteractionStartTime = 0.0f;

	/** Runtime: index into Interactions of the entry being held, or INDEX_NONE for the legacy single-hold path. */
	int32 ActiveInteractionIndex = INDEX_NONE;

	/** Runtime: hold duration of the active entry, cached so progress/complete don't re-resolve. */
	float ActiveHoldDuration = 0.0f;

	/** Runtime: aggregate outcome of the last completed interaction's effects (read by completion listeners). */
	UPROPERTY(Transient)
	FNexusInteractionResult LastInteractionResult;

	void CompleteInteraction();
	void CancelInteraction();

	/** Build the context passed to conditions/effects for a given interactor + state key. */
	FNexusInteractionContext BuildContext(AActor* Interactor, FGameplayTag StateKey) const;

	/** True if every condition on Entry is met for Interactor; otherwise fills OutFailReason from the first failing condition. */
	bool IsInteractionEnabled(const FNexusInteraction& Entry, AActor* Interactor, FText& OutFailReason) const;

	/** Index of the highest-priority ENABLED entry for Interactor (Primary preferred on ties), or INDEX_NONE; fills OutGatedReason when every entry is gated. */
	int32 ResolveBestInteraction(AActor* Interactor, FText& OutGatedReason) const;

	/** Run an entry's effects in order through the context (each mutates the world only via public APIs). */
	void RunEffects(const FNexusInteraction& Entry, AActor* Interactor);

	/** Per-interactable consumed-state (see MarkInteractionConsumed). Round-trips via the owning actor's EMS save once wired. */
	UPROPERTY(SaveGame)
	FGameplayTagContainer ConsumedInteractions;

	UPROPERTY()
	FGameplayTagContainer InteractableState;

	UPROPERTY(Transient)
	TObjectPtr<USceneComponent> IndicatorTarget;
	void ResolveIndicatorComponent();
	
	UPROPERTY(Transient)
	TObjectPtr<UPrimitiveComponent> InteractionTriggerTarget;
	void ResolveInteractionTriggerComponent();
};
