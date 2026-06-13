#include "NexusInputRebindFacade.h"

#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"

#include "Engine/LocalPlayer.h"

#include "Nexus/Nexus.h"

void UNexusInputRebindFacade::Initialize(ULocalPlayer* InLocalPlayer)
{
	LocalPlayer = InLocalPlayer;
}

UEnhancedInputUserSettings* UNexusInputRebindFacade::GetUserSettings() const
{
	const ULocalPlayer* LP = LocalPlayer.Get();
	if (!LP)
	{
		return nullptr;
	}
	if (UEnhancedInputLocalPlayerSubsystem* EI = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		// Null unless the project enabled Enhanced Input User Settings — the facade degrades to
		// a safe no-op in that case.
		return EI->GetUserSettings();
	}
	return nullptr;
}

bool UNexusInputRebindFacade::IsAvailable() const
{
	return GetUserSettings() != nullptr;
}

void UNexusInputRebindFacade::RegisterContext(const UInputMappingContext* MappingContext)
{
	if (UEnhancedInputUserSettings* Settings = GetUserSettings())
	{
		if (MappingContext)
		{
			Settings->RegisterInputMappingContext(MappingContext);
		}
	}
}

bool UNexusInputRebindFacade::ApplyKey(FName MappingName, FKey NewKey)
{
	UEnhancedInputUserSettings* Settings = GetUserSettings();
	if (!Settings || MappingName.IsNone())
	{
		return false;
	}

	FMapPlayerKeyArgs Args;
	Args.MappingName = MappingName;
	Args.Slot = EPlayerMappableKeySlot::First;
	Args.NewKey = NewKey;

	FGameplayTagContainer FailureReason;
	Settings->MapPlayerKey(Args, FailureReason);
	Settings->ApplySettings();
	Settings->AsyncSaveSettings();

#if !UE_BUILD_SHIPPING
	if (!FailureReason.IsEmpty())
	{
		UE_LOG(LogNexusInput, Warning, TEXT("[Input] Rebind %s -> %s failed: %s"),
			*MappingName.ToString(), *NewKey.ToString(), *FailureReason.ToString());
	}
#endif
	return FailureReason.IsEmpty();
}

TArray<FName> UNexusInputRebindFacade::ListMappingNames() const
{
	TArray<FName> Names;
	if (const UEnhancedInputUserSettings* Settings = GetUserSettings())
	{
		if (const UEnhancedPlayerMappableKeyProfile* Profile = Settings->GetActiveKeyProfile())
		{
			Profile->GetPlayerMappingRows().GetKeys(Names);
		}
	}
	return Names;
}

void UNexusInputRebindFacade::Save()
{
	if (UEnhancedInputUserSettings* Settings = GetUserSettings())
	{
		Settings->ApplySettings();
		Settings->AsyncSaveSettings();
	}
}
