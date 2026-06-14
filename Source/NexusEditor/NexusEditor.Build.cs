// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

/**
 * Editor-only module for Nexus authoring tools.
 *
 * NOTE: this is the cumulative Build.cs — it supersedes the one shipped in the
 * Phase 1-2 zip (same contents plus "AssetDefinition" for the custom asset
 * definitions / right-click Create factories added in Phase 3).
 */
public class NexusEditor : ModuleRules
{
	public NexusEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Per-file helper duplicates (GatherAssets, LeafName, FindWeapon, ...) that used to
		// collide under a unity build have been routed through the shared NexusEditorUtil /
		// NexusEditorWidgets headers, so unity (UBT's default) is re-enabled.

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Nexus",          // the runtime data-asset types we audit / create
			"Slate",
			"SlateCore",
			"ApplicationCore", // FPlatformApplicationMisc::ClipboardCopy (real Copy buttons in the docs browser)
			"UnrealEd",       // asset editor subsystem, GEditor, save utils, UFactory
			"ToolMenus",      // Tools-menu entries
			"DataValidation", // UEditorValidatorBase
			"DeveloperSettings", // UNexusEditorSettings (Project Settings page for the tools)
			"AssetDefinition", // UAssetDefinitionDefault (colours / categories / right-click Create)
			"GameplayTags",
			"GameplayTagsEditor", // register derived identity tags (AddNewGameplayTagToINI)
			"AssetRegistry",  // scan all item/attachment assets
			"AssetTools",     // unique-name resolution for the creator
			"PropertyEditor", // embedded Details panel in the creator window
			"ContentBrowser", // folder picker in the creator window
			"DesktopPlatform", // CSV export/import file dialogs
			"AdvancedPreviewScene", // 3D mesh preview in the creator window
			"AssetManagerEditor", // reference viewer launch from the validation banner
		});
	}
}
