#pragma once

#include "CoreMinimal.h"

#include "Nexus/Weapon/HitDelivery/NexusHitDelivery.h"

#include "NexusHitDelivery_Projectile.generated.h"

class ANexusProjectile;


/**
 * Spawns a projectile along the aim ray instead of tracing instantly. The firing
 * ability is identical to the hitscan case — only the delivery differs — so flipping
 * a weapon from hitscan to projectile is this strategy + the projectile's data, never
 * a rewrite of Fire. The projectile builds the same FNexusDamageContext on impact.
 *
 * Author a Blueprint subclass to point ProjectileClass at a grenade / bolt / flame
 * round and tune the speed; that is all a projectile weapon needs in code.
 */
UCLASS()
class NEXUS_API UNexusHitDelivery_Projectile : public UNexusHitDelivery
{
	GENERATED_BODY()

public:
	virtual void Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const override;

protected:
	/** The projectile actor to spawn (defaults to the minimal ANexusProjectile). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<ANexusProjectile> ProjectileClass;

	/** Launch speed (cm/s). 0 = use the projectile's own default. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (ClampMin = "0.0"))
	float ProjectileSpeed = 6000.0f;

	/** Auto-destroy after this many seconds if it never hits. 0 = use the projectile's own default. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (ClampMin = "0.0"))
	float ProjectileLifeSeconds = 5.0f;
};
