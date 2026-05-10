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

	/**
	 * Apply the actor's currently-resolved viewpoint state (cast-shadow,
	 * first-person primitive type) to a single mesh. Called from both
	 * ApplyOwnerViewpointRendering and from the assembly component when a
	 * new attachment mesh is spawned, so attachments don't miss the
	 * initial viewpoint pass.
	 */
	void ApplyViewpointToMesh(USkeletalMeshComponent* TargetMesh) const;

	UFUNCTION(BlueprintPure, Category = "Equipped")
	bool IsRenderedFirstPerson() const { return bIsFirstPersonView; }


	/**
	 * Generic action-montage entry point. Resolves the right montage by:
	 *   1. Asking the assembly (so attachment overrides win), and
	 *   2. Falling back to each installed UNexusEquippedActorBehavior in
	 *      registration order.
	 *
	 * The actor doesn't know about Action.Weapon.* vs. future Action.Flashlight.*
	 * vs. anything else — fragments install the behavior that owns those
	 * action montages, and the actor just relays.
	 *
	 * Called by UNexusAnimNotify_WeaponAction so an arms montage can drive the
	 * equipped mesh's slide/bolt/magazine animations in lockstep.
	 */
	UFUNCTION(BlueprintCallable, Category = "Equipped|Anim")
	UAnimMontage* PlayActionMontage(FGameplayTag ActionTag);

	UFUNCTION(BlueprintPure, Category = "Equipped|Anim")
	UAnimMontage* GetEffectiveActionMontage(FGameplayTag ActionTag) const;

	// Effective stat helpers. Read through the assembly so attachment modifiers apply.
	UFUNCTION(BlueprintPure, Category = "Equipped|Stats")
	float GetEffectiveStat(FGameplayTag StatTag, float Default = 0.0f) const;

	UFUNCTION(BlueprintPure, Category = "Equipped|Stats")
	FResolvedWeaponStats GetResolvedStats() const;

	UFUNCTION(BlueprintPure, Category = "Equipped|Assembly")
	UNexusWeaponAssemblyComponent* GetAssembly() const { return Assembly; }

public:
	/**
	 * Generic equipment-side anim cache, populated from FNexusFragment_Equippable::Animations
	 * at InitializeFromInstance. These apply to any equipment type (a flashlight
	 * has an unholster, a radio has an inspect) — kept on the actor so the
	 * equipment component can read swap timing without walking fragments.
	 *
	 * Weapon-specific action montages (Action.Weapon.*) are NOT here; they live
	 * on UNexusWeaponBehaviorComponent and route through PlayActionMontage.
	 */
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<UNexusWeaponAssemblyComponent> Assembly;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<UNexusItemInstance> SourceInstance;

	UPROPERTY(Transient)
	bool bVisible = true;

	UPROPERTY(Transient)
	bool bIsFirstPersonView = false;

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