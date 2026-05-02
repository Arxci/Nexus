#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_KeyItem.generated.h"


USTRUCT(BlueprintType, DisplayName = "Key Item")
struct NEXUS_API FNexusFragment_KeyItem : public FNexusItemFragment
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Key"))
	FGameplayTag UnlockTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bConsumeOnUse = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bQuestLocked = true;
};