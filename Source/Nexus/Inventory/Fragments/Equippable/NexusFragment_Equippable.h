#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Equippable.generated.h"

class UNexusAbility;
class ANexusEquippedActor;
class UAnimInstance;
class USkeletalMesh;


USTRUCT(BlueprintType, DisplayName = "Animation Set")
struct NEXUS_API FEquippableAnimationSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pose",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimSequence> IdlePose;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loops",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimSequence> IdleLoop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pose",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimSequence> RunLoop;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> InspectMontage;
};

USTRUCT(BlueprintType, DisplayName = "Equippable")
struct NEXUS_API FNexusFragment_Equippable : public FNexusItemFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Equipment.Slot"))
	FGameplayTag SlotTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (AssetBundles = "Equipped"))
	TSoftClassPtr<ANexusEquippedActor> EquippedActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USkeletalMesh> WorldMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttachSocket = "hand_r_socket";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UNexusAbility>> GrantedAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer OwnedTagsWhileEquipped;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	FEquippableAnimationSet Animations;
};