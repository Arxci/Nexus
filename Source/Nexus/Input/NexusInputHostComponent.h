#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "NexusInputHostComponent.generated.h"

class APlayerController;
class UNexusInputComponent;
class UNexusInputContext;
class UNexusInputManager;


/**
 * The hero's ONLY input member. On possession by a local controller it creates the
 * per-pawn binder (UNexusInputComponent), pushes it onto the controller's input stack,
 * and registers the pawn with UNexusInputManager — which pushes the pawn's default
 * contexts (Gameplay at the bottom). On controller change / teardown it pops the binder
 * and unregisters the pawn.
 *
 * It holds no per-action methods and no verb knowledge: adding a verb is a data edit to
 * a context asset and never touches this component or the hero. An AI-controlled pawn
 * simply never has this component, so nothing registers and the input layer is a no-op
 * for it.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusInputHostComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNexusInputHostComponent();

	/** The contexts the pawn pushes when it becomes locally controlled (Gameplay at the bottom). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<TObjectPtr<UNexusInputContext>> DefaultContexts;

	/**
	 * Re-evaluate wiring after the owning pawn's controller changed. Called by
	 * ANexusCharacterBase::PossessedBy / UnPossessed so a possession swap (escort segment,
	 * AI <-> player handover) rewires input without stranding it on the old pawn. Tears down
	 * any prior wiring, then sets up again if the new controller is a local player.
	 */
	void NotifyControllerChanged();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool IsLocallyControlledPlayer() const;
	void SetUpInput();
	void TearDownInput();

	UPROPERTY(Transient)
	TObjectPtr<UNexusInputComponent> Binder;

	UPROPERTY(Transient)
	TWeakObjectPtr<APlayerController> BoundController;

	/** Cached at setup so teardown can still reach the manager after the controller has gone. */
	UPROPERTY(Transient)
	TWeakObjectPtr<UNexusInputManager> BoundManager;

	bool bInputSetUp = false;
};
