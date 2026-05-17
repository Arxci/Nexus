#include "NexusItemPickup.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "Nexus/Character/NexusCharacterBase.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"

ANexusItemPickup::ANexusItemPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Interactable = CreateDefaultSubobject<UNexusInteractableComponent>(TEXT("Interactable"));
}

void ANexusItemPickup::BeginPlay()
{
	Super::BeginPlay();

	if (bWasCollected)
	{
		Destroy();
		return;
	}

	RequestPickupMeshLoad();

	if (Interactable)
	{
		Interactable->OnInteractionCompleted.AddDynamic(this, &ANexusItemPickup::HandleInteractionCompleted);
	}
}

void ANexusItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PickupMeshHandle.IsValid())
	{
		PickupMeshHandle->CancelHandle();
		PickupMeshHandle.Reset();
	}

	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PickupCeremonyTimer);
	}

	// Drop the OnSlotAssigned subscription on the player's equipment if the
	// pickup is being torn down before the async assignment resolved. Without
	// this, the equipment component holds a stale dynamic-delegate entry
	// pointing at a destroyed UObject — UE handles invocation gracefully but
	// the binding list keeps growing.
	if (UNexusEquipmentComponent* Equipment = PendingCeremonyEquipment.Get())
	{
		Equipment->OnSlotAssigned.RemoveDynamic(this, &ANexusItemPickup::HandleSlotAssignedForCeremony);
	}
	PendingCeremonyEquipment = nullptr;
	PendingCeremonySlot = FGameplayTag();
	PendingFinishInteractor = nullptr;

	Super::EndPlay(EndPlayReason);
}

void ANexusItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!Mesh) return;

#if WITH_EDITOR
	if (Definition && !Definition->PickupMesh.IsNull())
	{
		Mesh->SetStaticMesh(Definition->PickupMesh.LoadSynchronous());
	}
#endif
}

#if WITH_EDITOR
void ANexusItemPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)) return;

	const FName PropName = PropertyChangedEvent.GetPropertyName();
	if (PropName == GET_MEMBER_NAME_CHECKED(ANexusItemPickup, Definition))
	{
		RerunConstructionScripts();
	}
}
#endif

void ANexusItemPickup::ConfigurePickup(UNexusItemDefinition* InDefinition, int32 InCount)
{
	Definition   = InDefinition;
	InitialCount = FMath::Max(1, InCount);
	RequestPickupMeshLoad();
}

void ANexusItemPickup::RequestPickupMeshLoad()
{
	if (!Mesh || !Definition || Definition->PickupMesh.IsNull()) return;
	if (Mesh->GetStaticMesh()) return;
	if (PickupMeshHandle.IsValid() && !PickupMeshHandle->HasLoadCompleted()) return;

	const FPrimaryAssetId AssetId = Definition->GetPrimaryAssetId();
	if (!AssetId.IsValid()) return;

	TWeakObjectPtr<ANexusItemPickup> WeakSelf(this);
	UAssetManager& AM = UAssetManager::Get();
	PickupMeshHandle = AM.LoadPrimaryAsset(
		AssetId, TArray<FName>{ TEXT("Pickup") },
		FStreamableDelegate::CreateLambda([WeakSelf]()
		{
			ANexusItemPickup* Self = WeakSelf.Get();
			if (!Self || !Self->Mesh || !Self->Definition) return;
			if (Self->Mesh->GetStaticMesh()) return;
			if (UStaticMesh* Loaded = Self->Definition->PickupMesh.Get())
			{
				Self->Mesh->SetStaticMesh(Loaded);
			}
		}));
}

UNexusInventoryComponent* ANexusItemPickup::ResolveInventory(AActor* Interactor) const
{
	if (Interactor)
	{
		if (UNexusInventoryComponent* Direct = Interactor->FindComponentByClass<UNexusInventoryComponent>())
		{
			return Direct;
		}
	}

	if (const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		return PlayerPawn->FindComponentByClass<UNexusInventoryComponent>();
	}
	
	return nullptr;
}

void ANexusItemPickup::HandleInteractionCompleted(AActor* Interactor)
{
    if (bWasCollected || !Definition) return;

    UNexusInventoryComponent* Inventory = ResolveInventory(Interactor);
    if (!Inventory) return;

    // First-pickup ceremony gate: needs at least one ceremony stream authored
    // AND this definition hasn't been seen in this save. Otherwise commit the
    // pickup synchronously through the standard path.
    const bool bHasCeremony = !CeremonyArmsMontage.IsNull() || !CeremonyItemMontage.IsNull();
    const bool bWantsCeremony = bHasCeremony && !Inventory->HasSeenItemDefinition(Definition);

    if (!bWantsCeremony)
    {
        FinishPickup(Inventory, Interactor);
        return;
    }

    // Ceremony path. Hide the pickup mesh immediately so the visual reads as
    // "the item from the ground is now in your hands."
    if (Mesh)
    {
        Mesh->SetVisibility(false, /*bPropagateToChildren*/ true);
    }

    if (!BeginCeremony(Inventory, Interactor))
    {
        // Couldn't kick off the ceremony (AddItem failed, world tearing down).
        // Restore visibility so the pickup remains interactable.
        if (Mesh)
        {
            Mesh->SetVisibility(true, /*bPropagateToChildren*/ true);
        }
    }
}

bool ANexusItemPickup::BeginCeremony(UNexusInventoryComponent* Inventory, AActor* Interactor)
{
    if (!Inventory || !Interactor) return false;

    // AddItem up front: the item is in inventory even if the ceremony is
    // interrupted (player dies mid-anim, world tears down). Apply stat-tag
    // init to each new instance.
    const FNexusAddItemResult AddResult = Inventory->AddItem(Definition, InitialCount);
    if (InitialStatTags.Num() > 0)
    {
        for (UNexusItemInstance* New : AddResult.NewInstances)
        {
            if (!New) continue;
            for (const TPair<FGameplayTag, int32>& Pair : InitialStatTags)
            {
                New->SetStat(Pair.Key, Pair.Value);
            }
        }
    }

    if (AddResult.AmountAdded <= 0) return false;

    // Mark seen on successful add — the ceremony only fires once per def per
    // save regardless of whether playback finishes cleanly.
    Inventory->MarkItemDefinitionSeen(Definition);

    // Look for an auto-equippable instance + a free target slot. The ceremony
    // only routes through the equipment path when both exist; otherwise fall
    // back to arms-only (e.g. a key item with a "found it" inspection anim).
    UNexusEquipmentComponent* Equipment = Interactor->FindComponentByClass<UNexusEquipmentComponent>();
    UNexusItemInstance* InstanceForCeremony = nullptr;
    FGameplayTag CeremonySlot;
    if (Equipment)
    {
        for (UNexusItemInstance* New : AddResult.NewInstances)
        {
            if (!New) continue;
            const UNexusItemDefinition* Def = New->GetDefinition();
            const FNexusFragment_Equippable* Eq = Def ? Def->FindFragment<FNexusFragment_Equippable>() : nullptr;
            if (!Eq || !Eq->bAutoAssignOnPickup) continue;
            const FGameplayTag Target = PickAutoEquipSlot(Equipment, New, Eq);
            if (Target.IsValid())
            {
                InstanceForCeremony = New;
                CeremonySlot = Target;
                break;
            }
        }
    }

    PendingFinishInteractor = Interactor;

    if (InstanceForCeremony)
    {
        // Auto-equip + ceremony. AssignToSlot is async (Equipped bundle load),
        // so the item-side montage can't play yet — the equipped actor doesn't
        // exist until FinalizeAssignment fires OnSlotAssigned. Subscribe first,
        // then kick off the assignment.
        PendingCeremonyEquipment = Equipment;
        PendingCeremonySlot = CeremonySlot;
        Equipment->OnSlotAssigned.AddDynamic(this, &ANexusItemPickup::HandleSlotAssignedForCeremony);

        if (Equipment->AssignToSlot(InstanceForCeremony, CeremonySlot))
        {
            // HandleSlotAssignedForCeremony drives activation + anim playback.
            return true;
        }

        // AssignToSlot rejected (PickAutoEquipSlot already pre-screened, so
        // shouldn't happen — but defend). Unsubscribe and fall through to the
        // arms-only path so the player still gets a beat.
        Equipment->OnSlotAssigned.RemoveDynamic(this, &ANexusItemPickup::HandleSlotAssignedForCeremony);
        PendingCeremonyEquipment = nullptr;
        PendingCeremonySlot = FGameplayTag();
    }

    // Arms-only path — no auto-equip, no item mesh to animate.
    const float Duration = PlayCeremonyMontages(Interactor, /*EquippedActor=*/nullptr);
    if (Duration <= 0.0f)
    {
        // Nothing to wait on. Item is already in inventory; tear down now.
        bWasCollected = true;
        Destroy();
        return true;
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(PickupCeremonyTimer, this,
            &ANexusItemPickup::OnCeremonyFinished, Duration, /*bLoop*/ false);
        return true;
    }
    return false;
}

void ANexusItemPickup::HandleSlotAssignedForCeremony(FGameplayTag SlotTag, UNexusItemInstance* /*Instance*/)
{
    // Equipment broadcasts OnSlotAssigned for every assignment, including ones
    // the player makes through inventory UI while our ceremony is still in
    // flight. Filter to our pending slot.
    if (!SlotTag.MatchesTagExact(PendingCeremonySlot)) return;

    UNexusEquipmentComponent* Equipment = PendingCeremonyEquipment.Get();
    if (!Equipment)
    {
        PendingCeremonySlot = FGameplayTag();
        return;
    }

    // One-shot — unsubscribe before any subsequent slot work re-enters.
    Equipment->OnSlotAssigned.RemoveDynamic(this, &ANexusItemPickup::HandleSlotAssignedForCeremony);
    PendingCeremonyEquipment = nullptr;
    const FGameplayTag TargetSlot = PendingCeremonySlot;
    PendingCeremonySlot = FGameplayTag();

    AActor* Interactor = PendingFinishInteractor.Get();
    if (!Interactor)
    {
        // Player went away between AssignToSlot and the callback. Item is in
        // inventory + slot; just tear down.
        bWasCollected = true;
        Destroy();
        return;
    }

    // Activate the slot with the standard unholster suppressed — the ceremony
    // arms montage we're about to play IS the unholster. The equipped actor
    // is already spawned and attached (FinalizeAssignment did that before
    // broadcasting); RequestActivateSlot just makes it visible + active.
    Equipment->RequestActivateSlot(TargetSlot, /*bSuppressArmsUnholsterAnim=*/true);

    ANexusEquippedActor* EquippedActor = Equipment->GetEquippedActorInSlot(TargetSlot);
    const float Duration = PlayCeremonyMontages(Interactor, EquippedActor);

    if (Duration <= 0.0f)
    {
        // Neither stream actually played. Item is equipped — just tear down.
        bWasCollected = true;
        Destroy();
        return;
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(PickupCeremonyTimer, this,
            &ANexusItemPickup::OnCeremonyFinished, Duration, /*bLoop*/ false);
    }
}

void ANexusItemPickup::OnCeremonyFinished()
{
    // AddItem + auto-equip + activate already happened during BeginCeremony or
    // HandleSlotAssignedForCeremony. Just tear down.
    PendingFinishInteractor = nullptr;
    bWasCollected = true;
    Destroy();
}

void ANexusItemPickup::FinishPickup(UNexusInventoryComponent* Inventory, AActor* Interactor)
{
	if (bWasCollected || !Definition || !Inventory) return;

	const FNexusAddItemResult AddResult = Inventory->AddItem(Definition, InitialCount);

	if (InitialStatTags.Num() > 0)
	{
		for (UNexusItemInstance* New : AddResult.NewInstances)
		{
			if (!New) continue;
			for (const TPair<FGameplayTag, int32>& Pair : InitialStatTags)
			{
				New->SetStat(Pair.Key, Pair.Value);
			}
		}
	}

	if (AddResult.AmountAdded <= 0) return;

	// Mark seen even for non-ceremony pickups so a later ceremony pickup of
	// the same def doesn't replay ground that's already covered (e.g. picked
	// up via debug spawn first, then via a ceremony-bearing pickup actor).
	Inventory->MarkItemDefinitionSeen(Definition);

	for (UNexusItemInstance* New : AddResult.NewInstances)
	{
		AutoEquipIfRequested(New, Interactor);
	}

	if (AddResult.Remainder > 0)
	{
		InitialCount = AddResult.Remainder;
		return;
	}

	bWasCollected = true;
	Destroy();
}

void ANexusItemPickup::AutoEquipIfRequested(UNexusItemInstance* Instance, AActor* Interactor) const
{
	if (!Instance || !Interactor) return;

	const UNexusItemDefinition* Def = Instance->GetDefinition();
	const FNexusFragment_Equippable* Eq = Def ? Def->FindFragment<FNexusFragment_Equippable>() : nullptr;
	if (!Eq || !Eq->bAutoAssignOnPickup) return;

	UNexusEquipmentComponent* Equipment = Interactor->FindComponentByClass<UNexusEquipmentComponent>();
	if (!Equipment) return;

	const FGameplayTag TargetSlot = PickAutoEquipSlot(Equipment, Instance, Eq);
	if (!TargetSlot.IsValid()) return;

	if (Equipment->AssignToSlot(Instance, TargetSlot))
	{
		// Auto-activate with the standard unholster — the player explicitly
		// chose to pick this up, so landing it in their hands is the expected
		// payoff. The ceremony path handles its own activation (with the
		// unholster suppressed) so it doesn't go through here.
		Equipment->RequestActivateSlot(TargetSlot);
	}
}

FGameplayTag ANexusItemPickup::PickAutoEquipSlot(const UNexusEquipmentComponent* Equipment,
	const UNexusItemInstance* Instance, const FNexusFragment_Equippable* Eq) const
{
	if (!Equipment || !Instance || !Eq) return FGameplayTag();

	// Prefer the authored slot when it's currently free. Don't kick out an
	// existing slot occupant — silent replacement on every pickup would
	// destroy player loadout choices.
	if (Eq->PreferredSlot.IsValid()
		&& Equipment->CanAssignToSlot(Instance, Eq->PreferredSlot)
		&& !Equipment->IsSlotOccupied(Eq->PreferredSlot))
	{
		return Eq->PreferredSlot;
	}

	// Fall back to the first compatible free slot. If none, the item still
	// lives in inventory; the player can equip manually.
	for (const FGameplayTag& Slot : Equipment->GetCompatibleSlotsForInstance(Instance))
	{
		if (!Equipment->IsSlotOccupied(Slot))
		{
			return Slot;
		}
	}
	return FGameplayTag();
}

float ANexusItemPickup::PlayCeremonyMontages(AActor* Interactor, ANexusEquippedActor* EquippedActor) const
{
    float MaxDuration = 0.0f;

    // Arms-side stream on the interactor's arms mesh.
    if (!CeremonyArmsMontage.IsNull())
    {
        const ANexusCharacterBase* Char = Cast<ANexusCharacterBase>(Interactor);
        if (Char)
        {
            if (USkeletalMeshComponent* ArmsMesh = Char->GetEquipmentAttachMesh())
            {
                if (UAnimInstance* AnimInstance = ArmsMesh->GetAnimInstance())
                {
                    UAnimMontage* Montage = CeremonyArmsMontage.Get();
                    if (!Montage)
                    {
                        // Pickup bundle should have made this resident — the
                        // mesh load handle covers the bundle. If the author
                        // forgot to bundle-tag it, sync-load is better than
                        // silently skipping the ceremony.
                        Montage = CeremonyArmsMontage.LoadSynchronous();
                    }
                    if (Montage)
                    {
                        MaxDuration = FMath::Max(MaxDuration, AnimInstance->Montage_Play(Montage));
                    }
                }
            }
        }
    }

    // Item-side stream on the equipped actor's mesh. Only runs when the
    // caller supplied an equipped actor (auto-equip ceremony path) — there's
    // no item mesh to animate in the arms-only path.
    if (!CeremonyItemMontage.IsNull() && EquippedActor)
    {
        if (USkeletalMeshComponent* ItemMesh = EquippedActor->GetMesh())
        {
            if (UAnimInstance* AnimInstance = ItemMesh->GetAnimInstance())
            {
                UAnimMontage* Montage = CeremonyItemMontage.Get();
                if (!Montage)
                {
                    Montage = CeremonyItemMontage.LoadSynchronous();
                }
                if (Montage)
                {
                    MaxDuration = FMath::Max(MaxDuration, AnimInstance->Montage_Play(Montage));
                }
            }
        }
    }

    return MaxDuration;
}

void ANexusItemPickup::ActorLoaded_Implementation()
{
	if (bWasCollected)
	{
		Destroy();
	}
}