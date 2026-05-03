#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Curves/CurveFloat.h"

#include "Nexus/Inventory/NexusItemFragment.h"

#include "NexusFragment_Weapon.generated.h"

class UCameraShakeBase;
class UFXSystemAsset;
class USoundBase;
class UAnimMontage;


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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	FWeaponPresentation Presentation;

	float GetFireInterval() const
	{
		return Combat.RoundsPerMinute > 0.0f ? 60.0f / Combat.RoundsPerMinute : 0.0f;
	}

	virtual void InitializeInstance(UNexusItemInstance* Instance) const override;
};