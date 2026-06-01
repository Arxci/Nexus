#include "NexusAbility_WeaponFire.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "Camera/CameraShakeBase.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/EngineTypes.h"
#include "Engine/HitResult.h"
#include "Engine/World.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

#include "HAL/IConsoleManager.h"

#include "Kismet/GameplayStatics.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"

#include "Sound/SoundBase.h"

#include "Nexus/Nexus.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/Equipment/NexusEquipmentInterface.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/Fragments/Weapon/NexusFragment_Weapon.h"
#include "Nexus/Weapon/HitDelivery/NexusHitDelivery.h"
#include "Nexus/Weapon/HitDelivery/NexusHitDelivery_Hitscan.h"


namespace
{
	int32 GNexusWeaponDebugTrace = 0;
	FAutoConsoleVariableRef CVarNexusWeaponDebugTrace(
		TEXT("Nexus.Weapon.Debugtrace"),
		GNexusWeaponDebugTrace,
		TEXT("Visualize weapon traces. 0 = off, 1 = draw line + impact sphere, 2 = also UE_LOG per shot."),
		ECVF_Cheat);

	void SpawnFXAtLocation(const UObject* WorldContext, UFXSystemAsset* FX, const FVector& Loc, const FRotator& Rot)
	{
		if (!FX || !WorldContext) return;
		if (UParticleSystem* P = Cast<UParticleSystem>(FX))
		{
			UGameplayStatics::SpawnEmitterAtLocation(WorldContext, P, Loc, Rot);
		}
		else if (UNiagaraSystem* N = Cast<UNiagaraSystem>(FX))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(WorldContext, N, Loc, Rot);
		}
	}
}

UNexusAbility_WeaponFire::UNexusAbility_WeaponFire()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Weapon_Fire);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Firing);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Reloading);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Meleeing); // can't fire mid-swing
	bCooldownOnActivation   = true;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponFire::RequestDeactivateAbility(bool bForce)
{
	if (!IsActive()) return false;

	// Input release stops full-auto, but a burst always finishes the count it committed to.
	// A forced end (weapon swap / load reconcile) cancels either.
	if (!bForce && GetFireMode() == ENexusWeaponFireMode::Burst) return false;

	CommitAbilityEnd();
	return true;
}

void UNexusAbility_WeaponFire::CommitAbility()
{
	Super::CommitAbility(); // Active + starts the RPM cooldown (bCooldownOnActivation)

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon || !Weapon->bHasRanged) { CommitAbilityEnd(); return; }

	FireShot();

	// Semi / shotgun are one shot per press; full-auto and burst stay Active and re-fire
	// from the tick at the RPM cadence (held re-arm via cooldown).
	switch (Weapon->Ranged.Combat.FireMode)
	{
	case ENexusWeaponFireMode::FullAuto:
		return; // holds until the input releases (RequestDeactivate) or ammo runs out

	case ENexusWeaponFireMode::Burst:
		BurstRemaining = FMath::Max(0, Weapon->Ranged.Combat.BurstCount - 1);
		if (BurstRemaining > 0) return; // the tick fires the remainder
		break;                          // BurstCount <= 1 behaves like semi

	default:
		break;
	}

	CommitAbilityEnd();
}

void UNexusAbility_WeaponFire::CommitAbilityEnd()
{
	BurstRemaining = 0;
	Super::CommitAbilityEnd();
}

bool UNexusAbility_WeaponFire::CanTick()
{
	// Only the held modes remain Active after CommitAbility; semi / shotgun already ended.
	return IsActive();
}

void UNexusAbility_WeaponFire::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);

	if (!IsActive()) return;

	// Stop the instant a blocking state begins (weapon swap, reload) so a held full-auto
	// can't keep firing through a holster. (Reload also cancels Fire via CancelAbilitiesWithTags.)
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		if (!ActivationBlockedTags.IsEmpty() && ASC->HasAnyTags(ActivationBlockedTags))
		{
			CommitAbilityEnd();
			return;
		}
	}

	if (IsOnCooldown()) return; // wait out the RPM cadence

	const ENexusWeaponFireMode Mode = GetFireMode();

	if (Mode == ENexusWeaponFireMode::FullAuto)
	{
		if (!HasAmmoToFire()) { HandleDryFire(); CommitAbilityEnd(); return; }
		FireShot();
		RestartCooldown();
		return;
	}

	if (Mode == ENexusWeaponFireMode::Burst)
	{
		if (BurstRemaining <= 0 || !HasAmmoToFire()) { CommitAbilityEnd(); return; }
		FireShot();
		--BurstRemaining;
		RestartCooldown();
		if (BurstRemaining <= 0) CommitAbilityEnd();
		return;
	}

	// Semi / shotgun should not be active here; guard against a stuck active state.
	CommitAbilityEnd();
}

ENexusWeaponFireMode UNexusAbility_WeaponFire::GetFireMode() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	return Weapon ? Weapon->Ranged.Combat.FireMode : ENexusWeaponFireMode::SemiAuto;
}

bool UNexusAbility_WeaponFire::HasAmmoToFire() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	const UNexusItemInstance* Instance = GetActiveInstance();
	if (!Weapon || !Instance) return false;

	switch (Weapon->Ranged.Ammo.AmmoModel)
	{
	case ENexusWeaponAmmoModel::None:   return true;                 // infinite
	case ENexusWeaponAmmoModel::Pooled: return GetReserveAmmo() > 0; // fires from the reserve pool
	case ENexusWeaponAmmoModel::Magazine:
	default:
		return Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0) > 0;
	}
}

void UNexusAbility_WeaponFire::OnSaveStateRestored()
{
	Super::OnSaveStateRestored();

	// A full-auto / burst saved mid-fire restores to a clean ready state (mirrors Reload).
	BurstRemaining = 0;
	if (IsActive())
	{
		ForceEndAbility();
	}
}

float UNexusAbility_WeaponFire::GetCooldownTotalDuration() const
{
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!W) return Super::GetCooldownTotalDuration();

	// RPM can be lifted/lowered by attachment modifiers (e.g. lightweight bolt
	// carrier increases RPM). Read the effective value through the assembly.
	float Rpm = W->Ranged.Combat.RoundsPerMinute;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		Rpm = Equipped->GetEffectiveStat(NexusGameplayTags::Stat_Weapon_RPM, Rpm);
	}
	return Rpm > 0.0f ? FMath::Max(0.0f, 60.0f / Rpm) : 0.0f;
}

bool UNexusAbility_WeaponFire::HasCooldown() const
{
	return GetCooldownTotalDuration() > 0.0f;
}

bool UNexusAbility_WeaponFire::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;

	const UNexusItemInstance* Instance = GetActiveInstance();
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Instance || !Weapon || !Weapon->bHasRanged) return false; // Fire is a ranged-capability verb.

	return HasAmmoToFire();
}

bool UNexusAbility_WeaponFire::RequestActivateAbility()
{
	if (IsOnCooldown()) return false;

	const UNexusItemInstance* Instance = GetActiveInstance();
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Instance || !Weapon || !Weapon->bHasRanged) return false;

	if (!HasAmmoToFire())
	{
		HandleDryFire();
		RestartCooldown();
		return false;
	}

	if (!Super::RequestActivateAbility()) return false;
	CommitAbility();
	return true;
}

void UNexusAbility_WeaponFire::FireShot() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	UNexusItemInstance* Instance        = GetActiveInstance();
	if (!Weapon || !Instance || !Weapon->bHasRanged) return;

	const FWeaponRangedSpec& R = Weapon->Ranged;

	switch (R.Ammo.AmmoModel)
	{
	case ENexusWeaponAmmoModel::Magazine:
		Instance->ModifyStat(NexusGameplayTags::Stat_Ammo_InMagazine, -1);
		break;
	case ENexusWeaponAmmoModel::Pooled:
		ConsumeReserveAmmo(1); // no magazine — fire decrements the inventory reserve pool directly
		break;
	case ENexusWeaponAmmoModel::None:
	default:
		break;                 // infinite (melee / special)
	}

	FVector  ViewLoc;
	FRotator ViewRot;
	ResolveAimRay(ViewLoc, ViewRot);

	ANexusEquippedActor* EquippedActor = GetEquippedActor();

	// Every tunable comes from the effective stat (attachments + upgrades fold in via the
	// assembly), with the raw fragment value as the fallback when no equipped actor exists.
	auto Stat = [EquippedActor](const FGameplayTag& Tag, const float Fallback)
	{
		return EquippedActor ? EquippedActor->GetEffectiveStat(Tag, Fallback) : Fallback;
	};

	// Muzzle transform — the projectile spawn origin and the muzzle FX location. Falls back
	// to the aim ray when there's no equipped actor / socket.
	FVector  MuzzleLoc = ViewLoc;
	FRotator MuzzleRot = ViewRot;
	if (EquippedActor)
	{
		const FTransform MuzzleXf = EquippedActor->GetSocketTransform(R.Presentation.MuzzleSocketName);
		MuzzleLoc = MuzzleXf.GetLocation();
		MuzzleRot = MuzzleXf.Rotator();
	}

	FNexusHitDeliveryRequest Request;
	Request.Instigator         = GetOwner();
	Request.InstigatorPawn     = Cast<APawn>(GetOwner());
	Request.Causer             = EquippedActor;
	Request.Origin             = ViewLoc;
	Request.MuzzleLocation     = MuzzleLoc;
	Request.Direction          = ViewRot.Vector();
	Request.DamageTypeTag      = R.Combat.DamageTypeTag;
	Request.BaseDamage         = Stat(NexusGameplayTags::Stat_Weapon_Damage,   R.Combat.BaseDamage);
	Request.Range              = Stat(NexusGameplayTags::Stat_Weapon_MaxRange,  R.Combat.MaxRange);
	Request.DamageFalloffCurve = &R.Combat.DamageFalloffCurve;
	Request.ImpulseMagnitude   = 1000.0f;
	Request.TraceType          = UEngineTypes::ConvertToTraceType(NexusCollisionChannels::WeaponTrace);
	Request.bTraceComplex      = true;

	const float HipSpread = Stat(NexusGameplayTags::Stat_Weapon_SpreadHip, R.Combat.SpreadConeDegrees.X);
	const float AdsSpread = Stat(NexusGameplayTags::Stat_Weapon_SpreadADS, R.Combat.SpreadConeDegrees.Y);
	Request.SpreadHalfAngleDegrees = IsAiming() ? AdsSpread : HipSpread;

#if !(UE_BUILD_SHIPPING)
	if (GNexusWeaponDebugTrace > 0)
	{
		Request.bDrawDebug    = true;
		Request.DebugDrawTime = 1.5f;
	}
#endif

	// Hit delivery is a swappable strategy: hitscan today, projectile/etc. by data, with no
	// change to this ability. Shotgun fires N pellets through the same strategy.
	const UNexusHitDelivery* Strategy = ResolveHitDelivery();
	if (!Strategy) return;

	const int32 Pellets = FMath::Max(1, R.Combat.PelletsPerShot);
	int32 ReceiversHit = 0;
	FGameplayTagContainer HitContextTags;
	for (int32 i = 0; i < Pellets; ++i)
	{
		FNexusHitDeliveryResult Result;
		Strategy->Deliver(Request, Result);

#if !(UE_BUILD_SHIPPING)
		if (GNexusWeaponDebugTrace > 1)
		{
			for (const FHitResult& H : Result.Hits)
			{
				UE_LOG(LogNexusWeapon, Log, TEXT("[WeaponFire] hit actor=%s bone=%s dist=%.0f damaged=%d"),
					*GetNameSafe(H.GetActor()), *H.BoneName.ToString(),
					(H.ImpactPoint - Request.Origin).Size(), Result.ReceiversDamaged);
			}
		}
#endif

		for (const FHitResult& Hit : Result.Hits)
		{
			SpawnImpactPresentation(Hit);
		}

		ReceiversHit += Result.ReceiversDamaged;
		HitContextTags.AppendTags(Result.ContextTags);
	}

	// Attacker-side hit confirmation (hit-marker + weak-point cue) for the HUD.
	BroadcastHitConfirmed(ReceiversHit, HitContextTags);

	// Per-shot presentation (once, regardless of pellet count).
	if (R.Combat.FireCameraShake)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->ClientStartCameraShake(R.Combat.FireCameraShake, R.Combat.FireCameraShakeScale);
		}
	}

	ApplyRecoil();

	if (EquippedActor)
	{
		PlayMontage(EquippedActor->GetEffectiveHostMontage(NexusGameplayTags::Action_Equipment_Weapon_Fire));
	}

	if (USoundBase* S = NexusWeapon::GetEquippedAsset(R.Presentation.FireSound,
		TEXT("FireSound"), GetActiveDefinition()))
	{
		UGameplayStatics::PlaySoundAtLocation(this, S, ViewLoc);
	}

	if (UFXSystemAsset* FX = NexusWeapon::GetEquippedAsset(R.Presentation.MuzzleFlash,
		TEXT("MuzzleFlash"), GetActiveDefinition()))
	{
		SpawnFXAtLocation(this, FX, MuzzleLoc, MuzzleRot);
	}
}

bool UNexusAbility_WeaponFire::IsAiming() const
{
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		return ASC->HasTag(NexusGameplayTags::Character_State_Weapon_Aiming);
	}
	return false;
}

const UNexusHitDelivery* UNexusAbility_WeaponFire::ResolveHitDelivery() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	TSubclassOf<UNexusHitDelivery> Class = Weapon ? Weapon->Ranged.HitDelivery : nullptr;
	if (!Class)
	{
		// Unset = the default instant hitscan delivery.
		Class = UNexusHitDelivery_Hitscan::StaticClass();
	}
	return GetDefault<UNexusHitDelivery>(Class);
}

void UNexusAbility_WeaponFire::SpawnImpactPresentation(const FHitResult& Hit) const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;

	if (UFXSystemAsset* Impact = NexusWeapon::GetEquippedAsset(Weapon->Ranged.Presentation.ImpactFX,
		TEXT("ImpactFX"), GetActiveDefinition()))
	{
		SpawnFXAtLocation(this, Impact, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	if (USoundBase* ImpactS = NexusWeapon::GetEquippedAsset(Weapon->Ranged.Presentation.ImpactSound,
		TEXT("ImpactSound"), GetActiveDefinition()))
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactS, Hit.ImpactPoint);
	}
}

void UNexusAbility_WeaponFire::ApplyRecoil() const
{
	// Recoil perturbs the player's aim through the control rotation. AI has no camera to
	// kick, so it's player-only (guarded like the camera shake above).
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;

	ANexusEquippedActor* EquippedActor = GetEquippedActor();
	const auto Stat = [EquippedActor](const FGameplayTag& Tag, const float Fallback)
	{
		return EquippedActor ? EquippedActor->GetEffectiveStat(Tag, Fallback) : Fallback;
	};

	float Vertical   = Stat(NexusGameplayTags::Stat_Weapon_RecoilVertical,   Weapon->Ranged.Combat.RecoilVertical);
	float Horizontal = Stat(NexusGameplayTags::Stat_Weapon_RecoilHorizontal, Weapon->Ranged.Combat.RecoilHorizontal);

	// Steady-aim control: aiming reduces the felt kick (RE4R over-the-shoulder aim).
	if (IsAiming())
	{
		const float Control = FMath::Clamp(Weapon->Ranged.Combat.RecoilAimControl, 0.0f, 1.0f);
		Vertical   *= Control;
		Horizontal *= Control;
	}

	if (Vertical <= 0.0f && Horizontal <= 0.0f) return;

	FRotator Rot = PC->GetControlRotation();
	Rot.Pitch += Vertical;                                  // upward kick (camera manager clamps to pitch limits)
	Rot.Yaw   += FMath::FRandRange(-Horizontal, Horizontal); // randomized left/right
	PC->SetControlRotation(Rot);
}

void UNexusAbility_WeaponFire::HandleDryFire() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;

	if (const ANexusEquippedActor* EquippedActor = GetEquippedActor())
	{
		PlayMontage(EquippedActor->GetEffectiveHostMontage(NexusGameplayTags::Action_Equipment_Weapon_DryFire));
	}

	if (USoundBase* S = NexusWeapon::GetEquippedAsset(Weapon->Ranged.Presentation.DryFireSound,
		TEXT("DryFireSound"), GetActiveDefinition()))
	{
		if (const AActor* Owner = GetOwner())
		{
			UGameplayStatics::PlaySoundAtLocation(this, S, Owner->GetActorLocation());
		}
	}
}

UAnimMontage* UNexusAbility_WeaponFire::PlayMontage(UAnimMontage* Montage) const
{
	if (!Montage) return nullptr;

	// Through the host interface — no Cast<ACharacter>, no first-person assumption.
	if (INexusEquipmentInterface* Host = GetEquipmentHost())
	{
		if (Host->PlayMontage(Montage) > 0.0f)
		{
			return Montage;
		}
	}
	return nullptr;
}
