#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveVector.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "NexusFragment_Weapon.generated.h"

class UFXSystemAsset;
class USoundBase;

UENUM(BlueprintType)
enum class ENexusWeaponFireMode : uint8
{
	SemiAuto UMETA(DisplayName = "Semi-Auto"),
	Burst    UMETA(DisplayName = "Burst"),
	FullAuto UMETA(DisplayName = "Full-Auto"),
	Shotgun  UMETA(DisplayName = "Shotgun"),
	Melee    UMETA(DisplayName = "Melee"),
};

UENUM(BlueprintType)
enum class ENexusWeaponAmmoModel : uint8
{
	/** Magazine + reserve pulled from inventory ammo items keyed by AmmoIdentityTag. */
	Magazine UMETA(DisplayName = "Magazine"),

	/** No magazine; each shot consumes one ammo item directly from inventory. */
	Pooled   UMETA(DisplayName = "Pooled"),

	/** No ammo (melee, energy with infinite charge, debug). */
	None     UMETA(DisplayName = "None"),
};

/**
 * Authoring data for a weapon. Combine with FNexusFragment_Equippable on the
 * same UNexusItemDefinition to produce a usable weapon. Pure data —
 * fire/reload/aim verbs live on the abilities granted by the Equippable
 * fragment, which read this fragment via UNexusAbility_Weapon::GetWeaponFragment().
 */
USTRUCT(BlueprintType, DisplayName = "Weapon")
struct NEXUS_API FNexusFragment_Weapon : public FNexusItemFragment
{
	GENERATED_BODY()

	// ---- Ammo ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	ENexusWeaponAmmoModel AmmoModel = ENexusWeaponAmmoModel::Magazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo", meta = (ClampMin = "0"))
	int32 MagazineSize = 12;

	/** IdentityTag of the ammo item this weapon consumes from inventory (e.g. "Item.Ammo.9mm"). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	FGameplayTag AmmoIdentityTag;

	// ---- Combat ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	ENexusWeaponFireMode FireMode = ENexusWeaponFireMode::SemiAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "1"))
	float RoundsPerMinute = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "1"))
	int32 PelletsPerShot = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0.0"))
	float BaseDamage = 25.0f;

	/** Effective range in cm (UE units). Beyond this point DamageFalloffCurve applies. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0.0"))
	float MaxRange = 10000.0f;

	/** Distance (cm) → damage multiplier. If empty, treated as 1.0 across MaxRange. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FRuntimeFloatCurve DamageFalloffCurve;

	/** Tag used by enemy resistance lookup and enemy reaction logic. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (Categories = "Damage.Type"))
	FGameplayTag DamageTypeTag;

	// ---- Spread / accuracy ----
	/** Cone half-angle in degrees. X = hipfire, Y = aiming. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spread", meta = (ClampMin = "0.0"))
	FVector2D SpreadConeDegrees = FVector2D(2.0f, 0.25f);

	// ---- Recoil ----
	/**
	 * Pitch / Yaw / Roll impulse in degrees, sampled by **shot index** (X-axis = 0 for the
	 * first shot in a burst, 1 for the second, etc.). Author keys for as many shots as
	 * the pattern needs; the curve clamps at the last key. ShotIndex resets to 0 once
	 * RecoilResetWindow seconds have passed without firing.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil")
	TObjectPtr<UCurveVector> RecoilImpulseCurve;

	/** Seconds of "no fire" required before the shot index resets to 0. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil", meta = (ClampMin = "0.0"))
	float RecoilResetWindow = 0.5f;

	// ---- Animation (montages played on the character's anim instance via WeaponSlot) ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSoftObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSoftObjectPtr<UAnimMontage> DryFireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSoftObjectPtr<UAnimMontage> ReloadMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSoftObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSoftObjectPtr<UAnimMontage> InspectMontage;

	/** Static pose blended into the upper body while the weapon is held idle. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TSoftObjectPtr<UAnimSequence> WeaponHoldPose;

	// ---- Reload ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reload", meta = (ClampMin = "0.0"))
	float ReloadDuration = 1.5f;

	// ---- Presentation (soft refs — only resolved while the weapon is active) ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	FName MuzzleSocketName = "muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	TSoftObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	TSoftObjectPtr<USoundBase> DryFireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	TSoftObjectPtr<USoundBase> ReloadSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	TSoftObjectPtr<UFXSystemAsset> MuzzleFlash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Presentation")
	TSoftObjectPtr<UFXSystemAsset> ImpactFX;

	float GetFireInterval() const
	{
		return RoundsPerMinute > 0.0f ? 60.0f / RoundsPerMinute : 0.0f;
	}
};