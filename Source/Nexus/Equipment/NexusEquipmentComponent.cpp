#include "NexusEquipmentComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Components/SkeletalMeshComponent.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "NexusEquippedActor.h"
#include "NexusEquipmentInterface.h"
#include "NexusEquipmentLoadout.h"
#include "Nexus/Nexus.h"
#include "Nexus/NexusAssetManager.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/AbilitySystem/NexusAbility.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "GameFramework/Pawn.h"

#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "Nexus/Inventory/Fragments/PassiveEquipment/NexusFragment_PassiveEquipment.h"
#include "Nexus/Inventory/Fragments/Charm/NexusFragment_Charm.h"

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
		Inventory->OnEquippedCaseChanged.AddDynamic(this, &UNexusEquipmentComponent::HandleEquippedCaseChanged);
		// Sync against whatever case state already exists (covers BeginPlay order vs the
		// inventory equipping its default case).
		RefreshCharms();
	}

	// Apply starter gear on the next tick so the inventory (and any EMS restore) has
	// settled first. ComponentLoaded sets bStarterApplied on a save-restore, which
	// suppresses this so a loaded game doesn't double up its starting loadout.
	if (StarterEquipment.Num() > 0)
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimerForNextTick(this, &UNexusEquipmentComponent::ApplyStarterEquipment);
		}
	}
}

void UNexusEquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UNexusInventoryComponent* Inventory = GetInventory())
	{
		Inventory->OnItemRemoved.RemoveDynamic(this, &UNexusEquipmentComponent::HandleInventoryItemRemoved);
		Inventory->OnEquippedCaseChanged.RemoveDynamic(this, &UNexusEquipmentComponent::HandleEquippedCaseChanged);
	}

	// Drop any charm grants so we don't leave abilities/tags on the ASC after teardown.
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		for (const TSubclassOf<UNexusAbility>& Ability : GrantedCharmAbilities)
		{
			if (Ability) ASC->RemoveAbility(Ability);
		}
		for (const FGameplayTag& Tag : GrantedCharmTags)
		{
			ASC->RemoveLooseGameplayTag(Tag);
		}
	}
	GrantedCharmTags.Reset();
	GrantedCharmAbilities.Reset();

	PendingActivationsAfterAssignment.Empty();
	SlotPendingClear = FGameplayTag();
	HolsteringSlot   = FGameplayTag();
	PendingDrawSlot  = FGameplayTag();
	LastActiveSlot   = FGameplayTag();

	ClearAll();
	EquippableLoadHandles.Empty();

	Super::EndPlay(EndPlayReason);
}


// Host access — strictly through the interfaces, never a concrete character class.
INexusEquipmentInterface* UNexusEquipmentComponent::GetHost() const
{
	return Cast<INexusEquipmentInterface>(GetOwner());
}

UAnimInstance* UNexusEquipmentComponent::GetHostAnimInstance() const
{
	const INexusEquipmentInterface* Host = GetHost();
	return Host ? Host->GetAnimInstance() : nullptr;
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


// Loadout / slot queries
bool UNexusEquipmentComponent::IsValidSlot(FGameplayTag SlotTag) const
{
	return Loadout && Loadout->HasSlot(SlotTag);
}

bool UNexusEquipmentComponent::IsSlotPassive(FGameplayTag SlotTag) const
{
	const FNexusEquipmentSlotDef* SlotDef = Loadout ? Loadout->FindSlot(SlotTag) : nullptr;
	return SlotDef && SlotDef->bIsPassive;
}

TArray<FGameplayTag> UNexusEquipmentComponent::GetSlots() const
{
	TArray<FGameplayTag> Out;
	if (Loadout)
	{
		Loadout->GetSlotTagsSorted(Out);
	}
	return Out;
}

bool UNexusEquipmentComponent::CanAssignToSlot(const UNexusItemInstance* Instance, FGameplayTag SlotTag) const
{
	if (!Instance) return false;

	const FNexusEquipmentSlotDef* SlotDef = Loadout ? Loadout->FindSlot(SlotTag) : nullptr;
	if (!SlotDef) return false;

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return false;

	// Category filter: the item's category tags must intersect the slot's
	// AcceptedItemTags. An empty AcceptedItemTags is "no category restriction" —
	// accept any item of the slot's mode.
	if (!SlotDef->AcceptedItemTags.IsEmpty()
		&& !Definition->CategoryTags.HasAny(SlotDef->AcceptedItemTags))
	{
		return false;
	}

	// Mode routing: the fragment decides which slot mode an item belongs to.
	if (SlotDef->bIsPassive)
	{
		return Definition->HasFragment<FNexusFragment_PassiveEquipment>();
	}
	return Definition->HasFragment<FNexusFragment_Equippable>();
}

TArray<FGameplayTag> UNexusEquipmentComponent::GetCompatibleSlotsForInstance(const UNexusItemInstance* Instance) const
{
	TArray<FGameplayTag> Out;
	if (!Instance) return Out;

	for (const FGameplayTag& Slot : GetSlots())
	{
		if (CanAssignToSlot(Instance, Slot))
		{
			Out.Add(Slot);
		}
	}
	return Out;
}

FGameplayTag UNexusEquipmentComponent::PickAutoAssignSlot(const UNexusItemInstance* Instance) const
{
	if (!Instance) return FGameplayTag();

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	const FNexusFragment_Equippable* Eq = Definition
		? Definition->FindFragment<FNexusFragment_Equippable>() : nullptr;
	if (!Eq) return FGameplayTag();          // auto-equip is an in-hand concern

	// Definition-level veto: items flagged bAllowAutoAssign=false refuse silent slotting.
	if (!Eq->bAllowAutoAssign) return FGameplayTag();

	// Prefer the authored slot when it's free; never evict an existing occupant.
	if (Eq->PreferredSlot.IsValid()
		&& CanAssignToSlot(Instance, Eq->PreferredSlot)
		&& !IsSlotOccupied(Eq->PreferredSlot))
	{
		return Eq->PreferredSlot;
	}

	for (const FGameplayTag& Slot : GetCompatibleSlotsForInstance(Instance))
	{
		if (!IsSlotOccupied(Slot))
		{
			return Slot;
		}
	}
	return FGameplayTag();
}


// Assignment
bool UNexusEquipmentComponent::AssignItemToSlot(FGameplayTag SlotTag, UNexusItemInstance* Instance)
{
	if (!CanAssignToSlot(Instance, SlotTag))
	{
		UE_LOG(LogNexusEquipment, Warning,
			TEXT("[Equipment] Rejected %s -> slot %s: incompatible (item category doesn't intersect "
				 "the slot's AcceptedItemTags, the slot mode doesn't match the item's fragment, or the "
				 "slot isn't in this loadout)."),
			*GetNameSafe(Instance ? Instance->GetDefinition() : nullptr),
			*SlotTag.ToString());
		return false;
	}

	if (const FNexusEquipmentSlotState* Existing = SlotStates.Find(SlotTag))
	{
		if (Existing->Assigned == Instance) return true; // already here — no-op
		ClearSlotImmediate(SlotTag);
	}

	// An instance lives in at most one slot — pull it out of any other slot first.
	{
		TArray<FGameplayTag> PriorSlots;
		for (const TPair<FGameplayTag, FNexusEquipmentSlotState>& Pair : SlotStates)
		{
			if (Pair.Value.Assigned == Instance) PriorSlots.Add(Pair.Key);
		}
		for (const FGameplayTag& Prior : PriorSlots) ClearSlotImmediate(Prior);
	}

	const bool bPassive = IsSlotPassive(SlotTag);

	FNexusEquipmentSlotState& State = SlotStates.Add(SlotTag);
	State.Assigned = Instance;
	State.bPassive = bPassive;
	State.Phase    = EEquipmentSlotPhase::Idle;

	if (bPassive)
	{
		// Passive short-circuit: apply effects and announce immediately. No actor
		// spawn, no Equipped-bundle load, no montage — this is how armor / charm items work.
		ApplySlotEffects(SlotTag, State);
		OnSlotAssigned.Broadcast(SlotTag, Instance);
		return true;
	}

	// In-hand: load the Equipped bundle, then FinalizeInHandAssignment spawns the
	// actor and grants effects. The slot is "occupied" the moment it's in SlotStates,
	// even before the async actor exists.
	TWeakObjectPtr<UNexusEquipmentComponent> WeakSelf(this);
	TWeakObjectPtr<UNexusItemInstance> WeakInstance(Instance);
	const FStreamableDelegate OnReady = FStreamableDelegate::CreateLambda(
		[WeakSelf, WeakInstance, SlotTag]()
		{
			UNexusEquipmentComponent* Self = WeakSelf.Get();
			UNexusItemInstance* Inst = WeakInstance.Get();
			if (!Self || !Inst) return;
			const FNexusEquipmentSlotState* S = Self->SlotStates.Find(SlotTag);
			if (!S || S->Assigned != Inst) return; // slot changed under us while loading
			Self->FinalizeInHandAssignment(SlotTag, Inst);
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

void UNexusEquipmentComponent::FinalizeInHandAssignment(FGameplayTag SlotTag, UNexusItemInstance* Instance)
{
	FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	if (!State || State->Assigned != Instance) return;

	// Already finalized (a duplicate streamable callback, or a re-entrant finalize):
	// the actor exists, so don't spawn/grant a second time — just drain any waiting
	// activation. This is the guard that stops "holster + unholster spawns two".
	if (State->InWorld)
	{
		DrainPendingActivationsAfterAssignment(SlotTag);
		return;
	}

	ApplySlotEffects(SlotTag, *State);       // spawns the actor + grants abilities/tags
	AttachActorForSlotState(SlotTag, false); // mounted but hidden until drawn

	OnSlotAssigned.Broadcast(SlotTag, Instance);

	// Drain any AssignAndActivate that was waiting on this slot's actor to spawn.
	DrainPendingActivationsAfterAssignment(SlotTag);
}

void UNexusEquipmentComponent::ApplySlotEffects(FGameplayTag SlotTag, FNexusEquipmentSlotState& State)
{
	UNexusItemInstance* Instance = State.Assigned;
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	if (!Definition) return;

	TArray<TSubclassOf<UNexusAbility>> AbilitiesToGrant;
	FGameplayTagContainer TagsToApply;
	TagsToApply.AddTag(SlotTag); // a loose tag marking the slot occupied

	if (State.bPassive)
	{
		if (const FNexusFragment_PassiveEquipment* Passive = Definition->FindFragment<FNexusFragment_PassiveEquipment>())
		{
			AbilitiesToGrant = Passive->GrantedAbilities;
			TagsToApply.AppendTags(Passive->GrantedTags);
		}
	}
	else
	{
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

		// Never spawn a second actor for a slot that already has one.
		if (!State.InWorld)
		{
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
					State.InWorld = Spawned;
				}
			}
		}

		AbilitiesToGrant = Eq->GrantedAbilities;
		TagsToApply.AppendTags(Eq->OwnedTagsWhileEquipped);
	}

	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		for (const TSubclassOf<UNexusAbility>& AbilityClass : AbilitiesToGrant)
		{
			if (AbilityClass && ASC->GiveAbility(AbilityClass))
			{
				State.GrantedAbilities.Add(AbilityClass);
			}
		}
		for (const FGameplayTag& Tag : TagsToApply)
		{
			ASC->AddLooseGameplayTag(Tag);
		}
		State.GrantedTags = TagsToApply;
	}
}

void UNexusEquipmentComponent::RemoveSlotEffects(FNexusEquipmentSlotState& State)
{
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		for (const TSubclassOf<UNexusAbility>& AbilityClass : State.GrantedAbilities)
		{
			if (AbilityClass) ASC->RemoveAbility(AbilityClass);
		}
		for (const FGameplayTag& Tag : State.GrantedTags)
		{
			ASC->RemoveLooseGameplayTag(Tag);
		}
	}
	State.GrantedAbilities.Reset();
	State.GrantedTags.Reset();

	if (State.InWorld)
	{
		State.InWorld->Destroy();
		State.InWorld = nullptr;
	}
}

void UNexusEquipmentComponent::AttachActorForSlotState(FGameplayTag SlotTag, bool bActive) const
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	ANexusEquippedActor* Actor = State ? State->InWorld : nullptr;
	if (!Actor) return;

	if (!bActive)
	{
		Actor->SetEquippedVisibility(false);
		return;
	}

	const UNexusItemInstance* Instance = State->Assigned;
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	const FNexusFragment_Equippable* Eq = Definition
		? Definition->FindFragment<FNexusFragment_Equippable>() : nullptr;
	if (!Eq) return;

	const INexusEquipmentInterface* Host = GetHost();
	USkeletalMeshComponent* AttachMesh = Host ? Host->GetEquipmentAttachMesh() : nullptr;
	if (!AttachMesh) return;

	Actor->AttachToComponent(AttachMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, Eq->AttachSocket);
	Actor->SetEquippedVisibility(true);
}


// Clearing
bool UNexusEquipmentComponent::ClearSlot(FGameplayTag SlotTag)
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	if (!State || !State->Assigned) return false;

	// Passive or non-active slots have nothing on the host to animate — snap clear.
	if (State->bPassive || !ActiveSlot.MatchesTagExact(SlotTag))
	{
		return ClearSlotImmediate(SlotTag);
	}

	// Active in-hand slot: defer the removal until the holster montage finishes so
	// the wielder sees the weapon stowed. FinishHolsterPhase consults SlotPendingClear.
	SlotPendingClear = SlotTag;

	if (!HolsteringSlot.MatchesTagExact(SlotTag))
	{
		BeginHolsterPhase(SlotTag, FGameplayTag(), EUnholsterStyle::Normal);
	}
	return true;
}

bool UNexusEquipmentComponent::ClearSlotImmediate(FGameplayTag SlotTag)
{
	FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	if (!State || !State->Assigned) return false;

	if (SlotPendingClear.MatchesTagExact(SlotTag)) SlotPendingClear = FGameplayTag();
	if (LastActiveSlot.MatchesTagExact(SlotTag))   LastActiveSlot   = FGameplayTag();

	PendingActivationsAfterAssignment.RemoveAll([SlotTag](const FPendingActivation& P)
	{
		return P.SlotTag.MatchesTagExact(SlotTag);
	});

	UNexusItemInstance* Instance = State->Assigned;
	const bool bWasActive = ActiveSlot.MatchesTagExact(SlotTag);

	RemoveSlotEffects(*State); // removes abilities/tags, destroys the actor
	EquippableLoadHandles.Remove(Instance);

	// Unwind any in-flight transition that referenced this slot.
	if (HolsteringSlot.MatchesTagExact(SlotTag))  HolsteringSlot  = FGameplayTag();
	if (PendingDrawSlot.MatchesTagExact(SlotTag)) PendingDrawSlot = FGameplayTag();

	SlotStates.Remove(SlotTag); // State dangles past this point

	if (bWasActive)
	{
		ActiveSlot = FGameplayTag();
		SetSwapTag(false);
		OnSlotDeactivated.Broadcast(SlotTag, Instance);
	}

	OnSlotCleared.Broadcast(SlotTag, Instance);
	return true;
}

void UNexusEquipmentComponent::ClearAll()
{
	TArray<FGameplayTag> Keys;
	SlotStates.GetKeys(Keys);
	for (const FGameplayTag& Slot : Keys)
	{
		ClearSlotImmediate(Slot);
	}
}

bool UNexusEquipmentComponent::MoveItemBetweenSlots(FGameplayTag FromSlot, FGameplayTag ToSlot)
{
	if (FromSlot.MatchesTagExact(ToSlot)) return false;

	UNexusItemInstance* FromInst = GetAssigned(FromSlot);
	if (!FromInst) return false;
	UNexusItemInstance* ToInst = GetAssigned(ToSlot);

	if (!CanAssignToSlot(FromInst, ToSlot)) return false;
	if (ToInst && !CanAssignToSlot(ToInst, FromSlot)) return false;

	ClearSlotImmediate(FromSlot);
	if (ToInst) ClearSlotImmediate(ToSlot);

	const bool bMovedFrom = AssignItemToSlot(ToSlot, FromInst);
	const bool bMovedTo   = !ToInst || AssignItemToSlot(FromSlot, ToInst);
	return bMovedFrom && bMovedTo;
}

bool UNexusEquipmentComponent::AssignAndActivate(FGameplayTag SlotTag, UNexusItemInstance* Instance, EUnholsterStyle Style)
{
	if (!Instance || !SlotTag.IsValid()) return false;
	if (!AssignItemToSlot(SlotTag, Instance)) return false;

	// Passive slots have no draw — the effect is already applied.
	if (IsSlotPassive(SlotTag)) return true;

	// Latest queued activation for this slot wins.
	PendingActivationsAfterAssignment.RemoveAll([SlotTag](const FPendingActivation& P)
	{
		return P.SlotTag.MatchesTagExact(SlotTag);
	});
	PendingActivationsAfterAssignment.Add({ SlotTag, Style });

	// If the actor was already resident (synchronous load), drain now.
	DrainPendingActivationsAfterAssignment(SlotTag);
	return true;
}

void UNexusEquipmentComponent::DrainPendingActivationsAfterAssignment(FGameplayTag SlotTag)
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	if (!State || !State->InWorld) return; // actor not spawned yet — wait for finalize

	for (int32 i = PendingActivationsAfterAssignment.Num() - 1; i >= 0; --i)
	{
		if (!PendingActivationsAfterAssignment[i].SlotTag.MatchesTagExact(SlotTag)) continue;
		const EUnholsterStyle Style = PendingActivationsAfterAssignment[i].Style;
		PendingActivationsAfterAssignment.RemoveAt(i);
		RequestActivateSlot(SlotTag, Style);
	}
}


// Activation
bool UNexusEquipmentComponent::RequestActivateSlot(FGameplayTag SlotTag, EUnholsterStyle Style)
{
	if (!SlotTag.IsValid()) return RequestDeactivateActiveSlot();
	if (!IsValidSlot(SlotTag)) return false;
	if (IsSlotPassive(SlotTag)) return false; // passive items are always on, never drawn

	// Non-interruptible: a holster/draw always plays to completion. Presses during a
	// transition are dropped (not queued), so spamming an input can't stack actions or
	// cut an animation short.
	if (IsSwapping()) return false;

	if (ActiveSlot.MatchesTagExact(SlotTag) && IsSlotActive(SlotTag))
	{
		return RequestDeactivateActiveSlot(); // pressing the active slot toggles to empty
	}

	if (!IsSlotOccupied(SlotTag)) return false;

	BeginActivate(SlotTag, Style);
	return true;
}

bool UNexusEquipmentComponent::RequestDeactivateActiveSlot()
{
	// Non-interruptible: ignore a holster request while a transition is in flight.
	if (IsSwapping()) return false;
	if (!ActiveSlot.IsValid()) return false;

	BeginHolsterPhase(ActiveSlot, FGameplayTag(), EUnholsterStyle::Normal);
	return true;
}

bool UNexusEquipmentComponent::RequestActivateNextSlot() { return CycleActiveSlot(+1); }
bool UNexusEquipmentComponent::RequestActivatePrevSlot() { return CycleActiveSlot(-1); }

bool UNexusEquipmentComponent::CycleActiveSlot(int32 Direction)
{
	TArray<FGameplayTag> Slots = GetSlots();
	Slots.RemoveAll([this](const FGameplayTag& S) { return IsSlotPassive(S); });
	const int32 Count = Slots.Num();
	if (Count == 0 || Direction == 0) return false;

	const int32 ActiveIdx = Slots.IndexOfByKey(ActiveSlot); // INDEX_NONE when none/invalid
	for (int32 Step = 1; Step <= Count; ++Step)
	{
		int32 Idx;
		if (ActiveIdx == INDEX_NONE)
		{
			Idx = Direction > 0 ? (Step - 1) : (Count - Step);
		}
		else
		{
			Idx = ((ActiveIdx + Direction * Step) % Count + Count) % Count;
		}

		const FGameplayTag& Candidate = Slots[Idx];
		if (IsSlotOccupied(Candidate) && !Candidate.MatchesTagExact(ActiveSlot))
		{
			return RequestActivateSlot(Candidate);
		}
	}
	return false;
}

bool UNexusEquipmentComponent::RequestActivateLastSlot()
{
	if (!LastActiveSlot.IsValid()) return false;
	if (LastActiveSlot.MatchesTagExact(ActiveSlot)) return false;
	if (!IsSlotOccupied(LastActiveSlot)) return false;
	return RequestActivateSlot(LastActiveSlot);
}


// Lifecycle state machine (single active in-hand slot; advances on anim notifies)
void UNexusEquipmentComponent::BeginActivate(FGameplayTag SlotTag, EUnholsterStyle Style)
{
	if (ActiveSlot.IsValid())
	{
		// Swap: stow the current weapon, then draw the requested one.
		BeginHolsterPhase(ActiveSlot, SlotTag, Style);
	}
	else
	{
		BeginDrawPhase(SlotTag, Style);
	}
}

void UNexusEquipmentComponent::BeginHolsterPhase(FGameplayTag OutgoingSlot, FGameplayTag IncomingSlot, EUnholsterStyle IncomingStyle)
{
	HolsteringSlot   = OutgoingSlot;
	PendingDrawSlot  = IncomingSlot;
	PendingDrawStyle = IncomingStyle;

	if (FNexusEquipmentSlotState* State = SlotStates.Find(OutgoingSlot))
	{
		State->Phase = EEquipmentSlotPhase::Holstering;
	}

	// The stowed weapon becomes the quick-swap-to-previous target.
	LastActiveSlot = OutgoingSlot;

	SetSwapTag(true);

	UAnimMontage* Montage = ResolveTransitionMontage(OutgoingSlot, NexusGameplayTags::Action_Equipment_Holster);
	if (UAnimInstance* AnimInstance = GetHostAnimInstance())
	{
		if (Montage && AnimInstance->Montage_Play(Montage) > 0.0f)
		{
			// Advance when the montage starts BLENDING OUT, not when it fully ends: the
			// next montage cross-fades in over the blend-out and the hide lands before the
			// pose resolves to idle, so there's no one-frame idle pop.
			FOnMontageBlendingOutStarted BlendOutDelegate;
			BlendOutDelegate.BindUObject(this, &UNexusEquipmentComponent::HandleHolsterMontageBlendingOut);
			AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, Montage);
			return;
		}
	}

	// No montage authored (or no anim instance): instant transition.
	FinishHolsterPhase();
}

void UNexusEquipmentComponent::FinishHolsterPhase()
{
	if (!HolsteringSlot.IsValid()) return;

	const FGameplayTag OutgoingSlot = HolsteringSlot;
	FNexusEquipmentSlotState* State = SlotStates.Find(OutgoingSlot);
	if (!State || State->Phase != EEquipmentSlotPhase::Holstering)
	{
		// Already advanced (notify and montage-end both fired) — ignore the late call.
		return;
	}

	AttachActorForSlotState(OutgoingSlot, false); // out of view
	State->Phase = EEquipmentSlotPhase::Idle;

	UNexusItemInstance* OutgoingInstance = State->Assigned;

	HolsteringSlot = FGameplayTag();
	ActiveSlot     = FGameplayTag();
	OnSlotDeactivated.Broadcast(OutgoingSlot, OutgoingInstance);

	// Honor a deferred clear requested via ClearSlot() on the active slot.
	if (SlotPendingClear.MatchesTagExact(OutgoingSlot))
	{
		SlotPendingClear = FGameplayTag();
		ClearSlotImmediate(OutgoingSlot);
	}

	// Continue the swap into the incoming draw, if there is one.
	const FGameplayTag   NextSlot  = PendingDrawSlot;
	const EUnholsterStyle NextStyle = PendingDrawStyle;
	PendingDrawSlot = FGameplayTag();

	if (NextSlot.IsValid() && IsSlotOccupied(NextSlot) && !IsSlotPassive(NextSlot))
	{
		BeginDrawPhase(NextSlot, NextStyle);
		return;
	}

	// Settled to empty hands.
	SetSwapTag(false);
}

void UNexusEquipmentComponent::BeginDrawPhase(FGameplayTag IncomingSlot, EUnholsterStyle Style)
{
	ActiveSlot = IncomingSlot;
	if (FNexusEquipmentSlotState* State = SlotStates.Find(IncomingSlot))
	{
		State->Phase = EEquipmentSlotPhase::Unholstering;
	}

	AttachActorForSlotState(IncomingSlot, true); // mount + show
	OnSlotActivated.Broadcast(IncomingSlot, GetAssigned(IncomingSlot));

	SetSwapTag(true); // still locked (no fire / reload) until the draw completes

	const FGameplayTag PrimaryAction = (Style == EUnholsterStyle::Ceremony)
		? NexusGameplayTags::Action_Equipment_Ceremony
		: NexusGameplayTags::Action_Equipment_Unholster;

	UAnimMontage* Montage = ResolveTransitionMontage(IncomingSlot, PrimaryAction);
	// Ceremony falls back to the normal unholster, so an item without a ceremony
	// animation still draws instead of silently producing nothing.
	if (!Montage && Style == EUnholsterStyle::Ceremony)
	{
		Montage = ResolveTransitionMontage(IncomingSlot, NexusGameplayTags::Action_Equipment_Unholster);
	}

	if (UAnimInstance* AnimInstance = GetHostAnimInstance())
	{
		if (Montage && AnimInstance->Montage_Play(Montage) > 0.0f)
		{
			// Blend-out (not end) drives completion — avoids the one-frame idle pop and
			// lets the next transition cross-fade in.
			FOnMontageBlendingOutStarted BlendOutDelegate;
			BlendOutDelegate.BindUObject(this, &UNexusEquipmentComponent::HandleDrawMontageBlendingOut);
			AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, Montage);
			return;
		}
	}

	FinishDrawPhase();
}

void UNexusEquipmentComponent::FinishDrawPhase()
{
	FNexusEquipmentSlotState* State = SlotStates.Find(ActiveSlot);
	if (!State || State->Phase != EEquipmentSlotPhase::Unholstering)
	{
		return; // already advanced — ignore the late call
	}

	State->Phase = EEquipmentSlotPhase::Active;
	SetSwapTag(false); // fire / reload allowed now
}

UAnimMontage* UNexusEquipmentComponent::ResolveTransitionMontage(FGameplayTag SlotTag, FGameplayTag ActionTag) const
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	const ANexusEquippedActor* Actor = State ? State->InWorld : nullptr;
	return Actor ? Actor->GetEffectiveHostMontage(ActionTag) : nullptr;
}

void UNexusEquipmentComponent::HandleHolsterMontageBlendingOut(UAnimMontage* /*Montage*/, bool /*bInterrupted*/)
{
	FinishHolsterPhase(); // guarded internally (phase check)
}

void UNexusEquipmentComponent::HandleDrawMontageBlendingOut(UAnimMontage* /*Montage*/, bool /*bInterrupted*/)
{
	FinishDrawPhase(); // guarded internally (phase check)
}

void UNexusEquipmentComponent::SetSwapTag(bool bOn) const
{
	UNexusAbilitySystemComponent* ASC = GetASC();
	if (!ASC) return;

	const bool bAlreadyOn = ASC->HasTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	if (bOn && !bAlreadyOn)
	{
		ASC->AddLooseGameplayTag(NexusGameplayTags::Character_State_Weapon_Swapping);
		// A swap interrupts an in-flight reload so its timer can't transfer ammo after
		// the weapon has left the hands.
		ASC->ForceEndAbilityByTag(NexusGameplayTags::Ability_Weapon_Reload);
	}
	else if (!bOn && bAlreadyOn)
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	}
}


// Anim-notify hooks
void UNexusEquipmentComponent::NotifyHideOutgoingSlot()
{
	// Visual hand-off only: hide the outgoing actor at the authored frame. The phase
	// itself advances when the holster montage blends out (HandleHolsterMontageBlendingOut), so a
	// transition always runs to completion and can't be interrupted mid-montage.
	if (HolsteringSlot.IsValid())
	{
		AttachActorForSlotState(HolsteringSlot, false);
	}
}

void UNexusEquipmentComponent::HandleEquipmentActionNotify(FGameplayTag /*ActionTag*/)
{
	// Deprecated: phase advancement is driven by the montage blend-out delegates, never by
	// an anim notify, so a draw/holster always plays to completion. Kept as a no-op so
	// existing anim-notify references still resolve.
}


// Inventory hookup
void UNexusEquipmentComponent::HandleInventoryItemRemoved(UNexusItemInstance* RemovedInstance)
{
	if (!RemovedInstance || SlotStates.Num() == 0) return;

	TArray<FGameplayTag, TInlineAllocator<4>> ToClear;
	for (const TPair<FGameplayTag, FNexusEquipmentSlotState>& Pair : SlotStates)
	{
		if (Pair.Value.Assigned == RemovedInstance) ToClear.Add(Pair.Key);
	}
	for (const FGameplayTag& Slot : ToClear)
	{
		ClearSlotImmediate(Slot); // also deactivates if it was the active slot
	}
}


// Case-charm hookup — apply the equipped case's socketed charms through the SAME ASC
// passive-grant path armor uses (GiveAbility + AddLooseGameplayTag), never a parallel system.
void UNexusEquipmentComponent::HandleEquippedCaseChanged()
{
	RefreshCharms();
}

void UNexusEquipmentComponent::RefreshCharms()
{
	UNexusAbilitySystemComponent* ASC = GetASC();

	// Remove the previously-granted charm effects (ref-counted, so flat-list removal pairs
	// 1:1 with the grants below).
	if (ASC)
	{
		for (const TSubclassOf<UNexusAbility>& Ability : GrantedCharmAbilities)
		{
			if (Ability) ASC->RemoveAbility(Ability);
		}
		for (const FGameplayTag& Tag : GrantedCharmTags)
		{
			ASC->RemoveLooseGameplayTag(Tag);
		}
	}
	GrantedCharmAbilities.Reset();
	GrantedCharmTags.Reset();

	UNexusInventoryComponent* Inventory = GetInventory();
	if (!ASC || !Inventory) return;

	// Grant each socketed charm's payload — identical shape to FNexusFragment_PassiveEquipment,
	// so charms and armor share one mechanism.
	for (const FGameplayTag& Slot : Inventory->GetCaseCharmSlots())
	{
		UNexusItemDefinition* CharmDef = Inventory->GetSocketedCharm(Slot);
		const FNexusFragment_Charm* Charm = CharmDef
			? CharmDef->FindFragment<FNexusFragment_Charm>() : nullptr;
		if (!Charm) continue;

		for (const TSubclassOf<UNexusAbility>& Ability : Charm->GrantedAbilities)
		{
			if (Ability && ASC->GiveAbility(Ability))
			{
				GrantedCharmAbilities.Add(Ability);
			}
		}
		for (const FGameplayTag& Tag : Charm->GrantedTags)
		{
			ASC->AddLooseGameplayTag(Tag);
			GrantedCharmTags.Add(Tag);
		}
	}
}


// Queries
UNexusItemInstance* UNexusEquipmentComponent::GetAssigned(FGameplayTag SlotTag) const
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	return State ? State->Assigned : nullptr;
}

ANexusEquippedActor* UNexusEquipmentComponent::GetEquippedActorInSlot(FGameplayTag SlotTag) const
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	return State ? State->InWorld : nullptr;
}

bool UNexusEquipmentComponent::IsSlotOccupied(FGameplayTag SlotTag) const
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	return State && State->Assigned != nullptr;
}

bool UNexusEquipmentComponent::IsSlotActive(FGameplayTag SlotTag) const
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	return State && State->Phase == EEquipmentSlotPhase::Active;
}

EEquipmentSlotPhase UNexusEquipmentComponent::GetSlotPhase(FGameplayTag SlotTag) const
{
	const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
	return State ? State->Phase : EEquipmentSlotPhase::Idle;
}

TArray<FGameplayTag> UNexusEquipmentComponent::GetOccupiedSlots() const
{
	TArray<FGameplayTag> Out;
	SlotStates.GetKeys(Out);
	return Out;
}

FGameplayTag UNexusEquipmentComponent::GetSlotForInstance(const UNexusItemInstance* Instance) const
{
	if (!Instance) return FGameplayTag();
	for (const TPair<FGameplayTag, FNexusEquipmentSlotState>& Pair : SlotStates)
	{
		if (Pair.Value.Assigned == Instance) return Pair.Key;
	}
	return FGameplayTag();
}

bool UNexusEquipmentComponent::IsSwapping() const
{
	if (HolsteringSlot.IsValid()) return true;
	if (const FNexusEquipmentSlotState* State = SlotStates.Find(ActiveSlot))
	{
		return State->Phase == EEquipmentSlotPhase::Unholstering;
	}
	return false;
}


// Starter loadout
void UNexusEquipmentComponent::ApplyStarterEquipment()
{
	if (bStarterApplied) return;
	bStarterApplied = true;

	// Starter gear is a "give", so it goes through the one acquire façade (mark-seen, stat
	// seeding) like every other item source — just with auto-equip suppressed, because we
	// target an explicit slot below. The façade needs a pawn recipient; equipment hosts are
	// pawns (player character / NPC).
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	for (const FNexusStarterEquipped& Entry : StarterEquipment)
	{
		if (!Entry.SlotTag.IsValid() || !IsValidSlot(Entry.SlotTag)) continue;
		if (IsSlotOccupied(Entry.SlotTag)) continue;

		UNexusItemDefinition* Definition = Entry.ItemDefinition.LoadSynchronous();
		if (!Definition) continue;

		FNexusAcquireParams Params;
		Params.bAutoEquipIfPossible = false;
		const FNexusAcquireResult Acquired = UNexusInventoryAcquireLibrary::AcquireItem(
			OwnerPawn, Definition, 1, Params);

		// Starter equippables don't stack, so a new instance is always created.
		UNexusItemInstance* Instance = Acquired.NewInstances.Num() > 0 ? Acquired.NewInstances[0] : nullptr;
		if (!Instance) continue;

		if (Entry.bActivateOnSpawn && !IsSlotPassive(Entry.SlotTag))
		{
			AssignAndActivate(Entry.SlotTag, Instance, EUnholsterStyle::Normal);
		}
		else
		{
			AssignItemToSlot(Entry.SlotTag, Instance);
		}
	}
}


// Save / load
void UNexusEquipmentComponent::ComponentPreSave_Implementation()
{
	// The runtime instance pointers can't round-trip through EMS; persist the stable
	// per-instance GUIDs instead and re-resolve them on load against the inventory.
	SavedSlotGuids.Reset();
	for (const TPair<FGameplayTag, FNexusEquipmentSlotState>& Pair : SlotStates)
	{
		if (Pair.Value.Assigned)
		{
			SavedSlotGuids.Add(Pair.Key, Pair.Value.Assigned->GetInstanceGuid());
		}
	}
}

void UNexusEquipmentComponent::ComponentPreLoad_Implementation()
{
	ClearAll();
}

void UNexusEquipmentComponent::ComponentLoaded_Implementation()
{
	// A restored game brings its own slot state — don't also apply starter gear.
	bStarterApplied = true;

	// The equipped instances are owned by the inventory, which rebuilds them in its
	// own ComponentLoaded. Defer one tick so we resolve after the inventory restore
	// regardless of EMS component load order.
	PendingRestoreActiveSlot = ActiveSlot;
	ActiveSlot = FGameplayTag();
	SlotStates.Reset();

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

	// Rebuild slot → instance from the persisted GUIDs against the restored inventory.
	if (const UNexusInventoryComponent* Inventory = GetInventory())
	{
		for (const TPair<FGameplayTag, FGuid>& Pair : SavedSlotGuids)
		{
			if (!IsValidSlot(Pair.Key)) continue; // loadout changed since the save
			UNexusItemInstance* Instance = Inventory->FindInstanceByGuid(Pair.Value);
			if (!Instance) continue;              // item no longer exists — skip the slot

			FNexusEquipmentSlotState& State = SlotStates.Add(Pair.Key);
			State.Assigned = Instance;
			State.bPassive = IsSlotPassive(Pair.Key);
			State.Phase    = EEquipmentSlotPhase::Idle;
		}
	}
	SavedSlotGuids.Reset();

	// Sync-load Equipped bundles for in-hand slots (restore runs behind a loading screen).
	UAssetManager& AM = UAssetManager::Get();
	TArray<FGameplayTag> Keys;
	SlotStates.GetKeys(Keys);
	for (const FGameplayTag& SlotTag : Keys)
	{
		const FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
		if (!State || State->bPassive || !State->Assigned) continue;
		const UNexusItemDefinition* Def = State->Assigned->GetDefinition();
		const FPrimaryAssetId Id = Def ? Def->GetPrimaryAssetId() : FPrimaryAssetId();
		if (!Id.IsValid()) continue;
		if (TSharedPtr<FStreamableHandle> Handle = AM.LoadPrimaryAsset(
			Id, TArray<FName>{ UNexusAssetManager::BundleEquipped }))
		{
			EquippableLoadHandles.Add(State->Assigned, Handle);
		}
	}
	for (const TPair<TObjectPtr<UNexusItemInstance>, TSharedPtr<FStreamableHandle>>& Pair : EquippableLoadHandles)
	{
		if (Pair.Value.IsValid() && !Pair.Value->HasLoadCompleted())
		{
			Pair.Value->WaitUntilComplete();
		}
	}

	// Apply effects (passive grants / in-hand spawn) and announce each restored slot.
	for (const FGameplayTag& SlotTag : Keys)
	{
		FNexusEquipmentSlotState* State = SlotStates.Find(SlotTag);
		if (!State || !State->Assigned) continue;
		ApplySlotEffects(SlotTag, *State);
		if (!State->bPassive)
		{
			AttachActorForSlotState(SlotTag, false);
		}
		OnSlotAssigned.Broadcast(SlotTag, State->Assigned);
	}

	// Re-draw the previously-active slot silently (no montage), to avoid playing a
	// draw on level load.
	if (SavedActiveSlot.IsValid() && IsSlotOccupied(SavedActiveSlot) && !IsSlotPassive(SavedActiveSlot))
	{
		ActiveSlot = SavedActiveSlot;
		if (FNexusEquipmentSlotState* State = SlotStates.Find(SavedActiveSlot))
		{
			State->Phase = EEquipmentSlotPhase::Active;
		}
		AttachActorForSlotState(SavedActiveSlot, true);
		OnSlotActivated.Broadcast(SavedActiveSlot, GetAssigned(SavedActiveSlot));
	}
}
