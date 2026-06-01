#include "NexusFragment_Weapon.h"

#include "Nexus/Weapon/NexusWeaponBehaviorComponent.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusGameplayTags.h"

void FNexusFragment_Weapon::InitializeInstance(UNexusItemInstance* Instance) const
{
	if (!Instance) return;
	if (Ammo.AmmoModel != ENexusWeaponAmmoModel::Magazine) return;

	if (!Instance->HasStat(NexusGameplayTags::Stat_Ammo_InMagazine))
	{
		Instance->SetStat(NexusGameplayTags::Stat_Ammo_InMagazine, FMath::Max(0, Ammo.MagazineSize));
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

void FNexusFragment_Weapon::SeedStatTags(TMap<FGameplayTag, float>& OutBaseValues) const
{
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_Damage,         Combat.BaseDamage);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_RPM,            Combat.RoundsPerMinute);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_MaxRange,       Combat.MaxRange);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_SpreadHip,      Combat.SpreadConeDegrees.X);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_SpreadADS,      Combat.SpreadConeDegrees.Y);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_MagazineSize,   Ammo.MagazineSize);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_ReloadDuration, Reload.ReloadDuration);

	// Neutral defaults — not authored on FWeaponCombat yet, but seeded so
	// attachments can meaningfully modify them (a muzzle brake adds -recoil,
	// a fixed-stock removes ADS-time, etc).
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_RecoilVertical,   0.0f);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_RecoilHorizontal, 0.0f);
	OutBaseValues.Add(NexusGameplayTags::Stat_Weapon_ADSTime,          0.0f);
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