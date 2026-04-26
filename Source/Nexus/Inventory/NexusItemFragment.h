// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "NexusItemFragment.generated.h"

class UNexusItemDefinition;
class UNexusItemInstance;

/**
 * Base class for all item-definition fragments.
 *
 * Fragments are pure data, authored on UNexusItemDefinition::Fragments via
 * TInstancedStruct. Each subclass declares one capability (Stackable,
 * Equippable, Weapon, Consumable, KeyItem, Document, ...).
 *
 * Per-instance mutable state does NOT live here — runtime mutation is stored
 * on UNexusItemInstance::StatTags so that fragments stay shareable across all
 * instances of the same definition.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusItemFragment
{
	GENERATED_BODY()

	virtual ~FNexusItemFragment() = default;

	/** Optional hook for fragments that need to seed StatTags on a fresh instance. */
	virtual void InitializeInstance(UNexusItemInstance* Instance) const {}
};