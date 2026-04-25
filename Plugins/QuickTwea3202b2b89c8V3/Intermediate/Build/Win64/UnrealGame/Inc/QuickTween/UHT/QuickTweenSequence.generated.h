// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Tweens/QuickTweenSequence.h"

#ifdef QUICKTWEEN_QuickTweenSequence_generated_h
#error "QuickTweenSequence.generated.h already included, missing '#pragma once' in QuickTweenSequence.h"
#endif
#define QUICKTWEEN_QuickTweenSequence_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UQuickTweenable;
class UQuickTweenSequence;

// ********** Begin Delegate FDynamicDelegateTweenSequence *****************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_18_DELEGATE \
QUICKTWEEN_API void FDynamicDelegateTweenSequence_DelegateWrapper(const FScriptDelegate& DynamicDelegateTweenSequence, UQuickTweenSequence* TweenSequence);


// ********** End Delegate FDynamicDelegateTweenSequence *******************************************

// ********** Begin ScriptStruct FQuickTweenSequenceGroup ******************************************
struct Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics;
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_27_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FQuickTweenSequenceGroup_Statics; \
	QUICKTWEEN_API static class UScriptStruct* StaticStruct();


struct FQuickTweenSequenceGroup;
// ********** End ScriptStruct FQuickTweenSequenceGroup ********************************************

// ********** Begin Class UQuickTweenSequence ******************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRemoveAllOnLoopEvent); \
	DECLARE_FUNCTION(execRemoveAllOnKilledEvent); \
	DECLARE_FUNCTION(execRemoveAllOnCompleteEvent); \
	DECLARE_FUNCTION(execRemoveAllOnUpdateEvent); \
	DECLARE_FUNCTION(execRemoveAllOnStartEvent); \
	DECLARE_FUNCTION(execAssignOnLoopEvent); \
	DECLARE_FUNCTION(execAssignOnKilledEvent); \
	DECLARE_FUNCTION(execAssignOnCompleteEvent); \
	DECLARE_FUNCTION(execAssignOnUpdateEvent); \
	DECLARE_FUNCTION(execAssignOnStartEvent); \
	DECLARE_FUNCTION(execGetTween); \
	DECLARE_FUNCTION(execGetNumTweens); \
	DECLARE_FUNCTION(execAppend); \
	DECLARE_FUNCTION(execJoin);


struct Z_Construct_UClass_UQuickTweenSequence_Statics;
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenSequence_NoRegister();

#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_50_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUQuickTweenSequence(); \
	friend struct ::Z_Construct_UClass_UQuickTweenSequence_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend QUICKTWEEN_API UClass* ::Z_Construct_UClass_UQuickTweenSequence_NoRegister(); \
public: \
	DECLARE_CLASS2(UQuickTweenSequence, UQuickTweenable, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/QuickTween"), Z_Construct_UClass_UQuickTweenSequence_NoRegister) \
	DECLARE_SERIALIZER(UQuickTweenSequence)


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_50_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UQuickTweenSequence(UQuickTweenSequence&&) = delete; \
	UQuickTweenSequence(const UQuickTweenSequence&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UQuickTweenSequence); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UQuickTweenSequence); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UQuickTweenSequence)


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_47_PROLOG
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_50_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_50_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_50_INCLASS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h_50_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UQuickTweenSequence;

// ********** End Class UQuickTweenSequence ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenSequence_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
