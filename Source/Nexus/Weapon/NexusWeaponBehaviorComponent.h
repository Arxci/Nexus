#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Nexus/Equipment/NexusEquippedActorBehavior.h"

#include "NexusWeaponBehaviorComponent.generated.h"

class UNexusItemInstance;
class UStaticMeshComponent;
struct FNexusFragment_Weapon;


/**
 * Actor-side behavior installed by FNexusFragment_Weapon::OnInstall. Owns the
 * weapon's non-animation runtime state:
 *
 *   - The transient "chambered round" UStaticMeshComponent. ...
 *   - Magazine ammo visual swap. ...
 *
 * Action montages (Fire / Reload / Inspect / etc.) are NOT owned here — they
 * live on FEquippableAnimationSet::Actions and resolve through the assembly.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusWeaponBehaviorComponent : public UNexusEquippedActorBehavior
{
	GENERATED_BODY()

public:
	UNexusWeaponBehaviorComponent();

	virtual void OnInstalled(ANexusEquippedActor* InEquippedActor) override;
	virtual void OnUninstalled() override;

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

	void RefreshMagazineVisual();
	void SpawnChamberRoundMesh(const FNexusFragment_Weapon& WeaponFragment);

	const FNexusFragment_Weapon* GetWeaponFragment() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<UStaticMeshComponent> ChamberRoundMesh;

	int32 LastInMagazine = -1;
	bool bSubscribedToInstance = false;
};