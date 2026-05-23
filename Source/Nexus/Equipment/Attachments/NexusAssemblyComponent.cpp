#include "NexusAssemblyComponent.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/Skeleton.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "Nexus/NexusAssetManager.h"

#include "StructUtils/InstancedStruct.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"


UNexusAssemblyComponent::UNexusAssemblyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusAssemblyComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearAssembly();
	Super::EndPlay(EndPlayReason);
}

ANexusEquippedActor* UNexusAssemblyComponent::GetEquippedActor() const
{
	return Cast<ANexusEquippedActor>(GetOwner());
}

UNexusItemInstance* UNexusAssemblyComponent::GetSourceInstance() const
{
	const ANexusEquippedActor* Actor = GetEquippedActor();
	return Actor ? Actor->GetSourceInstance() : nullptr;
}

const FNexusFragment_Equippable* UNexusAssemblyComponent::GetEquippableFragment() const
{
	const UNexusItemInstance* Instance = GetSourceInstance();
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	return Definition ? Definition->FindFragment<FNexusFragment_Equippable>() : nullptr;
}

const FAssemblySlotDefinition* UNexusAssemblyComponent::FindSlotDefinition(const FGameplayTag SlotID) const
{
	return SlotDefinitions.Find(SlotID);
}

FGameplayTag UNexusAssemblyComponent::FindParentSlotFor(const FGameplayTag SlotID) const
{
	if (const FGameplayTag* Found = SlotParents.Find(SlotID)) return *Found;
	return FGameplayTag();
}


// Lifecycle
void UNexusAssemblyComponent::ClearAssembly()
{
	TGuardValue SuppressGuard(bSuppressBroadcasts, true);

	TArray<FGameplayTag> Slots;
	Attached.GetKeys(Slots);
	for (const FGameplayTag& SlotID : Slots)
	{
		DetachSubtree(SlotID);
	}

	SlotDefinitions.Reset();
	SlotParents.Reset();
	SlotLoadHandles.Reset();
	Attached.Reset();

	InvalidateCaches();
}

void UNexusAssemblyComponent::RebuildFromInstance()
{
	{
		TGuardValue SuppressGuard(bSuppressBroadcasts, true);

		ClearAssembly();

		if (const FNexusFragment_Equippable* Equippable = GetEquippableFragment())
		{
			// Stage 1: register the equippable's top-level slots.
			for (const FAssemblySlotDefinition& Slot : Equippable->Slots)
			{
				if (!Slot.SlotID.IsValid()) continue;
				RegisterSlotDefinition(Slot);
			}

			// Stage 2: install attachments — persisted instance config wins, otherwise default.
			FillMissingDefaults();
		}
	}

	// One consolidated broadcast — fires even on teardown-only paths so UI
	// listeners stay in sync with the cleared state.
	BroadcastChanged();
}

void UNexusAssemblyComponent::FillMissingDefaults()
{
	UNexusItemInstance* Instance = GetSourceInstance();

	// Fix-point loop: a freshly-installed attachment can introduce more sub-slots
	// that themselves want filling.
	bool bChanged;
	do
	{
		bChanged = false;
		TArray<FGameplayTag> SlotKeys;
		SlotDefinitions.GetKeys(SlotKeys);

		for (const FGameplayTag& SlotID : SlotKeys)
		{
			if (Attached.Contains(SlotID)) continue;

			const FAssemblySlotDefinition* SlotDef = SlotDefinitions.Find(SlotID);
			if (!SlotDef) continue;

			TSoftObjectPtr<UNexusAttachmentDefinition> ToInstall;
			if (Instance)
			{
				ToInstall = Instance->GetAttachmentForSlot(SlotID);
			}
			if (ToInstall.IsNull())
			{
				ToInstall = SlotDef->DefaultAttachment;
			}
			if (ToInstall.IsNull()) continue;

			// Both persisted refs and slot defaults are reachable from the
			// "Equipped" bundle that the equipment component awaited before
			// invoking us, so the asset should already be resident. Get() is
			// expected; LoadSynchronous fallback is defensive only.
			UNexusAttachmentDefinition* Definition = ToInstall.Get();
			if (!Definition) Definition = ToInstall.LoadSynchronous();
			if (!Definition) continue;

			if (!CanAttachItem(SlotID, Definition)) continue;

			// bPersist=false here — defaults shouldn't pollute the player's
			// per-instance attachment map. Only player-driven AttachItem persists.
			AttachItem(SlotID, Definition, /*bPersist*/ false);
			bChanged = true;
		}
	} while (bChanged);
}

void UNexusAssemblyComponent::RegisterSlotDefinition(const FAssemblySlotDefinition& Slot)
{
	if (!Slot.SlotID.IsValid()) return;
	if (SlotDefinitions.Contains(Slot.SlotID))
	{
		// Two attachments authored the same SlotID — treat as a hierarchy bug,
		// log and skip the duplicate so the older registration survives.
		UE_LOG(LogTemp, Warning,
			TEXT("[Assembly] Duplicate slot id %s in %s; ignoring duplicate"),
			*Slot.SlotID.ToString(),
			*GetNameSafe(GetSourceInstance()));
		return;
	}

	SlotDefinitions.Add(Slot.SlotID, Slot);
}


// Authoring API
bool UNexusAssemblyComponent::CanAttachItem(const FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const
{
	if (!Definition || !SlotID.IsValid()) return false;

	const FAssemblySlotDefinition* SlotDef = FindSlotDefinition(SlotID);
	if (!SlotDef) return false;

	if (SlotDef->bAcceptsAny) return true;

	if (SlotDef->AcceptedTags.IsEmpty())
	{
		// Legacy behaviour: empty AcceptedTags used to mean "anything fits".
		// Preserve it but warn once per slot so authors migrate to bAcceptsAny.
		static TSet<FGameplayTag> WarnedSlots;
		bool bAlreadyWarned;
		WarnedSlots.Add(SlotID, &bAlreadyWarned);
		if (!bAlreadyWarned)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("[Assembly] Slot %s has empty AcceptedTags and bAcceptsAny=false; treating as wildcard. ")
				TEXT("Set bAcceptsAny=true on the slot definition to silence this warning."),
				*SlotID.ToString());
		}
		return true;
	}

	return Definition->FitsSlot(SlotDef->AcceptedTags);
}

bool UNexusAssemblyComponent::AttachItem(const FGameplayTag SlotID, UNexusAttachmentDefinition* Definition, const bool bPersist)
{
	if (!Definition) return false;
	if (!CanAttachItem(SlotID, Definition)) return false;

	const FAssemblySlotDefinition* SlotDef = FindSlotDefinition(SlotID);
	if (!SlotDef) return false;

	const FGameplayTag ParentSlotID = FindParentSlotFor(SlotID);

	{
		// Suppress broadcasts during the swap so we emit one event for the whole
		// change (and so a recursive FillMissingDefaults pass doesn't fire its
		// own intermediate broadcasts).
		TGuardValue SuppressGuard(bSuppressBroadcasts, true);

		// Replace any existing attachment in this slot before installing the new one.
		if (Attached.Contains(SlotID))
		{
			DetachSubtree(SlotID);
		}

		FNexusAttachmentInstance Record;
		Record.SlotID        = SlotID;
		Record.ParentSlotID  = ParentSlotID;
		Record.Definition    = Definition;
		Record.AttachSocket  = SlotDef->AttachSocket;

		Attached.Add(SlotID, Record);

		// Register the new attachment's provided sub-slots so future passes can fill them.
		for (const FAssemblySlotDefinition& SubSlot : Definition->ProvidedSlots)
		{
			if (!SubSlot.SlotID.IsValid()) continue;
			RegisterSlotDefinition(SubSlot);
			SlotParents.Add(SubSlot.SlotID, SlotID);
		}

		if (bPersist)
		{
			if (UNexusItemInstance* Instance = GetSourceInstance())
			{
				Instance->SetAttachmentForSlot(SlotID, Definition);
			}
		}

		// Async-load the visual via the Asset Manager and spawn the mesh component
		// when ready. If the asset manager has nothing for this id (designer hasn't
		// registered the Attachment primary type), we fall back to spawning
		// straight from the resolved definition.
		const FPrimaryAssetId AssetId = Definition->GetPrimaryAssetId();
		if (AssetId.IsValid())
		{
			UAssetManager& AM = UAssetManager::Get();
			TWeakObjectPtr WeakSelf(this);
			const FStreamableDelegate OnReady = FStreamableDelegate::CreateLambda(
				[WeakSelf, SlotID]()
				{
					if (UNexusAssemblyComponent* Self = WeakSelf.Get())
					{
						Self->HandleAttachmentLoaded(SlotID);
					}
				});

			const TSharedPtr<FStreamableHandle> Handle = AM.LoadPrimaryAsset(
				AssetId, TArray<FName>{ UNexusAssetManager::BundleEquipped }, OnReady);
			if (Handle.IsValid())
			{
				SlotLoadHandles.Add(SlotID, Handle);
			}
			else
			{
				HandleAttachmentLoaded(SlotID);
			}
		}
		else
		{
			HandleAttachmentLoaded(SlotID);
		}

		InvalidateCaches();

		// If the new attachment exposed sub-slots, fill their defaults so a
		// runtime swap (UI-driven) behaves the same as the initial Rebuild.
		if (Definition->ProvidedSlots.Num() > 0)
		{
			FillMissingDefaults();
		}
	}

	// One consolidated broadcast after all internal mutations.
	BroadcastChanged();
	return true;
}

bool UNexusAssemblyComponent::DetachItem(const FGameplayTag SlotID)
{
	if (!Attached.Contains(SlotID)) return false;

	{
		TGuardValue SuppressGuard(bSuppressBroadcasts, true);
		DetachSubtree(SlotID);

		if (UNexusItemInstance* Instance = GetSourceInstance())
		{
			Instance->ClearAttachmentForSlot(SlotID);
		}

		InvalidateCaches();
	}

	BroadcastChanged();
	return true;
}

void UNexusAssemblyComponent::DetachSubtree(const FGameplayTag SlotID)
{
	// Destroy any descendants first so the mesh hierarchy unwinds cleanly.
	TArray<FGameplayTag> Children;
	for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
	{
		if (Pair.Value.ParentSlotID == SlotID)
		{
			Children.Add(Pair.Key);
		}
	}
	for (const FGameplayTag& ChildSlotID : Children)
	{
		DetachSubtree(ChildSlotID);
	}

	if (FNexusAttachmentInstance* Record = Attached.Find(SlotID))
	{
		if (Record->Mesh)
		{
			Record->Mesh->DestroyComponent();
			Record->Mesh = nullptr;
		}

		// Remove any sub-slots this attachment contributed. Their entries in
		// SlotDefinitions are no longer reachable since the parent is gone.
		if (const UNexusAttachmentDefinition* Definition = Record->Definition)
		{
			for (const FAssemblySlotDefinition& SubSlot : Definition->ProvidedSlots)
			{
				SlotDefinitions.Remove(SubSlot.SlotID);
				SlotParents.Remove(SubSlot.SlotID);
			}
		}

		Attached.Remove(SlotID);
	}

	SlotLoadHandles.Remove(SlotID);
	InvalidateCaches();
}

UNexusAttachmentDefinition* UNexusAssemblyComponent::GetAttachment(const FGameplayTag SlotID) const
{
	const FNexusAttachmentInstance* Record = Attached.Find(SlotID);
	return Record ? Record->Definition.Get() : nullptr;
}

TArray<FGameplayTag> UNexusAssemblyComponent::GetAllSlotIDs() const
{
	TArray<FGameplayTag> Out;
	SlotDefinitions.GetKeys(Out);
	return Out;
}

TArray<UMeshComponent*> UNexusAssemblyComponent::GetAttachmentMeshes() const
{
	TArray<UMeshComponent*> Out;
	Out.Reserve(Attached.Num());
	for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
	{
		if (UMeshComponent* M = Pair.Value.Mesh) Out.Add(M);
	}
	return Out;
}


// Mesh spawning
UMeshComponent* UNexusAssemblyComponent::GetParentMeshComponentForSlot(const FGameplayTag ParentSlotID) const
{
	if (ParentSlotID.IsValid())
	{
		if (const FNexusAttachmentInstance* ParentRecord = Attached.Find(ParentSlotID))
		{
			return ParentRecord->Mesh;
		}
		return nullptr;
	}

	if (const ANexusEquippedActor* Actor = GetEquippedActor())
	{
		return Actor->GetMesh();
	}
	return nullptr;
}

void UNexusAssemblyComponent::SpawnMeshForAttachment(FNexusAttachmentInstance& Record)
{
	if (Record.Mesh) return;
	if (!Record.Definition) return;

	UMeshComponent* ParentMesh = GetParentMeshComponentForSlot(Record.ParentSlotID);
	if (!ParentMesh) return; // Parent not ready yet; we'll retry from HandleAttachmentLoaded.

	AActor* Outer = GetOwner();
	if (!Outer) return;

	UMeshComponent* NewMesh = nullptr;

	// Skeletal wins on conflict (see UNexusAttachmentDefinition::SkeletalMesh).
	// Mesh + AnimInstance class come from the "Equipped" bundle that
	// AttachItem just LoadPrimaryAsset'd, so they should be resident. Get()
	// is expected; ensureAlways flags any missed bundle-await.
	if (!Record.Definition->SkeletalMesh.IsNull())
	{
		USkeletalMesh* MeshAsset = Record.Definition->SkeletalMesh.Get();
		if (!MeshAsset)
		{
			ensureAlwaysMsgf(false,
				TEXT("[Assembly] SkeletalMesh for attachment %s not resident; bundle 'Equipped' was not awaited"),
				*GetNameSafe(Record.Definition));
			MeshAsset = Record.Definition->SkeletalMesh.LoadSynchronous();
		}
		if (!MeshAsset) return;

		USkeletalMeshComponent* SkeletalComp = NewObject<USkeletalMeshComponent>(Outer);
		if (!SkeletalComp) return;

		SkeletalComp->SetSkeletalMesh(MeshAsset);

		// Modular host: when the attachment shares its skeleton with the host
		// mesh, drive its pose from the host via Leader Pose Component. The
		// host's montage animates a single skeleton; the magazine, slide, etc.
		// follow without their own AnimBP/montage. AAA-standard for split-mesh
		// authoring (Lyra, modern shooter pipelines).
		bool bUsedLeaderPose = false;
		if (USkeletalMeshComponent* HostSkeletalMesh = Cast<USkeletalMeshComponent>(ParentMesh))
		{
			const USkeleton* HostSkeleton = HostSkeletalMesh->GetSkeletalMeshAsset()
				? HostSkeletalMesh->GetSkeletalMeshAsset()->GetSkeleton()
				: nullptr;
			const USkeleton* AttachSkeleton = MeshAsset->GetSkeleton();
			if (HostSkeleton && AttachSkeleton == HostSkeleton)
			{
				SkeletalComp->SetLeaderPoseComponent(HostSkeletalMesh, /*bForceUpdate*/ true);
				bUsedLeaderPose = true;
			}
		}

		if (!bUsedLeaderPose)
		{
			// Independent skeleton — attachment runs its own AnimInstance if authored.
			UClass* AnimClass = Record.Definition->AnimInstanceClass.Get();
			if (!AnimClass && !Record.Definition->AnimInstanceClass.IsNull())
			{
				ensureAlwaysMsgf(false,
					TEXT("[Assembly] AnimInstance class for attachment %s not resident; bundle 'Equipped' was not awaited"),
					*GetNameSafe(Record.Definition));
				AnimClass = Record.Definition->AnimInstanceClass.LoadSynchronous();
			}
			if (AnimClass)
			{
				SkeletalComp->SetAnimInstanceClass(AnimClass);
			}
		}

		NewMesh = SkeletalComp;
	}
	else if (!Record.Definition->StaticMesh.IsNull())
	{
		UStaticMesh* MeshAsset = Record.Definition->StaticMesh.Get();
		if (!MeshAsset)
		{
			ensureAlwaysMsgf(false,
				TEXT("[Assembly] StaticMesh for attachment %s not resident; bundle 'Equipped' was not awaited"),
				*GetNameSafe(Record.Definition));
			MeshAsset = Record.Definition->StaticMesh.LoadSynchronous();
		}
		if (!MeshAsset) return;

		UStaticMeshComponent* StaticComp = NewObject<UStaticMeshComponent>(Outer);
		if (!StaticComp) return;

		StaticComp->SetStaticMesh(MeshAsset);
		NewMesh = StaticComp;
	}
	else
	{
		return;
	}

	NewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Register, then attach. SetupAttachment is for unregistered components only;
	// after RegisterComponent the attachment is finalized via AttachToComponent.
	NewMesh->RegisterComponent();
	NewMesh->AttachToComponent(ParentMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, Record.AttachSocket);

	// Mirror viewpoint state (cast-shadow + first-person primitive) from the actor.
	if (ANexusEquippedActor* Actor = GetEquippedActor())
	{
		Actor->ApplyViewpointToMesh(NewMesh);
	}

	Record.Mesh = NewMesh;
}

void UNexusAssemblyComponent::HandleAttachmentLoaded(const FGameplayTag SlotID)
{
	FNexusAttachmentInstance* Record = Attached.Find(SlotID);
	if (!Record) return;

	SpawnMeshForAttachment(*Record);

	// If this slot's mesh just appeared, any child whose parent was waiting on
	// it can now spawn — async load order is non-deterministic and a child
	// callback may have arrived before its parent's.
	if (Record->Mesh)
	{
		for (TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
		{
			if (Pair.Value.ParentSlotID == SlotID && !Pair.Value.Mesh)
			{
				SpawnMeshForAttachment(Pair.Value);
			}
		}
	}

	BroadcastChanged();
}


// Resolution
void UNexusAssemblyComponent::RebuildStatCache() const
{
	CachedStats.Values.Reset();

	// Seed phase: every fragment contributes its own base values. Assembly is
	// type-agnostic — it never reaches into a specific fragment subclass.
	const UNexusItemInstance* Instance = GetSourceInstance();
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	if (Definition)
	{
		for (const TInstancedStruct<FNexusItemFragment>& Frag : Definition->Fragments)
		{
			if (!Frag.IsValid()) continue;
			Frag.Get().SeedStatTags(CachedStats.Values);
		}
	}

	// Two-pass fold so multiplicative modifiers always apply on top of the
	// fully-summed additive base — matches how AAA gunsmiths describe their
	// attachment math (flat bonus, then percentage).
	TMap<FGameplayTag, float> AddSum;
	TMap<FGameplayTag, float> MulProduct;

	for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
	{
		const UNexusAttachmentDefinition* Def = Pair.Value.Definition;
		if (!Def) continue;
		for (const FAttachmentStatModifier& Mod : Def->Modifiers)
		{
			if (!Mod.StatTag.IsValid()) continue;
			AddSum.FindOrAdd(Mod.StatTag, 0.0f)     += Mod.Add;
			MulProduct.FindOrAdd(Mod.StatTag, 1.0f) *= Mod.Mul;
		}
	}

	for (const TPair<FGameplayTag, float>& Add : AddSum)
	{
		// Only modify keys we actually seeded — modifiers against unknown stat
		// tags would otherwise silently invent values.
		if (float* Value = CachedStats.Values.Find(Add.Key))
		{
			*Value += Add.Value;
		}
	}
	for (const TPair<FGameplayTag, float>& Mul : MulProduct)
	{
		if (float* Value = CachedStats.Values.Find(Mul.Key))
		{
			*Value *= Mul.Value;
		}
	}

	bStatCacheValid = true;
}

void UNexusAssemblyComponent::InvalidateCaches()
{
	bStatCacheValid = false;
}

const FResolvedItemStats& UNexusAssemblyComponent::ResolveStatsRef() const
{
	if (!bStatCacheValid)
	{
		RebuildStatCache();
	}
	return CachedStats;
}

namespace
{
    using FActionStreamPtr = TSoftObjectPtr<UAnimMontage> FEquipmentActionAnim::*;

    UAnimMontage* LoadStream(const TSoftObjectPtr<UAnimMontage>& Soft,
        const FGameplayTag& ActionTag, const UObject* OwnerForLog)
    {
        UAnimMontage* Loaded = Soft.Get();
        if (!Loaded && !Soft.IsNull())
        {
            ensureAlwaysMsgf(false,
                TEXT("[Assembly] Action montage for %s on %s not resident; bundle 'Equipped' was not awaited"),
                *ActionTag.ToString(), *GetNameSafe(OwnerForLog));
            Loaded = Soft.LoadSynchronous();
        }
        return Loaded;
    }
}

UAnimMontage* UNexusAssemblyComponent::ResolveArmsMontage(const FGameplayTag ActionTag) const
{
    return ResolveActionStream(ActionTag, /*bArmsStream=*/true);
}

UAnimMontage* UNexusAssemblyComponent::ResolveItemMontage(const FGameplayTag ActionTag) const
{
    return ResolveActionStream(ActionTag, /*bArmsStream=*/false);
}

UAnimMontage* UNexusAssemblyComponent::ResolveActionStream(
    const FGameplayTag ActionTag, const bool bArmsStream) const
{
    if (!ActionTag.IsValid()) return nullptr;

    // Cache lookup: a key present (even with nullptr value) means we've already
    // walked the override-then-fallback chain for this action under the current
    // assembly tree. Caches are dropped via InvalidateCaches on every
    // Attach/Detach/ClearAssembly so stale entries can't survive a config change.
    TMap<FGameplayTag, UAnimMontage*>& Cache = bArmsStream
        ? CachedArmsMontages
        : CachedItemMontages;
    if (UAnimMontage* const* Hit = Cache.Find(ActionTag))
    {
        return *Hit;
    }

    const FActionStreamPtr StreamPtr = bArmsStream
        ? &FEquipmentActionAnim::ArmsMontage
        : &FEquipmentActionAnim::ItemMontage;

    auto DepthOf = [this](FGameplayTag Slot) -> int32
    {
        int32 Depth = 0;
        while (Slot.IsValid())
        {
            const FNexusAttachmentInstance* Rec = Attached.Find(Slot);
            if (!Rec) break;
            Slot = Rec->ParentSlotID;
            ++Depth;
            if (Depth > 32) break;
        }
        return Depth;
    };

    // Collect all candidates first so we can pick a deterministic winner on
    // equal-depth ties (sort by SlotID name). TMap iteration order is otherwise
    // unspecified and would silently flip winners between runs. An attachment
    // only enters the candidate list if it overrides the *selected* stream —
    // a magazine that only authors an ItemMontage doesn't compete with a
    // foregrip that only authors an ArmsMontage for the same action.
    struct FCandidate { FGameplayTag SlotID; int32 Depth; };
    TArray<FCandidate, TInlineAllocator<8>> Candidates;

    for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
    {
        const UNexusAttachmentDefinition* Def = Pair.Value.Definition;
        if (!Def) continue;
        const FEquipmentActionAnim* Override = Def->ActionOverrides.Find(ActionTag);
        if (!Override) continue;
        if ((Override->*StreamPtr).IsNull()) continue;

        Candidates.Add({Pair.Key, DepthOf(Pair.Key)});
    }

    if (Candidates.Num() > 0)
    {
        Candidates.Sort([](const FCandidate& A, const FCandidate& B)
        {
            if (A.Depth != B.Depth) return A.Depth > B.Depth;
            return A.SlotID.GetTagName().LexicalLess(B.SlotID.GetTagName());
        });

        for (const FCandidate& Cand : Candidates)
        {
            const FNexusAttachmentInstance* Rec = Attached.Find(Cand.SlotID);
            if (!Rec || !Rec->Definition) continue;
            const FEquipmentActionAnim* Override = Rec->Definition->ActionOverrides.Find(ActionTag);
            if (!Override) continue;

            if (UAnimMontage* Loaded = LoadStream(Override->*StreamPtr, ActionTag, Rec->Definition))
            {
                Cache.Add(ActionTag, Loaded);
                return Loaded;
            }
        }
    }

    UAnimMontage* Fallback = nullptr;
    if (const FNexusFragment_Equippable* Eq = GetEquippableFragment())
    {
        if (const FEquipmentActionAnim* Pair = Eq->Animations.Actions.Find(ActionTag))
        {
            Fallback = LoadStream(Pair->*StreamPtr, ActionTag, GetSourceInstance());
        }
    }

    // Cache the negative result too — a non-overridden, non-authored action
    // should not re-walk every attachment + fragment lookup on every shot.
    Cache.Add(ActionTag, Fallback);
    return Fallback;
}


// Utility
void UNexusAssemblyComponent::BroadcastChanged()
{
	if (bSuppressBroadcasts) return;
	if (!HasBegunPlay()) return;
	OnAssemblyChanged.Broadcast();
}
