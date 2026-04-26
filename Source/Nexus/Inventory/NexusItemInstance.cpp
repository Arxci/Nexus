#include "NexusItemInstance.h"

#include "NexusItemDefinition.h"
#include "NexusItemFragment.h"

UNexusItemInstance::UNexusItemInstance()
{
}

void UNexusItemInstance::Initialize(UNexusItemDefinition* InDefinition, int32 InStackCount)
{
	if (!InDefinition) return;

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
}

UNexusItemDefinition* UNexusItemInstance::GetDefinition() const
{
	if (CachedDefinition) return CachedDefinition;
	// Loaded path: rehydrate the soft ref. Caller is responsible for accepting a sync load here.
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

int32 UNexusItemInstance::ModifyStack(int32 Delta, int32 MaxStack)
{
	const int32 Clamped = FMath::Clamp(StackCount + Delta, 0, MaxStack);
	const int32 Applied = Clamped - StackCount;
	StackCount = Clamped;
	return Applied;
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