// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickTweenSequence.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickTweenSequence() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenSequence();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenSequence_NoRegister();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature();
QUICKTWEEN_API UScriptStruct* Z_Construct_UScriptStruct_FQuickTweenSequenceGroup();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FDynamicDelegateTweenSequence *****************************************
struct Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics
{
	struct _Script_QuickTween_eventDynamicDelegateTweenSequence_Parms
	{
		UQuickTweenSequence* TweenSequence;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FDynamicDelegateTweenSequence constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TweenSequence;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FDynamicDelegateTweenSequence constinit property declarations ***********
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FDynamicDelegateTweenSequence Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::NewProp_TweenSequence = { "TweenSequence", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_QuickTween_eventDynamicDelegateTweenSequence_Parms, TweenSequence), Z_Construct_UClass_UQuickTweenSequence_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::NewProp_TweenSequence,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::PropPointers) < 2048);
// ********** End Delegate FDynamicDelegateTweenSequence Property Definitions **********************
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_QuickTween, nullptr, "DynamicDelegateTweenSequence__DelegateSignature", 	Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::PropPointers), 
sizeof(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::_Script_QuickTween_eventDynamicDelegateTweenSequence_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::_Script_QuickTween_eventDynamicDelegateTweenSequence_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FDynamicDelegateTweenSequence_DelegateWrapper(const FScriptDelegate& DynamicDelegateTweenSequence, UQuickTweenSequence* TweenSequence)
{
	struct _Script_QuickTween_eventDynamicDelegateTweenSequence_Parms
	{
		UQuickTweenSequence* TweenSequence;
	};
	_Script_QuickTween_eventDynamicDelegateTweenSequence_Parms Parms;
	Parms.TweenSequence=TweenSequence;
	DynamicDelegateTweenSequence.ProcessDelegate<UObject>(&Parms);
}
// ********** End Delegate FDynamicDelegateTweenSequence *******************************************

// ********** Begin ScriptStruct FQuickTweenSequenceGroup ******************************************
struct Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FQuickTweenSequenceGroup); }
	static inline consteval int16 GetStructAlignment() { return alignof(FQuickTweenSequenceGroup); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "/**\n * Represents a group of tweens that run in parallel.\n */" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Represents a group of tweens that run in parallel." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tweens_MetaData[] = {
		{ "Comment", "/** Tweens that are part of this group. */" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Tweens that are part of this group." },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FQuickTweenSequenceGroup constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Tweens_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Tweens;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FQuickTweenSequenceGroup constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FQuickTweenSequenceGroup>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup;
class UScriptStruct* FQuickTweenSequenceGroup::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FQuickTweenSequenceGroup, (UObject*)Z_Construct_UPackage__Script_QuickTween(), TEXT("QuickTweenSequenceGroup"));
	}
	return Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup.OuterSingleton;
	}

// ********** Begin ScriptStruct FQuickTweenSequenceGroup Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::NewProp_Tweens_Inner = { "Tweens", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::NewProp_Tweens = { "Tweens", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FQuickTweenSequenceGroup, Tweens), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tweens_MetaData), NewProp_Tweens_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::NewProp_Tweens_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::NewProp_Tweens,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FQuickTweenSequenceGroup Property Definitions ***********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
	nullptr,
	&NewStructOps,
	"QuickTweenSequenceGroup",
	Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::PropPointers),
	sizeof(FQuickTweenSequenceGroup),
	alignof(FQuickTweenSequenceGroup),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FQuickTweenSequenceGroup()
{
	if (!Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup.InnerSingleton, Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup.InnerSingleton);
}
// ********** End ScriptStruct FQuickTweenSequenceGroup ********************************************

// ********** Begin Class UQuickTweenSequence Function Append **************************************
struct Z_Construct_UFunction_UQuickTweenSequence_Append_Statics
{
	struct QuickTweenSequence_eventAppend_Parms
	{
		UQuickTweenable* tween;
		UQuickTweenSequence* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Sequence|Creation" },
		{ "Comment", "/**\n\x09 * Creates a new group and adds a new tween to it.\n\x09 * @param tween The tween to append.\n\x09 * @return Reference to this sequence.\n\x09 */" },
		{ "Keywords", "Sequence" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Creates a new group and adds a new tween to it.\n@param tween The tween to append.\n@return Reference to this sequence." },
	};
#endif // WITH_METADATA

// ********** Begin Function Append constinit property declarations ********************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Append constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Append Property Definitions *******************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventAppend_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventAppend_Parms, ReturnValue), Z_Construct_UClass_UQuickTweenSequence_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::NewProp_tween,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::PropPointers) < 2048);
// ********** End Function Append Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "Append", 	Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::QuickTweenSequence_eventAppend_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::QuickTweenSequence_eventAppend_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_Append()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_Append_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execAppend)
{
	P_GET_OBJECT(UQuickTweenable,Z_Param_tween);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickTweenSequence**)Z_Param__Result=P_THIS->Append(Z_Param_tween);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function Append ****************************************

// ********** Begin Class UQuickTweenSequence Function AssignOnCompleteEvent ***********************
struct Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics
{
	struct QuickTweenSequence_eventAssignOnCompleteEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween completes.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n\x09 *                 The provided delegate will be stored and called on completion.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween completes.\n@param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n                The provided delegate will be stored and called on completion." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnCompleteEvent constinit property declarations *****************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnCompleteEvent constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnCompleteEvent Property Definitions ****************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventAssignOnCompleteEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 1455776595
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnCompleteEvent Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "AssignOnCompleteEvent", 	Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::QuickTweenSequence_eventAssignOnCompleteEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::QuickTweenSequence_eventAssignOnCompleteEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execAssignOnCompleteEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnCompleteEvent(FDynamicDelegateTweenSequence(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function AssignOnCompleteEvent *************************

// ********** Begin Class UQuickTweenSequence Function AssignOnKilledEvent *************************
struct Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics
{
	struct QuickTweenSequence_eventAssignOnKilledEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween is killed.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n\x09 *                 The provided delegate will be stored and called when the tween is killed.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween is killed.\n@param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n                The provided delegate will be stored and called when the tween is killed." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnKilledEvent constinit property declarations *******************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnKilledEvent constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnKilledEvent Property Definitions ******************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventAssignOnKilledEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 1455776595
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnKilledEvent Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "AssignOnKilledEvent", 	Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::QuickTweenSequence_eventAssignOnKilledEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::QuickTweenSequence_eventAssignOnKilledEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execAssignOnKilledEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnKilledEvent(FDynamicDelegateTweenSequence(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function AssignOnKilledEvent ***************************

// ********** Begin Class UQuickTweenSequence Function AssignOnLoopEvent ***************************
struct Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics
{
	struct QuickTweenSequence_eventAssignOnLoopEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween loops.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n\x09 *                 The provided delegate will be stored and called when the tween loops.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween loops.\n@param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n                The provided delegate will be stored and called when the tween loops." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnLoopEvent constinit property declarations *********************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnLoopEvent constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnLoopEvent Property Definitions ********************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventAssignOnLoopEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 1455776595
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnLoopEvent Property Definitions **********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "AssignOnLoopEvent", 	Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::QuickTweenSequence_eventAssignOnLoopEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::QuickTweenSequence_eventAssignOnLoopEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execAssignOnLoopEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnLoopEvent(FDynamicDelegateTweenSequence(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function AssignOnLoopEvent *****************************

// ********** Begin Class UQuickTweenSequence Function AssignOnStartEvent **************************
struct Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics
{
	struct QuickTweenSequence_eventAssignOnStartEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked when the tween starts.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n\x09 *                 The provided delegate will be stored and called on start events.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked when the tween starts.\n@param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n                The provided delegate will be stored and called on start events." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnStartEvent constinit property declarations ********************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnStartEvent constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnStartEvent Property Definitions *******************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventAssignOnStartEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 1455776595
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnStartEvent Property Definitions *********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "AssignOnStartEvent", 	Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::QuickTweenSequence_eventAssignOnStartEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::QuickTweenSequence_eventAssignOnStartEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execAssignOnStartEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnStartEvent(FDynamicDelegateTweenSequence(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function AssignOnStartEvent ****************************

// ********** Begin Class UQuickTweenSequence Function AssignOnUpdateEvent *************************
struct Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics
{
	struct QuickTweenSequence_eventAssignOnUpdateEvent_Parms
	{
		FScriptDelegate callback;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Assign a Blueprint dynamic delegate to be invoked on every tween update.\n\x09 * @param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n\x09 *                 The provided delegate will be stored and called each update tick.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Assign a Blueprint dynamic delegate to be invoked on every tween update.\n@param callback Dynamic delegate with signature (UQuickTweenSequence* Tween).\n                The provided delegate will be stored and called each update tick." },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignOnUpdateEvent constinit property declarations *******************
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_callback;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignOnUpdateEvent constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignOnUpdateEvent Property Definitions ******************************
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::NewProp_callback = { "callback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventAssignOnUpdateEvent_Parms, callback), Z_Construct_UDelegateFunction_QuickTween_DynamicDelegateTweenSequence__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 1455776595
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::NewProp_callback,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::PropPointers) < 2048);
// ********** End Function AssignOnUpdateEvent Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "AssignOnUpdateEvent", 	Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::QuickTweenSequence_eventAssignOnUpdateEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::QuickTweenSequence_eventAssignOnUpdateEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execAssignOnUpdateEvent)
{
	P_GET_PROPERTY(FDelegateProperty,Z_Param_callback);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignOnUpdateEvent(FDynamicDelegateTweenSequence(Z_Param_callback));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function AssignOnUpdateEvent ***************************

// ********** Begin Class UQuickTweenSequence Function GetNumTweens ********************************
struct Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics
{
	struct QuickTweenSequence_eventGetNumTweens_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Sequence|State" },
		{ "Comment", "/**\n\x09 * Gets the number of tweens in the sequence.\n\x09 * @return Number of tweens.\n\x09 */" },
		{ "Keywords", "Sequence" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Gets the number of tweens in the sequence.\n@return Number of tweens." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetNumTweens constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetNumTweens constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetNumTweens Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventGetNumTweens_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::PropPointers) < 2048);
// ********** End Function GetNumTweens Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "GetNumTweens", 	Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::QuickTweenSequence_eventGetNumTweens_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::QuickTweenSequence_eventGetNumTweens_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execGetNumTweens)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetNumTweens();
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function GetNumTweens **********************************

// ********** Begin Class UQuickTweenSequence Function GetTween ************************************
struct Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics
{
	struct QuickTweenSequence_eventGetTween_Parms
	{
		int32 index;
		UQuickTweenable* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Sequence|State" },
		{ "Comment", "/**\n\x09 * Gets the tween at the specified index.\n\x09 * @param index Index of the tween.\n\x09 * @return Pointer to the tween.\n\x09 */" },
		{ "Keywords", "Sequence" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Gets the tween at the specified index.\n@param index Index of the tween.\n@return Pointer to the tween." },
	};
#endif // WITH_METADATA

// ********** Begin Function GetTween constinit property declarations ******************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_index;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTween constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTween Property Definitions *****************************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::NewProp_index = { "index", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventGetTween_Parms, index), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventGetTween_Parms, ReturnValue), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::NewProp_index,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::PropPointers) < 2048);
// ********** End Function GetTween Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "GetTween", 	Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::QuickTweenSequence_eventGetTween_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::QuickTweenSequence_eventGetTween_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_GetTween()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_GetTween_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execGetTween)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_index);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickTweenable**)Z_Param__Result=P_THIS->GetTween(Z_Param_index);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function GetTween **************************************

// ********** Begin Class UQuickTweenSequence Function Join ****************************************
struct Z_Construct_UFunction_UQuickTweenSequence_Join_Statics
{
	struct QuickTweenSequence_eventJoin_Parms
	{
		UQuickTweenable* tween;
		UQuickTweenSequence* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Sequence|Creation" },
		{ "Comment", "/**\n\x09 * Joins a tween to the previously created group, or creates a new one if it is the first.\n\x09 * @param tween The tween to join.\n\x09 * @return Reference to this sequence.\n\x09 */" },
		{ "Keywords", "Sequence" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Joins a tween to the previously created group, or creates a new one if it is the first.\n@param tween The tween to join.\n@return Reference to this sequence." },
	};
#endif // WITH_METADATA

// ********** Begin Function Join constinit property declarations **********************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_tween;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Join constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Join Property Definitions *********************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::NewProp_tween = { "tween", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventJoin_Parms, tween), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventJoin_Parms, ReturnValue), Z_Construct_UClass_UQuickTweenSequence_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::NewProp_tween,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::PropPointers) < 2048);
// ********** End Function Join Property Definitions ***********************************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "Join", 	Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::QuickTweenSequence_eventJoin_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::QuickTweenSequence_eventJoin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_Join()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_Join_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execJoin)
{
	P_GET_OBJECT(UQuickTweenable,Z_Param_tween);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickTweenSequence**)Z_Param__Result=P_THIS->Join(Z_Param_tween);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function Join ******************************************

// ********** Begin Class UQuickTweenSequence Function RemoveAllOnCompleteEvent ********************
struct Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics
{
	struct QuickTweenSequence_eventRemoveAllOnCompleteEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the complete event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
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
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventRemoveAllOnCompleteEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnCompleteEvent Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "RemoveAllOnCompleteEvent", 	Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::QuickTweenSequence_eventRemoveAllOnCompleteEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::QuickTweenSequence_eventRemoveAllOnCompleteEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execRemoveAllOnCompleteEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnCompleteEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function RemoveAllOnCompleteEvent **********************

// ********** Begin Class UQuickTweenSequence Function RemoveAllOnKilledEvent **********************
struct Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics
{
	struct QuickTweenSequence_eventRemoveAllOnKilledEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the killed event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
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
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventRemoveAllOnKilledEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnKilledEvent Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "RemoveAllOnKilledEvent", 	Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::QuickTweenSequence_eventRemoveAllOnKilledEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::QuickTweenSequence_eventRemoveAllOnKilledEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execRemoveAllOnKilledEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnKilledEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function RemoveAllOnKilledEvent ************************

// ********** Begin Class UQuickTweenSequence Function RemoveAllOnLoopEvent ************************
struct Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics
{
	struct QuickTweenSequence_eventRemoveAllOnLoopEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the loop event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
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
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventRemoveAllOnLoopEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnLoopEvent Property Definitions *******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "RemoveAllOnLoopEvent", 	Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::QuickTweenSequence_eventRemoveAllOnLoopEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::QuickTweenSequence_eventRemoveAllOnLoopEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execRemoveAllOnLoopEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnLoopEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function RemoveAllOnLoopEvent **************************

// ********** Begin Class UQuickTweenSequence Function RemoveAllOnStartEvent ***********************
struct Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics
{
	struct QuickTweenSequence_eventRemoveAllOnStartEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the start event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
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
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventRemoveAllOnStartEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnStartEvent Property Definitions ******************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "RemoveAllOnStartEvent", 	Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::QuickTweenSequence_eventRemoveAllOnStartEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::QuickTweenSequence_eventRemoveAllOnStartEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execRemoveAllOnStartEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnStartEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function RemoveAllOnStartEvent *************************

// ********** Begin Class UQuickTweenSequence Function RemoveAllOnUpdateEvent **********************
struct Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics
{
	struct QuickTweenSequence_eventRemoveAllOnUpdateEvent_Parms
	{
		const UObject* object;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Tween|Info" },
		{ "Comment", "/**\n\x09 * Remove all bound Blueprint dynamic delegates for the update event that belong to the specified object.\n\x09 * @param object The UObject whose bindings should be removed. If nullptr, no action is taken.\n\x09 */" },
		{ "Keywords", "Tween | Event" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
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
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::NewProp_object = { "object", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenSequence_eventRemoveAllOnUpdateEvent_Parms, object), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_object_MetaData), NewProp_object_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::NewProp_object,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::PropPointers) < 2048);
// ********** End Function RemoveAllOnUpdateEvent Property Definitions *****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenSequence, nullptr, "RemoveAllOnUpdateEvent", 	Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::QuickTweenSequence_eventRemoveAllOnUpdateEvent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::QuickTweenSequence_eventRemoveAllOnUpdateEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenSequence::execRemoveAllOnUpdateEvent)
{
	P_GET_OBJECT(UObject,Z_Param_object);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RemoveAllOnUpdateEvent(Z_Param_object);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenSequence Function RemoveAllOnUpdateEvent ************************

// ********** Begin Class UQuickTweenSequence ******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickTweenSequence;
UClass* UQuickTweenSequence::GetPrivateStaticClass()
{
	using TClass = UQuickTweenSequence;
	if (!Z_Registration_Info_UClass_UQuickTweenSequence.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickTweenSequence"),
			Z_Registration_Info_UClass_UQuickTweenSequence.InnerSingleton,
			StaticRegisterNativesUQuickTweenSequence,
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
	return Z_Registration_Info_UClass_UQuickTweenSequence.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickTweenSequence_NoRegister()
{
	return UQuickTweenSequence::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickTweenSequence_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * UQuickTweenSequence manages a sequence of tween animations.\n * Allows joining, appending, and controlling multiple tweens as a group.\n * Supports looping, reversing, and querying sequence state.\n * Note:\n * - Tweens added to the sequence can not be controlled individually.\n */" },
		{ "IncludePath", "Tweens/QuickTweenSequence.h" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "UQuickTweenSequence manages a sequence of tween animations.\nAllows joining, appending, and controlling multiple tweens as a group.\nSupports looping, reversing, and querying sequence state.\nNote:\n- Tweens added to the sequence can not be controlled individually." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TweenGroups_MetaData[] = {
		{ "Comment", "/** Array of tween groups in the sequence. */" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "ToolTip", "Array of tween groups in the sequence." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldContextObject_MetaData[] = {
		{ "Comment", "/** Object to do world queries. */" },
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
		{ "NativeConst", "" },
		{ "ToolTip", "Object to do world queries." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Owner_MetaData[] = {
		{ "ModuleRelativePath", "Public/Tweens/QuickTweenSequence.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickTweenSequence constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_TweenGroups_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TweenGroups;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Owner;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UQuickTweenSequence constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Append"), .Pointer = &UQuickTweenSequence::execAppend },
		{ .NameUTF8 = UTF8TEXT("AssignOnCompleteEvent"), .Pointer = &UQuickTweenSequence::execAssignOnCompleteEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnKilledEvent"), .Pointer = &UQuickTweenSequence::execAssignOnKilledEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnLoopEvent"), .Pointer = &UQuickTweenSequence::execAssignOnLoopEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnStartEvent"), .Pointer = &UQuickTweenSequence::execAssignOnStartEvent },
		{ .NameUTF8 = UTF8TEXT("AssignOnUpdateEvent"), .Pointer = &UQuickTweenSequence::execAssignOnUpdateEvent },
		{ .NameUTF8 = UTF8TEXT("GetNumTweens"), .Pointer = &UQuickTweenSequence::execGetNumTweens },
		{ .NameUTF8 = UTF8TEXT("GetTween"), .Pointer = &UQuickTweenSequence::execGetTween },
		{ .NameUTF8 = UTF8TEXT("Join"), .Pointer = &UQuickTweenSequence::execJoin },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnCompleteEvent"), .Pointer = &UQuickTweenSequence::execRemoveAllOnCompleteEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnKilledEvent"), .Pointer = &UQuickTweenSequence::execRemoveAllOnKilledEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnLoopEvent"), .Pointer = &UQuickTweenSequence::execRemoveAllOnLoopEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnStartEvent"), .Pointer = &UQuickTweenSequence::execRemoveAllOnStartEvent },
		{ .NameUTF8 = UTF8TEXT("RemoveAllOnUpdateEvent"), .Pointer = &UQuickTweenSequence::execRemoveAllOnUpdateEvent },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickTweenSequence_Append, "Append" }, // 99529299
		{ &Z_Construct_UFunction_UQuickTweenSequence_AssignOnCompleteEvent, "AssignOnCompleteEvent" }, // 904795656
		{ &Z_Construct_UFunction_UQuickTweenSequence_AssignOnKilledEvent, "AssignOnKilledEvent" }, // 3685798561
		{ &Z_Construct_UFunction_UQuickTweenSequence_AssignOnLoopEvent, "AssignOnLoopEvent" }, // 3546777249
		{ &Z_Construct_UFunction_UQuickTweenSequence_AssignOnStartEvent, "AssignOnStartEvent" }, // 372778058
		{ &Z_Construct_UFunction_UQuickTweenSequence_AssignOnUpdateEvent, "AssignOnUpdateEvent" }, // 4161361480
		{ &Z_Construct_UFunction_UQuickTweenSequence_GetNumTweens, "GetNumTweens" }, // 714492306
		{ &Z_Construct_UFunction_UQuickTweenSequence_GetTween, "GetTween" }, // 257628657
		{ &Z_Construct_UFunction_UQuickTweenSequence_Join, "Join" }, // 1089410064
		{ &Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnCompleteEvent, "RemoveAllOnCompleteEvent" }, // 3023687880
		{ &Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnKilledEvent, "RemoveAllOnKilledEvent" }, // 2556780931
		{ &Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnLoopEvent, "RemoveAllOnLoopEvent" }, // 1302402858
		{ &Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnStartEvent, "RemoveAllOnStartEvent" }, // 1086059044
		{ &Z_Construct_UFunction_UQuickTweenSequence_RemoveAllOnUpdateEvent, "RemoveAllOnUpdateEvent" }, // 3937646382
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickTweenSequence>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickTweenSequence_Statics

// ********** Begin Class UQuickTweenSequence Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_TweenGroups_Inner = { "TweenGroups", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FQuickTweenSequenceGroup, METADATA_PARAMS(0, nullptr) }; // 2633348126
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_TweenGroups = { "TweenGroups", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickTweenSequence, TweenGroups), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TweenGroups_MetaData), NewProp_TweenGroups_MetaData) }; // 2633348126
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickTweenSequence, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldContextObject_MetaData), NewProp_WorldContextObject_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_Owner = { "Owner", nullptr, (EPropertyFlags)0x0040000000002000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickTweenSequence, Owner), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Owner_MetaData), NewProp_Owner_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UQuickTweenSequence_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_TweenGroups_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_TweenGroups,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickTweenSequence_Statics::NewProp_Owner,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenSequence_Statics::PropPointers) < 2048);
// ********** End Class UQuickTweenSequence Property Definitions ***********************************
UObject* (*const Z_Construct_UClass_UQuickTweenSequence_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UQuickTweenable,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenSequence_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickTweenSequence_Statics::ClassParams = {
	&UQuickTweenSequence::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UQuickTweenSequence_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenSequence_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenSequence_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickTweenSequence_Statics::Class_MetaDataParams)
};
void UQuickTweenSequence::StaticRegisterNativesUQuickTweenSequence()
{
	UClass* Class = UQuickTweenSequence::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickTweenSequence_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickTweenSequence()
{
	if (!Z_Registration_Info_UClass_UQuickTweenSequence.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickTweenSequence.OuterSingleton, Z_Construct_UClass_UQuickTweenSequence_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickTweenSequence.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickTweenSequence);
// ********** End Class UQuickTweenSequence ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h__Script_QuickTween_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FQuickTweenSequenceGroup::StaticStruct, Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics::NewStructOps, TEXT("QuickTweenSequenceGroup"),&Z_Registration_Info_UScriptStruct_FQuickTweenSequenceGroup, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FQuickTweenSequenceGroup), 2633348126U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickTweenSequence, UQuickTweenSequence::StaticClass, TEXT("UQuickTweenSequence"), &Z_Registration_Info_UClass_UQuickTweenSequence, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickTweenSequence), 2936585866U) },
	};
}; // Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h__Script_QuickTween_4229417316{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h__Script_QuickTween_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h__Script_QuickTween_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h__Script_QuickTween_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
