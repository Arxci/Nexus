#include "NexusAbility_WeaponFire.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "Camera/CameraShakeBase.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

#include "HAL/IConsoleManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"

#include "Sound/SoundBase.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/Combat/NexusDamageContext.h"
#include "Nexus/Combat/NexusDamageReceiverInterface.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/Fragments/NexusFragment_Weapon.h"
#include "Nexus/Weapon/NexusWeaponEquippedActor.h"


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
	bCooldownOnActivation   = true;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponFire::RequestDeactivateAbility(bool bForce)
{
	if (!bForce && !IsActive()) return false;
	CommitAbilityEnd();
	return true;
}

void UNexusAbility_WeaponFire::CommitAbility()
{
	Super::CommitAbility();

	if (!GetWeaponFragment()) { CommitAbilityEnd(); return; }

	FireShot();

	CommitAbilityEnd();
}

float UNexusAbility_WeaponFire::GetCooldownTotalDuration() const
{
	if (const FNexusFragment_Weapon* W = GetWeaponFragment())
	{
		return FMath::Max(0.0f, W->GetFireInterval());
	}
	return Super::GetCooldownTotalDuration();
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
	if (!Instance || !Weapon) return false;

	if (Weapon->Ammo.AmmoModel == ENexusWeaponAmmoModel::None) return true;
	return Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0) > 0;
}

bool UNexusAbility_WeaponFire::RequestActivateAbility()
{
	if (IsOnCooldown()) return false;

	const UNexusItemInstance* Instance = GetActiveInstance();
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Instance || !Weapon) return false;

	const bool bRequiresAmmo = Weapon->Ammo.AmmoModel != ENexusWeaponAmmoModel::None;
	const bool bHasAmmo      = Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0) > 0;
	if (bRequiresAmmo && !bHasAmmo)
	{
		// Cap dry-fire spam at the weapon's fire interval. Re-uses the standard
		// cooldown machinery so trigger-mash can't strobe the SFX/anim. The
		// IsOnCooldown() check at the top of this function blocks subsequent
		// presses until the interval elapses.
		HandleDryFire();
		RestartCooldown();
		return false;
	}

	if (!Super::RequestActivateAbility()) return false;
	CommitAbility();
	return true;
}

void UNexusAbility_WeaponFire::FireShot()
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	UNexusItemInstance* Instance       = GetActiveInstance();
	if (!Weapon || !Instance) return;

	if (Weapon->Ammo.AmmoModel != ENexusWeaponAmmoModel::None)
	{
		Instance->ModifyStat(NexusGameplayTags::Stat_Ammo_InMagazine, -1);
	}

	FVector  ViewLoc;
	FRotator ViewRot;
	if (const AController* Ctrl = GetController())
	{
		Ctrl->GetPlayerViewPoint(ViewLoc, ViewRot);
	}
	else if (const AActor* Owner = GetOwner())
	{
		ViewLoc = Owner->GetActorLocation() + FVector(0, 0, 60.0f);
		ViewRot = Owner->GetActorRotation();
	}

	const int32 Pellets = FMath::Max(1, Weapon->Combat.PelletsPerShot);
	for (int32 i = 0; i < Pellets; ++i)
	{
		FireOnePellet(ViewLoc, ViewRot);
	}

	if (Weapon->Combat.FireCameraShake)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->ClientStartCameraShake(Weapon->Combat.FireCameraShake, Weapon->Combat.FireCameraShakeScale);
		}
	}

	const ANexusWeaponEquippedActor* WeaponActor = GetEquippedWeaponActor();

	PlayMontage(WeaponActor ? WeaponActor->CachedFireMontage.Get() : Weapon->Animations.FireMontage.LoadSynchronous());

	if (USoundBase* S = WeaponActor ? WeaponActor->CachedFireSound.Get() : Weapon->Presentation.FireSound.LoadSynchronous())
	{
		UGameplayStatics::PlaySoundAtLocation(this, S, ViewLoc);
	}

	if (UFXSystemAsset* FX = WeaponActor ? WeaponActor->CachedMuzzleFlash.Get() : Weapon->Presentation.MuzzleFlash.LoadSynchronous())
	{
		// Falls back to the view location so the FX still spawns on a weapon
		// definition that doesn't use ANexusWeaponEquippedActor. The first-person
		// rifle case (the common one) takes the muzzle-socket path.
		FVector MuzzleLoc = ViewLoc;
		FRotator MuzzleRot = ViewRot;
		if (WeaponActor)
		{
			const FTransform MuzzleXf = WeaponActor->GetSocketTransform(Weapon->Presentation.MuzzleSocketName);
			MuzzleLoc = MuzzleXf.GetLocation();
			MuzzleRot = MuzzleXf.Rotator();
		}
		SpawnFXAtLocation(this, FX, MuzzleLoc, MuzzleRot);
	}
}

void UNexusAbility_WeaponFire::FireOnePellet(const FVector& ViewLoc, const FRotator& ViewRot)
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;

	UWorld* World = GetWorld();
	if (!World) return;

	bool bAiming = false;
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		bAiming = ASC->HasTag(NexusGameplayTags::Character_State_Weapon_Aiming);
	}
	const float ConeHalfDeg = bAiming ? Weapon->Combat.SpreadConeDegrees.Y : Weapon->Combat.SpreadConeDegrees.X;

	const FVector AimDir = ViewRot.Vector();
	const FVector Spread = FMath::VRandCone(AimDir, FMath::DegreesToRadians(ConeHalfDeg));
	const FVector End    = ViewLoc + Spread * Weapon->Combat.MaxRange;

	TArray<AActor*> ActorsToIgnore;
	if (AActor* Owner = GetOwner()) ActorsToIgnore.Add(Owner);

	const ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(NexusCollisionChannels::WeaponTrace);

	EDrawDebugTrace::Type DrawDebug = EDrawDebugTrace::None;
#if !(UE_BUILD_SHIPPING)
	if (GNexusWeaponDebugTrace > 0)
	{
		DrawDebug = EDrawDebugTrace::ForDuration;
	}
#endif

	FHitResult Hit;
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(
		this, ViewLoc, End, TraceType, /*bTraceComplex*/true,
		ActorsToIgnore, DrawDebug, Hit, /*bIgnoreSelf*/true,
		FLinearColor::Red, FLinearColor::Green, /*DrawTime*/1.5f);

#if !(UE_BUILD_SHIPPING)
	if (GNexusWeaponDebugTrace > 1)
	{
		UE_LOG(LogTemp, Log, TEXT("[WeaponFire] hit=%d actor=%s bone=%s dist=%.0f"),
			bHit, *GetNameSafe(Hit.GetActor()), *Hit.BoneName.ToString(),
			bHit ? FVector::Distance(ViewLoc, Hit.ImpactPoint) : -1.0f);
	}
#endif

	if (!bHit) return;

	AActor* HitActor = Hit.GetActor();
	if (!HitActor) return;

	if (HitActor->Implements<UNexusDamageReceiver>())
	{
		FNexusDamageContext Ctx;
		Ctx.Instigator       = GetOwner();
		Ctx.Causer           = GetEquippedActor();
		Ctx.DamageTypeTag    = Weapon->Combat.DamageTypeTag;
		Ctx.BaseDamage       = Weapon->Combat.BaseDamage;
		Ctx.HitResult        = Hit;
		Ctx.ImpulseDirection = Spread;
		Ctx.ImpulseMagnitude = 1000.0f;

		const float Distance = FVector::Distance(ViewLoc, Hit.ImpactPoint);
		if (Weapon->Combat.DamageFalloffCurve.GetRichCurveConst() && Weapon->Combat.DamageFalloffCurve.GetRichCurveConst()->GetNumKeys() > 0)
		{
			Ctx.Multiplier = Weapon->Combat.DamageFalloffCurve.GetRichCurveConst()->Eval(Distance, 1.0f);
		}

		INexusDamageReceiver::Execute_ReceiveDamage(HitActor, Ctx);
	}

	if (UFXSystemAsset* Impact = Weapon->Presentation.ImpactFX.LoadSynchronous())
	{
		SpawnFXAtLocation(this, Impact, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	if (USoundBase* ImpactS = Weapon->Presentation.ImpactSound.LoadSynchronous())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactS, Hit.ImpactPoint);
	}
}

UAnimMontage* UNexusAbility_WeaponFire::PlayMontage(UAnimMontage* Montage) const
{
	if (!Montage) return nullptr;

	if (const ACharacter* Char = Cast<ACharacter>(GetOwner()))
	{
		if (const USkeletalMeshComponent* Mesh = Char->GetMesh())
		{
			if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
			{
				AnimInstance->Montage_Play(Montage);
				return Montage;
			}
		}
	}
	return nullptr;
}

void UNexusAbility_WeaponFire::HandleDryFire() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;

	const ANexusWeaponEquippedActor* WeaponActor = GetEquippedWeaponActor();

	PlayMontage(WeaponActor ? WeaponActor->CachedDryFireMontage.Get() : Weapon->Animations.DryFireMontage.LoadSynchronous());

	if (USoundBase* S = WeaponActor ? WeaponActor->CachedDryFireSound.Get() : Weapon->Presentation.DryFireSound.LoadSynchronous())
	{
		if (const AActor* Owner = GetOwner())
		{
			UGameplayStatics::PlaySoundAtLocation(this, S, Owner->GetActorLocation());
		}
	}
}