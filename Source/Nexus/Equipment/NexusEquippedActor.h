#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "NexusEquippedActor.generated.h"

class UNexusItemInstance;
class USkeletalMeshComponent;


UCLASS(Blueprintable)
class NEXUS_API ANexusEquippedActor : public AActor
{
	GENERATED_BODY()

public:
	ANexusEquippedActor();
	
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
	
	UFUNCTION(BlueprintCallable, Category = "Equipped")
	void ApplyOwnerViewpointRendering();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimSequence> IdlePose;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimSequence> IdleLoop;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimSequence> RunLoop;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimMontage> UnequipMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimMontage> InspectMontage;

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