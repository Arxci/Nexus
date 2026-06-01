#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "EMSCompSaveInterface.h"

#include "NexusStaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStaminaChanged, UNexusStaminaComponent*, Component,
	float, OldStamina, float, NewStamina);


/**
 * A dedicated stamina pool, deliberately shaped like UNexusHealthComponent so it saves,
 * regenerates and broadcasts the same way a HUD already understands. Melee swings drain
 * it (see UNexusAbility_WeaponMelee); it regenerates after a short delay. Opt-in like
 * health — a wielder without this component is treated as having infinite stamina, so
 * NPCs need not carry it.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusStaminaComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusStaminaComponent();

	/** Spend Amount if available; returns false (and spends nothing) when there isn't enough. */
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	bool ConsumeStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void RestoreStamina(float Amount);

	UFUNCTION(BlueprintPure, Category = "Stamina")
	bool HasStamina(float Amount) const { return Stamina >= Amount; }

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetStamina() const { return Stamina; }

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetMaxStamina() const { return MaxStamina; }

	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetStaminaPercent() const { return MaxStamina > 0.0f ? Stamina / MaxStamina : 0.0f; }

	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void SetStamina(float NewStamina);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0.0"))
	float MaxStamina = 100.0f;

	/** Stamina restored per second once regen resumes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0.0"))
	float RegenPerSecond = 25.0f;

	/** Seconds after spending stamina before regeneration resumes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0.0"))
	float RegenDelay = 1.0f;

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Stamina")
	float Stamina = 100.0f;

private:
	float TimeSinceSpend = 0.0f;
};
