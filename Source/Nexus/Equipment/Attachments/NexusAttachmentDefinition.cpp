#include "NexusAttachmentDefinition.h"

FPrimaryAssetId UNexusAttachmentDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("NexusAttachmentDefinition"), GetFName());
}