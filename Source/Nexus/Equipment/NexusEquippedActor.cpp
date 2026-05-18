#include "NexusEquippedActor.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/SkeletalMesh.h"

#include "GameFramework/Pawn.h"

#include "StructUtils/InstancedStruct.h"

#include "Nexus/Equipment/Attachments/NexusAssemblyComponent.h"
#include "Nexus/Equipment/NexusEquippedActorBehavior.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"

ANexusEquippedActor::ANexusEquippedActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Assembly = CreateDefaultSubobject<UNexusAssemblyComponent>(TEXT("Assembly"));
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

		IdlePose = Eq->Animations.IdlePose.Get();
		IdleLoop = Eq->Animations.IdleLoop.Get();
		RunLoop  = Eq->Animations.RunLoop.Get();

		if (UClass* AnimClass = Eq->Animations.MeshAnimInstanceClass.Get())
		{
			Mesh->SetAnimInstanceClass(AnimClass);
		}
	}

	// Fragments install their actor-side behaviors (e.g. weapon fragment adds
	// UNexusWeaponBehaviorComponent). Done before assembly rebuild so behaviors
	// are present when OnAssemblyChanged first broadcasts.
	for (const TInstancedStruct<FNexusItemFragment>& Frag : DefinitionData->Fragments)
	{
		if (!Frag.IsValid()) continue;
		Frag.Get().OnInstall(this);
	}

	if (Assembly)
	{
		Assembly->RebuildFromInstance();
	}

	K2_OnInitializedFromInstance();
}

void ANexusEquippedActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Mirror InitializeFromInstance: walk fragments and let each uninstall its
	// behavior. Defensive — DestroyActor will tear behaviors down anyway, but
	// fragment-driven cleanup gives us a hook for non-component side effects.
	if (SourceInstance)
	{
		if (const UNexusItemDefinition* DefinitionData = SourceInstance->GetDefinition())
		{
			for (const TInstancedStruct<FNexusItemFragment>& Frag : DefinitionData->Fragments)
			{
				if (!Frag.IsValid()) continue;
				Frag.Get().OnUninstall(this);
			}
		}
	}

	Super::EndPlay(EndPlayReason);
}

UAnimMontage* ANexusEquippedActor::GetEffectiveArmsMontage(const FGameplayTag ActionTag) const
{
	if (!ActionTag.IsValid() || !Assembly) return nullptr;
	return Assembly->ResolveArmsMontage(ActionTag);
}

UAnimMontage* ANexusEquippedActor::GetEffectiveItemMontage(const FGameplayTag ActionTag) const
{
	if (!ActionTag.IsValid() || !Assembly) return nullptr;
	return Assembly->ResolveItemMontage(ActionTag);
}

UAnimMontage* ANexusEquippedActor::PlayItemActionMontage(FGameplayTag ActionTag)
{
	UAnimMontage* Montage = GetEffectiveItemMontage(ActionTag);
	if (!Montage || !Mesh) return nullptr;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance) return nullptr;

	if (AnimInstance->Montage_Play(Montage) > 0.0f)
	{
		return Montage;
	}
	return nullptr;
}

float ANexusEquippedActor::GetEffectiveStat(const FGameplayTag StatTag, const float Default) const
{
	if (Assembly)
	{
		// Hot path (per-shot): read the cached map by reference — avoids the
		// TMap copy that the BP-facing ResolveStats() return-by-value would do.
		return Assembly->ResolveStatsRef().Get(StatTag, Default);
	}
	return Default;
}

FResolvedItemStats ANexusEquippedActor::GetResolvedStats() const
{
	if (Assembly) return Assembly->ResolveStats();
	return FResolvedItemStats{};
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
	const bool bChanged = bVisible != bNewVisible;
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
	// "Locally controlled by a player" — true for the singleplayer player pawn,
	// false for AI (which is locally controlled but not player-controlled) and
	// false for any future remote players.
	const APawn* OwnerPawn = Cast<APawn>(GetOwner());
	bIsFirstPersonView = OwnerPawn
		&& OwnerPawn->IsPlayerControlled()
		&& OwnerPawn->IsLocallyControlled();

	ApplyViewpointToMesh(Mesh);

	// Propagate to every attachment mesh currently spawned by the assembly so a
	// view change at runtime updates the whole gun, not just the receiver.
	if (Assembly)
	{
		for (USkeletalMeshComponent* AttachMesh : Assembly->GetAttachmentMeshes())
		{
			ApplyViewpointToMesh(AttachMesh);
		}
	}

	// Behavior components own their own meshes (chamber round, future
	// flashlight cone, etc.) — let each apply viewpoint to its own children.
	TArray<UNexusEquippedActorBehavior*> Behaviors;
	GetComponents<UNexusEquippedActorBehavior>(Behaviors);
	for (UNexusEquippedActorBehavior* Behavior : Behaviors)
	{
		if (Behavior) Behavior->ApplyViewpoint(bIsFirstPersonView);
	}

	K2_OnOwnerViewpointApplied(bIsFirstPersonView);
}

void ANexusEquippedActor::ApplyViewpointToMesh(USkeletalMeshComponent* TargetMesh) const
{
	if (!TargetMesh) return;

	if (bIsFirstPersonView)
	{
		TargetMesh->SetCastShadow(false);
		TargetMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	}
	else
	{
		TargetMesh->SetCastShadow(true);
		TargetMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::None;
	}
}