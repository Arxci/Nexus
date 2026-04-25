// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Utils/EaseType.h"

#ifdef QUICKTWEEN_EaseType_generated_h
#error "EaseType.generated.h already included, missing '#pragma once' in EaseType.h"
#endif
#define QUICKTWEEN_EaseType_generated_h

#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/NoDestroy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_EaseType_h

// ********** Begin Enum EEaseType *****************************************************************
#define FOREACH_ENUM_EEASETYPE(op) \
	op(EEaseType::Linear) \
	op(EEaseType::InSine) \
	op(EEaseType::OutSine) \
	op(EEaseType::InOutSine) \
	op(EEaseType::InQuad) \
	op(EEaseType::OutQuad) \
	op(EEaseType::InOutQuad) \
	op(EEaseType::InCubic) \
	op(EEaseType::OutCubic) \
	op(EEaseType::InOutCubic) \
	op(EEaseType::InQuart) \
	op(EEaseType::OutQuart) \
	op(EEaseType::InOutQuart) \
	op(EEaseType::InQuint) \
	op(EEaseType::OutQuint) \
	op(EEaseType::InOutQuint) \
	op(EEaseType::InExpo) \
	op(EEaseType::OutExpo) \
	op(EEaseType::InOutExpo) \
	op(EEaseType::InCirc) \
	op(EEaseType::OutCirc) \
	op(EEaseType::InOutCirc) \
	op(EEaseType::InBack) \
	op(EEaseType::OutBack) \
	op(EEaseType::InOutBack) \
	op(EEaseType::InElastic) \
	op(EEaseType::OutElastic) \
	op(EEaseType::InOutElastic) \
	op(EEaseType::InBounce) \
	op(EEaseType::OutBounce) \
	op(EEaseType::InOutBounce) 

enum class EEaseType : uint8;
template<> struct TIsUEnumClass<EEaseType> { enum { Value = true }; };
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<EEaseType>();
// ********** End Enum EEaseType *******************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
