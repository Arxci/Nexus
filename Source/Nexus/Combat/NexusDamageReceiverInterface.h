#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "NexusDamageContext.h"
#include "NexusDamageReceiverInterface.generated.h"

UINTERFACE(BlueprintType)
class NEXUS_API UNexusDamageReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implemented by anything that can be damaged: enemies, breakables, the player,
 * destructible cover. Damage sources call Execute_ReceiveDamage on the hit
 * actor; the receiver decides how (or whether) to apply it.
 *
 * Implementing on a component is supported as long as the actor forwards the
 * call (UNexusHealthComponent does this from its owner's interface impl).
 */
class NEXUS_API INexusDamageReceiver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Damage")
	void ReceiveDamage(const FNexusDamageContext& Context);
	virtual void ReceiveDamage_Implementation(const FNexusDamageContext& Context) {}

	/** Resistance multiplier (0..1+) applied to damage of the given type. 0 = immune, 1 = normal. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Damage")
	float GetResistanceForDamageType(FGameplayTag DamageType) const;
	virtual float GetResistanceForDamageType_Implementation(FGameplayTag DamageType) const { return 1.0f; }
};