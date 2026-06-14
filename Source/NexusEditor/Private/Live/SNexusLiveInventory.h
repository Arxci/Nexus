#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"
#include "Widgets/SCompoundWidget.h"

class SBox;
class SVerticalBox;
class SNexusInventoryCanvas;
class FNexusAssetWatcher;
class UNexusItemDefinition;
class UNexusInventoryComponent;
class UNexusItemContainerSubsystem;
class APawn;
class UWorld;
template <typename ItemType> class SComboBox;

/**
 * Live Inventory — a PIE window onto the player's REAL runtime container.
 *
 * Outside Play-In-Editor it is an empty read-only prompt. While PIE runs it polls the live
 * UNexusInventoryComponent (the player's attaché case) and the UNexusItemContainerSubsystem
 * (the shared item box), reflecting grid occupancy, weight, the equipped case and its charm
 * sockets. The grid is drawn by the shipping SNexusInventoryCanvas in read-only mode, so what
 * the designer sees here is exactly what the game packs — no separate renderer to drift.
 *
 * It can also drive the systems it observes, but only through their public runtime API and
 * only while a PIE world is live: spawn items (the canonical AcquireItem path), swap the
 * attaché case (which exercises the overflow-to-box spill), auto-arrange, and clear. Every
 * mutation is gated on a located player inventory; there is no path that writes to content.
 */
class SNexusLiveInventory : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusLiveInventory) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	enum class EView : uint8
	{
		PlayerCase,
		ItemBox,
	};

	/** One option in the spawn / case pickers: a definition plus its display label. */
	struct FPick
	{
		TWeakObjectPtr<UNexusItemDefinition> Def;
		FString Label;
	};

	// --- Live-world location (all null-safe; everything hangs off a live PIE world) ---------
	UWorld* GetPIEWorld() const;
	APawn* GetPlayerPawn() const;
	UNexusInventoryComponent* GetPlayerInventory() const;
	UNexusItemContainerSubsystem* GetBoxSubsystem() const;
	/** True when there is a located player inventory in a running PIE world — mutations allowed. */
	bool IsLive() const;

	// --- Refresh ---------------------------------------------------------------------------
	EActiveTimerReturnType ActiveTick(double InCurrentTime, float InDeltaTime);
	/** Re-read the live container when its contents (or the live state) have changed. */
	void RefreshLive();
	/** Cheap content fingerprint — drives the "only rebuild when something changed" gate. */
	uint32 ComputeSignature() const;

	void SetView(EView InView);
	void RefreshPlayerCase();
	void RefreshItemBox();
	void PopulateSidePanel(UNexusInventoryComponent* Inventory);

	// --- Pickers / mutations ---------------------------------------------------------------
	void RebuildPickLists();
	FReply OnSpawnClicked();
	FReply OnSwapCaseClicked();
	FReply OnAutoArrangeClicked();
	FReply OnClearClicked();

	FText GetStatusText() const;

	// --- Widgets ---------------------------------------------------------------------------
	TSharedPtr<SBox> BodyHost;                 // swaps between the case grid and the box list
	TSharedPtr<SNexusInventoryCanvas> Canvas;  // read-only mirror of the live spatial grid
	TSharedPtr<SVerticalBox> SidePanel;        // weight / case / charms / non-grid items
	TSharedPtr<SVerticalBox> BoxList;          // item-box contents
	TSharedPtr<SWidget> PlayerCaseBody;
	TSharedPtr<SWidget> ItemBoxBody;

	TSharedPtr<SComboBox<TSharedPtr<FPick>>> SpawnCombo;
	TSharedPtr<SComboBox<TSharedPtr<FPick>>> CaseCombo;

	// --- State -----------------------------------------------------------------------------
	EView View = EView::PlayerCase;
	uint32 LastSignature = 0;
	bool bForceRefresh = true;

	TArray<TSharedPtr<FPick>> SpawnOptions;  // every item definition
	TArray<TSharedPtr<FPick>> CaseOptions;   // items carrying a Case fragment
	TSharedPtr<FPick> SelectedSpawn;
	TSharedPtr<FPick> SelectedCase;
	int32 SpawnCount = 1;
	FText LastActionResult;

	/** Refresh the pick lists when items are created / deleted in the editor. */
	TSharedPtr<FNexusAssetWatcher> Watcher;
};
