#include "NexusAttachmentDefinition.h"

#include "Nexus/NexusAssetManager.h"

FPrimaryAssetId UNexusAttachmentDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UNexusAssetManager::TypeAttachmentDefinition, GetFName());
}
