#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"

#include "Docs/NexusDocsModel.h"

class SEditableTextBox;
class SScrollBox;
class SSearchBox;
template <typename ItemType> class SListView;

/**
 * Three-pane API reference browser. Designed for the designer audience:
 *  - Left pane: search box + collapsible tree grouped by folder (Combat,
 *    Inventory, Weapon, ...). Each leaf is one C++ type.
 *  - Right pane: class header (display name, parent, source file, tooltip)
 *    followed by Functions / Events / Properties sections. Function rows show
 *    a Blueprint-style signature, badges (Pure / Callable / Event / Server /
 *    Latent / Static), description, parameters with descriptions, and the
 *    return value.
 *
 * The model is rebuilt on construction and on "Refresh"; both walks are O(every
 * UCLASS) but cheap (sub-100ms in a project this size). A "Show internal API"
 * toggle includes classes whose public surface area has no BlueprintCallable /
 * BlueprintPure members, so engineers can still browse the full module.
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

	// === Data ===============================================================
	FNexusDocCollection Collection;
	TArray<FNodePtr> RootNodes;
	TSharedPtr<FNexusDocClass> SelectedClass;
	FString CurrentSearch;
	bool bShowInternalApi = false;

	// === Widgets ============================================================
	TSharedPtr<STreeView<FNodePtr>> TreeView;
	TSharedPtr<SScrollBox> DetailScroll;
	TSharedPtr<SSearchBox> SearchBox;

	// === Build helpers ======================================================
	void RebuildModel();
	void RebuildTree();
	bool ClassMatchesFilters(const FNexusDocClass& Entry) const;

	// === Tree callbacks =====================================================
	TSharedRef<ITableRow> OnGenerateTreeRow(FNodePtr Node, const TSharedRef<STableViewBase>& Owner);
	void OnGetChildren(FNodePtr Node, TArray<FNodePtr>& OutChildren);
	void OnSelectionChanged(FNodePtr Node, ESelectInfo::Type SelectInfo);
	void ExpandAll(const TArray<FNodePtr>& Nodes);

	// === Search / refresh / toggle ==========================================
	void OnSearchTextChanged(const FText& NewText);
	FReply OnRefreshClicked();
	void OnInternalToggleChanged(ECheckBoxState NewState);
	ECheckBoxState GetInternalToggleState() const;

	// === Right pane =========================================================
	void RefreshDetailPane();
	TSharedRef<SWidget> BuildEmptyState() const;
	TSharedRef<SWidget> BuildClassDetail(const FNexusDocClass& Entry);
	TSharedRef<SWidget> BuildFunctionCard(const FNexusDocFunction& Func);
	TSharedRef<SWidget> BuildPropertyCard(const FNexusDocProperty& Prop, bool bIsEvent);
	TSharedRef<SWidget> BuildBadgeRow(const TArray<TPair<FString, FLinearColor>>& Badges) const;
	TSharedRef<SWidget> BuildBadge(const FString& Label, const FLinearColor& Color) const;
};
