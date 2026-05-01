// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Particles/ParticleSystem.h"
#include "NexusWeaponEquippedActor.generated.h"

class UAnimMontage;
class USoundBase;

/**
 * Equipped-actor specialization for weapons. Pages in the weapon's
 * presentation soft refs (sounds, FX, fire montage) at equip time so the
 * fire/reload abilities can read hard pointers without sync-loading on the
 * hot path.
 *
 * Set FNexusFragment_Equippable::EquippedActorClass to a subclass of this
 * (or this class itself) on weapon item definitions.
 */
UCLASS(Blueprintable)
class NEXUS_API ANexusWeaponEquippedActor : public ANexusEquippedActor
{
	GENERATED_BODY()

public:
	virtual void InitializeFromInstance(UNexusItemInstance* Instance) override;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<USoundBase> CachedFireSound;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<USoundBase> CachedDryFireSound;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<USoundBase> CachedReloadSound;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UFXSystemAsset> CachedMuzzleFlash;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UFXSystemAsset> CachedImpactFX;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> CachedFireMontage;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> CachedDryFireMontage;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UAnimMontage> CachedReloadMontage;
};