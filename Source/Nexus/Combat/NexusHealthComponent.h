// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "EMSCompSaveInterface.h"
#include "NexusDamageReceiverInterface.h"
#include "NexusHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, UNexusHealthComponent*, Component,
	float, OldHealth, float, NewHealth, const FNexusDamageContext&, Context);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, const FNexusDamageContext&, Context);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, const FNexusDamageContext&, Context);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusHealthComponent : public UActorComponent, public IEMSCompSaveInterface
{
	GENERATED_BODY()

public:
	UNexusHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(const FNexusDamageContext& Context);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Kill(const FNexusDamageContext& Context);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const { return MaxHealth > 0.0f ? Health / MaxHealth : 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsAlive() const { return Health > 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetResistance(FGameplayTag DamageType) const;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetBoneMultiplier(FName BoneName) const;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDamageTaken OnDamageTaken;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "0.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health",
		meta = (Categories = "Damage.Type"))
	TMap<FGameplayTag, float> Resistances;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health|DamageZones")
	TMap<FName, float> BoneDamageMultipliers;

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Health")
	float Health = 100.0f;

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = "Health")
	bool bDead = false;
};