#include "NexusEquipmentLoadout.h"

const FNexusEquipmentSlotDef* UNexusEquipmentLoadout::FindSlot(const FGameplayTag SlotTag) const
{
	if (!SlotTag.IsValid()) return nullptr;

	for (const FNexusEquipmentSlotDef& Slot : Slots)
	{
		if (Slot.SlotTag.MatchesTagExact(SlotTag))
		{
			return &Slot;
		}
	}
	return nullptr;
}

void UNexusEquipmentLoadout::GetSlotTagsSorted(TArray<FGameplayTag>& OutSlotTags) const
{
	OutSlotTags.Reset(Slots.Num());

	// Index list sorted by (SortOrder, declaration index) keeps the result stable
	// even when two slots share a SortOrder — designers get a deterministic order.
	TArray<int32> Order;
	Order.Reserve(Slots.Num());
	for (int32 i = 0; i < Slots.Num(); ++i)
	{
		if (Slots[i].SlotTag.IsValid())
		{
			Order.Add(i);
		}
	}

	Order.StableSort([this](const int32 A, const int32 B)
	{
		return Slots[A].SortOrder < Slots[B].SortOrder;
	});

	for (const int32 Index : Order)
	{
		OutSlotTags.Add(Slots[Index].SlotTag);
	}
}