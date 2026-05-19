#include "NexusLevelManifest.h"

FPrimaryAssetId UNexusLevelManifest::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("NexusLevelManifest"), GetFName());
}