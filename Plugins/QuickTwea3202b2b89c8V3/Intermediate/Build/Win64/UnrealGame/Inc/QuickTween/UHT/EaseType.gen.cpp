// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EaseType.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEaseType() {}

// ********** Begin Cross Module References ********************************************************
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EEaseType();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EEaseType *****************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEaseType;
static UEnum* EEaseType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEaseType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEaseType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_QuickTween_EEaseType, (UObject*)Z_Construct_UPackage__Script_QuickTween(), TEXT("EEaseType"));
	}
	return Z_Registration_Info_UEnum_EEaseType.OuterSingleton;
}
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EEaseType>()
{
	return EEaseType_StaticEnum();
}
struct Z_Construct_UEnum_QuickTween_EEaseType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * EEaseType\n *\n * Enum representing various types of easing functions for tweening animations.\n * These easing types control the rate of change of a parameter over time,\n * allowing for smooth, natural, or stylized transitions.\n *\n * Each value corresponds to a specific mathematical easing function,\n * such as linear, sine, quad, cubic, quart, quint, expo, circ, back, elastic, and bounce,\n * with variants for ease-in, ease-out, and ease-in-out.\n *\n * This enum is exposed to Blueprints.\n */" },
		{ "InBack.Comment", "/** Easing in with a back function (overshoots slightly) */" },
		{ "InBack.DisplayName", "Ease In Back" },
		{ "InBack.Name", "EEaseType::InBack" },
		{ "InBack.ToolTip", "Easing in with a back function (overshoots slightly)" },
		{ "InBounce.Comment", "/** Easing in with a bounce function */" },
		{ "InBounce.DisplayName", "Ease In Bounce" },
		{ "InBounce.Name", "EEaseType::InBounce" },
		{ "InBounce.ToolTip", "Easing in with a bounce function" },
		{ "InCirc.Comment", "/** Easing in with a circular function */" },
		{ "InCirc.DisplayName", "Ease In Circ" },
		{ "InCirc.Name", "EEaseType::InCirc" },
		{ "InCirc.ToolTip", "Easing in with a circular function" },
		{ "InCubic.Comment", "/** Easing in with a cubic function */" },
		{ "InCubic.DisplayName", "Ease In Cubic" },
		{ "InCubic.Name", "EEaseType::InCubic" },
		{ "InCubic.ToolTip", "Easing in with a cubic function" },
		{ "InElastic.Comment", "/** Easing in with an elastic function (bounces at the start) */" },
		{ "InElastic.DisplayName", "Ease In Elastic" },
		{ "InElastic.Name", "EEaseType::InElastic" },
		{ "InElastic.ToolTip", "Easing in with an elastic function (bounces at the start)" },
		{ "InExpo.Comment", "/** Easing in with an exponential function */" },
		{ "InExpo.DisplayName", "Ease In Expo" },
		{ "InExpo.Name", "EEaseType::InExpo" },
		{ "InExpo.ToolTip", "Easing in with an exponential function" },
		{ "InOutBack.Comment", "/** Easing in and out with a back function (overshoots slightly) */" },
		{ "InOutBack.DisplayName", "Ease InOut Back" },
		{ "InOutBack.Name", "EEaseType::InOutBack" },
		{ "InOutBack.ToolTip", "Easing in and out with a back function (overshoots slightly)" },
		{ "InOutBounce.Comment", "/** Easing in and out with a bounce function */" },
		{ "InOutBounce.DisplayName", "Ease InOut Bounce" },
		{ "InOutBounce.Name", "EEaseType::InOutBounce" },
		{ "InOutBounce.ToolTip", "Easing in and out with a bounce function" },
		{ "InOutCirc.Comment", "/** Easing in and out with a circular function */" },
		{ "InOutCirc.DisplayName", "Ease InOut Circ" },
		{ "InOutCirc.Name", "EEaseType::InOutCirc" },
		{ "InOutCirc.ToolTip", "Easing in and out with a circular function" },
		{ "InOutCubic.Comment", "/** Easing in and out with a cubic function */" },
		{ "InOutCubic.DisplayName", "Ease InOut Cubic" },
		{ "InOutCubic.Name", "EEaseType::InOutCubic" },
		{ "InOutCubic.ToolTip", "Easing in and out with a cubic function" },
		{ "InOutElastic.Comment", "/** Easing in and out with an elastic function (bounces at both ends) */" },
		{ "InOutElastic.DisplayName", "Ease InOut Elastic" },
		{ "InOutElastic.Name", "EEaseType::InOutElastic" },
		{ "InOutElastic.ToolTip", "Easing in and out with an elastic function (bounces at both ends)" },
		{ "InOutExpo.Comment", "/** Easing in and out with an exponential function */" },
		{ "InOutExpo.DisplayName", "Ease InOut Expo" },
		{ "InOutExpo.Name", "EEaseType::InOutExpo" },
		{ "InOutExpo.ToolTip", "Easing in and out with an exponential function" },
		{ "InOutQuad.Comment", "/** Easing in and out with a quadratic function */" },
		{ "InOutQuad.DisplayName", "Ease InOut Quad" },
		{ "InOutQuad.Name", "EEaseType::InOutQuad" },
		{ "InOutQuad.ToolTip", "Easing in and out with a quadratic function" },
		{ "InOutQuart.Comment", "/** Easing in and out with a quartic function */" },
		{ "InOutQuart.DisplayName", "Ease InOut Quart" },
		{ "InOutQuart.Name", "EEaseType::InOutQuart" },
		{ "InOutQuart.ToolTip", "Easing in and out with a quartic function" },
		{ "InOutQuint.Comment", "/** Easing in and out with a quintic function */" },
		{ "InOutQuint.DisplayName", "Ease InOut Quint" },
		{ "InOutQuint.Name", "EEaseType::InOutQuint" },
		{ "InOutQuint.ToolTip", "Easing in and out with a quintic function" },
		{ "InOutSine.Comment", "/** Easing in and out with a sine function */" },
		{ "InOutSine.DisplayName", "Ease InOut Sine" },
		{ "InOutSine.Name", "EEaseType::InOutSine" },
		{ "InOutSine.ToolTip", "Easing in and out with a sine function" },
		{ "InQuad.Comment", "/** Easing in with a quadratic function */" },
		{ "InQuad.DisplayName", "Ease In Quad" },
		{ "InQuad.Name", "EEaseType::InQuad" },
		{ "InQuad.ToolTip", "Easing in with a quadratic function" },
		{ "InQuart.Comment", "/** Easing in with a quartic function */" },
		{ "InQuart.DisplayName", "Ease In Quart" },
		{ "InQuart.Name", "EEaseType::InQuart" },
		{ "InQuart.ToolTip", "Easing in with a quartic function" },
		{ "InQuint.Comment", "/** Easing in with a quintic function */" },
		{ "InQuint.DisplayName", "Ease In Quint" },
		{ "InQuint.Name", "EEaseType::InQuint" },
		{ "InQuint.ToolTip", "Easing in with a quintic function" },
		{ "InSine.Comment", "/** Easing in with a sine function */" },
		{ "InSine.DisplayName", "Ease In Sine" },
		{ "InSine.Name", "EEaseType::InSine" },
		{ "InSine.ToolTip", "Easing in with a sine function" },
		{ "Linear.Comment", "/** Linear interpolation (no easing) */" },
		{ "Linear.DisplayName", "Linear" },
		{ "Linear.Name", "EEaseType::Linear" },
		{ "Linear.ToolTip", "Linear interpolation (no easing)" },
		{ "ModuleRelativePath", "Public/Utils/EaseType.h" },
		{ "OutBack.Comment", "/** Easing out with a back function (overshoots slightly) */" },
		{ "OutBack.DisplayName", "Ease Out Back" },
		{ "OutBack.Name", "EEaseType::OutBack" },
		{ "OutBack.ToolTip", "Easing out with a back function (overshoots slightly)" },
		{ "OutBounce.Comment", "/** Easing out with a bounce function */" },
		{ "OutBounce.DisplayName", "Ease Out Bounce" },
		{ "OutBounce.Name", "EEaseType::OutBounce" },
		{ "OutBounce.ToolTip", "Easing out with a bounce function" },
		{ "OutCirc.Comment", "/** Easing out with a circular function */" },
		{ "OutCirc.DisplayName", "Ease Out Circ" },
		{ "OutCirc.Name", "EEaseType::OutCirc" },
		{ "OutCirc.ToolTip", "Easing out with a circular function" },
		{ "OutCubic.Comment", "/** Easing out with a cubic function */" },
		{ "OutCubic.DisplayName", "Ease Out Cubic" },
		{ "OutCubic.Name", "EEaseType::OutCubic" },
		{ "OutCubic.ToolTip", "Easing out with a cubic function" },
		{ "OutElastic.Comment", "/** Easing out with an elastic function (bounces at the end) */" },
		{ "OutElastic.DisplayName", "Ease Out Elastic" },
		{ "OutElastic.Name", "EEaseType::OutElastic" },
		{ "OutElastic.ToolTip", "Easing out with an elastic function (bounces at the end)" },
		{ "OutExpo.Comment", "/** Easing out with an exponential function */" },
		{ "OutExpo.DisplayName", "Ease Out Expo" },
		{ "OutExpo.Name", "EEaseType::OutExpo" },
		{ "OutExpo.ToolTip", "Easing out with an exponential function" },
		{ "OutQuad.Comment", "/** Easing out with a quadratic function */" },
		{ "OutQuad.DisplayName", "Ease Out Quad" },
		{ "OutQuad.Name", "EEaseType::OutQuad" },
		{ "OutQuad.ToolTip", "Easing out with a quadratic function" },
		{ "OutQuart.Comment", "/** Easing out with a quartic function */" },
		{ "OutQuart.DisplayName", "Ease Out Quart" },
		{ "OutQuart.Name", "EEaseType::OutQuart" },
		{ "OutQuart.ToolTip", "Easing out with a quartic function" },
		{ "OutQuint.Comment", "/** Easing out with a quintic function */" },
		{ "OutQuint.DisplayName", "Ease Out Quint" },
		{ "OutQuint.Name", "EEaseType::OutQuint" },
		{ "OutQuint.ToolTip", "Easing out with a quintic function" },
		{ "OutSine.Comment", "/** Easing out with a sine function */" },
		{ "OutSine.DisplayName", "Ease Out Sine" },
		{ "OutSine.Name", "EEaseType::OutSine" },
		{ "OutSine.ToolTip", "Easing out with a sine function" },
		{ "ToolTip", "EEaseType\n\nEnum representing various types of easing functions for tweening animations.\nThese easing types control the rate of change of a parameter over time,\nallowing for smooth, natural, or stylized transitions.\n\nEach value corresponds to a specific mathematical easing function,\nsuch as linear, sine, quad, cubic, quart, quint, expo, circ, back, elastic, and bounce,\nwith variants for ease-in, ease-out, and ease-in-out.\n\nThis enum is exposed to Blueprints." },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEaseType::Linear", (int64)EEaseType::Linear },
		{ "EEaseType::InSine", (int64)EEaseType::InSine },
		{ "EEaseType::OutSine", (int64)EEaseType::OutSine },
		{ "EEaseType::InOutSine", (int64)EEaseType::InOutSine },
		{ "EEaseType::InQuad", (int64)EEaseType::InQuad },
		{ "EEaseType::OutQuad", (int64)EEaseType::OutQuad },
		{ "EEaseType::InOutQuad", (int64)EEaseType::InOutQuad },
		{ "EEaseType::InCubic", (int64)EEaseType::InCubic },
		{ "EEaseType::OutCubic", (int64)EEaseType::OutCubic },
		{ "EEaseType::InOutCubic", (int64)EEaseType::InOutCubic },
		{ "EEaseType::InQuart", (int64)EEaseType::InQuart },
		{ "EEaseType::OutQuart", (int64)EEaseType::OutQuart },
		{ "EEaseType::InOutQuart", (int64)EEaseType::InOutQuart },
		{ "EEaseType::InQuint", (int64)EEaseType::InQuint },
		{ "EEaseType::OutQuint", (int64)EEaseType::OutQuint },
		{ "EEaseType::InOutQuint", (int64)EEaseType::InOutQuint },
		{ "EEaseType::InExpo", (int64)EEaseType::InExpo },
		{ "EEaseType::OutExpo", (int64)EEaseType::OutExpo },
		{ "EEaseType::InOutExpo", (int64)EEaseType::InOutExpo },
		{ "EEaseType::InCirc", (int64)EEaseType::InCirc },
		{ "EEaseType::OutCirc", (int64)EEaseType::OutCirc },
		{ "EEaseType::InOutCirc", (int64)EEaseType::InOutCirc },
		{ "EEaseType::InBack", (int64)EEaseType::InBack },
		{ "EEaseType::OutBack", (int64)EEaseType::OutBack },
		{ "EEaseType::InOutBack", (int64)EEaseType::InOutBack },
		{ "EEaseType::InElastic", (int64)EEaseType::InElastic },
		{ "EEaseType::OutElastic", (int64)EEaseType::OutElastic },
		{ "EEaseType::InOutElastic", (int64)EEaseType::InOutElastic },
		{ "EEaseType::InBounce", (int64)EEaseType::InBounce },
		{ "EEaseType::OutBounce", (int64)EEaseType::OutBounce },
		{ "EEaseType::InOutBounce", (int64)EEaseType::InOutBounce },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_QuickTween_EEaseType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_QuickTween_EEaseType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_QuickTween,
	nullptr,
	"EEaseType",
	"EEaseType",
	Z_Construct_UEnum_QuickTween_EEaseType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EEaseType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EEaseType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_QuickTween_EEaseType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_QuickTween_EEaseType()
{
	if (!Z_Registration_Info_UEnum_EEaseType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEaseType.InnerSingleton, Z_Construct_UEnum_QuickTween_EEaseType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEaseType.InnerSingleton;
}
// ********** End Enum EEaseType *******************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_EaseType_h__Script_QuickTween_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EEaseType_StaticEnum, TEXT("EEaseType"), &Z_Registration_Info_UEnum_EEaseType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2272651248U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_EaseType_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_EaseType_h__Script_QuickTween_461371826{
	TEXT("/Script/QuickTween"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_EaseType_h__Script_QuickTween_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_EaseType_h__Script_QuickTween_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
