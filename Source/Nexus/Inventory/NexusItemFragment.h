// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "NexusItemFragment.generated.h"

class ANexusEquippedActor;
class UNexusItemDefinition;
class UNexusItemInstance;


USTRUCT(BlueprintType, meta = (Hidden))
struct NEXUS_API FNexusItemFragment
{
	GENERATED_BODY()

	virtual ~FNexusItemFragment() = default;

	virtual void InitializeInstance(UNexusItemInstance* Instance) const {}

	/**
	 * Called once on the spawned ANexusEquippedActor right after its mesh and
	 * generic equippable anim cache have been populated, before
	 * UNexusAssemblyComponent::RebuildFromInstance. Fragments use this
	 * hook to install actor-side behavior components (e.g. the weapon fragment
	 * adds a UNexusWeaponBehaviorComponent), so the equipped actor stays a
	 * generic shell — no subclassing, no fragment-type checks in the actor.
	 */
	virtual void OnInstall(ANexusEquippedActor* EquippedActor) const {}

	/**
	 * Mirror of OnInstall for teardown. Called from the equipped actor's
	 * EndPlay so behaviors get a clean uninstall path even if the actor is
	 * destroyed mid-life (e.g. owner death, save load).
	 */
	virtual void OnUninstall(ANexusEquippedActor* EquippedActor) const {}

	/**
	 * Contribute this fragment's base stat values into the assembly's
	 * stat-resolution map. Called by UNexusAssemblyComponent during its cache
	 * rebuild, before attachment Add/Mul modifiers are folded in. Each fragment
	 * seeds the keys it owns — the weapon fragment seeds Stat.Weapon.*, a
	 * future flashlight fragment could seed Stat.Flashlight.*, etc.
	 *
	 * Keeps the assembly agnostic of fragment type: it never type-checks
	 * fragments, never reaches into FNexusFragment_Weapon directly.
	 */
	virtual void SeedStatTags(TMap<FGameplayTag, float>& OutBaseValues) const {}
};