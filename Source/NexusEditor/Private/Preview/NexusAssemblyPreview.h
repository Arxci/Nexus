#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UNexusItemDefinition;
class UNexusAttachmentDefinition;

/** One stat resolved through the full assembly fold, with each intermediate step exposed. */
struct FNexusResolvedStat
{
	FGameplayTag StatTag;
	float Base = 0.0f;
	float AfterAttachments = 0.0f;
	float AfterUpgrade = 0.0f;
	float Final = 0.0f;
	bool bClamped = false;
};

/**
 * Author-time mirror of UNexusAssemblyComponent's effective-stat resolution, so a designer
 * can see what a weapon + chosen attachments + upgrade tier actually produces before play.
 *
 * The fold matches the runtime contract documented on FNexusStatClamp:
 *     base (item fragments' SeedStatTags)
 *       -> (base + ΣAdd) × ΠMul     (attachment Modifiers)
 *       -> + upgrade-tier delta      (weapon UpgradeTracks, cumulative Value)
 *       -> clamp to [Min, Max]       (fragments' SeedStatClamps; Max <= Min = unbounded)
 *
 * It reuses the game's own SeedStatTags / SeedStatClamps, so it can't drift from runtime.
 */
struct FNexusAssemblyPreview
{
	static TArray<FNexusResolvedStat> Resolve(
		const UNexusItemDefinition* Weapon,
		const TArray<UNexusAttachmentDefinition*>& Attachments,
		int32 UpgradeTier);

	/** Highest tier offered by any of the weapon's upgrade tracks (0 = no upgrades). */
	static int32 GetMaxUpgradeTier(const UNexusItemDefinition* Weapon);
};
