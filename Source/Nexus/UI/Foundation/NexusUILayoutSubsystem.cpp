#include "NexusUILayoutSubsystem.h"

#include "CommonActivatableWidget.h"

#include "Blueprint/UserWidget.h"
#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"

#include "Nexus/Nexus.h"
#include "Nexus/Game/NexusUIRequestSubsystem.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/UI/Foundation/NexusPrimaryGameLayout.h"

UNexusUILayoutSubsystem* UNexusUILayoutSubsystem::Get(const ULocalPlayer* LocalPlayer)
{
	return LocalPlayer ? LocalPlayer->GetSubsystem<UNexusUILayoutSubsystem>() : nullptr;
}

void UNexusUILayoutSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Listen for "open panel tagged X" requests (interaction effects, input verbs). This is the
	// one place that turns a decoupled, widget-agnostic gameplay request into an actual push.
	const ULocalPlayer* LP = GetLocalPlayer<ULocalPlayer>();
	if (UGameInstance* GI = LP ? LP->GetGameInstance() : nullptr)
	{
		if (UNexusUIRequestSubsystem* Requests = GI->GetSubsystem<UNexusUIRequestSubsystem>())
		{
			Requests->OnUIPanelRequested.AddDynamic(this, &UNexusUILayoutSubsystem::HandlePanelRequested);
		}
	}
}

void UNexusUILayoutSubsystem::Deinitialize()
{
	if (const ULocalPlayer* LP = GetLocalPlayer<ULocalPlayer>())
	{
		if (UGameInstance* GI = LP->GetGameInstance())
		{
			if (UNexusUIRequestSubsystem* Requests = GI->GetSubsystem<UNexusUIRequestSubsystem>())
			{
				Requests->OnUIPanelRequested.RemoveDynamic(this, &UNexusUILayoutSubsystem::HandlePanelRequested);
			}
		}
	}

	// Don't strand a paused world if the player teardown happens with a menu open.
	if (PauseRefCount > 0)
	{
		PauseRefCount = 0;
		SetWorldPaused(false);
	}
	if (Layout)
	{
		Layout->RemoveFromParent();
		Layout = nullptr;
	}
	Super::Deinitialize();
}

void UNexusUILayoutSubsystem::CreateLayout(APlayerController* OwningController, TSubclassOf<UNexusPrimaryGameLayout> LayoutClass,
	const TMap<FGameplayTag, FNexusUIPanelDef>& InPanels)
{
	Panels = InPanels;

	if (Layout || !OwningController || !LayoutClass)
	{
		return;
	}

	Layout = CreateWidget<UNexusPrimaryGameLayout>(OwningController, LayoutClass);
	if (Layout)
	{
		Layout->AddToViewport();
#if !UE_BUILD_SHIPPING
		UE_LOG(LogNexusGame, Verbose, TEXT("[UI] Created primary layout %s for %s (%d panel mapping(s))."),
			*GetNameSafe(Layout), *GetNameSafe(OwningController), Panels.Num());
#endif
	}
}

void UNexusUILayoutSubsystem::HandlePanelRequested(FGameplayTag PanelTag, AActor* /*Source*/)
{
	if (!Layout)
	{
		return; // no layout yet (request arrived before the player's UI was created)
	}

	const FNexusUIPanelDef* Def = Panels.Find(PanelTag);
	if (!Def || Def->Widget.IsNull())
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogNexusGame, Warning, TEXT("[UI] Panel requested with no mapping/widget: %s"), *PanelTag.ToString());
#endif
		return;
	}

	// Load the widget class on demand (it's a soft ref, so this is the first time it touches
	// memory). A synchronous load on a user-initiated panel open is acceptable.
	UClass* WidgetClass = Def->Widget.LoadSynchronous();
	if (!WidgetClass)
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogNexusGame, Warning, TEXT("[UI] Panel %s failed to load its widget class."), *PanelTag.ToString());
#endif
		return;
	}

	const FGameplayTag Layer = Def->Layer.IsValid() ? Def->Layer : NexusGameplayTags::UI_Layer_Menu;
	Layout->PushWidgetToLayer(Layer, WidgetClass);
}

void UNexusUILayoutSubsystem::PushWorldPause()
{
	if (++PauseRefCount == 1)
	{
		SetWorldPaused(true);
	}
}

void UNexusUILayoutSubsystem::PopWorldPause()
{
	if (PauseRefCount <= 0)
	{
		return;
	}
	if (--PauseRefCount == 0)
	{
		SetWorldPaused(false);
	}
}

void UNexusUILayoutSubsystem::SetWorldPaused(bool bPaused)
{
	const ULocalPlayer* LP = GetLocalPlayer<ULocalPlayer>();
	if (APlayerController* PC = LP ? LP->GetPlayerController(LP->GetWorld()) : nullptr)
	{
		PC->SetPause(bPaused);
	}
}
