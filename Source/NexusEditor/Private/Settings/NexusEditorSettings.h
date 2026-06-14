#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NexusEditorSettings.generated.h"

/**
 * A named Creator preset: a template plus smart defaults, so one click stamps a
 * preconfigured item instead of the bare template. Template is the
 * ENexusItemTemplate value as a number (see the tooltip), kept as a uint8 because
 * that enum is editor-only and not reflected.
 */
USTRUCT()
struct FNexusCreatorPreset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, config, Category = "Preset")
	FString Name;

	/** Item template: 0 Ranged, 1 Melee, 2 Consumable, 3 Ammo, 4 Treasure, 5 KeyItem, 6 Charm, 7 Generic. */
	UPROPERTY(EditAnywhere, config, Category = "Preset", meta = (ClampMin = "0", ClampMax = "7"))
	uint8 Template = 0;

	UPROPERTY(EditAnywhere, config, Category = "Preset")
	FIntPoint GridSize = FIntPoint(1, 1);

	UPROPERTY(EditAnywhere, config, Category = "Preset", meta = (ClampMin = "0.0"))
	float Weight = 0.0f;

	UPROPERTY(EditAnywhere, config, Category = "Preset", meta = (ClampMin = "0"))
	int32 BaseValue = 0;
};

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

	/**
	 * Economy View flags an item as a value-per-cell outlier when it sits this many
	 * times above or below the roster median. Lower = stricter (more items flagged).
	 */
	UPROPERTY(EditAnywhere, config, Category = "Balancing", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float EconomyOutlierFactor = 3.0f;

	/** Named one-click presets shown beside the Creator's template combo. */
	UPROPERTY(EditAnywhere, config, Category = "Presets")
	TArray<FNexusCreatorPreset> CreatorPresets;

	/** Convenience accessor used by the tools. */
	static const UNexusEditorSettings& Get()
	{
		return *GetDefault<UNexusEditorSettings>();
	}
};
