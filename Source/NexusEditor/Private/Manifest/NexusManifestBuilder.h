#pragma once

#include "CoreMinimal.h"

class UNexusLevelManifest;

/**
 * One-click level manifest authoring. Scans every actor in the active editor level for
 * referenced item / attachment definitions (e.g. a placed ANexusItemPickup's Definition)
 * and writes them into the level's manifest — updating the one the World Settings already
 * points at, or creating a fresh manifest (and wiring it onto the World Settings) if there
 * isn't one yet. Editor-only.
 */
struct FNexusManifestBuilder
{
	/**
	 * Build/refresh the current level's manifest from its placed content.
	 * Returns the manifest (dirty, unsaved) or null with OutMessage explaining why.
	 */
	static UNexusLevelManifest* BuildFromCurrentLevel(FString& OutMessage);
};
