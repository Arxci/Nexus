// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QuickTweenLibrary.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeQuickTweenLibrary() {}

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
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickColorTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickEmptyTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickFloatTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickIntTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickRotatorTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenLibrary();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenLibrary_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenSequence_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVector2DTween_NoRegister();
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickVectorTween_NoRegister();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EEaseType();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_ELoopType();
QUICKTWEEN_API UEnum* Z_Construct_UEnum_QuickTween_EQuickTweenSpace();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature();
QUICKTWEEN_API UFunction* Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature();
UMG_API UClass* Z_Construct_UClass_UImage_NoRegister();
UMG_API UClass* Z_Construct_UClass_UWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_QuickTween();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenChangeColorTo_Image ****************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics
{
	struct QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a color tween that animates a `UImage`'s color/tint to a target `FColor`.\n\x09 *\n\x09 * The widget's start color is sampled on the first update and the tween will\n\x09 * interpolate from that start value to the specified `to` value over `duration`\n\x09 * seconds. Easing can be controlled with a predefined `EEaseType` or by supplying\n\x09 * a custom `UCurveFloat` (`easeCurve` overrides `easeType` when provided).\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param widget The `UImage` widget whose color will be animated.\n\x09 * @param to Target color to animate to.\n\x09 * @param duration Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param timeScale Multiplier applied to the tween time (default 1.0f).\n\x09 * @param easeType Predefined easing function to use for interpolation.\n\x09 * @param easeCurve Optional custom `UCurveFloat` used for easing (overrides `easeType` when provided).\n\x09 * @param loops Number of times to loop the tween (-1 for infinite).\n\x09 * @param loopType How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start playing immediately after creation.\n\x09 * @return Pointer to the created `UQuickColorTween`, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Color | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a color tween that animates a `UImage`'s color/tint to a target `FColor`.\n\nThe widget's start color is sampled on the first update and the tween will\ninterpolate from that start value to the specified `to` value over `duration`\nseconds. Easing can be controlled with a predefined `EEaseType` or by supplying\na custom `UCurveFloat` (`easeCurve` overrides `easeType` when provided).\n\n@param worldContextObject Context object used to find the world for the tween.\n@param widget The `UImage` widget whose color will be animated.\n@param to Target color to animate to.\n@param duration Time in seconds for the tween to complete (default 1.0f).\n@param timeScale Multiplier applied to the tween time (default 1.0f).\n@param easeType Predefined easing function to use for interpolation.\n@param easeCurve Optional custom `UCurveFloat` used for easing (overrides `easeType` when provided).\n@param loops Number of times to loop the tween (-1 for infinite).\n@param loopType How the tween loops (Restart, PingPong, etc.).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start playing immediately after creation.\n@return Pointer to the created `UQuickColorTween`, or nullptr on failure." },
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

// ********** Begin Function QuickTweenChangeColorTo_Image constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenChangeColorTo_Image constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenChangeColorTo_Image Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, widget), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, to), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenChangeColorTo_Image Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenChangeColorTo_Image", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::QuickTweenLibrary_eventQuickTweenChangeColorTo_Image_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenChangeColorTo_Image)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenChangeColorTo_Image(Z_Param_worldContextObject,Z_Param_widget,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenChangeColorTo_Image ******************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenChangeDistanceBy_SpringArm *********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics
{
	struct QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that animates the spring arm's TargetArmLength by a relative amount.\n\x09 *\n\x09 * This function creates a UQuickFloatTween which samples the spring arm's current\n\x09 * TargetArmLength on the first update and interpolates to (start + by) over \\p duration seconds.\n\x09 * Easing is controlled by \\p easeType or overridden by \\p easeCurve when provided.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param springArm The USpringArmComponent whose TargetArmLength will be animated.\n\x09 * @param by Relative change to apply to the spring arm's current TargetArmLength.\n\x09 * @param duration Time in seconds for the tween to complete.\n\x09 * @param timeScale Multiplier applied to the tween time.\n\x09 * @param easeType Predefined easing function to use for interpolation.\n\x09 * @param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops Number of times to loop the tween (-1 for infinite).\n\x09 * @param loopType How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start playing immediately after creation.\n\x09 * @return Pointer to the created UQuickFloatTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Distance | Camera" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that animates the spring arm's TargetArmLength by a relative amount.\n\nThis function creates a UQuickFloatTween which samples the spring arm's current\nTargetArmLength on the first update and interpolates to (start + by) over \\p duration seconds.\nEasing is controlled by \\p easeType or overridden by \\p easeCurve when provided.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param springArm The USpringArmComponent whose TargetArmLength will be animated.\n@param by Relative change to apply to the spring arm's current TargetArmLength.\n@param duration Time in seconds for the tween to complete.\n@param timeScale Multiplier applied to the tween time.\n@param easeType Predefined easing function to use for interpolation.\n@param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops Number of times to loop the tween (-1 for infinite).\n@param loopType How the tween loops (Restart, PingPong, etc.).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start playing immediately after creation.\n@return Pointer to the created UQuickFloatTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_springArm_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenChangeDistanceBy_SpringArm constinit property declarations **
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenChangeDistanceBy_SpringArm constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenChangeDistanceBy_SpringArm Property Definitions *************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_springArm = { "springArm", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, springArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_springArm_MetaData), NewProp_springArm_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, by), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_springArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenChangeDistanceBy_SpringArm Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenChangeDistanceBy_SpringArm", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::QuickTweenLibrary_eventQuickTweenChangeDistanceBy_SpringArm_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenChangeDistanceBy_SpringArm)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenChangeDistanceBy_SpringArm(Z_Param_worldContextObject,Z_Param_springArm,Z_Param_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenChangeDistanceBy_SpringArm ***********

// ********** Begin Class UQuickTweenLibrary Function QuickTweenChangeDistanceTo_SpringArm *********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics
{
	struct QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Animate the spring arm's distance (TargetArmLength) to a target value.\n\x09 *\n\x09 * Creates a UQuickFloatTween that interpolates the spring arm's current arm length\n\x09 * (sampled at the first update) to the provided \\p to value over \\p duration seconds.\n\x09 * Easing can be controlled with a predefined \\p EEaseType or by supplying a custom\n\x09 * \\p UCurveFloat (when provided, \\p easeCurve overrides \\p easeType).\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param springArm          The USpringArmComponent whose TargetArmLength will be animated.\n\x09 * @param to                 Target arm length (world units).\n\x09 * @param duration           Time in seconds for the tween to complete.\n\x09 * @param timeScale          Multiplier applied to the tween time.\n\x09 * @param easeType           Predefined easing function to use for interpolation.\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween (-1 for infinite).\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag           Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n\x09 * @return                   Pointer to the created UQuickFloatTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Distance | Camera" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Animate the spring arm's distance (TargetArmLength) to a target value.\n\nCreates a UQuickFloatTween that interpolates the spring arm's current arm length\n(sampled at the first update) to the provided \\p to value over \\p duration seconds.\nEasing can be controlled with a predefined \\p EEaseType or by supplying a custom\n\\p UCurveFloat (when provided, \\p easeCurve overrides \\p easeType).\n\n@param worldContextObject Context object used to find the world for the tween.\n@param springArm          The USpringArmComponent whose TargetArmLength will be animated.\n@param to                 Target arm length (world units).\n@param duration           Time in seconds for the tween to complete.\n@param timeScale          Multiplier applied to the tween time.\n@param easeType           Predefined easing function to use for interpolation.\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween (-1 for infinite).\n@param loopType           How the tween loops (Restart, PingPong, etc.).\n@param tweenTag           Optional tag to identify the created tween.\n@param bShouldAutoKill    If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n@return                   Pointer to the created UQuickFloatTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_springArm_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenChangeDistanceTo_SpringArm constinit property declarations **
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenChangeDistanceTo_SpringArm constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenChangeDistanceTo_SpringArm Property Definitions *************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_springArm = { "springArm", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, springArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_springArm_MetaData), NewProp_springArm_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_springArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenChangeDistanceTo_SpringArm Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenChangeDistanceTo_SpringArm", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::QuickTweenLibrary_eventQuickTweenChangeDistanceTo_SpringArm_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenChangeDistanceTo_SpringArm)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenChangeDistanceTo_SpringArm(Z_Param_worldContextObject,Z_Param_springArm,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenChangeDistanceTo_SpringArm ***********

// ********** Begin Class UQuickTweenLibrary Function QuickTweenChangeFovTo_Camera *****************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics
{
	struct QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Animate camera field of view (FOV) to a target value.\n\x09 *\n\x09 * Creates a UQuickFloatTween that interpolates the camera's FOV from the\n\x09 * camera's current FOV (sampled at first update) to the provided \\p to value\n\x09 * over \\p duration seconds. Easing can be selected via \\p easeType or an\n\x09 * optional \\p easeCurve (when provided, \\p easeCurve overrides \\p easeType).\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param camera             The UCameraComponent whose FOV will be animated.\n\x09 * @param to                 Target FOV value in degrees.\n\x09 * @param duration           Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param timeScale          Multiplier applied to the tween time (default 1.0f).\n\x09 * @param easeType           Predefined easing function to use (default EEaseType::Linear).\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween (-1 for infinite, default 1).\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n\x09 * @param tweenTag           Optional tag to identify the created tween (default empty).\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete (default false).\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation (default false).\n\x09 * @return                   Pointer to the created UQuickFloatTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Color | Camera" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Animate camera field of view (FOV) to a target value.\n\nCreates a UQuickFloatTween that interpolates the camera's FOV from the\ncamera's current FOV (sampled at first update) to the provided \\p to value\nover \\p duration seconds. Easing can be selected via \\p easeType or an\noptional \\p easeCurve (when provided, \\p easeCurve overrides \\p easeType).\n\n@param worldContextObject Context object used to find the world for the tween.\n@param camera             The UCameraComponent whose FOV will be animated.\n@param to                 Target FOV value in degrees.\n@param duration           Time in seconds for the tween to complete (default 1.0f).\n@param timeScale          Multiplier applied to the tween time (default 1.0f).\n@param easeType           Predefined easing function to use (default EEaseType::Linear).\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween (-1 for infinite, default 1).\n@param loopType           How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n@param tweenTag           Optional tag to identify the created tween (default empty).\n@param bShouldAutoKill    If true the tween will be automatically killed when complete (default false).\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation (default false).\n@return                   Pointer to the created UQuickFloatTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_camera_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenChangeFovTo_Camera constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenChangeFovTo_Camera constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenChangeFovTo_Camera Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_camera = { "camera", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_camera_MetaData), NewProp_camera_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenChangeFovTo_Camera Property Definitions ***********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenChangeFovTo_Camera", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::QuickTweenLibrary_eventQuickTweenChangeFovTo_Camera_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenChangeFovTo_Camera)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenChangeFovTo_Camera(Z_Param_worldContextObject,Z_Param_camera,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenChangeFovTo_Camera *******************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenChangeOpacityTo_Widget *************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics
{
	struct QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that animates a UWidget's opacity to a target value.\n\x09 *\n\x09 * The widget's start opacity is sampled on the first update and the tween will\n\x09 * interpolate from that start value to the specified `to` value over `duration`\n\x09 * seconds. Easing may be controlled using a predefined `EEaseType` or by\n\x09 * supplying a custom `UCurveFloat` (`easeCurve` overrides `easeType` when set).\n\x09 *\n\x09 * @param worldContextObject    Context object used to find the world for the tween.\n\x09 * @param widget                The UWidget whose opacity will be animated.\n\x09 * @param to                    Target opacity value (0.0 = transparent, 1.0 = opaque).\n\x09 * @param duration              Time in seconds for the tween to complete.\n\x09 * @param timeScale             Multiplier applied to the tween time.\n\x09 * @param easeType              Predefined easing function to use for interpolation.\n\x09 * @param easeCurve             Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops                 Number of times to loop the tween (-1 for infinite).\n\x09 * @param loopType              How the tween loops (e.g., Restart, PingPong).\n\x09 * @param tweenTag              Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill       If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n\x09 * @return                      Pointer to the created UQuickFloatTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Color | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that animates a UWidget's opacity to a target value.\n\nThe widget's start opacity is sampled on the first update and the tween will\ninterpolate from that start value to the specified `to` value over `duration`\nseconds. Easing may be controlled using a predefined `EEaseType` or by\nsupplying a custom `UCurveFloat` (`easeCurve` overrides `easeType` when set).\n\n@param worldContextObject    Context object used to find the world for the tween.\n@param widget                The UWidget whose opacity will be animated.\n@param to                    Target opacity value (0.0 = transparent, 1.0 = opaque).\n@param duration              Time in seconds for the tween to complete.\n@param timeScale             Multiplier applied to the tween time.\n@param easeType              Predefined easing function to use for interpolation.\n@param easeCurve             Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops                 Number of times to loop the tween (-1 for infinite).\n@param loopType              How the tween loops (e.g., Restart, PingPong).\n@param tweenTag              Optional tag to identify the created tween.\n@param bShouldAutoKill       If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n@return                      Pointer to the created UQuickFloatTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenChangeOpacityTo_Widget constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenChangeOpacityTo_Widget constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenChangeOpacityTo_Widget Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenChangeOpacityTo_Widget Property Definitions *******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenChangeOpacityTo_Widget", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenChangeOpacityTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenChangeOpacityTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenChangeOpacityTo_Widget(Z_Param_worldContextObject,Z_Param_widget,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenChangeOpacityTo_Widget ***************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenColorParameterBy_Material **********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics
{
	struct QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a color tween that animates a material color parameter by a relative amount.\n\x09 *\n\x09 * The material parameter's starting value is sampled on the first update and the tween will interpolate\n\x09 * from that start value to (start + by) over `duration` seconds. Note: the `by` parameter is provided\n\x09 * as a float and should be interpreted according to how the material parameter consumes the value\n\x09 * (e.g., intensity or a scalar channel modifier).\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param material           The UMaterialInstanceDynamic containing the color parameter.\n\x09 * @param parameterName      The name of the color parameter to animate.\n\x09 * @param by                 Relative FColor value to add to the sampled start value.\n\x09 * @param duration           Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param timeScale          Multiplier applied to the tween time (default 1.0f).\n\x09 * @param easeType           Predefined easing function to use for interpolation (default EEaseType::Linear).\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween (-1 for infinite, default 1).\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n\x09 * @param tweenTag           Optional tag to identify the created tween (default empty).\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete (default false).\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation (default false).\n\x09 * @return                   Pointer to the created UQuickColorTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Color | Material" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a color tween that animates a material color parameter by a relative amount.\n\nThe material parameter's starting value is sampled on the first update and the tween will interpolate\nfrom that start value to (start + by) over `duration` seconds. Note: the `by` parameter is provided\nas a float and should be interpreted according to how the material parameter consumes the value\n(e.g., intensity or a scalar channel modifier).\n\n@param worldContextObject Context object used to find the world for the tween.\n@param material           The UMaterialInstanceDynamic containing the color parameter.\n@param parameterName      The name of the color parameter to animate.\n@param by                 Relative FColor value to add to the sampled start value.\n@param duration           Time in seconds for the tween to complete (default 1.0f).\n@param timeScale          Multiplier applied to the tween time (default 1.0f).\n@param easeType           Predefined easing function to use for interpolation (default EEaseType::Linear).\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween (-1 for infinite, default 1).\n@param loopType           How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n@param tweenTag           Optional tag to identify the created tween (default empty).\n@param bShouldAutoKill    If true the tween will be automatically killed when complete (default false).\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation (default false).\n@return                   Pointer to the created UQuickColorTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenColorParameterBy_Material constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenColorParameterBy_Material constinit property declarations *****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenColorParameterBy_Material Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, by), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenColorParameterBy_Material Property Definitions ****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenColorParameterBy_Material", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::QuickTweenLibrary_eventQuickTweenColorParameterBy_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenColorParameterBy_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenColorParameterBy_Material(Z_Param_worldContextObject,Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenColorParameterBy_Material ************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenColorParameterTo_Material **********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics
{
	struct QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a color tween that animates a vector/color parameter on a dynamic material instance to an absolute color.\n\x09 *\n\x09 * The material parameter's starting color is sampled on the first update and the tween will interpolate\n\x09 * from that start value to the provided `to` FColor over `duration` seconds. Easing may be controlled\n\x09 * using a predefined `EEaseType` or an optional `UCurveFloat` (`easeCurve` overrides `easeType` when provided).\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param material           The UMaterialInstanceDynamic containing the color parameter.\n\x09 * @param parameterName      The name of the color parameter to animate.\n\x09 * @param to                  Target FColor value for the material parameter.\n\x09 * @param duration           Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param timeScale          Multiplier applied to the tween time (default 1.0f).\n\x09 * @param easeType           Predefined easing function to use for interpolation (default EEaseType::Linear).\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween (-1 for infinite, default 1).\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n\x09 * @param tweenTag           Optional tag to identify the created tween (default empty).\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete (default false).\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation (default false).\n\x09 * @return                   Pointer to the created UQuickColorTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Color | Material" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a color tween that animates a vector/color parameter on a dynamic material instance to an absolute color.\n\nThe material parameter's starting color is sampled on the first update and the tween will interpolate\nfrom that start value to the provided `to` FColor over `duration` seconds. Easing may be controlled\nusing a predefined `EEaseType` or an optional `UCurveFloat` (`easeCurve` overrides `easeType` when provided).\n\n@param worldContextObject Context object used to find the world for the tween.\n@param material           The UMaterialInstanceDynamic containing the color parameter.\n@param parameterName      The name of the color parameter to animate.\n@param to                  Target FColor value for the material parameter.\n@param duration           Time in seconds for the tween to complete (default 1.0f).\n@param timeScale          Multiplier applied to the tween time (default 1.0f).\n@param easeType           Predefined easing function to use for interpolation (default EEaseType::Linear).\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween (-1 for infinite, default 1).\n@param loopType           How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n@param tweenTag           Optional tag to identify the created tween (default empty).\n@param bShouldAutoKill    If true the tween will be automatically killed when complete (default false).\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation (default false).\n@return                   Pointer to the created UQuickColorTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenColorParameterTo_Material constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenColorParameterTo_Material constinit property declarations *****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenColorParameterTo_Material Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, to), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenColorParameterTo_Material Property Definitions ****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenColorParameterTo_Material", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::QuickTweenLibrary_eventQuickTweenColorParameterTo_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenColorParameterTo_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenColorParameterTo_Material(Z_Param_worldContextObject,Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenColorParameterTo_Material ************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCompleteAllTweens ******************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCompleteAllTweens_Parms
	{
		const UObject* worldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Complete all active QuickTweens within the specified world context.\n\x09 *\n\x09 * This function locates the tween manager for the provided \\p worldContextObject\n\x09 * and immediately completes all active tweens, setting them to their end state.\n\x09 * Completed tweens may be auto-killed based on their configuration.\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 */" },
		{ "Keywords", "Tween | Complete | All" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Complete all active QuickTweens within the specified world context.\n\nThis function locates the tween manager for the provided \\p worldContextObject\nand immediately completes all active tweens, setting them to their end state.\nCompleted tweens may be auto-killed based on their configuration.\n\n@param worldContextObject Context object used to locate the world that contains the tweens." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCompleteAllTweens constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenCompleteAllTweens constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCompleteAllTweens Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCompleteAllTweens_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::NewProp_worldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCompleteAllTweens Property Definitions ************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCompleteAllTweens", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::QuickTweenLibrary_eventQuickTweenCompleteAllTweens_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::QuickTweenLibrary_eventQuickTweenCompleteAllTweens_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCompleteAllTweens)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UQuickTweenLibrary::QuickTweenCompleteAllTweens(Z_Param_worldContextObject);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCompleteAllTweens ********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateSequence *********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateSequence_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a new Quick Tween sequence.\n\x09 *\n\x09 * @param worldContextObject  Context object used to find the world for the sequence.\n\x09 * @param loops               Number of times to loop the sequence. Use -1 for infinite.\n\x09 * @param loopType            How the sequence loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag            Optional tag to identify the created sequence.\n\x09 * @param bShouldAutoKill     If true the sequence will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the sequence will update while game is paused.\n\x09 * @return                    A newly created UQuickTweenSequence pointer.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_loops", "1" },
		{ "CPP_Default_loopType", "Restart" },
		{ "CPP_Default_tweenTag", "" },
		{ "Keywords", "Tween | Sequence | Create | Make" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a new Quick Tween sequence.\n\n@param worldContextObject  Context object used to find the world for the sequence.\n@param loops               Number of times to loop the sequence. Use -1 for infinite.\n@param loopType            How the sequence loops (Restart, PingPong, etc.).\n@param tweenTag            Optional tag to identify the created sequence.\n@param bShouldAutoKill     If true the sequence will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the sequence will update while game is paused.\n@return                    A newly created UQuickTweenSequence pointer." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateSequence constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateSequence constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateSequence Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateSequence_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateSequence_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateSequence_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateSequence_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateSequence_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateSequence_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateSequence_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateSequence_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateSequence_Parms, ReturnValue), Z_Construct_UClass_UQuickTweenSequence_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateSequence Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateSequence", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::QuickTweenLibrary_eventQuickTweenCreateSequence_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::QuickTweenLibrary_eventQuickTweenCreateSequence_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateSequence)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_PROPERTY(FIntProperty,Z_Param_loops);
	P_GET_ENUM(ELoopType,Z_Param_loopType);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickTweenSequence**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateSequence(Z_Param_worldContextObject,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateSequence ***********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateTweenColor *******************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a Color tween that interpolates between two FColor values and applies the\n\x09 * interpolated value via the provided setter delegate each tick.\n\x09 *\n\x09 * Easing can be controlled with a predefined EEaseType or by supplying a UCurveFloat.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param from               Starting FColor value.\n\x09 * @param to                 Target FColor value.\n\x09 * @param setter     Delegate invoked each update with the current interpolated FColor.\n\x09 * @param duration           Time in seconds for the tween to complete.\n\x09 * @param timeScale          Multiplier applied to the tween time.\n\x09 * @param easeType           Predefined easing function to use for interpolation.\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag           Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n\x09 * @return                   Pointer to the created UQuickColorTween.\n\x09 */" },
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
		{ "Keywords", "Tween | Color" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a Color tween that interpolates between two FColor values and applies the\ninterpolated value via the provided setter delegate each tick.\n\nEasing can be controlled with a predefined EEaseType or by supplying a UCurveFloat.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param from               Starting FColor value.\n@param to                 Target FColor value.\n@param setter     Delegate invoked each update with the current interpolated FColor.\n@param duration           Time in seconds for the tween to complete.\n@param timeScale          Multiplier applied to the tween time.\n@param easeType           Predefined easing function to use for interpolation.\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween. Use -1 for infinite.\n@param loopType           How the tween loops (Restart, PingPong, etc.).\n@param tweenTag           Optional tag to identify the created tween.\n@param bShouldAutoKill    If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n@return                   Pointer to the created UQuickColorTween." },
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

// ********** Begin Function QuickTweenCreateTweenColor constinit property declarations ************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateTweenColor constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateTweenColor Property Definitions ***********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, from), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, to), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_ColorSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 4149733706
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms, ReturnValue), Z_Construct_UClass_UQuickColorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateTweenColor Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateTweenColor", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenColor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateTweenColor)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickColorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateTweenColor(Z_Param_worldContextObject,Z_Param_Out_from,Z_Param_Out_to,FColorSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateTweenColor *********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateTweenEmpty *******************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create an empty tween that acts as a timed marker or delay without modifying values.\n\x09 *\n\x09 * The empty tween runs for \\p duration seconds and can be tagged and configured to\n\x09 * auto-kill, play while the game is paused, or auto-play on creation. Useful for\n\x09 * creating delays, sequencing, or timed callbacks in Blueprints and C++.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param duration           Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param tweenTag           Optional tag to identify the created tween (default empty).\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n\x09 * @return                   Pointer to the created UQuickEmptyTween, or nullptr on failure.\n\x09 */" },
		{ "CPP_Default_bShouldAutoKill", "true" },
		{ "CPP_Default_bShouldAutoPlay", "false" },
		{ "CPP_Default_bShouldPlayWhilePaused", "false" },
		{ "CPP_Default_duration", "1.000000" },
		{ "CPP_Default_tweenTag", "" },
		{ "Keywords", "Tween | Empty" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create an empty tween that acts as a timed marker or delay without modifying values.\n\nThe empty tween runs for \\p duration seconds and can be tagged and configured to\nauto-kill, play while the game is paused, or auto-play on creation. Useful for\ncreating delays, sequencing, or timed callbacks in Blueprints and C++.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param duration           Time in seconds for the tween to complete (default 1.0f).\n@param tweenTag           Optional tag to identify the created tween (default empty).\n@param bShouldAutoKill    If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n@return                   Pointer to the created UQuickEmptyTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateTweenEmpty constinit property declarations ************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateTweenEmpty constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateTweenEmpty Property Definitions ***********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms, ReturnValue), Z_Construct_UClass_UQuickEmptyTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateTweenEmpty Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateTweenEmpty", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenEmpty_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateTweenEmpty)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_PROPERTY(FFloatProperty,Z_Param_duration);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_GET_UBOOL(Z_Param_bShouldAutoKill);
	P_GET_UBOOL(Z_Param_bShouldPlayWhilePaused);
	P_GET_UBOOL(Z_Param_bShouldAutoPlay);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickEmptyTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateTweenEmpty(Z_Param_worldContextObject,Z_Param_duration,Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateTweenEmpty *********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateTweenFloat *******************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that interpolates a value from `from` to `to` and applies it via `setter`.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param from Delegate that returns the starting float value.\n\x09 * @param to Delegate that returns the target float value.\n\x09 * @param setter Delegate invoked each update with the current interpolated float value.\n\x09 * @param duration Time in seconds for the tween to complete.\n\x09 * @param timeScale Multiplier applied to the tween time.\n\x09 * @param easeType Predefined easing function to use for interpolation.\n\x09 * @param easeCurve Optional custom `UCurveFloat` used for easing (overrides `easeType` when provided).\n\x09 * @param loops Number of times to loop the tween. Use -1 for infinite loops.\n\x09 * @param loopType How the tween loops (e.g., Restart, PingPong).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true, the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true, the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true, the tween will start playing immediately after creation.\n\x09 * @return A pointer to the created `UQuickFloatTween`.\n\x09 */" },
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
		{ "Keywords", "Tween | Float" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that interpolates a value from `from` to `to` and applies it via `setter`.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param from Delegate that returns the starting float value.\n@param to Delegate that returns the target float value.\n@param setter Delegate invoked each update with the current interpolated float value.\n@param duration Time in seconds for the tween to complete.\n@param timeScale Multiplier applied to the tween time.\n@param easeType Predefined easing function to use for interpolation.\n@param easeCurve Optional custom `UCurveFloat` used for easing (overrides `easeType` when provided).\n@param loops Number of times to loop the tween. Use -1 for infinite loops.\n@param loopType How the tween loops (e.g., Restart, PingPong).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true, the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true, the tween will update while the game is paused.\n@param bShouldAutoPlay If true, the tween will start playing immediately after creation.\n@return A pointer to the created `UQuickFloatTween`." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateTweenFloat constinit property declarations ************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateTweenFloat constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateTweenFloat Property Definitions ***********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, from), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_FloatSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 2499567968
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateTweenFloat Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateTweenFloat", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenFloat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateTweenFloat)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateTweenFloat(Z_Param_worldContextObject,Z_Param_from,Z_Param_to,FFloatSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateTweenFloat *********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateTweenInt *********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create an Int tween that interpolates between two integer values and applies the\n\x09 * interpolated value via the provided setter delegate each tick.\n\x09 *\n\x09 * The tween uses floating point easing internally but outputs integer values to the setter.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param from               Starting integer value.\n\x09 * @param to                 Target integer value.\n\x09 * @param setter     Delegate invoked each update with the current interpolated integer.\n\x09 * @param duration           Time in seconds for the tween to complete.\n\x09 * @param timeScale          Multiplier applied to the tween time.\n\x09 * @param easeType           Predefined easing function to use for interpolation.\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag           Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n\x09 * @return                   Pointer to the created UQuickIntTween.\n\x09 */" },
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
		{ "Keywords", "Tween | Int" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create an Int tween that interpolates between two integer values and applies the\ninterpolated value via the provided setter delegate each tick.\n\nThe tween uses floating point easing internally but outputs integer values to the setter.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param from               Starting integer value.\n@param to                 Target integer value.\n@param setter     Delegate invoked each update with the current interpolated integer.\n@param duration           Time in seconds for the tween to complete.\n@param timeScale          Multiplier applied to the tween time.\n@param easeType           Predefined easing function to use for interpolation.\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween. Use -1 for infinite.\n@param loopType           How the tween loops (Restart, PingPong, etc.).\n@param tweenTag           Optional tag to identify the created tween.\n@param bShouldAutoKill    If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n@return                   Pointer to the created UQuickIntTween." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenCreateTweenInt constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateTweenInt constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateTweenInt Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, from), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_IntSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 2363718048
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms, ReturnValue), Z_Construct_UClass_UQuickIntTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateTweenInt Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateTweenInt", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenInt_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateTweenInt)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickIntTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateTweenInt(Z_Param_worldContextObject,Z_Param_from,Z_Param_to,FIntSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateTweenInt ***********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateTweenRotator *****************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a rotator tween that interpolates between two rotator values using delegates.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param from Delegate that returns the starting rotation.\n\x09 * @param to Delegate that returns the target rotation.\n\x09 * @param setter Delegate invoked each update with the current interpolated rotator.\n\x09 * @param bUseShortestPath If true, rotation will take the shortest angular path.\n\x09 * @param duration Time in seconds for the tween to complete.\n\x09 * @param timeScale Multiplier applied to the tween time.\n\x09 * @param easeType Predefined easing function to use for interpolation.\n\x09 * @param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops Number of times to loop the tween. Use -1 for infinite loops.\n\x09 * @param loopType How the tween loops (e.g., Restart, PingPong).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true, the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true, the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true, the tween will start playing immediately after creation.\n\x09 * @return A pointer to the created UQuickRotatorTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Rotator" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a rotator tween that interpolates between two rotator values using delegates.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param from Delegate that returns the starting rotation.\n@param to Delegate that returns the target rotation.\n@param setter Delegate invoked each update with the current interpolated rotator.\n@param bUseShortestPath If true, rotation will take the shortest angular path.\n@param duration Time in seconds for the tween to complete.\n@param timeScale Multiplier applied to the tween time.\n@param easeType Predefined easing function to use for interpolation.\n@param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops Number of times to loop the tween. Use -1 for infinite loops.\n@param loopType How the tween loops (e.g., Restart, PingPong).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true, the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true, the tween will update while the game is paused.\n@param bShouldAutoPlay If true, the tween will start playing immediately after creation.\n@return A pointer to the created UQuickRotatorTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenCreateTweenRotator constinit property declarations **********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateTweenRotator constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateTweenRotator Property Definitions *********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, from), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, to), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_RotatorSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 2384351140
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateTweenRotator Property Definitions ***********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateTweenRotator", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenRotator_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateTweenRotator)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateTweenRotator(Z_Param_worldContextObject,Z_Param_Out_from,Z_Param_Out_to,FRotatorSetter(Z_Param_setter),Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateTweenRotator *******************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateTweenVector ******************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a vector tween that interpolates between two FVector values using delegate getters\n\x09 * and applies the interpolated value via a setter delegate each tick.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param from Delegate that returns the starting FVector value.\n\x09 * @param to Delegate that returns the target FVector value.\n\x09 * @param setter Delegate invoked each update with the current interpolated FVector.\n\x09 * @param duration Time in seconds for the tween to complete. Defaults to 1.0f.\n\x09 * @param timeScale Multiplier applied to the tween time. Defaults to 1.0f.\n\x09 * @param easeType Predefined easing function to use for interpolation. Defaults to EEaseType::Linear.\n\x09 * @param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops Number of times to loop the tween. Use -1 for infinite. Defaults to 1.\n\x09 * @param loopType How the tween loops (Restart, PingPong, etc.). Defaults to ELoopType::Restart.\n\x09 * @param tweenTag Optional tag to identify the created tween. Defaults to empty string.\n\x09 * @param bShouldAutoKill If true the tween will be automatically killed when complete. Defaults to true.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while game is paused. Defaults to false.\n\x09 * @param bShouldAutoPlay If true the tween will start playing immediately after creation. Defaults to false.\n\x09 * @return A pointer to the created UQuickVectorTween.\n\x09 */" },
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
		{ "Keywords", "Tween | Vector" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a vector tween that interpolates between two FVector values using delegate getters\nand applies the interpolated value via a setter delegate each tick.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param from Delegate that returns the starting FVector value.\n@param to Delegate that returns the target FVector value.\n@param setter Delegate invoked each update with the current interpolated FVector.\n@param duration Time in seconds for the tween to complete. Defaults to 1.0f.\n@param timeScale Multiplier applied to the tween time. Defaults to 1.0f.\n@param easeType Predefined easing function to use for interpolation. Defaults to EEaseType::Linear.\n@param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops Number of times to loop the tween. Use -1 for infinite. Defaults to 1.\n@param loopType How the tween loops (Restart, PingPong, etc.). Defaults to ELoopType::Restart.\n@param tweenTag Optional tag to identify the created tween. Defaults to empty string.\n@param bShouldAutoKill If true the tween will be automatically killed when complete. Defaults to true.\n@param bShouldPlayWhilePaused If true the tween will update while game is paused. Defaults to false.\n@param bShouldAutoPlay If true the tween will start playing immediately after creation. Defaults to false.\n@return A pointer to the created UQuickVectorTween." },
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

// ********** Begin Function QuickTweenCreateTweenVector constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateTweenVector constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateTweenVector Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, from), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_VectorSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3599544734
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateTweenVector Property Definitions ************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateTweenVector", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenVector_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateTweenVector)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateTweenVector(Z_Param_worldContextObject,Z_Param_Out_from,Z_Param_Out_to,FVectorSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateTweenVector ********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenCreateTweenVector2D ****************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics
{
	struct QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a Vector2D tween that interpolates between two FVector2D values and applies the\n\x09 * interpolated value via the provided setter delegate each tick.\n\x09 *\n\x09 * The tween will evaluate easing using either a predefined EEaseType or an optional\n\x09 * UCurveFloat. The start and target values are provided directly as parameters.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param from               Starting FVector2D value.\n\x09 * @param to                 Target FVector2D value.\n\x09 * @param setter     Delegate invoked each update with the current interpolated FVector2D.\n\x09 * @param duration           Time in seconds for the tween to complete.\n\x09 * @param timeScale          Multiplier applied to the tween time.\n\x09 * @param easeType           Predefined easing function to use for interpolation.\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag           Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n\x09 * @return                   Pointer to the created UQuickVector2DTween.\n\x09 */" },
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
		{ "Keywords", "Tween | Vector" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a Vector2D tween that interpolates between two FVector2D values and applies the\ninterpolated value via the provided setter delegate each tick.\n\nThe tween will evaluate easing using either a predefined EEaseType or an optional\nUCurveFloat. The start and target values are provided directly as parameters.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param from               Starting FVector2D value.\n@param to                 Target FVector2D value.\n@param setter     Delegate invoked each update with the current interpolated FVector2D.\n@param duration           Time in seconds for the tween to complete.\n@param timeScale          Multiplier applied to the tween time.\n@param easeType           Predefined easing function to use for interpolation.\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween. Use -1 for infinite.\n@param loopType           How the tween loops (Restart, PingPong, etc.).\n@param tweenTag           Optional tag to identify the created tween.\n@param bShouldAutoKill    If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n@return                   Pointer to the created UQuickVector2DTween." },
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

// ********** Begin Function QuickTweenCreateTweenVector2D constinit property declarations *********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenCreateTweenVector2D constinit property declarations ***********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenCreateTweenVector2D Property Definitions ********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, from), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_from_MetaData), NewProp_from_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, to), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_setter = { "setter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, setter), Z_Construct_UDelegateFunction_QuickTween_Vector2DSetter__DelegateSignature, METADATA_PARAMS(0, nullptr) }; // 3010275275
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_setter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenCreateTweenVector2D Property Definitions **********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenCreateTweenVector2D", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::QuickTweenLibrary_eventQuickTweenCreateTweenVector2D_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenCreateTweenVector2D)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenCreateTweenVector2D(Z_Param_worldContextObject,Z_Param_Out_from,Z_Param_Out_to,FVector2DSetter(Z_Param_setter),Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenCreateTweenVector2D ******************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenExecuteActionByPredicate ***********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics
{
	struct QuickTweenLibrary_eventQuickTweenExecuteActionByPredicate_Parms
	{
		const UObject* worldContextObject;
		FScriptDelegate predicate;
		FScriptDelegate action;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Execute a specified action on all active QuickTweens that match a given predicate within the world context.\n\x09 *\n\x09 * This function searches through all active tweens managed by the tween manager\n\x09 * associated with the provided \\p worldContextObject. For each tween that satisfies\n\x09 * the given \\p predicate, the specified \\p action is executed.\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 * @param predicate          The predicate function used to filter tweens.\n\x09 * @param action             The action to execute on matching tweens.\n\x09 */" },
		{ "Keywords", "Tween | Some" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Execute a specified action on all active QuickTweens that match a given predicate within the world context.\n\nThis function searches through all active tweens managed by the tween manager\nassociated with the provided \\p worldContextObject. For each tween that satisfies\nthe given \\p predicate, the specified \\p action is executed.\n\n@param worldContextObject Context object used to locate the world that contains the tweens.\n@param predicate          The predicate function used to filter tweens.\n@param action             The action to execute on matching tweens." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_predicate_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_action_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenExecuteActionByPredicate constinit property declarations ****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_predicate;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_action;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenExecuteActionByPredicate constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenExecuteActionByPredicate Property Definitions ***************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenExecuteActionByPredicate_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::NewProp_predicate = { "predicate", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenExecuteActionByPredicate_Parms, predicate), Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_predicate_MetaData), NewProp_predicate_MetaData) }; // 594604995
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::NewProp_action = { "action", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenExecuteActionByPredicate_Parms, action), Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_action_MetaData), NewProp_action_MetaData) }; // 1273358790
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::NewProp_predicate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::NewProp_action,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenExecuteActionByPredicate Property Definitions *****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenExecuteActionByPredicate", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::QuickTweenLibrary_eventQuickTweenExecuteActionByPredicate_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::QuickTweenLibrary_eventQuickTweenExecuteActionByPredicate_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenExecuteActionByPredicate)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_predicate);
	P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_action);
	P_FINISH;
	P_NATIVE_BEGIN;
	UQuickTweenLibrary::QuickTweenExecuteActionByPredicate(Z_Param_worldContextObject,FQuickConstTweenableAction(Z_Param_Out_predicate),FQuickTweenableAction(Z_Param_Out_action));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenExecuteActionByPredicate *************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenExecuteActionOnAllTweens ***********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics
{
	struct QuickTweenLibrary_eventQuickTweenExecuteActionOnAllTweens_Parms
	{
		const UObject* worldContextObject;
		FScriptDelegate action;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Execute a specified action on all active QuickTweens within the given world context.\n\x09 *\n\x09 * This function locates the tween manager for the provided \\p worldContextObject\n\x09 * and performs the specified \\p action on all active tweens. The action is defined\n\x09 * by the FQuickTweenableAction enum (e.g., Pause, Play, Reverse, etc.).\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 * @param action             The action to execute on all active tweens.\n\x09 */" },
		{ "Keywords", "Tween | All" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Execute a specified action on all active QuickTweens within the given world context.\n\nThis function locates the tween manager for the provided \\p worldContextObject\nand performs the specified \\p action on all active tweens. The action is defined\nby the FQuickTweenableAction enum (e.g., Pause, Play, Reverse, etc.).\n\n@param worldContextObject Context object used to locate the world that contains the tweens.\n@param action             The action to execute on all active tweens." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_action_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenExecuteActionOnAllTweens constinit property declarations ****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_action;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenExecuteActionOnAllTweens constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenExecuteActionOnAllTweens Property Definitions ***************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenExecuteActionOnAllTweens_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::NewProp_action = { "action", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenExecuteActionOnAllTweens_Parms, action), Z_Construct_UDelegateFunction_QuickTween_QuickTweenableAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_action_MetaData), NewProp_action_MetaData) }; // 1273358790
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::NewProp_action,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenExecuteActionOnAllTweens Property Definitions *****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenExecuteActionOnAllTweens", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::QuickTweenLibrary_eventQuickTweenExecuteActionOnAllTweens_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::QuickTweenLibrary_eventQuickTweenExecuteActionOnAllTweens_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenExecuteActionOnAllTweens)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_action);
	P_FINISH;
	P_NATIVE_BEGIN;
	UQuickTweenLibrary::QuickTweenExecuteActionOnAllTweens(Z_Param_worldContextObject,FQuickTweenableAction(Z_Param_Out_action));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenExecuteActionOnAllTweens *************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenFindAllTweensByPredicate ***********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics
{
	struct QuickTweenLibrary_eventQuickTweenFindAllTweensByPredicate_Parms
	{
		const UObject* worldContextObject;
		FScriptDelegate predicate;
		TArray<UQuickTweenable*> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Find all active QuickTweens that match a specified predicate within the world context.\n\x09 *\n\x09 * This function searches through all active tweens managed by the tween manager\n\x09 * associated with the provided \\p worldContextObject and returns an array of\n\x09 * UQuickTweenable instances that satisfy the given \\p predicate.\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 * @param predicate          The predicate function used to filter tweens.\n\x09 * @return                   An array of UQuickTweenable pointers that match the predicate.\n\x09 */" },
		{ "Keywords", "Tween | Find | All" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Find all active QuickTweens that match a specified predicate within the world context.\n\nThis function searches through all active tweens managed by the tween manager\nassociated with the provided \\p worldContextObject and returns an array of\nUQuickTweenable instances that satisfy the given \\p predicate.\n\n@param worldContextObject Context object used to locate the world that contains the tweens.\n@param predicate          The predicate function used to filter tweens.\n@return                   An array of UQuickTweenable pointers that match the predicate." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_predicate_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenFindAllTweensByPredicate constinit property declarations ****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FDelegatePropertyParams NewProp_predicate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenFindAllTweensByPredicate constinit property declarations ******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenFindAllTweensByPredicate Property Definitions ***************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenFindAllTweensByPredicate_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_predicate = { "predicate", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenFindAllTweensByPredicate_Parms, predicate), Z_Construct_UDelegateFunction_QuickTween_QuickConstTweenableAction__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_predicate_MetaData), NewProp_predicate_MetaData) }; // 594604995
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenFindAllTweensByPredicate_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_predicate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenFindAllTweensByPredicate Property Definitions *****************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenFindAllTweensByPredicate", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::QuickTweenLibrary_eventQuickTweenFindAllTweensByPredicate_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::QuickTweenLibrary_eventQuickTweenFindAllTweensByPredicate_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenFindAllTweensByPredicate)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_PROPERTY_REF(FDelegateProperty,Z_Param_Out_predicate);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<UQuickTweenable*>*)Z_Param__Result=UQuickTweenLibrary::QuickTweenFindAllTweensByPredicate(Z_Param_worldContextObject,FQuickConstTweenableAction(Z_Param_Out_predicate));
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenFindAllTweensByPredicate *************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenFindTweenByTag *********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics
{
	struct QuickTweenLibrary_eventQuickTweenFindTweenByTag_Parms
	{
		const UObject* worldContextObject;
		FString tweenTag;
		UQuickTweenable* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Find an active QuickTween by its tag within the world context.\n\x09 *\n\x09 * @param worldContextObject  Context object used to locate the world that contains the tween.\n\x09 * @param tweenTag            Tag identifying the tween to find.\n\x09 * @return                    Pointer to the found UQuickTweenable instance, or nullptr if none found.\n\x09 */" },
		{ "Keywords", "Tween | Find | By Tag" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Find an active QuickTween by its tag within the world context.\n\n@param worldContextObject  Context object used to locate the world that contains the tween.\n@param tweenTag            Tag identifying the tween to find.\n@return                    Pointer to the found UQuickTweenable instance, or nullptr if none found." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenFindTweenByTag constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FStrPropertyParams NewProp_tweenTag;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenFindTweenByTag constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenFindTweenByTag Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenFindTweenByTag_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenFindTweenByTag_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenFindTweenByTag_Parms, ReturnValue), Z_Construct_UClass_UQuickTweenable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenFindTweenByTag Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenFindTweenByTag", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::QuickTweenLibrary_eventQuickTweenFindTweenByTag_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::QuickTweenLibrary_eventQuickTweenFindTweenByTag_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenFindTweenByTag)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_GET_PROPERTY(FStrProperty,Z_Param_tweenTag);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UQuickTweenable**)Z_Param__Result=UQuickTweenLibrary::QuickTweenFindTweenByTag(Z_Param_worldContextObject,Z_Param_tweenTag);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenFindTweenByTag ***********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenKillAllTweens **********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics
{
	struct QuickTweenLibrary_eventQuickTweenKillAllTweens_Parms
	{
		const UObject* worldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Kill all active QuickTweens within the specified world context.\n\x09 *\n\x09 * This function locates the tween manager for the provided \\p worldContextObject\n\x09 * and immediately kills/removes all active tweens. Use this to forcefully stop\n\x09 * any running tweens (useful for cleanup, level transitions, or global reset).\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 */" },
		{ "Keywords", "Tween | Kill | All" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Kill all active QuickTweens within the specified world context.\n\nThis function locates the tween manager for the provided \\p worldContextObject\nand immediately kills/removes all active tweens. Use this to forcefully stop\nany running tweens (useful for cleanup, level transitions, or global reset).\n\n@param worldContextObject Context object used to locate the world that contains the tweens." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenKillAllTweens constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenKillAllTweens constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenKillAllTweens Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenKillAllTweens_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::NewProp_worldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenKillAllTweens Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenKillAllTweens", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::QuickTweenLibrary_eventQuickTweenKillAllTweens_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::QuickTweenLibrary_eventQuickTweenKillAllTweens_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenKillAllTweens)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UQuickTweenLibrary::QuickTweenKillAllTweens(Z_Param_worldContextObject);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenKillAllTweens ************************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenLookAt_SceneComponent **************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a rotator tween that orients a SceneComponent to look at a target point.\n\x09 *\n\x09 * Note: The start and end value will be cached from the component's current location at the first update.\n\x09 *\n\x09 * @param worldContextObject  Context object used to find the world for the tween.\n\x09 * @param component           The SceneComponent to rotate.\n\x09 * @param to                  Target world-space location to look at.\n\x09 * @param bUseShortestPath    If true rotation will take the shortest angular path.\n\x09 * @param duration            Time in seconds for the tween to complete.\n\x09 * @param timeScale           Multiplier applied to the tween time.\n\x09 * @param easeType            Predefined easing type to use.\n\x09 * @param easeCurve           Optional custom curve to evaluate easing.\n\x09 * @param loops               Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType            How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag            Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill     If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while game is paused.\n\x09 * @param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n\x09 * @return                    A UQuickRotatorTween pointer controlling the look-at rotation.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a rotator tween that orients a SceneComponent to look at a target point.\n\nNote: The start and end value will be cached from the component's current location at the first update.\n\n@param worldContextObject  Context object used to find the world for the tween.\n@param component           The SceneComponent to rotate.\n@param to                  Target world-space location to look at.\n@param bUseShortestPath    If true rotation will take the shortest angular path.\n@param duration            Time in seconds for the tween to complete.\n@param timeScale           Multiplier applied to the tween time.\n@param easeType            Predefined easing type to use.\n@param easeCurve           Optional custom curve to evaluate easing.\n@param loops               Number of times to loop the tween. Use -1 for infinite.\n@param loopType            How the tween loops (Restart, PingPong, etc.).\n@param tweenTag            Optional tag to identify the created tween.\n@param bShouldAutoKill     If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while game is paused.\n@param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n@return                    A UQuickRotatorTween pointer controlling the look-at rotation." },
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

// ********** Begin Function QuickTweenLookAt_SceneComponent constinit property declarations *******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenLookAt_SceneComponent constinit property declarations *********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenLookAt_SceneComponent Property Definitions ******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenLookAt_SceneComponent Property Definitions ********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenLookAt_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenLookAt_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenLookAt_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenLookAt_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_Out_to,Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenLookAt_SceneComponent ****************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenMoveBy_SceneComponent **************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a vector tween that moves a SceneComponent by a relative offset.\n\x09 *\n\x09 * This function generates a UQuickVectorTween which will drive the component's world\n\x09 * or local position from its current value (cached at the first update) by adding the\n\x09 * provided `by` vector to the start position. The interpolated value is applied each\n\x09 * tick via the tween's setter. Easing can be controlled with either a predefined\n\x09 * EEaseType or an optional UCurveFloat. The operation can be performed in local or\n\x09 * world space according to `space`.\n\x09 *\n\x09 * @param worldContextObject  Context object used to find the world for the tween.\n\x09 * @param component           The SceneComponent to move.\n\x09 * @param by                  Relative world/local offset to apply (added to the start location).\n\x09 * @param duration            Time in seconds for the tween to complete.\n\x09 * @param timeScale           Multiplier applied to the tween time.\n\x09 * @param easeType            Predefined easing type to use for interpolation.\n\x09 * @param easeCurve           Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops               Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType            How the tween loops (Restart, PingPong, etc.).\n\x09 * @param space               Space in which to apply the movement (World or Local).\n\x09 * @param tweenTag            Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill     If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n\x09 * @return                    A UQuickVectorTween pointer controlling the movement.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a vector tween that moves a SceneComponent by a relative offset.\n\nThis function generates a UQuickVectorTween which will drive the component's world\nor local position from its current value (cached at the first update) by adding the\nprovided `by` vector to the start position. The interpolated value is applied each\ntick via the tween's setter. Easing can be controlled with either a predefined\nEEaseType or an optional UCurveFloat. The operation can be performed in local or\nworld space according to `space`.\n\n@param worldContextObject  Context object used to find the world for the tween.\n@param component           The SceneComponent to move.\n@param by                  Relative world/local offset to apply (added to the start location).\n@param duration            Time in seconds for the tween to complete.\n@param timeScale           Multiplier applied to the tween time.\n@param easeType            Predefined easing type to use for interpolation.\n@param easeCurve           Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops               Number of times to loop the tween. Use -1 for infinite.\n@param loopType            How the tween loops (Restart, PingPong, etc.).\n@param space               Space in which to apply the movement (World or Local).\n@param tweenTag            Optional tag to identify the created tween.\n@param bShouldAutoKill     If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n@return                    A UQuickVectorTween pointer controlling the movement." },
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

// ********** Begin Function QuickTweenMoveBy_SceneComponent constinit property declarations *******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenMoveBy_SceneComponent constinit property declarations *********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenMoveBy_SceneComponent Property Definitions ******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, by), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenMoveBy_SceneComponent Property Definitions ********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenMoveBy_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenMoveBy_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenMoveBy_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenMoveBy_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenMoveBy_SceneComponent ****************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenMoveBy_Widget **********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics
{
	struct QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a Vector2D tween that moves a UWidget by a relative offset.\n\x09 *\n\x09 * The tween samples the widget's current position/translation on its first update\n\x09 * and interpolates from that start value to (start + by) over `duration` seconds.\n\x09 * The interpolated FVector2D is applied to the widget each tick via the tween's\n\x09 * internal setter. Easing may be controlled using a predefined `EEaseType` or by\n\x09 * supplying a custom `UCurveFloat`.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param widget             The UWidget to move.\n\x09 * @param by                 Relative offset to add to the widget's start position.\n\x09 * @param duration           Time in seconds for the tween to complete.\n\x09 * @param timeScale          Multiplier applied to the tween time.\n\x09 * @param easeType           Predefined easing function to use for interpolation.\n\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops              Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType           How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag           Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n\x09 * @return                   Pointer to the created UQuickVector2DTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a Vector2D tween that moves a UWidget by a relative offset.\n\nThe tween samples the widget's current position/translation on its first update\nand interpolates from that start value to (start + by) over `duration` seconds.\nThe interpolated FVector2D is applied to the widget each tick via the tween's\ninternal setter. Easing may be controlled using a predefined `EEaseType` or by\nsupplying a custom `UCurveFloat`.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param widget             The UWidget to move.\n@param by                 Relative offset to add to the widget's start position.\n@param duration           Time in seconds for the tween to complete.\n@param timeScale          Multiplier applied to the tween time.\n@param easeType           Predefined easing function to use for interpolation.\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween. Use -1 for infinite.\n@param loopType           How the tween loops (Restart, PingPong, etc.).\n@param tweenTag           Optional tag to identify the created tween.\n@param bShouldAutoKill    If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n@return                   Pointer to the created UQuickVector2DTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenMoveBy_Widget constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenMoveBy_Widget constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenMoveBy_Widget Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, by), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenMoveBy_Widget Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenMoveBy_Widget", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::QuickTweenLibrary_eventQuickTweenMoveBy_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenMoveBy_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenMoveBy_Widget(Z_Param_worldContextObject,Z_Param_widget,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenMoveBy_Widget ************************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenMoveTo_SceneComponent **************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a vector tween that moves a SceneComponent to a target location.\n\x09 *\n\x09 * Note: The start and end value will be cached from the component's current location at the first update.\n\x09 *\n\x09 * @param worldContextObject  Context object used to find the world for the tween.\n\x09 * @param component           The SceneComponent to move.\n\x09 * @param to                  Target world-space location.\n\x09 * @param duration            Time in seconds for the tween to complete.\n\x09 * @param timeScale           Multiplier applied to the tween time.\n\x09 * @param easeType            Predefined easing type to use.\n\x09 * @param easeCurve           Optional custom curve to evaluate easing.\n\x09 * @param loops               Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType            How the tween loops (Restart, PingPong, etc.).\n\x09 * @param space          Space in which to perform the look-at operation (World or Local).\n\x09 * @param tweenTag            Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill     If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while game is paused.\n\x09 * @param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n\x09 * @return                    A UQuickVectorTween pointer controlling the movement.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a vector tween that moves a SceneComponent to a target location.\n\nNote: The start and end value will be cached from the component's current location at the first update.\n\n@param worldContextObject  Context object used to find the world for the tween.\n@param component           The SceneComponent to move.\n@param to                  Target world-space location.\n@param duration            Time in seconds for the tween to complete.\n@param timeScale           Multiplier applied to the tween time.\n@param easeType            Predefined easing type to use.\n@param easeCurve           Optional custom curve to evaluate easing.\n@param loops               Number of times to loop the tween. Use -1 for infinite.\n@param loopType            How the tween loops (Restart, PingPong, etc.).\n@param space          Space in which to perform the look-at operation (World or Local).\n@param tweenTag            Optional tag to identify the created tween.\n@param bShouldAutoKill     If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while game is paused.\n@param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n@return                    A UQuickVectorTween pointer controlling the movement." },
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

// ********** Begin Function QuickTweenMoveTo_SceneComponent constinit property declarations *******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenMoveTo_SceneComponent constinit property declarations *********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenMoveTo_SceneComponent Property Definitions ******************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenMoveTo_SceneComponent Property Definitions ********************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenMoveTo_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenMoveTo_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenMoveTo_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenMoveTo_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenMoveTo_SceneComponent ****************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenMoveTo_Widget **********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics
{
	struct QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a Vector2D tween that moves a UWidget to a target absolute position.\n\x09 *\n\x09 * The widget's start position is sampled on the first update and the tween interpolates\n\x09 * from that start position to the specified `to` value over `duration` seconds.\n\x09 * Easing is controlled via `easeType` or an optional `easeCurve`. The returned tween\n\x09 * will apply interpolated FVector2D values to the widget each tick.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param widget The UWidget to move.\n\x09 * @param to Target position as an FVector2D.\n\x09 * @param duration Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param timeScale Multiplier applied to the tween time (default 1.0f).\n\x09 * @param easeType Predefined easing function to use (default EEaseType::Linear).\n\x09 * @param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops Number of times to loop the tween (-1 for infinite, default 1).\n\x09 * @param loopType How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n\x09 * @param tweenTag Optional tag to identify the created tween (default empty).\n\x09 * @param bShouldAutoKill If true the tween will be automatically killed when complete (default false).\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n\x09 * @param bShouldAutoPlay If true the tween will start playing immediately after creation (default false).\n\x09 * @return Pointer to the created UQuickVector2DTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a Vector2D tween that moves a UWidget to a target absolute position.\n\nThe widget's start position is sampled on the first update and the tween interpolates\nfrom that start position to the specified `to` value over `duration` seconds.\nEasing is controlled via `easeType` or an optional `easeCurve`. The returned tween\nwill apply interpolated FVector2D values to the widget each tick.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param widget The UWidget to move.\n@param to Target position as an FVector2D.\n@param duration Time in seconds for the tween to complete (default 1.0f).\n@param timeScale Multiplier applied to the tween time (default 1.0f).\n@param easeType Predefined easing function to use (default EEaseType::Linear).\n@param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops Number of times to loop the tween (-1 for infinite, default 1).\n@param loopType How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n@param tweenTag Optional tag to identify the created tween (default empty).\n@param bShouldAutoKill If true the tween will be automatically killed when complete (default false).\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n@param bShouldAutoPlay If true the tween will start playing immediately after creation (default false).\n@return Pointer to the created UQuickVector2DTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenMoveTo_Widget constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenMoveTo_Widget constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenMoveTo_Widget Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, to), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenMoveTo_Widget Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenMoveTo_Widget", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenMoveTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenMoveTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenMoveTo_Widget(Z_Param_worldContextObject,Z_Param_widget,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenMoveTo_Widget ************************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenPauseAllTweens *********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics
{
	struct QuickTweenLibrary_eventQuickTweenPauseAllTweens_Parms
	{
		const UObject* worldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Pause all active QuickTweens within the specified world context.\n\x09 *\n\x09 * This function finds the tween manager associated with \\p worldContextObject\n\x09 * and pauses all currently active tweens. Paused tweens retain their state and\n\x09 * can be resumed later. This does not kill or destroy tweens.\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 */" },
		{ "Keywords", "Tween | Pause | All" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Pause all active QuickTweens within the specified world context.\n\nThis function finds the tween manager associated with \\p worldContextObject\nand pauses all currently active tweens. Paused tweens retain their state and\ncan be resumed later. This does not kill or destroy tweens.\n\n@param worldContextObject Context object used to locate the world that contains the tweens." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenPauseAllTweens constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenPauseAllTweens constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenPauseAllTweens Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenPauseAllTweens_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::NewProp_worldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenPauseAllTweens Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenPauseAllTweens", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::QuickTweenLibrary_eventQuickTweenPauseAllTweens_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::QuickTweenLibrary_eventQuickTweenPauseAllTweens_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenPauseAllTweens)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UQuickTweenLibrary::QuickTweenPauseAllTweens(Z_Param_worldContextObject);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenPauseAllTweens ***********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenPlayAllTweens **********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics
{
	struct QuickTweenLibrary_eventQuickTweenPlayAllTweens_Parms
	{
		const UObject* worldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Play all QuickTweens within the specified world context.\n\x09 *\n\x09 * This function locates the tween manager for the provided \\p worldContextObject\n\x09 * and resumes all tweens that were previously paused. Active tweens that are not\n\x09 * paused remain unaffected.\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 */" },
		{ "Keywords", "Tween | Play | All" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Play all QuickTweens within the specified world context.\n\nThis function locates the tween manager for the provided \\p worldContextObject\nand resumes all tweens that were previously paused. Active tweens that are not\npaused remain unaffected.\n\n@param worldContextObject Context object used to locate the world that contains the tweens." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenPlayAllTweens constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenPlayAllTweens constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenPlayAllTweens Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenPlayAllTweens_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::NewProp_worldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenPlayAllTweens Property Definitions ****************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenPlayAllTweens", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::QuickTweenLibrary_eventQuickTweenPlayAllTweens_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::QuickTweenLibrary_eventQuickTweenPlayAllTweens_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenPlayAllTweens)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UQuickTweenLibrary::QuickTweenPlayAllTweens(Z_Param_worldContextObject);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenPlayAllTweens ************************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenReverseAllTweens *******************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics
{
	struct QuickTweenLibrary_eventQuickTweenReverseAllTweens_Parms
	{
		const UObject* worldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "QuickTween" },
		{ "Comment", "/**\n\x09 * Reverse all active QuickTweens within the specified world context.\n\x09 *\n\x09 * This function finds the tween manager associated with \\p worldContextObject\n\x09 * and reverses the playback direction of all currently active tweens. Tweens\n\x09 * that were playing forward will play backward, and vice versa.\n\x09 *\n\x09 * @param worldContextObject Context object used to locate the world that contains the tweens.\n\x09 */" },
		{ "Keywords", "Tween | Reverse | All" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Reverse all active QuickTweens within the specified world context.\n\nThis function finds the tween manager associated with \\p worldContextObject\nand reverses the playback direction of all currently active tweens. Tweens\nthat were playing forward will play backward, and vice versa.\n\n@param worldContextObject Context object used to locate the world that contains the tweens." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_worldContextObject_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenReverseAllTweens constinit property declarations ************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function QuickTweenReverseAllTweens constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenReverseAllTweens Property Definitions ***********************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenReverseAllTweens_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_worldContextObject_MetaData), NewProp_worldContextObject_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::NewProp_worldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenReverseAllTweens Property Definitions *************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenReverseAllTweens", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::QuickTweenLibrary_eventQuickTweenReverseAllTweens_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::QuickTweenLibrary_eventQuickTweenReverseAllTweens_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenReverseAllTweens)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UQuickTweenLibrary::QuickTweenReverseAllTweens(Z_Param_worldContextObject);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenReverseAllTweens *********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenRotateAroundPoint_SceneComponent ***
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that rotates a SceneComponent around a specified point and axis.\n\x09 *\n\x09 * The tween will drive a single float value (angle) from \\p from to \\p to over \\p duration\n\x09 * and apply that rotation to \\p component around \\p point using \\p normal as the rotation axis.\n\x09 *\n\x09 * Note: The starting position is determined by the current location of the component at the time of tween creation, unlike other functions that the starting position is determined at the first update.\n\x09 *\n\x09 * @param worldContextObject         Context object used to find the world for the tween.\n\x09 * @param component                  The SceneComponent to rotate around the point.\n\x09 * @param from                       Starting angle in degrees.\n\x09 * @param to                         Target angle in degrees.\n\x09 * @param point                      World-space point to rotate around.\n\x09 * @param normal                     Axis (normal) to rotate around.\n\x09 * @param duration                   Time in seconds for the tween to complete.\n\x09 * @param timeScale                  Multiplier applied to the tween time.\n\x09 * @param easeType                   Predefined easing type to use.\n\x09 * @param easeCurve                  Optional custom curve to evaluate easing.\n\x09 * @param loops                      Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType                   How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag                   Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill            If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused     If true the tween will update while game is paused.\n\x09 * @param bShouldAutoPlay            If true the tween will start playing immediately after creation.\n\x09 * @return                           A UQuickFloatTween pointer controlling the rotation, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that rotates a SceneComponent around a specified point and axis.\n\nThe tween will drive a single float value (angle) from \\p from to \\p to over \\p duration\nand apply that rotation to \\p component around \\p point using \\p normal as the rotation axis.\n\nNote: The starting position is determined by the current location of the component at the time of tween creation, unlike other functions that the starting position is determined at the first update.\n\n@param worldContextObject         Context object used to find the world for the tween.\n@param component                  The SceneComponent to rotate around the point.\n@param from                       Starting angle in degrees.\n@param to                         Target angle in degrees.\n@param point                      World-space point to rotate around.\n@param normal                     Axis (normal) to rotate around.\n@param duration                   Time in seconds for the tween to complete.\n@param timeScale                  Multiplier applied to the tween time.\n@param easeType                   Predefined easing type to use.\n@param easeCurve                  Optional custom curve to evaluate easing.\n@param loops                      Number of times to loop the tween. Use -1 for infinite.\n@param loopType                   How the tween loops (Restart, PingPong, etc.).\n@param tweenTag                   Optional tag to identify the created tween.\n@param bShouldAutoKill            If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused     If true the tween will update while game is paused.\n@param bShouldAutoPlay            If true the tween will start playing immediately after creation.\n@return                           A UQuickFloatTween pointer controlling the rotation, or nullptr on failure." },
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

// ********** Begin Function QuickTweenRotateAroundPoint_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenRotateAroundPoint_SceneComponent constinit property declarations 
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenRotateAroundPoint_SceneComponent Property Definitions *******
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_from = { "from", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, from), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_point = { "point", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, point), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_point_MetaData), NewProp_point_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_normal = { "normal", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, normal), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_normal_MetaData), NewProp_normal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_from,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_point,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_normal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenRotateAroundPoint_SceneComponent Property Definitions *********
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenRotateAroundPoint_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenRotateAroundPoint_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenRotateAroundPoint_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenRotateAroundPoint_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_from,Z_Param_to,Z_Param_Out_point,Z_Param_Out_normal,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenRotateAroundPoint_SceneComponent *****

// ********** Begin Class UQuickTweenLibrary Function QuickTweenRotateBy_SceneComponent ************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a rotator tween that rotates a SceneComponent by a relative rotator value.\n\x09 *\n\x09 * This method creates a `UQuickRotatorTween` which will drive the component's rotation\n\x09 * from its current rotation (cached at the first update) by the provided `by` rotator.\n\x09 * The rotation can be applied in world or local space according to `space`. When\n\x09 * `bUseShortestPath` is true the interpolation will pick the shortest angular path\n\x09 * for each axis.\n\x09 *\n\x09 * @param worldContextObject  Context object used to find the world for the tween.\n\x09 * @param component           The SceneComponent to rotate.\n\x09 * @param by                  Relative rotator to apply (added to the start rotation).\n\x09 * @param bUseShortestPath    If true rotation will take the shortest angular path.\n\x09 * @param duration            Time in seconds for the tween to complete.\n\x09 * @param timeScale           Multiplier applied to the tween time.\n\x09 * @param easeType            Predefined easing type to use.\n\x09 * @param easeCurve           Optional custom curve to evaluate easing.\n\x09 * @param loops               Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType            How the tween loops (Restart, PingPong, etc.).\n\x09 * @param space               Space in which to apply the relative rotation (World or Local).\n\x09 * @param tweenTag            Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill     If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while game is paused.\n\x09 * @param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n\x09 * @return                    A UQuickRotatorTween pointer controlling the rotation.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a rotator tween that rotates a SceneComponent by a relative rotator value.\n\nThis method creates a `UQuickRotatorTween` which will drive the component's rotation\nfrom its current rotation (cached at the first update) by the provided `by` rotator.\nThe rotation can be applied in world or local space according to `space`. When\n`bUseShortestPath` is true the interpolation will pick the shortest angular path\nfor each axis.\n\n@param worldContextObject  Context object used to find the world for the tween.\n@param component           The SceneComponent to rotate.\n@param by                  Relative rotator to apply (added to the start rotation).\n@param bUseShortestPath    If true rotation will take the shortest angular path.\n@param duration            Time in seconds for the tween to complete.\n@param timeScale           Multiplier applied to the tween time.\n@param easeType            Predefined easing type to use.\n@param easeCurve           Optional custom curve to evaluate easing.\n@param loops               Number of times to loop the tween. Use -1 for infinite.\n@param loopType            How the tween loops (Restart, PingPong, etc.).\n@param space               Space in which to apply the relative rotation (World or Local).\n@param tweenTag            Optional tag to identify the created tween.\n@param bShouldAutoKill     If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while game is paused.\n@param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n@return                    A UQuickRotatorTween pointer controlling the rotation." },
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

// ********** Begin Function QuickTweenRotateBy_SceneComponent constinit property declarations *****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenRotateBy_SceneComponent constinit property declarations *******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenRotateBy_SceneComponent Property Definitions ****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, by), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenRotateBy_SceneComponent Property Definitions ******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenRotateBy_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenRotateBy_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenRotateBy_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenRotateBy_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_Out_by,Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenRotateBy_SceneComponent **************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenRotateBy_Widget ********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics
{
	struct QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that rotates a UWidget by a relative angle.\n\x09 *\n\x09 * The tween will drive a single float value representing the widget's rotation angle\n\x09 * and apply a relative change of `by` degrees over `duration`. The widget's starting\n\x09 * rotation is sampled when the tween first updates. Easing may be controlled using a\n\x09 * predefined `EEaseType` or a custom `UCurveFloat`.\n\x09 *\n\x09 * @param worldContextObject    Context object used to find the world for the tween.\n\x09 * @param widget                The UWidget to rotate.\n\x09 * @param by                    Relative angle in degrees to rotate the widget (added to start rotation).\n\x09 * @param duration              Time in seconds for the tween to complete.\n\x09 * @param timeScale             Multiplier applied to the tween time.\n\x09 * @param easeType              Predefined easing function to use for interpolation.\n\x09 * @param easeCurve             Optional custom `UCurveFloat` used for easing (overrides `easeType` when provided).\n\x09 * @param loops                 Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType              How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag              Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill       If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n\x09 * @return                      Pointer to the created `UQuickFloatTween`.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that rotates a UWidget by a relative angle.\n\nThe tween will drive a single float value representing the widget's rotation angle\nand apply a relative change of `by` degrees over `duration`. The widget's starting\nrotation is sampled when the tween first updates. Easing may be controlled using a\npredefined `EEaseType` or a custom `UCurveFloat`.\n\n@param worldContextObject    Context object used to find the world for the tween.\n@param widget                The UWidget to rotate.\n@param by                    Relative angle in degrees to rotate the widget (added to start rotation).\n@param duration              Time in seconds for the tween to complete.\n@param timeScale             Multiplier applied to the tween time.\n@param easeType              Predefined easing function to use for interpolation.\n@param easeCurve             Optional custom `UCurveFloat` used for easing (overrides `easeType` when provided).\n@param loops                 Number of times to loop the tween. Use -1 for infinite.\n@param loopType              How the tween loops (Restart, PingPong, etc.).\n@param tweenTag              Optional tag to identify the created tween.\n@param bShouldAutoKill       If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n@return                      Pointer to the created `UQuickFloatTween`." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenRotateBy_Widget constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenRotateBy_Widget constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenRotateBy_Widget Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, by), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenRotateBy_Widget Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenRotateBy_Widget", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::QuickTweenLibrary_eventQuickTweenRotateBy_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenRotateBy_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenRotateBy_Widget(Z_Param_worldContextObject,Z_Param_widget,Z_Param_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenRotateBy_Widget **********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenRotateTo_SceneComponent ************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a rotator tween that rotates a SceneComponent to a target rotator.\n\x09 *\n\x09 * Note: The start and end value will be cached from the component's current location at the first update.\n\x09 *\n\x09 * @param worldContextObject  Context object used to find the world for the tween.\n\x09 * @param component           The SceneComponent to rotate.\n\x09 * @param to                  Target rotation (should be in the target space).\n\x09 * @param bUseShortestPath    If true rotation will take the shortest angular path.\n\x09 * @param duration            Time in seconds for the tween to complete.\n\x09 * @param timeScale           Multiplier applied to the tween time.\n\x09 * @param easeType            Predefined easing type to use.\n\x09 * @param easeCurve           Optional custom curve to evaluate easing.\n\x09 * @param loops               Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType            How the tween loops (Restart, PingPong, etc.).\n\x09 * @param space          Space in which to perform the look-at operation (World or Local).\n\x09 * @param tweenTag            Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill     If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while game is paused.\n\x09 * @param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n\x09 * @return                    A UQuickRotatorTween pointer controlling the rotation.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a rotator tween that rotates a SceneComponent to a target rotator.\n\nNote: The start and end value will be cached from the component's current location at the first update.\n\n@param worldContextObject  Context object used to find the world for the tween.\n@param component           The SceneComponent to rotate.\n@param to                  Target rotation (should be in the target space).\n@param bUseShortestPath    If true rotation will take the shortest angular path.\n@param duration            Time in seconds for the tween to complete.\n@param timeScale           Multiplier applied to the tween time.\n@param easeType            Predefined easing type to use.\n@param easeCurve           Optional custom curve to evaluate easing.\n@param loops               Number of times to loop the tween. Use -1 for infinite.\n@param loopType            How the tween loops (Restart, PingPong, etc.).\n@param space          Space in which to perform the look-at operation (World or Local).\n@param tweenTag            Optional tag to identify the created tween.\n@param bShouldAutoKill     If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while game is paused.\n@param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n@return                    A UQuickRotatorTween pointer controlling the rotation." },
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

// ********** Begin Function QuickTweenRotateTo_SceneComponent constinit property declarations *****
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenRotateTo_SceneComponent constinit property declarations *******
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenRotateTo_SceneComponent Property Definitions ****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms*)Obj)->bUseShortestPath = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath = { "bUseShortestPath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickRotatorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bUseShortestPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenRotateTo_SceneComponent Property Definitions ******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenRotateTo_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenRotateTo_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenRotateTo_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickRotatorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenRotateTo_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_Out_to,Z_Param_bUseShortestPath,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenRotateTo_SceneComponent **************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenRotateTo_Widget ********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics
{
	struct QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that rotates a UWidget to a target absolute angle.\n\x09 *\n\x09 * This tween drives a single float value representing the widget's rotation angle\n\x09 * and interpolates from the widget's current rotation (sampled at first update)\n\x09 * to the specified target \\p to over \\p duration seconds.\n\x09 *\n\x09 * Easing may be controlled using a predefined \\p EEaseType or a custom \\p UCurveFloat.\n\x09 *\n\x09 * @param worldContextObject    Context object used to find the world for the tween.\n\x09 * @param widget                The UWidget to rotate.\n\x09 * @param to                    Target absolute angle in degrees to rotate the widget to.\n\x09 * @param duration              Time in seconds for the tween to complete.\n\x09 * @param timeScale             Multiplier applied to the tween time.\n\x09 * @param easeType              Predefined easing function to use for interpolation.\n\x09 * @param easeCurve             Optional custom UCurveFloat used for easing (overrides \\p easeType when provided).\n\x09 * @param loops                 Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType              How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag              Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill       If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n\x09 * @return                      Pointer to the created UQuickFloatTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that rotates a UWidget to a target absolute angle.\n\nThis tween drives a single float value representing the widget's rotation angle\nand interpolates from the widget's current rotation (sampled at first update)\nto the specified target \\p to over \\p duration seconds.\n\nEasing may be controlled using a predefined \\p EEaseType or a custom \\p UCurveFloat.\n\n@param worldContextObject    Context object used to find the world for the tween.\n@param widget                The UWidget to rotate.\n@param to                    Target absolute angle in degrees to rotate the widget to.\n@param duration              Time in seconds for the tween to complete.\n@param timeScale             Multiplier applied to the tween time.\n@param easeType              Predefined easing function to use for interpolation.\n@param easeCurve             Optional custom UCurveFloat used for easing (overrides \\p easeType when provided).\n@param loops                 Number of times to loop the tween. Use -1 for infinite.\n@param loopType              How the tween loops (Restart, PingPong, etc.).\n@param tweenTag              Optional tag to identify the created tween.\n@param bShouldAutoKill       If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n@return                      Pointer to the created UQuickFloatTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_widget_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenRotateTo_Widget constinit property declarations *************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenRotateTo_Widget constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenRotateTo_Widget Property Definitions ************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenRotateTo_Widget Property Definitions **************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenRotateTo_Widget", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenRotateTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenRotateTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenRotateTo_Widget(Z_Param_worldContextObject,Z_Param_widget,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenRotateTo_Widget **********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenScalarParameterBy_Material *********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics
{
	struct QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that animates a scalar parameter on a dynamic material instance by a relative amount.\n\x09 *\n\x09 * The tween samples the material parameter's current value on the first update and interpolates\n\x09 * from that start value to (start + by) over the specified duration. Easing is controlled by\n\x09 * `easeType` or overridden by `easeCurve` when provided.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param material The UMaterialInstanceDynamic containing the scalar parameter.\n\x09 * @param parameterName The name of the scalar parameter to animate.\n\x09 * @param by Relative float value to add to the sampled start value.\n\x09 * @param duration Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param timeScale Multiplier applied to the tween time (default 1.0f).\n\x09 * @param easeType Predefined easing function to use for interpolation.\n\x09 * @param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops Number of times to loop the tween (-1 for infinite, default 1).\n\x09 * @param loopType How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n\x09 * @param tweenTag Optional tag to identify the created tween (default empty).\n\x09 * @param bShouldAutoKill If true the tween will be automatically killed when complete (default false).\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n\x09 * @param bShouldAutoPlay If true the tween will start playing immediately after creation (default false).\n\x09 * @return Pointer to the created UQuickFloatTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Float | Material" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that animates a scalar parameter on a dynamic material instance by a relative amount.\n\nThe tween samples the material parameter's current value on the first update and interpolates\nfrom that start value to (start + by) over the specified duration. Easing is controlled by\n`easeType` or overridden by `easeCurve` when provided.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param material The UMaterialInstanceDynamic containing the scalar parameter.\n@param parameterName The name of the scalar parameter to animate.\n@param by Relative float value to add to the sampled start value.\n@param duration Time in seconds for the tween to complete (default 1.0f).\n@param timeScale Multiplier applied to the tween time (default 1.0f).\n@param easeType Predefined easing function to use for interpolation.\n@param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops Number of times to loop the tween (-1 for infinite, default 1).\n@param loopType How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n@param tweenTag Optional tag to identify the created tween (default empty).\n@param bShouldAutoKill If true the tween will be automatically killed when complete (default false).\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n@param bShouldAutoPlay If true the tween will start playing immediately after creation (default false).\n@return Pointer to the created UQuickFloatTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenScalarParameterBy_Material constinit property declarations **
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenScalarParameterBy_Material constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenScalarParameterBy_Material Property Definitions *************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, by), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenScalarParameterBy_Material Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenScalarParameterBy_Material", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::QuickTweenLibrary_eventQuickTweenScalarParameterBy_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenScalarParameterBy_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenScalarParameterBy_Material(Z_Param_worldContextObject,Z_Param_material,Z_Param_Out_parameterName,Z_Param_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenScalarParameterBy_Material ***********

// ********** Begin Class UQuickTweenLibrary Function QuickTweenScalarParameterTo_Material *********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics
{
	struct QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a float tween that animates a scalar parameter on a dynamic material instance.\n\x09 *\n\x09 * The tween will sample the material parameter's current value on the first update and\n\x09 * interpolate from that start value to the provided `to` value over `duration` seconds.\n\x09 * Easing is controlled using `easeType` or overridden by `easeCurve` when provided.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param material The UMaterialInstanceDynamic containing the scalar parameter.\n\x09 * @param parameterName The name of the scalar parameter to animate.\n\x09 * @param to Target float value for the material parameter.\n\x09 * @param duration Time in seconds for the tween to complete (default 1.0f).\n\x09 * @param timeScale Multiplier applied to the tween time (default 1.0f).\n\x09 * @param easeType Predefined easing function to use for interpolation.\n\x09 * @param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops Number of times to loop the tween (-1 for infinite, default 1).\n\x09 * @param loopType How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n\x09 * @param tweenTag Optional tag to identify the created tween (default empty).\n\x09 * @param bShouldAutoKill If true the tween will be automatically killed when complete (default false).\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n\x09 * @param bShouldAutoPlay If true the tween will start playing immediately after creation (default false).\n\x09 * @return Pointer to the created UQuickFloatTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Float | Material" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a float tween that animates a scalar parameter on a dynamic material instance.\n\nThe tween will sample the material parameter's current value on the first update and\ninterpolate from that start value to the provided `to` value over `duration` seconds.\nEasing is controlled using `easeType` or overridden by `easeCurve` when provided.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param material The UMaterialInstanceDynamic containing the scalar parameter.\n@param parameterName The name of the scalar parameter to animate.\n@param to Target float value for the material parameter.\n@param duration Time in seconds for the tween to complete (default 1.0f).\n@param timeScale Multiplier applied to the tween time (default 1.0f).\n@param easeType Predefined easing function to use for interpolation.\n@param easeCurve Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops Number of times to loop the tween (-1 for infinite, default 1).\n@param loopType How the tween loops (Restart, PingPong, etc., default ELoopType::Restart).\n@param tweenTag Optional tag to identify the created tween (default empty).\n@param bShouldAutoKill If true the tween will be automatically killed when complete (default false).\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused (default false).\n@param bShouldAutoPlay If true the tween will start playing immediately after creation (default false).\n@return Pointer to the created UQuickFloatTween, or nullptr on failure." },
		{ "WorldContext", "worldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parameterName_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_tweenTag_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function QuickTweenScalarParameterTo_Material constinit property declarations **
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenScalarParameterTo_Material constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenScalarParameterTo_Material Property Definitions *************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, to), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickFloatTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenScalarParameterTo_Material Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenScalarParameterTo_Material", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::QuickTweenLibrary_eventQuickTweenScalarParameterTo_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenScalarParameterTo_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickFloatTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenScalarParameterTo_Material(Z_Param_worldContextObject,Z_Param_material,Z_Param_Out_parameterName,Z_Param_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenScalarParameterTo_Material ***********

// ********** Begin Class UQuickTweenLibrary Function QuickTweenScaleBy_SceneComponent *************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a vector tween that scales a SceneComponent by a relative amount.\n\x09 *\n\x09 * This function generates a UQuickVectorTween which will drive the component's scale\n\x09 * from its current value (cached at the first update) by adding the provided \\p by\n\x09 * vector to the start scale. The scale change is applied every tick via the tween's\n\x09 * setter. Easing can be controlled with either a predefined EEaseType or an optional\n\x09 * UCurveFloat. The operation can be performed in local or world space according to \\p space.\n\x09 *\n\x09 * @param worldContextObject    Context object used to find the world for the tween.\n\x09 * @param component             The SceneComponent to scale.\n\x09 * @param by                    Relative scale vector to apply (added to the start scale).\n\x09 * @param duration              Time in seconds for the tween to complete.\n\x09 * @param timeScale             Multiplier applied to the tween time.\n\x09 * @param easeType              Predefined easing type to use for interpolation.\n\x09 * @param easeCurve             Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops                 Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType              How the tween loops (Restart, PingPong, etc.).\n\x09 * @param space                 Space in which to apply the scale (World or Local).\n\x09 * @param tweenTag              Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill       If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n\x09 * @return                      A UQuickVectorTween pointer controlling the scale tween.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a vector tween that scales a SceneComponent by a relative amount.\n\nThis function generates a UQuickVectorTween which will drive the component's scale\nfrom its current value (cached at the first update) by adding the provided \\p by\nvector to the start scale. The scale change is applied every tick via the tween's\nsetter. Easing can be controlled with either a predefined EEaseType or an optional\nUCurveFloat. The operation can be performed in local or world space according to \\p space.\n\n@param worldContextObject    Context object used to find the world for the tween.\n@param component             The SceneComponent to scale.\n@param by                    Relative scale vector to apply (added to the start scale).\n@param duration              Time in seconds for the tween to complete.\n@param timeScale             Multiplier applied to the tween time.\n@param easeType              Predefined easing type to use for interpolation.\n@param easeCurve             Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops                 Number of times to loop the tween. Use -1 for infinite.\n@param loopType              How the tween loops (Restart, PingPong, etc.).\n@param space                 Space in which to apply the scale (World or Local).\n@param tweenTag              Optional tag to identify the created tween.\n@param bShouldAutoKill       If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n@return                      A UQuickVectorTween pointer controlling the scale tween." },
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

// ********** Begin Function QuickTweenScaleBy_SceneComponent constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenScaleBy_SceneComponent constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenScaleBy_SceneComponent Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, by), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenScaleBy_SceneComponent Property Definitions *******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenScaleBy_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenScaleBy_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenScaleBy_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenScaleBy_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenScaleBy_SceneComponent ***************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenScaleBy_Widget *********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics
{
	struct QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a Vector2D tween that scales a UWidget by a relative amount.\n\x09 *\n\x09 * This function creates a UQuickVector2DTween which will drive the widget's scale\n\x09 * from its current value (sampled at the first update) by adding the provided \\p by\n\x09 * vector to the start scale. Easing may be controlled using a predefined \\p EEaseType\n\x09 * or by supplying a custom \\p UCurveFloat. The tween will apply the interpolated\n\x09 * FVector2D value to the widget each tick.\n\x09 *\n\x09 * @param worldContextObject    Context object used to find the world for the tween.\n\x09 * @param widget                The UWidget to scale.\n\x09 * @param by                    Relative scale vector to apply (added to the start scale).\n\x09 * @param duration              Time in seconds for the tween to complete.\n\x09 * @param timeScale             Multiplier applied to the tween time.\n\x09 * @param easeType              Predefined easing function to use for interpolation.\n\x09 * @param easeCurve             Optional custom UCurveFloat used for easing (overrides \\p easeType when provided).\n\x09 * @param loops                 Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType              How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag              Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill       If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n\x09 * @return                      Pointer to the created UQuickVector2DTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a Vector2D tween that scales a UWidget by a relative amount.\n\nThis function creates a UQuickVector2DTween which will drive the widget's scale\nfrom its current value (sampled at the first update) by adding the provided \\p by\nvector to the start scale. Easing may be controlled using a predefined \\p EEaseType\nor by supplying a custom \\p UCurveFloat. The tween will apply the interpolated\nFVector2D value to the widget each tick.\n\n@param worldContextObject    Context object used to find the world for the tween.\n@param widget                The UWidget to scale.\n@param by                    Relative scale vector to apply (added to the start scale).\n@param duration              Time in seconds for the tween to complete.\n@param timeScale             Multiplier applied to the tween time.\n@param easeType              Predefined easing function to use for interpolation.\n@param easeCurve             Optional custom UCurveFloat used for easing (overrides \\p easeType when provided).\n@param loops                 Number of times to loop the tween. Use -1 for infinite.\n@param loopType              How the tween loops (Restart, PingPong, etc.).\n@param tweenTag              Optional tag to identify the created tween.\n@param bShouldAutoKill       If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay       If true the tween will start playing immediately after creation.\n@return                      Pointer to the created UQuickVector2DTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenScaleBy_Widget constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenScaleBy_Widget constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenScaleBy_Widget Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, by), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenScaleBy_Widget Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenScaleBy_Widget", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::QuickTweenLibrary_eventQuickTweenScaleBy_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenScaleBy_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenScaleBy_Widget(Z_Param_worldContextObject,Z_Param_widget,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenScaleBy_Widget ***********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenScaleTo_SceneComponent *************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics
{
	struct QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a vector tween that scales a SceneComponent to a target scale.\n\x09 *\n\x09 * Note: The start and end value will be cached from the component's current location at the first update.\n\x09 *\n\x09 * @param worldContextObject  Context object used to find the world for the tween.\n\x09 * @param component           The SceneComponent to scale.\n\x09 * @param to                  Target scale vector.\n\x09 * @param duration            Time in seconds for the tween to complete.\n\x09 * @param timeScale           Multiplier applied to the tween time.\n\x09 * @param easeType            Predefined easing type to use.\n\x09 * @param easeCurve           Optional custom curve to evaluate easing.\n\x09 * @param loops               Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType            How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag            Optional tag to identify the created tween.\n\x09 * @param space          Space in which to perform the look-at operation (World or Local).\n\x09 * @param bShouldAutoKill     If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while game is paused.\n\x09 * @param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n\x09 * @return                    A UQuickVectorTween pointer controlling the scale tween.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | SceneComponent" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a vector tween that scales a SceneComponent to a target scale.\n\nNote: The start and end value will be cached from the component's current location at the first update.\n\n@param worldContextObject  Context object used to find the world for the tween.\n@param component           The SceneComponent to scale.\n@param to                  Target scale vector.\n@param duration            Time in seconds for the tween to complete.\n@param timeScale           Multiplier applied to the tween time.\n@param easeType            Predefined easing type to use.\n@param easeCurve           Optional custom curve to evaluate easing.\n@param loops               Number of times to loop the tween. Use -1 for infinite.\n@param loopType            How the tween loops (Restart, PingPong, etc.).\n@param tweenTag            Optional tag to identify the created tween.\n@param space          Space in which to perform the look-at operation (World or Local).\n@param bShouldAutoKill     If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while game is paused.\n@param bShouldAutoPlay     If true the tween will start playing immediately after creation.\n@return                    A UQuickVectorTween pointer controlling the scale tween." },
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

// ********** Begin Function QuickTweenScaleTo_SceneComponent constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenScaleTo_SceneComponent constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenScaleTo_SceneComponent Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_component = { "component", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, component), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_component_MetaData), NewProp_component_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_space_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_space = { "space", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, space), Z_Construct_UEnum_QuickTween_EQuickTweenSpace, METADATA_PARAMS(0, nullptr) }; // 2719769293
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_component,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_space_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_space,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenScaleTo_SceneComponent Property Definitions *******************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenScaleTo_SceneComponent", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::QuickTweenLibrary_eventQuickTweenScaleTo_SceneComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenScaleTo_SceneComponent)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenScaleTo_SceneComponent(Z_Param_worldContextObject,Z_Param_component,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),EQuickTweenSpace(Z_Param_space),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenScaleTo_SceneComponent ***************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenScaleTo_Widget *********************
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics
{
	struct QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a Vector2D tween that scales a UWidget to a target absolute scale.\n\x09 *\n\x09 * This function creates a UQuickVector2DTween which will sample the widget's\n\x09 * current scale on the first update and interpolate from that start value to\n\x09 * the provided `to` target over `duration` seconds. Easing may be controlled\n\x09 * using a predefined `EEaseType` or by supplying a custom `UCurveFloat`.\n\x09 *\n\x09 * @param worldContextObject    Context object used to find the world for the tween.\n\x09 * @param widget                The UWidget to scale.\n\x09 * @param to                    Target absolute scale as an FVector2D.\n\x09 * @param duration              Time in seconds for the tween to complete. Defaults to 1.0f.\n\x09 * @param timeScale             Multiplier applied to the tween time. Defaults to 1.0f.\n\x09 * @param easeType              Predefined easing function to use for interpolation. Defaults to EEaseType::Linear.\n\x09 * @param easeCurve             Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09 * @param loops                 Number of times to loop the tween. Use -1 for infinite. Defaults to 1.\n\x09 * @param loopType              How the tween loops (Restart, PingPong, etc.). Defaults to ELoopType::Restart.\n\x09 * @param tweenTag              Optional tag to identify the created tween. Defaults to empty string.\n\x09 * @param bShouldAutoKill       If true the tween will be automatically killed when complete. Defaults to false.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused. Defaults to false.\n\x09 * @param bShouldAutoPlay       If true the tween will start playing immediately after creation. Defaults to false.\n\x09 * @return                      Pointer to the created UQuickVector2DTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Movement | Widget" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a Vector2D tween that scales a UWidget to a target absolute scale.\n\nThis function creates a UQuickVector2DTween which will sample the widget's\ncurrent scale on the first update and interpolate from that start value to\nthe provided `to` target over `duration` seconds. Easing may be controlled\nusing a predefined `EEaseType` or by supplying a custom `UCurveFloat`.\n\n@param worldContextObject    Context object used to find the world for the tween.\n@param widget                The UWidget to scale.\n@param to                    Target absolute scale as an FVector2D.\n@param duration              Time in seconds for the tween to complete. Defaults to 1.0f.\n@param timeScale             Multiplier applied to the tween time. Defaults to 1.0f.\n@param easeType              Predefined easing function to use for interpolation. Defaults to EEaseType::Linear.\n@param easeCurve             Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops                 Number of times to loop the tween. Use -1 for infinite. Defaults to 1.\n@param loopType              How the tween loops (Restart, PingPong, etc.). Defaults to ELoopType::Restart.\n@param tweenTag              Optional tag to identify the created tween. Defaults to empty string.\n@param bShouldAutoKill       If true the tween will be automatically killed when complete. Defaults to false.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused. Defaults to false.\n@param bShouldAutoPlay       If true the tween will start playing immediately after creation. Defaults to false.\n@return                      Pointer to the created UQuickVector2DTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenScaleTo_Widget constinit property declarations **************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenScaleTo_Widget constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenScaleTo_Widget Property Definitions *************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_widget = { "widget", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, widget), Z_Construct_UClass_UWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_widget_MetaData), NewProp_widget_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, to), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms, ReturnValue), Z_Construct_UClass_UQuickVector2DTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_widget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenScaleTo_Widget Property Definitions ***************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenScaleTo_Widget", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::QuickTweenLibrary_eventQuickTweenScaleTo_Widget_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenScaleTo_Widget)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVector2DTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenScaleTo_Widget(Z_Param_worldContextObject,Z_Param_widget,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenScaleTo_Widget ***********************

// ********** Begin Class UQuickTweenLibrary Function QuickTweenVectorParameterBy_Material *********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics
{
	struct QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09 * Create a vector tween that animates a vector parameter on a dynamic material instance by a relative amount.\n\x09 *\n\x09 * The tween samples the material parameter's current value on its first update and interpolates from that start\n\x09 * value to (start + by) over the specified duration. Easing is controlled by \\p easeType or overridden by\n\x09 * \\p easeCurve when provided.\n\x09 *\n\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09 * @param material The UMaterialInstanceDynamic containing the vector parameter.\n\x09 * @param parameterName The name of the vector parameter to animate.\n\x09 * @param by Relative FVector value to add to the sampled start value.\n\x09 * @param duration Time in seconds for the tween to complete.\n\x09 * @param timeScale Multiplier applied to the tween time.\n\x09 * @param easeType Predefined easing function to use for interpolation.\n\x09 * @param easeCurve Optional custom UCurveFloat used for easing (overrides \\p easeType when provided).\n\x09 * @param loops Number of times to loop the tween. Use -1 for infinite.\n\x09 * @param loopType How the tween loops (Restart, PingPong, etc.).\n\x09 * @param tweenTag Optional tag to identify the created tween.\n\x09 * @param bShouldAutoKill If true the tween will be automatically killed when complete.\n\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09 * @param bShouldAutoPlay If true the tween will start playing immediately after creation.\n\x09 * @return Pointer to the created UQuickVectorTween, or nullptr on failure.\n\x09 */" },
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
		{ "Keywords", "Tween | Vector | Material" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a vector tween that animates a vector parameter on a dynamic material instance by a relative amount.\n\nThe tween samples the material parameter's current value on its first update and interpolates from that start\nvalue to (start + by) over the specified duration. Easing is controlled by \\p easeType or overridden by\n\\p easeCurve when provided.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param material The UMaterialInstanceDynamic containing the vector parameter.\n@param parameterName The name of the vector parameter to animate.\n@param by Relative FVector value to add to the sampled start value.\n@param duration Time in seconds for the tween to complete.\n@param timeScale Multiplier applied to the tween time.\n@param easeType Predefined easing function to use for interpolation.\n@param easeCurve Optional custom UCurveFloat used for easing (overrides \\p easeType when provided).\n@param loops Number of times to loop the tween. Use -1 for infinite.\n@param loopType How the tween loops (Restart, PingPong, etc.).\n@param tweenTag Optional tag to identify the created tween.\n@param bShouldAutoKill If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay If true the tween will start playing immediately after creation.\n@return Pointer to the created UQuickVectorTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenVectorParameterBy_Material constinit property declarations **
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenVectorParameterBy_Material constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenVectorParameterBy_Material Property Definitions *************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_by = { "by", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, by), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_by_MetaData), NewProp_by_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_by,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenVectorParameterBy_Material Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenVectorParameterBy_Material", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::QuickTweenLibrary_eventQuickTweenVectorParameterBy_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenVectorParameterBy_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenVectorParameterBy_Material(Z_Param_worldContextObject,Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_by,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenVectorParameterBy_Material ***********

// ********** Begin Class UQuickTweenLibrary Function QuickTweenVectorParameterTo_Material *********
struct Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics
{
	struct QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms
	{
		UObject* worldContextObject;
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
		{ "Comment", "/**\n\x09\x09 * Create a vector tween that animates a vector parameter on a dynamic material instance.\n\x09\x09 *\n\x09\x09 * The tween will sample the material parameter's current value on the first update and\n\x09\x09 * interpolate from that start value to the provided `to` value over `duration` seconds.\n\x09\x09 * Easing is controlled using `easeType` or overridden by `easeCurve` when provided.\n\x09\x09 *\n\x09\x09 * @param worldContextObject Context object used to find the world for the tween.\n\x09\x09 * @param material           The UMaterialInstanceDynamic containing the vector parameter.\n\x09\x09 * @param parameterName      The name of the vector parameter to animate.\n\x09\x09 * @param to                 Target FVector value for the material parameter.\n\x09\x09 * @param duration           Time in seconds for the tween to complete.\n\x09\x09 * @param timeScale          Multiplier applied to the tween time.\n\x09\x09 * @param easeType           Predefined easing function to use for interpolation.\n\x09\x09 * @param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n\x09\x09 * @param loops              Number of times to loop the tween. Use -1 for infinite.\n\x09\x09 * @param loopType           How the tween loops (Restart, PingPong, etc.).\n\x09\x09 * @param tweenTag           Optional tag to identify the created tween.\n\x09\x09 * @param bShouldAutoKill    If true the tween will be automatically killed when complete.\n\x09\x09 * @param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n\x09\x09 * @param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n\x09\x09 * @return                   Pointer to the created UQuickVectorTween, or nullptr on failure.\n\x09\x09 */" },
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
		{ "Keywords", "Tween | Vector | Material" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "Create a vector tween that animates a vector parameter on a dynamic material instance.\n\nThe tween will sample the material parameter's current value on the first update and\ninterpolate from that start value to the provided `to` value over `duration` seconds.\nEasing is controlled using `easeType` or overridden by `easeCurve` when provided.\n\n@param worldContextObject Context object used to find the world for the tween.\n@param material           The UMaterialInstanceDynamic containing the vector parameter.\n@param parameterName      The name of the vector parameter to animate.\n@param to                 Target FVector value for the material parameter.\n@param duration           Time in seconds for the tween to complete.\n@param timeScale          Multiplier applied to the tween time.\n@param easeType           Predefined easing function to use for interpolation.\n@param easeCurve          Optional custom UCurveFloat used for easing (overrides easeType when provided).\n@param loops              Number of times to loop the tween. Use -1 for infinite.\n@param loopType           How the tween loops (Restart, PingPong, etc.).\n@param tweenTag           Optional tag to identify the created tween.\n@param bShouldAutoKill    If true the tween will be automatically killed when complete.\n@param bShouldPlayWhilePaused If true the tween will update while the game is paused.\n@param bShouldAutoPlay    If true the tween will start playing immediately after creation.\n@return                   Pointer to the created UQuickVectorTween, or nullptr on failure." },
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

// ********** Begin Function QuickTweenVectorParameterTo_Material constinit property declarations **
	static const UECodeGen_Private::FObjectPropertyParams NewProp_worldContextObject;
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
// ********** End Function QuickTweenVectorParameterTo_Material constinit property declarations ****
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function QuickTweenVectorParameterTo_Material Property Definitions *************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_worldContextObject = { "worldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, worldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_material = { "material", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, material), Z_Construct_UClass_UMaterialInstanceDynamic_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_parameterName = { "parameterName", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, parameterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parameterName_MetaData), NewProp_parameterName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_to = { "to", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, to), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_to_MetaData), NewProp_to_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_duration = { "duration", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, duration), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_timeScale = { "timeScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, timeScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_easeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_easeType = { "easeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, easeType), Z_Construct_UEnum_QuickTween_EEaseType, METADATA_PARAMS(0, nullptr) }; // 2272651248
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_easeCurve = { "easeCurve", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, easeCurve), Z_Construct_UClass_UCurveFloat_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_loops = { "loops", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, loops), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_loopType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_loopType = { "loopType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, loopType), Z_Construct_UEnum_QuickTween_ELoopType, METADATA_PARAMS(0, nullptr) }; // 1754923220
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_tweenTag = { "tweenTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, tweenTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_tweenTag_MetaData), NewProp_tweenTag_MetaData) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms*)Obj)->bShouldAutoKill = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill = { "bShouldAutoKill", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms*)Obj)->bShouldPlayWhilePaused = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused = { "bShouldPlayWhilePaused", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit(void* Obj)
{
	((QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms*)Obj)->bShouldAutoPlay = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay = { "bShouldAutoPlay", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms), &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms, ReturnValue), Z_Construct_UClass_UQuickVectorTween_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_worldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_parameterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_to,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_timeScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_easeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_easeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_easeCurve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_loops,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_loopType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_loopType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_tweenTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoKill,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldPlayWhilePaused,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_bShouldAutoPlay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::PropPointers) < 2048);
// ********** End Function QuickTweenVectorParameterTo_Material Property Definitions ***************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UQuickTweenLibrary, nullptr, "QuickTweenVectorParameterTo_Material", 	Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::QuickTweenLibrary_eventQuickTweenVectorParameterTo_Material_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UQuickTweenLibrary::execQuickTweenVectorParameterTo_Material)
{
	P_GET_OBJECT(UObject,Z_Param_worldContextObject);
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
	*(UQuickVectorTween**)Z_Param__Result=UQuickTweenLibrary::QuickTweenVectorParameterTo_Material(Z_Param_worldContextObject,Z_Param_material,Z_Param_Out_parameterName,Z_Param_Out_to,Z_Param_duration,Z_Param_timeScale,EEaseType(Z_Param_easeType),Z_Param_easeCurve,Z_Param_loops,ELoopType(Z_Param_loopType),Z_Param_tweenTag,Z_Param_bShouldAutoKill,Z_Param_bShouldPlayWhilePaused,Z_Param_bShouldAutoPlay);
	P_NATIVE_END;
}
// ********** End Class UQuickTweenLibrary Function QuickTweenVectorParameterTo_Material ***********

// ********** Begin Class UQuickTweenLibrary *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UQuickTweenLibrary;
UClass* UQuickTweenLibrary::GetPrivateStaticClass()
{
	using TClass = UQuickTweenLibrary;
	if (!Z_Registration_Info_UClass_UQuickTweenLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("QuickTweenLibrary"),
			Z_Registration_Info_UClass_UQuickTweenLibrary.InnerSingleton,
			StaticRegisterNativesUQuickTweenLibrary,
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
	return Z_Registration_Info_UClass_UQuickTweenLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UQuickTweenLibrary_NoRegister()
{
	return UQuickTweenLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UQuickTweenLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * UQuickTweenLibrary\n *\n * Blueprint function library exposing helpers to create and manage QuickTween\n * objects (sequences and tweens) from Blueprints and C++.\n *\n * This class is a static container (derived from UBlueprintFunctionLibrary)\n * providing factory functions for creating vector, rotator and float tweens,\n * plus convenience functions for common SceneComponent operations (move, rotate,\n * scale, look-at and rotate-around). All functions operate on the game thread\n * and require a valid world context object when applicable.\n */" },
		{ "IncludePath", "Blueprint/QuickTweenLibrary.h" },
		{ "ModuleRelativePath", "Public/Blueprint/QuickTweenLibrary.h" },
		{ "ToolTip", "UQuickTweenLibrary\n\nBlueprint function library exposing helpers to create and manage QuickTween\nobjects (sequences and tweens) from Blueprints and C++.\n\nThis class is a static container (derived from UBlueprintFunctionLibrary)\nproviding factory functions for creating vector, rotator and float tweens,\nplus convenience functions for common SceneComponent operations (move, rotate,\nscale, look-at and rotate-around). All functions operate on the game thread\nand require a valid world context object when applicable." },
	};
#endif // WITH_METADATA

// ********** Begin Class UQuickTweenLibrary constinit property declarations ***********************
// ********** End Class UQuickTweenLibrary constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("QuickTweenChangeColorTo_Image"), .Pointer = &UQuickTweenLibrary::execQuickTweenChangeColorTo_Image },
		{ .NameUTF8 = UTF8TEXT("QuickTweenChangeDistanceBy_SpringArm"), .Pointer = &UQuickTweenLibrary::execQuickTweenChangeDistanceBy_SpringArm },
		{ .NameUTF8 = UTF8TEXT("QuickTweenChangeDistanceTo_SpringArm"), .Pointer = &UQuickTweenLibrary::execQuickTweenChangeDistanceTo_SpringArm },
		{ .NameUTF8 = UTF8TEXT("QuickTweenChangeFovTo_Camera"), .Pointer = &UQuickTweenLibrary::execQuickTweenChangeFovTo_Camera },
		{ .NameUTF8 = UTF8TEXT("QuickTweenChangeOpacityTo_Widget"), .Pointer = &UQuickTweenLibrary::execQuickTweenChangeOpacityTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenColorParameterBy_Material"), .Pointer = &UQuickTweenLibrary::execQuickTweenColorParameterBy_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenColorParameterTo_Material"), .Pointer = &UQuickTweenLibrary::execQuickTweenColorParameterTo_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCompleteAllTweens"), .Pointer = &UQuickTweenLibrary::execQuickTweenCompleteAllTweens },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateSequence"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateSequence },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateTweenColor"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateTweenColor },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateTweenEmpty"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateTweenEmpty },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateTweenFloat"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateTweenFloat },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateTweenInt"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateTweenInt },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateTweenRotator"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateTweenRotator },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateTweenVector"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateTweenVector },
		{ .NameUTF8 = UTF8TEXT("QuickTweenCreateTweenVector2D"), .Pointer = &UQuickTweenLibrary::execQuickTweenCreateTweenVector2D },
		{ .NameUTF8 = UTF8TEXT("QuickTweenExecuteActionByPredicate"), .Pointer = &UQuickTweenLibrary::execQuickTweenExecuteActionByPredicate },
		{ .NameUTF8 = UTF8TEXT("QuickTweenExecuteActionOnAllTweens"), .Pointer = &UQuickTweenLibrary::execQuickTweenExecuteActionOnAllTweens },
		{ .NameUTF8 = UTF8TEXT("QuickTweenFindAllTweensByPredicate"), .Pointer = &UQuickTweenLibrary::execQuickTweenFindAllTweensByPredicate },
		{ .NameUTF8 = UTF8TEXT("QuickTweenFindTweenByTag"), .Pointer = &UQuickTweenLibrary::execQuickTweenFindTweenByTag },
		{ .NameUTF8 = UTF8TEXT("QuickTweenKillAllTweens"), .Pointer = &UQuickTweenLibrary::execQuickTweenKillAllTweens },
		{ .NameUTF8 = UTF8TEXT("QuickTweenLookAt_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenLookAt_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenMoveBy_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenMoveBy_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenMoveBy_Widget"), .Pointer = &UQuickTweenLibrary::execQuickTweenMoveBy_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenMoveTo_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenMoveTo_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenMoveTo_Widget"), .Pointer = &UQuickTweenLibrary::execQuickTweenMoveTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenPauseAllTweens"), .Pointer = &UQuickTweenLibrary::execQuickTweenPauseAllTweens },
		{ .NameUTF8 = UTF8TEXT("QuickTweenPlayAllTweens"), .Pointer = &UQuickTweenLibrary::execQuickTweenPlayAllTweens },
		{ .NameUTF8 = UTF8TEXT("QuickTweenReverseAllTweens"), .Pointer = &UQuickTweenLibrary::execQuickTweenReverseAllTweens },
		{ .NameUTF8 = UTF8TEXT("QuickTweenRotateAroundPoint_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenRotateAroundPoint_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenRotateBy_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenRotateBy_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenRotateBy_Widget"), .Pointer = &UQuickTweenLibrary::execQuickTweenRotateBy_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenRotateTo_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenRotateTo_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenRotateTo_Widget"), .Pointer = &UQuickTweenLibrary::execQuickTweenRotateTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenScalarParameterBy_Material"), .Pointer = &UQuickTweenLibrary::execQuickTweenScalarParameterBy_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenScalarParameterTo_Material"), .Pointer = &UQuickTweenLibrary::execQuickTweenScalarParameterTo_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenScaleBy_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenScaleBy_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenScaleBy_Widget"), .Pointer = &UQuickTweenLibrary::execQuickTweenScaleBy_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenScaleTo_SceneComponent"), .Pointer = &UQuickTweenLibrary::execQuickTweenScaleTo_SceneComponent },
		{ .NameUTF8 = UTF8TEXT("QuickTweenScaleTo_Widget"), .Pointer = &UQuickTweenLibrary::execQuickTweenScaleTo_Widget },
		{ .NameUTF8 = UTF8TEXT("QuickTweenVectorParameterBy_Material"), .Pointer = &UQuickTweenLibrary::execQuickTweenVectorParameterBy_Material },
		{ .NameUTF8 = UTF8TEXT("QuickTweenVectorParameterTo_Material"), .Pointer = &UQuickTweenLibrary::execQuickTweenVectorParameterTo_Material },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeColorTo_Image, "QuickTweenChangeColorTo_Image" }, // 3164387483
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceBy_SpringArm, "QuickTweenChangeDistanceBy_SpringArm" }, // 3093037054
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeDistanceTo_SpringArm, "QuickTweenChangeDistanceTo_SpringArm" }, // 640523074
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeFovTo_Camera, "QuickTweenChangeFovTo_Camera" }, // 1177528270
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenChangeOpacityTo_Widget, "QuickTweenChangeOpacityTo_Widget" }, // 4221956165
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterBy_Material, "QuickTweenColorParameterBy_Material" }, // 2715689714
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenColorParameterTo_Material, "QuickTweenColorParameterTo_Material" }, // 2816689122
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCompleteAllTweens, "QuickTweenCompleteAllTweens" }, // 3076417510
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateSequence, "QuickTweenCreateSequence" }, // 3832043533
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenColor, "QuickTweenCreateTweenColor" }, // 2897485268
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenEmpty, "QuickTweenCreateTweenEmpty" }, // 3250741212
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenFloat, "QuickTweenCreateTweenFloat" }, // 3502099330
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenInt, "QuickTweenCreateTweenInt" }, // 3448240947
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenRotator, "QuickTweenCreateTweenRotator" }, // 2347893291
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector, "QuickTweenCreateTweenVector" }, // 1292782124
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenCreateTweenVector2D, "QuickTweenCreateTweenVector2D" }, // 1632952426
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionByPredicate, "QuickTweenExecuteActionByPredicate" }, // 1296181149
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenExecuteActionOnAllTweens, "QuickTweenExecuteActionOnAllTweens" }, // 4168992265
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindAllTweensByPredicate, "QuickTweenFindAllTweensByPredicate" }, // 1419646675
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenFindTweenByTag, "QuickTweenFindTweenByTag" }, // 2276593372
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenKillAllTweens, "QuickTweenKillAllTweens" }, // 224001203
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenLookAt_SceneComponent, "QuickTweenLookAt_SceneComponent" }, // 3978136297
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_SceneComponent, "QuickTweenMoveBy_SceneComponent" }, // 1894769542
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveBy_Widget, "QuickTweenMoveBy_Widget" }, // 1634668916
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_SceneComponent, "QuickTweenMoveTo_SceneComponent" }, // 2380239565
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenMoveTo_Widget, "QuickTweenMoveTo_Widget" }, // 3712152076
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPauseAllTweens, "QuickTweenPauseAllTweens" }, // 2158735818
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenPlayAllTweens, "QuickTweenPlayAllTweens" }, // 4263684795
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenReverseAllTweens, "QuickTweenReverseAllTweens" }, // 2431324493
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateAroundPoint_SceneComponent, "QuickTweenRotateAroundPoint_SceneComponent" }, // 1893422547
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_SceneComponent, "QuickTweenRotateBy_SceneComponent" }, // 654998140
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateBy_Widget, "QuickTweenRotateBy_Widget" }, // 1209060083
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_SceneComponent, "QuickTweenRotateTo_SceneComponent" }, // 224077159
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenRotateTo_Widget, "QuickTweenRotateTo_Widget" }, // 2193033841
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterBy_Material, "QuickTweenScalarParameterBy_Material" }, // 4020154709
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScalarParameterTo_Material, "QuickTweenScalarParameterTo_Material" }, // 3788947070
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_SceneComponent, "QuickTweenScaleBy_SceneComponent" }, // 582812936
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleBy_Widget, "QuickTweenScaleBy_Widget" }, // 3457544279
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_SceneComponent, "QuickTweenScaleTo_SceneComponent" }, // 983517966
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenScaleTo_Widget, "QuickTweenScaleTo_Widget" }, // 2698378580
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterBy_Material, "QuickTweenVectorParameterBy_Material" }, // 4229806566
		{ &Z_Construct_UFunction_UQuickTweenLibrary_QuickTweenVectorParameterTo_Material, "QuickTweenVectorParameterTo_Material" }, // 3103475841
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickTweenLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UQuickTweenLibrary_Statics
UObject* (*const Z_Construct_UClass_UQuickTweenLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_QuickTween,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickTweenLibrary_Statics::ClassParams = {
	&UQuickTweenLibrary::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickTweenLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickTweenLibrary_Statics::Class_MetaDataParams)
};
void UQuickTweenLibrary::StaticRegisterNativesUQuickTweenLibrary()
{
	UClass* Class = UQuickTweenLibrary::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UQuickTweenLibrary_Statics::Funcs));
}
UClass* Z_Construct_UClass_UQuickTweenLibrary()
{
	if (!Z_Registration_Info_UClass_UQuickTweenLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickTweenLibrary.OuterSingleton, Z_Construct_UClass_UQuickTweenLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UQuickTweenLibrary.OuterSingleton;
}
UQuickTweenLibrary::UQuickTweenLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UQuickTweenLibrary);
UQuickTweenLibrary::~UQuickTweenLibrary() {}
// ********** End Class UQuickTweenLibrary *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h__Script_QuickTween_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UQuickTweenLibrary, UQuickTweenLibrary::StaticClass, TEXT("UQuickTweenLibrary"), &Z_Registration_Info_UClass_UQuickTweenLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickTweenLibrary), 2544572321U) },
	};
}; // Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h__Script_QuickTween_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h__Script_QuickTween_2901013123{
	TEXT("/Script/QuickTween"),
	Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h__Script_QuickTween_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h__Script_QuickTween_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
