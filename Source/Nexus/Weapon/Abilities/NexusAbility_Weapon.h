#pragma once

#include "CoreMinimal.h"

#include "Nexus/AbilitySystem/NexusAbility.h"

#include "NexusAbility_Weapon.generated.h"

class ANexusEquippedActor;
class INexusEquipmentInterface;
class UNexusEquipmentComponent;
class UNexusItemDefinition;
class UNexusItemInstance;
struct FNexusFragment_Weapon;

namespace NexusWeapon
{
	/**
	 * Read a soft-pointed asset that's supposed to be resident via the Equipped
	 * bundle (sounds, FX, etc.). Null path returns null silently — designer just
	 * didn't author one. Non-null path that isn't resident fires ensureAlwaysMsgf
	 * and falls back to LoadSynchronous so the gameplay still works while the
	 * authoring bug is visible. Mirrors UNexusAssemblyComponent's LoadStream
	 * pattern so the firing path doesn't hitch on every shot.
	 */
	template <typename TAsset>
	TAsset* GetEquippedAsset(const TSoftObjectPtr<TAsset>& Soft,
		const TCHAR* WhatField, const UObject* OwnerForLog)
	{
		if (Soft.IsNull()) return nullptr;
		TAsset* Loaded = Soft.Get();
		if (!Loaded)
		{
			ensureAlwaysMsgf(false,
				TEXT("[Weapon] %s not resident on %s; bundle 'Equipped' was not awaited"),
				WhatField, *GetNameSafe(OwnerForLog));
			Loaded = Soft.LoadSynchronous();
		}
		return Loaded;
	}
}


UCLASS(Abstract, Blueprintable)
class NEXUS_API UNexusAbility_Weapon : public UNexusAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Weapon Ability")
	UNexusEquipmentComponent* GetEquipment() const;

	UFUNCTION(BlueprintPure, Category = "Weapon Ability")
	UNexusItemInstance* GetActiveInstance() const;

	UFUNCTION(BlueprintPure, Category = "Weapon Ability")
	UNexusItemDefinition* GetActiveDefinition() const;

	UFUNCTION(BlueprintPure, Category = "Weapon Ability")
	ANexusEquippedActor* GetEquippedActor() const;

	/** May be nullptr if the active item lacks an FNexusFragment_Weapon. */
	const FNexusFragment_Weapon* GetWeaponFragment() const;

	/**
	 * The owning actor as an equipment host. Weapon montages play through this
	 * (Host->PlayMontage / Host->GetAnimInstance()->Montage_Play) so the same fire
	 * and reload code drives the player's view-space mesh and an NPC's body mesh
	 * alike — no Cast<ACharacter>, no first-person assumptions.
	 */
	INexusEquipmentInterface* GetEquipmentHost() const;

	virtual bool CanActivateAbility_Implementation() const override;
};