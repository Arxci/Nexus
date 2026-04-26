// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NexusEquippedActor.generated.h"

class UNexusItemInstance;
class USkeletalMeshComponent;

/**
 * Visible 3D representation of an equipped item, attached to the owning
 * character's mesh. Pure presentation — no game state lives here.
 *
 * Subclass for custom FX hooks (muzzle sockets, shell ejection, light cones).
 * The default actor is sufficient for any simple equippable.
 */
UCLASS(Blueprintable)
class NEXUS_API ANexusEquippedActor : public AActor
{
	GENERATED_BODY()

public:
	ANexusEquippedActor();

	/** Called by EquipmentComponent immediately after Spawn + Attach. */
	virtual void InitializeFromInstance(UNexusItemInstance* Instance);

	UFUNCTION(BlueprintPure, Category = "Equipped")
	UNexusItemInstance* GetSourceInstance() const { return SourceInstance; }

	UFUNCTION(BlueprintPure, Category = "Equipped")
	USkeletalMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintPure, Category = "Equipped")
	FTransform GetSocketTransform(FName SocketName) const;

	/** Hard refs to the active weapon's presentation assets, paged in on equip
 *  so the fire ability never sync-loads on the hot path. */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped|Weapon")
	TObjectPtr<USoundBase> CachedFireSound;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped|Weapon")
	TObjectPtr<USoundBase> CachedDryFireSound;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped|Weapon")
	TObjectPtr<USoundBase> CachedReloadSound;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped|Weapon")
	TObjectPtr<class UFXSystemAsset> CachedMuzzleFlash;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped|Weapon")
	TObjectPtr<class UFXSystemAsset> CachedImpactFX;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped|Weapon")
	TObjectPtr<class UAnimMontage> CachedFireMontage;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<UNexusItemInstance> SourceInstance;

	/** BP-only hook for FX/audio after init (e.g. light cone setup, hover anim). */
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipped",
		meta = (DisplayName = "On Initialized From Instance"))
	void K2_OnInitializedFromInstance();
};