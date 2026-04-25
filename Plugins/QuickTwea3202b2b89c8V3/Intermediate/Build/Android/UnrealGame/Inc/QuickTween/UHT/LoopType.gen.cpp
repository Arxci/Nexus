// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LoopType.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeLoopType() {}

// ********** Begin Cross Module References ********************************************************
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_ELoopType();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ELoopType *****************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ELoopType;
static UEnum* ELoopType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ELoopType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ELoopType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_QuickTween_ELoopType, (UObject*)Z_Construct_UPackage__Script_QuickTween(), TEXT("ELoopType"));
	}
	return Z_Registration_Info_UEnum_ELoopType.OuterSingleton;
}
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<ELoopType>()
{
	return ELoopType_StaticEnum();
}
struct Z_Construct_UEnum_QuickTween_ELoopType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Enum representing the type of looping behavior for tweens.\n * - Restart: The tween restarts from the beginning after completion.\n * - PingPong: The tween reverses direction after reaching the end, creating a back-and-forth effect.\n */" },
		{ "ModuleRelativePath", "Public/Utils/LoopType.h" },
		{ "PingPong.DisplayName", "Ping Pong" },
		{ "PingPong.Name", "ELoopType::PingPong" },
		{ "Restart.DisplayName", "Restart" },
		{ "Restart.Name", "ELoopType::Restart" },
		{ "ToolTip", "Enum representing the type of looping behavior for tweens.\n- Restart: The tween restarts from the beginning after completion.\n- PingPong: The tween reverses direction after reaching the end, creating a back-and-forth effect." },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ELoopType::Restart", (int64)ELoopType::Restart },
		{ "ELoopType::PingPong", (int64)ELoopType::PingPong },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_QuickTween_ELoopType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_QuickTween_ELoopType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_QuickTween,
	nullptr,
	"ELoopType",
	"ELoopType",
	Z_Construct_UEnum_QuickTween_ELoopType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_ELoopType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_ELoopType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_QuickTween_ELoopType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_QuickTween_ELoopType()
{
	if (!Z_Registration_Info_UEnum_ELoopType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ELoopType.InnerSingleton, Z_Construct_UEnum_QuickTween_ELoopType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ELoopType.InnerSingleton;
}
// ********** End Enum ELoopType *******************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_LoopType_h__Script_QuickTween_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ELoopType_StaticEnum, TEXT("ELoopType"), &Z_Registration_Info_UEnum_ELoopType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1754923220U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_LoopType_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_LoopType_h__Script_QuickTween_2957569523{
	TEXT("/Script/QuickTween"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_LoopType_h__Script_QuickTween_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_LoopType_h__Script_QuickTween_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
