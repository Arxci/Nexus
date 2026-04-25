// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FQuickTweenLatentAction.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeFQuickTweenLatentAction() {}

// ********** Begin Cross Module References ********************************************************
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EQuickTweenLatentSteps ****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EQuickTweenLatentSteps;
static UEnum* EQuickTweenLatentSteps_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EQuickTweenLatentSteps.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EQuickTweenLatentSteps.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, (UObject*)Z_Construct_UPackage__Script_QuickTween(), TEXT("EQuickTweenLatentSteps"));
	}
	return Z_Registration_Info_UEnum_EQuickTweenLatentSteps.OuterSingleton;
}
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EQuickTweenLatentSteps>()
{
	return EQuickTweenLatentSteps_StaticEnum();
}
struct Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Comment", "/**\n * Enumeration used by the latent action to indicate the current step/state\n * of a QuickTween when reported back to Blueprint latent nodes.\n *\n * Each value represents a lifecycle point of a tween so Blueprint code\n * waiting on the latent action can branch or resume execution accordingly.\n */" },
		{ "Default.Comment", "/** Initial/default state before any tween events have been received. */" },
		{ "Default.Name", "EQuickTweenLatentSteps::Default" },
		{ "Default.ToolTip", "Initial/default state before any tween events have been received." },
		{ "ModuleRelativePath", "Public/Blueprint/Latent/FQuickTweenLatentAction.h" },
		{ "OnComplete.Comment", "/** The tween completed successfully (OnComplete event). */" },
		{ "OnComplete.Name", "EQuickTweenLatentSteps::OnComplete" },
		{ "OnComplete.ToolTip", "The tween completed successfully (OnComplete event)." },
		{ "OnKilled.Comment", "/** The tween will no longer be usable. */" },
		{ "OnKilled.Name", "EQuickTweenLatentSteps::OnKilled" },
		{ "OnKilled.ToolTip", "The tween will no longer be usable." },
		{ "OnLoop.Comment", "/** The tween has looped (OnLoop event). */" },
		{ "OnLoop.Name", "EQuickTweenLatentSteps::OnLoop" },
		{ "OnLoop.ToolTip", "The tween has looped (OnLoop event)." },
		{ "OnStart.Comment", "/** The tween has started (OnStart event). */" },
		{ "OnStart.Name", "EQuickTweenLatentSteps::OnStart" },
		{ "OnStart.ToolTip", "The tween has started (OnStart event)." },
		{ "OnUpdate.Comment", "/** The tween has produced an update/tick (OnUpdate event). */" },
		{ "OnUpdate.Name", "EQuickTweenLatentSteps::OnUpdate" },
		{ "OnUpdate.ToolTip", "The tween has produced an update/tick (OnUpdate event)." },
		{ "ToolTip", "Enumeration used by the latent action to indicate the current step/state\nof a QuickTween when reported back to Blueprint latent nodes.\n\nEach value represents a lifecycle point of a tween so Blueprint code\nwaiting on the latent action can branch or resume execution accordingly." },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EQuickTweenLatentSteps::Default", (int64)EQuickTweenLatentSteps::Default },
		{ "EQuickTweenLatentSteps::OnStart", (int64)EQuickTweenLatentSteps::OnStart },
		{ "EQuickTweenLatentSteps::OnUpdate", (int64)EQuickTweenLatentSteps::OnUpdate },
		{ "EQuickTweenLatentSteps::OnLoop", (int64)EQuickTweenLatentSteps::OnLoop },
		{ "EQuickTweenLatentSteps::OnComplete", (int64)EQuickTweenLatentSteps::OnComplete },
		{ "EQuickTweenLatentSteps::OnKilled", (int64)EQuickTweenLatentSteps::OnKilled },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_QuickTween,
	nullptr,
	"EQuickTweenLatentSteps",
	"EQuickTweenLatentSteps",
	Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics::Enum_MetaDataParams), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps()
{
	if (!Z_Registration_Info_UEnum_EQuickTweenLatentSteps.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EQuickTweenLatentSteps.InnerSingleton, Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EQuickTweenLatentSteps.InnerSingleton;
}
// ********** End Enum EQuickTweenLatentSteps ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_Latent_FQuickTweenLatentAction_h__Script_QuickTween_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EQuickTweenLatentSteps_StaticEnum, TEXT("EQuickTweenLatentSteps"), &Z_Registration_Info_UEnum_EQuickTweenLatentSteps, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 193244591U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_Latent_FQuickTweenLatentAction_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_Latent_FQuickTweenLatentAction_h__Script_QuickTween_508930038{
	TEXT("/Script/QuickTween"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_Latent_FQuickTweenLatentAction_h__Script_QuickTween_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_Latent_FQuickTweenLatentAction_h__Script_QuickTween_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
