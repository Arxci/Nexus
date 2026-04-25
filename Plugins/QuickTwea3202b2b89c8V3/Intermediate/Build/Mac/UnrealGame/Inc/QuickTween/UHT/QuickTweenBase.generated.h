// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Tweens/QuickTweenBase.h"

#ifdef QUICKTWEEN_QuickTweenBase_generated_h
#error "QuickTweenBase.generated.h already included, missing '#pragma once' in QuickTweenBase.h"
#endif
#define QUICKTWEEN_QuickTweenBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UQuickTweenBase;

// ********** Begin Delegate FDynamicDelegateTween *************************************************
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_18_DELEGATE \
QUICKTWEEN_API void FDynamicDelegateTween_DelegateWrapper(const FScriptDelegate& DynamicDelegateTween, UQuickTweenBase* Tween);


// ********** End Delegate FDynamicDelegateTween ***************************************************

// ********** Begin Class UQuickTweenBase **********************************************************
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRemoveAllOnLoopEvent); \
	DECLARE_FUNCTION(execRemoveAllOnKilledEvent); \
	DECLARE_FUNCTION(execRemoveAllOnCompleteEvent); \
	DECLARE_FUNCTION(execRemoveAllOnUpdateEvent); \
	DECLARE_FUNCTION(execRemoveAllOnStartEvent); \
	DECLARE_FUNCTION(execAssignOnLoopEvent); \
	DECLARE_FUNCTION(execAssignOnKilledEvent); \
	DECLARE_FUNCTION(execAssignOnCompleteEvent); \
	DECLARE_FUNCTION(execAssignOnUpdateEvent); \
	DECLARE_FUNCTION(execAssignOnStartEvent);


struct Z_Construct_UClass_UQuickTweenBase_Statics;
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenBase_NoRegister();

#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUQuickTweenBase(); \
	friend struct ::Z_Construct_UClass_UQuickTweenBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend QUICKTWEEN_API UClass* ::Z_Construct_UClass_UQuickTweenBase_NoRegister(); \
public: \
	DECLARE_CLASS2(UQuickTweenBase, UQuickTweenable, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/QuickTween"), Z_Construct_UClass_UQuickTweenBase_NoRegister) \
	DECLARE_SERIALIZER(UQuickTweenBase)


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_27_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UQuickTweenBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UQuickTweenBase(UQuickTweenBase&&) = delete; \
	UQuickTweenBase(const UQuickTweenBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UQuickTweenBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UQuickTweenBase); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UQuickTweenBase)


#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_24_PROLOG
#define FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_27_INCLASS_NO_PURE_DECLS \
	FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UQuickTweenBase;

// ********** End Class UQuickTweenBase ************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Tweens_QuickTweenBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
