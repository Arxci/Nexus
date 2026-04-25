// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickRotatorTween.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickRotatorTween() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickRotatorTween();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickRotatorTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickRotatorTween Function GetCurrentValue ******************************
struct Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics
{
	struct QuickRotatorTween_eventGetCurrentValue_Parms
	{
		FRotator ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the current interpolated FRotator value. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickRotatorTween.h" },
		{ "ToolTip", "Get the current interpolated FRotator value." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentValue constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentValue constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentValue Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickRotatorTween_eventGetCurrentValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentValue Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickRotatorTween, nullptr, "GetCurrentValue", 	Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::QuickRotatorTween_eventGetCurrentValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::QuickRotatorTween_eventGetCurrentValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickRotatorTween::execGetCurrentValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FRotator*)Z_Param__Result=P_THIS->GetCurrentValue();
	P_NATIVE_END;
}
// ********** End Class UQuickRotatorTween Function GetCurrentValue ********************************

// ********** Begin Class UQuickRotatorTween Function GetEndValue **********************************
struct Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics
{
	struct QuickRotatorTween_eventGetEndValue_Parms
	{
		FRotator ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the ending FRotator value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickRotatorTween.h" },
		{ "ToolTip", "Get the ending FRotator value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEndValue constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEndValue constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEndValue Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickRotatorTween_eventGetEndValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::PropPointers) < 2048);
// ********** End Function GetEndValue Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickRotatorTween, nullptr, "GetEndValue", 	Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::QuickRotatorTween_eventGetEndValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::QuickRotatorTween_eventGetEndValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickRotatorTween_GetEndValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickRotatorTween_GetEndValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickRotatorTween::execGetEndValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FRotator*)Z_Param__Result=P_THIS->GetEndValue();
	P_NATIVE_END;
}
// ********** End Class UQuickRotatorTween Function GetEndValue ************************************

// ********** Begin Class UQuickRotatorTween Function GetStartValue ********************************
struct Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics
{
	struct QuickRotatorTween_eventGetStartValue_Parms
	{
		FRotator ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the starting FRotator value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickRotatorTween.h" },
		{ "ToolTip", "Get the starting FRotator value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStartValue constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStartValue constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStartValue Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickRotatorTween_eventGetStartValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::PropPointers) < 2048);
// ********** End Function GetStartValue Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickRotatorTween, nullptr, "GetStartValue", 	Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::QuickRotatorTween_eventGetStartValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::QuickRotatorTween_eventGetStartValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickRotatorTween_GetStartValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickRotatorTween_GetStartValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickRotatorTween::execGetStartValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FRotator*)Z_Param__Result=P_THIS->GetStartValue();
	P_NATIVE_END;
}
// ********** End Class UQuickRotatorTween Function GetStartValue **********************************

// ********** Begin Class UQuickRotatorTween *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickRotatorTween;
UClass* UQuickRotatorTween::GetPrivateStaticClass()
{
	using TClass = UQuickRotatorTween;
	if (!Z_Registration_Info_UClass_UQuickRotatorTween.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickRotatorTween"),
			Z_Registration_Info_UClass_UQuickRotatorTween.InnerSingleton,
			StaticRegisterNativesUQuickRotatorTween,
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
	return Z_Registration_Info_UClass_UQuickRotatorTween.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickRotatorTween_NoRegister()
{
	return UQuickRotatorTween::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickRotatorTween_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Tween class for interpolating between two FRotator values over time.\n * Inherits from UQuickTweenBase and provides rotator-specific tweening functionality.\n */" },
		{ "IncludePath", "Tweens/QuickRotatorTween.h" },
		{ "ModuleRelativePath", "Public/Tweens/QuickRotatorTween.h" },
		{ "ToolTip", "Tween class for interpolating between two FRotator values over time.\nInherits from UQuickTweenBase and provides rotator-specific tweening functionality." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickRotatorTween constinit property declarations ***********************
// ********** End Class UQuickRotatorTween constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentValue"), .Pointer = &UQuickRotatorTween::execGetCurrentValue },
		{ .NameUTF8 = UTF8TEXT("GetEndValue"), .Pointer = &UQuickRotatorTween::execGetEndValue },
		{ .NameUTF8 = UTF8TEXT("GetStartValue"), .Pointer = &UQuickRotatorTween::execGetStartValue },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickRotatorTween_GetCurrentValue, "GetCurrentValue" }, // 2710971928
		{ &Z_Construct_UFunction_UQuickRotatorTween_GetEndValue, "GetEndValue" }, // 3304599610
		{ &Z_Construct_UFunction_UQuickRotatorTween_GetStartValue, "GetStartValue" }, // 2351067219
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickRotatorTween>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickRotatorTween_Statics
UObject* (*const Z_Construct_UClass_UQuickRotatorTween_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenBase,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickRotatorTween_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickRotatorTween_Statics::ClassParams = {
	&UQuickRotatorTween::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickRotatorTween_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickRotatorTween_Statics::Class_MetaDataParams)
};
void UQuickRotatorTween::StaticRegisterNativesUQuickRotatorTween()
{
	UClass* Class = UQuickRotatorTween::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickRotatorTween_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickRotatorTween()
{
	if (!Z_Registration_Info_UClass_UQuickRotatorTween.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickRotatorTween.OuterSingleton, Z_Construct_UClass_UQuickRotatorTween_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickRotatorTween.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickRotatorTween);
UQuickRotatorTween::~UQuickRotatorTween() {}
// ********** End Class UQuickRotatorTween *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickRotatorTween_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickRotatorTween, UQuickRotatorTween::StaticClass, TEXT("UQuickRotatorTween"), &Z_Registration_Info_UClass_UQuickRotatorTween, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickRotatorTween), 4006402181U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickRotatorTween_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickRotatorTween_h__Script_QuickTween_2763291101{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickRotatorTween_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickRotatorTween_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
