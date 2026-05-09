#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Nexus/Equipment/Attachments/NexusWeaponAssemblyComponent.h"

#include "NexusEquippedActor.generated.h"

class UAnimMontage;
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


	// Weapon-mesh animation. The weapon mesh has its own AnimInstance running
	// the AnimBP authored on the equippable definition; arms-side notifies
	// (UNexusAnimNotify_WeaponAction) call PlayWeaponAction so the gun's
	// slide/bolt/magazine animate in lockstep with the player's reload/fire/etc.
	UFUNCTION(BlueprintCallable, Category = "Equipped|Anim")
	UAnimMontage* PlayWeaponAction(FGameplayTag ActionTag);

	UFUNCTION(BlueprintPure, Category = "Equipped|Anim")
	UAnimMontage* GetWeaponActionMontage(FGameplayTag ActionTag) const;

	// Effective stat / montage helpers. Read through the assembly so attachment
	// modifiers and overrides are applied; fall back to the weapon fragment
	// (or the equippable's WeaponActionMontages) when no assembly is present.
	UFUNCTION(BlueprintPure, Category = "Equipped|Stats")
	float GetEffectiveStat(FGameplayTag StatTag, float Default = 0.0f) const;

	UFUNCTION(BlueprintPure, Category = "Equipped|Stats")
	FResolvedWeaponStats GetResolvedStats() const;

	UFUNCTION(BlueprintPure, Category = "Equipped|Anim")
	UAnimMontage* GetEffectiveActionMontage(FGameplayTag ActionTag) const;

	UFUNCTION(BlueprintPure, Category = "Equipped|Assembly")
	UNexusWeaponAssemblyComponent* GetAssembly() const { return Assembly; }

public:
	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimSequence> IdlePose;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimSequence> IdleLoop;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimSequence> RunLoop;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimMontage> UnholsterMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimMontage> HolsterMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
	TObjectPtr<UAnimMontage> InspectMontage;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<UNexusWeaponAssemblyComponent> Assembly;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<UNexusItemInstance> SourceInstance;

	/**
	 * Resolved arms-side action montages cached at init from the equippable
	 * fragment (FEquippableAnimationSet::WeaponActionMontages). Keyed by
	 * Action.Weapon.* tag.
	 */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipment|Anims")
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> WeaponActionMontages;

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