// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickVectorTween.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickVectorTween() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVectorTween();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVectorTween_NoRegister();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickVectorTween Function GetCurrentValue *******************************
struct Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics
{
	struct QuickVectorTween_eventGetCurrentValue_Parms
	{
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the current interpolated FVector value. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVectorTween.h" },
		{ "ToolTip", "Get the current interpolated FVector value." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentValue constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentValue constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentValue Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickVectorTween_eventGetCurrentValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentValue Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickVectorTween, nullptr, "GetCurrentValue", 	Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::QuickVectorTween_eventGetCurrentValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::QuickVectorTween_eventGetCurrentValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickVectorTween::execGetCurrentValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetCurrentValue();
	P_NATIVE_END;
}
// ********** End Class UQuickVectorTween Function GetCurrentValue *********************************

// ********** Begin Class UQuickVectorTween Function GetEndValue ***********************************
struct Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics
{
	struct QuickVectorTween_eventGetEndValue_Parms
	{
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the ending FVector value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVectorTween.h" },
		{ "ToolTip", "Get the ending FVector value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEndValue constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEndValue constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEndValue Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickVectorTween_eventGetEndValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::PropPointers) < 2048);
// ********** End Function GetEndValue Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickVectorTween, nullptr, "GetEndValue", 	Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::QuickVectorTween_eventGetEndValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::QuickVectorTween_eventGetEndValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickVectorTween_GetEndValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickVectorTween_GetEndValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickVectorTween::execGetEndValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetEndValue();
	P_NATIVE_END;
}
// ********** End Class UQuickVectorTween Function GetEndValue *************************************

// ********** Begin Class UQuickVectorTween Function GetStartValue *********************************
struct Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics
{
	struct QuickVectorTween_eventGetStartValue_Parms
	{
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the starting FVector value. Set after the first tick */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVectorTween.h" },
		{ "ToolTip", "Get the starting FVector value. Set after the first tick" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetStartValue constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStartValue constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStartValue Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickVectorTween_eventGetStartValue_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::PropPointers) < 2048);
// ********** End Function GetStartValue Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickVectorTween, nullptr, "GetStartValue", 	Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::QuickVectorTween_eventGetStartValue_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::QuickVectorTween_eventGetStartValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickVectorTween_GetStartValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickVectorTween_GetStartValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickVectorTween::execGetStartValue)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetStartValue();
	P_NATIVE_END;
}
// ********** End Class UQuickVectorTween Function GetStartValue ***********************************

// ********** Begin Class UQuickVectorTween ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickVectorTween;
UClass* UQuickVectorTween::GetPrivateStaticClass()
{
	using TClass = UQuickVectorTween;
	if (!Z_Registration_Info_UClass_UQuickVectorTween.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickVectorTween"),
			Z_Registration_Info_UClass_UQuickVectorTween.InnerSingleton,
			StaticRegisterNativesUQuickVectorTween,
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
	return Z_Registration_Info_UClass_UQuickVectorTween.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickVectorTween_NoRegister()
{
	return UQuickVectorTween::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickVectorTween_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Tween class for interpolating between two FVector values over time.\n * Inherits from UQuickTweenBase and provides vector-specific tweening functionality.\n */" },
		{ "IncludePath", "Tweens/QuickVectorTween.h" },
		{ "ModuleRelativePath", "Public/Tweens/QuickVectorTween.h" },
		{ "ToolTip", "Tween class for interpolating between two FVector values over time.\nInherits from UQuickTweenBase and provides vector-specific tweening functionality." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickVectorTween constinit property declarations ************************
// ********** End Class UQuickVectorTween constinit property declarations **************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentValue"), .Pointer = &UQuickVectorTween::execGetCurrentValue },
		{ .NameUTF8 = UTF8TEXT("GetEndValue"), .Pointer = &UQuickVectorTween::execGetEndValue },
		{ .NameUTF8 = UTF8TEXT("GetStartValue"), .Pointer = &UQuickVectorTween::execGetStartValue },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickVectorTween_GetCurrentValue, "GetCurrentValue" }, // 4075934486
		{ &Z_Construct_UFunction_UQuickVectorTween_GetEndValue, "GetEndValue" }, // 242796566
		{ &Z_Construct_UFunction_UQuickVectorTween_GetStartValue, "GetStartValue" }, // 1456655555
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickVectorTween>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickVectorTween_Statics
UObject* (*const Z_Construct_UClass_UQuickVectorTween_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenBase,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickVectorTween_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickVectorTween_Statics::ClassParams = {
	&UQuickVectorTween::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickVectorTween_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickVectorTween_Statics::Class_MetaDataParams)
};
void UQuickVectorTween::StaticRegisterNativesUQuickVectorTween()
{
	UClass* Class = UQuickVectorTween::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickVectorTween_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickVectorTween()
{
	if (!Z_Registration_Info_UClass_UQuickVectorTween.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickVectorTween.OuterSingleton, Z_Construct_UClass_UQuickVectorTween_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickVectorTween.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickVectorTween);
UQuickVectorTween::~UQuickVectorTween() {}
// ********** End Class UQuickVectorTween **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVectorTween_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickVectorTween, UQuickVectorTween::StaticClass, TEXT("UQuickVectorTween"), &Z_Registration_Info_UClass_UQuickVectorTween, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickVectorTween), 3330036945U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVectorTween_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVectorTween_h__Script_QuickTween_4291308967{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVectorTween_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickVectorTween_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
