#pragma once

#include "CoreMinimal.h"

#include "Subsystems/LocalPlayerSubsystem.h"

#include "GameplayTagContainer.h"

#include "Templates/SubclassOf.h"

#include "NexusUILayoutSubsystem.generated.h"

class APlayerController;
class UCommonActivatableWidget;
class UNexusPrimaryGameLayout;


/**
 * One requestable UI screen: which widget opens, and on which layer. This is the bridge
 * between C++ (which only knows the panel tag) and Blueprint (which owns the widget asset) —
 * a designer points a tag at a BP widget, so gameplay code never references a widget.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusUIPanelDef
{
	GENERATED_BODY()

	/**
	 * The activatable widget (a Blueprint) to open for this tag. SOFT on purpose: the owner
	 * (the PC's PanelMap) does NOT hard-reference your menu widgets, so they aren't pulled into
	 * memory until a panel is actually opened — no coupling/load just by listing them.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (MetaClass = "/Script/CommonUI.CommonActivatableWidget"))
	TSoftClassPtr<UCommonActivatableWidget> Widget;

	/** Which layer it opens on (defaults to UI.Layer.Menu when unset). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (Categories = "UI.Layer"))
	FGameplayTag Layer;
};


/**
 * Lightweight per-local-player owner of the primary UI layout — the self-contained stand-in
 * for Lyra's GameUIManagerSubsystem / GameUIPolicy (which live in the unused CommonGame
 * plugin). It:
 *   - creates the layout and adds it to the viewport,
 *   - ref-counts world pause so stacked RE-style paused menus pause once,
 *   - and is the single listener on UNexusUIRequestSubsystem: gameplay (interaction, an input
 *     verb's RequestUIPanelTag) posts "open panel tagged X"; this resolves the tag through the
 *     PC's panel map and pushes the mapped widget. That's how a C++ request opens a BP widget.
 *
 * Player-only by construction; no-op for an AI-only context.
 */
UCLASS()
class NEXUS_API UNexusUILayoutSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	static UNexusUILayoutSubsystem* Get(const ULocalPlayer* LocalPlayer);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Create the layout (if not already) from LayoutClass, owned by PC, add it to the viewport,
	 * and adopt the tag->widget panel map used to answer UI requests.
	 */
	void CreateLayout(APlayerController* OwningController, TSubclassOf<UNexusPrimaryGameLayout> LayoutClass,
		const TMap<FGameplayTag, FNexusUIPanelDef>& InPanels);

	UFUNCTION(BlueprintPure, Category = "Nexus|UI")
	UNexusPrimaryGameLayout* GetLayout() const { return Layout; }

	/** Ref-counted world pause: first push pauses, last pop resumes (handles stacked paused menus). */
	void PushWorldPause();
	void PopWorldPause();

protected:
	/** UNexusUIRequestSubsystem::OnUIPanelRequested -> resolve the tag through the panel map and open it. */
	UFUNCTION()
	void HandlePanelRequested(FGameplayTag PanelTag, AActor* Source);

private:
	void SetWorldPaused(bool bPaused);

	UPROPERTY(Transient)
	TObjectPtr<UNexusPrimaryGameLayout> Layout;

	/** tag -> { widget, layer }; populated from the PC's config. The C++ <-> BP widget bridge. */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FNexusUIPanelDef> Panels;

	int32 PauseRefCount = 0;
};
