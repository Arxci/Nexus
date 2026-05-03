#pragma once

#include "CoreMinimal.h"

#include "Nexus/AbilitySystem/NexusAbility.h"

#include "NexusAbility_Weapon.generated.h"

class ANexusEquippedActor;
class UNexusEquipmentComponent;
class UNexusItemDefinition;
class UNexusItemInstance;
struct FNexusFragment_Weapon;


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