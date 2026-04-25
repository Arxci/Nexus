// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickTweenable.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickTweenable() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable_NoRegister();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EEaseType();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_ELoopType();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickTweenable Function Complete ****************************************
struct Z_Construct_UFunction_UQuickTweenable_Complete_Statics
{
	struct QuickTweenable_eventComplete_Parms
	{
		bool bSnapToEnd;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Control" },
		{ "Comment", "/** Immediately complete the tween.\n\x09 *  If the tween is reversed bSnapToEnd is inverted.\n\x09 * @param bSnapToEnd If true, snap properties to final state when completing.\n\x09 */" },
		{ "CPP_Default_bSnapToEnd", "true" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Immediately complete the tween.\nIf the tween is reversed bSnapToEnd is inverted.\n@param bSnapToEnd If true, snap properties to final state when completing." },
	};
#endif // WITH_METADATA

// ********** Begin Function Complete constinit property declarations ******************************
	static void NewProp_bSnapToEnd_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSnapToEnd;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Complete constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Complete Property Definitions *****************************************
void Z_Construct_UFunction_UQuickTweenable_Complete_Statics::NewProp_bSnapToEnd_SetBit(void* Obj)
{
	((QuickTweenable_eventComplete_Parms*)Obj)->bSnapToEnd = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenable_Complete_Statics::NewProp_bSnapToEnd = { "bSnapToEnd", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenable_eventComplete_Parms), &Z_Construct_UFunction_UQuickTweenable_Complete_Statics::NewProp_bSnapToEnd_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_Complete_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_Complete_Statics::NewProp_bSnapToEnd,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Complete_Statics::PropPointers) < 2048);
// ********** End Function Complete Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_Complete_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "Complete", 	Z_Construct_UFunction_UQuickTweenable_Complete_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Complete_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_Complete_Statics::QuickTweenable_eventComplete_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Complete_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_Complete_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_Complete_Statics::QuickTweenable_eventComplete_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_Complete()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_Complete_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execComplete)
{
	P_GET_UBOOL(Z_Param_bSnapToEnd);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Complete(Z_Param_bSnapToEnd);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function Complete ******************************************

// ********** Begin Class UQuickTweenable Function GetAutoKill *************************************
struct Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics
{
	struct QuickTweenable_eventGetAutoKill_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Returns whether this tween will be removed automatically after completion. */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Returns whether this tween will be removed automatically after completion." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAutoKill constinit property declarations ***************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAutoKill constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAutoKill Property Definitions **************************************
void Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((QuickTweenable_eventGetAutoKill_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenable_eventGetAutoKill_Parms), &Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::PropPointers) < 2048);
// ********** End Function GetAutoKill Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetAutoKill", 	Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::QuickTweenable_eventGetAutoKill_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::QuickTweenable_eventGetAutoKill_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetAutoKill()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetAutoKill_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetAutoKill)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetAutoKill();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetAutoKill ***************************************

// ********** Begin Class UQuickTweenable Function GetCurrentLoop **********************************
struct Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics
{
	struct QuickTweenable_eventGetCurrentLoop_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the current loop index (0-based) the tween is on.\n\x09 * @return 0 for the first loop, 1 for the second, etc.\n\x09 */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the current loop index (0-based) the tween is on.\n@return 0 for the first loop, 1 for the second, etc." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentLoop constinit property declarations ************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentLoop constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentLoop Property Definitions ***********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetCurrentLoop_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::PropPointers) < 2048);
// ********** End Function GetCurrentLoop Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetCurrentLoop", 	Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::QuickTweenable_eventGetCurrentLoop_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::QuickTweenable_eventGetCurrentLoop_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetCurrentLoop)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCurrentLoop();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetCurrentLoop ************************************

// ********** Begin Class UQuickTweenable Function GetEaseCurve ************************************
struct Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics
{
	struct QuickTweenable_eventGetEaseCurve_Parms
	{
		UCurveFloat* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the custom easing curve used by the tween, if any.\n\x09 * @return Pointer to a UCurveFloat or nullptr if not set.\n\x09 */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the custom easing curve used by the tween, if any.\n@return Pointer to a UCurveFloat or nullptr if not set." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEaseCurve constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEaseCurve constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEaseCurve Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetEaseCurve_Parms, ReturnValue), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::PropPointers) < 2048);
// ********** End Function GetEaseCurve Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetEaseCurve", 	Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::QuickTweenable_eventGetEaseCurve_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::QuickTweenable_eventGetEaseCurve_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetEaseCurve()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetEaseCurve_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetEaseCurve)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UCurveFloat**)Z_Param__Result=P_THIS->GetEaseCurve();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetEaseCurve **************************************

// ********** Begin Class UQuickTweenable Function GetEaseType *************************************
struct Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics
{
	struct QuickTweenable_eventGetEaseType_Parms
	{
		EEaseType ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the easing function type used by this tween. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the easing function type used by this tween." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetEaseType constinit property declarations ***************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEaseType constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEaseType Property Definitions **************************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetEaseType_Parms, ReturnValue), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::PropPointers) < 2048);
// ********** End Function GetEaseType Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetEaseType", 	Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::QuickTweenable_eventGetEaseType_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::QuickTweenable_eventGetEaseType_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetEaseType()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetEaseType_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetEaseType)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EEaseType*)Z_Param__Result=P_THIS->GetEaseType();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetEaseType ***************************************

// ********** Begin Class UQuickTweenable Function GetElapsedTime **********************************
struct Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics
{
	struct QuickTweenable_eventGetElapsedTime_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the total elapsed time since the tween started (in seconds). */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the total elapsed time since the tween started (in seconds)." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetElapsedTime constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetElapsedTime constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetElapsedTime Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetElapsedTime_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::PropPointers) < 2048);
// ********** End Function GetElapsedTime Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetElapsedTime", 	Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::QuickTweenable_eventGetElapsedTime_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::QuickTweenable_eventGetElapsedTime_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetElapsedTime()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetElapsedTime_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetElapsedTime)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetElapsedTime();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetElapsedTime ************************************

// ********** Begin Class UQuickTweenable Function GetIsCompleted **********************************
struct Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics
{
	struct QuickTweenable_eventGetIsCompleted_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Check whether the tween has reached its completion state. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Check whether the tween has reached its completion state." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetIsCompleted constinit property declarations ************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetIsCompleted constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetIsCompleted Property Definitions ***********************************
void Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((QuickTweenable_eventGetIsCompleted_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenable_eventGetIsCompleted_Parms), &Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::PropPointers) < 2048);
// ********** End Function GetIsCompleted Property Definitions *************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetIsCompleted", 	Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::QuickTweenable_eventGetIsCompleted_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::QuickTweenable_eventGetIsCompleted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetIsCompleted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetIsCompleted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetIsCompleted)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetIsCompleted();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetIsCompleted ************************************

// ********** Begin Class UQuickTweenable Function GetIsPendingKill ********************************
struct Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics
{
	struct QuickTweenable_eventGetIsPendingKill_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Query whether this tween is pending removal from the manager.\n\x09 * @return True if the tween is pending kill, false otherwise.\n\x09 */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Query whether this tween is pending removal from the manager.\n@return True if the tween is pending kill, false otherwise." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetIsPendingKill constinit property declarations **********************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetIsPendingKill constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetIsPendingKill Property Definitions *********************************
void Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((QuickTweenable_eventGetIsPendingKill_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenable_eventGetIsPendingKill_Parms), &Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::PropPointers) < 2048);
// ********** End Function GetIsPendingKill Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetIsPendingKill", 	Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::QuickTweenable_eventGetIsPendingKill_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::QuickTweenable_eventGetIsPendingKill_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetIsPendingKill)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetIsPendingKill();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetIsPendingKill **********************************

// ********** Begin Class UQuickTweenable Function GetIsPlaying ************************************
struct Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics
{
	struct QuickTweenable_eventGetIsPlaying_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Check if the tween is currently playing.\n\x09 * @return True when playing; false when paused or stopped.\n\x09 */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Check if the tween is currently playing.\n@return True when playing; false when paused or stopped." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetIsPlaying constinit property declarations **************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetIsPlaying constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetIsPlaying Property Definitions *************************************
void Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((QuickTweenable_eventGetIsPlaying_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenable_eventGetIsPlaying_Parms), &Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::PropPointers) < 2048);
// ********** End Function GetIsPlaying Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetIsPlaying", 	Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::QuickTweenable_eventGetIsPlaying_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::QuickTweenable_eventGetIsPlaying_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetIsPlaying()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetIsPlaying_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetIsPlaying)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetIsPlaying();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetIsPlaying **************************************

// ********** Begin Class UQuickTweenable Function GetIsReversed ***********************************
struct Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics
{
	struct QuickTweenable_eventGetIsReversed_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Returns true if the tween's reversed flag is set (affects playback direction). */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Returns true if the tween's reversed flag is set (affects playback direction)." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetIsReversed constinit property declarations *************************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetIsReversed constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetIsReversed Property Definitions ************************************
void Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((QuickTweenable_eventGetIsReversed_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenable_eventGetIsReversed_Parms), &Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::PropPointers) < 2048);
// ********** End Function GetIsReversed Property Definitions **************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetIsReversed", 	Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::QuickTweenable_eventGetIsReversed_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::QuickTweenable_eventGetIsReversed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetIsReversed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetIsReversed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetIsReversed)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetIsReversed();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetIsReversed *************************************

// ********** Begin Class UQuickTweenable Function GetLoopDuration *********************************
struct Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics
{
	struct QuickTweenable_eventGetLoopDuration_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the configured duration of the loop in seconds. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the configured duration of the loop in seconds." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetLoopDuration constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetLoopDuration constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetLoopDuration Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetLoopDuration_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::PropPointers) < 2048);
// ********** End Function GetLoopDuration Property Definitions ************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetLoopDuration", 	Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::QuickTweenable_eventGetLoopDuration_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::QuickTweenable_eventGetLoopDuration_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetLoopDuration()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetLoopDuration_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetLoopDuration)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetLoopDuration();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetLoopDuration ***********************************

// ********** Begin Class UQuickTweenable Function GetLoops ****************************************
struct Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics
{
	struct QuickTweenable_eventGetLoops_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the configured number of loops for this tween (-1 for infinite if supported). */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the configured number of loops for this tween (-1 for infinite if supported)." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetLoops constinit property declarations ******************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetLoops constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetLoops Property Definitions *****************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetLoops_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::PropPointers) < 2048);
// ********** End Function GetLoops Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetLoops", 	Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::QuickTweenable_eventGetLoops_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::QuickTweenable_eventGetLoops_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetLoops()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetLoops_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetLoops)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetLoops();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetLoops ******************************************

// ********** Begin Class UQuickTweenable Function GetLoopType *************************************
struct Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics
{
	struct QuickTweenable_eventGetLoopType_Parms
	{
		ELoopType ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the loop behavior used when the tween repeats (e.g., Restart, Yoyo). */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the loop behavior used when the tween repeats (e.g., Restart, Yoyo)." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetLoopType constinit property declarations ***************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetLoopType constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetLoopType Property Definitions **************************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetLoopType_Parms, ReturnValue), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::PropPointers) < 2048);
// ********** End Function GetLoopType Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetLoopType", 	Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::QuickTweenable_eventGetLoopType_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::QuickTweenable_eventGetLoopType_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetLoopType()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetLoopType_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetLoopType)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ELoopType*)Z_Param__Result=P_THIS->GetLoopType();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetLoopType ***************************************

// ********** Begin Class UQuickTweenable Function GetShouldPlayWhilePaused ************************
struct Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics
{
	struct QuickTweenable_eventGetShouldPlayWhilePaused_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Whether the tween should continue running even when the game is paused. */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Whether the tween should continue running even when the game is paused." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetShouldPlayWhilePaused constinit property declarations **************
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetShouldPlayWhilePaused constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetShouldPlayWhilePaused Property Definitions *************************
void Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((QuickTweenable_eventGetShouldPlayWhilePaused_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenable_eventGetShouldPlayWhilePaused_Parms), &Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::PropPointers) < 2048);
// ********** End Function GetShouldPlayWhilePaused Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetShouldPlayWhilePaused", 	Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::QuickTweenable_eventGetShouldPlayWhilePaused_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::QuickTweenable_eventGetShouldPlayWhilePaused_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetShouldPlayWhilePaused)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetShouldPlayWhilePaused();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetShouldPlayWhilePaused **************************

// ********** Begin Class UQuickTweenable Function GetTimeScale ************************************
struct Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics
{
	struct QuickTweenable_eventGetTimeScale_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the current time scale applied to the tween (1.0 = normal speed). */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the current time scale applied to the tween (1.0 = normal speed)." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetTimeScale constinit property declarations **************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTimeScale constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTimeScale Property Definitions *************************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetTimeScale_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::PropPointers) < 2048);
// ********** End Function GetTimeScale Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetTimeScale", 	Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::QuickTweenable_eventGetTimeScale_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::QuickTweenable_eventGetTimeScale_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetTimeScale()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetTimeScale_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetTimeScale)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetTimeScale();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetTimeScale **************************************

// ********** Begin Class UQuickTweenable Function GetTotalDuration ********************************
struct Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics
{
	struct QuickTweenable_eventGetTotalDuration_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the total duration of the whole tween (max value for infinite) */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the total duration of the whole tween (max value for infinite)" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetTotalDuration constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTotalDuration constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTotalDuration Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetTotalDuration_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::PropPointers) < 2048);
// ********** End Function GetTotalDuration Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetTotalDuration", 	Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::QuickTweenable_eventGetTotalDuration_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::QuickTweenable_eventGetTotalDuration_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetTotalDuration()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetTotalDuration_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetTotalDuration)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetTotalDuration();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetTotalDuration **********************************

// ********** Begin Class UQuickTweenable Function GetTweenTag *************************************
struct Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics
{
	struct QuickTweenable_eventGetTweenTag_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/** Get the user-assigned tag for this tween. Useful for identification and grouping. */" },
		{ "Keywords", "Tween" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Get the user-assigned tag for this tween. Useful for identification and grouping." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetTweenTag constinit property declarations ***************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTweenTag constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTweenTag Property Definitions **************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenable_eventGetTweenTag_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::PropPointers) < 2048);
// ********** End Function GetTweenTag Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "GetTweenTag", 	Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::QuickTweenable_eventGetTweenTag_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::QuickTweenable_eventGetTweenTag_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenable_GetTweenTag()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_GetTweenTag_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execGetTweenTag)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetTweenTag();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function GetTweenTag ***************************************

// ********** Begin Class UQuickTweenable Function Kill ********************************************
struct Z_Construct_UFunction_UQuickTweenable_Kill_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Control" },
		{ "Comment", "/** Forcefully kill the tween and mark it for removal.\n\x09 */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Forcefully kill the tween and mark it for removal." },
	};
#endif // WITH_METADATA

// ********** Begin Function Kill constinit property declarations **********************************
// ********** End Function Kill constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_Kill_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "Kill", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Kill_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_Kill_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UQuickTweenable_Kill()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_Kill_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execKill)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Kill();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function Kill **********************************************

// ********** Begin Class UQuickTweenable Function Pause *******************************************
struct Z_Construct_UFunction_UQuickTweenable_Pause_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Control" },
		{ "Comment", "/** Pause playback of the tween.\n\x09 */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Pause playback of the tween." },
	};
#endif // WITH_METADATA

// ********** Begin Function Pause constinit property declarations *********************************
// ********** End Function Pause constinit property declarations ***********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_Pause_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "Pause", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Pause_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_Pause_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UQuickTweenable_Pause()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_Pause_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execPause)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Pause();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function Pause *********************************************

// ********** Begin Class UQuickTweenable Function Play ********************************************
struct Z_Construct_UFunction_UQuickTweenable_Play_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Control" },
		{ "Comment", "/** Start or resume playback of the tween.\n\x09 */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Start or resume playback of the tween." },
	};
#endif // WITH_METADATA

// ********** Begin Function Play constinit property declarations **********************************
// ********** End Function Play constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_Play_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "Play", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Play_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_Play_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UQuickTweenable_Play()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_Play_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execPlay)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Play();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function Play **********************************************

// ********** Begin Class UQuickTweenable Function Restart *****************************************
struct Z_Construct_UFunction_UQuickTweenable_Restart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Control" },
		{ "Comment", "/** Restart the tween from its beginning (in case it is reversed, it will restart at the end).\n\x09 *  Must be played again after restarting.\n\x09 */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Restart the tween from its beginning (in case it is reversed, it will restart at the end).\nMust be played again after restarting." },
	};
#endif // WITH_METADATA

// ********** Begin Function Restart constinit property declarations *******************************
// ********** End Function Restart constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_Restart_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "Restart", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Restart_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_Restart_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UQuickTweenable_Restart()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_Restart_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execRestart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Restart();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function Restart *******************************************

// ********** Begin Class UQuickTweenable Function Reverse *****************************************
struct Z_Construct_UFunction_UQuickTweenable_Reverse_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Control" },
		{ "Comment", "/** Play the tween in reverse (playback direction is inverted).\n\x09 */" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Play the tween in reverse (playback direction is inverted)." },
	};
#endif // WITH_METADATA

// ********** Begin Function Reverse constinit property declarations *******************************
// ********** End Function Reverse constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenable_Reverse_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenable, nullptr, "Reverse", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenable_Reverse_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenable_Reverse_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UQuickTweenable_Reverse()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenable_Reverse_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenable::execReverse)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Reverse();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenable Function Reverse *******************************************

// ********** Begin Class UQuickTweenable **********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickTweenable;
UClass* UQuickTweenable::GetPrivateStaticClass()
{
	using TClass = UQuickTweenable;
	if (!Z_Registration_Info_UClass_UQuickTweenable.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickTweenable"),
			Z_Registration_Info_UClass_UQuickTweenable.InnerSingleton,
			StaticRegisterNativesUQuickTweenable,
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
	return Z_Registration_Info_UClass_UQuickTweenable.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickTweenable_NoRegister()
{
	return UQuickTweenable::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickTweenable_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Base UObject for QuickTween tweens.\n *\n * Provides a common interface for playback control, querying state, and configuring\n * tween behavior. This class is intended to be extended in C++ or Blueprint to\n * implement concrete tween logic (e.g., property interpolation). Marked as\n * BlueprintType so instances and subclasses can be used in Blueprint graphs.\n *\n * Usage notes:\n *  - Use SetOwner to assign the owning sequence.\n */" },
		{ "IncludePath", "QuickTweenable.h" },
		{ "ModuleRelativePath", "Public/QuickTweenable.h" },
		{ "ToolTip", "Base UObject for QuickTween tweens.\n\nProvides a common interface for playback control, querying state, and configuring\ntween behavior. This class is intended to be extended in C++ or Blueprint to\nimplement concrete tween logic (e.g., property interpolation). Marked as\nBlueprintType so instances and subclasses can be used in Blueprint graphs.\n\nUsage notes:\n - Use SetOwner to assign the owning sequence." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickTweenable constinit property declarations **************************
// ********** End Class UQuickTweenable constinit property declarations ****************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Complete"), .Pointer = &UQuickTweenable::execComplete },
		{ .NameUTF8 = UTF8TEXT("GetAutoKill"), .Pointer = &UQuickTweenable::execGetAutoKill },
		{ .NameUTF8 = UTF8TEXT("GetCurrentLoop"), .Pointer = &UQuickTweenable::execGetCurrentLoop },
		{ .NameUTF8 = UTF8TEXT("GetEaseCurve"), .Pointer = &UQuickTweenable::execGetEaseCurve },
		{ .NameUTF8 = UTF8TEXT("GetEaseType"), .Pointer = &UQuickTweenable::execGetEaseType },
		{ .NameUTF8 = UTF8TEXT("GetElapsedTime"), .Pointer = &UQuickTweenable::execGetElapsedTime },
		{ .NameUTF8 = UTF8TEXT("GetIsCompleted"), .Pointer = &UQuickTweenable::execGetIsCompleted },
		{ .NameUTF8 = UTF8TEXT("GetIsPendingKill"), .Pointer = &UQuickTweenable::execGetIsPendingKill },
		{ .NameUTF8 = UTF8TEXT("GetIsPlaying"), .Pointer = &UQuickTweenable::execGetIsPlaying },
		{ .NameUTF8 = UTF8TEXT("GetIsReversed"), .Pointer = &UQuickTweenable::execGetIsReversed },
		{ .NameUTF8 = UTF8TEXT("GetLoopDuration"), .Pointer = &UQuickTweenable::execGetLoopDuration },
		{ .NameUTF8 = UTF8TEXT("GetLoops"), .Pointer = &UQuickTweenable::execGetLoops },
		{ .NameUTF8 = UTF8TEXT("GetLoopType"), .Pointer = &UQuickTweenable::execGetLoopType },
		{ .NameUTF8 = UTF8TEXT("GetShouldPlayWhilePaused"), .Pointer = &UQuickTweenable::execGetShouldPlayWhilePaused },
		{ .NameUTF8 = UTF8TEXT("GetTimeScale"), .Pointer = &UQuickTweenable::execGetTimeScale },
		{ .NameUTF8 = UTF8TEXT("GetTotalDuration"), .Pointer = &UQuickTweenable::execGetTotalDuration },
		{ .NameUTF8 = UTF8TEXT("GetTweenTag"), .Pointer = &UQuickTweenable::execGetTweenTag },
		{ .NameUTF8 = UTF8TEXT("Kill"), .Pointer = &UQuickTweenable::execKill },
		{ .NameUTF8 = UTF8TEXT("Pause"), .Pointer = &UQuickTweenable::execPause },
		{ .NameUTF8 = UTF8TEXT("Play"), .Pointer = &UQuickTweenable::execPlay },
		{ .NameUTF8 = UTF8TEXT("Restart"), .Pointer = &UQuickTweenable::execRestart },
		{ .NameUTF8 = UTF8TEXT("Reverse"), .Pointer = &UQuickTweenable::execReverse },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickTweenable_Complete, "Complete" }, // 260510174
		{ &Z_Construct_UFunction_UQuickTweenable_GetAutoKill, "GetAutoKill" }, // 3056852721
		{ &Z_Construct_UFunction_UQuickTweenable_GetCurrentLoop, "GetCurrentLoop" }, // 1781867671
		{ &Z_Construct_UFunction_UQuickTweenable_GetEaseCurve, "GetEaseCurve" }, // 1452847662
		{ &Z_Construct_UFunction_UQuickTweenable_GetEaseType, "GetEaseType" }, // 3983594577
		{ &Z_Construct_UFunction_UQuickTweenable_GetElapsedTime, "GetElapsedTime" }, // 1995373903
		{ &Z_Construct_UFunction_UQuickTweenable_GetIsCompleted, "GetIsCompleted" }, // 1888972017
		{ &Z_Construct_UFunction_UQuickTweenable_GetIsPendingKill, "GetIsPendingKill" }, // 2207862998
		{ &Z_Construct_UFunction_UQuickTweenable_GetIsPlaying, "GetIsPlaying" }, // 1184452681
		{ &Z_Construct_UFunction_UQuickTweenable_GetIsReversed, "GetIsReversed" }, // 2990559895
		{ &Z_Construct_UFunction_UQuickTweenable_GetLoopDuration, "GetLoopDuration" }, // 2657296226
		{ &Z_Construct_UFunction_UQuickTweenable_GetLoops, "GetLoops" }, // 623907179
		{ &Z_Construct_UFunction_UQuickTweenable_GetLoopType, "GetLoopType" }, // 2166982840
		{ &Z_Construct_UFunction_UQuickTweenable_GetShouldPlayWhilePaused, "GetShouldPlayWhilePaused" }, // 630008993
		{ &Z_Construct_UFunction_UQuickTweenable_GetTimeScale, "GetTimeScale" }, // 987502070
		{ &Z_Construct_UFunction_UQuickTweenable_GetTotalDuration, "GetTotalDuration" }, // 1794209310
		{ &Z_Construct_UFunction_UQuickTweenable_GetTweenTag, "GetTweenTag" }, // 3776924400
		{ &Z_Construct_UFunction_UQuickTweenable_Kill, "Kill" }, // 4273708563
		{ &Z_Construct_UFunction_UQuickTweenable_Pause, "Pause" }, // 2132729237
		{ &Z_Construct_UFunction_UQuickTweenable_Play, "Play" }, // 2409582678
		{ &Z_Construct_UFunction_UQuickTweenable_Restart, "Restart" }, // 3730616426
		{ &Z_Construct_UFunction_UQuickTweenable_Reverse, "Reverse" }, // 1788148674
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickTweenable>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickTweenable_Statics
UObject* (*const Z_Construct_UClass_UQuickTweenable_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenable_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickTweenable_Statics::ClassParams = {
	&UQuickTweenable::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenable_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickTweenable_Statics::Class_MetaDataParams)
};
void UQuickTweenable::StaticRegisterNativesUQuickTweenable()
{
	UClass* Class = UQuickTweenable::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickTweenable_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickTweenable()
{
	if (!Z_Registration_Info_UClass_UQuickTweenable.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickTweenable.OuterSingleton, Z_Construct_UClass_UQuickTweenable_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickTweenable.OuterSingleton;
}
UQuickTweenable::UQuickTweenable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickTweenable);
UQuickTweenable::~UQuickTweenable() {}
// ********** End Class UQuickTweenable ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickTweenable, UQuickTweenable::StaticClass, TEXT("UQuickTweenable"), &Z_Registration_Info_UClass_UQuickTweenable, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickTweenable), 4073128397U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h__Script_QuickTween_4094622700{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
