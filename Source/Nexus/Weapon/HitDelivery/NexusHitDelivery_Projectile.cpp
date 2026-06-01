#include "NexusHitDelivery_Projectile.h"

#include "Engine/World.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Weapon/HitDelivery/NexusProjectile.h"

void UNexusHitDelivery_Projectile::Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const
{
	UWorld* World = Request.ResolveWorld();
	if (!World) return;

	// Per-shot cone spread around the aim direction (same effective spread as hitscan).
	const FVector Dir = Request.SpreadHalfAngleDegrees > 0.0f
		? FMath::VRandCone(Request.Direction, FMath::DegreesToRadians(Request.SpreadHalfAngleDegrees))
		: Request.Direction;

	// Spawn at the muzzle (set by the caller), aimed along the camera-resolved direction.
	const FVector  SpawnLoc = Request.MuzzleLocation;
	const FRotator SpawnRot = Dir.Rotation();

	const TSubclassOf<ANexusProjectile> Class = ProjectileClass
		? ProjectileClass
		: TSubclassOf<ANexusProjectile>(ANexusProjectile::StaticClass());

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.Owner      = Request.Causer.Get() ? Request.Causer.Get() : Request.Instigator.Get();
	Params.Instigator = Request.InstigatorPawn.Get();

	ANexusProjectile* Projectile = World->SpawnActor<ANexusProjectile>(Class, SpawnLoc, SpawnRot, Params);
	if (!Projectile) return;

	Projectile->Launch(Request, Dir, ProjectileSpeed, ProjectileLifeSeconds);

	// Deferred delivery: no synchronous hits to report here — the projectile routes its
	// own packet + impact FX when it lands, so OutResult stays empty.
}
