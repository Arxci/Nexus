// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusCharacterBase.h"
#include "NexusCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ANexusCharacterBase::ANexusCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNexusCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	
	NexusAbilitySystemComponent = CreateDefaultSubobject<UNexusAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
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
		NexusAbilitySystemComponent->InitAbilityActorInfo(this);
	}
}
