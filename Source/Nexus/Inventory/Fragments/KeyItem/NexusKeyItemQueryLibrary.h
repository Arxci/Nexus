#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "NexusKeyItemQueryLibrary.generated.h"


class UNexusInventoryComponent;

UCLASS()
class NEXUS_API UNexusKeyItemQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Inventory|Keys",
		meta = (DefaultToSelf = "Inventory"))
	static bool InventoryHasUnlockTag(
		const UNexusInventoryComponent* Inventory, FGameplayTag UnlockTag);
};