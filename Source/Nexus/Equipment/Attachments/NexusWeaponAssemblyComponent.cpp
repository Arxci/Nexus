#include "NexusWeaponAssemblyComponent.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/Skeleton.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/SkeletalMesh.h"

#include "Nexus/Weapon/NexusWeaponBehaviorComponent.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "Nexus/Inventory/Fragments/Weapon/NexusFragment_Weapon.h"
#include "Nexus/NexusGameplayTags.h"


UNexusWeaponAssemblyComponent::UNexusWeaponAssemblyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusWeaponAssemblyComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearAssembly();
	Super::EndPlay(EndPlayReason);
}

ANexusEquippedActor* UNexusWeaponAssemblyComponent::GetEquippedActor() const
{
	return Cast<ANexusEquippedActor>(GetOwner());
}

UNexusItemInstance* UNexusWeaponAssemblyComponent::GetSourceInstance() const
{
	const ANexusEquippedActor* Actor = GetEquippedActor();
	return Actor ? Actor->GetSourceInstance() : nullptr;
}

const FNexusFragment_Weapon* UNexusWeaponAssemblyComponent::GetWeaponFragment() const
{
	const UNexusItemInstance* Instance = GetSourceInstance();
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	return Definition ? Definition->FindFragment<FNexusFragment_Weapon>() : nullptr;
}

const FNexusFragment_Equippable* UNexusWeaponAssemblyComponent::GetEquippableFragment() const
{
	const UNexusItemInstance* Instance = GetSourceInstance();
	const UNexusItemDefinition* Definition = Instance ? Instance->GetDefinition() : nullptr;
	return Definition ? Definition->FindFragment<FNexusFragment_Equippable>() : nullptr;
}

const FWeaponSlotDefinition* UNexusWeaponAssemblyComponent::FindSlotDefinition(const FGameplayTag SlotID) const
{
	return SlotDefinitions.Find(SlotID);
}

FGameplayTag UNexusWeaponAssemblyComponent::FindParentSlotFor(const FGameplayTag SlotID) const
{
	if (const FGameplayTag* Found = SlotParents.Find(SlotID)) return *Found;
	return FGameplayTag();
}


// Lifecycle
void UNexusWeaponAssemblyComponent::ClearAssembly()
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

	InvalidateStatCache();
}

void UNexusWeaponAssemblyComponent::RebuildFromInstance()
{
	{
		TGuardValue SuppressGuard(bSuppressBroadcasts, true);

		ClearAssembly();

		if (const FNexusFragment_Weapon* Weapon = GetWeaponFragment())
		{
			// Stage 1: register the weapon's top-level slots.
			for (const FWeaponSlotDefinition& Slot : Weapon->Slots)
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

void UNexusWeaponAssemblyComponent::FillMissingDefaults()
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

			const FWeaponSlotDefinition* SlotDef = SlotDefinitions.Find(SlotID);
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

void UNexusWeaponAssemblyComponent::RegisterSlotDefinition(const FWeaponSlotDefinition& Slot)
{
	if (!Slot.SlotID.IsValid()) return;
	if (SlotDefinitions.Contains(Slot.SlotID))
	{
		// Two attachments authored the same SlotID — treat as a hierarchy bug,
		// log and skip the duplicate so the older registration survives.
		UE_LOG(LogTemp, Warning,
			TEXT("[WeaponAssembly] Duplicate slot id %s in %s; ignoring duplicate"),
			*Slot.SlotID.ToString(),
			*GetNameSafe(GetSourceInstance()));
		return;
	}

	SlotDefinitions.Add(Slot.SlotID, Slot);
}


// Authoring API
bool UNexusWeaponAssemblyComponent::CanAttachItem(const FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const
{
	if (!Definition || !SlotID.IsValid()) return false;

	const FWeaponSlotDefinition* SlotDef = FindSlotDefinition(SlotID);
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
				TEXT("[WeaponAssembly] Slot %s has empty AcceptedTags and bAcceptsAny=false; treating as wildcard. ")
				TEXT("Set bAcceptsAny=true on the slot definition to silence this warning."),
				*SlotID.ToString());
		}
		return true;
	}

	return Definition->FitsSlot(SlotDef->AcceptedTags);
}

bool UNexusWeaponAssemblyComponent::AttachItem(const FGameplayTag SlotID, UNexusAttachmentDefinition* Definition, const bool bPersist)
{
	if (!Definition) return false;
	if (!CanAttachItem(SlotID, Definition)) return false;

	const FWeaponSlotDefinition* SlotDef = FindSlotDefinition(SlotID);
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
		for (const FWeaponSlotDefinition& SubSlot : Definition->ProvidedSlots)
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
					if (UNexusWeaponAssemblyComponent* Self = WeakSelf.Get())
					{
						Self->HandleAttachmentLoaded(SlotID);
					}
				});

			const TSharedPtr<FStreamableHandle> Handle = AM.LoadPrimaryAsset(
				AssetId, TArray<FName>{ TEXT("Equipped") }, OnReady);
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

		InvalidateStatCache();

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

bool UNexusWeaponAssemblyComponent::DetachItem(const FGameplayTag SlotID)
{
	if (!Attached.Contains(SlotID)) return false;

	{
		TGuardValue SuppressGuard(bSuppressBroadcasts, true);
		DetachSubtree(SlotID);

		if (UNexusItemInstance* Instance = GetSourceInstance())
		{
			Instance->ClearAttachmentForSlot(SlotID);
		}

		InvalidateStatCache();
	}

	BroadcastChanged();
	return true;
}

void UNexusWeaponAssemblyComponent::DetachSubtree(const FGameplayTag SlotID)
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
			for (const FWeaponSlotDefinition& SubSlot : Definition->ProvidedSlots)
			{
				SlotDefinitions.Remove(SubSlot.SlotID);
				SlotParents.Remove(SubSlot.SlotID);
			}
		}

		Attached.Remove(SlotID);
	}

	SlotLoadHandles.Remove(SlotID);
	InvalidateStatCache();
}

UNexusAttachmentDefinition* UNexusWeaponAssemblyComponent::GetAttachment(const FGameplayTag SlotID) const
{
	const FNexusAttachmentInstance* Record = Attached.Find(SlotID);
	return Record ? Record->Definition.Get() : nullptr;
}

TArray<FGameplayTag> UNexusWeaponAssemblyComponent::GetAllSlotIDs() const
{
	TArray<FGameplayTag> Out;
	SlotDefinitions.GetKeys(Out);
	return Out;
}

TArray<USkeletalMeshComponent*> UNexusWeaponAssemblyComponent::GetAttachmentMeshes() const
{
	TArray<USkeletalMeshComponent*> Out;
	Out.Reserve(Attached.Num());
	for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
	{
		if (USkeletalMeshComponent* M = Pair.Value.Mesh) Out.Add(M);
	}
	return Out;
}


// Mesh spawning
UMeshComponent* UNexusWeaponAssemblyComponent::GetParentMeshComponentForSlot(const FGameplayTag ParentSlotID) const
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

void UNexusWeaponAssemblyComponent::SpawnMeshForAttachment(FNexusAttachmentInstance& Record)
{
	if (Record.Mesh) return;
	if (!Record.Definition) return;

	UMeshComponent* ParentMesh = GetParentMeshComponentForSlot(Record.ParentSlotID);
	if (!ParentMesh) return; // Parent not ready yet; we'll retry from HandleAttachmentLoaded.

	// Mesh + AnimInstance class come from the "Equipped" bundle that
	// AttachItem just LoadPrimaryAsset'd, so they should be resident. Get()
	// is expected; ensureAlways flags any missed bundle-await.
	USkeletalMesh* MeshAsset = Record.Definition->Mesh.Get();
	if (!MeshAsset)
	{
		ensureAlwaysMsgf(Record.Definition->Mesh.IsNull(),
			TEXT("[WeaponAssembly] Mesh for attachment %s not resident; bundle 'Equipped' was not awaited"),
			*GetNameSafe(Record.Definition));
		MeshAsset = Record.Definition->Mesh.LoadSynchronous();
	}
	if (!MeshAsset) return;

	AActor* Outer = GetOwner();
	if (!Outer) return;

	USkeletalMeshComponent* NewMesh = NewObject<USkeletalMeshComponent>(Outer);
	if (!NewMesh) return;

	NewMesh->SetSkeletalMesh(MeshAsset);
	NewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Modular weapon: when the attachment shares its skeleton with the host
	// weapon mesh (frame), drive its pose from the host via Leader Pose Component.
	// The frame's montage animates a single skeleton; the magazine, slide, etc.
	// follow without their own AnimBP/montage. AAA-standard for split-mesh
	// weapons (Lyra, modern shooter pipelines).
	bool bUsedLeaderPose = false;
	if (USkeletalMeshComponent* HostSkeletalMesh = Cast<USkeletalMeshComponent>(ParentMesh))
	{
		const USkeleton* HostSkeleton = HostSkeletalMesh->GetSkeletalMeshAsset()
			? HostSkeletalMesh->GetSkeletalMeshAsset()->GetSkeleton()
			: nullptr;
		const USkeleton* AttachSkeleton = MeshAsset->GetSkeleton();
		if (HostSkeleton && AttachSkeleton == HostSkeleton)
		{
			NewMesh->SetLeaderPoseComponent(HostSkeletalMesh, /*bForceUpdate*/ true);
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
				TEXT("[WeaponAssembly] AnimInstance class for attachment %s not resident; bundle 'Equipped' was not awaited"),
				*GetNameSafe(Record.Definition));
			AnimClass = Record.Definition->AnimInstanceClass.LoadSynchronous();
		}
		if (AnimClass)
		{
			NewMesh->SetAnimInstanceClass(AnimClass);
		}
	}

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

void UNexusWeaponAssemblyComponent::HandleAttachmentLoaded(const FGameplayTag SlotID)
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
namespace
{
	void SeedBaseStat(TMap<FGameplayTag, float>& Out, const FGameplayTag& Tag, const float Value)
	{
		Out.Add(Tag, Value);
	}
}

void UNexusWeaponAssemblyComponent::RebuildStatCache() const
{
	CachedStats.Values.Reset();

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) { bStatCacheValid = true; return; }

	// Seed every well-known Stat.Weapon.* tag with the fragment's authored
	// value (or a sensible neutral default). Multiplicative-only modifiers
	// applied to non-seeded keys would otherwise multiply against zero and
	// silently zero the value out.
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_Damage,           Weapon->Combat.BaseDamage);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_RPM,              Weapon->Combat.RoundsPerMinute);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_MaxRange,         Weapon->Combat.MaxRange);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_SpreadHip,        Weapon->Combat.SpreadConeDegrees.X);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_SpreadADS,        Weapon->Combat.SpreadConeDegrees.Y);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_MagazineSize,     Weapon->Ammo.MagazineSize);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_ReloadDuration,   Weapon->Reload.ReloadDuration);

	// Recoil/ADS-time aren't authored on FWeaponCombat yet, but seed neutrally
	// so attachments can still meaningfully modify them.
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_RecoilVertical,   0.0f);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_RecoilHorizontal, 0.0f);
	SeedBaseStat(CachedStats.Values, NexusGameplayTags::Stat_Weapon_ADSTime,          0.0f);

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

void UNexusWeaponAssemblyComponent::InvalidateStatCache()
{
	bStatCacheValid = false;
}

const FResolvedWeaponStats& UNexusWeaponAssemblyComponent::ResolveStatsRef() const
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
                TEXT("[WeaponAssembly] Action montage for %s on %s not resident; bundle 'Equipped' was not awaited"),
                *ActionTag.ToString(), *GetNameSafe(OwnerForLog));
            Loaded = Soft.LoadSynchronous();
        }
        return Loaded;
    }
}

UAnimMontage* UNexusWeaponAssemblyComponent::ResolveArmsMontage(const FGameplayTag ActionTag) const
{
    return ResolveActionStream(ActionTag, /*bArmsStream=*/true);
}

UAnimMontage* UNexusWeaponAssemblyComponent::ResolveItemMontage(const FGameplayTag ActionTag) const
{
    return ResolveActionStream(ActionTag, /*bArmsStream=*/false);
}

UAnimMontage* UNexusWeaponAssemblyComponent::ResolveActionStream(
    const FGameplayTag ActionTag, const bool bArmsStream) const
{
    if (!ActionTag.IsValid()) return nullptr;

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
                return Loaded;
            }
        }
    }

    if (const FNexusFragment_Equippable* Eq = GetEquippableFragment())
    {
        if (const FEquipmentActionAnim* Pair = Eq->Animations.Actions.Find(ActionTag))
        {
            return LoadStream(Pair->*StreamPtr, ActionTag, GetSourceInstance());
        }
    }

    return nullptr;
}


// Utility
void UNexusWeaponAssemblyComponent::BroadcastChanged()
{
	if (bSuppressBroadcasts) return;
	if (!HasBegunPlay()) return;
	OnAssemblyChanged.Broadcast();
}