// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Blueprint/QuickTweenLatentLibrary.h"

#ifdef QUICKTWEEN_QuickTweenLatentLibrary_generated_h
#error "QuickTweenLatentLibrary.generated.h already included, missing '#pragma once' in QuickTweenLatentLibrary.h"
#endif
#define QUICKTWEEN_QuickTweenLatentLibrary_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UCameraComponent;
class UCurveFloat;
class UImage;
class UMaterialInstanceDynamic;
class UObject;
class UQuickColorTween;
class UQuickEmptyTween;
class UQuickFloatTween;
class UQuickIntTween;
class UQuickRotatorTween;
class UQuickTweenSequence;
class UQuickVector2DTween;
class UQuickVectorTween;
class USceneComponent;
class USpringArmComponent;
class UWidget;
enum class EEaseType : uint8;
enum class ELoopType : uint8;
enum class EQuickTweenLatentSteps : uint8;
enum class EQuickTweenSpace : uint8;
struct FColor;
struct FLatentActionInfo;

// ********** Begin Class UQuickTweenLatentLibrary *************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_39_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execQuickTweenLatentColorParameterBy_Material); \
	DECLARE_FUNCTION(execQuickTweenLatentColorParameterTo_Material); \
	DECLARE_FUNCTION(execQuickTweenLatentScalarParameterBy_Material); \
	DECLARE_FUNCTION(execQuickTweenLatentScalarParameterTo_Material); \
	DECLARE_FUNCTION(execQuickTweenLatentVectorParameterBy_Material); \
	DECLARE_FUNCTION(execQuickTweenLatentVectorParameterTo_Material); \
	DECLARE_FUNCTION(execQuickTweenLatentChangeDistanceBy_SpringArm); \
	DECLARE_FUNCTION(execQuickTweenLatentChangeDistanceTo_SpringArm); \
	DECLARE_FUNCTION(execQuickTweenLatentChangeFovTo_Camera); \
	DECLARE_FUNCTION(execQuickTweenLatentChangeOpacityTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenLatentChangeColorTo_Image); \
	DECLARE_FUNCTION(execQuickTweenLatentRotateAroundPoint_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLatentLookAt_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLatentRotateBy_Widget); \
	DECLARE_FUNCTION(execQuickTweenLatentRotateBy_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLatentRotateTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenLatentRotateTo_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLatentScaleBy_Widget); \
	DECLARE_FUNCTION(execQuickTweenLatentScaleBy_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLatentScaleTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenLatentScaleTo_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLatentMoveBy_Widget); \
	DECLARE_FUNCTION(execQuickTweenLatentMoveBy_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLatentMoveTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenLatentMoveTo_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentTweenEmpty); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentTweenInt); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentTweenColor); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentTweenVector2D); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentTweenFloat); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentTweenRotator); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentTweenVector); \
	DECLARE_FUNCTION(execQuickTweenCreateLatentSequence);


struct Z_Construct_UClass_UQuickTweenLatentLibrary_Statics;
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenLatentLibrary_NoRegister();

#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_39_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUQuickTweenLatentLibrary(); \
	friend struct ::Z_Construct_UClass_UQuickTweenLatentLibrary_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend QUICKTWEEN_API UClass* ::Z_Construct_UClass_UQuickTweenLatentLibrary_NoRegister(); \
public: \
	DECLARE_CLASS2(UQuickTweenLatentLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/QuickTween"), Z_Construct_UClass_UQuickTweenLatentLibrary_NoRegister) \
	DECLARE_SERIALIZER(UQuickTweenLatentLibrary)


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_39_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UQuickTweenLatentLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UQuickTweenLatentLibrary(UQuickTweenLatentLibrary&&) = delete; \
	UQuickTweenLatentLibrary(const UQuickTweenLatentLibrary&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UQuickTweenLatentLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UQuickTweenLatentLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UQuickTweenLatentLibrary) \
	NO_API virtual ~UQuickTweenLatentLibrary();


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_36_PROLOG
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_39_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_39_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_39_INCLASS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h_39_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UQuickTweenLatentLibrary;

// ********** End Class UQuickTweenLatentLibrary ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLatentLibrary_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
