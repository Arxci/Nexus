// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NexusAbilitySystemComponent.generated.h"

class ACharacter;
class AController;
class UActorComponent;
class UNexusAbility;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusAbilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNexusAbilitySystemComponent();

	void InitAbilityActorInfo(ACharacter* InCharacter);

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	ACharacter* GetCharacter() const { return CachedCharacter; }

	UFUNCTION(BlueprintCallable, Category = "Ability System")
	AController* GetController() const { return CachedController; }

protected:
	UFUNCTION(BlueprintCallable, Category="Ability System")
	UNexusAbility* GiveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryActivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToActivate);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryDeactivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToDeactivate);

	UPROPERTY(Transient)
	ACharacter* CachedCharacter = nullptr;

	UPROPERTY(Transient)
	AController* CachedController = nullptr;

	UPROPERTY()
	TMap<TSubclassOf<UNexusAbility>, UNexusAbility*> GrantedAbilities;
};
