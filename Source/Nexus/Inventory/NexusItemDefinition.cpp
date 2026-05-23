#include "NexusItemDefinition.h"

#include "Nexus/NexusAssetManager.h"

FPrimaryAssetId UNexusItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UNexusAssetManager::TypeItemDefinition, GetFName());
}
