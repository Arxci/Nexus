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