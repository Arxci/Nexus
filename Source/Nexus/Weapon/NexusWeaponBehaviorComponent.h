#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Equipment/NexusEquippedActorBehavior.h"

#include "NexusWeaponBehaviorComponent.generated.h"

class UAnimMontage;
class UNexusItemInstance;
class UStaticMeshComponent;
struct FNexusFragment_Weapon;


/**
 * Actor-side behavior installed by FNexusFragment_Weapon::OnInstall. Owns the
 * weapon's per-equipped-actor runtime state:
 *
 *   - Cached arms-side -> weapon-mesh action montages (Action.Weapon.*),
 *     populated from FNexusFragment_Weapon::Animations::ActionMontages and
 *     served via GetActionMontage so ANexusEquippedActor::PlayActionMontage
 *     stays generic across equipment types.
 *
 *   - The transient "chambered round" UStaticMeshComponent. Authored once on
 *     install, attached to the gun's ammo socket, hidden by default.
 *     UNexusAnimNotifyState_ShowChamberRound toggles SetChamberRoundVisible
 *     on/off across the chamber window of the unholster/reload montage; the
 *     mesh's transform is driven by the ammo bone via the socket attachment,
 *     mirroring the sequencer authoring path.
 *
 *   - Magazine ammo visual swap. Subscribes to UNexusItemInstance::OnInstanceChanged;
 *     on Stat.Ammo.InMagazine transition across zero, finds the attached
 *     magazine via the assembly (any attachment carrying
 *     FNexusAttachmentFragment_Magazine — slot-tag-agnostic so a weapon with
 *     two mag slots still works), and SetSkeletalMesh()'s its mesh component
 *     to the loaded or empty variant. Leader Pose persists across the swap.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusWeaponBehaviorComponent : public UNexusEquippedActorBehavior
{
	GENERATED_BODY()

public:
	UNexusWeaponBehaviorComponent();

	virtual void OnInstalled(ANexusEquippedActor* InEquippedActor) override;
	virtual void OnUninstalled() override;
	virtual UAnimMontage* GetActionMontage(FGameplayTag ActionTag) const override;

	/**
	 * Toggle the chambered-round visual. Driven by
	 * UNexusAnimNotifyState_ShowChamberRound across the chamber window of an
	 * arms-side montage.
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon|Behavior")
	void SetChamberRoundVisible(bool bVisible);

	UFUNCTION(BlueprintPure, Category = "Weapon|Behavior")
	UStaticMeshComponent* GetChamberRoundMesh() const { return ChamberRoundMesh; }

	virtual void ApplyViewpoint(bool bIsFirstPerson) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void HandleInstanceChanged(UNexusItemInstance* Instance);

	UFUNCTION()
	void HandleAssemblyChanged();

	/**
	 * Reapply the magazine's loaded/empty mesh based on the current
	 * Stat.Ammo.InMagazine value. Safe to call when no magazine attachment is
	 * installed — it's a no-op in that case.
	 */
	void RefreshMagazineVisual();

	void CacheActionMontages(const FNexusFragment_Weapon& WeaponFragment);
	void SpawnChamberRoundMesh(const FNexusFragment_Weapon& WeaponFragment);

	const FNexusFragment_Weapon* GetWeaponFragment() const;

private:
	/** Resolved arms-side -> weapon-mesh montages, keyed by Action.Weapon.* tag. */
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> ActionMontages;

	/**
	 * Transient round shown during the chamber portion of an unholster/reload
	 * montage. Static mesh; world transform driven by the gun's ammo bone via
	 * a socket attachment, identical to the sequencer authoring path.
	 */
	UPROPERTY(Transient)
	TObjectPtr<UStaticMeshComponent> ChamberRoundMesh;

	/**
	 * Last observed Stat.Ammo.InMagazine, used to detect transitions across
	 * zero so we don't redundantly call SetSkeletalMesh on every stat change.
	 * Sentinel -1 means "no observation yet — force an apply on first refresh."
	 */
	int32 LastInMagazine = -1;

	bool bSubscribedToInstance = false;
};