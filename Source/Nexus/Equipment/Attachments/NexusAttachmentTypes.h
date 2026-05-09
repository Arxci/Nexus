#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "NexusAttachmentTypes.generated.h"

class UNexusAttachmentDefinition;


USTRUCT(BlueprintType, DisplayName = "Attachment Stat Modifier")
struct NEXUS_API FAttachmentStatModifier
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (Categories = "Stat.Weapon"))
	FGameplayTag StatTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Add = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Mul = 1.0f;
};


USTRUCT(BlueprintType, DisplayName = "Weapon Slot")
struct NEXUS_API FWeaponSlotDefinition
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (Categories = "Attachment.Slot"))
	FGameplayTag SlotID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttachSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (Categories = "Attachment.Type"))
	FGameplayTagContainer AcceptedTags;

	/**
	 * When true, AcceptedTags is ignored and any attachment fits this slot.
	 * Useful for prototype/test slots; prefer authoring AcceptedTags for ship.
	 *
	 * Empty AcceptedTags + bAcceptsAny=false is treated as "accepts any" with a
	 * one-time warning (legacy compatibility) — set bAcceptsAny=true to silence.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAcceptsAny = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRequired = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UNexusAttachmentDefinition> DefaultAttachment;
};