#include "NexusItemInstance.h"

#include "NexusItemDefinition.h"
#include "NexusItemFragment.h"

UNexusItemInstance::UNexusItemInstance()
{
}

void UNexusItemInstance::Initialize(UNexusItemDefinition* InDefinition, int32 InStackCount)
{
	if (!ensureMsgf(InDefinition, TEXT("Initialize called with null Definition"))) return;
	if (!ensureMsgf(!bInitialized, TEXT("Initialize called twice on %s"), *GetName())) return;

	CachedDefinition = InDefinition;
	DefinitionRef    = InDefinition;
	StackCount       = FMath::Max(1, InStackCount);

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

	bInitialized = true;
}

UNexusItemDefinition* UNexusItemInstance::GetDefinition() const
{
	if (CachedDefinition) return CachedDefinition;
	
	return DefinitionRef.LoadSynchronous();
}

void UNexusItemInstance::RestoreLoadedState()
{
	if (!CachedDefinition && !DefinitionRef.IsNull())
	{
		CachedDefinition = DefinitionRef.LoadSynchronous();
	}
}

FGameplayTag UNexusItemInstance::GetIdentityTag() const
{
	if (const UNexusItemDefinition* Def = GetDefinition())
	{
		return Def->IdentityTag;
	}
	return FGameplayTag();
}

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
	return true;
}

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
	StatTags.Add(StatTag, Value);
}

int32 UNexusItemInstance::ModifyStat(FGameplayTag StatTag, int32 Delta)
{
	if (!StatTag.IsValid()) return 0;
	int32& Value = StatTags.FindOrAdd(StatTag, 0);
	Value += Delta;
	return Value;
}

bool UNexusItemInstance::HasStat(FGameplayTag StatTag) const
{
	return StatTags.Contains(StatTag);
}