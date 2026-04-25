// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Utils/LoopType.h"

#ifdef QUICKTWEEN_LoopType_generated_h
#error "LoopType.generated.h already included, missing '#pragma once' in LoopType.h"
#endif
#define QUICKTWEEN_LoopType_generated_h

#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/NoDestroy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Build_U5M_Mac_Sync_LocalBuilds_PluginTemp_HostProject_Plugins_QuickTween_Source_QuickTween_Public_Utils_LoopType_h

// ********** Begin Enum ELoopType *****************************************************************
#define FOREACH_ENUM_ELOOPTYPE(op) \
	op(ELoopType::Restart) \
	op(ELoopType::PingPong) 

enum class ELoopType : uint8;
template<> struct TIsUEnumClass<ELoopType> { enum { Value = true }; };
template<> QUICKTWEEN_NON_ATTRIBUTED_API UEnum* StaticEnum<ELoopType>();
// ********** End Enum ELoopType *******************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
