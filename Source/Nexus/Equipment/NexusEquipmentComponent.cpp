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

FResolvedSlotAnims UNexusEquipmentComponent::GetResolvedSlotAnims(FGameplayTag SlotTag) const
{
	if (const FResolvedSlotAnims* Found = SlotAnims.Find(SlotTag))
	{
		return *Found;
	}
	return FResolvedSlotAnims();
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
	
	FResolvedSlotAnims Resolved;
	const FEquippableAnimationSet& AnimationSet = Eq->Animations;

	Resolved.IdlePose        = AnimationSet.IdlePose.LoadSynchronous();
	Resolved.IdleLoop        = AnimationSet.IdleLoop.LoadSynchronous();
	Resolved.RunLoop         = AnimationSet.RunLoop.LoadSynchronous();
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
	
	if (OutgoingPendingHide.MatchesTagExact(SlotTag))
	{
		OutgoingPendingHide = FGameplayTag();
	}

	SlotAnims.Remove(SlotTag);
}

void UNexusEquipmentComponent::HandleActiveSlotTransition(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot)
{
	if (OutgoingPendingHide.IsValid() && !OutgoingPendingHide.MatchesTagExact(OutgoingSlot))
	{
		AttachActorForSlotState(OutgoingPendingHide, /*bActive*/false);
		OutgoingPendingHide = FGameplayTag();
	}

	float UnequipLength = 0.0f;
	float EquipLength   = 0.0f;
	
	if (OutgoingSlot.IsValid())
	{
		UAnimMontage* UnequipMontage = nullptr;
		if (const FResolvedSlotAnims* Anims = SlotAnims.Find(OutgoingSlot))
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

			AttachActorForSlotState(OutgoingSlot, false);
		}
	}
	
	if (IncomingSlot.IsValid())
	{
		AttachActorForSlotState(IncomingSlot, /*bActive*/true);
		if (const FResolvedSlotAnims* Anims = SlotAnims.Find(IncomingSlot))
		{
			EquipLength = PlayMontageOnOwner(Anims->EquipMontage);
		}
	}
	
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