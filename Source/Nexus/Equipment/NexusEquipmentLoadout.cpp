#include "NexusEquipmentLoadout.h"

#if WITH_EDITOR
#include "Nexus/Validation/NexusDataValidation.h"
#endif

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

#if WITH_EDITOR

EDataValidationResult UNexusEquipmentLoadout::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (Slots.Num() == 0)
	{
		Context.AddWarning(INVTEXT("Loadout exposes no slots — a character using it can equip nothing."));
	}

	// SlotTag is the runtime key FindSlot/HasSlot look up by; a repeat would shadow the
	// earlier slot, so every slot's tag must be set and unique within the loadout.
	TSet<FGameplayTag> Seen;
	for (int32 Index = 0; Index < Slots.Num(); ++Index)
	{
		const FString Field = FString::Printf(TEXT("Slots[%d].Slot Tag"), Index);
		NexusDataValidation::RequireTag     (Context, Result, Slots[Index].SlotTag, *Field);
		NexusDataValidation::RequireTagUnder(Context, Result, Slots[Index].SlotTag, TEXT("Equipment.Slot"), *Field);

		if (Slots[Index].SlotTag.IsValid())
		{
			bool bAlreadySeen = false;
			Seen.Add(Slots[Index].SlotTag, &bAlreadySeen);
			if (bAlreadySeen)
			{
				Context.AddError(FText::FromString(FString::Printf(
					TEXT("Slots[%d] repeats Slot Tag %s — slot tags are runtime keys and must be unique within a loadout."),
					Index, *Slots[Index].SlotTag.ToString())));
				NexusDataValidation::Accumulate(Result, EDataValidationResult::Invalid);
			}
		}
	}

	return Result;
}

#endif // WITH_EDITOR