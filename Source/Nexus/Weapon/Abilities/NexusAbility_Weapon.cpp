#include "NexusAbility_Weapon.h"

#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Weapon/NexusFragment_Weapon.h"

UNexusEquipmentComponent* UNexusAbility_Weapon::GetEquipment() const
{
	const AActor* Owner = GetOwner();
	return Owner ? Owner->FindComponentByClass<UNexusEquipmentComponent>() : nullptr;
}

UNexusItemInstance* UNexusAbility_Weapon::GetActiveInstance() const
{
	const UNexusEquipmentComponent* Equipment = GetEquipment();
	return Equipment ? Equipment->GetActiveInstance() : nullptr;
}

UNexusItemDefinition* UNexusAbility_Weapon::GetActiveDefinition() const
{
	const UNexusItemInstance* Instance = GetActiveInstance();
	return Instance ? Instance->GetDefinition() : nullptr;
}

ANexusEquippedActor* UNexusAbility_Weapon::GetEquippedActor() const
{
	const UNexusEquipmentComponent* Equipment = GetEquipment();
	return Equipment ? Equipment->GetEquippedActorInSlot(Equipment->GetActiveSlot()) : nullptr;
}

const FNexusFragment_Weapon* UNexusAbility_Weapon::GetWeaponFragment() const
{
	const UNexusItemDefinition* Def = GetActiveDefinition();
	return Def ? Def->FindFragment<FNexusFragment_Weapon>() : nullptr;
}

bool UNexusAbility_Weapon::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;
	return GetActiveInstance() != nullptr;
}