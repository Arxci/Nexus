#pragma once

#include "CoreMinimal.h"

#include "Engine/AssetManager.h"

#include "NexusAssetManager.generated.h"


/**
 * Project's UAssetManager subclass. Single source of truth for:
 *   - Bundle names (Equipped / Pickup / UI)
 *   - Primary asset types (NexusItemDefinition / NexusAttachmentDefinition / NexusLevelManifest)
 *   - Future project-wide asset-loading hooks (StartInitialLoading override,
 *     custom bundle expansion, etc.)
 *
 * Wired via DefaultEngine.ini:
 *   [/Script/Engine.Engine]
 *   AssetManagerClassName=/Script/Nexus.NexusAssetManager
 *
 * Pattern mirrors ULyraAssetManager.
 */
UCLASS(Config = Game)
class NEXUS_API UNexusAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	/**
	 * Typed accessor. UAssetManager::Get() still works for any base-class
	 * operation; use this overload when you need Nexus-specific statics or
	 * to call future project-specific helpers without casting at every site.
	 */
	static UNexusAssetManager& Get();

	// Bundle names
	static const FName BundleEquipped;
	static const FName BundlePickup;
	static const FName BundleUI;

	// Primary asset types
	static const FPrimaryAssetType TypeItemDefinition;
	static const FPrimaryAssetType TypeAttachmentDefinition;
	static const FPrimaryAssetType TypeLevelManifest;
};