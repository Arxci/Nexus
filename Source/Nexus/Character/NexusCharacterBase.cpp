#include "NexusCharacterBase.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/NexusGameplayTags.h"

ANexusCharacterBase::ANexusCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNexusCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	NexusCharacterMovement = Cast<UNexusCharacterMovementComponent>(GetCharacterMovement());
	NexusAbilitySystemComponent = CreateDefaultSubobject<UNexusAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	NexusInventoryComponent     = CreateDefaultSubobject<UNexusInventoryComponent>(TEXT("InventoryComponent"));
	NexusEquipmentComponent     = CreateDefaultSubobject<UNexusEquipmentComponent>(TEXT("EquipmentComponent"));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
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

void ANexusCharacterBase::StopRun() const
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

//Utility
bool ANexusCharacterBase::GetIsCrouched() const
{
	if (NexusCharacterMovement)
	{
		return NexusCharacterMovement->IsCrouching();
	}
	return false;	
}

bool ANexusCharacterBase::GetIsRunning() const
{
	if (NexusCharacterMovement)
	{
		return NexusCharacterMovement->IsRunning();
	}
	return false;	
}

bool ANexusCharacterBase::GetIsGrounded() const
{
	if (NexusCharacterMovement)
	{
		return NexusCharacterMovement->IsGrounded();
	}
	return true;	
}

void ANexusCharacterBase::ActorPreSave_Implementation()
{
	SavedPawnPosition = GetActorLocation();
	SavedPawnRotation = GetActorRotation();
}

void ANexusCharacterBase::ActorLoaded_Implementation()
{
	GetWorldTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this]
	{
		if (GetIsCrouched() && NexusAbilitySystemComponent && !NexusAbilitySystemComponent->HasTag(NexusGameplayTags::Ability_Locomotion_Crouch))
		{
			UnCrouch();
		}

		if (GetIsRunning() && NexusAbilitySystemComponent && !NexusAbilitySystemComponent->HasTag(NexusGameplayTags::Ability_Locomotion_Run))
		{
			StopRun();
		}
	}));

	if (!SavedPawnPosition.IsNearlyZero())
	{
		SetActorLocationAndRotation(SavedPawnPosition, SavedPawnRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
	
	OnCharacterLoaded.Broadcast();
}


