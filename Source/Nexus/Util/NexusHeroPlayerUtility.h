#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "NexusHeroPlayerUtility.generated.h"

UCLASS()
class NEXUS_API UNexusHeroPlayerUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Trace forward from the camera. Returns true on hit. */
	UFUNCTION(BlueprintCallable, Category = "Trace", meta = (DefaultToSelf = "Pawn"))
	static bool CameraForwardTrace(
		const APawn* Pawn,
		const float Distance,
		const ETraceTypeQuery TraceChannel,
		FHitResult& OutHit,
		const TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None,
		const float DrawTime = 0.0f);
};
