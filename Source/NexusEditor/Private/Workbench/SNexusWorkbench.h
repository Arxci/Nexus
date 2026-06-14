#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class SBox;
class SButton;
class SSearchBox;
class SNexusInspector;
class FNexusAssetWatcher;
struct FNexusSelection;

/**
 * The Nexus Workbench — the suite's single home, a three-pane window:
 * Navigator | Tool | Inspector.
 *
 * The left Navigator opens the Home page (the old Hub's cards + audit summary)
 * and lists the tools grouped by category (same registry the menu uses);
 * selecting one swaps the centre content area to that tool's widget. Tool
 * widgets are constructed lazily on first selection so opening the Workbench is
 * cheap even though it potentially hosts every panel. The right Inspector is a
 * persistent IDetailsView fed by the shared selection service: clicking an item
 * in any tool shows its editable properties there, and edits propagate back to
 * the tools via their FNexusAssetWatcher.
 *
 * The Workbench's Creator instance reassigns the module's ActiveCreator pointer
 * when it's constructed (same way the standalone Creator tab does), so other
 * tools' "Open in Creator" hand-offs route to whichever Creator was most
 * recently shown.
 */
class SNexusWorkbench : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusWorkbench) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual ~SNexusWorkbench();

	/** Ctrl-K focuses the global search box (best-effort: when focus is inside the Workbench). */
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	/** Internal tab id for the Home page (not a registered nomad tab). */
	static const FName HomeTabName;

private:
	/** Swap the content area to the tool registered under TabName, constructing it on first use. */
	void ShowTool(FName TabName);

	/** Construct a fresh widget for the given tool tab; null if TabName isn't recognised. */
	TSharedPtr<SWidget> ConstructToolWidget(FName TabName);

	/** Bound to the title above the content panel. */
	FText GetCurrentToolLabel() const;

	/** Build the Navigator: a search box over a switcher of (tool list | search results). */
	TSharedRef<SWidget> BuildNavigator();

	/** Build the tool list (Home + categorised stack of tool buttons + footer actions). */
	TSharedRef<SWidget> BuildSidebar();

	/** Build one sidebar button for a tool entry, with checked state when it's active. */
	TSharedRef<SWidget> BuildSidebarEntry(FName TabName, const FText& Label, const FName IconName, const FText& Tooltip);

	// --- Ctrl-K search over items / attachments / recipes ----------------------
	struct FSearchEntry
	{
		TWeakObjectPtr<UObject> Object;
		FString Name;
		FString Type;                          // "Item" / "Attachment" / "Recipe"
		FString Path;                          // object path, for pin/recent persistence
		FLinearColor TypeColor = FLinearColor::White;
	};
	void BuildSearchIndex();
	void OnSearchTextChanged(const FText& Text);
	void ApplySearchFilter();
	/** 0 = tool list, 1 = search results (when the query is non-empty). */
	int32 GetNavIndex() const;
	TSharedRef<ITableRow> OnGenerateSearchRow(TSharedPtr<FSearchEntry> Entry, const TSharedRef<STableViewBase>& Owner);
	void OnSearchSelectionChanged(TSharedPtr<FSearchEntry> Entry, ESelectInfo::Type SelectInfo);
	void FocusSearch();

	// Pinned + recent quick-access (persisted per-user).
	void OnGlobalSelectionChanged(const FNexusSelection& Selection);   // records recents
	void RebuildQuickAccess();
	TSharedRef<ITableRow> OnGenerateQuickRow(TSharedPtr<FSearchEntry> Entry, const TSharedRef<STableViewBase>& Owner);
	TSharedRef<SWidget> MakePinButton(TSharedPtr<FSearchEntry> Entry);
	TSharedPtr<FSearchEntry> FindIndexed(const FString& Path) const;
	bool IsPinned(const FString& Path) const;
	void TogglePin(const FString& Path);
	EVisibility GetQuickAccessVisibility() const;

	/** Currently shown tool's TabName; NAME_None when nothing has been shown yet. */
	FName CurrentTab;

	/** Tool widgets cached by tab name — built on first selection, reused after. */
	TMap<FName, TSharedPtr<SWidget>> ToolCache;

	/** Centre content host. */
	TSharedPtr<SBox> ContentBox;

	/** Right-hand Inspector, fed by the shared selection service. */
	TSharedPtr<SNexusInspector> Inspector;

	/** Splitter weights (Navigator / Tool / Inspector), restored from / saved to per-user config. */
	float NavValue = 0.18f;
	float ToolValue = 0.58f;
	float InspectorValue = 0.24f;

	// Search state.
	TSharedPtr<SSearchBox> SearchBox;
	TSharedPtr<SListView<TSharedPtr<FSearchEntry>>> SearchListView;
	TArray<TSharedPtr<FSearchEntry>> SearchIndex;     // every searchable asset
	TArray<TSharedPtr<FSearchEntry>> SearchResults;   // filtered view bound to the list
	FString SearchQuery;
	TSharedPtr<FNexusAssetWatcher> SearchWatcher;

	// Pinned + recent.
	TSharedPtr<SListView<TSharedPtr<FSearchEntry>>> QuickList;
	TArray<TSharedPtr<FSearchEntry>> QuickAccess;     // pinned first, then recents
	TArray<FString> PinnedPaths;
	TArray<FString> RecentPaths;
	FDelegateHandle SelectionHandle;
};
