#include "NexusInventoryAcquireLibrary.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "Nexus/NexusGameplayTags.h"

FNexusAcquireResult UNexusInventoryAcquireLibrary::AcquireItem(
	APawn* Recipient,
	UNexusItemDefinition* Definition,
	const int32 Count,
	const bool bAutoEquipIfPossible,
	const bool bSkipCeremony,
	const TMap<FGameplayTag, int32>& InitialStatTags)
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
	if (InitialStatTags.Num() > 0)
	{
		for (UNexusItemInstance* New : AddResult.NewInstances)
		{
			if (!New) continue;
			for (const TPair<FGameplayTag, int32>& Pair : InitialStatTags)
			{
				New->SetStat(Pair.Key, Pair.Value);
			}
		}
	}

	Inventory->MarkItemDefinitionSeen(Definition);

	if (!bAutoEquipIfPossible) return Result;

	UNexusEquipmentComponent* Equipment = Recipient->FindComponentByClass<UNexusEquipmentComponent>();
	if (!Equipment) return Result;

	// Pick the action tag for the draw phase. First-acquire uses Ceremony unless
	// the caller explicitly suppressed it; the equipment component falls back to
	// Action.Equipment.Unholster automatically if the def doesn't author a
	// ceremony, so it's safe to always pass Ceremony when first-acquire is true.
	const bool bUseCeremony = Result.bWasFirstAcquire && !bSkipCeremony;
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
