// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Utils/CommonValues.h"

#ifdef QUICKTWEEN_CommonValues_generated_h
#error "CommonValues.generated.h already included, missing '#pragma once' in CommonValues.h"
#endif
#define QUICKTWEEN_CommonValues_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UQuickTweenable;
struct FColor;

// ********** Begin Delegate FVectorSetter *********************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_8_DELEGATE \
QUICKTWEEN_API void FVectorSetter_DelegateWrapper(const FScriptDelegate& VectorSetter, FVector const& value, UQuickTweenable* tween);


// ********** End Delegate FVectorSetter ***********************************************************

// ********** Begin Delegate FRotatorSetter ********************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_9_DELEGATE \
QUICKTWEEN_API void FRotatorSetter_DelegateWrapper(const FScriptDelegate& RotatorSetter, FRotator const& value, UQuickTweenable* tween);


// ********** End Delegate FRotatorSetter **********************************************************

// ********** Begin Delegate FFloatSetter **********************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_10_DELEGATE \
QUICKTWEEN_API void FFloatSetter_DelegateWrapper(const FScriptDelegate& FloatSetter, const float value, UQuickTweenable* tween);


// ********** End Delegate FFloatSetter ************************************************************

// ********** Begin Delegate FVector2DSetter *******************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_11_DELEGATE \
QUICKTWEEN_API void FVector2DSetter_DelegateWrapper(const FScriptDelegate& Vector2DSetter, FVector2D const& value, UQuickTweenable* tween);


// ********** End Delegate FVector2DSetter *********************************************************

// ********** Begin Delegate FColorSetter **********************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_12_DELEGATE \
QUICKTWEEN_API void FColorSetter_DelegateWrapper(const FScriptDelegate& ColorSetter, FColor const& value, UQuickTweenable* tween);


// ********** End Delegate FColorSetter ************************************************************

// ********** Begin Delegate FIntSetter ************************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_13_DELEGATE \
QUICKTWEEN_API void FIntSetter_DelegateWrapper(const FScriptDelegate& IntSetter, const int32 value, UQuickTweenable* tween);


// ********** End Delegate FIntSetter **************************************************************

// ********** Begin Delegate FQuickTweenableAction *************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_14_DELEGATE \
QUICKTWEEN_API void FQuickTweenableAction_DelegateWrapper(const FScriptDelegate& QuickTweenableAction, UQuickTweenable* tween);


// ********** End Delegate FQuickTweenableAction ***************************************************

// ********** Begin Delegate FQuickConstTweenableAction ********************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h_15_DELEGATE \
QUICKTWEEN_API void FQuickConstTweenableAction_DelegateWrapper(const FScriptDelegate& QuickConstTweenableAction, const UQuickTweenable* tween);


// ********** End Delegate FQuickConstTweenableAction **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_CommonValues_h

// ********** Begin Enum EQuickTweenSpace **********************************************************
#define FOREACH_ENUM_EQUICKTWEENSPACE(op) \
	op(EQuickTweenSpace::WorldSpace) \
	op(EQuickTweenSpace::LocalSpace) 

enum class EQuickTweenSpace : uint8;
template<> struct TIsUEnumClass<EQuickTweenSpace> { enum { Value = true }; };
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EQuickTweenSpace>();
// ********** End Enum EQuickTweenSpace ************************************************************

// ********** Begin Enum EQuickTweenState **********************************************************
#define FOREACH_ENUM_EQUICKTWEENSTATE(op) \
	op(EQuickTweenState::Idle) \
	op(EQuickTweenState::Play) \
	op(EQuickTweenState::Pause) \
	op(EQuickTweenState::Complete) \
	op(EQuickTweenState::Kill) 

enum class EQuickTweenState : uint8;
template<> struct TIsUEnumClass<EQuickTweenState> { enum { Value = true }; };
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EQuickTweenState>();
// ********** End Enum EQuickTweenState ************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
