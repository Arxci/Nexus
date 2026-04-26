// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusAbility_WeaponReload.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Weapon/NexusFragment_Weapon.h"

UNexusAbility_WeaponReload::UNexusAbility_WeaponReload()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Weapon_Reload);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Reloading);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Reloading);
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Weapon_Fire); // <-- new
	bCooldownOnActivation   = false;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponReload::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;

	const UNexusItemInstance* Inst = GetActiveInstance();
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!Inst || !W) return false;
	if (W->AmmoModel == ENexusWeaponAmmoModel::None) return false;

	const int32 InMag = Inst->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0);
	if (InMag >= W->MagazineSize) return false;

	return GetReserveAmmo() > 0;
}

bool UNexusAbility_WeaponReload::RequestActivateAbility()
{
	if (!Super::RequestActivateAbility()) return false;
	CommitAbility();
	return true;
}

bool UNexusAbility_WeaponReload::RequestDeactivateAbility(bool bForce)
{
	if (!bForce && !IsActive()) return false;
	CommitAbilityEnd();
	return true;
}

void UNexusAbility_WeaponReload::CommitAbility()
{
	Super::CommitAbility();

	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!W) { CommitAbilityEnd(); return; }

	if (UAnimMontage* M = W->ReloadMontage.LoadSynchronous())
	{
		if (const ACharacter* C = Cast<ACharacter>(GetOwner()))
		{
			if (UAnimInstance* AI = C->GetMesh()->GetAnimInstance())
			{
				AI->Montage_Play(M);
			}
		}
	}
	if (USoundBase* S = W->ReloadSound.LoadSynchronous())
	{
		if (const AActor* Owner = GetOwner())
		{
			UGameplayStatics::PlaySoundAtLocation(this, S, Owner->GetActorLocation());
		}
	}

	const float Duration = FMath::Max(0.0f, W->ReloadDuration);
	if (Duration <= 0.0f)
	{
		FinishReload();
	}
	else if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(TimerHandle_ReloadFinish, this,
			&UNexusAbility_WeaponReload::FinishReload, Duration, false);
	}
}

void UNexusAbility_WeaponReload::CommitAbilityEnd()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle_ReloadFinish);
	}
	Super::CommitAbilityEnd();
}

void UNexusAbility_WeaponReload::FinishReload()
{
	UNexusItemInstance* Inst       = GetActiveInstance();
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	if (!Inst || !W) { CommitAbilityEnd(); return; }

	const int32 CurrentInMag = Inst->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0);
	const int32 Needed       = FMath::Max(0, W->MagazineSize - CurrentInMag);
	const int32 Available    = GetReserveAmmo();
	const int32 Transferring = FMath::Min(Needed, Available);

	if (Transferring > 0)
	{
		const int32 Consumed = ConsumeReserveAmmo(Transferring);
		Inst->SetStat(NexusGameplayTags::Stat_Ammo_InMagazine, CurrentInMag + Consumed);
	}

	CommitAbilityEnd();
}

int32 UNexusAbility_WeaponReload::GetReserveAmmo() const
{
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	const AActor* Owner            = GetOwner();
	if (!W || !Owner || !W->AmmoIdentityTag.IsValid()) return 0;
	if (const UNexusInventoryComponent* Inv = Owner->FindComponentByClass<UNexusInventoryComponent>())
	{
		return Inv->GetTotalCountForIdentityTag(W->AmmoIdentityTag);
	}
	return 0;
}

int32 UNexusAbility_WeaponReload::ConsumeReserveAmmo(int32 Amount)
{
	if (Amount <= 0) return 0;
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	AActor* Owner                  = GetOwner();
	if (!W || !Owner || !W->AmmoIdentityTag.IsValid()) return 0;

	UNexusInventoryComponent* Inv = Owner->FindComponentByClass<UNexusInventoryComponent>();
	if (!Inv) return 0;

	int32 Remaining = Amount;
	TArray<UNexusItemInstance*> Snapshot = Inv->GetItems();
	for (UNexusItemInstance* Inst : Snapshot)
	{
		if (Remaining <= 0) break;
		if (!Inst) continue;
		if (!Inst->GetIdentityTag().MatchesTagExact(W->AmmoIdentityTag)) continue;

		const int32 Taken = Inv->RemoveFromInstance(Inst, Remaining);
		Remaining -= Taken;
	}
	return Amount - Remaining;
}

void UNexusAbility_WeaponReload::OnSaveStateRestored()
{
	Super::OnSaveStateRestored();

	// Timers are transient. If the player saved mid-reload, the activation state is
	// loaded as Active but no timer is running — they'd be stuck Reloading forever
	// with Fire blocked. Abort the reload; the player can re-press Reload to retry.
	if (IsActive())
	{
		ForceEndAbility();
	}
}