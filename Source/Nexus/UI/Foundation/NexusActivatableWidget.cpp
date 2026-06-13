#include "NexusActivatableWidget.h"

#include "Engine/LocalPlayer.h"

#include "Nexus/Input/NexusInputContext.h"
#include "Nexus/Input/NexusInputManager.h"
#include "Nexus/UI/Foundation/NexusUILayoutSubsystem.h"

TOptional<FUIInputConfig> UNexusActivatableWidget::GetDesiredInputConfig() const
{
	// Common UI applies this on activation — the widget owns the menu/game input mode. We
	// never call SetInputMode. Mouse capture is paired to the mode the way an FPS expects.
	switch (InputMode)
	{
	case ENexusWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, EMouseCaptureMode::CapturePermanently);
	case ENexusWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	case ENexusWidgetInputMode::All:
		return FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::CaptureDuringMouseDown);
	case ENexusWidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>(); // inherit the layer below
	}
}

void UNexusActivatableWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	const ULocalPlayer* LP = GetOwningLocalPlayer();

	// Pause the world (ref-counted) for an RE-style paused menu.
	if (bPauseWorldWhileActive && LP)
	{
		if (UNexusUILayoutSubsystem* UI = LP->GetSubsystem<UNexusUILayoutSubsystem>())
		{
			UI->PushWorldPause();
			bPausePushed = true;
		}
	}

	// Only an All-mode overlay (world still live) needs to selectively suppress verbs; a
	// Menu-mode screen leaves this empty because Common UI's Menu mode already blocks gameplay.
	if (SuspendGameplayContext && LP)
	{
		if (UNexusInputManager* Manager = LP->GetSubsystem<UNexusInputManager>())
		{
			SuspendHandle = Manager->PushContext(SuspendGameplayContext);
		}
	}
}

void UNexusActivatableWidget::NativeOnDeactivated()
{
	const ULocalPlayer* LP = GetOwningLocalPlayer();

	if (SuspendHandle.IsValid() && LP)
	{
		if (UNexusInputManager* Manager = LP->GetSubsystem<UNexusInputManager>())
		{
			Manager->PopContext(SuspendHandle);
		}
	}
	SuspendHandle = FNexusInputContextHandle();

	if (bPausePushed && LP)
	{
		if (UNexusUILayoutSubsystem* UI = LP->GetSubsystem<UNexusUILayoutSubsystem>())
		{
			UI->PopWorldPause();
		}
	}
	bPausePushed = false;

	Super::NativeOnDeactivated();
}
