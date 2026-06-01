#include "NexusWorldStateSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "EMSObject.h"

UNexusWorldStateSubsystem* UNexusWorldStateSubsystem::Get(const UObject* WorldContext)
{
	if (!WorldContext || !GEngine) return nullptr;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			return GI->GetSubsystem<UNexusWorldStateSubsystem>();
		}
	}
	return nullptr;
}

int32 UNexusWorldStateSubsystem::GetValue(FGameplayTag Key)
{
	EnsureCurrent();
	return States.FindRef(Key);
}

bool UNexusWorldStateSubsystem::GetFlag(FGameplayTag Key)
{
	return GetValue(Key) != 0;
}

bool UNexusWorldStateSubsystem::HasValue(FGameplayTag Key)
{
	return GetValue(Key) != 0;
}

void UNexusWorldStateSubsystem::SetValue(FGameplayTag Key, int32 Value)
{
	if (!Key.IsValid()) return;
	EnsureCurrent();

	const int32 Old = States.FindRef(Key);
	if (Old == Value) return;

	// Treat 0 as "unset" so the map stays clean (GetValue returns 0 for absent keys).
	if (Value == 0)
	{
		States.Remove(Key);
	}
	else
	{
		States.Add(Key, Value);
	}

	Save();
	OnWorldStateChanged.Broadcast(Key, Value);
}

void UNexusWorldStateSubsystem::SetFlag(FGameplayTag Key, bool bValue)
{
	SetValue(Key, bValue ? 1 : 0);
}

int32 UNexusWorldStateSubsystem::ToggleFlag(FGameplayTag Key)
{
	const int32 NewValue = GetFlag(Key) ? 0 : 1;
	SetValue(Key, NewValue);
	return NewValue;
}

void UNexusWorldStateSubsystem::EnsureCurrent()
{
	const FString CurrentSlot = GetCurrentSlotName();
	if (bLoaded && CurrentSlot == LoadedSlotName) return;

	Load();
	LoadedSlotName = CurrentSlot;
	bLoaded = true;
}

FString UNexusWorldStateSubsystem::GetCurrentSlotName() const
{
	if (UEMSObject* EMS = UEMSObject::Get(this))
	{
		return EMS->GetCurrentSaveGameName();
	}
	return FString();
}

void UNexusWorldStateSubsystem::Load()
{
	States.Reset();

	UEMSObject* EMS = UEMSObject::Get(this);
	const UNexusWorldStateSaveGame* SaveObj = EMS
		? Cast<UNexusWorldStateSaveGame>(EMS->GetCustomSave(
			UNexusWorldStateSaveGame::StaticClass(), FString(), FString()))
		: nullptr;

	if (SaveObj)
	{
		States = SaveObj->States;
	}
}

void UNexusWorldStateSubsystem::Save()
{
	UEMSObject* EMS = UEMSObject::Get(this);
	if (!EMS) return;

	UNexusWorldStateSaveGame* SaveObj = Cast<UNexusWorldStateSaveGame>(EMS->GetCustomSave(
		UNexusWorldStateSaveGame::StaticClass(), FString(), FString()));
	if (!SaveObj) return;

	SaveObj->States = States;
	EMS->SaveCustom(SaveObj);
}
