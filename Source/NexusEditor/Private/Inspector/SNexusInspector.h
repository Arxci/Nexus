#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateColor.h"
#include "Widgets/SCompoundWidget.h"

class IDetailsView;
struct FNexusSelection;
struct FPropertyChangedEvent;

/** Raised when an Inspector "Open in …" button is clicked; the Workbench routes it to ShowTool. */
DECLARE_DELEGATE_OneParam(FNexusInspectorJump, FName);

/**
 * The shared Inspector: a persistent IDetailsView on the right of the Workbench that
 * always shows the current Nexus selection, plus the live validation / "where used"
 * banner extracted from the Creator.
 *
 * It subscribes to FNexusSelectionService, so selecting an item in *any* tool drops its
 * editable properties here. Edits flow back through FCoreUObjectDelegates::OnObjectPropertyChanged,
 * which every tool's FNexusAssetWatcher already listens to — so tuning grid-size / weight /
 * value on the right refreshes the Grid / Sandbox / Economy on the left with no extra wiring.
 */
class SNexusInspector : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusInspector) {}
		/** When bound, "Open in …" buttons switch the host Workbench's tool; else they open a tab. */
		SLATE_EVENT(FNexusInspectorJump, OnJumpToTool)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual ~SNexusInspector();

	/** Show the given asset directly (the selection service drives this too). */
	void SetInspected(UObject* Asset);

	/** Suppress the panel for tools that bring their own editor (shows a short note instead). */
	void SetSuppressed(bool bInSuppressed);

private:
	void OnGlobalSelectionChanged(const FNexusSelection& Selection);
	void OnInspectedPropertyChanged(const FPropertyChangedEvent& Event);

	void RefreshValidation();
	FText GetValidationText() const;
	FSlateColor GetValidationColor() const;
	FText GetReferencesTooltip() const;
	EVisibility GetBannerVisibility() const;
	FReply OnBannerClicked();

	/** Cross-tool jump: switch the Workbench to TabName (or open it as a tab) for the current selection. */
	void Jump(FName TabName);
	/** Reveal the inspected asset in the Content Browser. */
	FReply OnBrowseClicked();
	/** Jump buttons only make sense with something selected. */
	EVisibility GetJumpVisibility() const;

	/** 0 = empty-state prompt, 1 = details panel, 2 = "this tool has its own editor". */
	int32 GetContentIndex() const;

	TSharedPtr<IDetailsView> DetailsView;

	/** The asset currently shown (drives the validation/references banner). */
	TWeakObjectPtr<UObject> Inspected;
	FText ValidationSummary;
	FSlateColor ValidationColor = FSlateColor::UseForeground();
	FText ReferencesTooltip;

	/** Handle for the selection-service subscription; removed in the destructor. */
	FDelegateHandle SelectionHandle;

	/** Optional host hook to switch the Workbench's centre tool on a cross-tool jump. */
	FNexusInspectorJump OnJumpToTool;

	/** True while the active tool brings its own editor; the panel shows a note instead. */
	bool bSuppressed = false;
};
