#include "NexusAssetManager.h"

#include "Engine/Engine.h"

const FName UNexusAssetManager::BundleEquipped(TEXT("Equipped"));
const FName UNexusAssetManager::BundlePickup  (TEXT("Pickup"));
const FName UNexusAssetManager::BundleUI      (TEXT("UI"));

const FPrimaryAssetType UNexusAssetManager::TypeItemDefinition      (TEXT("NexusItemDefinition"));
const FPrimaryAssetType UNexusAssetManager::TypeAttachmentDefinition(TEXT("NexusAttachmentDefinition"));
const FPrimaryAssetType UNexusAssetManager::TypeLevelManifest       (TEXT("NexusLevelManifest"));

UNexusAssetManager& UNexusAssetManager::Get()
{
	checkf(GEngine, TEXT("UNexusAssetManager::Get called before GEngine exists"));
	UNexusAssetManager* This = Cast<UNexusAssetManager>(GEngine->AssetManager);
	checkf(This,
		TEXT("UNexusAssetManager not configured. Set AssetManagerClassName=/Script/Nexus.NexusAssetManager "
			 "under [/Script/Engine.Engine] in DefaultEngine.ini."));
	return *This;
}