#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Equippable.generated.h"

class UNexusAbility;
class ANexusEquippedActor;
class UAnimInstance;
class UAnimMontage;
class UAnimSequence;
class USkeletalMesh;


/**
 * One (Arms, Item) montage pair for a single Action.* tag. Both fields are
 * optional — an action can drive only arms (a flashlight click), only the
 * item mesh (a slide auto-rack triggered by a notify mid-fire), or both
 * (a reload where arms + gun animate together). The two streams are kept
 * in sync via UNexusAnimNotify_WeaponAction on the arms montage, which
 * fires the item montage at the authored frame.
 *
 * This is the unit attachments override — see UNexusAttachmentDefinition::ActionOverrides.
 * An attachment may supply either or both fields; the assembly resolves the
 * arms and item streams independently, so a drum-mag attachment can change the
 * reload arms animation without rewriting the gun's slide animation (and vice versa).
 */
USTRUCT(BlueprintType, DisplayName = "Action Anim")
struct NEXUS_API FEquipmentActionAnim
{
    GENERATED_BODY()

    /** Played on the character's first-person/arms skeletal mesh. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action",
        meta = (AssetBundles = "Equipped"))
    TSoftObjectPtr<UAnimMontage> ArmsMontage;

    /**
     * Played on the equipped actor's own skeletal mesh, triggered by
     * UNexusAnimNotify_WeaponAction on the arms montage so the two stay in sync.
     * Leave null for actions that don't animate the item itself.
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Action",
        meta = (AssetBundles = "Equipped"))
    TSoftObjectPtr<UAnimMontage> ItemMontage;
};


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

    /**
     * Per-action (Arms, Item) montage pairs, keyed by Action.* tag. This is the
     * single canonical place equipment animations are authored — holster/unholster
     * for any equippable, plus fire/reload/etc. for weapons. The assembly
     * resolves overrides through UNexusAttachmentDefinition::ActionOverrides
     * (deeper attachments win) before falling back to entries here.
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actions",
        meta = (AssetBundles = "Equipped",
            Categories = "Action",
            ForceInlineRow))
    TMap<FGameplayTag, FEquipmentActionAnim> Actions;

    /**
     * AnimBP class for the equipped actor's own mesh. Generic across equipment
     * types — a weapon AnimBP for guns, but a flashlight or radio could
     * supply its own (button click, antenna sway).
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipped Mesh",
        meta = (AssetBundles = "Equipped"))
    TSoftClassPtr<UAnimInstance> MeshAnimInstanceClass;
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