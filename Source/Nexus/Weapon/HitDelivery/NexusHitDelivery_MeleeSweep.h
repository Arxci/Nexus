#pragma once

#include "CoreMinimal.h"

#include "Nexus/Weapon/HitDelivery/NexusHitDelivery.h"

#include "NexusHitDelivery_MeleeSweep.generated.h"


/**
 * Sweeps a capsule (a sphere swept along the swing reach) from the weapon socket and
 * routes the same FNexusDamageContext as the other deliveries — with the melee damage
 * type, knockback impulse and a Stagger context tag (set by the caller via
 * ExtraContextTags). De-dupes per swing through the result's DamagedActors set, so the
 * melee ability can run this every tick of the anim-notify hit window without hitting a
 * target twice. Single-target (first receiver) or cleave (all) per Request.bCleave.
 */
UCLASS()
class NEXUS_API UNexusHitDelivery_MeleeSweep : public UNexusHitDelivery
{
	GENERATED_BODY()

public:
	virtual void Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const override;
};
