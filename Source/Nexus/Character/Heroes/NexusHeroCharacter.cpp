// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Nexus/NexusGameplayTags.h"

ANexusHeroCharacter::ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	ViewRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ViewRoot"));
	ViewRoot->SetupAttachment(GetRootComponent());
	ViewRoot->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(ViewRoot);
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 25.0f;

	ViewSource = CreateDefaultSubobject<USceneComponent>(TEXT("ViewSource"));
	ViewSource->SetupAttachment(SpringArm);
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
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANexusHeroCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANexusHeroCharacter::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnRunInputStarted);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnRunInputCompleted);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnCrouchInputStarted);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnCrouchInputCompleted);
	}
}

void ANexusHeroCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	if (ViewSource)
	{
		OutResult.Location = ViewSource->GetComponentLocation();
		OutResult.Rotation = ViewSource->GetComponentRotation();
	}
	else
	{
		Super::CalcCamera(DeltaTime, OutResult);
	}
}

// Player Input

void ANexusHeroCharacter::OnCrouchInputStarted()
{
	if (!NexusAbilitySystemComponent) return;
	
	if (CrouchInputMode == ECrouchInputMode::Hold)
	{
		NexusAbilitySystemComponent->AbilityInputPressed(NexusGameplayTags::InputTag_Crouch);
	}
	else 
	{

		if (NexusAbilitySystemComponent->IsAbilityActiveByTag(
				NexusGameplayTags::Ability_Locomotion_Crouch))
		{
			NexusAbilitySystemComponent->AbilityInputReleased(NexusGameplayTags::InputTag_Crouch);
		}
		else
		{
			NexusAbilitySystemComponent->AbilityInputPressed(NexusGameplayTags::InputTag_Crouch);
		}
	}
}

void ANexusHeroCharacter::OnCrouchInputCompleted()
{
	if (CrouchInputMode != ECrouchInputMode::Hold) return;
	if (!NexusAbilitySystemComponent) return;

	NexusAbilitySystemComponent->AbilityInputReleased(NexusGameplayTags::InputTag_Crouch);
}

void ANexusHeroCharacter::OnRunInputStarted()
{
	if (!NexusAbilitySystemComponent) return;

	if (RunInputMode == ERunInputMode::Hold)
	{
		NexusAbilitySystemComponent->AbilityInputPressed(NexusGameplayTags::InputTag_Run);
	}
	else 
	{

		if (NexusAbilitySystemComponent->IsAbilityActiveByTag(
				NexusGameplayTags::Ability_Locomotion_Run))
		{
			NexusAbilitySystemComponent->AbilityInputReleased(NexusGameplayTags::InputTag_Run);
		}
		else
		{
			NexusAbilitySystemComponent->AbilityInputPressed(NexusGameplayTags::InputTag_Run);
		}
	}
}

void ANexusHeroCharacter::OnRunInputCompleted()
{
	if (RunInputMode != ERunInputMode::Hold) return;
	if (!NexusAbilitySystemComponent) return;

	NexusAbilitySystemComponent->AbilityInputReleased(NexusGameplayTags::InputTag_Run);
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
