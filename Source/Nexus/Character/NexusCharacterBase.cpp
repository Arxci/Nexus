// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusCharacterBase.h"
#include "NexusCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Nexus/AbilitySystem/NexusAbility.h"

ANexusCharacterBase::ANexusCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNexusCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);

	NexusCharacterMovement = Cast<UNexusCharacterMovementComponent>(GetCharacterMovement());
	NexusAbilitySystemComponent = CreateDefaultSubobject<UNexusAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UNexusCharacterMovementComponent* ANexusCharacterBase::GetNexusCharacterMovement() const
{
	return NexusCharacterMovement;
}

UNexusAbilitySystemComponent* ANexusCharacterBase::GetNexusAbilityComponent() const
{
	return NexusAbilitySystemComponent;
}

void ANexusCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NexusAbilitySystemComponent)
	{
		NexusAbilitySystemComponent->InitAbilityActorInfo(NewController);

		for (const TSubclassOf<UNexusAbility>& AbilityClass : DefaultAbilities)
		{
			if (AbilityClass)
			{
				NexusAbilitySystemComponent->GiveAbility(AbilityClass);
			}
		}
	}
}
