#include "NexusEquippedActor.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/SkeletalMesh.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Equipment/Attachments/NexusWeaponAssemblyComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"

ANexusEquippedActor::ANexusEquippedActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Assembly = CreateDefaultSubobject<UNexusWeaponAssemblyComponent>(TEXT("WeaponAssembly"));
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
		UnholsterMontage   = Eq->Animations.UnholsterMontage.Get();
		HolsterMontage = Eq->Animations.HolsterMontage.Get();
		InspectMontage = Eq->Animations.InspectMontage.Get();

		if (UClass* AnimClass = Eq->Animations.WeaponAnimInstanceClass.Get())
		{
			Mesh->SetAnimInstanceClass(AnimClass);
		}

		WeaponActionMontages.Reserve(Eq->Animations.WeaponActionMontages.Num());
		for (const TPair<FGameplayTag, TSoftObjectPtr<UAnimMontage>>& Pair : Eq->Animations.WeaponActionMontages)
		{
			if (!Pair.Key.IsValid()) continue;
			if (UAnimMontage* Loaded = Pair.Value.Get())
			{
				WeaponActionMontages.Add(Pair.Key, Loaded);
			}
		}
	}

	if (Assembly)
	{
		Assembly->RebuildFromInstance();
	}

	K2_OnInitializedFromInstance();
}

UAnimMontage* ANexusEquippedActor::PlayWeaponAction(FGameplayTag ActionTag)
{
	if (!ActionTag.IsValid()) return nullptr;

	UAnimMontage* Montage = GetEffectiveActionMontage(ActionTag);
	if (!Montage) return nullptr;
	if (!Mesh) return nullptr;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance) return nullptr;

	if (AnimInstance->Montage_Play(Montage) > 0.0f)
	{
		return Montage;
	}
	return nullptr;
}

UAnimMontage* ANexusEquippedActor::GetWeaponActionMontage(const FGameplayTag ActionTag) const
{
	if (!ActionTag.IsValid()) return nullptr;
	if (const TObjectPtr<UAnimMontage>* Found = WeaponActionMontages.Find(ActionTag))
	{
		return Found->Get();
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

FResolvedWeaponStats ANexusEquippedActor::GetResolvedStats() const
{
	if (Assembly) return Assembly->ResolveStats();
	return FResolvedWeaponStats{};
}

UAnimMontage* ANexusEquippedActor::GetEffectiveActionMontage(const FGameplayTag ActionTag) const
{
	if (Assembly)
	{
		if (UAnimMontage* Resolved = Assembly->ResolveActionMontage(ActionTag))
		{
			return Resolved;
		}
	}
	return GetWeaponActionMontage(ActionTag);
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