// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusWeaponEquippedActor.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/NexusFragment_Weapon.h"

void ANexusWeaponEquippedActor::InitializeFromInstance(UNexusItemInstance* Instance)
{
	Super::InitializeFromInstance(Instance);
	if (!Instance) return;

	const UNexusItemDefinition* Def = Instance->GetDefinition();
	if (!Def) return;

	if (const FNexusFragment_Weapon* W = Def->FindFragment<FNexusFragment_Weapon>())
	{
		CachedFireSound      = W->Presentation.FireSound.LoadSynchronous();
		CachedDryFireSound   = W->Presentation.DryFireSound.LoadSynchronous();
		CachedReloadSound    = W->Presentation.ReloadSound.LoadSynchronous();
		CachedMuzzleFlash    = W->Presentation.MuzzleFlash.LoadSynchronous();
		CachedImpactFX       = W->Presentation.ImpactFX.LoadSynchronous();
		CachedFireMontage    = W->Animations.FireMontage.LoadSynchronous();
		CachedDryFireMontage = W->Animations.DryFireMontage.LoadSynchronous();
		CachedReloadMontage  = W->Animations.ReloadMontage.LoadSynchronous();
	}
}