// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_WeaponFire.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Curves/CurveVector.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
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
#include "Nexus/Player/NexusPlayerCameraManager.h"
#include "Nexus/Weapon/NexusFragment_Weapon.h"



namespace
{
	/** Console toggle: 0 off, 1 draw line + impact, 2 also log per-shot details. */
	static int32 GNexusWeaponDebugTrace = 0;
	static FAutoConsoleVariableRef CVarNexusWeaponDebugTrace(
		TEXT("Nexus.Weapon.Debugtrace"),
		GNexusWeaponDebugTrace,
		TEXT("Visualize weapon traces. 0 = off, 1 = draw line + impact sphere, 2 = also UE_LOG per shot."),
		ECVF_Cheat);
	
	/** Spawn a Cascade or Niagara emitter at a world transform — both flavours of UFXSystemAsset. */
	void SpawnFXAtLocation(UObject* WorldContext, UFXSystemAsset* FX, const FVector& Loc, const FRotator& Rot)
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
	bCooldownOnActivation   = true;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponFire::RequestDeactivateAbility(bool bForce)
{
	// Mirror Reload — without this, tag-based deactivate would only fire the K2 event.
	if (!bForce && !IsActive()) return false;
	CommitAbilityEnd();
	return true;
}

void UNexusAbility_WeaponFire::CommitAbility()
{
	Super::CommitAbility();

	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!W) { CommitAbilityEnd(); return; }

	FireShot();

	switch (W->FireMode)
	{
	case ENexusWeaponFireMode::FullAuto:
		// Stay active; TickAbility re-fires while cooldown clears AND intent is held.
		break;

	case ENexusWeaponFireMode::Burst:
		BurstShotsRemaining = FMath::Max(0, W->BurstCount - 1);
		if (BurstShotsRemaining <= 0) CommitAbilityEnd();
		break;

	case ENexusWeaponFireMode::SemiAuto:
	case ENexusWeaponFireMode::Shotgun:
	case ENexusWeaponFireMode::Melee:
	default:
		CommitAbilityEnd();
		break;
	}
}

void UNexusAbility_WeaponFire::CommitAbilityEnd()
{
	BurstShotsRemaining = 0;
	Super::CommitAbilityEnd();
}

void UNexusAbility_WeaponFire::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);

	if (!IsActive()) return;
	if (IsOnCooldown()) return;

	const FNexusFragment_Weapon* W = GetWeaponFragment();
	const UNexusItemInstance*    I = GetActiveInstance();
	if (!W || !I) { CommitAbilityEnd(); return; }

	// Out of ammo mid-burst/full-auto — bail with a click, don't keep ticking.
	const bool bRequiresAmmo = W->AmmoModel != ENexusWeaponAmmoModel::None;
	const bool bHasAmmo      = I->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0) > 0;
	if (bRequiresAmmo && !bHasAmmo)
	{
		HandleDryFire();
		CommitAbilityEnd();
		return;
	}

	if (IsBlockedByOwnedTags()) { CommitAbilityEnd(); return; }

	switch (W->FireMode)
	{
	case ENexusWeaponFireMode::Burst:
		if (BurstShotsRemaining <= 0) { CommitAbilityEnd(); return; }
		--BurstShotsRemaining;
		FireShot();
		RestartCooldown();
		if (BurstShotsRemaining <= 0) CommitAbilityEnd();
		break;

	case ENexusWeaponFireMode::FullAuto:
		if (!IsFireIntentHeld()) { CommitAbilityEnd(); return; }
		FireShot();
		RestartCooldown();
		break;

	default:
		// SemiAuto / Shotgun / Melee should never be Active here, but guard anyway.
		CommitAbilityEnd();
		break;
	}
}

bool UNexusAbility_WeaponFire::IsFireIntentHeld() const
{
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		return ASC->HasTag(NexusGameplayTags::Ability_Weapon_Intent_Fire);
	}
	return false;
}

bool UNexusAbility_WeaponFire::IsBlockedByOwnedTags() const
{
	const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent();
	return ASC && !ActivationBlockedTags.IsEmpty() && ASC->HasAnyTags(ActivationBlockedTags);
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
	// Must report true while a weapon with positive RPM is active, otherwise
	// the ASC tick loop skips TickCooldown and the cooldown sticks at "on" forever.
	return GetCooldownTotalDuration() > 0.0f;
}

bool UNexusAbility_WeaponFire::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;

	const UNexusItemInstance* Inst = GetActiveInstance();
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!Inst || !W) return false;

	if (W->AmmoModel == ENexusWeaponAmmoModel::None) return true;
	return Inst->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0) > 0;
}

bool UNexusAbility_WeaponFire::RequestActivateAbility()
{
	if (IsOnCooldown())
	{
		UE_LOG(LogTemp, Verbose, TEXT("[WeaponFire] blocked: on cooldown (%.2fs left)"), GetCooldownTimeRemaining());
		return false;
	}

	const UNexusItemInstance* Inst = GetActiveInstance();
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!Inst || !W)
	{
		UE_LOG(LogTemp, Verbose, TEXT("[WeaponFire] blocked: nothing equipped (Inst=%s, WeaponFragment=%s)"),
			Inst ? TEXT("ok") : TEXT("null"),
			W    ? TEXT("ok") : TEXT("null"));
		return false;
	}

	const bool bRequiresAmmo = W->AmmoModel != ENexusWeaponAmmoModel::None;
	const bool bHasAmmo      = Inst->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0) > 0;
	if (bRequiresAmmo && !bHasAmmo)
	{
		UE_LOG(LogTemp, Verbose, TEXT("[WeaponFire] dry-fire (mag=0/%d)"), W->MagazineSize);
		HandleDryFire();
		return false;
	}

	if (!Super::RequestActivateAbility())
	{
		UE_LOG(LogTemp, Verbose, TEXT("[WeaponFire] blocked: Super::RequestActivateAbility (CanActivate or tag-block)"));
		return false;
	}
	CommitAbility();
	return true;
}

void UNexusAbility_WeaponFire::FireShot()
{
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	UNexusItemInstance* Inst       = GetActiveInstance();
	if (!W || !Inst) return;

	if (W->AmmoModel != ENexusWeaponAmmoModel::None)
	{
		Inst->ModifyStat(NexusGameplayTags::Stat_Ammo_InMagazine, -1);
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

	const int32 Pellets = FMath::Max(1, W->PelletsPerShot);
	for (int32 i = 0; i < Pellets; ++i)
	{
		FireOnePellet(ViewLoc, ViewRot);
	}

	// 3. Recoil push to the camera manager (single shot — pellets share one kick).
	if (W->RecoilImpulseCurve)
	{
		const FVector Impulse = ConsumeRecoilImpulse();
		if (AController* Ctrl = GetController())
		{
			if (APlayerController* PC = Cast<APlayerController>(Ctrl))
			{
				if (ANexusPlayerCameraManager* CM = Cast<ANexusPlayerCameraManager>(PC->PlayerCameraManager))
				{
					CM->KickCamera(FVector2D(Impulse.X, Impulse.Y));
				}
			}
		}
	}

	const ANexusEquippedActor* EA = GetEquippedActor();

	PlayMontageSafe(W->FireMontage);
	if (USoundBase* S = W->FireSound.LoadSynchronous())
	{
		UGameplayStatics::PlaySoundAtLocation(this, S, ViewLoc);
	}

	if (UFXSystemAsset* FX = W->MuzzleFlash.LoadSynchronous())
	{
		if (const ANexusEquippedActor* EA = GetEquippedActor())
		{
			const FTransform MuzzleXf = EA->GetSocketTransform(W->MuzzleSocketName);
			SpawnFXAtLocation(this, FX, MuzzleXf.GetLocation(), MuzzleXf.Rotator());
		}
	}
}

void UNexusAbility_WeaponFire::FireOnePellet(const FVector& ViewLoc, const FRotator& ViewRot)
{
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!W) return;

	UWorld* World = GetWorld();
	if (!World) return;

	// Spread cone: hipfire vs aim picked by the Aiming owned-tag on the ASC.
	bool bAiming = false;
	if (const UNexusAbilitySystemComponent* ASC = GetNexusAbilitySystemComponent())
	{
		bAiming = ASC->HasTag(NexusGameplayTags::Character_State_Weapon_Aiming);
	}
	const float ConeHalfDeg = bAiming ? W->SpreadConeDegrees.Y : W->SpreadConeDegrees.X;

	const FVector AimDir = ViewRot.Vector();
	const FVector Spread = FMath::VRandCone(AimDir, FMath::DegreesToRadians(ConeHalfDeg));
	const FVector End    = ViewLoc + Spread * W->MaxRange;

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
		UE_LOG(LogTemp, Log, TEXT("[WeaponFire] hit=%d actor=%s dist=%.0f"),
			bHit, *GetNameSafe(Hit.GetActor()), bHit ? FVector::Distance(ViewLoc, Hit.ImpactPoint) : -1.0f);
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
		Ctx.DamageTypeTag    = W->DamageTypeTag;
		Ctx.BaseDamage       = W->BaseDamage;
		Ctx.HitResult        = Hit;
		Ctx.ImpulseDirection = Spread;
		Ctx.ImpulseMagnitude = 1000.0f;

		const float Distance = FVector::Distance(ViewLoc, Hit.ImpactPoint);
		if (W->DamageFalloffCurve.GetRichCurveConst() && W->DamageFalloffCurve.GetRichCurveConst()->GetNumKeys() > 0)
		{
			Ctx.Multiplier = W->DamageFalloffCurve.GetRichCurveConst()->Eval(Distance, 1.0f);
		}

		INexusDamageReceiver::Execute_ReceiveDamage(HitActor, Ctx);
	}

	// Impact FX at the surface — Cascade or Niagara, picked by type at runtime.
	if (UFXSystemAsset* Impact = W->ImpactFX.LoadSynchronous())
	{
		SpawnFXAtLocation(this, Impact, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}
}

UAnimMontage* UNexusAbility_WeaponFire::PlayMontageSafe(const TSoftObjectPtr<UAnimMontage>& Soft) const
{
	UAnimMontage* M = Soft.LoadSynchronous();
	if (!M) return nullptr;

	if (const ACharacter* C = Cast<ACharacter>(GetOwner()))
	{
		if (USkeletalMeshComponent* Mesh = C->GetMesh())
		{
			if (UAnimInstance* AI = Mesh->GetAnimInstance())
			{
				AI->Montage_Play(M);
				return M;
			}
		}
	}
	return nullptr;
}

void UNexusAbility_WeaponFire::HandleDryFire()
{
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!W) return;

	PlayMontageSafe(W->DryFireMontage);
	if (USoundBase* S = W->DryFireSound.LoadSynchronous())
	{
		if (const AActor* Owner = GetOwner())
		{
			UGameplayStatics::PlaySoundAtLocation(this, S, Owner->GetActorLocation());
		}
	}
}

FVector UNexusAbility_WeaponFire::ConsumeRecoilImpulse()
{
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!W || !W->RecoilImpulseCurve) return FVector::ZeroVector;

	const UWorld* World = GetWorld();
	const float Now     = World ? World->GetTimeSeconds() : 0.0f;

	// Reset the burst pattern after a quiet window. Author the curve as a function
	// of shot index: time=0 -> first shot, time=1 -> second, etc.
	if (Now - LastFireTime > W->RecoilResetWindow)
	{
		ShotIndex = 0;
	}

	const FVector Impulse = W->RecoilImpulseCurve->GetVectorValue(static_cast<float>(ShotIndex));

	LastFireTime = Now;
	++ShotIndex;
	return Impulse;
}