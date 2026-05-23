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
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
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

	// Read the effective magazine size off the assembly so an extended-mag
	// attachment lifts the cap; fall back to the fragment's authored value
	// when no equipped actor is currently spawned.
	int32 EffectiveMagSize = Weapon->Ammo.MagazineSize;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		EffectiveMagSize = FMath::FloorToInt(
			Equipped->GetEffectiveStat(NexusGameplayTags::Stat_Weapon_MagazineSize,
				static_cast<float>(Weapon->Ammo.MagazineSize)));
	}

	const int32 InMag = FMath::RoundToInt(Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0));
	if (InMag >= EffectiveMagSize) return false;

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

	// The arms-side reload montage, resolved through the assembly so a drum-mag
	// attachment can override it via ActionOverrides; falls back to the
	// equippable fragment's authored Reload arms montage.
	UAnimMontage* ArmsReload = nullptr;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		ArmsReload = Equipped->GetEffectiveArmsMontage(NexusGameplayTags::Action_Equipment_Weapon_Reload);
	}

	if (ArmsReload)
	{
		if (const ACharacter* Char = Cast<ACharacter>(GetOwner()))
		{
			if (USkeletalMeshComponent* Mesh = Char->GetMesh())
			{
				if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
				{
					MontageDuration = AnimInstance->Montage_Play(ArmsReload);
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

	BoundAnimInstance   = ReloadAnimInstance;
	BoundReloadMontage  = ArmsReload;

	if (USoundBase* ReloadSound = NexusWeapon::GetEquippedAsset(Weapon->Presentation.ReloadSound,
	TEXT("ReloadSound"), GetActiveDefinition()))
	{
		if (const AActor* Owner = GetOwner())
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, Owner->GetActorLocation());
		}
	}

	// Effective reload duration: assembly modifier > montage length > fragment fallback.
	float EffectiveConfigDuration = Weapon->Reload.ReloadDuration;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		EffectiveConfigDuration = Equipped->GetEffectiveStat(
			NexusGameplayTags::Stat_Weapon_ReloadDuration, EffectiveConfigDuration);
	}
	EffectiveConfigDuration = FMath::Max(0.0f, EffectiveConfigDuration);

	const float Duration = MontageDuration > 0.0f ? MontageDuration : EffectiveConfigDuration;
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
	BoundAnimInstance  = nullptr;
	BoundReloadMontage = nullptr;

	Super::CommitAbilityEnd();
}

void UNexusAbility_WeaponReload::HandleNotifyBegin(const FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;
	if (NotifyName != Weapon->Reload.AmmoTransferNotifyName) return;

	// OnPlayMontageNotifyBegin fires for any notify on any montage on the bound
	// AnimInstance. Verify our reload montage is still the one playing — another
	// montage with a coincidentally-named "AmmoTransfer" notify shouldn't transfer.
	UAnimInstance* AI = BoundAnimInstance.Get();
	UAnimMontage* Bound = BoundReloadMontage.Get();
	if (!AI || !Bound) return;
	if (!AI->Montage_IsPlaying(Bound)) return;

	TransferAmmo();
}

void UNexusAbility_WeaponReload::TransferAmmo()
{
	if (bAmmoTransferred) return;

	UNexusItemInstance* Instance       = GetActiveInstance();
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Instance || !Weapon) return;

	int32 EffectiveMagSize = Weapon->Ammo.MagazineSize;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		EffectiveMagSize = FMath::FloorToInt(
			Equipped->GetEffectiveStat(NexusGameplayTags::Stat_Weapon_MagazineSize,
				static_cast<float>(Weapon->Ammo.MagazineSize)));
	}

	const int32 CurrentInMag = FMath::RoundToInt(Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0));
	const int32 Needed       = FMath::Max(0, EffectiveMagSize - CurrentInMag);
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