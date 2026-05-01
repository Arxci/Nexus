// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Particles/ParticleSystem.h"
#include "NexusWeaponEquippedActor.generated.h"

class UAnimMontage;
class USoundBase;


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