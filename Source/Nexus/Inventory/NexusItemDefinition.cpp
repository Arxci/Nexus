#include "NexusItemDefinition.h"

FPrimaryAssetId UNexusItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("NexusItemDefinition"), GetFName());
}