#include "NexusHitDelivery_MeleeSweep.h"

#include "CollisionQueryParams.h"
#include "CollisionShape.h"

#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "GameFramework/Pawn.h"

void UNexusHitDelivery_MeleeSweep::Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const
{
	UWorld* World = Request.ResolveWorld();
	if (!World) return;

	// Sweep a sphere from the weapon socket along the swing reach — a sphere swept along a
	// line is a capsule-shaped volume, which is the melee hit window.
	const FVector Start  = Request.MuzzleLocation;
	const FVector End    = Start + Request.Direction.GetSafeNormal() * Request.Range;
	const float   Radius = FMath::Max(1.0f, Request.SweepRadius);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(NexusMeleeSweep), /*bTraceComplex*/ false);
	if (AActor* Ignore = Request.InstigatorPawn.Get())
	{
		Params.AddIgnoredActor(Ignore);
	}

	const ECollisionChannel Channel = UEngineTypes::ConvertToCollisionChannel(Request.TraceType);

	TArray<FHitResult> Hits;
	World->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, Channel,
		FCollisionShape::MakeSphere(Radius), Params);

	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor) continue;
		if (OutResult.DamagedActors.Contains(HitActor)) continue; // already hit this swing

		// Impulse along the swing direction (a melee shove), Stagger conveyed via ExtraContextTags.
		if (RouteDamage(Request, Hit, /*PreMultiplier*/ 1.0f, Request.Direction, OutResult))
		{
			OutResult.DamagedActors.Add(HitActor);
			OutResult.Hits.Add(Hit);
			if (!Request.bCleave) break; // single-target: stop at the first receiver
		}
	}
}
