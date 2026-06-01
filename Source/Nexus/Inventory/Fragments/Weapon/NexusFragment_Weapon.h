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


/**
 * One purchasable tier on a weapon upgrade track (RE4R-style: Power Lv.1..N).
 * Value is the CUMULATIVE upgrade delta over base at this tier — not a per-step
 * increment — so the merchant can derive the current tier from the persisted
 * stat and the displayed total is unambiguous. Cost is the currency to advance
 * INTO this tier from the previous one.
 */
USTRUCT(BlueprintType, DisplayName = "Weapon Upgrade Tier")
struct NEXUS_API FNexusWeaponUpgradeTier
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Value = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0"))
	int32 Cost = 0;
};

/**
 * A merchant upgrade track for one effective stat. The merchant reads these to
 * offer the next tier and enforce the per-stat cap (the last tier); the assembly
 * folds the purchased delta into the effective-stat resolution via the instance's
 * persistent stat tag — no new per-instance storage. Author tiers with strictly
 * increasing Value.
 */
USTRUCT(BlueprintType, DisplayName = "Weapon Upgrade Track")
struct NEXUS_API FNexusWeaponUpgradeTrack
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Stat.Weapon"))
	FGameplayTag StatTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FNexusWeaponUpgradeTier> Tiers;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo Visual")
	FAmmoVisualSpec AmmoVisual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	FWeaponPresentation Presentation;

	/**
	 * Optional hard bounds on the resolved effective stats, applied after base +
	 * attachment modifiers + persistent upgrades. Stops a stacked muzzle + max-tier
	 * Power tune-up from pushing damage past a sane ceiling, and keeps a heavy
	 * negative modifier from driving a stat below its floor. A stat with no entry is
	 * unbounded; an entry whose Max <= Min is ignored.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TArray<FNexusStatClamp> StatClamps;

	/**
	 * Merchant tune-up tracks (RE4R-style). The merchant offers the next tier per
	 * track and caps at the last; the purchased delta persists on the instance and
	 * folds into the effective-stat resolution. One track per upgradeable stat.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades")
	TArray<FNexusWeaponUpgradeTrack> UpgradeTracks;

	float GetFireInterval() const
	{
		return Combat.RoundsPerMinute > 0.0f ? 60.0f / Combat.RoundsPerMinute : 0.0f;
	}

	/** The upgrade track tuning StatTag, or null if this weapon doesn't tune that stat. */
	const FNexusWeaponUpgradeTrack* FindUpgradeTrack(const FGameplayTag StatTag) const
	{
		for (const FNexusWeaponUpgradeTrack& Track : UpgradeTracks)
		{
			if (Track.StatTag == StatTag) return &Track;
		}
		return nullptr;
	}

	virtual void InitializeInstance(UNexusItemInstance* Instance) const override;

	/** Installs UNexusWeaponBehaviorComponent on the equipped actor. */
	virtual void OnInstall(ANexusEquippedActor* EquippedActor) const override;
	virtual void OnUninstall(ANexusEquippedActor* EquippedActor) const override;

	/**
	 * Seeds the Stat.Weapon.* keys (Damage, RPM, MaxRange, spread, magazine size,
	 * reload duration, plus neutral defaults for recoil + ADS time so multiplicative
	 * attachment modifiers don't multiply against zero). The assembly applies
	 * attachment Add then Mul modifiers on top of these.
	 */
	virtual void SeedStatTags(TMap<FGameplayTag, float>& OutBaseValues) const override;

	/** Seeds authored per-stat clamp bounds (see StatClamps) for the assembly's final clamp pass. */
	virtual void SeedStatClamps(TMap<FGameplayTag, FVector2D>& OutClamps) const override;
};