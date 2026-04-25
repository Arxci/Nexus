// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickTweenManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickTweenManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenManager();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickTweenManager *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickTweenManager;
UClass* UQuickTweenManager::GetPrivateStaticClass()
{
	using TClass = UQuickTweenManager;
	if (!Z_Registration_Info_UClass_UQuickTweenManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickTweenManager"),
			Z_Registration_Info_UClass_UQuickTweenManager.InnerSingleton,
			StaticRegisterNativesUQuickTweenManager,
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
	return Z_Registration_Info_UClass_UQuickTweenManager.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickTweenManager_NoRegister()
{
	return UQuickTweenManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickTweenManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * World-scoped manager that updates active tweens each frame.\n * Implements a world subsystem to live with the UWorld and implements\n * FTickableGameObject so the engine will call Tick on this instance.\n *\n * Use UQuickTweenManager::Get(...) to retrieve the manager for a given\n * world context object.\n */" },
		{ "IncludePath", "QuickTweenManager.h" },
		{ "ModuleRelativePath", "Public/QuickTweenManager.h" },
		{ "ToolTip", "World-scoped manager that updates active tweens each frame.\nImplements a world subsystem to live with the UWorld and implements\nFTickableGameObject so the engine will call Tick on this instance.\n\nUse UQuickTweenManager::Get(...) to retrieve the manager for a given\nworld context object." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_QuickTweens_MetaData[] = {
		{ "Comment", "/** Array of active tweens managed by this subsystem. Transient so not serialized. */" },
		{ "ModuleRelativePath", "Public/QuickTweenManager.h" },
		{ "ToolTip", "Array of active tweens managed by this subsystem. Transient so not serialized." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickTweenManager constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_QuickTweens_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_QuickTweens;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UQuickTweenManager constinit property declarations *************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickTweenManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickTweenManager_Statics

// ********** Begin Class UQuickTweenManager Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickTweenManager_Statics::NewProp_QuickTweens_Inner = { "QuickTweens", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UQuickTweenManager_Statics::NewProp_QuickTweens = { "QuickTweens", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickTweenManager, QuickTweens), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QuickTweens_MetaData), NewProp_QuickTweens_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UQuickTweenManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenManager_Statics::NewProp_QuickTweens_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenManager_Statics::NewProp_QuickTweens,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenManager_Statics::PropPointers) < 2048);
// ********** End Class UQuickTweenManager Property Definitions ************************************
UObject* (*const Z_Construct_UClass_UQuickTweenManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UWorldSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickTweenManager_Statics::ClassParams = {
	&UQuickTweenManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UQuickTweenManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenManager_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickTweenManager_Statics::Class_MetaDataParams)
};
void UQuickTweenManager::StaticRegisterNativesUQuickTweenManager()
{
}
UClass* Z_Construct_UClass_UQuickTweenManager()
{
	if (!Z_Registration_Info_UClass_UQuickTweenManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickTweenManager.OuterSingleton, Z_Construct_UClass_UQuickTweenManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickTweenManager.OuterSingleton;
}
UQuickTweenManager::UQuickTweenManager() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickTweenManager);
UQuickTweenManager::~UQuickTweenManager() {}
// ********** End Class UQuickTweenManager *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenManager_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickTweenManager, UQuickTweenManager::StaticClass, TEXT("UQuickTweenManager"), &Z_Registration_Info_UClass_UQuickTweenManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickTweenManager), 1492469649U) },
	};
}; // Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenManager_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenManager_h__Script_QuickTween_3476369612{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenManager_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenManager_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
