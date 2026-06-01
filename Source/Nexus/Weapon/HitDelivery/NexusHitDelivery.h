#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Engine/EngineTypes.h"   // ETraceTypeQuery
#include "Engine/HitResult.h"

#include "NexusHitDelivery.generated.h"

class AActor;
class APawn;
struct FRuntimeFloatCurve;


/**
 * Inputs a hit-delivery strategy needs to acquire targets and emit the uniform
 * damage packet, host-agnostically. Built per shot / swing by the firing or melee
 * ability from EFFECTIVE stats (so attachments + merchant upgrades fold in) and a
 * host-neutral aim ray (the controller viewpoint — player camera OR AI eyes), then
 * handed to the selected UNexusHitDelivery.
 *
 * The strategy owns *how* targets are found (trace / projectile / sweep); this
 * struct owns *what* the resulting FNexusDamageContext carries. Nothing here knows
 * about the player camera, a first-person mesh, or a concrete character class.
 */
USTRUCT()
struct NEXUS_API FNexusHitDeliveryRequest
{
	GENERATED_BODY()

	/** Pawn / AI whose action caused the hit (FNexusDamageContext::Instigator). */
	TWeakObjectPtr<AActor> Instigator;

	/** Direct cause — the equipped weapon actor (FNexusDamageContext::Causer). */
	TWeakObjectPtr<AActor> Causer;

	/** The instigator as a pawn, ignored by traces / sweeps so a weapon can't hit its wielder. */
	TWeakObjectPtr<APawn> InstigatorPawn;

	/** Origin of the aim ray (world space) — the controller viewpoint, not the muzzle. */
	FVector Origin = FVector::ZeroVector;

	/**
	 * Muzzle / weapon-socket world location, used as the SPAWN origin by the projectile
	 * and melee-sweep deliveries (so a projectile leaves the barrel, not the camera),
	 * while hitscan still traces from Origin. The caller sets this to the muzzle socket,
	 * falling back to Origin when there is no equipped actor.
	 */
	FVector MuzzleLocation = FVector::ZeroVector;

	/** Normalized aim direction (world space), before any per-pellet spread cone. */
	FVector Direction = FVector::ForwardVector;

	/** Max trace / effective range in cm. The effective Stat.Weapon.MaxRange / Stat.Melee.Range. */
	float Range = 10000.0f;

	/** Per-shot cone half-angle (deg) applied by trace strategies. 0 = pinpoint. */
	float SpreadHalfAngleDegrees = 0.0f;

	/** Radius of the swept shape for the melee-sweep delivery (cm). Ignored by trace / projectile. */
	float SweepRadius = 0.0f;

	/** Melee sweep: damage every receiver in the arc (cleave) vs only the first. Ignored elsewhere. */
	bool bCleave = false;

	/** Damage type tag stamped on the packet (Damage.Type.*). */
	FGameplayTag DamageTypeTag;

	/**
	 * Delivery-specific context tags merged into every packet this request produces
	 * (e.g. a melee swing stamps Damage.Context.Stagger). Source-side weak-point
	 * classification (Critical / Headshot) is added on top per hit by RouteDamage.
	 */
	FGameplayTagContainer ExtraContextTags;

	/** Effective base damage (Stat.Weapon.Damage / Stat.Melee.Damage). */
	float BaseDamage = 0.0f;

	/** Optional distance falloff curve (owned by the weapon fragment; referenced, not copied). May be null. */
	const FRuntimeFloatCurve* DamageFalloffCurve = nullptr;

	/** Impulse magnitude applied to the receiver along the hit direction. */
	float ImpulseMagnitude = 1000.0f;

	/** Trace channel used by trace / sweep strategies. */
	TEnumAsByte<ETraceTypeQuery> TraceType = TraceTypeQuery1;

	/** Trace against complex (per-poly) collision — matches the prior hitscan behavior. */
	bool bTraceComplex = true;

	/** When true, a strategy draws its trace / sweep for the debug duration below. */
	bool bDrawDebug = false;
	float DebugDrawTime = 1.5f;

	/** First non-null of pawn / instigator / causer — a valid world-context + trace-ignore actor. */
	AActor* GetContextActor() const;

	UWorld* ResolveWorld() const;
};


/**
 * What a delivery produced. Hits drives caller-side presentation (impact FX / sound);
 * ReceiversDamaged drives the hit-marker. A deferred delivery (projectile) returns
 * with empty Hits — the spawned projectile owns its own impact presentation later.
 */
USTRUCT()
struct NEXUS_API FNexusHitDeliveryResult
{
	GENERATED_BODY()

	/** Blocking hits the caller can spawn impact FX / sound on (synchronous deliveries only). */
	TArray<FHitResult> Hits;

	/** How many INexusDamageReceiver consumed a packet this delivery (drives the hit-marker). */
	int32 ReceiversDamaged = 0;

	/** Union of the branch tags (Critical / Headshot / Stagger) stamped on this delivery's hits — the weak-point / hit cue for a HUD. */
	FGameplayTagContainer ContextTags;

	/**
	 * Actors already damaged — the per-swing de-dupe set for the melee sweep, which runs
	 * every tick during the hit window. The melee ability holds ONE result across the swing
	 * and passes it back in, so a target is hit once per swing no matter how many ticks the
	 * window spans. Trace / projectile deliveries leave it empty.
	 */
	TSet<TWeakObjectPtr<AActor>> DamagedActors;
};


/**
 * A swappable target-acquisition strategy. Hitscan, Projectile and MeleeSweep are
 * subclasses; the variable is *how* an attack finds targets, the constant is the
 * single FNexusDamageContext each one routes to INexusDamageReceiver. Stateless —
 * the firing / melee ability resolves the chosen class and calls Deliver on its CDO,
 * so there is no per-shot allocation. Adding a new delivery (beam, chain) is a new
 * subclass emitting the same packet, with zero change to the firing ability.
 */
UCLASS(Abstract, BlueprintType, EditInlineNew)
class NEXUS_API UNexusHitDelivery : public UObject
{
	GENERATED_BODY()

public:
	/** Acquire targets for one shot / swing and emit a uniform packet per damaged receiver. */
	virtual void Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const {}

	/**
	 * Shared packet router: stamp the common FNexusDamageContext fields from the
	 * request, fold in falloff + source-side weak-point classification, and route to
	 * the hit actor's INexusDamageReceiver. EVERY delivery ends here — the trace
	 * strategies AND a spawned projectile on impact — so the packet shape is identical
	 * regardless of how the hit was found. Returns true if a receiver consumed it.
	 *
	 * PreMultiplier folds delivery-specific scaling on top of falloff (e.g. a heavy
	 * melee attack's ×2); ImpulseDir overrides the impulse direction (zero = use the
	 * request's aim direction).
	 */
	static bool RouteDamage(const FNexusHitDeliveryRequest& Request, const FHitResult& Hit,
		float PreMultiplier, const FVector& ImpulseDir, FNexusHitDeliveryResult& OutResult);
};
