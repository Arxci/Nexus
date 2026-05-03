#include "NexusEquippedActor.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/SkeletalMesh.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"

ANexusEquippedActor::ANexusEquippedActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANexusEquippedActor::InitializeFromInstance(UNexusItemInstance* Instance)
{
	SourceInstance = Instance;
	if (!Instance) return;

	const UNexusItemDefinition* DefinitionData = Instance->GetDefinition();
	if (!DefinitionData) return;

	if (const FNexusFragment_Equippable* Eq = DefinitionData->FindFragment<FNexusFragment_Equippable>())
	{
		if (USkeletalMesh* Loaded = Eq->WorldMesh.LoadSynchronous())
		{
			Mesh->SetSkeletalMesh(Loaded);
		}

		IdlePose       = Eq->Animations.IdlePose.LoadSynchronous();
		IdleLoop       = Eq->Animations.IdleLoop.LoadSynchronous();
		RunLoop        = Eq->Animations.RunLoop.LoadSynchronous();
		EquipMontage   = Eq->Animations.EquipMontage.LoadSynchronous();
		UnequipMontage = Eq->Animations.UnequipMontage.LoadSynchronous();
		InspectMontage = Eq->Animations.InspectMontage.LoadSynchronous();
	}

	K2_OnInitializedFromInstance();
}

FTransform ANexusEquippedActor::GetSocketTransform(const FName SocketName) const
{
	if (Mesh && Mesh->DoesSocketExist(SocketName))
	{
		return Mesh->GetSocketTransform(SocketName);
	}
	return GetActorTransform();
}

void ANexusEquippedActor::SetEquippedVisibility(bool bNewVisible)
{
	const bool bChanged = (bVisible != bNewVisible);
	bVisible = bNewVisible;

	if (bChanged)
	{
		// Hide the whole actor (including any BP-added child components like
		// FX, lights) rather than touching just the mesh — keeps weapon laser /
		// lights behaving sanely.
		SetActorHiddenInGame(!bNewVisible);
		K2_OnEquippedVisibilityChanged(bNewVisible);
	}

	// Always sync the anim-tick option (no early-return). On the first equip,
	// bVisible defaulted to true and the change-guard above would otherwise skip
	// this — leaving the skeletal mesh on USkeletalMeshComponent's default tick
	// mode, which only ticks the anim graph during montages. FP weapons need
	// idle sway / breath bob to update every frame regardless.
	if (Mesh)
	{
		Mesh->VisibilityBasedAnimTickOption = bNewVisible
			? EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones
			: EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	}
}

void ANexusEquippedActor::ApplyOwnerViewpointRendering()
{
	if (!Mesh) return;

	// "Locally controlled by a player" — true for the singleplayer player pawn,
	// false for AI (which is locally controlled but not player-controlled) and
	// false for any future remote players.
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	const bool bIsFirstPerson = OwnerPawn
		&& OwnerPawn->IsPlayerControlled()
		&& OwnerPawn->IsLocallyControlled();

	if (bIsFirstPerson)
	{
		Mesh->SetCastShadow(false);
		Mesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	}
	else
	{
		Mesh->SetCastShadow(true);
		Mesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::None;
	}

	K2_OnOwnerViewpointApplied(bIsFirstPerson);
}