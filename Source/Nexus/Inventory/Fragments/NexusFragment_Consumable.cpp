#include "NexusFragment_Consumable.h"

#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/NexusGameplayTags.h"

void FNexusFragment_Consumable::InitializeInstance(UNexusItemInstance* Instance) const
{
	if (!Instance) return;
	if (ChargesPerPickup > 0)
	{
		Instance->SetStat(NexusGameplayTags::Stat_Charges, ChargesPerPickup);
	}
}