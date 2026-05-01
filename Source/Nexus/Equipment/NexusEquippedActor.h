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
 * The default rendering setup is third-person (cast shadows, default primitive
 * type) so AI-held weapons look correct out of the box. Equipment calls
 * ApplyOwnerViewpointRendering() post-spawn to flip into first-person mode
 * for the local player.
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
	FTransform GetSocketTransform(const FName SocketName) const;

	UFUNCTION(BlueprintCallable, Category = "Equipped")
	void SetEquippedVisibility(bool bNewVisible);

	UFUNCTION(BlueprintPure, Category = "Equipped")
	bool IsEquippedVisible() const { return bVisible; }

	/**
	 * Configure rendering based on who's holding the item:
	 *   - Local player pawn → first-person primitive type, no shadow casting
	 *     (avoids the FP weapon casting visible "ghost arm" shadows on walls).
	 *   - Anyone else (AI, remote) → default primitive type, shadows on
	 *     (silhouette on the wall is how the player spots a threat at distance).
	 *
	 * Equipment calls this once after spawn. Safe to call again on possession
	 * change — supports future camera-swap or POV-switching mechanics without
	 * touching Equipment.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipped")
	void ApplyOwnerViewpointRendering();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<UNexusItemInstance> SourceInstance;

	UPROPERTY(Transient)
	bool bVisible = true;

	/** BP-only hook for FX/audio after init (e.g. light cone setup, hover anim). */
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipped",
		meta = (DisplayName = "On Initialized From Instance"))
	void K2_OnInitializedFromInstance();

	/** BP hook so subclasses can toggle weapon-specific FX (laser sights, lights). */
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipped",
		meta = (DisplayName = "On Equipped Visibility Changed"))
	void K2_OnEquippedVisibilityChanged(bool bNewVisible);

	/**
	 * BP hook fired right after the C++ rendering toggle. Subclasses use this
	 * to toggle their own per-viewpoint visuals (e.g. swap muzzle FX scale).
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Equipped",
		meta = (DisplayName = "On Owner Viewpoint Applied"))
	void K2_OnOwnerViewpointApplied(bool bIsFirstPerson);
};