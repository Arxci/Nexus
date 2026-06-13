#include "NexusHeroCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Character/NexusCharacterMovementComponent.h"
#include "Nexus/Player/NexusPlayerCameraManager.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Input/NexusInputManager.h"
#include "Nexus/Input/NexusInputHostComponent.h"
#include "Nexus/Input/NexusLocomotionInputComponent.h"
#include "Nexus/Interaction/NexusExamineComponent.h"

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

	ExamineComponent = CreateDefaultSubobject<UNexusExamineComponent>(TEXT("ExamineComponent"));

	// The whole input layer for this pawn: the host owns the binder + manager registration;
	// the locomotion component subscribes to Move / Look. The hero binds nothing.
	InputHostComponent = CreateDefaultSubobject<UNexusInputHostComponent>(TEXT("InputHostComponent"));
	LocomotionInputComponent = CreateDefaultSubobject<UNexusLocomotionInputComponent>(TEXT("LocomotionInputComponent"));
}

void ANexusHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Input mapping contexts are no longer added here — UNexusInputManager applies each
	// active context's IMC when the host registers this pawn and pushes its default contexts.

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

// Input — re-sourced from the manager's per-verb cache (see header note).
FVector2D ANexusHeroCharacter::GetLookInput() const
{
	const UNexusInputManager* Manager = UNexusInputManager::GetForPawn(this);
	return Manager ? Manager->GetCachedAxis(NexusGameplayTags::InputTag_Look) : FVector2D::ZeroVector;
}

FVector2D ANexusHeroCharacter::GetMoveInput() const
{
	const UNexusInputManager* Manager = UNexusInputManager::GetForPawn(this);
	return Manager ? Manager->GetCachedAxis(NexusGameplayTags::InputTag_Move) : FVector2D::ZeroVector;
}

bool ANexusHeroCharacter::GetRunInput() const
{
	const UNexusInputManager* Manager = UNexusInputManager::GetForPawn(this);
	return Manager ? Manager->GetCachedBool(NexusGameplayTags::InputTag_Run) : false;
}

bool ANexusHeroCharacter::GetCrouchInput() const
{
	const UNexusInputManager* Manager = UNexusInputManager::GetForPawn(this);
	return Manager ? Manager->GetCachedBool(NexusGameplayTags::InputTag_Crouch) : false;
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

	// In-progress holds don't persist: end any hold-style ability (Run/Crouch/Aim) restored
	// active that the player isn't holding now. The manager owns the per-verb mode, so this is
	// one generic call instead of the old per-EInputMode branches.
	if (UNexusInputManager* Manager = UNexusInputManager::GetForPawn(this))
	{
		Manager->ReconcileHoldVerbsAfterLoad();
	}
}
