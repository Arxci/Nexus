// Fill out your copyright notice in the Description page of Project Settings.

#include "NexusEquipmentComponent.h"

#include "GameFramework/Character.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/World.h"

#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"

#include "NexusEquippedActor.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/NexusFragment_Equippable.h"

UNexusEquipmentComponent::UNexusEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (UNexusInventoryComponent* Inventory = GetInventory())
	{
		Inventory->OnItemRemoved.AddDynamic(this, &UNexusEquipmentComponent::HandleInventoryItemRemoved);
	}
}

void UNexusEquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UNexusInventoryComponent* Inventory = GetInventory())
	{
		Inventory->OnItemRemoved.RemoveDynamic(this, &UNexusEquipmentComponent::HandleInventoryItemRemoved);
	}

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(SwapLockoutTimer);
	}
	OutgoingPendingHide = FGameplayTag();

	UnequipAll();
	Super::EndPlay(EndPlayReason);
}

void UNexusEquipmentComponent::HandleInventoryItemRemoved(UNexusItemInstance* RemovedInstance)
{
	if (!RemovedInstance) return;
	if (EquippedSlots.Num() == 0) return;

	TArray<TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>, TInlineAllocator<4>> Snapshot;
	Snapshot.Reserve(EquippedSlots.Num());
	for (const TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>& Pair : EquippedSlots)
	{
		Snapshot.Add(Pair);
	}

	for (const TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>& Pair : Snapshot)
	{
		if (Pair.Value == RemovedInstance)
		{
			UnequipSlot(Pair.Key);
		}
	}
}

UNexusAbilitySystemComponent* UNexusEquipmentComponent::GetASC() const
{
	if (const INexusAbilitySystemInterface* ASCOwner = Cast<INexusAbilitySystemInterface>(GetOwner()))
	{
		return ASCOwner->GetNexusAbilitySystemComponent();
	}
	return nullptr;
}

UNexusInventoryComponent* UNexusEquipmentComponent::GetInventory() const
{
	return GetOwner() ? GetOwner()->FindComponentByClass<UNexusInventoryComponent>() : nullptr;
}


// Lifecycle
bool UNexusEquipmentComponent::EquipInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return false;
	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return false;

	const FNexusFragment_Equippable* Eq = Definition->FindFragment<FNexusFragment_Equippable>();
	if (!Eq || !Eq->SlotTag.IsValid()) return false;

	const FGameplayTag SlotTag = Eq->SlotTag;

	if (IsSlotOccupied(SlotTag))
	{
		UnequipSlot(SlotTag);
	}

	EquippedSlots.Add(SlotTag, Instance);
	ApplyEquipEffects(SlotTag, Instance);

	OnEquipped.Broadcast(SlotTag, Instance);

	if (!ActiveSlot.IsValid())
	{
		SetActiveSlot(SlotTag);
	}
	else
	{
		// Newly-equipped but not active: ensure it's stowed/hidden, not stuck on the hand.
		AttachActorForSlotState(SlotTag, /*bActive*/false);
	}
	return true;
}

UNexusItemInstance* UNexusEquipmentComponent::TryEquipFirstCompatibleForSlot(FGameplayTag SlotTag)
{
	if (!SlotTag.IsValid()) return nullptr;

	if (UNexusItemInstance* Existing = GetEquippedInSlot(SlotTag))
	{
		return Existing;
	}

	const UNexusInventoryComponent* Inventory = GetInventory();
	if (!Inventory) return nullptr;

	for (UNexusItemInstance* Inst : Inventory->GetItems())
	{
		if (!Inst) continue;
		const UNexusItemDefinition* Definition = Inst->GetDefinition();
		if (!Definition) continue;

		const FNexusFragment_Equippable* Eq = Definition->FindFragment<FNexusFragment_Equippable>();
		if (!Eq) continue;
		if (!Eq->SlotTag.MatchesTagExact(SlotTag)) continue;

		return EquipInstance(Inst) ? Inst : nullptr;
	}
	return nullptr;
}

bool UNexusEquipmentComponent::UnequipSlot(FGameplayTag SlotTag)
{
	UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
	if (!Instance) return false;

	const bool bWasActive = ActiveSlot.MatchesTagExact(SlotTag);

	RemoveEquipEffects(SlotTag);
	EquippedSlots.Remove(SlotTag);

	OnUnequipped.Broadcast(SlotTag, Instance);

	if (bWasActive)
	{
		ActiveSlot = FGameplayTag();
		OnActiveSlotChanged.Broadcast(ActiveSlot, nullptr);
	}
	return true;
}

void UNexusEquipmentComponent::UnequipAll()
{
	TArray<FGameplayTag> Slots;
	EquippedSlots.GetKeys(Slots);
	for (const FGameplayTag& Slot : Slots)
	{
		UnequipSlot(Slot);
	}
}


// Utility
UNexusItemInstance* UNexusEquipmentComponent::GetEquippedInSlot(FGameplayTag SlotTag) const
{
	return EquippedSlots.FindRef(SlotTag);
}

ANexusEquippedActor* UNexusEquipmentComponent::GetEquippedActorInSlot(FGameplayTag SlotTag) const
{
	return SpawnedActors.FindRef(SlotTag);
}

bool UNexusEquipmentComponent::IsSlotOccupied(FGameplayTag SlotTag) const
{
	return EquippedSlots.Contains(SlotTag);
}

void UNexusEquipmentComponent::SetActiveSlot(FGameplayTag SlotTag)
{
	if (ActiveSlot.MatchesTagExact(SlotTag)) return;
	if (SlotTag.IsValid() && !EquippedSlots.Contains(SlotTag)) return;

	const FGameplayTag OutgoingSlot = ActiveSlot;
	ActiveSlot = SlotTag;

	HandleActiveSlotTransition(OutgoingSlot, SlotTag);

	OnActiveSlotChanged.Broadcast(ActiveSlot, GetEquippedInSlot(ActiveSlot));
}

UNexusItemInstance* UNexusEquipmentComponent::GetActiveInstance() const
{
	return GetEquippedInSlot(ActiveSlot);
}

FNexusResolvedSlotAnims UNexusEquipmentComponent::GetResolvedSlotAnims(FGameplayTag SlotTag) const
{
	if (const FNexusResolvedSlotAnims* Found = SlotAnims.Find(SlotTag))
	{
		return *Found;
	}
	return FNexusResolvedSlotAnims();
}


// Effects
void UNexusEquipmentComponent::ApplyEquipEffects(FGameplayTag SlotTag, UNexusItemInstance* Instance)
{
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	if (!Definition) return;

	const FNexusFragment_Equippable* Eq = Definition->FindFragment<FNexusFragment_Equippable>();
	if (!Eq) return;

	UClass* ActorClass = Eq->EquippedActorClass.LoadSynchronous();
	if (!ActorClass) ActorClass = ANexusEquippedActor::StaticClass();

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters Params;
		Params.Owner                          = GetOwner();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ANexusEquippedActor* Spawned          = World->SpawnActor<ANexusEquippedActor>(ActorClass, Params);
		if (Spawned)
		{
			Spawned->InitializeFromInstance(Instance);
			Spawned->ApplyOwnerViewpointRendering();
			SpawnedActors.Add(SlotTag, Spawned);
		}
	}

	// Grant abilities. The ASC ref-counts grants now, so two slots granting the
	// same ability class share one instance and the second unequip won't pull
	// the rug out from under the first.
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		TArray<TSubclassOf<UNexusAbility>>& Granted = AppliedAbilitiesBySlot.FindOrAdd(SlotTag);
		for (const TSubclassOf<UNexusAbility>& AbilityClass : Eq->GrantedAbilities)
		{
			if (AbilityClass && ASC->GiveAbility(AbilityClass))
			{
				Granted.Add(AbilityClass);
			}
		}

		FGameplayTagContainer Pushed;
		Pushed.AddTag(SlotTag);
		Pushed.AppendTags(Eq->OwnedTagsWhileEquipped);
		for (const FGameplayTag& Tag : Pushed)
		{
			ASC->AddLooseGameplayTag(Tag);
		}
		AppliedTagsBySlot.Add(SlotTag, Pushed);
	}

	// Resolve presentation animations once at equip time so the anim BP /
	// fire ability can read hard pointers without sync-loading on the hot path.
	FNexusResolvedSlotAnims Resolved;
	const FEquippableAnimationSet& AnimationSet = Eq->Animations;

	Resolved.IdlePose        = AnimationSet.IdlePose.LoadSynchronous();
	Resolved.IdleLoop        = AnimationSet.IdleLoop.LoadSynchronous();
	Resolved.RunLoop = AnimationSet.RunLoop.LoadSynchronous();
	Resolved.EquipMontage    = AnimationSet.EquipMontage.LoadSynchronous();
	Resolved.UnequipMontage  = AnimationSet.UnequipMontage.LoadSynchronous();
	Resolved.InspectMontage  = AnimationSet.InspectMontage.LoadSynchronous();

	SlotAnims.Add(SlotTag, Resolved);
}


void UNexusEquipmentComponent::RemoveEquipEffects(FGameplayTag SlotTag)
{
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		if (TArray<TSubclassOf<UNexusAbility>>* Granted = AppliedAbilitiesBySlot.Find(SlotTag))
		{
			for (const TSubclassOf<UNexusAbility>& AbilityClass : *Granted)
			{
				// RemoveAbility is ref-counted on the ASC. Safe to call once per
				// grant from this slot, even if another slot still grants the
				// same class — the instance only dies at zero count.
				ASC->RemoveAbility(AbilityClass);
			}
		}
		AppliedAbilitiesBySlot.Remove(SlotTag);

		if (FGameplayTagContainer* Tags = AppliedTagsBySlot.Find(SlotTag))
		{
			for (const FGameplayTag& Tag : *Tags)
			{
				ASC->RemoveLooseGameplayTag(Tag);
			}
		}
		AppliedTagsBySlot.Remove(SlotTag);
	}

	if (TObjectPtr<ANexusEquippedActor> Actor = SpawnedActors.FindRef(SlotTag))
	{
		Actor->Destroy();
	}
	SpawnedActors.Remove(SlotTag);

	// If the slot we're tearing down was waiting for its hide notify, drop the
	// marker — its actor is gone anyway and we don't want a stale tag making
	// HandleSwapLockoutFinished's safety net target a freshly re-equipped slot.
	if (OutgoingPendingHide.MatchesTagExact(SlotTag))
	{
		OutgoingPendingHide = FGameplayTag();
	}

	SlotAnims.Remove(SlotTag);
}

void UNexusEquipmentComponent::HandleActiveSlotTransition(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot)
{
	// Stomp protection: if a previous swap is still mid-flight, its montage is
	// about to be interrupted by the new transition (montages share the upper-
	// body slot). The notify it was waiting on will never fire, so force-hide
	// that previous outgoing now before we overwrite the pending marker.
	if (OutgoingPendingHide.IsValid() && !OutgoingPendingHide.MatchesTagExact(OutgoingSlot))
	{
		AttachActorForSlotState(OutgoingPendingHide, /*bActive*/false);
		OutgoingPendingHide = FGameplayTag();
	}

	float UnequipLength = 0.0f;
	float EquipLength   = 0.0f;

	// Outgoing: play the unequip montage and let its HideOutgoingEquipped
	// anim notify drive the actual hide. We DO NOT hide the actor here — the
	// player should see the weapon being put away, not have it pop out on
	// frame 0 of the holster animation.
	if (OutgoingSlot.IsValid())
	{
		UAnimMontage* UnequipMontage = nullptr;
		if (const FNexusResolvedSlotAnims* Anims = SlotAnims.Find(OutgoingSlot))
		{
			UnequipMontage = Anims->UnequipMontage;
		}
		UnequipLength = PlayMontageOnOwner(UnequipMontage);

		if (UnequipLength > 0.0f)
		{
			OutgoingPendingHide = OutgoingSlot;
		}
		else
		{
			// No montage configured/played → nothing to wait for, hide now.
			AttachActorForSlotState(OutgoingSlot, /*bActive*/false);
		}
	}

	// Incoming: attach + show before playing the equip montage. The weapon
	// must be present in the hand from frame 0 of the draw so the animator
	// can move it into view as part of the animation, rather than have it
	// pop into existence partway through.
	if (IncomingSlot.IsValid())
	{
		AttachActorForSlotState(IncomingSlot, /*bActive*/true);
		if (const FNexusResolvedSlotAnims* Anims = SlotAnims.Find(IncomingSlot))
		{
			EquipLength = PlayMontageOnOwner(Anims->EquipMontage);
		}
	}

	// Lockout: blocks Fire / Reload / further swaps for the duration of the
	// longer of the two montages. HandleSwapLockoutFinished is also where the
	// "designer forgot the hide notify" safety net runs.
	const float LockoutDuration = FMath::Max(UnequipLength, EquipLength);
	if (LockoutDuration > 0.0f)
	{
		if (UNexusAbilitySystemComponent* ASC = GetASC())
		{
			if (!bIsSwapping)
			{
				bIsSwapping = true;
				ASC->AddLooseGameplayTag(NexusGameplayTags::Character_State_Weapon_Swapping);
			}
		}
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(
				SwapLockoutTimer, this,
				&UNexusEquipmentComponent::HandleSwapLockoutFinished,
				LockoutDuration, /*bLoop*/false);
		}
	}
	else
	{
		HandleSwapLockoutFinished();
	}
}

void UNexusEquipmentComponent::NotifyHideOutgoingSlot()
{
	if (!OutgoingPendingHide.IsValid()) return;

	const FGameplayTag SlotToHide = OutgoingPendingHide;
	OutgoingPendingHide = FGameplayTag();
	AttachActorForSlotState(SlotToHide, /*bActive*/false);
}

void UNexusEquipmentComponent::HandleSwapLockoutFinished()
{
	// Safety net: if the unequip montage finished (or was interrupted such
	// that its HideOutgoingEquipped notify never fired), hide the outgoing
	// now so we don't leak a visible weapon. Designer-authored notifies
	// fire earlier in the montage, so this path normally has nothing to do.
	if (OutgoingPendingHide.IsValid())
	{
		const FGameplayTag SlotToHide = OutgoingPendingHide;
		OutgoingPendingHide = FGameplayTag();
		AttachActorForSlotState(SlotToHide, /*bActive*/false);
	}

	if (!bIsSwapping) return;
	bIsSwapping = false;
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	}
}

void UNexusEquipmentComponent::AttachActorForSlotState(FGameplayTag SlotTag, bool bActive)
{
	ANexusEquippedActor* Actor = SpawnedActors.FindRef(SlotTag);
	if (!Actor) return;

	if (!bActive)
	{
		// Inactive: hide. The actor stays alive so swapping back is instant —
		// destroy/respawn on every weapon swap is too costly given the assets.
		Actor->SetEquippedVisibility(false);
		return;
	}

	const UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	const FNexusFragment_Equippable* Eq = Definition
		? Definition->FindFragment<FNexusFragment_Equippable>() : nullptr;
	if (!Eq) return;

	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (!CharacterMesh) return;

	Actor->AttachToComponent(CharacterMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, Eq->AttachSocket);
	Actor->SetEquippedVisibility(true);
}

float UNexusEquipmentComponent::PlayMontageOnOwner(UAnimMontage* Montage) const
{
	if (!Montage) return 0.0f;

	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return 0.0f;
	const USkeletalMeshComponent* Mesh = Character->GetMesh();
	if (!Mesh) return 0.0f;
	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance) return 0.0f;

	return AnimInstance->Montage_Play(Montage);
}


// Save
void UNexusEquipmentComponent::ComponentPreLoad_Implementation()
{
	UnequipAll();
}

void UNexusEquipmentComponent::ComponentLoaded_Implementation()
{
	const FGameplayTag SavedActiveSlot = ActiveSlot;
	ActiveSlot = FGameplayTag();

	TArray<FGameplayTag, TInlineAllocator<4>> Slots;
	EquippedSlots.GetKeys(Slots);
	for (const FGameplayTag& SlotTag : Slots)
	{
		if (UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag))
		{
			ApplyEquipEffects(SlotTag, Instance);
			AttachActorForSlotState(SlotTag, /*bActive*/false);
		}
	}

	// Snap to the saved active slot — no draw montage, no lockout. Player just
	// loaded; don't make them wait for a holster animation before they can fire.
	if (SavedActiveSlot.IsValid() && EquippedSlots.Contains(SavedActiveSlot))
	{
		ActiveSlot = SavedActiveSlot;
		AttachActorForSlotState(SavedActiveSlot, /*bActive*/true);
	}

	OnActiveSlotChanged.Broadcast(ActiveSlot, GetEquippedInSlot(ActiveSlot));
}