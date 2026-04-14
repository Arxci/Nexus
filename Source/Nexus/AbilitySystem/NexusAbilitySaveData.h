// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NexusAbility.h"
#include "NexusAbilitySaveData.generated.h"

/**
 * Per-ability snapshot used by the save system.
 *
 * The base fields (activation, enabled, cooldown) are populated automatically
 * by UNexusAbility::GatherSaveState. Subclasses append ability-specific data
 * (e.g. intent tags) to CustomTags via their GatherSaveState override.
 */
USTRUCT()
struct NEXUS_API FNexusAbilitySaveData
{
	GENERATED_BODY()

	/** The class of the ability this data belongs to. Used as a key to match on load. */
	UPROPERTY(SaveGame)
	TSubclassOf<UNexusAbility> AbilityClass;

	/** Activation state at time of save. */
	UPROPERTY(SaveGame)
	ENexusAbilityActivationState ActivationState = ENexusAbilityActivationState::Idle;

	/** Whether the ability was enabled. */
	UPROPERTY(SaveGame)
	bool bIsEnabled = true;

	/** Whether the ability was on cooldown. */
	UPROPERTY(SaveGame)
	bool bIsOnCooldown = false;

	/** How much cooldown time had elapsed at save time. */
	UPROPERTY(SaveGame)
	float CooldownElapsed = 0.0f;

	/** Total cooldown duration at time of save (for expired-while-saved detection). */
	UPROPERTY(SaveGame)
	float CooldownTotalDuration = 0.0f;

	/**
	 * Generic container for subclass-specific tags that need to persist.
	 * For locomotion abilities this holds intent tags (e.g. Intent_Crouch, Intent_Run).
	 * Abilities with no custom state leave this empty.
	 */
	UPROPERTY(SaveGame)
	FGameplayTagContainer CustomTags;
};