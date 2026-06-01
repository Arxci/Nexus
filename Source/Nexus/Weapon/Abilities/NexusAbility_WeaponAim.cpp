#include "NexusAbility_WeaponAim.h"

#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/Fragments/Weapon/NexusFragment_Weapon.h"
#include "Nexus/NexusGameplayTags.h"

UNexusAbility_WeaponAim::UNexusAbility_WeaponAim()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Weapon_Aim);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Aiming);
	// Can't begin aiming mid weapon-swap. Firing / reloading do NOT block aim — you aim
	// through them (criterion 9: aim must not block Fire, and vice versa).
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	bCooldownOnActivation   = false;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponAim::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	return Weapon && Weapon->bHasRanged; // aim is a ranged-capability verb
}

bool UNexusAbility_WeaponAim::RequestActivateAbility()
{
	if (!Super::RequestActivateAbility()) return false;
	CommitAbility();
	return true;
}

bool UNexusAbility_WeaponAim::RequestDeactivateAbility(bool bForce)
{
	if (!bForce && !IsActive()) return false;
	CommitAbilityEnd();
	return true;
}

void UNexusAbility_WeaponAim::CommitAbility()
{
	Super::CommitAbility(); // Active + applies the Aiming owned tag

	// Start the ADS ramp from hip; an instant-aim weapon (ADSTime 0) snaps to full.
	SetAimAlpha(GetADSTime() > 0.0f ? 0.0f : 1.0f);
}

void UNexusAbility_WeaponAim::CommitAbilityEnd()
{
	Super::CommitAbilityEnd(); // removes the Aiming owned tag
	SetAimAlpha(0.0f);
}

bool UNexusAbility_WeaponAim::CanTick()
{
	// Only tick while ramping up; once fully aimed there's nothing to advance.
	return IsActive() && AimAlpha < 1.0f;
}

void UNexusAbility_WeaponAim::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);
	if (!IsActive()) return;

	const float Ads = GetADSTime();
	if (Ads <= 0.0f)
	{
		SetAimAlpha(1.0f);
		return;
	}
	SetAimAlpha(FMath::Min(1.0f, AimAlpha + DeltaTime / Ads));
}

float UNexusAbility_WeaponAim::GetADSTime() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return 0.0f;

	float Ads = Weapon->Ranged.Combat.ADSTime;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		Ads = Equipped->GetEffectiveStat(NexusGameplayTags::Stat_Weapon_ADSTime, Ads);
	}
	return FMath::Max(0.0f, Ads);
}

void UNexusAbility_WeaponAim::SetAimAlpha(float NewAlpha)
{
	NewAlpha = FMath::Clamp(NewAlpha, 0.0f, 1.0f);
	if (NewAlpha == AimAlpha) return;
	AimAlpha = NewAlpha;
	OnAimProgress.Broadcast(AimAlpha);
}

void UNexusAbility_WeaponAim::OnSaveStateRestored()
{
	Super::OnSaveStateRestored();

	// Aim is a held state — restore to hip; the player re-presses to aim. Mirrors the
	// hero's hold-input flush for run / crouch on load.
	if (IsActive())
	{
		ForceEndAbility();
	}
	SetAimAlpha(0.0f);
}
