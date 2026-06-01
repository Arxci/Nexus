#include "NexusHitDelivery_Hitscan.h"

#include "GameFramework/Pawn.h"

#include "Kismet/KismetSystemLibrary.h"

void UNexusHitDelivery_Hitscan::Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const
{
	AActor* WorldContext = Request.GetContextActor();
	if (!WorldContext) return;

	// Per-shot cone spread around the aim direction (effective hip / ADS spread).
	const FVector Dir = Request.SpreadHalfAngleDegrees > 0.0f
		? FMath::VRandCone(Request.Direction, FMath::DegreesToRadians(Request.SpreadHalfAngleDegrees))
		: Request.Direction;

	const FVector Start = Request.Origin;
	const FVector End   = Start + Dir * Request.Range;

	TArray<AActor*> ActorsToIgnore;
	if (AActor* IgnorePawn = Request.InstigatorPawn.Get())
	{
		ActorsToIgnore.Add(IgnorePawn);
	}

	const EDrawDebugTrace::Type DrawDebug = Request.bDrawDebug
		? EDrawDebugTrace::ForDuration
		: EDrawDebugTrace::None;

	FHitResult Hit;
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(
		WorldContext, Start, End, Request.TraceType, Request.bTraceComplex, ActorsToIgnore,
		DrawDebug, Hit, /*bIgnoreSelf*/ true,
		FLinearColor::Red, FLinearColor::Green, Request.DebugDrawTime);

	if (!bHit || !Hit.GetActor()) return;

	OutResult.Hits.Add(Hit);

	// Impulse along the actual ray-to-impact (post-spread), matching the prior inline path.
	RouteDamage(Request, Hit, /*PreMultiplier*/ 1.0f, Hit.ImpactPoint - Request.Origin, OutResult);
}
