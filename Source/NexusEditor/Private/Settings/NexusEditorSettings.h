#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NexusEditorSettings.generated.h"

/**
 * Project-wide configuration for the Nexus authoring tools, surfaced under
 * Project Settings → Nexus → "Nexus Authoring Tools" (and stored in DefaultEditor.ini,
 * so the whole team shares one set of defaults).
 *
 * This replaces the folder-path string literals that were scattered across the
 * Creator window (/Game/Nexus/Blueprint/Data), the crafting tree
 * (.../Data/Recipes), and the manifest builder (/Game/Nexus/Manifests — which
 * didn't even match the Creator's root). Now every "where do new assets land"
 * decision reads from one place a designer can change without a recompile.
 */
UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Nexus Authoring Tools"))
class UNexusEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UNexusEditorSettings();

	/** Group these under a dedicated "Nexus" section in Project Settings. */
	virtual FName GetCategoryName() const override { return FName(TEXT("Nexus")); }

	/** Root content folder new Nexus assets are created under by default. */
	UPROPERTY(EditAnywhere, config, Category = "Folders")
	FString AuthoringRootFolder;

	/** Folder for level manifests (built from a level or created blank). */
	UPROPERTY(EditAnywhere, config, Category = "Folders")
	FString ManifestFolder;

	/** Folder for crafting recipes created from the Crafting Tree / Creator. */
	UPROPERTY(EditAnywhere, config, Category = "Folders")
	FString RecipeFolder;

	/**
	 * When the Creator's "Sort into type folders" toggle is on, route saves into
	 * per-type subfolders (Weapons, Attachments, ...) under AuthoringRootFolder.
	 * This is the default state of that toggle.
	 */
	UPROPERTY(EditAnywhere, config, Category = "Folders")
	bool bRouteIntoTypeFoldersByDefault = true;

	/** Convenience accessor used by the tools. */
	static const UNexusEditorSettings& Get()
	{
		return *GetDefault<UNexusEditorSettings>();
	}
};
