#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Nexus/Input/NexusInputTypes.h"

#include "NexusLocomotionInputComponent.generated.h"

struct FNexusInputActionPayload;


/**
 * The Move / Look listener. A small pawn component that subscribes to Input.Move and
 * Input.Look on the manager and feeds them to the pawn (movement input + control
 * rotation) — the home the hero's Move() / Look() handlers move to. Kept a dedicated
 * component (not folded into the movement component) so an AI pawn omits it cleanly and
 * never wires player input.
 *
 * Examine and other modal sub-modes are handled by the context stack, not here: while
 * Examine is active the gameplay IMC is suspended and Look resolves to
 * Input.Examine.Rotate instead, so this component simply stops receiving Look — no
 * IsExamining() branch.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusLocomotionInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNexusLocomotionInputComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool HandleMove(const FNexusInputActionPayload& Payload);
	bool HandleLook(const FNexusInputActionPayload& Payload);

	FNexusInputListenerHandle MoveHandle;
	FNexusInputListenerHandle LookHandle;
};
