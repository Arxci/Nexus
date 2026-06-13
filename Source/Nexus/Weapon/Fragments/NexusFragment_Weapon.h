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
class UNexusHitDelivery;
class UNexusAbility;


UENUM(BlueprintType)
enum class ENexusWeaponFireMode : uint8
{
	SemiAuto UMETA(DisplayName = "Semi-Auto"),   // one shot per trigger pull
	Shotgun  UMETA(DisplayName = "Shotgun"),     // one shot, N pellets
	FullAuto UMETA(DisplayName = "Full-Auto"),   // re-fires at RPM while the input is held
	Burst    UMETA(DisplayName = "Burst"),       // a fixed BurstCount per pull, at RPM cadence
	Melee    UMETA(DisplayName = "Melee"),       // legacy; melee is now a capability, not a fire mode
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

	/** Rounds fired per trigger pull when FireMode is Burst (ignored by the other modes). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "1"))
	int32 BurstCount = 3;

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

	/** Upward view kick per shot (degrees). Seeds Stat.Weapon.RecoilVertical — attachment / upgrade tunable. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Feel", meta = (ClampMin = "0.0"))
	float RecoilVertical = 0.0f;

	/** Max horizontal view kick per shot (degrees); the per-shot sign is randomized. Seeds Stat.Weapon.RecoilHorizontal. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Feel", meta = (ClampMin = "0.0"))
	float RecoilHorizontal = 0.0f;

	/** Felt-recoil multiplier while aiming (steady-aim control). 1 = no reduction, 0 = fully controlled. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Feel", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float RecoilAimControl = 0.5f;

	/** Seconds to raise into full aim (the ADS ramp). Seeds Stat.Weapon.ADSTime; 0 = instant. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Feel", meta = (ClampMin = "0.0"))
	float ADSTime = 0.25f;
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
 * The RANGED capability's authoring: ammo model, fire/combat tuning, reload, and the
 * gun-specific presentation + chambered-round visual. Present only when the weapon
 * declares bHasRanged — a melee-only knife carries none of this, so it never authors
 * RPM / magazine / muzzle fields. The Fire / Reload / Aim abilities read these (through
 * GetEffectiveStat where the value is a tunable stat).
 */
USTRUCT(BlueprintType, DisplayName = "Weapon Ranged Spec")
struct NEXUS_API FWeaponRangedSpec
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
	 * How a shot acquires targets: a UNexusHitDelivery subclass (Hitscan, Projectile,
	 * ...). The variable is target acquisition; every shot still ends in one
	 * FNexusDamageContext. Leave null for the default instant Hitscan — switching a
	 * weapon to projectile is this field plus the projectile's own data, never a
	 * rewrite of the Fire ability.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<UNexusHitDelivery> HitDelivery;

	/**
	 * The verbs a Ranged capability grants on equip. A null field falls back to the
	 * built-in C++ ability (Fire / Reload / Aim), so most weapons author nothing here;
	 * set one to slot a Blueprint subclass for a bespoke weapon.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UNexusAbility> FireAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UNexusAbility> ReloadAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UNexusAbility> AimAbility;
};


/**
 * The MELEE capability's authoring: swing damage / reach, sweep shape, cadence, the
 * stamina + durability costs, light/heavy scaling, and the swing presentation. Present
 * only when the weapon declares bHasMelee — a pistol carries none of this, so it never
 * authors a swing arc. A melee-capable weapon's swings resolve hits via the MeleeSweep
 * hit-delivery strategy during an anim-notify-state window; the tunables fold through
 * GetEffectiveStat as Stat.Melee.* keys so melee attachments / upgrades apply for free.
 */
USTRUCT(BlueprintType, DisplayName = "Weapon Melee Spec")
struct NEXUS_API FWeaponMeleeSpec
{
	GENERATED_BODY()

	/** Base light-attack damage. Seeds Stat.Melee.Damage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (ClampMin = "0.0"))
	float BaseDamage = 40.0f;

	/** Reach of the sweep measured from the weapon socket (cm). Seeds Stat.Melee.Range. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (ClampMin = "0.0"))
	float Range = 150.0f;

	/** Radius of the swept capsule (cm). Widens the arc that connects with a target. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (ClampMin = "0.0"))
	float SweepRadius = 30.0f;

	/** Swings per minute — gates the swing cadence via the ability cooldown. Seeds Stat.Melee.SwingRate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (ClampMin = "1.0"))
	float SwingsPerMinute = 80.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (Categories = "Damage.Type"))
	FGameplayTag DamageTypeTag;

	/** When true the sweep damages EVERY receiver in the arc (cleave); else first hit only. De-duped per swing. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	bool bCleave = false;

	/**
	 * How a swing acquires targets: a UNexusHitDelivery subclass. Null defaults to the
	 * capsule MeleeSweep; the same seam as the ranged HitDelivery, so a swing could become
	 * a traced arc or a thrown projectile with no ability change.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TSubclassOf<UNexusHitDelivery> HitDelivery;

	/** Knockback impulse magnitude applied along the swing direction on a connecting hit. Seeds Stat.Melee.Knockback. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee", meta = (ClampMin = "0.0"))
	float KnockbackImpulse = 600.0f;

	/** Stamina drained per light swing (heavy multiplies by HeavyStaminaMultiplier). 0 = free. Seeds Stat.Melee.StaminaCost. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Cost", meta = (ClampMin = "0.0"))
	float StaminaCost = 15.0f;

	/** Whether this weapon supports the heavy variant; a ranged weapon's contextual bash is typically light-only. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Heavy")
	bool bSupportsHeavy = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Heavy", meta = (ClampMin = "1.0"))
	float HeavyDamageMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Heavy", meta = (ClampMin = "1.0"))
	float HeavyStaminaMultiplier = 2.0f;

	/** Melee weapons degrade with use and BREAK (are removed) at zero durability — knife scarcity. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Durability")
	bool bUsesDurability = true;

	/** Starting / maximum durability seeded onto the item instance's Stat.Durability when bUsesDurability. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Durability", meta = (ClampMin = "0.0"))
	float MaxDurability = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Durability", meta = (ClampMin = "0.0"))
	float DurabilityPerSwing = 5.0f;

	/**
	 * Anim-notify-STATE name that opens/closes the hit window on the swing montage —
	 * the melee analogue of FWeaponReload::AmmoTransferNotifyName. The MeleeSweep
	 * delivery runs only while this window is open.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName HitWindowNotifyName = "MeleeHit";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USoundBase> SwingSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Presentation",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UFXSystemAsset> HitFX;

	/** The melee verb granted on equip. Null falls back to the built-in C++ melee ability. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee|Abilities")
	TSubclassOf<UNexusAbility> MeleeAbility;
};


/**
 * One purchasable tier on a weapon upgrade track (discrete tiers: Power Lv.1..N).
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

	// Categories = "Stat" (not just Stat.Weapon) so a melee weapon's tune-up tracks can
	// target Stat.Melee.* keys too; the assembly folds any seeded key regardless.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Stat"))
	FGameplayTag StatTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FNexusWeaponUpgradeTier> Tiers;
};


USTRUCT(BlueprintType, DisplayName = "Weapon")
struct NEXUS_API FNexusFragment_Weapon : public FNexusItemFragment
{
	GENERATED_BODY()

	/**
	 * Capability composition (locked design decision): a weapon declares a Ranged
	 * capability, a Melee capability, or both — it is not two systems. Equipping grants
	 * exactly the abilities each present capability needs (see GatherGrantedAbilities).
	 * A knife is Melee-only; a pistol is Ranged-only; a bayonet-rifle is both.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Capability")
	bool bHasRanged = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Capability")
	bool bHasMelee = false;

	/** Ranged authoring — only meaningful when bHasRanged. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ranged",
		meta = (EditCondition = "bHasRanged"))
	FWeaponRangedSpec Ranged;

	/** Melee authoring — only meaningful when bHasMelee. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee",
		meta = (EditCondition = "bHasMelee"))
	FWeaponMeleeSpec Melee;

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
	 * Merchant tune-up tracks (discrete tiers). The merchant offers the next tier per
	 * track and caps at the last; the purchased delta persists on the instance and
	 * folds into the effective-stat resolution. One track per upgradeable stat.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades")
	TArray<FNexusWeaponUpgradeTrack> UpgradeTracks;

	bool HasRanged() const { return bHasRanged; }
	bool HasMelee()  const { return bHasMelee; }

	float GetFireInterval() const
	{
		return (bHasRanged && Ranged.Combat.RoundsPerMinute > 0.0f)
			? 60.0f / Ranged.Combat.RoundsPerMinute : 0.0f;
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
	 * Grants the verbs each present capability needs: Fire + Reload + Aim for Ranged,
	 * Melee for Melee. Each falls back to its built-in C++ ability when the matching
	 * authored class is null, so a plain pistol or knife grants the right verbs with no
	 * extra authoring. A both-capable weapon (bayonet rifle) grants all of them.
	 */
	virtual void GatherGrantedAbilities(TArray<TSubclassOf<UNexusAbility>>& OutAbilities) const override;

	/**
	 * Seeds the effective-stat base values for whichever capabilities are present:
	 * Stat.Weapon.* (Damage, RPM, MaxRange, spread, magazine size, reload duration, plus
	 * neutral recoil + ADS-time defaults) when bHasRanged, and Stat.Melee.* (Damage,
	 * Range, SwingRate, StaminaCost, Knockback) when bHasMelee. The assembly applies
	 * attachment Add then Mul modifiers on top of these — melee keys fold identically to
	 * ranged keys, so a melee attachment / merchant tune-up applies for free.
	 */
	virtual void SeedStatTags(TMap<FGameplayTag, float>& OutBaseValues) const override;

	/** Seeds authored per-stat clamp bounds (see StatClamps) for the assembly's final clamp pass. */
	virtual void SeedStatClamps(TMap<FGameplayTag, FVector2D>& OutClamps) const override;
};