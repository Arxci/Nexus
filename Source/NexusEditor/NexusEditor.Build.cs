// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

/**
 * Editor-only module for Nexus authoring tools: the cross-asset content
 * validator and the content dashboard. Kept separate from the runtime "Nexus"
 * module because it links editor-only modules (UnrealEd, DataValidation, Slate,
 * ToolMenus) that must never end up in a packaged build.
 */
public class NexusEditor : ModuleRules
{
	public NexusEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
			"UnrealEd",       // asset editor subsystem, GEditor, save utils
			"ToolMenus",      // Tools-menu entries
			"DataValidation", // UEditorValidatorBase
			"GameplayTags",
			"GameplayTagsEditor", // register derived identity tags (AddNewGameplayTagToINI)
			"AssetRegistry",  // scan all item/attachment assets
			"AssetTools",     // unique-name resolution for the creator
			"PropertyEditor", // embedded Details panel in the creator window
			"ContentBrowser", // folder picker in the creator window
			"DesktopPlatform", // CSV export/import file dialogs
		});
	}
}
