// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusCharacterBase.h"
#include "NexusCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/NexusGameplayTags.h"

ANexusCharacterBase::ANexusCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNexusCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);

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

	// Mirror CMC run state onto the ASC via loose tags. This decouples the
	// "is actually running" state from the Run ability's lifecycle, so the
	// Character_State_Locomotion_Run tag reflects the CMC's truth rather
	// than whether the ability happens to be Active.
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

	// The CMC has finished resizing the capsule to crouch height. The tag
	// is owned by the character (not the Crouch ability) so it reflects the
	// capsule's real state — if UnCrouch fails because of overhead geometry,
	// this tag stays applied and correctly blocks Run from activating.
	if (NexusAbilitySystemComponent)
	{
		NexusAbilitySystemComponent->AddLooseGameplayTag(NexusGameplayTags::Character_State_Locomotion_Crouch);
	}
}

void ANexusCharacterBase::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);

	if (NexusAbilitySystemComponent)
	{
		NexusAbilitySystemComponent->RemoveLooseGameplayTag(NexusGameplayTags::Character_State_Locomotion_Crouch);
	}
}

void ANexusCharacterBase::OnStartRun()
{
	if (NexusAbilitySystemComponent)
	{
		NexusAbilitySystemComponent->AddLooseGameplayTag(NexusGameplayTags::Character_State_Locomotion_Run);
	}
}

void ANexusCharacterBase::OnEndRun()
{
	if (NexusAbilitySystemComponent)
	{
		NexusAbilitySystemComponent->RemoveLooseGameplayTag(NexusGameplayTags::Character_State_Locomotion_Run);
	}
}

void ANexusCharacterBase::ComponentsToSave_Implementation(TArray<UActorComponent*>& Components)
{
	if (NexusAbilitySystemComponent)
	{
		Components.Add(NexusAbilitySystemComponent);
	}
}