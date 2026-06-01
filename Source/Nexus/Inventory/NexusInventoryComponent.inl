#pragma once

#include "Nexus/Inventory/NexusItemContainer.h"

template <typename T>
void UNexusInventoryComponent::ForEachInstanceWithFragment(TFunctionRef<void(UNexusItemInstance*, const T&)> Fn) const
{
	if (Container)
	{
		Container->ForEachInstanceWithFragment<T>(Fn);
	}
}
