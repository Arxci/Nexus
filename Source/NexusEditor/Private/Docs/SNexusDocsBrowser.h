#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"

#include "Docs/NexusDocsModel.h"

class SComboButton;
class SEditableTextBox;
class SScrollBox;
class SSearchBox;
class STextBlock;
template <typename ItemType> class SListView;

/**
 * Three-pane API reference browser. Designed for the designer audience:
 *
 *  - Header band: title, content-coverage summary (X classes · Y functions ·
 *    Z% documented), a type-filter row (All / Components / Subsystems / ...),
 *    back/forward history, refresh.
 *  - Left pane: search box + collapsible tree grouped by folder (Combat,
 *    Inventory, Weapon, ...). Each leaf carries a consistent coloured type
 *    chip ("COMP" / "SUB" / "STRUCT" / ...) so designers can scan the tree
 *    without trying to decode mismatched icons. Category rows show a member
 *    count and a click-to-collapse caret.
 *  - Right pane: a header card (display name, kind chip, kind tooltip,
 *    parent/derived links, "Used By" callers, source path with Open Source
 *    and Copy buttons), a Summary chip row that scrolls to each section, a
 *    member quick-filter, member sort toggle (by Category vs by Name), and the
 *    Functions / Events / Properties sections rendered as cards. Function rows
 *    show a Blueprint-style signature, badges (Pure / Callable / Event /
 *    Server / Latent / Static), description, parameters with descriptions, and
 *    the return value.
 *  - Footer: a collapsible Reading Guide that explains the type chips, the
 *    function badges, and links out to the architecture markdown files in
 *    Docs/ (rendered inline, with full bold / italic / code / list support, by
 *    the NexusMarkdown reader).
 *
 * The header band's "Export Markdown" button writes the whole reference to a
 * single committable Markdown file (NexusDocs::ExportMarkdown) under Saved/.
 *
 * The model is rebuilt on construction and on "Refresh"; both walks are O(every
 * UCLASS) but cheap (sub-100ms in a project this size). A "Show internal API"
 * toggle includes classes whose public surface area has no BlueprintCallable /
 * BlueprintPure members, so engineers can still browse the full module.
 * Pinned types, navigation history, and the last-viewed type persist per-user
 * across editor restarts.
 */
class SNexusDocsBrowser : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusDocsBrowser) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	// === Tree node ==========================================================
	struct FNode
	{
		FString Label;
		// One of these two is set per node. Class entry for leaves; nothing for
		// category headers (Children carries leaves under them).
		TSharedPtr<FNexusDocClass> ClassEntry;
		TArray<TSharedPtr<FNode>> Children;
	};
	using FNodePtr = TSharedPtr<FNode>;

	/** Sort modes for the in-class member list. */
	enum class EMemberSort : uint8 { ByCategory, ByName };

	// === Data ===============================================================
	FNexusDocCollection Collection;
	TArray<FNodePtr> RootNodes;
	TSharedPtr<FNexusDocClass> SelectedClass;
	FString CurrentSearch;
	bool bShowInternalApi = false;

	/** Which top-level kinds the tree shows. ENexusDocKind values + UINT8_MAX = "all". */
	uint8 ActiveKindFilter = TNumericLimits<uint8>::Max();

	/** Linear navigation history of selected type names (back/forward). */
	TArray<FString> History;
	int32 HistoryIndex = INDEX_NONE;

	/** Pinned type names — small, in-memory set that survives Refresh but not editor restart. */
	TSet<FString> Pinned;

	/** Per-class detail-pane filter on member name; resets when the selection changes. */
	FString MemberFilter;
	EMemberSort MemberSort = EMemberSort::ByCategory;

	/** Type name the detail pane currently shows; used to reset the member filter only on a real change. */
	FString DetailedTypeName;

	/** Markdown architecture docs discovered under <Project>/Docs at construction time. */
	struct FArchDoc
	{
		FString DisplayName;     // "Attachment Architecture"
		FString AbsolutePath;    // resolved path to the .md
	};
	TArray<FArchDoc> ArchDocs;

	// === Widgets ============================================================
	TSharedPtr<STreeView<FNodePtr>> TreeView;
	TSharedPtr<SScrollBox> DetailScroll;
	TSharedPtr<SSearchBox> SearchBox;
	TSharedPtr<SSearchBox> MemberFilterBox;
	TSharedPtr<STextBlock> StatsText;

	/**
	 * The Functions / Events / Properties stack. Held so the member quick-filter
	 * can repopulate just this container instead of rebuilding the whole detail
	 * pane — which would otherwise replace (and unfocus) the filter box on every
	 * keystroke. The rest of the detail pane (header, inheritance, filter row)
	 * stays put.
	 */
	TSharedPtr<class SVerticalBox> MembersContainer;

	/** Section widgets captured while building the detail pane, so the Summary chips can scroll to them. */
	TWeakPtr<SWidget> FunctionsAnchor;
	TWeakPtr<SWidget> EventsAnchor;
	TWeakPtr<SWidget> PropertiesAnchor;
	TWeakPtr<SWidget> InheritanceAnchor;
	TWeakPtr<SWidget> ReferencesAnchor;

	/**
	 * Per-(colour, radius) cache of `FSlateBrush`es with `DrawAs = RoundedBox`
	 * so every pill, chip, and badge in the tool renders as a clean filled
	 * rounded rectangle instead of relying on the engine's named
	 * "RoundedFilledBorder" brush — which is missing on some UE versions and
	 * falls back to the missing-brush checker pattern. Mutable because the
	 * `const` widget builders populate it lazily on first use.
	 */
	mutable TMap<uint64, TSharedPtr<FSlateBrush>> PillBrushCache;

	// === Build helpers ======================================================
	void RebuildModel();
	void RebuildTree();
	void DiscoverArchDocs();
	bool ClassMatchesFilters(const FNexusDocClass& Entry) const;

	// === Tree callbacks =====================================================
	TSharedRef<ITableRow> OnGenerateTreeRow(FNodePtr Node, const TSharedRef<STableViewBase>& Owner);
	void OnGetChildren(FNodePtr Node, TArray<FNodePtr>& OutChildren);
	void OnSelectionChanged(FNodePtr Node, ESelectInfo::Type SelectInfo);
	void ExpandAll(const TArray<FNodePtr>& Nodes);
	void CollapseAll(const TArray<FNodePtr>& Nodes);

	// === Search / refresh / toggle ==========================================
	void OnSearchTextChanged(const FText& NewText);
	/** Debounce: rebuild the tree ~200ms after the last keystroke, not on every character. */
	EActiveTimerReturnType TickSearchDebounce(double InCurrentTime, float InDeltaTime);
	double LastSearchKeystrokeTime = 0.0;
	bool bSearchTimerActive = false;
	/** One-shot: put keyboard focus in the search box once the widget is laid out. */
	EActiveTimerReturnType FocusSearchBox(double InCurrentTime, float InDeltaTime);
	FReply OnRefreshClicked();
	FReply OnExpandAllClicked();
	FReply OnCollapseAllClicked();
	FReply OnClearFiltersClicked();
	void OnInternalToggleChanged(ECheckBoxState NewState);
	ECheckBoxState GetInternalToggleState() const;

	// === Navigation =========================================================
	/** Programmatic selection — used by all "click to navigate" affordances. */
	void NavigateToType(const FString& TypeName);
	void PushHistory(const FString& TypeName);
	FReply OnBackClicked();
	FReply OnForwardClicked();
	bool CanGoBack() const;
	bool CanGoForward() const;
	void SelectAndExpandForClass(const TSharedPtr<FNexusDocClass>& Entry);

	// === Type filter pills ==================================================
	bool IsKindFilterActive(uint8 Kind) const;
	void SetKindFilter(uint8 Kind);
	TSharedRef<SWidget> BuildKindFilterRow();
	TSharedRef<SWidget> BuildKindFilterPill(const FText& Label, uint8 Kind, const FText& Tooltip);

	// === Bookmarks ==========================================================
	bool IsPinned(const FString& TypeName) const;
	FReply OnTogglePinned(FString TypeName);

	// === Member filter / sort ===============================================
	void OnMemberFilterChanged(const FText& NewText);
	bool MemberMatchesFilter(const FString& Name, const FString& Tooltip, const FString& Category) const;

	// === Right pane =========================================================
	void RefreshDetailPane();
	/** Rebuild only the Functions/Events/Properties stack — keeps the member-filter box alive and focused. */
	void RefreshMemberSections();
	/** Populate the member-section stack for one class into the given container (filtered + sorted). */
	void PopulateMemberSections(const TSharedRef<class SVerticalBox>& Into, const FNexusDocClass& Entry);
	/** Scroll the detail pane so one of the captured section anchors sits at the top. */
	void ScrollToAnchor(TWeakPtr<SWidget> Anchor);
	TSharedRef<SWidget> BuildEmptyState();
	TSharedRef<SWidget> BuildClassDetail(const FNexusDocClass& Entry);
	TSharedRef<SWidget> BuildClassHeader(const FNexusDocClass& Entry);
	TSharedRef<SWidget> BuildJumpRow(const FNexusDocClass& Entry);
	TSharedRef<SWidget> BuildInheritanceSection(const FNexusDocClass& Entry);
	TSharedRef<SWidget> BuildReferencesSection(const FNexusDocClass& Entry);
	TSharedRef<SWidget> BuildMemberFilterRow();
	TSharedRef<SWidget> BuildFunctionCard(const FNexusDocFunction& Func);
	TSharedRef<SWidget> BuildPropertyCard(const FNexusDocProperty& Prop, bool bIsEvent);
	TSharedRef<SWidget> BuildBadgeRow(const TArray<TPair<FString, FLinearColor>>& Badges) const;
	TSharedRef<SWidget> BuildBadge(const FString& Label, const FLinearColor& Color) const;
	TSharedRef<SWidget> BuildTypeChip(ENexusDocKind Kind, bool bSmall = false) const;
	TSharedRef<SWidget> BuildTypeLink(const FString& TypeName);
	TSharedRef<SWidget> BuildArchDocsRow();
	TSharedRef<SWidget> BuildReadingGuide();
	TSharedRef<SWidget> BuildCopyButton(const FString& ToolTipText, FString TextToCopy);

	// === Markdown viewer ====================================================
	/** Open a popup window that renders one of the discovered architecture docs inline. */
	void OpenArchDocViewer(const FString& AbsolutePath, const FString& DisplayName);

	// === Export =============================================================
	/** Write the whole reference to a Markdown file under Saved/NexusDocs and reveal it. */
	FReply OnExportMarkdownClicked();

	// === Helpers ============================================================
	/** Pretty stats line for the header band. */
	FText GetStatsText() const;
	/** Colour for the type chip / pill background. */
	static FLinearColor ColorForKind(ENexusDocKind Kind);
	/**
	 * Return a cached `FSlateBrush*` with `DrawAs = RoundedBox`, tinted with
	 * `Color` and rounded to `Radius`. Lifetime is the widget's; the brush
	 * survives until the docs browser is destroyed. Used by every pill/chip/
	 * badge in the tool.
	 */
	const FSlateBrush* GetPillBrush(const FLinearColor& Color, float Radius = 6.0f) const;
};
