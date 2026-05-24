#include "NexusLoadingGateSubsystem.h"

#include "Camera/PlayerCameraManager.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerController.h"

#include "EMSObject.h"

namespace
{
	const FName NexusLoadReason_SaveLoad(TEXT("SaveLoad"));
}

void UNexusLoadingGateSubsystem::Deinitialize()
{
	if (bSaveLoadBound)
	{
		if (UEMSObject* EMS = UEMSObject::Get(this))
		{
			EMS->OnLevelLoaded.RemoveDynamic(this, &UNexusLoadingGateSubsystem::HandleSaveLoadComplete);
		}
		bSaveLoadBound = false;
	}

	Super::Deinitialize();
}

void UNexusLoadingGateSubsystem::PushHold(FName Reason)
{
	const bool bWasLoading = IsLoading();
	Holds.FindOrAdd(Reason)++;

	if (!bWasLoading)
	{
		ApplyPresentation();
		OnLoadingStateChanged.Broadcast(true);
	}
}

void UNexusLoadingGateSubsystem::PopHold(FName Reason)
{
	int32* Count = Holds.Find(Reason);
	if (!Count) return;   // popping a reason that was never pushed — ignore

	if (--(*Count) <= 0)
	{
		Holds.Remove(Reason);
	}

	if (!IsLoading())
	{
		ApplyPresentation();
		OnLoadingStateChanged.Broadcast(false);
	}
}

void UNexusLoadingGateSubsystem::HoldForSaveLoad()
{
	PushHold(NexusLoadReason_SaveLoad);

	if (!bSaveLoadBound)
	{
		if (UEMSObject* EMS = UEMSObject::Get(this))
		{
			EMS->OnLevelLoaded.AddDynamic(this, &UNexusLoadingGateSubsystem::HandleSaveLoadComplete);
			bSaveLoadBound = true;
		}
	}
}

void UNexusLoadingGateSubsystem::HandleSaveLoadComplete(const TArray<TSoftObjectPtr<AActor>>& /*LoadedActors*/)
{
	if (UEMSObject* EMS = UEMSObject::Get(this))
	{
		EMS->OnLevelLoaded.RemoveDynamic(this, &UNexusLoadingGateSubsystem::HandleSaveLoadComplete);
	}
	bSaveLoadBound = false;

	PopHold(NexusLoadReason_SaveLoad);
}

void UNexusLoadingGateSubsystem::SyncPlayerController(APlayerController* PC)
{
	ApplyToPlayerController(PC);
}

void UNexusLoadingGateSubsystem::ApplyPresentation()
{
	const UGameInstance* GI = GetGameInstance();
	ApplyToPlayerController(GI ? GI->GetFirstLocalPlayerController() : nullptr);
}

void UNexusLoadingGateSubsystem::ApplyToPlayerController(APlayerController* PC)
{
	if (!PC) return;

	if (AppliedPC.Get() != PC)
	{
		// A different PC carries none of our prior input-ignore counts, so treat it
		// as a clean slate before (re)applying the current screen state.
		AppliedState = EApplied::None;
		AppliedPC = PC;
	}

	const bool bShouldShow = IsLoading();

	if (bShouldShow && AppliedState != EApplied::Shown)
	{
		PC->SetIgnoreLookInput(true);
		PC->SetIgnoreMoveInput(true);
		if (PC->PlayerCameraManager)
		{
			PC->PlayerCameraManager->StartCameraFade(1.f, 1.f, 0.01f, FLinearColor::Black, /*bFadeAudio*/ false, /*bHoldWhenFinished*/ true);
		}
		AppliedState = EApplied::Shown;
	}
	else if (!bShouldShow && AppliedState == EApplied::Shown)
	{
		PC->SetIgnoreLookInput(false);
		PC->SetIgnoreMoveInput(false);
		if (PC->PlayerCameraManager)
		{
			PC->PlayerCameraManager->StartCameraFade(1.f, 0.f, 0.6f, FLinearColor::Black, /*bFadeAudio*/ true, /*bHoldWhenFinished*/ false);
		}
		AppliedState = EApplied::Revealed;
	}
}