#include "NexusHeroPlayerUtility.h"

#include "CollisionQueryParams.h"

#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#if ENABLE_DRAW_DEBUG
#include "DrawDebugHelpers.h"
#endif


bool UNexusHeroPlayerUtility::CameraForwardTrace(
	const APawn* Pawn,
	const float Distance,
	const ETraceTypeQuery TraceChannel,
	FHitResult& OutHit,
	const TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType, const float DrawTime,
	const bool bTraceComplex, const float SpreadHalfAngleDegrees)
{
	if (!Pawn) return false;

	UWorld* World = Pawn->GetWorld();
	if (!World) return false;

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

	// Low-level world trace with an FCollisionQueryParams ignore list instead of the
	// KismetSystemLibrary helper, so this per-tick interaction focus trace doesn't
	// heap-allocate an ignore-actor TArray every frame.
	FCollisionQueryParams Params(SCENE_QUERY_STAT(NexusCameraForwardTrace), bTraceComplex);
	Params.AddIgnoredActor(Pawn);

	const ECollisionChannel Channel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);
	const bool bHit = World->LineTraceSingleByChannel(OutHit, Start, End, Channel, Params);

#if ENABLE_DRAW_DEBUG
	if (DrawDebugType != EDrawDebugTrace::None)
	{
		DrawDebugLine(World, Start, bHit ? OutHit.ImpactPoint : End, FColor::Red, false, DrawTime);
		if (bHit)
		{
			DrawDebugSphere(World, OutHit.ImpactPoint, 8.0f, 12, FColor::Green, false, DrawTime);
		}
	}
#endif

	return bHit;
}