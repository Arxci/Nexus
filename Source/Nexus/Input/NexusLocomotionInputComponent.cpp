#include "NexusLocomotionInputComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"

#include "Nexus/Input/NexusInputManager.h"
#include "Nexus/NexusGameplayTags.h"

UNexusLocomotionInputComponent::UNexusLocomotionInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusLocomotionInputComponent::BeginPlay()
{
	Super::BeginPlay();

	// Player-only: with no manager (an AI pawn) this is a no-op and nothing registers.
	UNexusInputManager* Manager = UNexusInputManager::GetForActor(GetOwner());
	if (!Manager)
	{
		return;
	}

	MoveHandle = Manager->RegisterInputHandler(NexusGameplayTags::InputTag_Move,
		FNexusInputHandlerSignature::CreateUObject(this, &UNexusLocomotionInputComponent::HandleMove), GetOwner());
	LookHandle = Manager->RegisterInputHandler(NexusGameplayTags::InputTag_Look,
		FNexusInputHandlerSignature::CreateUObject(this, &UNexusLocomotionInputComponent::HandleLook), GetOwner());
}

void UNexusLocomotionInputComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UNexusInputManager* Manager = UNexusInputManager::GetForActor(GetOwner()))
	{
		Manager->UnregisterInputHandler(MoveHandle);
		Manager->UnregisterInputHandler(LookHandle);
	}
	Super::EndPlay(EndPlayReason);
}

bool UNexusLocomotionInputComponent::HandleMove(const FNexusInputActionPayload& Payload)
{
	// Move is a per-tick axis: act on Triggered only so the one-shot Started/Completed phases
	// don't double-add in the same frame.
	if (Payload.TriggerEvent != ENexusInputTriggerEvent::Triggered)
	{
		return false;
	}

	APawn* Pawn = Cast<APawn>(GetOwner());
	const AController* Controller = Pawn ? Pawn->GetController() : nullptr;
	if (!Controller)
	{
		return false;
	}

	const FVector2D MovementVector = Payload.AxisValue;
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	Pawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	Pawn->AddMovementInput(RightDirection,   MovementVector.X);
	return true;
}

bool UNexusLocomotionInputComponent::HandleLook(const FNexusInputActionPayload& Payload)
{
	if (Payload.TriggerEvent != ENexusInputTriggerEvent::Triggered)
	{
		return false;
	}

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
	{
		return false;
	}

	const FVector2D LookAxis = Payload.AxisValue;
	Pawn->AddControllerYawInput(LookAxis.X);
	Pawn->AddControllerPitchInput(LookAxis.Y);
	return true;
}
