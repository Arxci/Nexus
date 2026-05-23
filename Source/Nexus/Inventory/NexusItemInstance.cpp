#include "NexusItemInstance.h"

#include "Engine/AssetManager.h"
#include "Nexus/NexusAssetManager.h"

#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
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

void UNexusItemInstance::RestoreLoadedState()
{
	if (!CachedDefinition && !DefinitionRef.IsNull())
	{
		CachedDefinition = DefinitionRef.LoadSynchronous();
	}

	RequestEquippedBundleLoad();
}

// Utility
UNexusItemDefinition* UNexusItemInstance::GetDefinition() const
{
	if (CachedDefinition) return CachedDefinition;
	
	return DefinitionRef.LoadSynchronous();
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

bool UNexusItemInstance::CanStackWith(const UNexusItemInstance* Other) const
{
	if (!Other || Other == this) return false;
	if (GetDefinition() != Other->GetDefinition()) return false;
	if (StatTags.Num() != Other->StatTags.Num()) return false;

	for (const TPair<FGameplayTag, int32>& Pair : StatTags)
	{
		const int32* OtherVal = Other->StatTags.Find(Pair.Key);
		if (!OtherVal || *OtherVal != Pair.Value) return false;
	}

	// Stacking would silently drop one side's attachment configuration.
	// Refuse stacking if either side carries customizations.
	if (Attachments.Num() > 0 || Other->Attachments.Num() > 0) return false;

	return true;
}


// Stat
int32 UNexusItemInstance::GetStat(FGameplayTag StatTag, int32 Default) const
{
	if (const int32* Found = StatTags.Find(StatTag))
	{
		return *Found;
	}
	return Default;
}

void UNexusItemInstance::SetStat(FGameplayTag StatTag, int32 Value)
{
	if (!StatTag.IsValid()) return;
	int32* Existing = StatTags.Find(StatTag);
	if (Existing && *Existing == Value) return; 
	StatTags.Add(StatTag, Value);
	BroadcastChanged();
}

int32 UNexusItemInstance::ModifyStat(FGameplayTag StatTag, int32 Delta)
{
	if (!StatTag.IsValid()) return 0;
	int32& Value = StatTags.FindOrAdd(StatTag, 0);
	Value += Delta;
	if (Delta != 0)
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
TSoftObjectPtr<UNexusAttachmentDefinition> UNexusItemInstance::GetAttachmentForSlot(FGameplayTag SlotPath) const
{
	if (const TSoftObjectPtr<UNexusAttachmentDefinition>* Found = Attachments.Find(SlotPath))
	{
		return *Found;
	}
	return TSoftObjectPtr<UNexusAttachmentDefinition>();
}

void UNexusItemInstance::SetAttachmentForSlot(FGameplayTag SlotPath, TSoftObjectPtr<UNexusAttachmentDefinition> Attachment)
{
	if (!SlotPath.IsValid()) return;

	if (Attachment.IsNull())
	{
		ClearAttachmentForSlot(SlotPath);
		return;
	}

	const TSoftObjectPtr<UNexusAttachmentDefinition>* Existing = Attachments.Find(SlotPath);
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