#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/HitResult.h"
#include "NexusDamageContext.generated.h"

/**
 * Immutable per-hit packet routed from a damage source (weapon ability, AOE,
 * environment) to an INexusDamageReceiver. Single struct keeps the damage
 * pipeline boring on purpose — every damage source produces this, every
 * receiver consumes this.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusDamageContext
{
	GENERATED_BODY()

	/** Pawn / AI whose action caused the hit. */
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<AActor> Instigator;

	/** Direct cause — weapon actor, projectile, hazard volume. */
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	TWeakObjectPtr<AActor> Causer;

	UPROPERTY(BlueprintReadWrite, Category = "Damage", meta = (Categories = "Damage.Type"))
	FGameplayTag DamageTypeTag;

	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	float BaseDamage = 0.0f;

	/** Pre-resistance multiplier (falloff, headshot bonus, status). */
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	float Multiplier = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	FHitResult HitResult;

	/** Direction the impulse is applied along (normalized). */
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	FVector ImpulseDirection = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	float ImpulseMagnitude = 0.0f;

	/** Free-form tags receivers can branch on (Headshot, Stagger, Critical, ...). */
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	FGameplayTagContainer ContextTags;

	float GetEffectiveDamage() const { return FMath::Max(0.0f, BaseDamage * Multiplier); }
};