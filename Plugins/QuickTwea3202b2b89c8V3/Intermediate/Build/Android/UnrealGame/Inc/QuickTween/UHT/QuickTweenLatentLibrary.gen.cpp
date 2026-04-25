// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickTweenLatentLibrary.h"
#include "Engine/LatentActionManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickTweenLatentLibrary() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCurveFloat_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FLatentActionInfo();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickColorTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickEmptyTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickFloatTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickIntTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickRotatorTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenLatentLibrary();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenLatentLibrary_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenSequence_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVector2DTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVectorTween_NoRegister();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EEaseType();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_ELoopType();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenSpace();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature();
UMG_API UClass* Z_Construct_UClass_UImage_NoRegister();
UMG_API UClass* Z_Construct_UClass_UWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentSequence *********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		UQuickTweenSequence* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent QuickTween sequence.\n\x09 *\n\x09 * Creates and optionally starts a QuickTween sequence using latent execution in Blueprints.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param loops Number of times the sequence will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @return Pointer to the created UQuickTweenSequence.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Sequence | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent QuickTween sequence.\n\nCreates and optionally starts a QuickTween sequence using latent execution in Blueprints.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param loops Number of times the sequence will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@return Pointer to the created UQuickTweenSequence." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentSequence constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentSequence constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentSequence Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms, ReturnValue), Z_Construct_UClass_UQuickTweenSequence_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentSequence Property Definitions *********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentSequence", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentSequence_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentSequence)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickTweenSequence**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentSequence(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentSequence ***********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenColor *******
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		FColor from;
		FColor to;
		FScriptDelegate setter;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickColorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent color tween.\n\x09 *\n\x09 * Tween an FColor value from \\p from to \\p to using the provided setter function.\n\x09 * Exposed as a latent Blueprint node so execution can continue based on the latent step.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param from Starting color.\n\x09 * @param to Target color.\n\x09 * @param setter Callback used to apply interpolated FColor values.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickColorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Color | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent color tween.\n\nTween an FColor value from \\p from to \\p to using the provided setter function.\nExposed as a latent Blueprint node so execution can continue based on the latent step.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param from Starting color.\n@param to Target color.\n@param setter Callback used to apply interpolated FColor values.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickColorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_from_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentTweenColor constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_from;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_setter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentTweenColor constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentTweenColor Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, from), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, to), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 4149733706
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentTweenColor Property Definitions *******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentTweenColor", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenColor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenColor)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_STRUCT_REF(FColor,Z_Param_Out_from);
	P_GET_STRUCT_REF(FColor,Z_Param_Out_to);
	P_GET_PROPERTY(FDelegateProperty,Z_Param_setter);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentTweenColor(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_Out_from,Z_Param_Out_to,FColorSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenColor *********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenEmpty *******
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		float duration;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickEmptyTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent \"empty\" tween (no value) that can be used as a timed latent node in Blueprints.\n\x09 *\n\x09 * This function exposes a latent Blueprint node that creates a UQuickEmptyTween which only tracks time\n\x09 * and latent execution steps (useful for delays, sequencing or timing without changing any property).\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution (Blueprint-provided).\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param duration Duration of the empty tween in seconds.\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickEmptyTween instance.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Empty | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent \"empty\" tween (no value) that can be used as a timed latent node in Blueprints.\n\nThis function exposes a latent Blueprint node that creates a UQuickEmptyTween which only tracks time\nand latent execution steps (useful for delays, sequencing or timing without changing any property).\n\n@param worldContextObject World context for latent action execution (Blueprint-provided).\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param duration Duration of the empty tween in seconds.\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickEmptyTween instance." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentTweenEmpty constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentTweenEmpty constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentTweenEmpty Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms, ReturnValue), Z_Construct_UClass_UQuickEmptyTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentTweenEmpty Property Definitions *******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentTweenEmpty", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenEmpty_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenEmpty)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickEmptyTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentTweenEmpty(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_duration,Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenEmpty *********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenFloat *******
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		float from;
		float to;
		FScriptDelegate setter;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent float tween.\n\x09 *\n\x09 * Tween a float value from \\p from to \\p to using the provided setter function.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param from Starting float value.\n\x09 * @param to Target float value.\n\x09 * @param setter Callback used to apply interpolated float values.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Rotator | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent float tween.\n\nTween a float value from \\p from to \\p to using the provided setter function.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param from Starting float value.\n@param to Target float value.\n@param setter Callback used to apply interpolated float values.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentTweenFloat constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_from;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_to;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_setter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentTweenFloat constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentTweenFloat Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, from), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 2499567968
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentTweenFloat Property Definitions *******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentTweenFloat", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenFloat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenFloat)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_PROPERTY(FFloatProperty,Z_Param_from);
	P_GET_PROPERTY(FFloatProperty,Z_Param_to);
	P_GET_PROPERTY(FDelegateProperty,Z_Param_setter);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentTweenFloat(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_from,Z_Param_to,FFloatSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenFloat *********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenInt *********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		int32 from;
		int32 to;
		FScriptDelegate setter;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickIntTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent integer tween.\n\x09 *\n\x09 * Tween an integer value from \\p from to \\p to using the provided setter function.\n\x09 * Exposed as a latent Blueprint node so execution can continue based on the latent step.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param from Starting integer value.\n\x09 * @param to Target integer value.\n\x09 * @param setter Callback used to apply interpolated int32 values.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickIntTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Int | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent integer tween.\n\nTween an integer value from \\p from to \\p to using the provided setter function.\nExposed as a latent Blueprint node so execution can continue based on the latent step.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param from Starting integer value.\n@param to Target integer value.\n@param setter Callback used to apply interpolated int32 values.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickIntTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentTweenInt constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FIntPropertyParams NewProp_from;
	static const UECodeGen_Private::FIntPropertyParams NewProp_to;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_setter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentTweenInt constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentTweenInt Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, from), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 2363718048
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms, ReturnValue), Z_Construct_UClass_UQuickIntTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentTweenInt Property Definitions *********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentTweenInt", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenInt_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenInt)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_PROPERTY(FIntProperty,Z_Param_from);
	P_GET_PROPERTY(FIntProperty,Z_Param_to);
	P_GET_PROPERTY(FDelegateProperty,Z_Param_setter);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickIntTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentTweenInt(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_from,Z_Param_to,FIntSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenInt ***********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenRotator *****
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		FRotator from;
		FRotator to;
		FScriptDelegate setter;
		bool bUseShortestPath;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickRotatorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent rotator tween.\n\x09 *\n\x09 * Tween an FRotator value from \\p from to \\p to using the provided setter function.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param from Starting rotator.\n\x09 * @param to Target rotator.\n\x09 * @param setter Callback used to apply interpolated FRotator values.\n\x09 * @param bUseShortestPath When true, interpolation will use the shortest rotational path.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickRotatorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Rotator | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent rotator tween.\n\nTween an FRotator value from \\p from to \\p to using the provided setter function.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param from Starting rotator.\n@param to Target rotator.\n@param setter Callback used to apply interpolated FRotator values.\n@param bUseShortestPath When true, interpolation will use the shortest rotational path.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickRotatorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_from_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentTweenRotator constinit property declarations ****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_from;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_setter;
	static void NewProp_bUseShortestPath_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseShortestPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentTweenRotator constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentTweenRotator Property Definitions ***************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, from), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, to), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 2384351140
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentTweenRotator Property Definitions *****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentTweenRotator", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenRotator_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenRotator)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_from);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_to);
	P_GET_PROPERTY(FDelegateProperty,Z_Param_setter);
	P_GET_UBOOL(Z_Param_bUseShortestPath);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentTweenRotator(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_Out_from,Z_Param_Out_to,FRotatorSetter(Z_Param_setter),Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenRotator *******

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenVector ******
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		FVector from;
		FVector to;
		FScriptDelegate setter;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVectorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent vector tween.\n\x09 *\n\x09 * Tween a FVector value from \\p from to \\p to using the provided setter function.\n\x09 * Exposed as a latent Blueprint node.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param from Starting vector.\n\x09 * @param to Target vector.\n\x09 * @param setter Callback used to apply interpolated FVector values.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent vector tween.\n\nTween a FVector value from \\p from to \\p to using the provided setter function.\nExposed as a latent Blueprint node.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param from Starting vector.\n@param to Target vector.\n@param setter Callback used to apply interpolated FVector values.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVectorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_from_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentTweenVector constinit property declarations *****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_from;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_setter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentTweenVector constinit property declarations *******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentTweenVector Property Definitions ****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, from), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3599544734
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentTweenVector Property Definitions ******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentTweenVector", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenVector)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_from);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_to);
	P_GET_PROPERTY(FDelegateProperty,Z_Param_setter);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentTweenVector(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_Out_from,Z_Param_Out_to,FVectorSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenVector ********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenVector2D ****
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		FVector2D from;
		FVector2D to;
		FScriptDelegate setter;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVector2DTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent 2D vector tween.\n\x09 *\n\x09 * Tween an FVector2D value from \\p from to \\p to using the provided setter function.\n\x09 * Exposed as a latent Blueprint node so execution can continue based on the latent step.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param from Starting 2D vector.\n\x09 * @param to Target 2D vector.\n\x09 * @param setter Callback used to apply interpolated FVector2D values.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVector2DTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent 2D vector tween.\n\nTween an FVector2D value from \\p from to \\p to using the provided setter function.\nExposed as a latent Blueprint node so execution can continue based on the latent step.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param from Starting 2D vector.\n@param to Target 2D vector.\n@param setter Callback used to apply interpolated FVector2D values.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVector2DTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_from_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateLatentTweenVector2D constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_from;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_setter;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCreateLatentTweenVector2D constinit property declarations *****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateLatentTweenVector2D Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, from), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, to), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3010275275
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateLatentTweenVector2D Property Definitions ****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenCreateLatentTweenVector2D", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::QuickTweenLatentLibrary_eventQuickTweenCreateLatentTweenVector2D_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenVector2D)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_STRUCT_REF(FVector2D,Z_Param_Out_from);
	P_GET_STRUCT_REF(FVector2D,Z_Param_Out_to);
	P_GET_PROPERTY(FDelegateProperty,Z_Param_setter);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenCreateLatentTweenVector2D(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_Out_from,Z_Param_Out_to,FVector2DSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenCreateLatentTweenVector2D ******

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeColorTo_Image ****
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UImage* widget;
		FColor to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickColorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ChangeColor tween for a UImage widget.\n\x09 *\n\x09 * Tweens the image's color to the specified target color over time.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget UImage widget whose color will be changed.\n\x09 * @param to Target color.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickColorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Color | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ChangeColor tween for a UImage widget.\n\nTweens the image's color to the specified target color over time.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget UImage widget whose color will be changed.\n@param to Target color.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickColorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentChangeColorTo_Image constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentChangeColorTo_Image constinit property declarations *****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentChangeColorTo_Image Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, widget), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, to), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentChangeColorTo_Image Property Definitions ****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentChangeColorTo_Image", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeColorTo_Image_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentChangeColorTo_Image)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UImage,Z_Param_widget);
	P_GET_STRUCT_REF(FColor,Z_Param_Out_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentChangeColorTo_Image(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeColorTo_Image ******

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeDistanceBy_SpringArm 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USpringArmComponent* springArm;
		float by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ChangeDistanceBy tween for a spring arm (by delta).\n\x09 *\n\x09 * Tweens the spring arm's target arm length by adding the given delta to the current length.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param springArm Spring arm component whose length will be changed.\n\x09 * @param by Delta to add to the current arm length.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Float | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ChangeDistanceBy tween for a spring arm (by delta).\n\nTweens the spring arm's target arm length by adding the given delta to the current length.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param springArm Spring arm component whose length will be changed.\n@param by Delta to add to the current arm length.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_springArm_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentChangeDistanceBy_SpringArm constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_springArm;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentChangeDistanceBy_SpringArm constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentChangeDistanceBy_SpringArm Property Definitions *******
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_springArm = { "springArm", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, springArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_springArm_MetaData), NewProp_springArm_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, by), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_springArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentChangeDistanceBy_SpringArm Property Definitions *********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentChangeDistanceBy_SpringArm", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceBy_SpringArm_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentChangeDistanceBy_SpringArm)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USpringArmComponent,Z_Param_springArm);
	P_GET_PROPERTY(FFloatProperty,Z_Param_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentChangeDistanceBy_SpringArm(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_springArm,Z_Param_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeDistanceBy_SpringArm 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeDistanceTo_SpringArm 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USpringArmComponent* springArm;
		float to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ChangeDistance tween for a spring arm (to target).\n\x09 *\n\x09 * Tweens the spring arm's target arm length to the specified value.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param springArm Spring arm component whose length will be changed.\n\x09 * @param to Target arm length.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Float | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ChangeDistance tween for a spring arm (to target).\n\nTweens the spring arm's target arm length to the specified value.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param springArm Spring arm component whose length will be changed.\n@param to Target arm length.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_springArm_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentChangeDistanceTo_SpringArm constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_springArm;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentChangeDistanceTo_SpringArm constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentChangeDistanceTo_SpringArm Property Definitions *******
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_springArm = { "springArm", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, springArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_springArm_MetaData), NewProp_springArm_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_springArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentChangeDistanceTo_SpringArm Property Definitions *********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentChangeDistanceTo_SpringArm", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeDistanceTo_SpringArm_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentChangeDistanceTo_SpringArm)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USpringArmComponent,Z_Param_springArm);
	P_GET_PROPERTY(FFloatProperty,Z_Param_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentChangeDistanceTo_SpringArm(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_springArm,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeDistanceTo_SpringArm 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeFovTo_Camera *****
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UCameraComponent* camera;
		float to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ChangeFov tween for a camera component.\n\x09 *\n\x09 * Tweens the camera's field of view to the target value over time.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param camera Camera component whose FOV will be changed.\n\x09 * @param to Target FOV value in degrees.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Float | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ChangeFov tween for a camera component.\n\nTweens the camera's field of view to the target value over time.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param camera Camera component whose FOV will be changed.\n@param to Target FOV value in degrees.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_camera_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentChangeFovTo_Camera constinit property declarations ****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_camera;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentChangeFovTo_Camera constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentChangeFovTo_Camera Property Definitions ***************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_camera = { "camera", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_camera_MetaData), NewProp_camera_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentChangeFovTo_Camera Property Definitions *****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentChangeFovTo_Camera", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeFovTo_Camera_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentChangeFovTo_Camera)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UCameraComponent,Z_Param_camera);
	P_GET_PROPERTY(FFloatProperty,Z_Param_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentChangeFovTo_Camera(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_camera,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeFovTo_Camera *******

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeOpacityTo_Widget *
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UWidget* widget;
		float to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ChangeOpacity tween for a generic widget.\n\x09 *\n\x09 * Tweens a widget's opacity to the given value over the specified duration.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget Target widget whose opacity will be changed.\n\x09 * @param to Target opacity value (0.0 - 1.0).\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Float | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ChangeOpacity tween for a generic widget.\n\nTweens a widget's opacity to the given value over the specified duration.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget Target widget whose opacity will be changed.\n@param to Target opacity value (0.0 - 1.0).\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentChangeOpacityTo_Widget constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentChangeOpacityTo_Widget constinit property declarations **
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentChangeOpacityTo_Widget Property Definitions ***********
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentChangeOpacityTo_Widget Property Definitions *************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentChangeOpacityTo_Widget", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentChangeOpacityTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentChangeOpacityTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UWidget,Z_Param_widget);
	P_GET_PROPERTY(FFloatProperty,Z_Param_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentChangeOpacityTo_Widget(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentChangeOpacityTo_Widget ***

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentColorParameterBy_Material 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UMaterialInstanceDynamic* material;
		FName parameterName;
		FColor by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickColorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ColorParameterBy tween for a material instance.\n\x09 *\n\x09 * Tweens the named color parameter on the dynamic material by the specified scalar delta.\n\x09 * Typically used to adjust color channels uniformly by a value; implementation may interpret\n\x09 * the delta according to the material setup.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param material Dynamic material instance to modify.\n\x09 * @param parameterName Name of the color parameter.\n\x09 * @param by FColor delta to apply.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickColorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Color | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ColorParameterBy tween for a material instance.\n\nTweens the named color parameter on the dynamic material by the specified scalar delta.\nTypically used to adjust color channels uniformly by a value; implementation may interpret\nthe delta according to the material setup.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param material Dynamic material instance to modify.\n@param parameterName Name of the color parameter.\n@param by FColor delta to apply.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickColorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_by_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentColorParameterBy_Material constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_material;
	static const UECodeGen_Private::FNamePropertyParams NewProp_parameterName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentColorParameterBy_Material constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentColorParameterBy_Material Property Definitions ********
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, by), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentColorParameterBy_Material Property Definitions **********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentColorParameterBy_Material", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterBy_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentColorParameterBy_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UMaterialInstanceDynamic,Z_Param_material);
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_parameterName);
	P_GET_STRUCT_REF(FColor,Z_Param_Out_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentColorParameterBy_Material(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentColorParameterBy_Material 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentColorParameterTo_Material 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UMaterialInstanceDynamic* material;
		FName parameterName;
		FColor to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickColorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ColorParameterTo tween for a material instance.\n\x09 *\n\x09 * Tweens the named color parameter on the dynamic material to the target color.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param material Dynamic material instance to modify.\n\x09 * @param parameterName Name of the color parameter.\n\x09 * @param to Target color value.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickColorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Color | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ColorParameterTo tween for a material instance.\n\nTweens the named color parameter on the dynamic material to the target color.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param material Dynamic material instance to modify.\n@param parameterName Name of the color parameter.\n@param to Target color value.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickColorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentColorParameterTo_Material constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_material;
	static const UECodeGen_Private::FNamePropertyParams NewProp_parameterName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentColorParameterTo_Material constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentColorParameterTo_Material Property Definitions ********
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, to), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentColorParameterTo_Material Property Definitions **********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentColorParameterTo_Material", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentColorParameterTo_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentColorParameterTo_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UMaterialInstanceDynamic,Z_Param_material);
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_parameterName);
	P_GET_STRUCT_REF(FColor,Z_Param_Out_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentColorParameterTo_Material(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentColorParameterTo_Material 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentLookAt_SceneComponent **
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		FVector to;
		bool bUseShortestPath;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickRotatorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent LookAt rotator tween for a scene component.\n\x09 *\n\x09 * Rotates the component to look at the specified target location.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component to rotate.\n\x09 * @param to Target location to look at.\n\x09 * @param bUseShortestPath When true, interpolation will use the shortest rotational path.\n\x09 * @param duration Duration of the rotation in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickRotatorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_bUseShortestPath", "true" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Rotator | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent LookAt rotator tween for a scene component.\n\nRotates the component to look at the specified target location.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component to rotate.\n@param to Target location to look at.\n@param bUseShortestPath When true, interpolation will use the shortest rotational path.\n@param duration Duration of the rotation in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickRotatorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentLookAt_SceneComponent constinit property declarations *
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static void NewProp_bUseShortestPath_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseShortestPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentLookAt_SceneComponent constinit property declarations ***
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentLookAt_SceneComponent Property Definitions ************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentLookAt_SceneComponent Property Definitions **************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentLookAt_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentLookAt_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentLookAt_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_to);
	P_GET_UBOOL(Z_Param_bUseShortestPath);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentLookAt_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_Out_to,Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentLookAt_SceneComponent ****

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveBy_SceneComponent **
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		FVector by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		EQuickTweenSpace space;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVectorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent MoveBy tween for a scene component.\n\x09 *\n\x09 * Moves the provided scene component by the specified delta vector over time.\n\x09 * Exposed as a latent Blueprint node; execution can continue based on the\n\x09 * expanded \\c EQuickTweenLatentSteps output pins.\n\x09 *\n\x09 * @param worldContextObject World context used for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component to move.\n\x09 * @param by Delta vector to add to the component's current location.\n\x09 * @param duration Duration of the move in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve; overrides \\c easeType when provided.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param space Whether movement uses world or local space.\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_space", "WorldSpace" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent MoveBy tween for a scene component.\n\nMoves the provided scene component by the specified delta vector over time.\nExposed as a latent Blueprint node; execution can continue based on the\nexpanded \\c EQuickTweenLatentSteps output pins.\n\n@param worldContextObject World context used for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component to move.\n@param by Delta vector to add to the component's current location.\n@param duration Duration of the move in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve; overrides \\c easeType when provided.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param space Whether movement uses world or local space.\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVectorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_by_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentMoveBy_SceneComponent constinit property declarations *
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_space_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_space;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentMoveBy_SceneComponent constinit property declarations ***
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentMoveBy_SceneComponent Property Definitions ************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, by), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentMoveBy_SceneComponent Property Definitions **************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentMoveBy_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentMoveBy_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_ENUM(EQuickTweenSpace,Z_Param_space);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentMoveBy_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveBy_SceneComponent ****

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveBy_Widget **********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UWidget* widget;
		FVector2D by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVector2DTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent MoveBy tween for a UWidget.\n\x09 *\n\x09 * Moves the provided widget by the specified delta over the given duration.\n\x09 * Exposed as a latent Blueprint node; execution can continue based on the\n\x09 * expanded \\c EQuickTweenLatentSteps output pins.\n\x09 *\n\x09 * @param worldContextObject World context used for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget Target widget to move.\n\x09 * @param by Delta 2D vector to add to the widget's current position.\n\x09 * @param duration Duration of the move in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve; overrides \\c easeType when provided.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVector2DTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector2D | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent MoveBy tween for a UWidget.\n\nMoves the provided widget by the specified delta over the given duration.\nExposed as a latent Blueprint node; execution can continue based on the\nexpanded \\c EQuickTweenLatentSteps output pins.\n\n@param worldContextObject World context used for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget Target widget to move.\n@param by Delta 2D vector to add to the widget's current position.\n@param duration Duration of the move in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve; overrides \\c easeType when provided.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVector2DTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_by_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentMoveBy_Widget constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FStructPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentMoveBy_Widget constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentMoveBy_Widget Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, by), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentMoveBy_Widget Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentMoveBy_Widget", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveBy_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentMoveBy_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UWidget,Z_Param_widget);
	P_GET_STRUCT_REF(FVector2D,Z_Param_Out_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentMoveBy_Widget(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveBy_Widget ************

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveTo_SceneComponent **
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		FVector to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		EQuickTweenSpace space;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVectorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent MoveTo tween for a scene component.\n\x09 *\n\x09 * Moves the provided scene component to the target location over time.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component to move.\n\x09 * @param to Target world/local location depending on \\p space.\n\x09 * @param duration Duration of the move in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param space Whether the target is in WorldSpace or LocalSpace.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_space", "WorldSpace" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent MoveTo tween for a scene component.\n\nMoves the provided scene component to the target location over time.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component to move.\n@param to Target world/local location depending on \\p space.\n@param duration Duration of the move in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param space Whether the target is in WorldSpace or LocalSpace.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVectorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentMoveTo_SceneComponent constinit property declarations *
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_space_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_space;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentMoveTo_SceneComponent constinit property declarations ***
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentMoveTo_SceneComponent Property Definitions ************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentMoveTo_SceneComponent Property Definitions **************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentMoveTo_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentMoveTo_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_ENUM(EQuickTweenSpace,Z_Param_space);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentMoveTo_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveTo_SceneComponent ****

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveTo_Widget **********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UWidget* widget;
		FVector2D to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVector2DTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent MoveTo tween for a UWidget.\n\x09 *\n\x09 * Moves the provided widget to the target position over the given duration.\n\x09 * Exposed as a latent Blueprint node; execution can continue based on the\n\x09 * expanded \\c EQuickTweenLatentSteps output pins.\n\x09 *\n\x09 * @param worldContextObject World context used for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget Target widget to move.\n\x09 * @param to Target local position for the widget.\n\x09 * @param duration Duration of the move in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve; when provided it overrides \\c easeType.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVector2DTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent MoveTo tween for a UWidget.\n\nMoves the provided widget to the target position over the given duration.\nExposed as a latent Blueprint node; execution can continue based on the\nexpanded \\c EQuickTweenLatentSteps output pins.\n\n@param worldContextObject World context used for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget Target widget to move.\n@param to Target local position for the widget.\n@param duration Duration of the move in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve; when provided it overrides \\c easeType.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVector2DTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentMoveTo_Widget constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentMoveTo_Widget constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentMoveTo_Widget Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, to), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentMoveTo_Widget Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentMoveTo_Widget", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentMoveTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentMoveTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UWidget,Z_Param_widget);
	P_GET_STRUCT_REF(FVector2D,Z_Param_Out_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentMoveTo_Widget(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentMoveTo_Widget ************

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateAroundPoint_SceneComponent 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		float from;
		float to;
		FVector point;
		FVector normal;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent RotateAround tween for a scene component.\n\x09 *\n\x09 * Tweens a rotation value (float) around a point and axis (normal).\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component that will be rotated around the point.\n\x09 * @param from Starting angle in degrees.\n\x09 * @param to Target angle in degrees.\n\x09 * @param point Center point of rotation.\n\x09 * @param normal Axis (normal) around which to rotate.\n\x09 * @param duration Duration of the rotation in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Float | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent RotateAround tween for a scene component.\n\nTweens a rotation value (float) around a point and axis (normal).\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component that will be rotated around the point.\n@param from Starting angle in degrees.\n@param to Target angle in degrees.\n@param point Center point of rotation.\n@param normal Axis (normal) around which to rotate.\n@param duration Duration of the rotation in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_point_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_normal_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentRotateAroundPoint_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_from;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_to;
	static const UECodeGen_Private::FStructPropertyParams NewProp_point;
	static const UECodeGen_Private::FStructPropertyParams NewProp_normal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentRotateAroundPoint_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentRotateAroundPoint_SceneComponent Property Definitions *
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, from), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_point = { "point", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, point), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_point_MetaData), NewProp_point_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_normal = { "normal", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, normal), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_normal_MetaData), NewProp_normal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_point,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_normal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentRotateAroundPoint_SceneComponent Property Definitions ***
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentRotateAroundPoint_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateAroundPoint_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentRotateAroundPoint_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_PROPERTY(FFloatProperty,Z_Param_from);
	P_GET_PROPERTY(FFloatProperty,Z_Param_to);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_point);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_normal);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentRotateAroundPoint_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_from,Z_Param_to,Z_Param_Out_point,Z_Param_Out_normal,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateAroundPoint_SceneComponent 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateBy_SceneComponent 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		FRotator by;
		bool bUseShortestPath;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		EQuickTweenSpace space;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickRotatorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent RotateBy tween for a scene component.\n\x09 *\n\x09 * Rotates the provided scene component by the specified rotator delta over time.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component to rotate.\n\x09 * @param by Rotation delta to apply (added to current rotation).\n\x09 * @param bUseShortestPath When true, interpolation will use the shortest rotational path.\n\x09 * @param duration Duration of the rotation in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param space Whether rotation is applied in WorldSpace or LocalSpace.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickRotatorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_bUseShortestPath", "true" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_space", "LocalSpace" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Rotator | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent RotateBy tween for a scene component.\n\nRotates the provided scene component by the specified rotator delta over time.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component to rotate.\n@param by Rotation delta to apply (added to current rotation).\n@param bUseShortestPath When true, interpolation will use the shortest rotational path.\n@param duration Duration of the rotation in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param space Whether rotation is applied in WorldSpace or LocalSpace.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickRotatorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_by_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentRotateBy_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_by;
	static void NewProp_bUseShortestPath_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseShortestPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_space_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_space;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentRotateBy_SceneComponent constinit property declarations *
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentRotateBy_SceneComponent Property Definitions **********
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, by), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentRotateBy_SceneComponent Property Definitions ************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentRotateBy_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentRotateBy_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_by);
	P_GET_UBOOL(Z_Param_bUseShortestPath);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_ENUM(EQuickTweenSpace,Z_Param_space);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentRotateBy_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_Out_by,Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateBy_SceneComponent **

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateBy_Widget ********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UWidget* widget;
		float by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent RotateBy tween for a widget.\n\x09 *\n\x09 * Rotates the provided widget by the specified delta over time. Exposed as a latent\n\x09 * Blueprint node so execution can continue based on the latent step.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget Widget to rotate.\n\x09 * @param by Rotation delta to apply (added to current rotation).\n\x09 * @param duration Duration of the rotation in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickRotatorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Rotator | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent RotateBy tween for a widget.\n\nRotates the provided widget by the specified delta over time. Exposed as a latent\nBlueprint node so execution can continue based on the latent step.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget Widget to rotate.\n@param by Rotation delta to apply (added to current rotation).\n@param duration Duration of the rotation in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickRotatorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentRotateBy_Widget constinit property declarations *******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentRotateBy_Widget constinit property declarations *********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentRotateBy_Widget Property Definitions ******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, by), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentRotateBy_Widget Property Definitions ********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentRotateBy_Widget", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateBy_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentRotateBy_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UWidget,Z_Param_widget);
	P_GET_PROPERTY(FFloatProperty,Z_Param_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentRotateBy_Widget(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateBy_Widget **********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateTo_SceneComponent 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		FRotator to;
		bool bUseShortestPath;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		EQuickTweenSpace space;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickRotatorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent RotateTo tween for a scene component.\n\x09 *\n\x09 * Rotates the provided scene component to the target rotator.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component to rotate.\n\x09 * @param to Target rotator (should be in target space).\n\x09 * @param bUseShortestPath When true, interpolation will use the shortest rotational path.\n\x09 * @param duration Duration of the rotation in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param space Whether the target is in WorldSpace or LocalSpace.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickRotatorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_bUseShortestPath", "true" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_space", "LocalSpace" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Rotator | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent RotateTo tween for a scene component.\n\nRotates the provided scene component to the target rotator.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component to rotate.\n@param to Target rotator (should be in target space).\n@param bUseShortestPath When true, interpolation will use the shortest rotational path.\n@param duration Duration of the rotation in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param space Whether the target is in WorldSpace or LocalSpace.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickRotatorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentRotateTo_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static void NewProp_bUseShortestPath_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseShortestPath;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_space_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_space;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentRotateTo_SceneComponent constinit property declarations *
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentRotateTo_SceneComponent Property Definitions **********
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentRotateTo_SceneComponent Property Definitions ************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentRotateTo_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentRotateTo_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_STRUCT_REF(FRotator,Z_Param_Out_to);
	P_GET_UBOOL(Z_Param_bUseShortestPath);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_ENUM(EQuickTweenSpace,Z_Param_space);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentRotateTo_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_Out_to,Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateTo_SceneComponent **

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateTo_Widget ********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UWidget* widget;
		float to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent RotateTo tween for a widget.\n\x09 *\n\x09 * Tweens a widget's rotation value to the target angle over the specified duration.\n\x09 * This is exposed as a latent Blueprint node so execution can continue based on\n\x09 * the latent step enum (EQuickTweenLatentSteps).\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget Target widget whose rotation will be changed.\n\x09 * @param to Target rotation value (in degrees).\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Flo | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent RotateTo tween for a widget.\n\nTweens a widget's rotation value to the target angle over the specified duration.\nThis is exposed as a latent Blueprint node so execution can continue based on\nthe latent step enum (EQuickTweenLatentSteps).\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget Target widget whose rotation will be changed.\n@param to Target rotation value (in degrees).\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentRotateTo_Widget constinit property declarations *******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentRotateTo_Widget constinit property declarations *********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentRotateTo_Widget Property Definitions ******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentRotateTo_Widget Property Definitions ********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentRotateTo_Widget", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentRotateTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentRotateTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UWidget,Z_Param_widget);
	P_GET_PROPERTY(FFloatProperty,Z_Param_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentRotateTo_Widget(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentRotateTo_Widget **********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentScalarParameterBy_Material 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UMaterialInstanceDynamic* material;
		FName parameterName;
		float by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ScalarParameterBy tween for a material instance.\n\x09 *\n\x09 * Tweens the named scalar parameter on the dynamic material by the specified delta.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param material Dynamic material instance to modify.\n\x09 * @param parameterName Name of the scalar parameter.\n\x09 * @param by Delta to add to the current scalar parameter.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Float | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ScalarParameterBy tween for a material instance.\n\nTweens the named scalar parameter on the dynamic material by the specified delta.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param material Dynamic material instance to modify.\n@param parameterName Name of the scalar parameter.\n@param by Delta to add to the current scalar parameter.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentScalarParameterBy_Material constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_material;
	static const UECodeGen_Private::FNamePropertyParams NewProp_parameterName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentScalarParameterBy_Material constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentScalarParameterBy_Material Property Definitions *******
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, by), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentScalarParameterBy_Material Property Definitions *********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentScalarParameterBy_Material", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterBy_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentScalarParameterBy_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UMaterialInstanceDynamic,Z_Param_material);
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_parameterName);
	P_GET_PROPERTY(FFloatProperty,Z_Param_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentScalarParameterBy_Material(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_material,Z_Param_Out_parameterName,Z_Param_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentScalarParameterBy_Material 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentScalarParameterTo_Material 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UMaterialInstanceDynamic* material;
		FName parameterName;
		float to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickFloatTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ScalarParameterTo tween for a material instance.\n\x09 *\n\x09 * Tweens the named scalar parameter on the dynamic material to the target value.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param material Dynamic material instance to modify.\n\x09 * @param parameterName Name of the scalar parameter.\n\x09 * @param to Target scalar value.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Float | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ScalarParameterTo tween for a material instance.\n\nTweens the named scalar parameter on the dynamic material to the target value.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param material Dynamic material instance to modify.\n@param parameterName Name of the scalar parameter.\n@param to Target scalar value.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickFloatTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentScalarParameterTo_Material constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_material;
	static const UECodeGen_Private::FNamePropertyParams NewProp_parameterName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentScalarParameterTo_Material constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentScalarParameterTo_Material Property Definitions *******
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentScalarParameterTo_Material Property Definitions *********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentScalarParameterTo_Material", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScalarParameterTo_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentScalarParameterTo_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UMaterialInstanceDynamic,Z_Param_material);
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_parameterName);
	P_GET_PROPERTY(FFloatProperty,Z_Param_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentScalarParameterTo_Material(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_material,Z_Param_Out_parameterName,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentScalarParameterTo_Material 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleBy_SceneComponent *
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		FVector by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		EQuickTweenSpace space;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVectorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ScaleBy tween for a scene component.\n\x09 *\n\x09 * Tweens the scale of the provided scene component by the given delta.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component whose scale will be adjusted.\n\x09 * @param by Delta scale to be applied to current scale.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param space Whether the delta applies in WorldSpace or LocalSpace.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_space", "LocalSpace" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vecto | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ScaleBy tween for a scene component.\n\nTweens the scale of the provided scene component by the given delta.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component whose scale will be adjusted.\n@param by Delta scale to be applied to current scale.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param space Whether the delta applies in WorldSpace or LocalSpace.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVectorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_by_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentScaleBy_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_space_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_space;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentScaleBy_SceneComponent constinit property declarations **
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentScaleBy_SceneComponent Property Definitions ***********
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, by), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentScaleBy_SceneComponent Property Definitions *************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentScaleBy_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentScaleBy_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_ENUM(EQuickTweenSpace,Z_Param_space);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentScaleBy_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleBy_SceneComponent ***

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleBy_Widget *********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UWidget* widget;
		FVector2D by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVector2DTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ScaleBy tween for a UWidget.\n\x09 *\n\x09 * Tweens the widget's render scale by the specified delta.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget Target widget whose scale will be changed.\n\x09 * @param by 2D delta scale to apply to current scale.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVector2DTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector2D | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ScaleBy tween for a UWidget.\n\nTweens the widget's render scale by the specified delta.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget Target widget whose scale will be changed.\n@param by 2D delta scale to apply to current scale.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVector2DTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_by_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentScaleBy_Widget constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FStructPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentScaleBy_Widget constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentScaleBy_Widget Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, by), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentScaleBy_Widget Property Definitions *********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentScaleBy_Widget", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleBy_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentScaleBy_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UWidget,Z_Param_widget);
	P_GET_STRUCT_REF(FVector2D,Z_Param_Out_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentScaleBy_Widget(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleBy_Widget ***********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleTo_SceneComponent *
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		USceneComponent* component;
		FVector to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		EQuickTweenSpace space;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVectorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ScaleTo tween for a scene component.\n\x09 *\n\x09 * Tweens the scale of the provided scene component to \\p to.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param component Scene component whose scale will be tweened.\n\x09 * @param to Target scale.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior.\n\x09 * @param space Whether the target is in WorldSpace or LocalSpace.\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_space", "LocalSpace" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ScaleTo tween for a scene component.\n\nTweens the scale of the provided scene component to \\p to.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param component Scene component whose scale will be tweened.\n@param to Target scale.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior.\n@param space Whether the target is in WorldSpace or LocalSpace.\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVectorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_component_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentScaleTo_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_component;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_space_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_space;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentScaleTo_SceneComponent constinit property declarations **
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentScaleTo_SceneComponent Property Definitions ***********
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentScaleTo_SceneComponent Property Definitions *************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentScaleTo_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentScaleTo_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(USceneComponent,Z_Param_component);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_ENUM(EQuickTweenSpace,Z_Param_space);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentScaleTo_SceneComponent(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_component,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleTo_SceneComponent ***

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleTo_Widget *********
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UWidget* widget;
		FVector2D to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVector2DTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent ScaleTo tween for a UWidget.\n\x09 *\n\x09 * Tweens the widget's render scale to the specified target over time.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param widget Target widget whose scale will be changed.\n\x09 * @param to Target 2D scale.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve.\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVector2DTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector2D | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent ScaleTo tween for a UWidget.\n\nTweens the widget's render scale to the specified target over time.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param widget Target widget whose scale will be changed.\n@param to Target 2D scale.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve.\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVector2DTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentScaleTo_Widget constinit property declarations ********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_widget;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentScaleTo_Widget constinit property declarations **********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentScaleTo_Widget Property Definitions *******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, to), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentScaleTo_Widget Property Definitions *********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentScaleTo_Widget", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentScaleTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentScaleTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UWidget,Z_Param_widget);
	P_GET_STRUCT_REF(FVector2D,Z_Param_Out_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentScaleTo_Widget(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_widget,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentScaleTo_Widget ***********

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentVectorParameterBy_Material 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UMaterialInstanceDynamic* material;
		FName parameterName;
		FVector by;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVectorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent VectorParameterBy tween for a material instance.\n\x09 *\n\x09 * Tweens the named vector parameter on the dynamic material by the provided delta.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param material Dynamic material instance to modify.\n\x09 * @param parameterName Name of the vector parameter.\n\x09 * @param by Vector delta to add to the current parameter value.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent VectorParameterBy tween for a material instance.\n\nTweens the named vector parameter on the dynamic material by the provided delta.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param material Dynamic material instance to modify.\n@param parameterName Name of the vector parameter.\n@param by Vector delta to add to the current parameter value.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVectorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_by_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentVectorParameterBy_Material constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_material;
	static const UECodeGen_Private::FNamePropertyParams NewProp_parameterName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_by;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentVectorParameterBy_Material constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentVectorParameterBy_Material Property Definitions *******
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, by), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentVectorParameterBy_Material Property Definitions *********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentVectorParameterBy_Material", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterBy_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentVectorParameterBy_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UMaterialInstanceDynamic,Z_Param_material);
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_parameterName);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_by);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentVectorParameterBy_Material(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentVectorParameterBy_Material 

// ********** Begin Class UQuickTweenLatentLibrary Function QuickTweenLatentVectorParameterTo_Material 
struct Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics
{
	struct QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms
	{
		UObject* worldContextObject;
		FLatentActionInfo latentInfo;
		EQuickTweenLatentSteps latentStep;
		UMaterialInstanceDynamic* material;
		FName parameterName;
		FVector to;
		float duration;
		float timeScale;
		EEaseType easeType;
		UCurveFloat* easeCurve;
		int32 loops;
		ELoopType loopType;
		FString tweenTag;
		bool bShouldAutoKill;
		bool bShouldPlayWhilePaused;
		bool bShouldAutoPlay;
		UQuickVectorTween* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Create a latent VectorParameterTo tween for a material instance.\n\x09 *\n\x09 * Tweens the named vector parameter on the dynamic material to the target vector value.\n\x09 *\n\x09 * @param worldContextObject World context for latent action execution.\n\x09 * @param latentInfo Latent action execution info supplied by Blueprint.\n\x09 * @param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n\x09 * @param material Dynamic material instance to modify.\n\x09 * @param parameterName Name of the vector parameter.\n\x09 * @param to Target vector value.\n\x09 * @param duration Duration of the loop in seconds.\n\x09 * @param timeScale Global time scale multiplier for the tween.\n\x09 * @param easeType Built-in easing type to apply.\n\x09 * @param easeCurve Optional custom ease curve (overrides easeType when provided).\n\x09 * @param loops Number of times the tween will loop.\n\x09 * @param loopType Looping behavior (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag for identification.\n\x09 * @param bShouldAutoKill If true the tween will be auto-killed when finished.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while paused.\n\x09 * @param bShouldAutoPlay If true the tween will start immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_easeCurve", "None" },
		{ "CPP_Default_easeType", "Linear" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_timeScale", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "ExpandEnumAsExecs", "latentStep" },
		{ "HidePin", "latentStep" },
		{ "Keywords", "Tween | Vector | Create | Make | Latent" },
		{ "Latent", "" },
		{ "LatentInfo", "latentInfo" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Create a latent VectorParameterTo tween for a material instance.\n\nTweens the named vector parameter on the dynamic material to the target vector value.\n\n@param worldContextObject World context for latent action execution.\n@param latentInfo Latent action execution info supplied by Blueprint.\n@param latentStep Enum reference expanded as exec pins to control flow from Blueprint.\n@param material Dynamic material instance to modify.\n@param parameterName Name of the vector parameter.\n@param to Target vector value.\n@param duration Duration of the loop in seconds.\n@param timeScale Global time scale multiplier for the tween.\n@param easeType Built-in easing type to apply.\n@param easeCurve Optional custom ease curve (overrides easeType when provided).\n@param loops Number of times the tween will loop.\n@param loopType Looping behavior (Restart, PingPong, etc.).\n@param tweenTag Optional tag for identification.\n@param bShouldAutoKill If true the tween will be auto-killed when finished.\n@param bShouldPlayWhilePaused If true the tween will update while paused.\n@param bShouldAutoPlay If true the tween will start immediately after creation.\n@return Pointer to the created UQuickVectorTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_to_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenLatentVectorParameterTo_Material constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_latentInfo;
	static const UECodeGen_Private::FBytePropertyParams NewProp_latentStep_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_latentStep;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_material;
	static const UECodeGen_Private::FNamePropertyParams NewProp_parameterName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_to;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_timeScale;
	static const UECodeGen_Private::FBytePropertyParams NewProp_easeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_easeType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_easeCurve;
	static const UECodeGen_Private::FIntPropertyParams NewProp_loops;
	static const UECodeGen_Private::FBytePropertyParams NewProp_loopType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_loopType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static void NewProp_bShouldAutoKill_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoKill;
	static void NewProp_bShouldPlayWhilePaused_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldPlayWhilePaused;
	static void NewProp_bShouldAutoPlay_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldAutoPlay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenLatentVectorParameterTo_Material constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLatentVectorParameterTo_Material Property Definitions *******
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_latentInfo = { "latentInfo", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, latentInfo), Z_Construct_UScriptStruct_FLatentActionInfo, METADATA_PARAMS(0, nullptr) }; // 2463020907
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_latentStep_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_latentStep = { "latentStep", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, latentStep), Z_Construct_UEnum_QuickTween_EQuickTweenLatentSteps, METADATA_PARAMS(0, nullptr) }; // 193244591
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_latentInfo,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_latentStep_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_latentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLatentVectorParameterTo_Material Property Definitions *********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLatentLibrary, nullptr, "QuickTweenLatentVectorParameterTo_Material", 	Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::QuickTweenLatentLibrary_eventQuickTweenLatentVectorParameterTo_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLatentLibrary::execQuickTweenLatentVectorParameterTo_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_STRUCT(FLatentActionInfo,Z_Param_latentInfo);
	P_GET_ENUM_REF(EQuickTweenLatentSteps,Z_Param_Out_latentStep);
	P_GET_OBJECT(UMaterialInstanceDynamic,Z_Param_material);
	P_GET_PROPERTY_REF(FNameProperty,Z_Param_Out_parameterName);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_to);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FFloatProperty,Z_Param_timeScale);
	P_GET_ENUM(EEaseType,Z_Param_easeType);
	P_GET_OBJECT(UCurveFloat,Z_Param_easeCurve);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLatentLibrary::QuickTweenLatentVectorParameterTo_Material(Z_Param_worldContextObject,Z_Param_latentInfo,(EQuickTweenLatentSteps&)(Z_Param_Out_latentStep),Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLatentLibrary Function QuickTweenLatentVectorParameterTo_Material 

// ********** Begin Class UQuickTweenLatentLibrary *************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickTweenLatentLibrary;
UClass* UQuickTweenLatentLibrary::GetPrivateStaticClass()
{
	using TClass = UQuickTweenLatentLibrary;
	if (!Z_Registration_Info_UClass_UQuickTweenLatentLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickTweenLatentLibrary"),
			Z_Registration_Info_UClass_UQuickTweenLatentLibrary.InnerSingleton,
			StaticRegisterNativesUQuickTweenLatentLibrary,
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
	return Z_Registration_Info_UClass_UQuickTweenLatentLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickTweenLatentLibrary_NoRegister()
{
	return UQuickTweenLatentLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickTweenLatentLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Blueprint-accessible library exposing latent QuickTween creation helpers.\n *\n * This class provides static UFUNCTIONs that create various types of tweens and sequences\n * as latent blueprint nodes. Each function accepts a latent info struct and an\n * ExpandEnumAsExecs parameter (EQuickTweenLatentSteps) so execution can continue\n * based on the tween step in Blueprint.\n */" },
		{ "IncludePath", "Blueprint/QuickTweenLatentLibrary.h" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLatentLibrary.h" },
		{ "ToolTip", "Blueprint-accessible library exposing latent QuickTween creation helpers.\n\nThis class provides static UFUNCTIONs that create various types of tweens and sequences\nas latent blueprint nodes. Each function accepts a latent info struct and an\nExpandEnumAsExecs parameter (EQuickTweenLatentSteps) so execution can continue\nbased on the tween step in Blueprint." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickTweenLatentLibrary constinit property declarations *****************
// ********** End Class UQuickTweenLatentLibrary constinit property declarations *******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentSequence"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentSequence },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentTweenColor"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenColor },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentTweenEmpty"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenEmpty },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentTweenFloat"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenFloat },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentTweenInt"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenInt },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentTweenRotator"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenRotator },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentTweenVector"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenVector },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateLatentTweenVector2D"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenCreateLatentTweenVector2D },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentChangeColorTo_Image"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentChangeColorTo_Image },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentChangeDistanceBy_SpringArm"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentChangeDistanceBy_SpringArm },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentChangeDistanceTo_SpringArm"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentChangeDistanceTo_SpringArm },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentChangeFovTo_Camera"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentChangeFovTo_Camera },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentChangeOpacityTo_Widget"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentChangeOpacityTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentColorParameterBy_Material"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentColorParameterBy_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentColorParameterTo_Material"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentColorParameterTo_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentLookAt_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentLookAt_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentMoveBy_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentMoveBy_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentMoveBy_Widget"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentMoveBy_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentMoveTo_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentMoveTo_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentMoveTo_Widget"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentMoveTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentRotateAroundPoint_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentRotateAroundPoint_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentRotateBy_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentRotateBy_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentRotateBy_Widget"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentRotateBy_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentRotateTo_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentRotateTo_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentRotateTo_Widget"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentRotateTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentScalarParameterBy_Material"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentScalarParameterBy_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentScalarParameterTo_Material"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentScalarParameterTo_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentScaleBy_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentScaleBy_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentScaleBy_Widget"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentScaleBy_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentScaleTo_SceneComponent"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentScaleTo_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentScaleTo_Widget"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentScaleTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentVectorParameterBy_Material"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentVectorParameterBy_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLatentVectorParameterTo_Material"), .Pointer = &UQuickTweenLatentLibrary::execQuickTweenLatentVectorParameterTo_Material },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentSequence, "QuickTweenCreateLatentSequence" }, // 932976031
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenColor, "QuickTweenCreateLatentTweenColor" }, // 2682806333
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenEmpty, "QuickTweenCreateLatentTweenEmpty" }, // 3329154910
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenFloat, "QuickTweenCreateLatentTweenFloat" }, // 1071034249
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenInt, "QuickTweenCreateLatentTweenInt" }, // 931662672
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenRotator, "QuickTweenCreateLatentTweenRotator" }, // 1002839777
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector, "QuickTweenCreateLatentTweenVector" }, // 1313514532
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenCreateLatentTweenVector2D, "QuickTweenCreateLatentTweenVector2D" }, // 2955207144
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeColorTo_Image, "QuickTweenLatentChangeColorTo_Image" }, // 2777904902
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceBy_SpringArm, "QuickTweenLatentChangeDistanceBy_SpringArm" }, // 3450605703
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeDistanceTo_SpringArm, "QuickTweenLatentChangeDistanceTo_SpringArm" }, // 1491344829
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeFovTo_Camera, "QuickTweenLatentChangeFovTo_Camera" }, // 1355584572
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentChangeOpacityTo_Widget, "QuickTweenLatentChangeOpacityTo_Widget" }, // 1032848293
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterBy_Material, "QuickTweenLatentColorParameterBy_Material" }, // 419291945
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentColorParameterTo_Material, "QuickTweenLatentColorParameterTo_Material" }, // 181330122
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentLookAt_SceneComponent, "QuickTweenLatentLookAt_SceneComponent" }, // 493904709
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_SceneComponent, "QuickTweenLatentMoveBy_SceneComponent" }, // 3666117700
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveBy_Widget, "QuickTweenLatentMoveBy_Widget" }, // 2415711991
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_SceneComponent, "QuickTweenLatentMoveTo_SceneComponent" }, // 2144457557
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentMoveTo_Widget, "QuickTweenLatentMoveTo_Widget" }, // 388065257
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateAroundPoint_SceneComponent, "QuickTweenLatentRotateAroundPoint_SceneComponent" }, // 1207433973
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_SceneComponent, "QuickTweenLatentRotateBy_SceneComponent" }, // 2231347805
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateBy_Widget, "QuickTweenLatentRotateBy_Widget" }, // 3905836840
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_SceneComponent, "QuickTweenLatentRotateTo_SceneComponent" }, // 805050708
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentRotateTo_Widget, "QuickTweenLatentRotateTo_Widget" }, // 2953101991
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterBy_Material, "QuickTweenLatentScalarParameterBy_Material" }, // 1937031374
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScalarParameterTo_Material, "QuickTweenLatentScalarParameterTo_Material" }, // 2000712447
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_SceneComponent, "QuickTweenLatentScaleBy_SceneComponent" }, // 2403056317
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleBy_Widget, "QuickTweenLatentScaleBy_Widget" }, // 1770723906
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_SceneComponent, "QuickTweenLatentScaleTo_SceneComponent" }, // 2773632640
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentScaleTo_Widget, "QuickTweenLatentScaleTo_Widget" }, // 1089814844
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterBy_Material, "QuickTweenLatentVectorParameterBy_Material" }, // 1042042782
		{ &Z_Construct_UFunction_UQuickTweenLatentLibrary_QuickTweenLatentVectorParameterTo_Material, "QuickTweenLatentVectorParameterTo_Material" }, // 1343877530
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickTweenLatentLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickTweenLatentLibrary_Statics
UObject* (*const Z_Construct_UClass_UQuickTweenLatentLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenLatentLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickTweenLatentLibrary_Statics::ClassParams = {
	&UQuickTweenLatentLibrary::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenLatentLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickTweenLatentLibrary_Statics::Class_MetaDataParams)
};
void UQuickTweenLatentLibrary::StaticRegisterNativesUQuickTweenLatentLibrary()
{
	UClass* Class = UQuickTweenLatentLibrary::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickTweenLatentLibrary_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickTweenLatentLibrary()
{
	if (!Z_Registration_Info_UClass_UQuickTweenLatentLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickTweenLatentLibrary.OuterSingleton, Z_Construct_UClass_UQuickTweenLatentLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickTweenLatentLibrary.OuterSingleton;
}
UQuickTweenLatentLibrary::UQuickTweenLatentLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickTweenLatentLibrary);
UQuickTweenLatentLibrary::~UQuickTweenLatentLibrary() {}
// ********** End Class UQuickTweenLatentLibrary ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickTweenLatentLibrary, UQuickTweenLatentLibrary::StaticClass, TEXT("UQuickTweenLatentLibrary"), &Z_Registration_Info_UClass_UQuickTweenLatentLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickTweenLatentLibrary), 1016561467U) },
	};
}; // Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h__Script_QuickTween_3216859385{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
