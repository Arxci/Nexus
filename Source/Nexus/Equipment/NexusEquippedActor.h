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