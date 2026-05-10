#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Curves/CurveFloat.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentTypes.h"
#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Weapon.generated.h"

class UCameraShakeBase;
class UFXSystemAsset;
class USoundBase;
class UAnimMontage;
class UStaticMesh;


UENUM(BlueprintType)
enum class ENexusWeaponFireMode : uint8
{
	SemiAuto UMETA(DisplayName = "Semi-Auto"),
	Shotgun  UMETA(DisplayName = "Shotgun"),
	Melee    UMETA(DisplayName = "Melee"),
};

UENUM(BlueprintType)
enum class ENexusWeaponAmmoModel : uint8
{
	Magazine UMETA(DisplayName = "Magazine"),
	Pooled   UMETA(DisplayName = "Pooled"),
	None     UMETA(DisplayName = "None"),
};

USTRUCT(BlueprintType, DisplayName = "Animations")
struct NEXUS_API FWeaponAnimations
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> DryFireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UAnimMontage> ReloadMontage;

	/**
	 * Weapon-mesh-side action montages, played on the equipped actor's own
	 * SkeletalMeshComponent in lockstep with the arms montage. Keyed by
	 * Action.Weapon.* tag; UNexusAnimNotify_WeaponAction on the arms montage
	 * triggers playback at the right frame so the slide/bolt/magazine animate
	 * in sync. Attachments override individual entries via
	 * UNexusAttachmentDefinition::AnimationOverrides (deeper attachments win).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation",
		meta = (AssetBundles = "Equipped",
			Categories = "Action.Weapon",
			ForceInlineRow))
	TMap<FGameplayTag, TSoftObjectPtr<UAnimMontage>> ActionMontages;
};

/**
 * Authoring data for the "chambered round" visual — the bullet that briefly
 * appears between the magazine and chamber during the unholster/chamber/reload
 * windows. Sequencer authoring uses a static mesh attached to the gun's ammo
 * bone; UNexusAnimNotifyState_ShowChamberRound uses the same mesh + socket at
 * runtime, driven by UNexusWeaponBehaviorComponent.
 */
USTRUCT(BlueprintType, DisplayName = "Ammo Visual")
struct NEXUS_API FAmmoVisualSpec
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UStaticMesh> RoundMesh;

	/** Socket on the equipped actor's main mesh that the round attaches to. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo Visual")
	FName AmmoSocket = "ammo";
};

USTRUCT(BlueprintType, DisplayName = "Combat")
struct NEXUS_API FWeaponCombat
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	ENexusWeaponFireMode FireMode = ENexusWeaponFireMode::SemiAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "1"))
	float RoundsPerMinute = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "1"))
	int32 PelletsPerShot = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0.0"))
	float BaseDamage = 25.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0.0"))
	float MaxRange = 10000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FRuntimeFloatCurve DamageFalloffCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (Categories = "Damage.Type"))
	FGameplayTag DamageTypeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0.0"))
	FVector2D SpreadConeDegrees = FVector2D(2.0f, 0.25f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Feel")
	TSubclassOf<UCameraShakeBase> FireCameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Feel", meta = (ClampMin = "0.0"))
	float FireCameraShakeScale = 1.0f;
};

USTRUCT(BlueprintType, DisplayName = "Presentation")
struct NEXUS_API FWeaponPresentation
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	FName MuzzleSocketName = "muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USoundBase> DryFireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USoundBase> ReloadSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UFXSystemAsset> MuzzleFlash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UFXSystemAsset> ImpactFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USoundBase> ImpactSound;
};

USTRUCT(BlueprintType, DisplayName = "Ammo")
struct NEXUS_API FWeaponAmmo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	ENexusWeaponAmmoModel AmmoModel = ENexusWeaponAmmoModel::Magazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo", meta = (ClampMin = "0"))
	int32 MagazineSize = 12;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	FGameplayTag AmmoIdentityTag;
};

USTRUCT(BlueprintType, DisplayName = "Reload")
struct NEXUS_API FWeaponReload
{
	GENERATED_BODY()

	/** Fallback duration if the reload montage has no AmmoTransfer notify. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reload", meta = (ClampMin = "0.0"))
	float ReloadDuration = 1.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reload")
	FName AmmoTransferNotifyName = "AmmoTransfer";
};


USTRUCT(BlueprintType, DisplayName = "Weapon")
struct NEXUS_API FNexusFragment_Weapon : public FNexusItemFragment
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	FWeaponAmmo Ammo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FWeaponCombat Combat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reload")
	FWeaponReload Reload;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	FWeaponAnimations Animations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo Visual")
	FAmmoVisualSpec AmmoVisual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	FWeaponPresentation Presentation;

	/**
	 * Attachment slots exposed by this weapon. Each slot declares an attach
	 * socket on the weapon's skeletal mesh, the GameplayTags it accepts, and
	 * an optional default attachment installed at spawn time. Attachments can
	 * themselves provide more slots (rail risers, foregrips with built-in
	 * lasers), so this list is just the top of the tree — see
	 * UNexusWeaponAssemblyComponent for runtime resolution.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attachments")
	TArray<FWeaponSlotDefinition> Slots;

	float GetFireInterval() const
	{
		return Combat.RoundsPerMinute > 0.0f ? 60.0f / Combat.RoundsPerMinute : 0.0f;
	}

	virtual void InitializeInstance(UNexusItemInstance* Instance) const override;

	/** Installs UNexusWeaponBehaviorComponent on the equipped actor. */
	virtual void OnInstall(ANexusEquippedActor* EquippedActor) const override;
	virtual void OnUninstall(ANexusEquippedActor* EquippedActor) const override;
};