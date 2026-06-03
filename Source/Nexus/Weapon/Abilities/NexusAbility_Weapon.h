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


/** Attacker-side hit confirmation: how many receivers a shot / swing damaged, and the union of branch tags. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponHitConfirmed, int32, ReceiversHit, const FGameplayTagContainer&, ContextTags);

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

	/**
	 * Fires on the attacker side when a shot / swing damages one or more receivers,
	 * carrying the union of branch tags (Critical / Headshot / Stagger). A HUD subscribes
	 * (via the granted ability) for the hit-marker and weak-point cue, without any system
	 * reaching into the damaged actor's health.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Weapon Ability")
	FOnWeaponHitConfirmed OnHitConfirmed;

protected:
	/** Broadcast OnHitConfirmed when ReceiversHit > 0. Shared by Fire and Melee. Const — the
	 *  dynamic delegate's Broadcast is const, and Fire's hit path is a const method. */
	void BroadcastHitConfirmed(int32 ReceiversHit, const FGameplayTagContainer& ContextTags) const;

	/**
	 * Reserve ammo for the active weapon's ammo identity (FWeaponAmmo::AmmoIdentityTag),
	 * summed across the wielder's inventory via the public inventory query API. Shared by
	 * Reload (magazine refill) and Fire (pooled-model consumption). 0 when there is no
	 * inventory or no identity tag.
	 */
	int32 GetReserveAmmo() const;

	/** Remove up to Amount of the active weapon's ammo identity from inventory; returns the amount actually removed. */
	int32 ConsumeReserveAmmo(int32 Amount) const;

	/**
	 * Host-agnostic aim ray: the controller viewpoint (player camera via the camera
	 * manager, or an AI controller's eyes), with an owner-eyes fallback for an
	 * uncontrolled host. Shared by Fire (trace / projectile origin) and Melee (sweep
	 * direction) — no player-camera utility, no first-person assumption.
	 */
	void ResolveAimRay(FVector& OutLocation, FRotator& OutRotation) const;

private:
	/**
	 * Cached equipment-component handle. The ability's owner is fixed for its lifetime, so
	 * the component never moves; caching it keeps the hot fire / melee paths from re-running
	 * FindComponentByClass on every accessor call (GetActiveInstance / GetActiveDefinition /
	 * GetEquippedActor / GetWeaponFragment all route through GetEquipment). Weak so a
	 * torn-down component is transparently re-resolved; mutable so the const accessors fill it.
	 */
	mutable TWeakObjectPtr<UNexusEquipmentComponent> CachedEquipment;
};