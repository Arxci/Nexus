// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "NexusCharacterMovementComponent.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/NexusGameplayTags.h"

ANexusCharacterBase::ANexusCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNexusCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	NexusCharacterMovement = Cast<UNexusCharacterMovementComponent>(GetCharacterMovement());
	NexusAbilitySystemComponent = CreateDefaultSubobject<UNexusAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

UNexusCharacterMovementComponent* ANexusCharacterBase::GetNexusCharacterMovement() const
{
	return NexusCharacterMovement;
}

UNexusAbilitySystemComponent* ANexusCharacterBase::GetNexusAbilitySystemComponent() const
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

void ANexusCharacterBase::UnPossessed()
{
	if (NexusAbilitySystemComponent)
	{
		NexusAbilitySystemComponent->InitAbilityActorInfo(nullptr);
	}
	Super::UnPossessed();
}

void ANexusCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (NexusCharacterMovement)
	{
		NexusCharacterMovement->OnRunStart.AddDynamic(this, &ANexusCharacterBase::OnStartRun);
		NexusCharacterMovement->OnRunEnd.AddDynamic(this, &ANexusCharacterBase::OnEndRun);
	}
}

void ANexusCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (NexusCharacterMovement)
	{
		NexusCharacterMovement->OnRunStart.RemoveDynamic(this, &ANexusCharacterBase::OnStartRun);
		NexusCharacterMovement->OnRunEnd.RemoveDynamic(this, &ANexusCharacterBase::OnEndRun);
	}

	Super::EndPlay(EndPlayReason);
}

void ANexusCharacterBase::StartRunning()
{
	if (NexusCharacterMovement)
	{
		NexusCharacterMovement->StartRunning();
	}
}

void ANexusCharacterBase::StopRunning()
{
	if (NexusCharacterMovement)
	{
		NexusCharacterMovement->StopRunning();
	}
}

void ANexusCharacterBase::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void ANexusCharacterBase::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
}

void ANexusCharacterBase::OnStartRun()
{

}

void ANexusCharacterBase::OnEndRun()
{

}

void ANexusCharacterBase::ActorPreSave_Implementation()
{
	SavedPawnPosition = GetActorLocation();
	SavedPawnRotation = GetActorRotation();
}

void ANexusCharacterBase::ActorLoaded_Implementation()
{
	if (!SavedPawnPosition.IsNearlyZero())
	{
		SetActorLocationAndRotation(SavedPawnPosition, SavedPawnRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
	
	OnGameLoaded.Broadcast();
	
}
