#include "NexusPrimaryGameLayout.h"

#include "CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "Nexus/Nexus.h"

void UNexusPrimaryGameLayout::NativeConstruct()
{
	Super::NativeConstruct();

	// Populate default content once the layers are up. Super::NativeConstruct above fired the
	// Blueprint Construct event (where RegisterLayer runs), so the stacks are registered here.
	// Driven by data on this layout, so nothing external pushes the HUD and there's no race.
	if (!bInitialContentApplied)
	{
		bInitialContentApplied = true;
		for (const TPair<FGameplayTag, TSubclassOf<UCommonActivatableWidget>>& Entry : InitialContent)
		{
			if (Entry.Value)
			{
				PushWidgetToLayer(Entry.Key, Entry.Value);
			}
		}
	}
}

void UNexusPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* Layer)
{
	if (LayerTag.IsValid() && Layer)
	{
		Layers.Add(LayerTag, Layer);
	}
}

UCommonActivatableWidget* UNexusPrimaryGameLayout::PushWidgetToLayer(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!WidgetClass)
	{
		return nullptr;
	}
	const TObjectPtr<UCommonActivatableWidgetContainerBase>* Layer = Layers.Find(LayerTag);
	if (!Layer || !*Layer)
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogNexusGame, Warning, TEXT("[UI] PushWidgetToLayer: no stack registered for layer %s."), *LayerTag.ToString());
#endif
		return nullptr;
	}
	// The pushed widget's activation owns its input mode (and any pause) via UNexusActivatableWidget.
	return (*Layer)->AddWidget<UCommonActivatableWidget>(WidgetClass);
}
