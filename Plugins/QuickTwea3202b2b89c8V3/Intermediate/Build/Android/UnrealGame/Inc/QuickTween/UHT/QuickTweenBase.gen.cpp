// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickTweenBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickTweenBase() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase_NoRegister();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FDynamicDelegateTween *************************************************
struct Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventDynamicDelegateTween_Parms
	{
		UQuickTweenBase* Tween;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDynamicDelegateTween constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tween;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDynamicDelegateTween constinit property declarations *******************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDynamicDelegateTween Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::NewProp_Tween = { "Tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventDynamicDelegateTween_Parms, Tween), Z_Construct_UClass_UQuickTweenBase_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::NewProp_Tween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FDynamicDelegateTween Property Definitions ******************************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "DynamicDelegateTween__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::_Script_QuickTween_eventDynamicDelegateTween_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::_Script_QuickTween_eventDynamicDelegateTween_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FDynamicDelegateTween_DelegateWrapper(const FScriptDelegate& DynamicDelegateTween, UQuickTweenBase* Tween)
{
	struct _Script_QuickTween_eventDynamicDelegateTween_Parms
	{
		UQuickTweenBase* Tween;
	};
	_Script_QuickTween_eventDynamicDelegateTween_Parms Parms;
	Parms.Tween=Tween;
	DynamicDelegateTween.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FDynamicDelegateTween ***************************************************

// ********** Begin Class UQuickTweenBase Function AssignOnCompleteEvent ***************************
struct Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics
{
	struct QuickTweenBase_eventAssignOnCompleteEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween completes.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n\x09 *                 The provided delegate will be stored and called on completion.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween completes.\n@param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n                The provided delegate will be stored and called on completion." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnCompleteEvent constinit property declarations *****************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnCompleteEvent constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnCompleteEvent Property Definitions ****************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventAssignOnCompleteEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3398770099
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnCompleteEvent Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "AssignOnCompleteEvent", 	Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::QuickTweenBase_eventAssignOnCompleteEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::QuickTweenBase_eventAssignOnCompleteEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execAssignOnCompleteEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnCompleteEvent(FDynamicDelegateTween(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function AssignOnCompleteEvent *****************************

// ********** Begin Class UQuickTweenBase Function AssignOnKilledEvent *****************************
struct Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics
{
	struct QuickTweenBase_eventAssignOnKilledEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween is killed.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n\x09 *                 The provided delegate will be stored and called when the tween is killed.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween is killed.\n@param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n                The provided delegate will be stored and called when the tween is killed." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnKilledEvent constinit property declarations *******************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnKilledEvent constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnKilledEvent Property Definitions ******************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventAssignOnKilledEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3398770099
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnKilledEvent Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "AssignOnKilledEvent", 	Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::QuickTweenBase_eventAssignOnKilledEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::QuickTweenBase_eventAssignOnKilledEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execAssignOnKilledEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnKilledEvent(FDynamicDelegateTween(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function AssignOnKilledEvent *******************************

// ********** Begin Class UQuickTweenBase Function AssignOnLoopEvent *******************************
struct Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics
{
	struct QuickTweenBase_eventAssignOnLoopEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween loops.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n\x09 *                 The provided delegate will be stored and called when the tween loops.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween loops.\n@param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n                The provided delegate will be stored and called when the tween loops." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnLoopEvent constinit property declarations *********************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnLoopEvent constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnLoopEvent Property Definitions ********************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventAssignOnLoopEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3398770099
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnLoopEvent Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "AssignOnLoopEvent", 	Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::QuickTweenBase_eventAssignOnLoopEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::QuickTweenBase_eventAssignOnLoopEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execAssignOnLoopEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnLoopEvent(FDynamicDelegateTween(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function AssignOnLoopEvent *********************************

// ********** Begin Class UQuickTweenBase Function AssignOnStartEvent ******************************
struct Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics
{
	struct QuickTweenBase_eventAssignOnStartEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween starts.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n\x09 *                 The provided delegate will be stored and called on start events.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween starts.\n@param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n                The provided delegate will be stored and called on start events." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnStartEvent constinit property declarations ********************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnStartEvent constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnStartEvent Property Definitions *******************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventAssignOnStartEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3398770099
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnStartEvent Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "AssignOnStartEvent", 	Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::QuickTweenBase_eventAssignOnStartEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::QuickTweenBase_eventAssignOnStartEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execAssignOnStartEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnStartEvent(FDynamicDelegateTween(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function AssignOnStartEvent ********************************

// ********** Begin Class UQuickTweenBase Function AssignOnUpdateEvent *****************************
struct Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics
{
	struct QuickTweenBase_eventAssignOnUpdateEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked on every tween update.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n\x09 *                 The provided delegate will be stored and called each update tick.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked on every tween update.\n@param callback Dynamic delegate with signature (UQuickTweenBase* Tween).\n                The provided delegate will be stored and called each update tick." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnUpdateEvent constinit property declarations *******************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnUpdateEvent constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnUpdateEvent Property Definitions ******************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventAssignOnUpdateEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTween__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3398770099
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnUpdateEvent Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "AssignOnUpdateEvent", 	Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::QuickTweenBase_eventAssignOnUpdateEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::QuickTweenBase_eventAssignOnUpdateEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execAssignOnUpdateEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnUpdateEvent(FDynamicDelegateTween(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function AssignOnUpdateEvent *******************************

// ********** Begin Class UQuickTweenBase Function RemoveAllOnCompleteEvent ************************
struct Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics
{
	struct QuickTweenBase_eventRemoveAllOnCompleteEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the complete event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Remove all bound Blueprint dynamic delegates for the complete event that belong to the specified object.\n@param object The UObject whose bindings should be removed. If nullptr, no action is taken." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_object_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveAllOnCompleteEvent constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_object;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveAllOnCompleteEvent constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveAllOnCompleteEvent Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventRemoveAllOnCompleteEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnCompleteEvent Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "RemoveAllOnCompleteEvent", 	Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::QuickTweenBase_eventRemoveAllOnCompleteEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::QuickTweenBase_eventRemoveAllOnCompleteEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execRemoveAllOnCompleteEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnCompleteEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function RemoveAllOnCompleteEvent **************************

// ********** Begin Class UQuickTweenBase Function RemoveAllOnKilledEvent **************************
struct Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics
{
	struct QuickTweenBase_eventRemoveAllOnKilledEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the killed event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Remove all bound Blueprint dynamic delegates for the killed event that belong to the specified object.\n@param object The UObject whose bindings should be removed. If nullptr, no action is taken." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_object_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveAllOnKilledEvent constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_object;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveAllOnKilledEvent constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveAllOnKilledEvent Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventRemoveAllOnKilledEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnKilledEvent Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "RemoveAllOnKilledEvent", 	Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::QuickTweenBase_eventRemoveAllOnKilledEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::QuickTweenBase_eventRemoveAllOnKilledEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execRemoveAllOnKilledEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnKilledEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function RemoveAllOnKilledEvent ****************************

// ********** Begin Class UQuickTweenBase Function RemoveAllOnLoopEvent ****************************
struct Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics
{
	struct QuickTweenBase_eventRemoveAllOnLoopEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the loop event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Remove all bound Blueprint dynamic delegates for the loop event that belong to the specified object.\n@param object The UObject whose bindings should be removed. If nullptr, no action is taken." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_object_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveAllOnLoopEvent constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_object;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveAllOnLoopEvent constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveAllOnLoopEvent Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventRemoveAllOnLoopEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnLoopEvent Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "RemoveAllOnLoopEvent", 	Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::QuickTweenBase_eventRemoveAllOnLoopEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::QuickTweenBase_eventRemoveAllOnLoopEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execRemoveAllOnLoopEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnLoopEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function RemoveAllOnLoopEvent ******************************

// ********** Begin Class UQuickTweenBase Function RemoveAllOnStartEvent ***************************
struct Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics
{
	struct QuickTweenBase_eventRemoveAllOnStartEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the start event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Remove all bound Blueprint dynamic delegates for the start event that belong to the specified object.\n@param object The UObject whose bindings should be removed. If nullptr, no action is taken." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_object_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveAllOnStartEvent constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_object;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveAllOnStartEvent constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveAllOnStartEvent Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventRemoveAllOnStartEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnStartEvent Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "RemoveAllOnStartEvent", 	Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::QuickTweenBase_eventRemoveAllOnStartEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::QuickTweenBase_eventRemoveAllOnStartEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execRemoveAllOnStartEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnStartEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function RemoveAllOnStartEvent *****************************

// ********** Begin Class UQuickTweenBase Function RemoveAllOnUpdateEvent **************************
struct Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics
{
	struct QuickTweenBase_eventRemoveAllOnUpdateEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the update event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Remove all bound Blueprint dynamic delegates for the update event that belong to the specified object.\n@param object The UObject whose bindings should be removed. If nullptr, no action is taken." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_object_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveAllOnUpdateEvent constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_object;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveAllOnUpdateEvent constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveAllOnUpdateEvent Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenBase_eventRemoveAllOnUpdateEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnUpdateEvent Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenBase, nullptr, "RemoveAllOnUpdateEvent", 	Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::QuickTweenBase_eventRemoveAllOnUpdateEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::QuickTweenBase_eventRemoveAllOnUpdateEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenBase::execRemoveAllOnUpdateEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnUpdateEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenBase Function RemoveAllOnUpdateEvent ****************************

// ********** Begin Class UQuickTweenBase **********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickTweenBase;
UClass* UQuickTweenBase::GetPrivateStaticClass()
{
	using TClass = UQuickTweenBase;
	if (!Z_Registration_Info_UClass_UQuickTweenBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickTweenBase"),
			Z_Registration_Info_UClass_UQuickTweenBase.InnerSingleton,
			StaticRegisterNativesUQuickTweenBase,
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
	return Z_Registration_Info_UClass_UQuickTweenBase.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickTweenBase_NoRegister()
{
	return UQuickTweenBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickTweenBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Base class for all QuickTween tweens.\n * Provides core tweening functionality, state, and events.\n */" },
		{ "IncludePath", "Tweens/QuickTweenBase.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Base class for all QuickTween tweens.\nProvides core tweening functionality, state, and events." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EaseCurve_MetaData[] = {
		{ "Comment", "/** Custom curve for easing, if any. */" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "Custom curve for easing, if any." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Owner_MetaData[] = {
		{ "Comment", "/** If this tween has an owner */" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "ToolTip", "If this tween has an owner" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenBase.h" },
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickTweenBase constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EaseCurve;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Owner;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UQuickTweenBase constinit property declarations ****************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AssignOnCompleteEvent"), .Pointer = &UQuickTweenBase::execAssignOnCompleteEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnKilledEvent"), .Pointer = &UQuickTweenBase::execAssignOnKilledEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnLoopEvent"), .Pointer = &UQuickTweenBase::execAssignOnLoopEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnStartEvent"), .Pointer = &UQuickTweenBase::execAssignOnStartEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnUpdateEvent"), .Pointer = &UQuickTweenBase::execAssignOnUpdateEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnCompleteEvent"), .Pointer = &UQuickTweenBase::execRemoveAllOnCompleteEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnKilledEvent"), .Pointer = &UQuickTweenBase::execRemoveAllOnKilledEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnLoopEvent"), .Pointer = &UQuickTweenBase::execRemoveAllOnLoopEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnStartEvent"), .Pointer = &UQuickTweenBase::execRemoveAllOnStartEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnUpdateEvent"), .Pointer = &UQuickTweenBase::execRemoveAllOnUpdateEvent },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickTweenBase_AssignOnCompleteEvent, "AssignOnCompleteEvent" }, // 831325081
		{ &Z_Construct_UFunction_UQuickTweenBase_AssignOnKilledEvent, "AssignOnKilledEvent" }, // 2263748734
		{ &Z_Construct_UFunction_UQuickTweenBase_AssignOnLoopEvent, "AssignOnLoopEvent" }, // 1260168051
		{ &Z_Construct_UFunction_UQuickTweenBase_AssignOnStartEvent, "AssignOnStartEvent" }, // 2934627712
		{ &Z_Construct_UFunction_UQuickTweenBase_AssignOnUpdateEvent, "AssignOnUpdateEvent" }, // 2002168711
		{ &Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnCompleteEvent, "RemoveAllOnCompleteEvent" }, // 113064468
		{ &Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnKilledEvent, "RemoveAllOnKilledEvent" }, // 440213478
		{ &Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnLoopEvent, "RemoveAllOnLoopEvent" }, // 2232534018
		{ &Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnStartEvent, "RemoveAllOnStartEvent" }, // 682744384
		{ &Z_Construct_UFunction_UQuickTweenBase_RemoveAllOnUpdateEvent, "RemoveAllOnUpdateEvent" }, // 3325332020
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickTweenBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickTweenBase_Statics

// ********** Begin Class UQuickTweenBase Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickTweenBase_Statics::NewProp_EaseCurve = { "EaseCurve", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickTweenBase, EaseCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EaseCurve_MetaData), NewProp_EaseCurve_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickTweenBase_Statics::NewProp_Owner = { "Owner", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickTweenBase, Owner), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Owner_MetaData), NewProp_Owner_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickTweenBase_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickTweenBase, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UQuickTweenBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenBase_Statics::NewProp_EaseCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenBase_Statics::NewProp_Owner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenBase_Statics::NewProp_WorldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenBase_Statics::PropPointers) < 2048);
// ********** End Class UQuickTweenBase Property Definitions ***************************************
UObject* (*const Z_Construct_UClass_UQuickTweenBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenable,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickTweenBase_Statics::ClassParams = {
	&UQuickTweenBase::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UQuickTweenBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenBase_Statics::PropPointers),
	0,
	0x001000A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickTweenBase_Statics::Class_MetaDataParams)
};
void UQuickTweenBase::StaticRegisterNativesUQuickTweenBase()
{
	UClass* Class = UQuickTweenBase::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickTweenBase_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickTweenBase()
{
	if (!Z_Registration_Info_UClass_UQuickTweenBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickTweenBase.OuterSingleton, Z_Construct_UClass_UQuickTweenBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickTweenBase.OuterSingleton;
}
UQuickTweenBase::UQuickTweenBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickTweenBase);
// ********** End Class UQuickTweenBase ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickTweenBase, UQuickTweenBase::StaticClass, TEXT("UQuickTweenBase"), &Z_Registration_Info_UClass_UQuickTweenBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickTweenBase), 3949780922U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h__Script_QuickTween_2594596423{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
