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
#include "Nexus/Inventory/Fragments/Weapon/NexusFragment_Weapon.h"

UNexusAbility_WeaponReload::UNexusAbility_WeaponReload()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Weapon_Reload);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Reloading);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Reloading);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	CancelAbilitiesWithTags.AddTag(NexusGameplayTags::Ability_Weapon_Fire);
	bCooldownOnActivation   = false;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponReload::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;

	const UNexusItemInstance* Instance = GetActiveInstance();
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Instance || !Weapon) return false;
	if (Weapon->Ammo.AmmoModel == ENexusWeaponAmmoModel::None) return false;

	const int32 InMag = Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0);
	if (InMag >= Weapon->Ammo.MagazineSize) return false;

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

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) { CommitAbilityEnd(); return; }

	bAmmoTransferred = false;

	UAnimInstance* ReloadAnimInstance = nullptr;
	float MontageDuration = 0.0f;

	if (UAnimMontage* Montage = Weapon->Animations.ReloadMontage.LoadSynchronous())
	{
		if (const ACharacter* Char = Cast<ACharacter>(GetOwner()))
		{
			if (USkeletalMeshComponent* Mesh = Char->GetMesh())
			{
				if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
				{
					MontageDuration = AnimInstance->Montage_Play(Montage);
					if (MontageDuration > 0.0f)
					{
						ReloadAnimInstance = AnimInstance;
						AnimInstance->OnPlayMontageNotifyBegin.AddUniqueDynamic(
							this, &UNexusAbility_WeaponReload::HandleNotifyBegin);
					}
				}
			}
		}
	}

	BoundAnimInstance = ReloadAnimInstance;

	if (USoundBase* ReloadSound = Weapon->Presentation.ReloadSound.LoadSynchronous())
	{
		if (const AActor* Owner = GetOwner())
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, Owner->GetActorLocation());
		}
	}

	// If the montage played, prefer its actual duration over the configured fallback
	// — keeps ReloadDuration honest if the designer trims the montage in the editor.
	const float ConfiguredDuration = FMath::Max(0.0f, Weapon->Reload.ReloadDuration);
	const float Duration = MontageDuration > 0.0f ? MontageDuration : ConfiguredDuration;
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
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle_ReloadFinish);
	}

	if (UAnimInstance* AnimInstance = BoundAnimInstance.Get())
	{
		AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UNexusAbility_WeaponReload::HandleNotifyBegin);
	}
	BoundAnimInstance = nullptr;

	Super::CommitAbilityEnd();
}

void UNexusAbility_WeaponReload::HandleNotifyBegin(const FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;
	if (NotifyName != Weapon->Reload.AmmoTransferNotifyName) return;

	TransferAmmo();
}

void UNexusAbility_WeaponReload::TransferAmmo()
{
	if (bAmmoTransferred) return;

	UNexusItemInstance* Instance       = GetActiveInstance();
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Instance || !Weapon) return;

	const int32 CurrentInMag = Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0);
	const int32 Needed       = FMath::Max(0, Weapon->Ammo.MagazineSize - CurrentInMag);
	const int32 Available    = GetReserveAmmo();
	const int32 Transferring = FMath::Min(Needed, Available);

	if (Transferring > 0)
	{
		const int32 Consumed = ConsumeReserveAmmo(Transferring);
		Instance->SetStat(NexusGameplayTags::Stat_Ammo_InMagazine, CurrentInMag + Consumed);
	}
	bAmmoTransferred = true;
}

void UNexusAbility_WeaponReload::FinishReload()
{
	// Fallback path: timer expired. If the AmmoTransfer notify already moved ammo, this is a no-op.
	TransferAmmo();
	CommitAbilityEnd();
}

int32 UNexusAbility_WeaponReload::GetReserveAmmo() const
{
	const FNexusFragment_Weapon* W = GetWeaponFragment();
	const AActor* Owner            = GetOwner();
	if (!W || !Owner || !W->Ammo.AmmoIdentityTag.IsValid()) return 0;
	if (const UNexusInventoryComponent* Inv = Owner->FindComponentByClass<UNexusInventoryComponent>())
	{
		return Inv->GetTotalCountForIdentityTag(W->Ammo.AmmoIdentityTag);
	}
	return 0;
}

int32 UNexusAbility_WeaponReload::ConsumeReserveAmmo(const int32 Amount) const
{
	if (Amount <= 0) return 0;
	
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	const AActor* Owner = GetOwner();
	
	if (!Weapon || !Owner || !Weapon->Ammo.AmmoIdentityTag.IsValid()) return 0;

	UNexusInventoryComponent* Inventory = Owner->FindComponentByClass<UNexusInventoryComponent>();
	if (!Inventory) return 0;

	int32 Remaining = Amount;
	TArray<UNexusItemInstance*> Snapshot = Inventory->GetItems();
	for (UNexusItemInstance* Inst : Snapshot)
	{
		if (Remaining <= 0) break;
		if (!Inst) continue;
		if (!Inst->GetIdentityTag().MatchesTagExact(Weapon->Ammo.AmmoIdentityTag)) continue;

		const int32 Taken = Inventory->RemoveFromInstance(Inst, Remaining);
		Remaining -= Taken;
	}
	return Amount - Remaining;
}

void UNexusAbility_WeaponReload::OnSaveStateRestored()
{
	Super::OnSaveStateRestored();
	
	if (IsActive())
	{
		ForceEndAbility();
	}
}