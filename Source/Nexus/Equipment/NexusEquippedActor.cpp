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
		const FResolvedWeaponStats Stats = Assembly->ResolveStats();
		return Stats.Get(StatTag, Default);
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