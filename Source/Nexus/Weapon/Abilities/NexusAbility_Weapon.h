// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "NexusAbility_Weapon.generated.h"

class ANexusEquippedActor;
class UNexusEquipmentComponent;
class UNexusItemDefinition;
class UNexusItemInstance;
struct FNexusFragment_Weapon;

/**
 * Shared base for any ability granted by an equipped weapon (Fire, Reload, Aim,
 * Melee, Inspect). Resolves its weapon context from the active equipment slot
 * each call so abilities don't need to cache it across equip/unequip events.
 *
 * Note: this is abstract. Concrete fire/reload/aim subclasses are added in the
 * next slice; the base is shipped now so weapon definitions can compile and
 * reference it from FNexusFragment_Equippable::GrantedAbilities.
 */
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

	virtual bool CanActivateAbility_Implementation() const override;
};