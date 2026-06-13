#pragma once

#include "CoreMinimal.h"

#include "EnhancedInputComponent.h"

#include "NexusInputComponent.generated.h"

class UNexusInputManager;


/**
 * The per-pawn binder — a thin UEnhancedInputComponent that binds the manager's active
 * (Input Action -> verb) set to the manager's dispatch entry points (Lyra's
 * BindAbilityActions shape). It owns no per-action logic and no verb knowledge: it
 * pulls the resolved set from UNexusInputManager and re-binds whenever the manager
 * broadcasts that the applied contexts changed. Created and owned by
 * UNexusInputHostComponent; one per locally-controlled pawn.
 */
UCLASS()
class NEXUS_API UNexusInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	/** Adopt InManager: subscribe to its rebind broadcast and bind the current active set. */
	void InitializeBinder(UNexusInputManager* InManager);

	/** Drop the subscription and clear every binding. */
	void TearDownBinder();

private:
	/**
	 * The manager broadcast that the applied contexts changed. Defers the actual rebind to the
	 * next tick: this can fire from inside an input handler (a verb that pushes/pops a context),
	 * and mutating this component's action bindings mid-dispatch is unsafe.
	 */
	void HandleActiveBindingsChanged();

	/** Clear our bindings and bind each (action -> verb) for all four trigger phases. */
	void RebindFromManager();

	UPROPERTY(Transient)
	TWeakObjectPtr<UNexusInputManager> Manager;

	FDelegateHandle BindingsChangedHandle;
	FTimerHandle RebindTimerHandle;
	bool bRebindScheduled = false;
};
