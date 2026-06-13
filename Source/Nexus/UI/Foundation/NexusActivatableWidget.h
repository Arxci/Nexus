#pragma once

#include "CoreMinimal.h"

#include "CommonActivatableWidget.h"

#include "Input/CommonUIInputTypes.h"

#include "Nexus/Input/NexusInputTypes.h"

#include "NexusActivatableWidget.generated.h"

class UNexusInputContext;


/**
 * How this screen wants input routed while it's the active (top-most) widget. Common UI
 * reads it from GetDesiredInputConfig and applies it — the widget is the source of truth
 * for input mode, so nothing ever calls SetInputMode. Mirrors Lyra's ELyraWidgetInputMode.
 */
UENUM(BlueprintType)
enum class ENexusWidgetInputMode : uint8
{
	/** Don't override — inherit whatever the layer below established. */
	Default UMETA(DisplayName = "Default (inherit)"),
	/** Gameplay input only; mouse captured, cursor hidden. The always-on HUD uses this. */
	Game    UMETA(DisplayName = "Game"),
	/** UI navigation only; gameplay input blocked, cursor shown. Full-screen menus use this. */
	Menu    UMETA(DisplayName = "Menu"),
	/** Both gameplay and UI input live at once. Interactive overlays used while playing. */
	All     UMETA(DisplayName = "All (game + menu)"),
};


/**
 * Project base for every screen pushed onto a Common UI activatable layer (HUD, pause,
 * inventory, dialog, confirm popups). It owns the two cross-cutting concerns so designers
 * never hand-wire them per widget:
 *
 *  1. Input mode — GetDesiredInputConfig is driven by the InputMode enum. (This is why the
 *     HUD must be Game: with no widget declaring a config, Common UI falls back to Menu and
 *     gameplay input is blocked.)
 *  2. World pause — bPauseWorldWhileActive pauses the world on activation (the RE-style
 *     paused inventory / menu) and unpauses on deactivation, ref-counted so stacked paused
 *     screens behave.
 *
 * For a full-screen Menu-mode screen that's left empty, nothing else is needed — Common UI's
 * Menu mode already stops gameplay input, so the Nexus input stack is not involved.
 * SuspendGameplayContext is the rare opt-in for an All-mode overlay (world still live) that
 * wants to suppress specific verbs (e.g. block Fire but allow Move).
 */
UCLASS(Abstract, Blueprintable)
class NEXUS_API UNexusActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	//~Begin UCommonActivatableWidget
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	//~End UCommonActivatableWidget

protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

protected:
	/** Input routing while this screen is active. Menu for full-screen screens; Game for the HUD. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Nexus|UI")
	ENexusWidgetInputMode InputMode = ENexusWidgetInputMode::Menu;

	/** Pause the world while active (the RE-style paused inventory / menu). Ref-counted across screens. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Nexus|UI")
	bool bPauseWorldWhileActive = false;

	/**
	 * Optional: a Nexus input context to push while active — only for an All-mode overlay
	 * (world still live) that needs to suppress specific gameplay verbs. Leave empty for a
	 * normal Menu-mode screen; Common UI's Menu mode already stops gameplay input.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Nexus|UI")
	TObjectPtr<UNexusInputContext> SuspendGameplayContext;

private:
	FNexusInputContextHandle SuspendHandle;
	bool bPausePushed = false;
};
