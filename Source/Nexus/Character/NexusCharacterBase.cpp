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

void ANexusCharacterBase::Run() const
{
	if (NexusCharacterMovement)
	{
		NexusCharacterMovement->StartRunning();
	}
}

void ANexusCharacterBase::StopRunning() const
{
	if (NexusCharacterMovement)
	{
		NexusCharacterMovement->StopRunning();
	}
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
	GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this]()
	{
		if (IsCrouched())
		{
			UnCrouch();
		}
	}));
	
	
	if (!SavedPawnPosition.IsNearlyZero())
	{
		SetActorLocationAndRotation(SavedPawnPosition, SavedPawnRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
	
	OnCharacterLoaded.Broadcast();
}


