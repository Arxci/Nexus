#include "NexusHeroPlayerUtility.h"

#include "GameFramework/Pawn.h"

#include "GameFramework/PlayerController.h"


bool UNexusHeroPlayerUtility::CameraForwardTrace(
	const APawn* Pawn,
	const float Distance,
	const ETraceTypeQuery TraceChannel,
	FHitResult& OutHit,
	const TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType, const float DrawTime,
	const bool bTraceComplex, const float SpreadHalfAngleDegrees)
{
	if (!Pawn) return false;

	FVector CamLoc;
	FRotator CamRot;
	if (const AController* Controller = Pawn->GetController())
	{
		// APlayerController routes this through the camera manager; an AIController
		// (or any other) falls back to the pawn's eye view point.
		Controller->GetPlayerViewPoint(CamLoc, CamRot);
	}
	else
	{
		Pawn->GetActorEyesViewPoint(CamLoc, CamRot);
	}

	const FVector Forward   = CamRot.Vector();
	const FVector Direction = SpreadHalfAngleDegrees > 0.0f
		? FMath::VRandCone(Forward, FMath::DegreesToRadians(SpreadHalfAngleDegrees))
		: Forward;

	const FVector Start = CamLoc;
	const FVector End   = Start + Direction * Distance;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(const_cast<APawn*>(Pawn));

	return UKismetSystemLibrary::LineTraceSingle(
		Pawn,                                              // WorldContextObject
		Start,
		End,
		TraceChannel,
		bTraceComplex,
		ActorsToIgnore,
		DrawDebugType,
		OutHit,
		true,                                              // bIgnoreSelf
		FLinearColor::Red,
		FLinearColor::Green,
		DrawTime                                             // DrawTime
	);
}