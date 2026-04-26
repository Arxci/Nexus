// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusFragment_Weapon.h"

#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusGameplayTags.h"

void FNexusFragment_Weapon::InitializeInstance(UNexusItemInstance* Instance) const
{
	if (!Instance) return;
	if (AmmoModel != ENexusWeaponAmmoModel::Magazine) return;

	// Only seed if the pickup didn't pre-author a value (e.g. half-empty crate).
	if (!Instance->HasStat(NexusGameplayTags::Stat_Ammo_InMagazine))
	{
		Instance->SetStat(NexusGameplayTags::Stat_Ammo_InMagazine, FMath::Max(0, MagazineSize));
	}
}