// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ANexusHeroCharacter::ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SprintAbilityTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Locomotion.Run"));
	
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
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::StopSprint);
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

void ANexusHeroCharacter::StartSprint()
{
	bWantsToSprint = true;

	if (NexusAbilitySystemComponent && SprintAbilityTag.IsValid())
	{
		NexusAbilitySystemComponent->TryActivateAbilityByTag(SprintAbilityTag);
	}
}

void ANexusHeroCharacter::StopSprint()
{
	bWantsToSprint = false;

	if (NexusAbilitySystemComponent && SprintAbilityTag.IsValid())
	{
		NexusAbilitySystemComponent->TryDeactivateAbilityByTag(SprintAbilityTag);
	}
}

void ANexusHeroCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		
		if (bWantsToSprint && NexusAbilitySystemComponent && SprintAbilityTag.IsValid())
		{
			NexusAbilitySystemComponent->TryActivateAbilityByTag(SprintAbilityTag);
		}
	}
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
