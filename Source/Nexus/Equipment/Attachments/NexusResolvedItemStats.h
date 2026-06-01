#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "NexusResolvedItemStats.generated.h"


/**
 * Runtime resolution of (Stat.* tag) -> (final float value), produced by walking
 * the attachment tree from the equipped item's base values. Base values are
 * contributed by each FNexusItemFragment via SeedStatTags — the assembly itself
 * is fragment-agnostic. Attachment modifiers are layered as
 * (base + sum(Add)) * product(Mul), then persistent upgrade tags are added as a
 * final tier, then the value is clamped to its authored [min,max].
 *
 * Named "FResolvedItemStats" (not WeaponStats) so the type name reflects its
 * actual scope: any modular equippable can have a resolved stat block, not just
 * weapons. Stat keys are still data-driven (Stat.Weapon.*, Stat.Flashlight.*,
 * etc.) — the struct is just the (key -> value) container.
 *
 * Lives in its own lightweight header so consumers that only need the resolved
 * block (the gunsmith catalog's preview, the equipped actor's accessor) don't
 * have to pull in the whole UNexusAssemblyComponent.
 */
USTRUCT(BlueprintType, DisplayName = "Resolved Item Stats")
struct NEXUS_API FResolvedItemStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, float> Values;

	float Get(const FGameplayTag StatTag, const float Default = 0.0f) const
	{
		const float* Found = Values.Find(StatTag);
		return Found ? *Found : Default;
	}
};
