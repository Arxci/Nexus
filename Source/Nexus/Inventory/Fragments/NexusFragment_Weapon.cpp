// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusFragment_Weapon.h"

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