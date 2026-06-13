#pragma once

#include "CoreMinimal.h"

#include "Nexus/UI/Foundation/NexusCommonUserWidget.h"

#include "GameplayTagContainer.h"

#include "NexusPrimaryGameLayout.generated.h"

class UCommonActivatableWidget;
class UCommonActivatableWidgetContainerBase;


/**
 * The primary layout host — the root widget that owns the named activatable layers
 * (UI.Layer.Game / Menu / Modal). Mirrors Lyra's UPrimaryGameLayout, but lightweight and
 * self-contained (the full GameUIPolicy / GameUIManagerSubsystem lives in the CommonGame
 * plugin, which this project doesn't use) and built on the project's own base widget rather
 * than raw UCommonUserWidget.
 *
 * The widget tree — the Canvas / ScaleBox / SizeBox aspect-lock scaling and the three
 * CommonActivatableWidgetStacks — stays authored in the Blueprint. The BP calls RegisterLayer
 * once per stack (PreConstruct/Construct) to bind each stack to its layer tag; everything else
 * is just "push a widget to a layer."
 */
UCLASS(Abstract, Blueprintable)
class NEXUS_API UNexusPrimaryGameLayout : public UNexusCommonUserWidget
{
	GENERATED_BODY()

public:
	/** Bind a layer tag (UI.Layer.*) to one of the BP's activatable stacks. Call once per stack. */
	UFUNCTION(BlueprintCallable, Category = "Nexus|UI")
	void RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* Layer);

	/** Push WidgetClass onto LayerTag's stack and return the instance (null if the layer is unregistered). */
	UFUNCTION(BlueprintCallable, Category = "Nexus|UI", meta = (DeterminesOutputType = "WidgetClass"))
	UCommonActivatableWidget* PushWidgetToLayer(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass);

protected:
	virtual void NativeConstruct() override;

protected:
	/**
	 * Content this layout shows itself once its layers are registered — typically the always-on
	 * HUD on UI.Layer.Game. Authored on the layout asset (data), so no gameplay class (the PC,
	 * the game mode) needs to know the HUD widget and there's no create-order race: the layout
	 * populates itself from its own construct, after RegisterLayer has run. Keyed by layer tag.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Nexus|UI", meta = (Categories = "UI.Layer"))
	TMap<FGameplayTag, TSubclassOf<UCommonActivatableWidget>> InitialContent;

private:
	UPROPERTY(Transient)
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> Layers;

	bool bInitialContentApplied = false;
};
