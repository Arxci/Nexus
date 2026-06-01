#include "NexusHeroCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/Player/NexusPlayerCameraManager.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/Character/Abilities/NexusAbility_Interaction.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/Interaction/NexusInteractableInterface.h"

ANexusHeroCharacter::ANexusHeroCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->InitCapsuleSize(45.0f, 90.0f);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));
	GetMesh()->SetCastShadow(false);
	GetMesh()->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	
	// View origin rides the capsule at eye height — it is NOT welded to the head bone.
	// Look (pitch/yaw) comes from control rotation via the spring arm; the head bone's
	// motion is layered back onto the view as a camera-only offset in
	// ANexusPlayerCameraManager::UpdateViewTarget. 70 is a rough eye height for the
	// 90cm half-height capsule — tune it (or override in BP) so the neutral view sits
	// at the eyes.
	ViewRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ViewRoot"));
	ViewRoot->SetupAttachment(GetCapsuleComponent());
	ViewRoot->SetRelativeLocation(FVector(0.f, 0.f, 70.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(ViewRoot);
	SpringArm->TargetArmLength = 0.0f;
	// Drive the camera straight from control rotation and keep it crisp. Any weight or
	// lag the view model needs is authored as weapon sway in the Anim BP, not on the
	// camera itself (lagging the camera lags your actual aim).
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bDoCollisionTest = false;

	ViewSource = CreateDefaultSubobject<USceneComponent>(TEXT("ViewSource"));
	ViewSource->SetupAttachment(SpringArm);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(ViewSource);
	FollowCamera->SetFirstPersonScale(0.6);
	FollowCamera->SetEnableFirstPersonFieldOfView(true);
	FollowCamera->SetEnableFirstPersonScale(true);

	// Arms hang off a sibling of the camera (both under the spring arm) so they inherit
	// only the shared control rotation. The camera-only head-bone offset moves the view
	// without dragging the arms along with it.
	ViewModelRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ViewModelRoot"));
	ViewModelRoot->SetupAttachment(SpringArm);

	FirstPersonArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonArms"));
	FirstPersonArms->SetupAttachment(ViewModelRoot);
	FirstPersonArms->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FirstPersonArms->SetCollisionProfileName(FName("NoCollision"));
	FirstPersonArms->SetCastShadow(false);
	FirstPersonArms->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	FirstPersonArms->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	// Re-tune in editor: the parent frame changed from head-bone space to
	// control-rotation space, so the old weld (-162.575 Z, -90 roll) no longer maps 1:1.
	FirstPersonArms->SetRelativeLocation(FVector(0.f, 0.f, -162.575263f));
	FirstPersonArms->SetRelativeRotation(FRotator(0.f, 0.f, -90.0f));
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

	if (NexusEquipmentComponent)
	{
		NexusEquipmentComponent->OnSlotActivated.AddDynamic(this, &ANexusHeroCharacter::HandleActiveSlotChanged);
		NexusEquipmentComponent->OnSlotDeactivated.AddDynamic(this, &ANexusHeroCharacter::HandleActiveSlotChanged);
	}
	UpdateArmsVisibility();
}

void ANexusHeroCharacter::HandleActiveSlotChanged(FGameplayTag /*SlotTag*/, UNexusItemInstance* /*Instance*/)
{
	UpdateArmsVisibility();
}

void ANexusHeroCharacter::UpdateArmsVisibility()
{
	if (!FirstPersonArms) return;
	const bool bItemInHand = NexusEquipmentComponent && NexusEquipmentComponent->GetActiveSlot().IsValid();
	FirstPersonArms->SetVisibility(bItemInHand);
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
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnFireInputCompleted);
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnReloadInputStarted);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnAimInputStarted);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnAimInputCompleted);
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Started, this, &ANexusHeroCharacter::OnMeleeInputStarted);
		// Hold trigger per slot action: Canceled (released before the hold threshold) =
		// tap = Normal draw; Triggered (held past the threshold) = Ceremony draw.
		EnhancedInputComponent->BindAction(SlotPrimaryAction, ETriggerEvent::Canceled, this, &ANexusHeroCharacter::OnSlotPrimaryTap);
		EnhancedInputComponent->BindAction(SlotPrimaryAction, ETriggerEvent::Triggered, this, &ANexusHeroCharacter::OnSlotPrimaryHold);
		EnhancedInputComponent->BindAction(SlotSecondaryAction, ETriggerEvent::Canceled, this, &ANexusHeroCharacter::OnSlotSecondaryTap);
		EnhancedInputComponent->BindAction(SlotSecondaryAction, ETriggerEvent::Triggered, this, &ANexusHeroCharacter::OnSlotSecondaryHold);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started,   this, &ANexusHeroCharacter::OnInteractInputStarted);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ANexusHeroCharacter::OnInteractInputCompleted);

		if (LookAction)   EIC->BindActionValue(LookAction);
		if (MoveAction)   EIC->BindActionValue(MoveAction);
		if (RunAction)    EIC->BindActionValue(RunAction);
		if (CrouchAction) EIC->BindActionValue(CrouchAction);
		if (FireAction)   EIC->BindActionValue(FireAction);
		if (AimAction)    EIC->BindActionValue(AimAction);
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

UNexusInteractableComponent* ANexusHeroCharacter::GetFocusedInteractable() const
{
	if (!NexusAbilitySystemComponent) return nullptr;
	const UNexusAbility_Interaction* InteractAbility = Cast<UNexusAbility_Interaction>(
		NexusAbilitySystemComponent->FindAbilityByClass(UNexusAbility_Interaction::StaticClass()));
	return InteractAbility ? InteractAbility->GetFocusedInteractable() : nullptr;
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
	return EnhancedInputComponent ? EnhancedInputComponent->GetBoundActionValue(LookAction).Get<FVector2D>() : FVector2D::ZeroVector;
}

FVector2D ANexusHeroCharacter::GetMoveInput() const
{
	return EnhancedInputComponent ? EnhancedInputComponent->GetBoundActionValue(MoveAction).Get<FVector2D>() : FVector2D::ZeroVector;
}

bool ANexusHeroCharacter::GetRunInput() const
{
	return EnhancedInputComponent ? EnhancedInputComponent->GetBoundActionValue(RunAction).Get<bool>() : false;
}

bool ANexusHeroCharacter::GetCrouchInput() const
{
	return EnhancedInputComponent ? EnhancedInputComponent->GetBoundActionValue(CrouchAction).Get<bool>() : false;
}

// Player Input
void ANexusHeroCharacter::OnInteractInputStarted()
{
	UNexusInteractableComponent* Focused = GetFocusedInteractable();
	if (!Focused) return;
	ActiveInteractable = Focused;
	INexusInteractableInterface::Execute_TryStartInteraction(Focused, this);
}

void ANexusHeroCharacter::OnInteractInputCompleted()
{
	// Release-before-completion is a cancel. Target the interactable we
	// originally started on, not the currently focused one — the player may
	// have looked away mid-hold, and that other interactable shouldn't get a
	// Stop call it never received a matching Start for. If the hold finished
	// and our cached interactable already auto-completed, its CurrentInteractor
	// was cleared, so TryStopInteraction will no-op — safe to fire unconditionally.
	UNexusInteractableComponent* Started = ActiveInteractable.Get();
	ActiveInteractable = nullptr;
	if (!Started) return;
	INexusInteractableInterface::Execute_TryStopInteraction(Started, this);
}

void ANexusHeroCharacter::OnFireInputStarted()
{
	if (!NexusAbilitySystemComponent) return;
	NexusAbilitySystemComponent->TryActivateAbilityByTag(NexusGameplayTags::Ability_Weapon_Fire);
}

void ANexusHeroCharacter::OnFireInputCompleted()
{
	// Releasing the trigger ends a held full-auto; semi / shotgun already ended after their
	// shot (no-op), and a burst ignores the release and finishes its count.
	if (!NexusAbilitySystemComponent) return;
	NexusAbilitySystemComponent->TryDeactivateAbilityByTag(NexusGameplayTags::Ability_Weapon_Fire);
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

void ANexusHeroCharacter::OnMeleeInputStarted()
{
	// One press = a light swing (knife primary, or a ranged weapon's contextual bash). The
	// ability supports a heavy variant via SetHeavyNext for a designer-added heavy binding.
	if (!NexusAbilitySystemComponent) return;
	NexusAbilitySystemComponent->TryActivateAbilityByTag(NexusGameplayTags::Ability_Weapon_Melee);
}

void ANexusHeroCharacter::OnSlotPrimaryTap()    { HandleSlotInput(NexusGameplayTags::Equipment_Slot_Primary,   EUnholsterStyle::Normal); }
void ANexusHeroCharacter::OnSlotPrimaryHold()   { HandleSlotInput(NexusGameplayTags::Equipment_Slot_Primary,   EUnholsterStyle::Ceremony); }
void ANexusHeroCharacter::OnSlotSecondaryTap()  { HandleSlotInput(NexusGameplayTags::Equipment_Slot_Secondary, EUnholsterStyle::Normal); }
void ANexusHeroCharacter::OnSlotSecondaryHold() { HandleSlotInput(NexusGameplayTags::Equipment_Slot_Secondary, EUnholsterStyle::Ceremony); }

void ANexusHeroCharacter::HandleSlotInput(FGameplayTag SlotTag, EUnholsterStyle Style)
{
	if (!NexusEquipmentComponent) return;

	// Pressing the already-active slot routes through RequestActivateSlot's toggle to
	// empty hands; otherwise this draws SlotTag with the requested style.
	NexusEquipmentComponent->RequestActivateSlot(SlotTag, Style);
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
