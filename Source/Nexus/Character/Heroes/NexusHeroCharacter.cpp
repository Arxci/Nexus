// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"

ANexusHeroCharacter::ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->InitCapsuleSize(45.0f, 90.0f);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));
	GetMesh()->SetCastShadow(false);
	GetMesh()->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);

	ViewRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ViewRoot"));
	ViewRoot->SetupAttachment(GetMesh(), FName("head"));
	ViewRoot->SetRelativeRotation(FRotator(-90.f, 0.f, 90.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(ViewRoot);
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 15.0f;

	ViewSource = CreateDefaultSubobject<USceneComponent>(TEXT("ViewSource"));
	ViewSource->SetupAttachment(SpringArm);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(ViewSource);
	FollowCamera->SetFirstPersonScale(0.6);
	FollowCamera->SetEnableFirstPersonFieldOfView(true);
	FollowCamera->SetEnableFirstPersonScale(true);
}

void ANexusHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0); 
		}
	}
}

void ANexusHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent = EIC;
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANexusHeroCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANexusHeroCharacter::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnRunInputStarted);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnRunInputCompleted);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnCrouchInputStarted);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnCrouchInputCompleted);
	}
}


//Utility
bool ANexusHeroCharacter::GetIsCrouched() const
{
	if (NexusCharacterMovement)
	{
		return NexusCharacterMovement->IsCrouching();
	}
	return false;	
}

bool ANexusHeroCharacter::GetIsGrounded() const
{
	if (NexusCharacterMovement)
	{
		return NexusCharacterMovement->IsGrounded();
	}
	return true;	
}

FVector ANexusHeroCharacter::GetRelativeAcceleration() const
{
	if (NexusCharacterMovement)
	{
		return NexusCharacterMovement->GetRelativeAcceleration();
	}
	return {0, 0, 0};	
}

FVector ANexusHeroCharacter::GetAcceleration() const
{
	if (NexusCharacterMovement)
	{
		return NexusCharacterMovement->GetAcceleration();
	}
	return {0, 0, 0};	
}

bool ANexusHeroCharacter::GetIsTurning() const
{
	return GetLookInput().X != 0;	
}


FVector2D ANexusHeroCharacter::GetLookInput() const
{
	if (EnhancedInputComponent)
	{
		const FEnhancedInputActionValueBinding LookActionBinding = EnhancedInputComponent->BindActionValue(LookAction);
		const FVector2D LookInput = LookActionBinding.GetValue().Get<FVector2D>();
		
		return LookInput;
	}
	
	return {0, 0};
}

FVector2D ANexusHeroCharacter::GetMoveInput() const
{
	if (EnhancedInputComponent)
	{
		const FEnhancedInputActionValueBinding MoveActionBinding = EnhancedInputComponent->BindActionValue(MoveAction);
		const FVector2D MoveInput = MoveActionBinding.GetValue().Get<FVector2D>();
		
		return MoveInput;
	}
	
	return {0, 0};
}


// Player Input
void ANexusHeroCharacter::OnCrouchInputStarted()
{
	if (!NexusAbilitySystemComponent) return;
	if (CrouchInputMode == EInputMode::Hold)
	{
		NexusAbilitySystemComponent->TryActivateAbilityByTag(NexusGameplayTags::Ability_Locomotion_Crouch);
		return;
	}
	HandleToggleAbilityInput(NexusGameplayTags::Ability_Locomotion_Crouch, NexusGameplayTags::Ability_Locomotion_Intent_UnCrouch);
}


void ANexusHeroCharacter::OnCrouchInputCompleted()
{
	if (CrouchInputMode != EInputMode::Hold) return;
	if (!NexusAbilitySystemComponent) return;

	NexusAbilitySystemComponent->TryDeactivateAbilityByTag(NexusGameplayTags::Ability_Locomotion_Crouch);
}

void ANexusHeroCharacter::OnRunInputStarted()
{
	if (!NexusAbilitySystemComponent) return;
	if (RunInputMode == EInputMode::Hold)
	{
		NexusAbilitySystemComponent->TryActivateAbilityByTag(NexusGameplayTags::Ability_Locomotion_Run);
		return;
	}
	HandleToggleAbilityInput(NexusGameplayTags::Ability_Locomotion_Run, NexusGameplayTags::Ability_Locomotion_Intent_Walk);
}

void ANexusHeroCharacter::OnRunInputCompleted()
{
	if (RunInputMode != EInputMode::Hold) return;
	if (!NexusAbilitySystemComponent) return;

	NexusAbilitySystemComponent->TryDeactivateAbilityByTag(NexusGameplayTags::Ability_Locomotion_Run);
}

void ANexusHeroCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller == nullptr) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection,   MovementVector.X);
}

void ANexusHeroCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANexusHeroCharacter::HandleToggleAbilityInput(FGameplayTag AbilityTag, FGameplayTag DeactivateIntentTag)
{
	if (NexusAbilitySystemComponent->HasTag(DeactivateIntentTag))
	{
		NexusAbilitySystemComponent->RemoveLooseGameplayTag(DeactivateIntentTag);
	}
	else if (NexusAbilitySystemComponent->IsAbilityActiveByTag(AbilityTag))
	{
		NexusAbilitySystemComponent->TryDeactivateAbilityByTag(AbilityTag);
	}
	else
	{
		NexusAbilitySystemComponent->TryActivateAbilityByTag(AbilityTag);
	}
}




