// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickEmptyTween.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickEmptyTween() {}

// ********** Begin Cross Module References ********************************************************
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickEmptyTween();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickEmptyTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickEmptyTween *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickEmptyTween;
UClass* UQuickEmptyTween::GetPrivateStaticClass()
{
	using TClass = UQuickEmptyTween;
	if (!Z_Registration_Info_UClass_UQuickEmptyTween.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickEmptyTween"),
			Z_Registration_Info_UClass_UQuickEmptyTween.InnerSingleton,
			StaticRegisterNativesUQuickEmptyTween,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UQuickEmptyTween.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickEmptyTween_NoRegister()
{
	return UQuickEmptyTween::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickEmptyTween_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * A lightweight \"empty\" tween used as a timing placeholder.\n *\n * This tween does not interpolate any property; it only provides timing.\n * Useful for sequencing or delaying actions without animating values.\n */" },
		{ "IncludePath", "Tweens/QuickEmptyTween.h" },
		{ "ModuleRelativePath", "Public/Tweens/QuickEmptyTween.h" },
		{ "ToolTip", "A lightweight \"empty\" tween used as a timing placeholder.\n\nThis tween does not interpolate any property; it only provides timing.\nUseful for sequencing or delaying actions without animating values." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickEmptyTween constinit property declarations *************************
// ********** End Class UQuickEmptyTween constinit property declarations ***************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickEmptyTween>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickEmptyTween_Statics
UObject* (*const Z_Construct_UClass_UQuickEmptyTween_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenBase,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickEmptyTween_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickEmptyTween_Statics::ClassParams = {
	&UQuickEmptyTween::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickEmptyTween_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickEmptyTween_Statics::Class_MetaDataParams)
};
void UQuickEmptyTween::StaticRegisterNativesUQuickEmptyTween()
{
}
UClass* Z_Construct_UClass_UQuickEmptyTween()
{
	if (!Z_Registration_Info_UClass_UQuickEmptyTween.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickEmptyTween.OuterSingleton, Z_Construct_UClass_UQuickEmptyTween_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickEmptyTween.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickEmptyTween);
UQuickEmptyTween::~UQuickEmptyTween() {}
// ********** End Class UQuickEmptyTween ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickEmptyTween_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickEmptyTween, UQuickEmptyTween::StaticClass, TEXT("UQuickEmptyTween"), &Z_Registration_Info_UClass_UQuickEmptyTween, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickEmptyTween), 1449531366U) },
	};
}; // Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickEmptyTween_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickEmptyTween_h__Script_QuickTween_1455474360{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickEmptyTween_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickEmptyTween_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
