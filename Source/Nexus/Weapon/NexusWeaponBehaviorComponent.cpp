#include "NexusWeaponBehaviorComponent.h"

#include "Animation/AnimMontage.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Equipment/Attachments/NexusWeaponAssemblyComponent.h"
#include "Nexus/Equipment/Attachments/Fragments/NexusAttachmentFragment_Magazine.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Weapon/NexusFragment_Weapon.h"
#include "Nexus/NexusGameplayTags.h"

UNexusWeaponBehaviorComponent::UNexusWeaponBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusWeaponBehaviorComponent::OnInstalled(ANexusEquippedActor* InEquippedActor)
{
	Super::OnInstalled(InEquippedActor);

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;

	CacheActionMontages(*Weapon);
	SpawnChamberRoundMesh(*Weapon);

	if (UNexusItemInstance* Instance = EquippedActor ? EquippedActor->GetSourceInstance() : nullptr)
	{
		Instance->OnInstanceChanged.AddDynamic(this, &UNexusWeaponBehaviorComponent::HandleInstanceChanged);
		bSubscribedToInstance = true;

		LastInMagazine = Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0);
	}

	if (UNexusWeaponAssemblyComponent* AssemblyComp = EquippedActor ? EquippedActor->GetAssembly() : nullptr)
	{
		AssemblyComp->OnAssemblyChanged.AddDynamic(this, &UNexusWeaponBehaviorComponent::HandleAssemblyChanged);
	}

	// Initial pass — magazine attachment may already be in place from the
	// assembly's RebuildFromInstance ordering. Safe no-op if it isn't.
	RefreshMagazineVisual();
}

void UNexusWeaponBehaviorComponent::OnUninstalled()
{
	if (bSubscribedToInstance && EquippedActor)
	{
		if (UNexusItemInstance* Instance = EquippedActor->GetSourceInstance())
		{
			Instance->OnInstanceChanged.RemoveDynamic(this, &UNexusWeaponBehaviorComponent::HandleInstanceChanged);
		}
		bSubscribedToInstance = false;
	}

	if (EquippedActor)
	{
		if (UNexusWeaponAssemblyComponent* AssemblyComp = EquippedActor->GetAssembly())
		{
			AssemblyComp->OnAssemblyChanged.RemoveDynamic(this, &UNexusWeaponBehaviorComponent::HandleAssemblyChanged);
		}
	}

	if (ChamberRoundMesh)
	{
		ChamberRoundMesh->DestroyComponent();
		ChamberRoundMesh = nullptr;
	}

	ActionMontages.Reset();
	LastInMagazine = -1;

	Super::OnUninstalled();
}

void UNexusWeaponBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Backstop the install-time RefreshMagazineVisual: the assembly suppresses
	// OnAssemblyChanged broadcasts before its own BeginPlay, so synchronously
	// resident attachments that finished loading during InitializeFromInstance
	// don't reach this behavior's HandleAssemblyChanged. Re-running here picks
	// them up; async-loaded attachments are still handled via the delegate.
	RefreshMagazineVisual();
}

void UNexusWeaponBehaviorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnUninstalled();
	Super::EndPlay(EndPlayReason);
}

UAnimMontage* UNexusWeaponBehaviorComponent::GetActionMontage(FGameplayTag ActionTag) const
{
	if (!ActionTag.IsValid()) return nullptr;
	if (const TObjectPtr<UAnimMontage>* Found = ActionMontages.Find(ActionTag))
	{
		return Found->Get();
	}
	return nullptr;
}

void UNexusWeaponBehaviorComponent::SetChamberRoundVisible(bool bVisible)
{
	if (!ChamberRoundMesh) return;
	ChamberRoundMesh->SetVisibility(bVisible, /*bPropagateToChildren*/ true);
}

void UNexusWeaponBehaviorComponent::CacheActionMontages(const FNexusFragment_Weapon& WeaponFragment)
{
	ActionMontages.Reset();
	ActionMontages.Reserve(WeaponFragment.Animations.ActionMontages.Num());
	for (const TPair<FGameplayTag, TSoftObjectPtr<UAnimMontage>>& Pair : WeaponFragment.Animations.ActionMontages)
	{
		if (!Pair.Key.IsValid()) continue;
		if (UAnimMontage* Loaded = Pair.Value.Get())
		{
			ActionMontages.Add(Pair.Key, Loaded);
		}
	}
}

void UNexusWeaponBehaviorComponent::SpawnChamberRoundMesh(const FNexusFragment_Weapon& WeaponFragment)
{
	if (!EquippedActor) return;

	UStaticMesh* RoundMesh = WeaponFragment.AmmoVisual.RoundMesh.Get();
	if (!RoundMesh)
	{
		// Bundle should have made this resident; absence means the weapon
		// fragment didn't author one (a melee weapon, or a magazineless
		// design). Skip silently.
		if (WeaponFragment.AmmoVisual.RoundMesh.IsNull()) return;
		RoundMesh = WeaponFragment.AmmoVisual.RoundMesh.LoadSynchronous();
		if (!RoundMesh) return;
	}

	USkeletalMeshComponent* HostMesh = EquippedActor->GetMesh();
	if (!HostMesh) return;

	const FName Socket = WeaponFragment.AmmoVisual.AmmoSocket;
	if (!HostMesh->DoesSocketExist(Socket))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[WeaponBehavior] Ammo socket '%s' not found on equipped mesh; chamber round visual will be inert."),
			*Socket.ToString());
	}

	ChamberRoundMesh = NewObject<UStaticMeshComponent>(EquippedActor);
	if (!ChamberRoundMesh) return;

	ChamberRoundMesh->SetStaticMesh(RoundMesh);
	ChamberRoundMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChamberRoundMesh->SetVisibility(false, /*bPropagateToChildren*/ true);
	ChamberRoundMesh->RegisterComponent();
	ChamberRoundMesh->AttachToComponent(HostMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);

	// ApplyViewpoint is called from the actor's ApplyOwnerViewpointRendering
	// after InitializeFromInstance returns; the chamber round picks up cast-
	// shadow / first-person primitive type there.
}

void UNexusWeaponBehaviorComponent::ApplyViewpoint(bool bIsFirstPerson)
{
	if (!ChamberRoundMesh) return;
	if (bIsFirstPerson)
	{
		ChamberRoundMesh->SetCastShadow(false);
		ChamberRoundMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	}
	else
	{
		ChamberRoundMesh->SetCastShadow(true);
		ChamberRoundMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::None;
	}
}

void UNexusWeaponBehaviorComponent::HandleInstanceChanged(UNexusItemInstance* Instance)
{
	if (!Instance) return;
	if (!EquippedActor || Instance != EquippedActor->GetSourceInstance()) return;

	const int32 NewInMagazine = Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0);
	const bool bWasEmpty = LastInMagazine == 0;
	const bool bIsEmpty  = NewInMagazine == 0;

	// Only act on transitions across zero — the user wants binary, immediate
	// swap on InMagazine -> 0 (and -> >0 for refilled). Mid-range stat changes
	// (e.g. 12 -> 11) leave the visual untouched.
	if (LastInMagazine < 0 || bWasEmpty != bIsEmpty)
	{
		LastInMagazine = NewInMagazine;
		RefreshMagazineVisual();
	}
	else
	{
		LastInMagazine = NewInMagazine;
	}
}

void UNexusWeaponBehaviorComponent::HandleAssemblyChanged()
{
	// Magazine attachment may have changed (player swapped to extended mag,
	// removed it, etc.). Reapply with the current ammo state.
	RefreshMagazineVisual();
}

void UNexusWeaponBehaviorComponent::RefreshMagazineVisual()
{
	if (!EquippedActor) return;

	UNexusWeaponAssemblyComponent* AssemblyComp = EquippedActor->GetAssembly();
	if (!AssemblyComp) return;

	UNexusItemInstance* Instance = EquippedActor->GetSourceInstance();
	if (!Instance) return;

	const int32 InMagazine = Instance->GetStat(NexusGameplayTags::Stat_Ammo_InMagazine, 0);
	const bool bLoaded = InMagazine > 0;

	// Slot-tag-agnostic: any attachment that carries the Magazine fragment is
	// a magazine. Lets a weapon expose two mag slots (revolver speedloader +
	// drum) without baking the slot tag here.
	for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : AssemblyComp->GetAttachedRecordsRef())
	{
		const FNexusAttachmentInstance& Record = Pair.Value;
		if (!Record.Definition || !Record.Mesh) continue;

		const FNexusAttachmentFragment_Magazine* MagFrag =
			Record.Definition->FindFragment<FNexusAttachmentFragment_Magazine>();
		if (!MagFrag) continue;

		const TSoftObjectPtr<USkeletalMesh>& Target = bLoaded ? MagFrag->LoadedMesh : MagFrag->EmptyMesh;
		USkeletalMesh* TargetMesh = Target.Get();
		if (!TargetMesh && !Target.IsNull())
		{
			TargetMesh = Target.LoadSynchronous();
		}
		if (!TargetMesh) continue; // designer left this state's mesh blank — keep the current visual

		USkeletalMesh* CurrentMesh = Record.Mesh->GetSkeletalMeshAsset();
		if (CurrentMesh == TargetMesh) continue;

		Record.Mesh->SetSkeletalMesh(TargetMesh);
	}
}

const FNexusFragment_Weapon* UNexusWeaponBehaviorComponent::GetWeaponFragment() const
{
	if (!EquippedActor) return nullptr;
	const UNexusItemInstance* Instance = EquippedActor->GetSourceInstance();
	if (!Instance) return nullptr;
	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return nullptr;
	return Definition->FindFragment<FNexusFragment_Weapon>();
}