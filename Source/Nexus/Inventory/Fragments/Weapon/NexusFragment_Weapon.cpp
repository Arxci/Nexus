#include "NexusFragment_Weapon.h"

#include "Nexus/Weapon/NexusWeaponBehaviorComponent.h"
#include "Nexus/Weapon/Abilities/NexusAbility_WeaponFire.h"
#include "Nexus/Weapon/Abilities/NexusAbility_WeaponReload.h"
#include "Nexus/Weapon/Abilities/NexusAbility_WeaponAim.h"
#include "Nexus/Weapon/Abilities/NexusAbility_WeaponMelee.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusGameplayTags.h"

void FNexusFragment_Weapon::InitializeInstance(UNexusItemInstance* Instance) const
{
	if (!Instance) return;

	// Ranged magazine weapons start with a full magazine (seeded once, persisted thereafter).
	if (bHasRanged && Ranged.Ammo.AmmoModel == ENexusWeaponAmmoModel::Magazine
		&& !Instance->HasStat(NexusGameplayTags::Stat_Ammo_InMagazine))
	{
		Instance->SetStat(NexusGameplayTags::Stat_Ammo_InMagazine, FMath::Max(0, Ranged.Ammo.MagazineSize));
	}

	// Melee weapons that degrade start at full durability (seeded once, persisted thereafter).
	// At zero the weapon breaks — see the melee ability's durability tick.
	if (bHasMelee && Melee.bUsesDurability
		&& !Instance->HasStat(NexusGameplayTags::Stat_Durability))
	{
		Instance->SetStat(NexusGameplayTags::Stat_Durability, FMath::Max(0.0f, Melee.MaxDurability));
	}
}

void FNexusFragment_Weapon::OnInstall(ANexusEquippedActor* EquippedActor) const
{
	if (!EquippedActor) return;

	// Idempotent: if a weapon behavior already exists, don't double-install.
	if (EquippedActor->FindComponentByClass<UNexusWeaponBehaviorComponent>()) return;

	UNexusWeaponBehaviorComponent* Behavior = NewObject<UNexusWeaponBehaviorComponent>(EquippedActor);
	if (!Behavior) return;

	EquippedActor->AddInstanceComponent(Behavior);
	Behavior->RegisterComponent();
	Behavior->OnInstalled(EquippedActor);
}

void FNexusFragment_Weapon::OnUninstall(ANexusEquippedActor* EquippedActor) const
{
	if (!EquippedActor) return;

	if (UNexusWeaponBehaviorComponent* Behavior = EquippedActor->FindComponentByClass<UNexusWeaponBehaviorComponent>())
	{
		Behavior->OnUninstalled();
		Behavior->DestroyComponent();
	}
}

void FNexusFragment_Weapon::GatherGrantedAbilities(TArray<TSubclassOf<UNexusAbility>>& OutAbilities) const
{
	if (bHasRanged)
	{
		TSubclassOf<UNexusAbility> Fire = Ranged.FireAbility;
		if (!Fire) Fire = UNexusAbility_WeaponFire::StaticClass();
		OutAbilities.Add(Fire);

		TSubclassOf<UNexusAbility> Reload = Ranged.ReloadAbility;
		if (!Reload) Reload = UNexusAbility_WeaponReload::StaticClass();
		OutAbilities.Add(Reload);

		TSubclassOf<UNexusAbility> Aim = Ranged.AimAbility;
		if (!Aim) Aim = UNexusAbility_WeaponAim::StaticClass();
		OutAbilities.Add(Aim);
	}

	if (bHasMelee)
	{
		TSubclassOf<UNexusAbility> MeleeSwing = Melee.MeleeAbility;
		if (!MeleeSwing) MeleeSwing = UNexusAbility_WeaponMelee::StaticClass();
		OutAbilities.Add(MeleeSwing);
	}
}

void FNexusFragment_Weapon::SeedStatTags(TMap<FGameplayTag, float>& OutBaseValues) const
{
	// Capability-gated: a melee-only weapon never seeds Stat.Weapon.* (no RPM/spread/mag),
	// a ranged-only weapon never seeds Stat.Melee.*. A both-capable weapon seeds both.
	if (bHasRanged)
	{
		const FWeaponCombat& C  = Ranged.Combat;
		const FWeaponAmmo&   A  = Ranged.Ammo;
		const FWeaponReload& Rl = Ranged.Reload;

		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_Damage,         C.BaseDamage);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_RPM,            C.RoundsPerMinute);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_MaxRange,       C.MaxRange);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_SpreadHip,      C.SpreadConeDegrees.X);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_SpreadADS,      C.SpreadConeDegrees.Y);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_MagazineSize,   A.MagazineSize);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_ReloadDuration, Rl.ReloadDuration);

		// Recoil + ADS time base from the combat spec; a muzzle brake (-recoil), a quick-aim
		// stock (-ADS time) or a merchant tune-up folds in on top.
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_RecoilVertical,   C.RecoilVertical);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_RecoilHorizontal, C.RecoilHorizontal);
		OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_ADSTime,          C.ADSTime);
	}

	if (bHasMelee)
	{
		OutBaseValues.Add(NexusGameplayTags::Stat_Melee_Damage,      Melee.BaseDamage);
		OutBaseValues.Add(NexusGameplayTags::Stat_Melee_Range,       Melee.Range);
		OutBaseValues.Add(NexusGameplayTags::Stat_Melee_SwingRate,   Melee.SwingsPerMinute);
		OutBaseValues.Add(NexusGameplayTags::Stat_Melee_StaminaCost, Melee.StaminaCost);
		OutBaseValues.Add(NexusGameplayTags::Stat_Melee_Knockback,   Melee.KnockbackImpulse);
	}
}

void FNexusFragment_Weapon::SeedStatClamps(TMap<FGameplayTag, FVector2D>& OutClamps) const
{
	for (const FNexusStatClamp& Clamp : StatClamps)
	{
		if (!Clamp.StatTag.IsValid()) continue;
		// Last writer wins if two entries target the same key — authoring slip,
		// but deterministic. (Min, Max); the assembly ignores Max <= Min.
		OutClamps.Add(Clamp.StatTag, FVector2D(Clamp.Min, Clamp.Max));
	}
}