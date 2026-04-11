// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Nexus : ModuleRules
{
	public Nexus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GameplayTags", "EasyMultiSave" });

		PrivateDependencyModuleNames.AddRange(new string[] { "InputCore", "EnhancedInput", "CommonInput", "ModularGameplay",  });

		// Uncomment if you are using Slate UIW
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
