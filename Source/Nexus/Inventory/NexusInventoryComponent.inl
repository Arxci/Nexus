#pragma once

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"

template <typename T>
void UNexusInventoryComponent::ForEachInstanceWithFragment(TFunctionRef<void(UNexusItemInstance*, const T&)> Fn) const
{
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (!Def) continue;
		if (const T* Frag = Def->FindFragment<T>())
		{
			Fn(Instance, *Frag);
		}
	}
}