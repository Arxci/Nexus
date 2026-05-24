#include "NexusInventoryAcquireLibrary.h"

#include "Engine/World.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Combat/NexusHealthComponent.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/NexusItemPickup.h"
#include "Nexus/Inventory/Fragments/Consumable/NexusFragment_Consumable.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "Nexus/NexusGameplayTags.h"

FNexusAcquireResult UNexusInventoryAcquireLibrary::AcquireItem(
	APawn* Recipient,
	UNexusItemDefinition* Definition,
	const int32 Count,
	const FNexusAcquireParams& Params)
{
	FNexusAcquireResult Result;
	if (!Recipient || !Definition || Count <= 0)
	{
		Result.Remainder = FMath::Max(0, Count);
		return Result;
	}

	UNexusInventoryComponent* Inventory = Recipient->FindComponentByClass<UNexusInventoryComponent>();
	if (!Inventory)
	{
		Result.Remainder = Count;
		return Result;
	}

	// First-acquire is determined *before* AddItem so that MarkItemDefinitionSeen
	// doesn't mask it. A first-pickup ceremony only fires once per save per def.
	Result.bWasFirstAcquire = !Inventory->HasSeenItemDefinition(Definition);

	const FNexusAddItemResult AddResult = Inventory->AddItem(Definition, Count);
	Result.AmountAdded = AddResult.AmountAdded;
	Result.Remainder   = AddResult.Remainder;
	Result.NewInstances = AddResult.NewInstances;

	if (AddResult.AmountAdded <= 0) return Result;

	// Apply caller-provided initial stat tags to brand-new instances. Stacked-into
	// existing instances aren't touched — those carry whatever stats they already
	// had, which is also why stack merging refuses instances with stat tags.
	if (Params.InitialStatTags.Num() > 0)
	{
		for (UNexusItemInstance* New : AddResult.NewInstances)
		{
			if (!New) continue;
			for (const TPair<FGameplayTag, int32>& Pair : Params.InitialStatTags)
			{
				New->SetStat(Pair.Key, Pair.Value);
			}
		}
	}

	Inventory->MarkItemDefinitionSeen(Definition);

	if (!Params.bAutoEquipIfPossible) return Result;

	UNexusEquipmentComponent* Equipment = Recipient->FindComponentByClass<UNexusEquipmentComponent>();
	if (!Equipment) return Result;

	// Pick the action tag for the draw phase. First-acquire uses Ceremony unless
	// the caller explicitly suppressed it; the equipment component falls back to
	// Action.Equipment.Unholster automatically if the def doesn't author a
	// ceremony, so it's safe to always pass Ceremony when first-acquire is true.
	const bool bUseCeremony = Result.bWasFirstAcquire && !Params.bSkipCeremony;
	const FGameplayTag UnholsterAction = bUseCeremony
		? NexusGameplayTags::Action_Equipment_Ceremony
		: FGameplayTag();

	// Auto-equip the first new instance that has both an equippable fragment
	// and a free compatible slot. Multiple-pickup cases (loot crate yielding
	// several guns) only put one in hands; the rest live in inventory.
	for (UNexusItemInstance* New : AddResult.NewInstances)
	{
		if (!New) continue;
		const UNexusItemDefinition* Def = New->GetDefinition();
		const FNexusFragment_Equippable* Eq = Def
			? Def->FindFragment<FNexusFragment_Equippable>() : nullptr;
		if (!Eq) continue;

		const FGameplayTag Slot = Equipment->PickAutoAssignSlot(New);
		if (!Slot.IsValid()) continue;

		if (Equipment->AssignAndActivate(New, Slot, UnholsterAction))
		{
			Result.AssignedSlot = Slot;
			break;
		}
	}

	return Result;
}

ANexusItemPickup* UNexusInventoryAcquireLibrary::DropItem(
	APawn* From, UNexusItemInstance* Instance, const int32 Count, TSubclassOf<ANexusItemPickup> PickupClass)
{
	if (!From || !Instance || Count <= 0) return nullptr;

	UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return nullptr;

	UNexusInventoryComponent* Inventory = From->FindComponentByClass<UNexusInventoryComponent>();
	if (!Inventory) return nullptr;

	UWorld* World = From->GetWorld();
	if (!World) return nullptr;

	// Remove first; only spawn a pickup for what we actually took out.
	const int32 Removed = Inventory->RemoveFromInstance(Instance, Count);
	if (Removed <= 0) return nullptr;

	UClass* SpawnClass = PickupClass ? PickupClass.Get() : ANexusItemPickup::StaticClass();

	// Drop a short distance in front of the pawn.
	const FVector    SpawnLoc = From->GetActorLocation() + From->GetActorForwardVector() * 100.0f;
	const FTransform SpawnXf(From->GetActorRotation(), SpawnLoc);

	ANexusItemPickup* Pickup = World->SpawnActorDeferred<ANexusItemPickup>(
		SpawnClass, SpawnXf, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (!Pickup) return nullptr;

	Pickup->ConfigurePickup(Definition, Removed);
	Pickup->FinishSpawning(SpawnXf);
	return Pickup;
}

bool UNexusInventoryAcquireLibrary::UseItem(APawn* User, UNexusItemInstance* Instance)
{
	if (!User || !Instance) return false;

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return false;

	const FNexusFragment_Consumable* Consumable = Definition->FindFragment<FNexusFragment_Consumable>();
	if (!Consumable) return false;

	UNexusInventoryComponent* Inventory = User->FindComponentByClass<UNexusInventoryComponent>();
	if (!Inventory) return false;
	if (!Inventory->GetItems().Contains(Instance)) return false; // only use what the pawn holds

	bool bApplied = false;
	if (Consumable->HealAmount > 0.0f)
	{
		if (UNexusHealthComponent* Health = User->FindComponentByClass<UNexusHealthComponent>())
		{
			Health->Heal(Consumable->HealAmount);
			bApplied = true;
		}
	}

	if (bApplied && Consumable->bConsumeOnUse)
	{
		Inventory->RemoveFromInstance(Instance, 1);
	}
	return bApplied;
}
