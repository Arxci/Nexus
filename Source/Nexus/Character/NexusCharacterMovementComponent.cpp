#include "NexusCharacterMovementComponent.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UNexusCharacterMovementComponent::UNexusCharacterMovementComponent()
{

}

void UNexusCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const ACharacter* Char = GetCharacterOwner())
	{
		StandingHalfHeight = Char->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	}
}

void UNexusCharacterMovementComponent::StartRunning()
{
	if (bIsRunning) return;

	bIsRunning = true;
	CachedWalkSpeed = MaxWalkSpeed;
	MaxWalkSpeed = MaxWalkSpeedRun;
	OnRunStart.Broadcast();
}

void UNexusCharacterMovementComponent::StopRunning()
{
	if (!bIsRunning) return;

	bIsRunning = false;
	MaxWalkSpeed = CachedWalkSpeed;
	OnRunEnd.Broadcast();
}

bool UNexusCharacterMovementComponent::IsMovingForward(float Threshold) const
{
	if (!IsMovingOnGround()) return false;
	
	const FVector InputVector = GetLastInputVector();
	if (InputVector.IsNearlyZero()) return false;

	const FVector Forward = GetOwner()->GetActorForwardVector();
	return FVector::DotProduct(Forward, InputVector.GetSafeNormal()) > Threshold;
}

bool UNexusCharacterMovementComponent::CanStand() const
{
	if (ACharacter* Char = Cast<ACharacter>(GetCharacterOwner()))
	{
		const UCapsuleComponent* Capsule = Char->GetCapsuleComponent();
		const float Radius = Capsule->GetScaledCapsuleRadius();
		const FVector Location = Char->GetActorLocation();

		const float CurrentHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
		const FVector TraceLocation = Location + FVector(0.f, 0.f, StandingHalfHeight - CurrentHalfHeight);

		TArray<FHitResult> Hits;
		UKismetSystemLibrary::CapsuleTraceMulti(
			Char->GetWorld(),
			TraceLocation,
			TraceLocation,
			Radius,
			StandingHalfHeight,
			UEngineTypes::ConvertToTraceType(ECC_Pawn),
			false,
			{Char},
			EDrawDebugTrace::None,
			Hits,
			true,
			FLinearColor::Green,  
			FLinearColor::Red,    
			0.f  
		);

		return Hits.IsEmpty();
	}
	return true;
}