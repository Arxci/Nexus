#include "NexusWeaponAssemblyComponent.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "Components/SkeletalMeshComponent.h"

#include "Engine/AssetManager.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/World.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
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

const FWeaponSlotDefinition* UNexusWeaponAssemblyComponent::FindSlotDefinition(const FGameplayTag SlotID) const
{
	return SlotDefinitions.Find(SlotID);
}


// Lifecycle
void UNexusWeaponAssemblyComponent::ClearAssembly()
{
	TArray<FGameplayTag> Slots;
	Attached.GetKeys(Slots);
	for (const FGameplayTag& SlotID : Slots)
	{
		DetachSubtree(SlotID);
	}

	SlotDefinitions.Reset();
	SlotLoadHandles.Reset();
	Attached.Reset();
}

void UNexusWeaponAssemblyComponent::RebuildFromInstance()
{
	ClearAssembly();

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return;

	UNexusItemInstance* Instance = GetSourceInstance();

	// Stage 1: register the weapon's top-level slots (no parent).
	for (const FWeaponSlotDefinition& Slot : Weapon->Slots)
	{
		if (!Slot.SlotID.IsValid()) continue;
		RegisterSlotDefinition(Slot, FGameplayTag());
	}

	// Stage 2: install attachments. Persisted instance config wins; otherwise
	// the slot's DefaultAttachment is used. We loop because a freshly-installed
	// attachment can introduce more sub-slots that themselves want filling.
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

			// LoadSynchronous here is acceptable for assembly-time setup —
			// the equipment component already gates equipping behind an async
			// load of the "Equipped" bundle, which includes attachment soft refs
			// reachable from the fragment. For runtime player-driven attaches,
			// AttachItem() goes through the Asset Manager async path.
			UNexusAttachmentDefinition* Definition = ToInstall.LoadSynchronous();
			if (!Definition) continue;
			if (!CanAttachItem(SlotID, Definition)) continue;

			AttachItem(SlotID, Definition);
			bChanged = true;
		}
	} while (bChanged);

	BroadcastChanged();
}

void UNexusWeaponAssemblyComponent::RegisterSlotDefinition(const FWeaponSlotDefinition& Slot, const FGameplayTag /*ParentSlotID*/)
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

	// Parent linkage is tracked on the FNexusAttachmentInstance during
	// AttachItem (it scans Attached for the contributor), so SlotDefinitions
	// only needs the per-slot fields the slot author wrote down.
	SlotDefinitions.Add(Slot.SlotID, Slot);
}


// Authoring API
bool UNexusWeaponAssemblyComponent::CanAttachItem(const FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const
{
	if (!Definition || !SlotID.IsValid()) return false;

	const FWeaponSlotDefinition* SlotDef = FindSlotDefinition(SlotID);
	if (!SlotDef) return false;

	// Empty AcceptedTags = "anything fits" — useful for prototype/test slots.
	if (SlotDef->AcceptedTags.IsEmpty()) return true;

	return Definition->FitsSlot(SlotDef->AcceptedTags);
}

bool UNexusWeaponAssemblyComponent::AttachItem(const FGameplayTag SlotID, UNexusAttachmentDefinition* Definition)
{
	if (!Definition) return false;
	if (!CanAttachItem(SlotID, Definition)) return false;

	const FWeaponSlotDefinition* SlotDef = FindSlotDefinition(SlotID);
	if (!SlotDef) return false;

	// Determine the parent slot, if any. A slot is a child when it was
	// contributed by an attachment further up the tree — i.e. when an existing
	// installed attachment lists this SlotID inside its ProvidedSlots.
	FGameplayTag ParentSlotID;
	for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
	{
		const UNexusAttachmentDefinition* ParentDef = Pair.Value.Definition;
		if (!ParentDef) continue;
		for (const FWeaponSlotDefinition& Provided : ParentDef->ProvidedSlots)
		{
			if (Provided.SlotID == SlotID)
			{
				ParentSlotID = Pair.Key;
				break;
			}
		}
		if (ParentSlotID.IsValid()) break;
	}

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

	// Register the new attachment's provided sub-slots so future passes (or
	// player-driven attaches) can fill them.
	for (const FWeaponSlotDefinition& SubSlot : Definition->ProvidedSlots)
	{
		if (!SubSlot.SlotID.IsValid()) continue;
		RegisterSlotDefinition(SubSlot, SlotID);
	}

	if (UNexusItemInstance* Instance = GetSourceInstance())
	{
		Instance->SetAttachmentForSlot(SlotID, Definition);
	}

	// Async-load the visual via the Asset Manager and spawn the mesh component
	// when ready. If the asset manager has nothing for this id (designer hasn't
	// registered the Attachment primary type), we fall back to spawning
	// straight from the resolved definition.
	const FPrimaryAssetId AssetId = Definition->GetPrimaryAssetId();
	if (AssetId.IsValid())
	{
		UAssetManager& AM = UAssetManager::Get();
		TWeakObjectPtr<UNexusWeaponAssemblyComponent> WeakSelf(this);
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

	BroadcastChanged();
	return true;
}

bool UNexusWeaponAssemblyComponent::DetachItem(const FGameplayTag SlotID)
{
	if (!Attached.Contains(SlotID)) return false;

	DetachSubtree(SlotID);

	if (UNexusItemInstance* Instance = GetSourceInstance())
	{
		Instance->ClearAttachmentForSlot(SlotID);
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
			}
		}

		Attached.Remove(SlotID);
	}

	SlotLoadHandles.Remove(SlotID);
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
	if (!ParentMesh) return;

	USkeletalMesh* MeshAsset = Record.Definition->Mesh.LoadSynchronous();
	if (!MeshAsset) return;

	AActor* Outer = GetOwner();
	if (!Outer) return;

	USkeletalMeshComponent* NewMesh = NewObject<USkeletalMeshComponent>(Outer);
	if (!NewMesh) return;

	NewMesh->SetSkeletalMesh(MeshAsset);
	NewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NewMesh->SetCastShadow(false);

	if (UClass* AnimClass = Record.Definition->AnimInstanceClass.LoadSynchronous())
	{
		NewMesh->SetAnimInstanceClass(AnimClass);
	}

	NewMesh->SetupAttachment(ParentMesh, Record.AttachSocket);
	NewMesh->RegisterComponent();
	NewMesh->AttachToComponent(ParentMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, Record.AttachSocket);

	// Mirror the equipped actor's first-person rendering treatment.
	if (const ANexusEquippedActor* Actor = GetEquippedActor())
	{
		if (const USkeletalMeshComponent* ActorMesh = Actor->GetMesh())
		{
			NewMesh->FirstPersonPrimitiveType = ActorMesh->FirstPersonPrimitiveType;
		}
	}

	Record.Mesh = NewMesh;
}

void UNexusWeaponAssemblyComponent::HandleAttachmentLoaded(const FGameplayTag SlotID)
{
	FNexusAttachmentInstance* Record = Attached.Find(SlotID);
	if (!Record) return;

	SpawnMeshForAttachment(*Record);
	BroadcastChanged();
}


// Resolution
FResolvedWeaponStats UNexusWeaponAssemblyComponent::ResolveStats() const
{
	FResolvedWeaponStats Out;

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return Out;

	// Seed with the weapon's authored base values. Each lives as a
	// well-known Stat.Weapon.* tag so attachments can layer on them generically.
	Out.Values.Add(NexusGameplayTags::Stat_Weapon_Damage,           Weapon->Combat.BaseDamage);
	Out.Values.Add(NexusGameplayTags::Stat_Weapon_RPM,              Weapon->Combat.RoundsPerMinute);
	Out.Values.Add(NexusGameplayTags::Stat_Weapon_MaxRange,         Weapon->Combat.MaxRange);
	Out.Values.Add(NexusGameplayTags::Stat_Weapon_SpreadHip,        Weapon->Combat.SpreadConeDegrees.X);
	Out.Values.Add(NexusGameplayTags::Stat_Weapon_SpreadADS,        Weapon->Combat.SpreadConeDegrees.Y);
	Out.Values.Add(NexusGameplayTags::Stat_Weapon_MagazineSize,     Weapon->Ammo.MagazineSize);
	Out.Values.Add(NexusGameplayTags::Stat_Weapon_ReloadDuration,   Weapon->Reload.ReloadDuration);

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
			MulProduct.FindOrAdd(Mod.StatTag, 1.0f) *= (Mod.Mul == 0.0f ? 1.0f : Mod.Mul);
		}
	}

	for (const TPair<FGameplayTag, float>& Add : AddSum)
	{
		float& Value = Out.Values.FindOrAdd(Add.Key, 0.0f);
		Value += Add.Value;
	}
	for (const TPair<FGameplayTag, float>& Mul : MulProduct)
	{
		float& Value = Out.Values.FindOrAdd(Mul.Key, 0.0f);
		Value *= Mul.Value;
	}

	return Out;
}

UAnimMontage* UNexusWeaponAssemblyComponent::ResolveActionMontage(const FGameplayTag ActionTag) const
{
	if (!ActionTag.IsValid()) return nullptr;

	// Walk the tree depth-first: deeper attachments are more specific and win
	// ties. We compute depth via parent-walk because the storage is flat.
	auto DepthOf = [this](FGameplayTag Slot) -> int32
	{
		int32 Depth = 0;
		while (Slot.IsValid())
		{
			const FNexusAttachmentInstance* Rec = Attached.Find(Slot);
			if (!Rec) break;
			Slot = Rec->ParentSlotID;
			++Depth;
			if (Depth > 32) break; // sanity
		}
		return Depth;
	};

	UAnimMontage* Best = nullptr;
	int32 BestDepth = -1;

	for (const TPair<FGameplayTag, FNexusAttachmentInstance>& Pair : Attached)
	{
		const UNexusAttachmentDefinition* Def = Pair.Value.Definition;
		if (!Def) continue;
		const TSoftObjectPtr<UAnimMontage>* OverrideRef = Def->AnimationOverrides.Find(ActionTag);
		if (!OverrideRef || OverrideRef->IsNull()) continue;

		const int32 Depth = DepthOf(Pair.Key);
		if (Depth > BestDepth)
		{
			if (UAnimMontage* Loaded = OverrideRef->LoadSynchronous())
			{
				Best      = Loaded;
				BestDepth = Depth;
			}
		}
	}

	if (Best) return Best;

	// Fallback: the equipped actor's authored weapon-mesh action montages
	// (FEquippableAnimationSet::WeaponActionMontages — populated via
	// ANexusEquippedActor on init).
	if (const ANexusEquippedActor* Actor = GetEquippedActor())
	{
		if (UAnimMontage* WeaponSelfMontage = Actor->GetWeaponActionMontage(ActionTag))
		{
			return WeaponSelfMontage;
		}
	}

	return nullptr;
}


// Utility
void UNexusWeaponAssemblyComponent::BroadcastChanged()
{
	if (!HasBegunPlay()) return;
	OnAssemblyChanged.Broadcast();
}