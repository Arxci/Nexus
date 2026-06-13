#pragma once

#include "CoreMinimal.h"

#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/Input/NexusInputTypes.h"

#include "NexusAbility_Interaction.generated.h"

class UNexusInteractableComponent;
struct FNexusInputActionPayload;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFocusCleared);


UCLASS()
class NEXUS_API UNexusAbility_Interaction : public UNexusAbility
{
	GENERATED_BODY()
	
public:
	/**
	 * Broadcast when the previously focused interactable is destroyed between
	 * frames. No component pointer is provided (it's already dead); listeners
	 * should clear any focus-dependent state (HUD prompts, etc.).
	 */
	UPROPERTY(BlueprintAssignable)
	FOnInteractionFocusCleared OnInteractionFocusCleared;

	/**
	 * The currently focused interactable, or null if nothing under the reticle.
	 * Input handlers query this on press to know what to TryStartInteraction on.
	 */
	UFUNCTION(BlueprintPure, Category = "Interaction")
	UNexusInteractableComponent* GetFocusedInteractable() const { return InteractionTarget.Get(); }

protected:
	UNexusAbility_Interaction();

protected:
	virtual void OnDisableAbility() override;
	virtual void OnEnableAbility() override;

	virtual void InitializeAbility() override;
	virtual void TickAbility(float DeltaTime) override;
	virtual bool CanTick() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FocusReachDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AwarenessRadius;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AwarenessUpdateInterval;

	FTimerHandle TimerHandle_UpdateInteractables;

private:
	// Input
	/** Register/unregister the Input.Interact listener (player-only; no-op without a local manager). */
	void RegisterInteractInput();
	void UnregisterInteractInput();
	/** Started -> start the interaction on the focused target; Released -> cancel the one we started on. */
	bool HandleInteractInput(const FNexusInputActionPayload& Payload);

	FNexusInputListenerHandle InteractListenerHandle;

	/**
	 * The interactable we last called TryStartInteraction on. Used on release so a player who
	 * starts holding on A and looks away to B before releasing still cancels A — without this,
	 * A would keep ticking toward auto-complete because release reads the current focus.
	 */
	UPROPERTY()
	TWeakObjectPtr<UNexusInteractableComponent> ActiveInteractable;

	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> NearbyInteractables;

	UPROPERTY()
	TWeakObjectPtr<UNexusInteractableComponent> InteractionTarget;

	void TraceForInteractables();
	void UpdateInteractionTarget(UNexusInteractableComponent* NewInteractionTarget);
	void UpdateNearbyInteractables();
	void StartAwarenessTimer();
	void ClearAwarenessState();
};
