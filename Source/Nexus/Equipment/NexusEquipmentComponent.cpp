#include "NexusEquipmentComponent.h"

#include "Engine/AssetManager.h"

#include "GameFramework/Character.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/World.h"
#include "Engine/World.h"

#include "TimerManager.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"

#include "NexusEquippedActor.h"
#include "Nexus/NexusAssetManager.h"
#include "Nexus/Character/NexusCharacterBase.h"
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
	UnbindPhaseMontage();

	OutgoingPendingHide = FGameplayTag();
	PendingActivation.Reset();
	PendingActivationsAfterAssignment.Empty();
	PendingUnholsterActionTag = FGameplayTag();
	SlotPendingClear = FGameplayTag();
	SwapPhase = ENexusEquipSwapPhase::Idle;
	SwapOutgoingSlot = FGameplayTag();
	SwapIncomingSlot = FGameplayTag();
	LastActiveSlot = FGameplayTag();

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

	// We don't need to own residency — the instance already pins the Equipped
	// bundle. This load exists only to deliver OnReady; the handle is held just
	// long enough to keep the async request alive until the callback, then dropped
	// in FinalizeAssignment (or ClearSlotImmediate if the slot is torn down first).
	UAssetManager& AM = UAssetManager::Get();
	const TSharedPtr<FStreamableHandle> Handle = AM.LoadPrimaryAsset(
		AssetId, TArray<FName>{ UNexusAssetManager::BundleEquipped }, OnReady);
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

	// The Equipped bundle is kept resident by the item instance for its whole
	// lifetime (UNexusItemInstance::RequestEquippedBundleLoad, and EquippedSlots
	// holds a hard ref so the instance can't be GC'd while slotted). Our streamable
	// handle existed only to fire this completion callback — drop it now instead of
	// holding a second, redundant residency pin for the slot's entire occupancy.
	EquippableLoadHandles.Remove(Instance);

	// Drain any AssignAndActivate calls that were waiting on this slot's actor
	// to spawn. Runs after the broadcast so external listeners see the assigned
	// state first; the activation that follows is purely the caller's queued intent.
	DrainPendingActivationsAfterAssignment(SlotTag);
}

bool UNexusEquipmentComponent::AssignAndActivate(UNexusItemInstance* Instance, FGameplayTag SlotTag,
	FGameplayTag UnholsterActionTag)
{
	if (!Instance || !SlotTag.IsValid()) return false;

	// AssignToSlot can trigger ClearSlotImmediate on the previous occupant, which
	// scrubs pending activations for this slot — so we add our queue entry AFTER
	// AssignToSlot returns. The downside: if the streamable callback fired inline
	// (synchronously-resident asset), FinalizeAssignment already drained an empty
	// queue. The DrainPendingActivationsAfterAssignment(SlotTag) call at the end
	// picks up our just-added entry in that case.
	if (!AssignToSlot(Instance, SlotTag)) return false;

	// Latest call wins — if a previous AssignAndActivate for this slot was still
	// queued, drop it so we don't double-activate when the load finishes.
	PendingActivationsAfterAssignment.RemoveAll([SlotTag](const FPendingActivation& P)
	{
		return P.SlotTag.MatchesTagExact(SlotTag);
	});
	PendingActivationsAfterAssignment.Add({ SlotTag, UnholsterActionTag });

	DrainPendingActivationsAfterAssignment(SlotTag);
	return true;
}

void UNexusEquipmentComponent::DrainPendingActivationsAfterAssignment(FGameplayTag SlotTag)
{
	if (!SpawnedActors.Contains(SlotTag)) return;

	// Reverse iteration so RemoveAt indices stay valid; activations within the
	// queue for this slot are deduped by AssignAndActivate, so there's at most
	// one in practice — the loop is defensive.
	for (int32 i = PendingActivationsAfterAssignment.Num() - 1; i >= 0; --i)
	{
		if (!PendingActivationsAfterAssignment[i].SlotTag.MatchesTagExact(SlotTag)) continue;

		const FGameplayTag Action = PendingActivationsAfterAssignment[i].UnholsterActionTag;
		PendingActivationsAfterAssignment.RemoveAt(i);
		RequestActivateSlot(SlotTag, Action);
	}
}

FGameplayTag UNexusEquipmentComponent::PickAutoAssignSlot(const UNexusItemInstance* Instance) const
{
	if (!Instance) return FGameplayTag();

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	const FNexusFragment_Equippable* Eq = Definition
		? Definition->FindFragment<FNexusFragment_Equippable>() : nullptr;
	if (!Eq) return FGameplayTag();

	// Definition-level veto: items flagged bAllowAutoAssign=false refuse to be
	// silently slotted by *any* caller (pickup, library, debug). Manual UI-
	// driven AssignToSlot still works — this only gates the auto-equip flow.
	if (!Eq->bAllowAutoAssign) return FGameplayTag();

	// Prefer the authored slot when it's currently free. Don't kick out an
	// existing occupant — silent replacement on every pickup would destroy
	// player loadout choices.
	if (Eq->PreferredSlot.IsValid()
		&& CanAssignToSlot(Instance, Eq->PreferredSlot)
		&& !IsSlotOccupied(Eq->PreferredSlot))
	{
		return Eq->PreferredSlot;
	}

	// Fall back to the first compatible free slot. If none is free, the caller
	// gets an invalid tag — the item stays in inventory and the player can
	// swap it in manually.
	for (const FGameplayTag& Slot : GetCompatibleSlotsForInstance(Instance))
	{
		if (!IsSlotOccupied(Slot))
		{
			return Slot;
		}
	}
	return FGameplayTag();
}

bool UNexusEquipmentComponent::ClearSlot(FGameplayTag SlotTag)
{
	UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
	if (!Instance) return false;

	// Non-active slot: nothing on the player's mesh to animate — snap.
	if (!ActiveSlot.MatchesTagExact(SlotTag))
	{
		return ClearSlotImmediate(SlotTag);
	}

	// Active slot: defer the actual removal until the holster montage finishes
	// so the player sees the gun being stowed. SlotPendingClear is the marker
	// HandleHolsterPhaseFinished consults to convert the holster into a clear
	// instead of an idle-empty state.
	SlotPendingClear = SlotTag;

	// A queued activation for this very slot would otherwise win after the
	// holster runs and immediately re-spawn what we just told to leave —
	// drop it. Other queued activations (a slot the player WANTS to draw to
	// after this clear) remain.
	if (PendingActivation.IsSet() && PendingActivation->SlotTag.MatchesTagExact(SlotTag))
	{
		PendingActivation.Reset();
	}

	// Route through the same swap-lock discipline as RequestActivateSlot /
	// RequestHolster rather than yanking the FSM out from under an in-progress
	// montage (the old code called BeginSlotTransition directly even mid-draw,
	// replacing the draw timer and interrupting the animation):
	//   - Idle: start the holster-to-clear now.
	//   - Already holstering this slot: HandleHolsterPhaseFinished will honor
	//     SlotPendingClear, so there's nothing to kick off.
	//   - Any other in-flight phase (drawing this slot): queue a holster so the
	//     weapon finishes its current animation, then gets stowed and cleared via
	//     SlotPendingClear when the phase completes.
	if (SwapPhase == ENexusEquipSwapPhase::Idle)
	{
		BeginSlotTransition(SlotTag, FGameplayTag());
	}
	else if (!(SwapPhase == ENexusEquipSwapPhase::Holstering && SwapOutgoingSlot.MatchesTagExact(SlotTag)))
	{
		PendingActivation = FPendingActivation{ FGameplayTag(), FGameplayTag() };
	}
	return true;
}

bool UNexusEquipmentComponent::ClearSlotImmediate(FGameplayTag SlotTag)
{
	UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
	if (!Instance) return false;

	// If this slot had an animated-clear deferred via ClearSlot(), we're
	// handling the actual removal now — drop the marker so a later, unrelated
	// holster phase can't pick it up and clear an innocent slot.
	if (SlotPendingClear.MatchesTagExact(SlotTag))
	{
		SlotPendingClear = FGameplayTag();
	}

	// A cleared slot can no longer be the quick-swap-to-previous target.
	if (LastActiveSlot.MatchesTagExact(SlotTag))
	{
		LastActiveSlot = FGameplayTag();
	}

	const bool bWasActive = ActiveSlot.MatchesTagExact(SlotTag);

	// Drop any AssignAndActivate calls still waiting for this slot's actor —
	// the instance is gone, the deferred activation would land on whatever
	// (if anything) is assigned next.
	PendingActivationsAfterAssignment.RemoveAll([SlotTag](const FPendingActivation& P)
	{
		return P.SlotTag.MatchesTagExact(SlotTag);
	});

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
			UnbindPhaseMontage();
			SwapPhase = ENexusEquipSwapPhase::Idle;
			SwapOutgoingSlot = FGameplayTag();
			SwapIncomingSlot = FGameplayTag();
			SetSwapTag(false);

			// The aborted swap's queued input is now dead. Left set, a PendingActivation
			// would linger and fire on the next unrelated holster completion — a weapon
			// drawing itself with no player input. Drop it with the FSM reset.
			PendingActivation.Reset();
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

	// Remember which instance is in the player's hands. ClearSlotImmediate (below)
	// deactivates the active slot, so without re-activating afterward the moved
	// weapon would silently vanish from the player's hands — the header contract
	// for a loadout reorder doesn't say "and you lose your drawn weapon."
	const UNexusItemInstance* ActiveInst = GetEquippedInSlot(ActiveSlot);

	ClearSlotImmediate(FromSlot);
	if (ToInst)
	{
		ClearSlotImmediate(ToSlot);
	}

	// Re-assign each instance to its destination, re-activating whichever one was
	// active so the player keeps (a redraw of) the weapon they had equipped.
	// AssignAndActivate waits on the async actor spawn before drawing.
	auto AssignPreservingActive = [this, ActiveInst](UNexusItemInstance* Inst, const FGameplayTag Slot) -> bool
	{
		if (!Inst) return true;
		return Inst == ActiveInst
			? AssignAndActivate(Inst, Slot)
			: AssignToSlot(Inst, Slot);
	};

	const bool bMovedFrom = AssignPreservingActive(FromInst, ToSlot);
	const bool bMovedTo   = AssignPreservingActive(ToInst, FromSlot);
	return bMovedFrom && bMovedTo;
}

bool UNexusEquipmentComponent::RequestActivateLastSlot()
{
	if (!LastActiveSlot.IsValid()) return false;
	if (LastActiveSlot.MatchesTagExact(ActiveSlot)) return false;
	if (!IsSlotOccupied(LastActiveSlot)) return false;

	// Defer to the normal activation path — it owns the swap-lock queueing, the
	// "already active → holster" shortcut, and the draw montage. LastActiveSlot is
	// re-captured by BeginHolsterPhase as this swap stows the current weapon, so a
	// second press toggles straight back.
	return RequestActivateSlot(LastActiveSlot);
}


// Activation (input-driven)
bool UNexusEquipmentComponent::RequestActivateSlot(const FGameplayTag SlotTag,
	const FGameplayTag UnholsterActionTag)
{
	if (!SlotTag.IsValid())
	{
		return RequestHolster();
	}

	if (!IsValidSlot(SlotTag)) return false;

	if (SwapPhase != ENexusEquipSwapPhase::Idle)
	{
		PendingActivation = FPendingActivation{ SlotTag, UnholsterActionTag };
		return true;
	}

	if (ActiveSlot.MatchesTagExact(SlotTag))
	{
		return RequestHolster();
	}

	if (!IsSlotOccupied(SlotTag)) return false;

	PendingUnholsterActionTag = UnholsterActionTag;
	BeginSlotTransition(ActiveSlot, SlotTag);
	return true;
}

bool UNexusEquipmentComponent::RequestHolster()
{
	if (SwapPhase != ENexusEquipSwapPhase::Idle)
	{
		PendingActivation = FPendingActivation{ FGameplayTag(), FGameplayTag() };
		return true;
	}

	if (!ActiveSlot.IsValid()) return false;

	BeginSlotTransition(ActiveSlot, FGameplayTag());
	return true;
}


// Transition state machine
void UNexusEquipmentComponent::BeginSlotTransition(const FGameplayTag OutgoingSlot, const FGameplayTag IncomingSlot)
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

void UNexusEquipmentComponent::BeginHolsterPhase(const FGameplayTag OutgoingSlot, const  FGameplayTag IncomingSlot)
{
	SwapPhase        = ENexusEquipSwapPhase::Holstering;
	SwapOutgoingSlot = OutgoingSlot;
	SwapIncomingSlot = IncomingSlot;
	SetSwapTag(true);

	// The weapon being stowed becomes the quick-swap-to-previous target.
	if (OutgoingSlot.IsValid())
	{
		LastActiveSlot = OutgoingSlot;
	}

	UAnimMontage* Unequip = nullptr;
	if (const ANexusEquippedActor* OutActor = SpawnedActors.FindRef(OutgoingSlot))
	{
		Unequip = OutActor->GetEffectiveArmsMontage(NexusGameplayTags::Action_Equipment_Holster);
	}
	const float Duration = PlayPhaseMontage(Unequip);

	UWorld* World = GetWorld();
	if (Duration > 0.0f && World)
	{
		// Completion is driven by the montage's end delegate (HandlePhaseMontageEnded)
		// so an early blend-out completes the phase immediately; PhaseTimer is the
		// fallback if that delegate never fires.
		OutgoingPendingHide = OutgoingSlot;
		World->GetTimerManager().SetTimer(
			PhaseTimer, this,
			&UNexusEquipmentComponent::HandleHolsterPhaseFinished,
			Duration, false);
		return;
	}

	// No montage (or no world to schedule the fallback timer): hide and finish now.
	// Without the world guard a Duration>0 montage with no timer would latch us in
	// Holstering forever with the Swapping tag stuck on.
	AttachActorForSlotState(OutgoingSlot, false);
	HandleHolsterPhaseFinished();
}

void UNexusEquipmentComponent::HandleHolsterPhaseFinished()
{
	if (OutgoingPendingHide.IsValid())
	{
		AttachActorForSlotState(OutgoingPendingHide, false);
		OutgoingPendingHide = FGameplayTag();
	}

	// Honor a deferred clear from ClearSlot(active): drop the slot entirely now
	// that the player has seen the holster montage play. ClearSlotImmediate
	// handles ActiveSlot reset, swap-state cleanup, and the OnActiveSlotChanged
	// + OnSlotCleared broadcasts in one pass — must run BEFORE we decide on the
	// next draw, or a queued activation could re-occupy the slot we just told
	// to clear.
	if (SlotPendingClear.IsValid())
	{
		const FGameplayTag SlotToClear = SlotPendingClear;
		SlotPendingClear = FGameplayTag();
		ClearSlotImmediate(SlotToClear);
	}
	else
	{
		const FGameplayTag OldActive = ActiveSlot;
		ActiveSlot = FGameplayTag();
		if (OldActive.IsValid())
		{
			OnActiveSlotChanged.Broadcast(ActiveSlot, nullptr);
		}
	}

	FGameplayTag NextDraw = SwapIncomingSlot;
	if (PendingActivation.IsSet())
	{
		// Queued activation supersedes the swap's original incoming slot AND its
		// authored action tag. With nothing queued, PendingUnholsterActionTag
		// stays as the original RequestActivateSlot caller's value — don't
		// overwrite it with default-constructed-invalid.
		NextDraw = PendingActivation->SlotTag;
		PendingUnholsterActionTag = PendingActivation->UnholsterActionTag;
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

void UNexusEquipmentComponent::BeginDrawPhase(const  FGameplayTag IncomingSlot)
{
	SwapPhase        = ENexusEquipSwapPhase::Drawing;
	SwapIncomingSlot = IncomingSlot;
	SwapOutgoingSlot = FGameplayTag();
	SetSwapTag(true);

	ActiveSlot = IncomingSlot;
	AttachActorForSlotState(IncomingSlot, true);

	OnActiveSlotChanged.Broadcast(ActiveSlot, GetEquippedInSlot(ActiveSlot));

	// Consume the action-tag override; it's a one-shot. Invalid → standard unholster.
	const FGameplayTag RequestedAction = PendingUnholsterActionTag;
	PendingUnholsterActionTag = FGameplayTag();

	UAnimMontage* Equip = nullptr;
	if (const ANexusEquippedActor* InActor = SpawnedActors.FindRef(IncomingSlot))
	{
		const FGameplayTag PrimaryTag = RequestedAction.IsValid()
			? RequestedAction
			: NexusGameplayTags::Action_Equipment_Unholster;

		Equip = InActor->GetEffectiveArmsMontage(PrimaryTag);

		// Caller-requested overrides fall back to the standard unholster so an
		// item that doesn't author (e.g.) a Ceremony anim still draws normally
		// instead of silently producing no animation. Action.Equipment.Unholster
		// has no fallback — if it's missing, the draw phase finishes without anim.
		if (!Equip && RequestedAction.IsValid()
			&& !RequestedAction.MatchesTagExact(NexusGameplayTags::Action_Equipment_Unholster))
		{
			Equip = InActor->GetEffectiveArmsMontage(NexusGameplayTags::Action_Equipment_Unholster);
		}
	}
	const float Duration = PlayPhaseMontage(Equip);

	UWorld* World = GetWorld();
	if (Duration > 0.0f && World)
	{
		// Montage end delegate drives completion; PhaseTimer is the fallback.
		World->GetTimerManager().SetTimer(
			PhaseTimer, this,
			&UNexusEquipmentComponent::HandleDrawPhaseFinished,
			Duration, false);
		return;
	}

	// No montage (or no world for the fallback timer): complete now rather than
	// latch in Drawing with the Swapping tag (and the Fire/Reload lockout) stuck on.
	HandleDrawPhaseFinished();
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

	UnbindPhaseMontage();

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PhaseTimer);
	}
}

void UNexusEquipmentComponent::ProcessPendingActivation()
{
	if (!PendingActivation.IsSet()) return;

	const FPendingActivation Next = PendingActivation.GetValue();
	PendingActivation.Reset();

	RequestActivateSlot(Next.SlotTag, Next.UnholsterActionTag);
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

	// Idempotent guard: ApplyEquipEffects must run exactly once per slot occupancy.
	// If anything already applied effects for this slot (a future double-finalize,
	// a restore over a populated slot), tear them down first so we never orphan the
	// prior actor or stack a second ability grant / tag push.
	if (SpawnedActors.Contains(SlotTag)
		|| AppliedAbilitiesBySlot.Contains(SlotTag)
		|| AppliedTagsBySlot.Contains(SlotTag))
	{
		RemoveEquipEffects(SlotTag);
	}

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

float UNexusEquipmentComponent::PlayPhaseMontage(UAnimMontage* Montage)
{
	// Drop any prior phase binding before we (maybe) make a new one.
	UnbindPhaseMontage();

	if (!Montage) return 0.0f;

	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return 0.0f;

	USkeletalMeshComponent* Mesh = Character->GetMesh();
	if (!Mesh) return 0.0f;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance) return 0.0f;

	const float Length = AnimInstance->Montage_Play(Montage);
	if (Length > 0.0f)
	{
		// Bind the montage's end so phase completion tracks the *actual* animation,
		// not a wall-clock timer. An interrupting montage (hit react, stagger) blends
		// this out early and fires OnMontageEnded(bInterrupted=true), which completes
		// the phase right away instead of holding the Swapping lockout for the full
		// nominal length. OnMontageEnded is multicast across all montages on this
		// instance — HandlePhaseMontageEnded filters to the one we're waiting on.
		SwapMontageAnimInstance = AnimInstance;
		SwapMontage             = Montage;
		AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UNexusEquipmentComponent::HandlePhaseMontageEnded);
	}
	return Length;
}

void UNexusEquipmentComponent::UnbindPhaseMontage()
{
	if (UAnimInstance* AnimInstance = SwapMontageAnimInstance.Get())
	{
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &UNexusEquipmentComponent::HandlePhaseMontageEnded);
	}
	SwapMontageAnimInstance = nullptr;
	SwapMontage             = nullptr;
}

void UNexusEquipmentComponent::HandlePhaseMontageEnded(UAnimMontage* Montage, bool /*bInterrupted*/)
{
	// Ignore montages we're not waiting on (this delegate fires for every montage
	// on the owner mesh — reloads, fires, a stale prior phase that the timer fallback
	// already completed). Whether the end was natural or an interrupt, the phase is
	// done: the weapon is in hand / stowed, so stop blocking combat.
	if (Montage == nullptr || Montage != SwapMontage.Get()) return;

	UnbindPhaseMontage();
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PhaseTimer);
	}

	if (SwapPhase == ENexusEquipSwapPhase::Holstering)
	{
		HandleHolsterPhaseFinished();
	}
	else if (SwapPhase == ENexusEquipSwapPhase::Drawing)
	{
		HandleDrawPhaseFinished();
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

	const ANexusCharacterBase* Character = Cast<ANexusCharacterBase>(GetOwner());
	if (!Character) return;
	USkeletalMeshComponent* CharacterMesh = Character->GetEquipmentAttachMesh();
	if (!CharacterMesh) return;

	Actor->AttachToComponent(CharacterMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, Eq->AttachSocket);
	Actor->SetEquippedVisibility(true);
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
// Save / Load
void UNexusEquipmentComponent::ComponentPreSave_Implementation()
{
	// EquippedSlots holds runtime instance pointers that cannot round-trip through
	// EMS. Persist the stable per-instance GUIDs instead; ResolveEquippedFromSave
	// rebuilds the pointer map on load by looking each GUID up in the inventory.
	SavedSlotGuids.Reset();
	for (const TPair<FGameplayTag, TObjectPtr<UNexusItemInstance>>& Pair : EquippedSlots)
	{
		if (Pair.Value)
		{
			SavedSlotGuids.Add(Pair.Key, Pair.Value->GetInstanceGuid());
		}
	}
}

void UNexusEquipmentComponent::ComponentPreLoad_Implementation()
{
	ClearAll();
}

void UNexusEquipmentComponent::ComponentLoaded_Implementation()
{
	// The equipped instances are owned by the inventory, which rebuilds them in its
	// own ComponentLoaded. Defer resolution one tick so it runs after the inventory
	// restore regardless of EMS component load order. ActiveSlot and SavedSlotGuids
	// were just restored by EMS and persist until the deferred pass consumes them.
	PendingRestoreActiveSlot = ActiveSlot;
	ActiveSlot = FGameplayTag();
	EquippedSlots.Reset();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimerForNextTick(this, &UNexusEquipmentComponent::ResolveEquippedFromSave);
	}
	else
	{
		ResolveEquippedFromSave();
	}
}

void UNexusEquipmentComponent::ResolveEquippedFromSave()
{
	const FGameplayTag SavedActiveSlot = PendingRestoreActiveSlot;
	PendingRestoreActiveSlot = FGameplayTag();

	if (const UNexusInventoryComponent* Inventory = GetInventory())
	{
		for (const TPair<FGameplayTag, FGuid>& Pair : SavedSlotGuids)
		{
			// A null result means the inventory dropped the item (e.g. its definition
			// was removed from the build); skip the slot rather than restore an empty one.
			if (UNexusItemInstance* Instance = Inventory->FindInstanceByGuid(Pair.Value))
			{
				EquippedSlots.Add(Pair.Key, Instance);
			}
		}
	}
	SavedSlotGuids.Reset();

	TArray<FGameplayTag, TInlineAllocator<4>> Slots;
	EquippedSlots.GetKeys(Slots);

	// Residency is already owned by the item instances — LoadFromSaveData re-issued
	// each one's Equipped-bundle pin. We only need the bundle *finished* before we
	// spawn actors, so kick a load to get a handle to wait on, then let the handle
	// drop at the end of this scope. Keeping these in EquippableLoadHandles would
	// duplicate the instance's pin for the slot's whole occupancy.
	UAssetManager& AM = UAssetManager::Get();
	TArray<TSharedPtr<FStreamableHandle>, TInlineAllocator<4>> PendingHandles;
	for (const FGameplayTag& SlotTag : Slots)
	{
		UNexusItemInstance* Instance = EquippedSlots.FindRef(SlotTag);
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (!Def) continue;
		const FPrimaryAssetId Id = Def->GetPrimaryAssetId();
		if (!Id.IsValid()) continue;

		if (TSharedPtr<FStreamableHandle> Handle = AM.LoadPrimaryAsset(
			Id, TArray<FName>{ UNexusAssetManager::BundleEquipped }))
		{
			PendingHandles.Add(Handle);
		}
	}
	for (const TSharedPtr<FStreamableHandle>& Handle : PendingHandles)
	{
		if (Handle.IsValid() && !Handle->HasLoadCompleted())
		{
			Handle->WaitUntilComplete();
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