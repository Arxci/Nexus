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

	/** Static pose blended into the upper body while the item is held idle. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pose")
	TSoftObjectPtr<UAnimSequence> IdlePose;

	/** Optional override pose used while the owner is moving (jog/run). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pose")
	TSoftObjectPtr<UAnimSequence> RunPoseOverride;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loops")
	TSoftObjectPtr<UAnimSequence> IdleLoop;

	/** Played on the owner's anim instance when this item becomes equipped. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage")
	TSoftObjectPtr<UAnimMontage> EquipMontage;

	/** Played on the owner's anim instance when this item is unequipped. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage")
	TSoftObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage")
	TSoftObjectPtr<UAnimMontage> InspectMontage;
};

/**
 * Item can be bound to an equipment slot. While equipped:
 *   - An ANexusEquippedActor is spawned and attached to the owning character.
 *   - GrantedAbilities are added to the character's NexusAbilitySystemComponent.
 *   - SlotTag and any OwnedTagsWhileEquipped are pushed as loose tags on the ASC.
 */
USTRUCT(BlueprintType, DisplayName = "Equippable")
struct NEXUS_API FNexusFragment_Equippable : public FNexusItemFragment
{
	GENERATED_BODY()

	/** Which slot tag this item occupies. Equipment.Slot.Primary, .Secondary, .Utility, .Body, ... */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Equipment.Slot"))
	FGameplayTag SlotTag;

	/** Class of actor spawned and attached while equipped. Defaults to ANexusEquippedActor when null. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<ANexusEquippedActor> EquippedActorClass;

	/** Visible mesh used by the equipped actor. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> WorldMesh;

	/** Socket on the owning character mesh the equipped actor attaches to. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttachSocket = "hand_r_socket";

	/** Abilities granted to the owner's ASC while equipped. Revoked on unequip. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UNexusAbility>> GrantedAbilities;

	/** Loose tags pushed onto the owner's ASC while equipped (ref-counted). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer OwnedTagsWhileEquipped;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	FEquippableAnimationSet Animations;
};