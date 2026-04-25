// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Blueprint/Latent/FQuickTweenLatentAction.h"

#ifdef QUICKTWEEN_FQuickTweenLatentAction_generated_h
#error "FQuickTweenLatentAction.generated.h already included, missing '#pragma once' in FQuickTweenLatentAction.h"
#endif
#define QUICKTWEEN_FQuickTweenLatentAction_generated_h

#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/NoDestroy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Blueprint_Latent_FQuickTweenLatentAction_h

// ********** Begin Enum EQuickTweenLatentSteps ****************************************************
#define FOREACH_ENUM_EQUICKTWEENLATENTSTEPS(op) \
	op(EQuickTweenLatentSteps::Default) \
	op(EQuickTweenLatentSteps::OnStart) \
	op(EQuickTweenLatentSteps::OnUpdate) \
	op(EQuickTweenLatentSteps::OnLoop) \
	op(EQuickTweenLatentSteps::OnComplete) \
	op(EQuickTweenLatentSteps::OnKilled) 

enum class EQuickTweenLatentSteps : uint8;
template<> struct TIsUEnumClass<EQuickTweenLatentSteps> { enum { Value = true }; };
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EQuickTweenLatentSteps>();
// ********** End Enum EQuickTweenLatentSteps ******************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
