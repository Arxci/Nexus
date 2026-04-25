// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickFloatTween.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickFloatTween() {}

// ********** Begin Cross Module References ********************************************************
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickFloatTween();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickFloatTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickFloatTween Function GetCurrentValue ********************************
struct Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics
{
	struct QuickFloatTween_eventGetCurrentValue_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the current interpolated float value. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickFloatTween.h" },
		{ "ToolTip", "Get the current interpolated float value." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentValue constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentValue constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentValue Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickFloatTween_eventGetCurrentValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentValue Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickFloatTween, nullptr, "GetCurrentValue", 	Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::QuickFloatTween_eventGetCurrentValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::QuickFloatTween_eventGetCurrentValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickFloatTween::execGetCurrentValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetCurrentValue();
	P_NATIVE_END;
}
// ********** End Class UQuickFloatTween Function GetCurrentValue **********************************

// ********** Begin Class UQuickFloatTween Function GetEndValue ************************************
struct Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics
{
	struct QuickFloatTween_eventGetEndValue_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the ending float value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickFloatTween.h" },
		{ "ToolTip", "Get the ending float value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEndValue constinit property declarations ***************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEndValue constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEndValue Property Definitions **************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickFloatTween_eventGetEndValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::PropPointers) < 2048);
// ********** End Function GetEndValue Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickFloatTween, nullptr, "GetEndValue", 	Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::QuickFloatTween_eventGetEndValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::QuickFloatTween_eventGetEndValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickFloatTween_GetEndValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickFloatTween_GetEndValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickFloatTween::execGetEndValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetEndValue();
	P_NATIVE_END;
}
// ********** End Class UQuickFloatTween Function GetEndValue **************************************

// ********** Begin Class UQuickFloatTween Function GetStartValue **********************************
struct Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics
{
	struct QuickFloatTween_eventGetStartValue_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the starting float value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickFloatTween.h" },
		{ "ToolTip", "Get the starting float value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStartValue constinit property declarations *************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStartValue constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStartValue Property Definitions ************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickFloatTween_eventGetStartValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::PropPointers) < 2048);
// ********** End Function GetStartValue Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickFloatTween, nullptr, "GetStartValue", 	Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::QuickFloatTween_eventGetStartValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::QuickFloatTween_eventGetStartValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickFloatTween_GetStartValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickFloatTween_GetStartValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickFloatTween::execGetStartValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetStartValue();
	P_NATIVE_END;
}
// ********** End Class UQuickFloatTween Function GetStartValue ************************************

// ********** Begin Class UQuickFloatTween *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickFloatTween;
UClass* UQuickFloatTween::GetPrivateStaticClass()
{
	using TClass = UQuickFloatTween;
	if (!Z_Registration_Info_UClass_UQuickFloatTween.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickFloatTween"),
			Z_Registration_Info_UClass_UQuickFloatTween.InnerSingleton,
			StaticRegisterNativesUQuickFloatTween,
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
	return Z_Registration_Info_UClass_UQuickFloatTween.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickFloatTween_NoRegister()
{
	return UQuickFloatTween::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickFloatTween_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Tween class for interpolating between two FVector values over time.\n * Inherits from UQuickTweenBase and provides vector-specific tweening functionality.\n */" },
		{ "IncludePath", "Tweens/QuickFloatTween.h" },
		{ "ModuleRelativePath", "Public/Tweens/QuickFloatTween.h" },
		{ "ToolTip", "Tween class for interpolating between two FVector values over time.\nInherits from UQuickTweenBase and provides vector-specific tweening functionality." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickFloatTween constinit property declarations *************************
// ********** End Class UQuickFloatTween constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentValue"), .Pointer = &UQuickFloatTween::execGetCurrentValue },
		{ .NameUTF8 = UTF8TEXT("GetEndValue"), .Pointer = &UQuickFloatTween::execGetEndValue },
		{ .NameUTF8 = UTF8TEXT("GetStartValue"), .Pointer = &UQuickFloatTween::execGetStartValue },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickFloatTween_GetCurrentValue, "GetCurrentValue" }, // 1779857846
		{ &Z_Construct_UFunction_UQuickFloatTween_GetEndValue, "GetEndValue" }, // 877466917
		{ &Z_Construct_UFunction_UQuickFloatTween_GetStartValue, "GetStartValue" }, // 3219395724
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickFloatTween>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickFloatTween_Statics
UObject* (*const Z_Construct_UClass_UQuickFloatTween_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenBase,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickFloatTween_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickFloatTween_Statics::ClassParams = {
	&UQuickFloatTween::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickFloatTween_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickFloatTween_Statics::Class_MetaDataParams)
};
void UQuickFloatTween::StaticRegisterNativesUQuickFloatTween()
{
	UClass* Class = UQuickFloatTween::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickFloatTween_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickFloatTween()
{
	if (!Z_Registration_Info_UClass_UQuickFloatTween.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickFloatTween.OuterSingleton, Z_Construct_UClass_UQuickFloatTween_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickFloatTween.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickFloatTween);
UQuickFloatTween::~UQuickFloatTween() {}
// ********** End Class UQuickFloatTween ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickFloatTween_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickFloatTween, UQuickFloatTween::StaticClass, TEXT("UQuickFloatTween"), &Z_Registration_Info_UClass_UQuickFloatTween, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickFloatTween), 509798710U) },
	};
}; // Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickFloatTween_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickFloatTween_h__Script_QuickTween_2165379689{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickFloatTween_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickFloatTween_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
