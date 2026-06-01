#pragma once

#include "CoreMinimal.h"

#include "Nexus/Weapon/HitDelivery/NexusHitDelivery.h"

#include "NexusHitDelivery_Hitscan.generated.h"


/**
 * Instant camera-forward (or AI-eyes-forward) line trace with a per-shot cone
 * spread, ignoring the wielder. The default ranged delivery — extracted verbatim
 * from the firing ability's former inline trace so behavior is unchanged; the
 * difference is that it now resolves through the swappable strategy seam and is
 * host-agnostic (no dependence on the player camera utility).
 */
UCLASS()
class NEXUS_API UNexusHitDelivery_Hitscan : public UNexusHitDelivery
{
	GENERATED_BODY()

public:
	virtual void Deliver(const FNexusHitDeliveryRequest& Request, FNexusHitDeliveryResult& OutResult) const override;
};
