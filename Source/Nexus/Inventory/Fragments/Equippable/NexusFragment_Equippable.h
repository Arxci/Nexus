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
	TSoftObjectPtr<UAnimMontage> UnholsterMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> HolsterMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> InspectMontage;

	// Weapon-mesh-side animations (played on the equipped actor's own
	// SkeletalMeshComponent). The arms montage is the source of truth for
	// timing; UNexusAnimNotify_WeaponAction notifies on the arms montage relay
	// to the weapon mesh, which plays the matching action montage so its
	// slide/bolt/magazine animate in sync.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Mesh",
		meta = (AssetBundles = "Equipped"))
	TSoftClassPtr<UAnimInstance> WeaponAnimInstanceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Mesh",
		meta = (AssetBundles = "Equipped",
			Categories = "Action.Weapon",
			ForceInlineRow))
	TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> WeaponActionMontages;
};

USTRUCT(BlueprintType, DisplayName = "Equippable")
struct NEXUS_API FNexusFragment_Equippable : public FNexusItemFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
		meta = (Categories = "Equipment.Slot"))
	FGameplayTagContainer AllowedSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
	meta = (Categories = "Equipment.Slot"))
	FGameplayTag PreferredSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAutoAssignOnPickup = false;
	
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

	bool CanFitInSlot(const FGameplayTag SlotTag) const
	{
		return SlotTag.IsValid() && AllowedSlots.HasTagExact(SlotTag);
	}
};