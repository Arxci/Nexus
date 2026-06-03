#include "NexusHitDelivery_Hitscan.h"

#include "CollisionQueryParams.h"

#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "GameFramework/Pawn.h"

#if ENABLE_DRAW_DEBUG
#include "DrawDebugHelpers.h"
#endif

void UNexusHitDelivery_Hitscan::Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const
{
	UWorld* World = Request.ResolveWorld();
	if (!World) return;

	// Per-shot cone spread around the aim direction (effective hip / ADS spread).
	const FVector Dir = Request.SpreadHalfAngleDegrees > 0.0f
		? FMath::VRandCone(Request.Direction, FMath::DegreesToRadians(Request.SpreadHalfAngleDegrees))
		: Request.Direction;

	const FVector Start = Request.Origin;
	const FVector End   = Start + Dir * Request.Range;

	// Trace through the low-level world API with an FCollisionQueryParams ignore list (the
	// same approach the melee-sweep strategy uses), so a multi-pellet shotgun blast doesn't
	// heap-allocate an ignore-actor TArray for every pellet the way the Kismet helper did.
	FCollisionQueryParams Params(SCENE_QUERY_STAT(NexusHitscan), Request.bTraceComplex);
	if (AActor* Self = Request.GetContextActor())         Params.AddIgnoredActor(Self);
	if (APawn* IgnorePawn = Request.InstigatorPawn.Get()) Params.AddIgnoredActor(IgnorePawn);

	const ECollisionChannel Channel = UEngineTypes::ConvertToCollisionChannel(Request.TraceType);

	FHitResult Hit;
	const bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, Channel, Params);

#if ENABLE_DRAW_DEBUG
	if (Request.bDrawDebug)
	{
		DrawDebugLine(World, Start, bHit ? Hit.ImpactPoint : End, FColor::Red, false, Request.DebugDrawTime);
		if (bHit)
		{
			DrawDebugSphere(World, Hit.ImpactPoint, 8.0f, 12, FColor::Green, false, Request.DebugDrawTime);
		}
	}
#endif

	if (!bHit || !Hit.GetActor()) return;

	OutResult.Hits.Add(Hit);

	// Impulse along the actual ray-to-impact (post-spread), matching the prior inline path.
	RouteDamage(Request, Hit, /*PreMultiplier*/ 1.0f, Hit.ImpactPoint - Request.Origin, OutResult);
}
