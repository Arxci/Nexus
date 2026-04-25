// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonValues.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeCommonValues() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable_NoRegister();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenSpace();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenState();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FVectorSetter *********************************************************
struct Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventVectorSetter_Parms
	{
		FVector value;
		UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FVectorSetter constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_value;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FVectorSetter constinit property declarations ***************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FVectorSetter Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventVectorSetter_Parms, value), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_value_MetaData), NewProp_value_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventVectorSetter_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::NewProp_value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FVectorSetter Property Definitions **************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "VectorSetter__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::_Script_QuickTween_eventVectorSetter_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00520000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::_Script_QuickTween_eventVectorSetter_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FVectorSetter_DelegateWrapper(const FScriptDelegate& VectorSetter, FVector const& value, UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventVectorSetter_Parms
	{
		FVector value;
		UQuickTweenable* tween;
	};
	_Script_QuickTween_eventVectorSetter_Parms Parms;
	Parms.value=value;
	Parms.tween=tween;
	VectorSetter.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FVectorSetter ***********************************************************

// ********** Begin Delegate FRotatorSetter ********************************************************
struct Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventRotatorSetter_Parms
	{
		FRotator value;
		UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FRotatorSetter constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_value;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FRotatorSetter constinit property declarations **************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FRotatorSetter Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventRotatorSetter_Parms, value), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_value_MetaData), NewProp_value_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventRotatorSetter_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::NewProp_value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FRotatorSetter Property Definitions *************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "RotatorSetter__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::_Script_QuickTween_eventRotatorSetter_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00520000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::_Script_QuickTween_eventRotatorSetter_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FRotatorSetter_DelegateWrapper(const FScriptDelegate& RotatorSetter, FRotator const& value, UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventRotatorSetter_Parms
	{
		FRotator value;
		UQuickTweenable* tween;
	};
	_Script_QuickTween_eventRotatorSetter_Parms Parms;
	Parms.value=value;
	Parms.tween=tween;
	RotatorSetter.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FRotatorSetter **********************************************************

// ********** Begin Delegate FFloatSetter **********************************************************
struct Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventFloatSetter_Parms
	{
		float value;
		UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FFloatSetter constinit property declarations **************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FFloatSetter constinit property declarations ****************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FFloatSetter Property Definitions *************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventFloatSetter_Parms, value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_value_MetaData), NewProp_value_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventFloatSetter_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::NewProp_value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FFloatSetter Property Definitions ***************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "FloatSetter__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::_Script_QuickTween_eventFloatSetter_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::_Script_QuickTween_eventFloatSetter_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FFloatSetter_DelegateWrapper(const FScriptDelegate& FloatSetter, const float value, UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventFloatSetter_Parms
	{
		float value;
		UQuickTweenable* tween;
	};
	_Script_QuickTween_eventFloatSetter_Parms Parms;
	Parms.value=value;
	Parms.tween=tween;
	FloatSetter.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FFloatSetter ************************************************************

// ********** Begin Delegate FVector2DSetter *******************************************************
struct Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventVector2DSetter_Parms
	{
		FVector2D value;
		UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FVector2DSetter constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_value;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FVector2DSetter constinit property declarations *************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FVector2DSetter Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventVector2DSetter_Parms, value), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_value_MetaData), NewProp_value_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventVector2DSetter_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::NewProp_value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FVector2DSetter Property Definitions ************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "Vector2DSetter__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::_Script_QuickTween_eventVector2DSetter_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00520000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::_Script_QuickTween_eventVector2DSetter_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FVector2DSetter_DelegateWrapper(const FScriptDelegate& Vector2DSetter, FVector2D const& value, UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventVector2DSetter_Parms
	{
		FVector2D value;
		UQuickTweenable* tween;
	};
	_Script_QuickTween_eventVector2DSetter_Parms Parms;
	Parms.value=value;
	Parms.tween=tween;
	Vector2DSetter.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FVector2DSetter *********************************************************

// ********** Begin Delegate FColorSetter **********************************************************
struct Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventColorSetter_Parms
	{
		FColor value;
		UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FColorSetter constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_value;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FColorSetter constinit property declarations ****************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FColorSetter Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventColorSetter_Parms, value), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_value_MetaData), NewProp_value_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventColorSetter_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::NewProp_value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FColorSetter Property Definitions ***************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "ColorSetter__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::_Script_QuickTween_eventColorSetter_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00520000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::_Script_QuickTween_eventColorSetter_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FColorSetter_DelegateWrapper(const FScriptDelegate& ColorSetter, FColor const& value, UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventColorSetter_Parms
	{
		FColor value;
		UQuickTweenable* tween;
	};
	_Script_QuickTween_eventColorSetter_Parms Parms;
	Parms.value=value;
	Parms.tween=tween;
	ColorSetter.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FColorSetter ************************************************************

// ********** Begin Delegate FIntSetter ************************************************************
struct Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventIntSetter_Parms
	{
		int32 value;
		UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FIntSetter constinit property declarations ****************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_value;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FIntSetter constinit property declarations ******************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FIntSetter Property Definitions ***************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventIntSetter_Parms, value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_value_MetaData), NewProp_value_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventIntSetter_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::NewProp_value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FIntSetter Property Definitions *****************************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "IntSetter__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::_Script_QuickTween_eventIntSetter_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::_Script_QuickTween_eventIntSetter_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIntSetter_DelegateWrapper(const FScriptDelegate& IntSetter, const int32 value, UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventIntSetter_Parms
	{
		int32 value;
		UQuickTweenable* tween;
	};
	_Script_QuickTween_eventIntSetter_Parms Parms;
	Parms.value=value;
	Parms.tween=tween;
	IntSetter.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FIntSetter **************************************************************

// ********** Begin Delegate FQuickTweenableAction *************************************************
struct Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventQuickTweenableAction_Parms
	{
		UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FQuickTweenableAction constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FQuickTweenableAction constinit property declarations *******************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FQuickTweenableAction Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventQuickTweenableAction_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FQuickTweenableAction Property Definitions ******************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "QuickTweenableAction__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::_Script_QuickTween_eventQuickTweenableAction_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::_Script_QuickTween_eventQuickTweenableAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FQuickTweenableAction_DelegateWrapper(const FScriptDelegate& QuickTweenableAction, UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventQuickTweenableAction_Parms
	{
		UQuickTweenable* tween;
	};
	_Script_QuickTween_eventQuickTweenableAction_Parms Parms;
	Parms.tween=tween;
	QuickTweenableAction.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FQuickTweenableAction ***************************************************

// ********** Begin Delegate FQuickConstTweenableAction ********************************************
struct Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventQuickConstTweenableAction_Parms
	{
		const UQuickTweenable* tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tween_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FQuickConstTweenableAction constinit property declarations ************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FQuickConstTweenableAction constinit property declarations **************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FQuickConstTweenableAction Property Definitions ***********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventQuickConstTweenableAction_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tween_MetaData), NewProp_tween_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::NewProp_tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FQuickConstTweenableAction Property Definitions *************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "QuickConstTweenableAction__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::_Script_QuickTween_eventQuickConstTweenableAction_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::_Script_QuickTween_eventQuickConstTweenableAction_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FQuickConstTweenableAction_DelegateWrapper(const FScriptDelegate& QuickConstTweenableAction, const UQuickTweenable* tween)
{
	struct _Script_QuickTween_eventQuickConstTweenableAction_Parms
	{
		const UQuickTweenable* tween;
	};
	_Script_QuickTween_eventQuickConstTweenableAction_Parms Parms;
	Parms.tween=tween;
	QuickConstTweenableAction.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FQuickConstTweenableAction **********************************************

// ********** Begin Enum EQuickTweenSpace **********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EQuickTweenSpace;
static UEnum* EQuickTweenSpace_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EQuickTweenSpace.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EQuickTweenSpace.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_QuickTween_EQuickTweenSpace, (UObject*)Z_Construct_UPackage__Script_QuickTween(), TEXT("EQuickTweenSpace"));
	}
	return Z_Registration_Info_UEnum_EQuickTweenSpace.OuterSingleton;
}
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EQuickTweenSpace>()
{
	return EQuickTweenSpace_StaticEnum();
}
struct Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n *  Enum defining the space in which a QuickTween operates.\n */" },
		{ "LocalSpace.DisplayName", "Local Space" },
		{ "LocalSpace.Name", "EQuickTweenSpace::LocalSpace" },
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
		{ "ToolTip", "Enum defining the space in which a QuickTween operates." },
		{ "WorldSpace.DisplayName", "World Space" },
		{ "WorldSpace.Name", "EQuickTweenSpace::WorldSpace" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EQuickTweenSpace::WorldSpace", (int64)EQuickTweenSpace::WorldSpace },
		{ "EQuickTweenSpace::LocalSpace", (int64)EQuickTweenSpace::LocalSpace },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_QuickTween,
	nullptr,
	"EQuickTweenSpace",
	"EQuickTweenSpace",
	Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics::Enum_MetaDataParams), Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenSpace()
{
	if (!Z_Registration_Info_UEnum_EQuickTweenSpace.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EQuickTweenSpace.InnerSingleton, Z_Construct_UEnum_QuickTween_EQuickTweenSpace_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EQuickTweenSpace.InnerSingleton;
}
// ********** End Enum EQuickTweenSpace ************************************************************

// ********** Begin Enum EQuickTweenState **********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EQuickTweenState;
static UEnum* EQuickTweenState_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EQuickTweenState.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EQuickTweenState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_QuickTween_EQuickTweenState, (UObject*)Z_Construct_UPackage__Script_QuickTween(), TEXT("EQuickTweenState"));
	}
	return Z_Registration_Info_UEnum_EQuickTweenState.OuterSingleton;
}
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EQuickTweenState>()
{
	return EQuickTweenState_StaticEnum();
}
struct Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n *  Enum defining the current state of a QuickTween.\n */" },
		{ "Complete.Name", "EQuickTweenState::Complete" },
		{ "Idle.Name", "EQuickTweenState::Idle" },
		{ "Kill.Name", "EQuickTweenState::Kill" },
		{ "ModuleRelativePath", "Public/Utils/CommonValues.h" },
		{ "Pause.Name", "EQuickTweenState::Pause" },
		{ "Play.Name", "EQuickTweenState::Play" },
		{ "ToolTip", "Enum defining the current state of a QuickTween." },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EQuickTweenState::Idle", (int64)EQuickTweenState::Idle },
		{ "EQuickTweenState::Play", (int64)EQuickTweenState::Play },
		{ "EQuickTweenState::Pause", (int64)EQuickTweenState::Pause },
		{ "EQuickTweenState::Complete", (int64)EQuickTweenState::Complete },
		{ "EQuickTweenState::Kill", (int64)EQuickTweenState::Kill },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_QuickTween,
	nullptr,
	"EQuickTweenState",
	"EQuickTweenState",
	Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics::Enum_MetaDataParams), Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenState()
{
	if (!Z_Registration_Info_UEnum_EQuickTweenState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EQuickTweenState.InnerSingleton, Z_Construct_UEnum_QuickTween_EQuickTweenState_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EQuickTweenState.InnerSingleton;
}
// ********** End Enum EQuickTweenState ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h__Script_QuickTween_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EQuickTweenSpace_StaticEnum, TEXT("EQuickTweenSpace"), &Z_Registration_Info_UEnum_EQuickTweenSpace, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2719769293U) },
		{ EQuickTweenState_StaticEnum, TEXT("EQuickTweenState"), &Z_Registration_Info_UEnum_EQuickTweenState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2679500786U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h__Script_QuickTween_692370815{
	TEXT("/Script/QuickTween"),
	nullptr, 0,
	nullptr, 0,
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h__Script_QuickTween_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h__Script_QuickTween_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
