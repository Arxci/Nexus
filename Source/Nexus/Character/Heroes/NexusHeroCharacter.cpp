#include "NexusHeroCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/Player/NexusPlayerCameraManager.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"

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
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnRunInputStarted);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnRunInputCompleted);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnCrouchInputStarted);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnCrouchInputCompleted);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnFireInputStarted);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnReloadInputStarted);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnAimInputStarted);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnAimInputCompleted);
		EnhancedInputComponent->BindAction(SlotPrimaryAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnSlotPrimaryInputStarted);
		EnhancedInputComponent->BindAction(SlotSecondaryAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnSlotSecondaryInputStarted);
		
		if (LookAction)   LookBinding   = &EIC->BindActionValue(LookAction);
		if (MoveAction)   MoveBinding   = &EIC->BindActionValue(MoveAction);
		if (RunAction)    RunBinding    = &EIC->BindActionValue(RunAction);
		if (CrouchAction) CrouchBinding = &EIC->BindActionValue(CrouchAction);
		if (FireAction)   FireBinding =   &EIC->BindActionValue(FireAction);
		if (AimAction)    AimBinding  =   &EIC->BindActionValue(AimAction);
	}
}


//Utility
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
	return LookBinding ? LookBinding->GetValue().Get<FVector2D>() : FVector2D::ZeroVector;
}

FVector2D ANexusHeroCharacter::GetMoveInput() const
{
	return MoveBinding ? MoveBinding->GetValue().Get<FVector2D>() : FVector2D::ZeroVector;
}

bool ANexusHeroCharacter::GetRunInput() const
{
	return RunBinding ? RunBinding->GetValue().Get<bool>() : false;
}

bool ANexusHeroCharacter::GetCrouchInput() const
{
	return CrouchBinding ? CrouchBinding->GetValue().Get<bool>() : false;
}


// Player Input
void ANexusHeroCharacter::OnFireInputStarted()
{
	if (!NexusAbilitySystemComponent) return;
	NexusAbilitySystemComponent->TryActivateAbilityByTag(NexusGameplayTags::Ability_Weapon_Fire);
}

void ANexusHeroCharacter::OnReloadInputStarted()
{
	if (!NexusAbilitySystemComponent) return;
	NexusAbilitySystemComponent->TryActivateAbilityByTag(NexusGameplayTags::Ability_Weapon_Reload);
}

void ANexusHeroCharacter::OnAimInputStarted()
{
	if (!NexusAbilitySystemComponent) return;
	if (AimInputMode == EInputMode::Hold)
	{
		NexusAbilitySystemComponent->TryActivateAbilityByTag(NexusGameplayTags::Ability_Weapon_Aim);
		return;
	}
	HandleToggleAbilityInput(NexusGameplayTags::Ability_Weapon_Aim, NexusGameplayTags::Ability_Weapon_Intent_Unaim);
}

void ANexusHeroCharacter::OnAimInputCompleted()
{
	if (AimInputMode != EInputMode::Hold) return;
	if (!NexusAbilitySystemComponent) return;
	NexusAbilitySystemComponent->TryDeactivateAbilityByTag(NexusGameplayTags::Ability_Weapon_Aim);
}

void ANexusHeroCharacter::OnSlotPrimaryInputStarted()
{
	HandleSlotInput(NexusGameplayTags::Equipment_Slot_Primary);
}

void ANexusHeroCharacter::OnSlotSecondaryInputStarted()
{
	HandleSlotInput(NexusGameplayTags::Equipment_Slot_Secondary);
}

void ANexusHeroCharacter::HandleSlotInput(FGameplayTag SlotTag)
{
	if (!NexusEquipmentComponent) return;
	if (NexusEquipmentComponent->IsSwapping()) return; // ignore mash during draw/holster

	// Snapshot the active slot BEFORE TryEquip — equipping into an empty setup
	// auto-activates the new slot, so reading GetActiveSlot() after the fact
	// would always make the toggle check below see "already active" and
	// immediately holster what we just drew.
	const FGameplayTag PreviousActive = NexusEquipmentComponent->GetActiveSlot();

	NexusEquipmentComponent->TryEquipFirstCompatibleForSlot(SlotTag);

	// RE-style toggle: tap an already-active slot key to holster.
	if (PreviousActive.MatchesTagExact(SlotTag))
	{
		NexusEquipmentComponent->SetActiveSlot(FGameplayTag());
	}
	else
	{
		// Either nothing was active, a different slot was active, or this slot
		// was equipped-but-inactive. Activate it. (Idempotent if EquipInstance
		// just auto-activated it — SetActiveSlot early-outs on no-op.)
		NexusEquipmentComponent->SetActiveSlot(SlotTag);
	}
}

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
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANexusHeroCharacter::HandleToggleAbilityInput(const FGameplayTag AbilityTag, const FGameplayTag DeactivateIntentTag)
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


// Save/restore
void ANexusHeroCharacter::ActorPreLoad_Implementation()
{
	Super::ActorPreLoad_Implementation();

	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		
		if (ANexusPlayerCameraManager* CManager = Cast<ANexusPlayerCameraManager>(PC->PlayerCameraManager))
		{
			CManager->StartCameraFade(0, 1, 0.01f, FLinearColor::Black, true, true);
		}
	}
}


void ANexusHeroCharacter::ActorLoaded_Implementation()
{
	Super::ActorLoaded_Implementation();

	if (const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		
		if (ANexusPlayerCameraManager* CManager = Cast<ANexusPlayerCameraManager>(PC->PlayerCameraManager))
		{
			CManager->StartCameraFadeWithDelay(1, 0, 0.5f, 1.0f, FLinearColor::Black, true, true);
		}
	}

	if (!NexusAbilitySystemComponent) return;

	//Flush out intent for hold input modes
	if (RunInputMode == EInputMode::Hold && !GetRunInput()) NexusAbilitySystemComponent->ForceEndAbilityByTag(
			NexusGameplayTags::Ability_Locomotion_Run);

	if (CrouchInputMode == EInputMode::Hold && !GetCrouchInput()) NexusAbilitySystemComponent->ForceEndAbilityByTag(
			NexusGameplayTags::Ability_Locomotion_Crouch);
}
