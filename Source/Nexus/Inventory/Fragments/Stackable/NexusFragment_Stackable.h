#pragma once

#include "CoreMinimal.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Stackable.generated.h"

USTRUCT(BlueprintType, DisplayName = "Stackable")
struct NEXUS_API FNexusFragment_Stackable : public FNexusItemFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 MaxStackSize = 99;
};