#include "NexusAbility_Weapon.h"

#include "GameFramework/Controller.h"

#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Equipment/NexusEquipmentInterface.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"

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

INexusEquipmentInterface* UNexusAbility_Weapon::GetEquipmentHost() const
{
	return Cast<INexusEquipmentInterface>(GetOwner());
}

bool UNexusAbility_Weapon::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;
	return GetActiveInstance() != nullptr;
}

int32 UNexusAbility_Weapon::GetReserveAmmo() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	const AActor* Owner = GetOwner();
	if (!Weapon || !Owner || !Weapon->Ranged.Ammo.AmmoIdentityTag.IsValid()) return 0;

	if (const UNexusInventoryComponent* Inventory = Owner->FindComponentByClass<UNexusInventoryComponent>())
	{
		return Inventory->GetTotalCountForIdentityTag(Weapon->Ranged.Ammo.AmmoIdentityTag);
	}
	return 0;
}

void UNexusAbility_Weapon::BroadcastHitConfirmed(int32 ReceiversHit, const FGameplayTagContainer& ContextTags) const
{
	if (ReceiversHit > 0)
	{
		OnHitConfirmed.Broadcast(ReceiversHit, ContextTags);
	}
}

void UNexusAbility_Weapon::ResolveAimRay(FVector& OutLocation, FRotator& OutRotation) const
{
	// Controller viewpoint is host-agnostic: a player controller routes through the camera
	// manager, an AI controller falls back to the pawn's eyes.
	if (const AController* Ctrl = GetController())
	{
		Ctrl->GetPlayerViewPoint(OutLocation, OutRotation);
	}
	else if (const AActor* Owner = GetOwner())
	{
		OutLocation = Owner->GetActorLocation() + FVector(0, 0, 60.0f);
		OutRotation = Owner->GetActorRotation();
	}
}

int32 UNexusAbility_Weapon::ConsumeReserveAmmo(const int32 Amount) const
{
	if (Amount <= 0) return 0;

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	const AActor* Owner = GetOwner();
	if (!Weapon || !Owner || !Weapon->Ranged.Ammo.AmmoIdentityTag.IsValid()) return 0;

	UNexusInventoryComponent* Inventory = Owner->FindComponentByClass<UNexusInventoryComponent>();
	if (!Inventory) return 0;

	int32 Remaining = Amount;
	TArray<UNexusItemInstance*> Snapshot = Inventory->GetItems();
	for (UNexusItemInstance* Inst : Snapshot)
	{
		if (Remaining <= 0) break;
		if (!Inst) continue;
		if (!Inst->GetIdentityTag().MatchesTagExact(Weapon->Ranged.Ammo.AmmoIdentityTag)) continue;

		const int32 Taken = Inventory->RemoveFromInstance(Inst, Remaining);
		Remaining -= Taken;
	}
	return Amount - Remaining;
}