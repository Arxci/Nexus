// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

// Per-subsystem log categories. One category per gameplay subsystem keeps the
// Output Log filterable (e.g. `Log LogNexusEquipment Verbose`) and avoids the
// catch-all LogTemp. Declared here, defined in Nexus.cpp.
DECLARE_LOG_CATEGORY_EXTERN(LogNexusAbilitySystem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusCharacter, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusCombat, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusEquipment, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusGame, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusInput, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusInteraction, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusInventory, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusLevelLoader, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogNexusWeapon, Log, All);