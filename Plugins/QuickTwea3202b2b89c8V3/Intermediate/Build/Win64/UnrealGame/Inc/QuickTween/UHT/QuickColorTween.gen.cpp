// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickColorTween.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickColorTween() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickColorTween();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickColorTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickColorTween Function GetCurrentValue ********************************
struct Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics
{
	struct QuickColorTween_eventGetCurrentValue_Parms
	{
		FColor ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the current interpolated FColor value. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickColorTween.h" },
		{ "ToolTip", "Get the current interpolated FColor value." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentValue constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentValue constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentValue Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickColorTween_eventGetCurrentValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentValue Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickColorTween, nullptr, "GetCurrentValue", 	Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::QuickColorTween_eventGetCurrentValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::QuickColorTween_eventGetCurrentValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickColorTween_GetCurrentValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickColorTween_GetCurrentValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickColorTween::execGetCurrentValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FColor*)Z_Param__Result=P_THIS->GetCurrentValue();
	P_NATIVE_END;
}
// ********** End Class UQuickColorTween Function GetCurrentValue **********************************

// ********** Begin Class UQuickColorTween Function GetEndValue ************************************
struct Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics
{
	struct QuickColorTween_eventGetEndValue_Parms
	{
		FColor ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the ending FColor value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickColorTween.h" },
		{ "ToolTip", "Get the ending FColor value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEndValue constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEndValue constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEndValue Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickColorTween_eventGetEndValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::PropPointers) < 2048);
// ********** End Function GetEndValue Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickColorTween, nullptr, "GetEndValue", 	Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::QuickColorTween_eventGetEndValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::QuickColorTween_eventGetEndValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickColorTween_GetEndValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickColorTween_GetEndValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickColorTween::execGetEndValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FColor*)Z_Param__Result=P_THIS->GetEndValue();
	P_NATIVE_END;
}
// ********** End Class UQuickColorTween Function GetEndValue **************************************

// ********** Begin Class UQuickColorTween Function GetStartValue **********************************
struct Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics
{
	struct QuickColorTween_eventGetStartValue_Parms
	{
		FColor ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the starting FColor value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickColorTween.h" },
		{ "ToolTip", "Get the starting FColor value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStartValue constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStartValue constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStartValue Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickColorTween_eventGetStartValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::PropPointers) < 2048);
// ********** End Function GetStartValue Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickColorTween, nullptr, "GetStartValue", 	Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::QuickColorTween_eventGetStartValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::QuickColorTween_eventGetStartValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickColorTween_GetStartValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickColorTween_GetStartValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickColorTween::execGetStartValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FColor*)Z_Param__Result=P_THIS->GetStartValue();
	P_NATIVE_END;
}
// ********** End Class UQuickColorTween Function GetStartValue ************************************

// ********** Begin Class UQuickColorTween *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickColorTween;
UClass* UQuickColorTween::GetPrivateStaticClass()
{
	using TClass = UQuickColorTween;
	if (!Z_Registration_Info_UClass_UQuickColorTween.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickColorTween"),
			Z_Registration_Info_UClass_UQuickColorTween.InnerSingleton,
			StaticRegisterNativesUQuickColorTween,
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
	return Z_Registration_Info_UClass_UQuickColorTween.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickColorTween_NoRegister()
{
	return UQuickColorTween::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickColorTween_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Tween class for interpolating between two FColor values over time.\n * Inherits from UQuickTweenBase and provides vector-specific tweening functionality.\n */" },
		{ "IncludePath", "Tweens/QuickColorTween.h" },
		{ "ModuleRelativePath", "Public/Tweens/QuickColorTween.h" },
		{ "ToolTip", "Tween class for interpolating between two FColor values over time.\nInherits from UQuickTweenBase and provides vector-specific tweening functionality." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickColorTween constinit property declarations *************************
// ********** End Class UQuickColorTween constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentValue"), .Pointer = &UQuickColorTween::execGetCurrentValue },
		{ .NameUTF8 = UTF8TEXT("GetEndValue"), .Pointer = &UQuickColorTween::execGetEndValue },
		{ .NameUTF8 = UTF8TEXT("GetStartValue"), .Pointer = &UQuickColorTween::execGetStartValue },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickColorTween_GetCurrentValue, "GetCurrentValue" }, // 2574594539
		{ &Z_Construct_UFunction_UQuickColorTween_GetEndValue, "GetEndValue" }, // 2813750223
		{ &Z_Construct_UFunction_UQuickColorTween_GetStartValue, "GetStartValue" }, // 121540605
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickColorTween>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickColorTween_Statics
UObject* (*const Z_Construct_UClass_UQuickColorTween_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenBase,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickColorTween_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickColorTween_Statics::ClassParams = {
	&UQuickColorTween::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickColorTween_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickColorTween_Statics::Class_MetaDataParams)
};
void UQuickColorTween::StaticRegisterNativesUQuickColorTween()
{
	UClass* Class = UQuickColorTween::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickColorTween_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickColorTween()
{
	if (!Z_Registration_Info_UClass_UQuickColorTween.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickColorTween.OuterSingleton, Z_Construct_UClass_UQuickColorTween_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickColorTween.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickColorTween);
UQuickColorTween::~UQuickColorTween() {}
// ********** End Class UQuickColorTween ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickColorTween_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickColorTween, UQuickColorTween::StaticClass, TEXT("UQuickColorTween"), &Z_Registration_Info_UClass_UQuickColorTween, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickColorTween), 2652536235U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickColorTween_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickColorTween_h__Script_QuickTween_1519876334{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickColorTween_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickColorTween_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
