// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Blueprint/QuickTweenLibrary.h"

#ifdef QUICKTWEEN_QuickTweenLibrary_generated_h
#error "QuickTweenLibrary.generated.h already included, missing '#pragma once' in QuickTweenLibrary.h"
#endif
#define QUICKTWEEN_QuickTweenLibrary_generated_h

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
class UQuickTweenable;
class UQuickTweenSequence;
class UQuickVector2DTween;
class UQuickVectorTween;
class USceneComponent;
class USpringArmComponent;
class UWidget;
enum class EEaseType : uint8;
enum class ELoopType : uint8;
enum class EQuickTweenSpace : uint8;
struct FColor;

// ********** Begin Class UQuickTweenLibrary *******************************************************
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_43_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execQuickTweenExecuteActionByPredicate); \
	DECLARE_FUNCTION(execQuickTweenExecuteActionOnAllTweens); \
	DECLARE_FUNCTION(execQuickTweenCompleteAllTweens); \
	DECLARE_FUNCTION(execQuickTweenReverseAllTweens); \
	DECLARE_FUNCTION(execQuickTweenPlayAllTweens); \
	DECLARE_FUNCTION(execQuickTweenPauseAllTweens); \
	DECLARE_FUNCTION(execQuickTweenKillAllTweens); \
	DECLARE_FUNCTION(execQuickTweenFindAllTweensByPredicate); \
	DECLARE_FUNCTION(execQuickTweenFindTweenByTag); \
	DECLARE_FUNCTION(execQuickTweenColorParameterBy_Material); \
	DECLARE_FUNCTION(execQuickTweenColorParameterTo_Material); \
	DECLARE_FUNCTION(execQuickTweenScalarParameterBy_Material); \
	DECLARE_FUNCTION(execQuickTweenScalarParameterTo_Material); \
	DECLARE_FUNCTION(execQuickTweenVectorParameterBy_Material); \
	DECLARE_FUNCTION(execQuickTweenVectorParameterTo_Material); \
	DECLARE_FUNCTION(execQuickTweenChangeDistanceBy_SpringArm); \
	DECLARE_FUNCTION(execQuickTweenChangeDistanceTo_SpringArm); \
	DECLARE_FUNCTION(execQuickTweenChangeFovTo_Camera); \
	DECLARE_FUNCTION(execQuickTweenChangeOpacityTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenChangeColorTo_Image); \
	DECLARE_FUNCTION(execQuickTweenRotateAroundPoint_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenLookAt_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenRotateBy_Widget); \
	DECLARE_FUNCTION(execQuickTweenRotateBy_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenRotateTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenRotateTo_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenScaleBy_Widget); \
	DECLARE_FUNCTION(execQuickTweenScaleBy_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenScaleTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenScaleTo_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenMoveBy_Widget); \
	DECLARE_FUNCTION(execQuickTweenMoveBy_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenMoveTo_Widget); \
	DECLARE_FUNCTION(execQuickTweenMoveTo_SceneComponent); \
	DECLARE_FUNCTION(execQuickTweenCreateTweenEmpty); \
	DECLARE_FUNCTION(execQuickTweenCreateTweenInt); \
	DECLARE_FUNCTION(execQuickTweenCreateTweenColor); \
	DECLARE_FUNCTION(execQuickTweenCreateTweenVector2D); \
	DECLARE_FUNCTION(execQuickTweenCreateTweenFloat); \
	DECLARE_FUNCTION(execQuickTweenCreateTweenRotator); \
	DECLARE_FUNCTION(execQuickTweenCreateTweenVector); \
	DECLARE_FUNCTION(execQuickTweenCreateSequence);


struct Z_Construct_UClass_UQuickTweenLibrary_Statics;
QUICKTWEEN_API UClass* Z_Construct_UClass_UQuickTweenLibrary_NoRegister();

#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_43_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUQuickTweenLibrary(); \
	friend struct ::Z_Construct_UClass_UQuickTweenLibrary_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend QUICKTWEEN_API UClass* ::Z_Construct_UClass_UQuickTweenLibrary_NoRegister(); \
public: \
	DECLARE_CLASS2(UQuickTweenLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/QuickTween"), Z_Construct_UClass_UQuickTweenLibrary_NoRegister) \
	DECLARE_SERIALIZER(UQuickTweenLibrary)


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_43_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UQuickTweenLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UQuickTweenLibrary(UQuickTweenLibrary&&) = delete; \
	UQuickTweenLibrary(const UQuickTweenLibrary&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UQuickTweenLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UQuickTweenLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UQuickTweenLibrary) \
	NO_API virtual ~UQuickTweenLibrary();


#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_40_PROLOG
#define FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_43_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_43_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_43_INCLASS_NO_PURE_DECLS \
	FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h_43_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UQuickTweenLibrary;

// ********** End Class UQuickTweenLibrary *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_build_U5M_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_QuickTweenLibrary_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
