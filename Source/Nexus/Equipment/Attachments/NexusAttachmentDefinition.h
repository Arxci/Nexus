#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "NexusAttachmentTypes.h"

#include "NexusAttachmentDefinition.generated.h"

class UAnimInstance;
class UAnimMontage;
class USkeletalMesh;
class UTexture2D;


UCLASS(BlueprintType)
class NEXUS_API UNexusAttachmentDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	// Identity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity",
		meta = (Categories = "Attachment.Identity"))
	FGameplayTag IdentityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity",
		meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity",
		meta = (AssetBundles = "UI"))
	TSoftObjectPtr<UTexture2D> Icon;

	// Compatibility
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Compatibility",
		meta = (Categories = "Attachment.Type"))
	FGameplayTagContainer ProvidedTags;

	// Visual
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USkeletalMesh> Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftClassPtr<UAnimInstance> AnimInstanceClass;

	// Stat modifiers — applied on top of the weapon's base stats by the assembly.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TArray<FAttachmentStatModifier> Modifiers;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation",
		meta = (AssetBundles = "Equipped",
			Categories = "Action.Weapon",
			ForceInlineRow))
	TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> AnimationOverrides;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slots")
	TArray<FWeaponSlotDefinition> ProvidedSlots;
	
	bool FitsSlot(const FGameplayTagContainer& SlotAcceptedTags) const
	{
		return ProvidedTags.HasAny(SlotAcceptedTags);
	}
};