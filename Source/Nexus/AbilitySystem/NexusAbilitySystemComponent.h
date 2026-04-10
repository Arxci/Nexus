// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NexusAbilitySystemComponent.generated.h"

class ACharacter;
class AController;
class UNexusAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStateChanged, UNexusAbility*, Ability);

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

	UFUNCTION(BlueprintCallable, Category="Ability System")
	UNexusAbility* GiveAbility(TSubclassOf<UNexusAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryActivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToActivate);

	UFUNCTION(BlueprintCallable, Category="Ability System")
	bool TryDeactivateAbilityByClass(TSubclassOf<UNexusAbility> InAbilityToDeactivate);

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityActivated;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityStateChanged OnAbilityDeactivated;

protected:


	UPROPERTY(Transient)
	ACharacter* CachedCharacter = nullptr;

	UPROPERTY(Transient)
	AController* CachedController = nullptr;

	UPROPERTY()
	TMap<TSubclassOf<UNexusAbility>, UNexusAbility*> GrantedAbilities;
};
