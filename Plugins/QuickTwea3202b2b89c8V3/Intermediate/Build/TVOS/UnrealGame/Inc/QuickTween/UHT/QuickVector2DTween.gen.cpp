// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickVector2DTween.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickVector2DTween() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVector2DTween();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVector2DTween_NoRegister();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickVector2DTween Function GetCurrentValue *****************************
struct Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics
{
	struct QuickVector2DTween_eventGetCurrentValue_Parms
	{
		FVector2D ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the current interpolated FVector2D value. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVector2DTween.h" },
		{ "ToolTip", "Get the current interpolated FVector2D value." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentValue constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentValue constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentValue Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickVector2DTween_eventGetCurrentValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentValue Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickVector2DTween, nullptr, "GetCurrentValue", 	Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::QuickVector2DTween_eventGetCurrentValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::QuickVector2DTween_eventGetCurrentValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickVector2DTween::execGetCurrentValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector2D*)Z_Param__Result=P_THIS->GetCurrentValue();
	P_NATIVE_END;
}
// ********** End Class UQuickVector2DTween Function GetCurrentValue *******************************

// ********** Begin Class UQuickVector2DTween Function GetEndValue *********************************
struct Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics
{
	struct QuickVector2DTween_eventGetEndValue_Parms
	{
		FVector2D ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the ending FVector2D value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVector2DTween.h" },
		{ "ToolTip", "Get the ending FVector2D value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEndValue constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEndValue constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEndValue Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickVector2DTween_eventGetEndValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::PropPointers) < 2048);
// ********** End Function GetEndValue Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickVector2DTween, nullptr, "GetEndValue", 	Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::QuickVector2DTween_eventGetEndValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::QuickVector2DTween_eventGetEndValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickVector2DTween_GetEndValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickVector2DTween_GetEndValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickVector2DTween::execGetEndValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector2D*)Z_Param__Result=P_THIS->GetEndValue();
	P_NATIVE_END;
}
// ********** End Class UQuickVector2DTween Function GetEndValue ***********************************

// ********** Begin Class UQuickVector2DTween Function GetStartValue *******************************
struct Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics
{
	struct QuickVector2DTween_eventGetStartValue_Parms
	{
		FVector2D ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the starting FVector2D value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVector2DTween.h" },
		{ "ToolTip", "Get the starting FVector2D value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStartValue constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStartValue constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStartValue Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickVector2DTween_eventGetStartValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::PropPointers) < 2048);
// ********** End Function GetStartValue Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickVector2DTween, nullptr, "GetStartValue", 	Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::QuickVector2DTween_eventGetStartValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::QuickVector2DTween_eventGetStartValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickVector2DTween_GetStartValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickVector2DTween_GetStartValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickVector2DTween::execGetStartValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector2D*)Z_Param__Result=P_THIS->GetStartValue();
	P_NATIVE_END;
}
// ********** End Class UQuickVector2DTween Function GetStartValue *********************************

// ********** Begin Class UQuickVector2DTween ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickVector2DTween;
UClass* UQuickVector2DTween::GetPrivateStaticClass()
{
	using TClass = UQuickVector2DTween;
	if (!Z_Registration_Info_UClass_UQuickVector2DTween.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickVector2DTween"),
			Z_Registration_Info_UClass_UQuickVector2DTween.InnerSingleton,
			StaticRegisterNativesUQuickVector2DTween,
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
	return Z_Registration_Info_UClass_UQuickVector2DTween.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickVector2DTween_NoRegister()
{
	return UQuickVector2DTween::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickVector2DTween_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Tween class for interpolating between two FVector2D values over time.\n * Inherits from UQuickTweenBase and provides vector-specific tweening functionality.\n */" },
		{ "IncludePath", "Tweens/QuickVector2DTween.h" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVector2DTween.h" },
		{ "ToolTip", "Tween class for interpolating between two FVector2D values over time.\nInherits from UQuickTweenBase and provides vector-specific tweening functionality." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickVector2DTween constinit property declarations **********************
// ********** End Class UQuickVector2DTween constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentValue"), .Pointer = &UQuickVector2DTween::execGetCurrentValue },
		{ .NameUTF8 = UTF8TEXT("GetEndValue"), .Pointer = &UQuickVector2DTween::execGetEndValue },
		{ .NameUTF8 = UTF8TEXT("GetStartValue"), .Pointer = &UQuickVector2DTween::execGetStartValue },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickVector2DTween_GetCurrentValue, "GetCurrentValue" }, // 591607235
		{ &Z_Construct_UFunction_UQuickVector2DTween_GetEndValue, "GetEndValue" }, // 2744127339
		{ &Z_Construct_UFunction_UQuickVector2DTween_GetStartValue, "GetStartValue" }, // 2112794474
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickVector2DTween>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickVector2DTween_Statics
UObject* (*const Z_Construct_UClass_UQuickVector2DTween_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenBase,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickVector2DTween_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickVector2DTween_Statics::ClassParams = {
	&UQuickVector2DTween::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickVector2DTween_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickVector2DTween_Statics::Class_MetaDataParams)
};
void UQuickVector2DTween::StaticRegisterNativesUQuickVector2DTween()
{
	UClass* Class = UQuickVector2DTween::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickVector2DTween_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickVector2DTween()
{
	if (!Z_Registration_Info_UClass_UQuickVector2DTween.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickVector2DTween.OuterSingleton, Z_Construct_UClass_UQuickVector2DTween_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickVector2DTween.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickVector2DTween);
UQuickVector2DTween::~UQuickVector2DTween() {}
// ********** End Class UQuickVector2DTween ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVector2DTween_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickVector2DTween, UQuickVector2DTween::StaticClass, TEXT("UQuickVector2DTween"), &Z_Registration_Info_UClass_UQuickVector2DTween, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickVector2DTween), 401946480U) },
	};
}; // Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVector2DTween_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVector2DTween_h__Script_QuickTween_2735413900{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVector2DTween_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVector2DTween_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
