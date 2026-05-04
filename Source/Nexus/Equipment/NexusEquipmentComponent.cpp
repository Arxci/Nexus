#include "NexusEquipmentComponent.h"

#include "Engine/AssetManager.h"

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
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"

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

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PhaseTimer);
	}

	OutgoingPendingHide = FGameplayTag();
	PendingActivation.Reset();
	SwapPhase = ENexusEquipSwapPhase::Idle;
	SwapOutgoingSlot = FGameplayTag();
	SwapIncomingSlot = FGameplayTag();

	ClearAll();
	EquippableLoadHandles.Empty();

	Super::EndPlay(EndPlayReason);
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


// Loadout (UI-driven assignment)
bool UNexusEquipmentComponent::CanAssignToSlot(const UNexusItemInstance* Instance, FGameplayTag SlotTag) const
{
	if (!Instance || !SlotTag.IsValid()) return false;
	if (!IsValidSlot(SlotTag)) return false;

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return false;

	const FNexusFragment_Equippable* Eq = Definition->FindFragment<FNexusFragment_Equippable>();
	if (!Eq) return false;

	return Eq->CanFitInSlot(SlotTag);
}

bool UNexusEquipmentComponent::IsValidSlot(FGameplayTag SlotTag) const
{
	if (!SlotTag.IsValid()) return false;
	if (AvailableSlots.Num() == 0) return true;
	return AvailableSlots.Contains(SlotTag);
}

TArray<FGameplayTag> UNexusEquipmentComponent::GetCompatibleSlotsForInstance(const UNexusItemInstance* Instance) const
{
	TArray<FGameplayTag> Out;
	if (!Instance) return Out;

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return Out;

	const FNexusFragment_Equippable* Eq = Definition->FindFragment<FNexusFragment_Equippable>();
	if (!Eq) return Out;
	
	const TArray<FGameplayTag>& Slots = AvailableSlots.Num() > 0
		? AvailableSlots
		: Eq->AllowedSlots.GetGameplayTagArray();

	Out.Reserve(Slots.Num());
	for (const FGameplayTag& Slot : Slots)
	{
		if (Eq->CanFitInSlot(Slot))
		{
			Out.Add(Slot);
		}
	}
	return Out;
}

bool UNexusEquipmentComponent::AssignToSlot(UNexusItemInstance* Instance, FGameplayTag SlotTag)
{
	if (!CanAssignToSlot(Instance, SlotTag)) return false;

	UNexusItemInstance* Existing = EquippedSlots.FindRef(SlotTag);
	if (Existing == Instance) return true; 
	
	if (Existing)
	{
		ClearSlotImmediate(SlotTag);
	}
	
	{
		TArray<FGameplayTag> ExistingAssignments;
		for (const TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>& Pair : EquippedSlots)
		{
			if (Pair.Value == Instance) ExistingAssignments.Add(Pair.Key);
		}
		for (const FGameplayTag& Slot : ExistingAssignments)
		{
			ClearSlotImmediate(Slot);
		}
	}

	EquippedSlots.Add(SlotTag, Instance);
	
	TWeakObjectPtr WeakSelf(this);
	TWeakObjectPtr WeakInstance(Instance);
	const FStreamableDelegate OnReady = FStreamableDelegate::CreateLambda(
		[WeakSelf, WeakInstance, SlotTag]()
		{
			UNexusEquipmentComponent* Self = WeakSelf.Get();
			UNexusItemInstance* Inst = WeakInstance.Get();
			if (!Self || !Inst) return;
			if (Self->EquippedSlots.FindRef(SlotTag) != Inst) return;
			Self->FinalizeAssignment(SlotTag, Inst);
		});

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	const FPrimaryAssetId AssetId = Definition ? Definition->GetPrimaryAssetId() : FPrimaryAssetId();
	if (!AssetId.IsValid())
	{
		OnReady.ExecuteIfBound();
		return true;
	}

	UAssetManager& AM = UAssetManager::Get();
	const TSharedPtr<FStreamableHandle> Handle = AM.LoadPrimaryAsset(
		AssetId, TArray<FName>{ TEXT("Equipped") }, OnReady);
	if (Handle.IsValid())
	{
		EquippableLoadHandles.Add(Instance, Handle);
	}
	else
	{
		OnReady.ExecuteIfBound();
	}

	return true;
}

void UNexusEquipmentComponent::FinalizeAssignment(FGameplayTag SlotTag, UNexusItemInstance* Instance)
{
	ApplyEquipEffects(SlotTag, Instance);
	
	AttachActorForSlotState(SlotTag, false);

	OnSlotAssigned.Broadcast(SlotTag, Instance);
}

bool UNexusEquipmentComponent::ClearSlot(FGameplayTag SlotTag)
{
	return ClearSlotImmediate(SlotTag);
}

bool UNexusEquipmentComponent::ClearSlotImmediate(FGameplayTag SlotTag)
{
	UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
	if (!Instance) return false;

	const bool bWasActive = ActiveSlot.MatchesTagExact(SlotTag);

	RemoveEquipEffects(SlotTag);
	EquippedSlots.Remove(SlotTag);
	EquippableLoadHandles.Remove(Instance);

	if (bWasActive)
	{
		ActiveSlot = FGameplayTag();
		if (SwapOutgoingSlot.MatchesTagExact(SlotTag) || SwapIncomingSlot.MatchesTagExact(SlotTag))
		{
			if (const UWorld* World = GetWorld())
			{
				World->GetTimerManager().ClearTimer(PhaseTimer);
			}
			SwapPhase = ENexusEquipSwapPhase::Idle;
			SwapOutgoingSlot = FGameplayTag();
			SwapIncomingSlot = FGameplayTag();
			SetSwapTag(false);
		}
		OnActiveSlotChanged.Broadcast(ActiveSlot, nullptr);
	}

	OnSlotCleared.Broadcast(SlotTag, Instance);
	return true;
}

void UNexusEquipmentComponent::ClearAll()
{
	TArray<FGameplayTag> Slots;
	EquippedSlots.GetKeys(Slots);
	for (const FGameplayTag& Slot : Slots)
	{
		ClearSlotImmediate(Slot);
	}
}

bool UNexusEquipmentComponent::MoveAssignment(FGameplayTag FromSlot, FGameplayTag ToSlot)
{
	if (FromSlot.MatchesTagExact(ToSlot)) return false;

	UNexusItemInstance* FromInst = EquippedSlots.FindRef(FromSlot);
	if (!FromInst) return false;

	UNexusItemInstance* ToInst = EquippedSlots.FindRef(ToSlot);
	
	if (!CanAssignToSlot(FromInst, ToSlot)) return false;
	if (ToInst && !CanAssignToSlot(ToInst, FromSlot)) return false;
	
	ClearSlotImmediate(FromSlot);
	if (ToInst)
	{
		ClearSlotImmediate(ToSlot);
	}

	const bool bMovedFrom = AssignToSlot(FromInst, ToSlot);
	const bool bMovedTo   = !ToInst || AssignToSlot(ToInst, FromSlot);
	return bMovedFrom && bMovedTo;
}


// Activation (input-driven)
bool UNexusEquipmentComponent::RequestActivateSlot(FGameplayTag SlotTag)
{
	if (!SlotTag.IsValid())
	{
		return RequestHolster();
	}

	if (!IsValidSlot(SlotTag)) return false;
	
	if (SwapPhase != ENexusEquipSwapPhase::Idle)
	{
		PendingActivation = SlotTag;
		return true;
	}
	
	if (ActiveSlot.MatchesTagExact(SlotTag))
	{
		return RequestHolster();
	}
	
	if (!IsSlotOccupied(SlotTag)) return false;

	BeginSlotTransition(ActiveSlot, SlotTag);
	return true;
}

bool UNexusEquipmentComponent::RequestHolster()
{
	if (SwapPhase != ENexusEquipSwapPhase::Idle)
	{
		PendingActivation = FGameplayTag(); // queue: holster on completion
		return true;
	}

	if (!ActiveSlot.IsValid()) return false;

	BeginSlotTransition(ActiveSlot, FGameplayTag());
	return true;
}



// Transition state machine
void UNexusEquipmentComponent::BeginSlotTransition(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot)
{
	if (OutgoingSlot.IsValid() && SpawnedActors.Contains(OutgoingSlot))
	{
		BeginHolsterPhase(OutgoingSlot, IncomingSlot);
		return;
	}
	
	if (IncomingSlot.IsValid())
	{
		BeginDrawPhase(IncomingSlot);
		return;
	}
	
	CompleteSwap();
}

void UNexusEquipmentComponent::BeginHolsterPhase(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot)
{
	SwapPhase        = ENexusEquipSwapPhase::Holstering;
	SwapOutgoingSlot = OutgoingSlot;
	SwapIncomingSlot = IncomingSlot;
	SetSwapTag(true);

	UAnimMontage* Unequip = nullptr;
	if (const ANexusEquippedActor* OutActor = SpawnedActors.FindRef(OutgoingSlot))
	{
		Unequip = OutActor->UnequipMontage;
	}
	const float Duration = PlayMontageOnOwner(Unequip);

	if (Duration > 0.0f)
	{
		OutgoingPendingHide = OutgoingSlot;
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(
				PhaseTimer, this,
				&UNexusEquipmentComponent::HandleHolsterPhaseFinished,
				Duration, false);
		}
	}
	else
	{
		AttachActorForSlotState(OutgoingSlot, false);
		HandleHolsterPhaseFinished();
	}
}

void UNexusEquipmentComponent::HandleHolsterPhaseFinished()
{
	if (OutgoingPendingHide.IsValid())
	{
		AttachActorForSlotState(OutgoingPendingHide, false);
		OutgoingPendingHide = FGameplayTag();
	}

	const FGameplayTag OldActive = ActiveSlot;
	ActiveSlot = FGameplayTag();
	if (OldActive.IsValid())
	{
		OnActiveSlotChanged.Broadcast(ActiveSlot, nullptr);
	}
	
	FGameplayTag NextDraw = SwapIncomingSlot;
	if (PendingActivation.IsSet())
	{
		NextDraw = PendingActivation.GetValue();
		PendingActivation.Reset();
	}

	SwapOutgoingSlot = FGameplayTag();

	if (NextDraw.IsValid() && IsSlotOccupied(NextDraw))
	{
		BeginDrawPhase(NextDraw);
		return;
	}
	
	SwapIncomingSlot = FGameplayTag();
	CompleteSwap();
}

void UNexusEquipmentComponent::BeginDrawPhase(FGameplayTag IncomingSlot)
{
	SwapPhase        = ENexusEquipSwapPhase::Drawing;
	SwapIncomingSlot = IncomingSlot;
	SwapOutgoingSlot = FGameplayTag();
	SetSwapTag(true);

	ActiveSlot = IncomingSlot;
	AttachActorForSlotState(IncomingSlot, true);

	UAnimMontage* Equip = nullptr;
	if (const ANexusEquippedActor* InActor = SpawnedActors.FindRef(IncomingSlot))
	{
		Equip = InActor->EquipMontage;
	}
	const float Duration = PlayMontageOnOwner(Equip);

	OnActiveSlotChanged.Broadcast(ActiveSlot, GetEquippedInSlot(ActiveSlot));

	if (Duration > 0.0f)
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(
				PhaseTimer, this,
				&UNexusEquipmentComponent::HandleDrawPhaseFinished,
				Duration, false);
		}
	}
	else
	{
		HandleDrawPhaseFinished();
	}
}

void UNexusEquipmentComponent::HandleDrawPhaseFinished()
{
	SwapIncomingSlot = FGameplayTag();
	CompleteSwap();
	ProcessPendingActivation();
}

void UNexusEquipmentComponent::CompleteSwap()
{
	SwapPhase        = ENexusEquipSwapPhase::Idle;
	SwapOutgoingSlot = FGameplayTag();
	SwapIncomingSlot = FGameplayTag();
	SetSwapTag(false);

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PhaseTimer);
	}
}

void UNexusEquipmentComponent::ProcessPendingActivation()
{
	if (!PendingActivation.IsSet()) return;

	const FGameplayTag Next = PendingActivation.GetValue();
	PendingActivation.Reset();
	
	RequestActivateSlot(Next);
}

void UNexusEquipmentComponent::NotifyHideOutgoingSlot()
{
	if (!OutgoingPendingHide.IsValid()) return;

	const FGameplayTag SlotToHide = OutgoingPendingHide;
	OutgoingPendingHide = FGameplayTag();
	AttachActorForSlotState(SlotToHide, false);
}

void UNexusEquipmentComponent::SetSwapTag(const bool bOn) const
{
	UNexusAbilitySystemComponent* ASC = GetASC();
	if (!ASC) return;

	const bool bAlreadyOn = ASC->HasTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	if (bOn && !bAlreadyOn)
	{
		ASC->AddLooseGameplayTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	}
	else if (!bOn && bAlreadyOn)
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	}
}


// Mounting (effects + spawned actor)
void UNexusEquipmentComponent::ApplyEquipEffects(FGameplayTag SlotTag, UNexusItemInstance* Instance)
{
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	if (!Definition) return;

	const FNexusFragment_Equippable* Eq = Definition->FindFragment<FNexusFragment_Equippable>();
	if (!Eq) return;

	UClass* ActorClass = Eq->EquippedActorClass.Get();
	if (!ActorClass)
	{
		ensureMsgf(Eq->EquippedActorClass.IsNull(),
			TEXT("EquippedActorClass not resident for %s — Equipped bundle was not awaited"),
			*Definition->GetName());
		ActorClass = ANexusEquippedActor::StaticClass();
	}

	if (UWorld* World = GetWorld())
	{
		ANexusEquippedActor* Spawned = World->SpawnActorDeferred<ANexusEquippedActor>(
			ActorClass, FTransform::Identity, GetOwner(), nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (Spawned)
		{
			Spawned->InitializeFromInstance(Instance);
			Spawned->ApplyOwnerViewpointRendering();
			Spawned->FinishSpawning(FTransform::Identity, true);
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

	if (const TObjectPtr<ANexusEquippedActor> Actor = SpawnedActors.FindRef(SlotTag))
	{
		Actor->Destroy();
	}
	SpawnedActors.Remove(SlotTag);

	if (OutgoingPendingHide.MatchesTagExact(SlotTag))
	{
		OutgoingPendingHide = FGameplayTag();
	}
}

void UNexusEquipmentComponent::AttachActorForSlotState(const FGameplayTag SlotTag, const bool bActive) const
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


// Inventory hookup
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
			ClearSlotImmediate(Pair.Key);
		}
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

TArray<FGameplayTag> UNexusEquipmentComponent::GetOccupiedSlots() const
{
	TArray<FGameplayTag> Out;
	EquippedSlots.GetKeys(Out);
	return Out;
}


// Save / Load
void UNexusEquipmentComponent::ComponentPreLoad_Implementation()
{
	ClearAll();
}

void UNexusEquipmentComponent::ComponentLoaded_Implementation()
{
	const FGameplayTag SavedActiveSlot = ActiveSlot;
	ActiveSlot = FGameplayTag();
	
	for (auto It = EquippedSlots.CreateIterator(); It; ++It)
	{
		if (!It.Value()) It.RemoveCurrent();
	}

	TArray<FGameplayTag, TInlineAllocator<4>> Slots;
	EquippedSlots.GetKeys(Slots);

	UAssetManager& AM = UAssetManager::Get();
	for (const FGameplayTag& SlotTag : Slots)
	{
		UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (!Def) continue;
		const FPrimaryAssetId Id = Def->GetPrimaryAssetId();
		if (!Id.IsValid()) continue;

		if (TSharedPtr<FStreamableHandle> Handle = AM.LoadPrimaryAsset(
			Id, TArray<FName>{ TEXT("Equipped") }))
		{
			EquippableLoadHandles.Add(Instance, Handle);
		}
	}
	for (const TPair<TObjectPtr<UNexusItemInstance>, TSharedPtr<FStreamableHandle>>& Pair : EquippableLoadHandles)
	{
		if (Pair.Value.IsValid() && !Pair.Value->HasLoadCompleted())
		{
			Pair.Value->WaitUntilComplete();
		}
	}

	for (const FGameplayTag& SlotTag : Slots)
	{
		if (UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag))
		{
			ApplyEquipEffects(SlotTag, Instance);
			AttachActorForSlotState(SlotTag, false);
			OnSlotAssigned.Broadcast(SlotTag, Instance);
		}
	}

	if (SavedActiveSlot.IsValid() && EquippedSlots.Contains(SavedActiveSlot))
	{
		ActiveSlot = SavedActiveSlot;
		AttachActorForSlotState(SavedActiveSlot, true);
	}

	OnActiveSlotChanged.Broadcast(ActiveSlot, GetEquippedInSlot(ActiveSlot));
}