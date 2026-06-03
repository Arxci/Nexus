#include "Settings/NexusEditorSettings.h"

UNexusEditorSettings::UNexusEditorSettings()
{
	// Defaults match where the tools used to hard-code their writes, but now unified
	// under one root (the manifest builder previously wrote to /Game/Nexus/Manifests,
	// out of step with everything else).
	AuthoringRootFolder = TEXT("/Game/Nexus/Blueprint/Data");
	ManifestFolder      = TEXT("/Game/Nexus/Blueprint/Data/Manifests");
	RecipeFolder        = TEXT("/Game/Nexus/Blueprint/Data/Recipes");
}
