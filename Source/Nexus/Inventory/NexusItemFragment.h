// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "NexusItemFragment.generated.h"

class ANexusEquippedActor;
class UNexusItemDefinition;
class UNexusItemInstance;


/**
 * Authored hard bound for one resolved stat, applied by UNexusAssemblyComponent
 * after the (base + ΣAdd) × ΠMul attachment fold and the persistent-upgrade
 * additive tier. Min/Max are inclusive. An entry whose Max <= Min is treated as
 * "unbounded" (the neutral default), so adding an empty row never silently pins a
 * stat to zero. Fragments contribute these for the keys they own via
 * SeedStatClamps, keeping the assembly agnostic of which fragment authored a bound.
 */
USTRUCT(BlueprintType, DisplayName = "Stat Clamp")
struct NEXUS_API FNexusStatClamp
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Stat"))
	FGameplayTag StatTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Min = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Max = 0.0f;
};


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

	/**
	 * Contribute per-stat clamp bounds (StatTag -> (Min, Max)) for the keys this
	 * fragment owns. UNexusAssemblyComponent applies them as the final step of the
	 * effective-stat resolution — after base, attachment modifiers, and persistent
	 * upgrades — so a stacked attachment + max-tier upgrade can't push a stat past
	 * its authored ceiling (or below its floor). Mirrors SeedStatTags; the assembly
	 * never type-checks the fragment.
	 */
	virtual void SeedStatClamps(TMap<FGameplayTag, FVector2D>& OutClamps) const {}
};