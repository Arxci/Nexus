// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Nexus : ModuleRules
{
	public Nexus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		// Public: modules whose types appear in this module's PUBLIC headers (so any module that
		// includes them — e.g. NexusEditor's asset factories pulling NexusInputContext.h — gets
		// the include paths). The input/UI framework moved here because the input contexts, the
		// manager, the binder, and the activatable/layout widgets expose their types in headers.
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GameplayTags", "EasyMultiSave", "SlateCore", "Slate", "DeveloperSettings", "InputCore", "EnhancedInput", "CommonInput", "CommonUI", "UMG" });

		// Private: only referenced from .cpp, never exposed in a public header.
		PrivateDependencyModuleNames.AddRange(new string[] { "ModularGameplay", "ComponentPicker", "Niagara" });

		// Uncomment if you are using Slate UIW
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
