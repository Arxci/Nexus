#include "NexusItemInstance.h"

#include "Engine/AssetManager.h"
#include "Nexus/Nexus.h"
#include "Nexus/NexusAssetManager.h"

#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"


void UNexusItemInstance::Initialize(UNexusItemDefinition* InDefinition, int32 InStackCount)
{
	if (!ensureMsgf(InDefinition, TEXT("Initialize called with null Definition"))) return;
	if (!ensureMsgf(!bInitialized, TEXT("Initialize called twice on %s"), *GetName())) return;

	CachedDefinition = InDefinition;
	DefinitionRef    = InDefinition;
	StackCount       = FMath::Max(1, InStackCount);

	// Generate GUID
	if (!InstanceGuid.IsValid())
	{
		InstanceGuid = FGuid::NewGuid();
	}

	for (const TInstancedStruct<FNexusItemFragment>& Frag : InDefinition->Fragments)
	{
		if (Frag.IsValid())
		{
			Frag.Get().InitializeInstance(this);
		}
	}
	
	RequestEquippedBundleLoad();
	
	bInitialized = true;
}

FNexusItemSaveData UNexusItemInstance::ToSaveData() const
{
	FNexusItemSaveData Data;
	Data.DefinitionRef = CachedDefinition
		? TSoftObjectPtr<UNexusItemDefinition>(CachedDefinition.Get())
		: DefinitionRef;
	Data.InstanceGuid = InstanceGuid;
	Data.StackCount   = StackCount;
	Data.StatTags     = StatTags;
	Data.Attachments  = Attachments;
	Data.SocketedItems = SocketedItems;
	Data.GridPosition = GridPosition;
	Data.bRotated     = bRotated;
	return Data;
}

bool UNexusItemInstance::LoadFromSaveData(const FNexusItemSaveData& SaveData)
{
	DefinitionRef = SaveData.DefinitionRef;

	// Sync load is intentional: save-restore always runs behind the loading screen.
	CachedDefinition = DefinitionRef.LoadSynchronous();
	if (!CachedDefinition)
	{
		UE_LOG(LogNexusInventory, Warning,
			TEXT("Saved item definition '%s' could not be loaded (asset removed or renamed "
				 "without a redirector). Dropping item from restored inventory."),
			*DefinitionRef.ToSoftObjectPath().ToString());
		return false;
	}

	InstanceGuid = SaveData.InstanceGuid.IsValid() ? SaveData.InstanceGuid : FGuid::NewGuid();
	StackCount   = FMath::Max(0, SaveData.StackCount);
	StatTags     = SaveData.StatTags;
	Attachments  = SaveData.Attachments;
	SocketedItems = SaveData.SocketedItems;
	GridPosition = SaveData.GridPosition;
	bRotated     = SaveData.bRotated;

	// H1: a restored instance must be considered live, otherwise BroadcastChanged
	// early-outs forever and reloading a restored weapon never updates the HUD.
	bInitialized = true;

	RequestEquippedBundleLoad();
	return true;
}

UNexusItemDefinition* UNexusItemInstance::GetDefinition() const
{
	// Populated by Initialize() or LoadFromSaveData(). Null is possible only in
	// degenerate cases: an instance queried before either ran, or a save whose
	// definition asset was dropped from the build (LoadFromSaveData logs and skips
	// those on restore). Every caller null-checks the result — we degrade
	// gracefully rather than crash a player's session over one missing data asset.
	return CachedDefinition;
}

FGameplayTag UNexusItemInstance::GetIdentityTag() const
{
	if (const UNexusItemDefinition* Def = GetDefinition())
	{
		return Def->IdentityTag;
	}
	return FGameplayTag();
}


// Stack
int32 UNexusItemInstance::ModifyStack(int32 Delta, int32 MaxStack)
{
	const int64 Wide      = static_cast<int64>(StackCount) + static_cast<int64>(Delta);
	const int64 ClampedW  = FMath::Clamp<int64>(Wide, 0, MaxStack);
	const int32 Clamped   = static_cast<int32>(ClampedW);
	const int32 Applied   = Clamped - StackCount;
	
	StackCount = Clamped;
	
	return Applied;
}

bool UNexusItemInstance::IsMergeableStack() const
{
	// A fungible stack carries no per-instance state: no stat tags (e.g. a partial
	// magazine or a treasure's socketed gem value), no attachments, no socketed items
	// (a case's charms / a treasure's gems). Anything customised gets its own slot so
	// merging can never silently drop one side's state.
	return StatTags.Num() == 0 && Attachments.Num() == 0 && SocketedItems.Num() == 0;
}

bool UNexusItemInstance::CanStackWith(const UNexusItemInstance* Other) const
{
	if (!Other || Other == this) return false;
	if (GetDefinition() != Other->GetDefinition()) return false;
	return IsMergeableStack() && Other->IsMergeableStack();
}


// Stat
float UNexusItemInstance::GetStat(FGameplayTag StatTag, float Default) const
{
	if (const float* Found = StatTags.Find(StatTag))
	{
		return *Found;
	}
	return Default;
}

void UNexusItemInstance::SetStat(FGameplayTag StatTag, float Value)
{
	if (!StatTag.IsValid()) return;
	float* Existing = StatTags.Find(StatTag);
	if (Existing && *Existing == Value) return;
	StatTags.Add(StatTag, Value);
	BroadcastChanged();
}

float UNexusItemInstance::ModifyStat(FGameplayTag StatTag, float Delta)
{
	if (!StatTag.IsValid()) return 0.0f;
	float& Value = StatTags.FindOrAdd(StatTag, 0.0f);
	Value += Delta;
	if (Delta != 0.0f)
	{
		BroadcastChanged();
	}
	return Value;
}

bool UNexusItemInstance::HasStat(FGameplayTag StatTag) const
{
	return StatTags.Contains(StatTag);
}

// Attachments
TSoftObjectPtr<UObject> UNexusItemInstance::GetAttachmentForSlot(FGameplayTag SlotPath) const
{
	if (const TSoftObjectPtr<UObject>* Found = Attachments.Find(SlotPath))
	{
		return *Found;
	}
	return TSoftObjectPtr<UObject>();
}

void UNexusItemInstance::SetAttachmentForSlot(FGameplayTag SlotPath, TSoftObjectPtr<UObject> Attachment)
{
	if (!SlotPath.IsValid()) return;

	if (Attachment.IsNull())
	{
		ClearAttachmentForSlot(SlotPath);
		return;
	}

	const TSoftObjectPtr<UObject>* Existing = Attachments.Find(SlotPath);
	if (Existing && *Existing == Attachment) return;

	Attachments.Add(SlotPath, Attachment);
	BroadcastChanged();
}

void UNexusItemInstance::ClearAttachmentForSlot(FGameplayTag SlotPath)
{
	if (Attachments.Remove(SlotPath) > 0)
	{
		BroadcastChanged();
	}
}

// Sockets
TSoftObjectPtr<UNexusItemDefinition> UNexusItemInstance::GetSocketedItem(FGameplayTag SlotTag) const
{
	if (const TSoftObjectPtr<UNexusItemDefinition>* Found = SocketedItems.Find(SlotTag))
	{
		return *Found;
	}
	return TSoftObjectPtr<UNexusItemDefinition>();
}

void UNexusItemInstance::SetSocketedItem(FGameplayTag SlotTag, TSoftObjectPtr<UNexusItemDefinition> ItemDef)
{
	if (!SlotTag.IsValid()) return;

	if (ItemDef.IsNull())
	{
		ClearSocketedItem(SlotTag);
		return;
	}

	const TSoftObjectPtr<UNexusItemDefinition>* Existing = SocketedItems.Find(SlotTag);
	if (Existing && *Existing == ItemDef) return;

	SocketedItems.Add(SlotTag, ItemDef);
	BroadcastChanged();
}

void UNexusItemInstance::ClearSocketedItem(FGameplayTag SlotTag)
{
	if (SocketedItems.Remove(SlotTag) > 0)
	{
		BroadcastChanged();
	}
}

// Grid placement
FIntPoint UNexusItemInstance::GetGridFootprint() const
{
	FIntPoint Size(1, 1);
	if (const UNexusItemDefinition* Def = GetDefinition())
	{
		Size.X = FMath::Max(1, Def->GridSize.X);
		Size.Y = FMath::Max(1, Def->GridSize.Y);
	}
	if (bRotated)
	{
		Swap(Size.X, Size.Y);
	}
	return Size;
}

void UNexusItemInstance::SetGridPlacement(FIntPoint InPosition, bool bInRotated)
{
	GridPosition = InPosition;
	bRotated     = bInRotated;
}

void UNexusItemInstance::BroadcastChanged()
{
	if (!bInitialized) return; 
	OnInstanceChanged.Broadcast(this);
}

void UNexusItemInstance::RequestEquippedBundleLoad()
{
	if (EquippedBundleHandle.IsValid()) return;

	const UNexusItemDefinition* Def = CachedDefinition;
	if (!Def) return;

	// Skip non-equippables — ammo, herbs, keys, etc. have nothing in the
	// Equipped bundle, so the load would just hold an empty handle.
	if (!Def->HasFragment<FNexusFragment_Equippable>()) return;

	const FPrimaryAssetId Id = Def->GetPrimaryAssetId();
	if (!Id.IsValid()) return;

	EquippedBundleHandle = UAssetManager::Get().LoadPrimaryAsset(
		Id, TArray<FName>{ UNexusAssetManager::BundleEquipped });
}