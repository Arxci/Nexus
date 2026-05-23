#include "NexusLevelManifest.h"

#include "Nexus/NexusAssetManager.h"

FPrimaryAssetId UNexusLevelManifest::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UNexusAssetManager::TypeLevelManifest, GetFName());
}
