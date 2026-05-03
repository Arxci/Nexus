#include "NexusKeyItemQueryLibrary.h"

#include "Nexus/Inventory/Fragments/KeyItem/NexusFragment_KeyItem.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"

bool UNexusKeyItemQueryLibrary::InventoryHasUnlockTag(
	const UNexusInventoryComponent* Inventory, FGameplayTag UnlockTag)
{
	if (!Inventory || !UnlockTag.IsValid()) return false;

	bool bFound = false;
	Inventory->ForEachInstanceWithFragment<FNexusFragment_KeyItem>(
		[&](UNexusItemInstance*, const FNexusFragment_KeyItem& Key)
		{
			if (!bFound && Key.UnlockTag.MatchesTagExact(UnlockTag))
			{
				bFound = true;
			}
		});
	return bFound;
}