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
		if (USkeletalMesh* Loaded = Eq->WorldMesh.Get())
		{
			Mesh->SetSkeletalMesh(Loaded);
		}
		else
		{
			ensureMsgf(Eq->WorldMesh.IsNull(),
				TEXT("WorldMesh not resident for %s — Equipped bundle was not awaited before InitializeFromInstance"),
				*DefinitionData->GetName());
		}

		IdlePose       = Eq->Animations.IdlePose.Get();
		IdleLoop       = Eq->Animations.IdleLoop.Get();
		RunLoop        = Eq->Animations.RunLoop.Get();
		EquipMontage   = Eq->Animations.EquipMontage.Get();
		UnequipMontage = Eq->Animations.UnequipMontage.Get();
		InspectMontage = Eq->Animations.InspectMontage.Get();
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
		SetActorHiddenInGame(!bNewVisible);
		K2_OnEquippedVisibilityChanged(bNewVisible);
	}
	
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