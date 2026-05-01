// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusHealthComponent.h"

UNexusHealthComponent::UNexusHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!bDead && Health <= 0.0f)
	{
		Health = MaxHealth;
	}
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

float UNexusHealthComponent::GetResistance(FGameplayTag DamageType) const
{
	if (!DamageType.IsValid()) return 1.0f;
	if (const float* Found = Resistances.Find(DamageType))
	{
		return *Found;
	}
	return 1.0f;
}

float UNexusHealthComponent::GetBoneMultiplier(FName BoneName) const
{
	if (BoneName.IsNone()) return 1.0f;
	if (const float* Found = BoneDamageMultipliers.Find(BoneName))
	{
		return *Found;
	}
	return 1.0f;
}

void UNexusHealthComponent::ApplyDamage(const FNexusDamageContext& Context)
{
	if (!IsAlive()) return;

	const float BoneMul         = GetBoneMultiplier(Context.HitResult.BoneName);
	const float Resistance      = GetResistance(Context.DamageTypeTag);
	const float EffectiveDamage = Context.GetEffectiveDamage() * BoneMul * Resistance;
	if (EffectiveDamage <= 0.0f) return;

	OnDamageTaken.Broadcast(Context);

	const float Old = Health;
	Health          = FMath::Clamp(Health - EffectiveDamage, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(this, Old, Health, Context);

	if (Health <= 0.0f && !bDead)
	{
		bDead = true;
		OnDeath.Broadcast(Context);
	}
}

void UNexusHealthComponent::Heal(float Amount)
{
	if (Amount <= 0.0f || bDead) return;
	const float Old = Health;
	Health          = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	if (Health != Old)
	{
		OnHealthChanged.Broadcast(this, Old, Health, FNexusDamageContext{});
	}
}

void UNexusHealthComponent::Kill(const FNexusDamageContext& Context)
{
	if (bDead) return;
	const float Old = Health;
	Health          = 0.0f;
	bDead           = true;
	OnHealthChanged.Broadcast(this, Old, Health, Context);
	OnDeath.Broadcast(Context);
}