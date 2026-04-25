// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "QuickTweenable.h"

#ifdef QUICKTWEEN_QuickTweenable_generated_h
#error "QuickTweenable.generated.h already included, missing '#pragma once' in QuickTweenable.h"
#endif
#define QUICKTWEEN_QuickTweenable_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UCurveFloat;
enum class EEaseType : uint8;
enum class ELoopType : uint8;

// ********** Begin Class UQuickTweenable **********************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetShouldPlayWhilePaused); \
	DECLARE_FUNCTION(execGetAutoKill); \
	DECLARE_FUNCTION(execGetCurrentLoop); \
	DECLARE_FUNCTION(execGetTweenTag); \
	DECLARE_FUNCTION(execGetLoopType); \
	DECLARE_FUNCTION(execGetLoops); \
	DECLARE_FUNCTION(execGetEaseCurve); \
	DECLARE_FUNCTION(execGetEaseType); \
	DECLARE_FUNCTION(execGetIsReversed); \
	DECLARE_FUNCTION(execGetIsCompleted); \
	DECLARE_FUNCTION(execGetIsPlaying); \
	DECLARE_FUNCTION(execGetTimeScale); \
	DECLARE_FUNCTION(execGetElapsedTime); \
	DECLARE_FUNCTION(execGetTotalDuration); \
	DECLARE_FUNCTION(execGetLoopDuration); \
	DECLARE_FUNCTION(execGetIsPendingKill); \
	DECLARE_FUNCTION(execKill); \
	DECLARE_FUNCTION(execComplete); \
	DECLARE_FUNCTION(execRestart); \
	DECLARE_FUNCTION(execReverse); \
	DECLARE_FUNCTION(execPause); \
	DECLARE_FUNCTION(execPlay);


struct Z_Construct_UClass_UQuickTweenable_Statics;
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenable_NoRegister();

#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUQuickTweenable(); \
	friend struct ::Z_Construct_UClass_UQuickTweenable_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend QUICKTWEEN_API UClass* ::Z_Construct_UClass_UQuickTweenable_NoRegister(); \
public: \
	DECLARE_CLASS2(UQuickTweenable, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/QuickTween"), Z_Construct_UClass_UQuickTweenable_NoRegister) \
	DECLARE_SERIALIZER(UQuickTweenable)


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_25_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UQuickTweenable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UQuickTweenable(UQuickTweenable&&) = delete; \
	UQuickTweenable(const UQuickTweenable&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UQuickTweenable); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UQuickTweenable); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UQuickTweenable) \
	NO_API virtual ~UQuickTweenable();


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_22_PROLOG
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_25_INCLASS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UQuickTweenable;

// ********** End Class UQuickTweenable ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_QuickTweenable_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
