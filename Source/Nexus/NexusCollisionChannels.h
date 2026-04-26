#pragma once

#include "CoreMinimal.h"
#include "CollisionQueryParams.h"

namespace NexusCollisionChannels
{
	// Keep the order in sync with Project Settings → Collision.
	// Channel 1 = Interaction, Channel 2 = WeaponTrace, ...
	constexpr ECollisionChannel Interaction  = ECC_GameTraceChannel1;
	constexpr ECollisionChannel WeaponTrace  = ECC_GameTraceChannel2;
}