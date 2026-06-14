#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "Widgets/SCompoundWidget.h"

class ITableRow;
class STableViewBase;
class SEditableTextBox;
class SNexusInventoryCanvas;
class SWidget;
class UNexusItemDefinition;
template <typename ItemType> class SListView;

/**
 * The Nexus Inventory Sandbox: a searchable palette of every item on the left, an
 * interactive attaché grid on the right. Double-click (or "Add") to drop an item in,
 * drag to rearrange, R to rotate, right-click to remove, Auto-arrange to run the
 * runtime repack, and a case-size selector to feel how a bigger/smaller case plays.
 *
 * The grid is backed by the real UNexusItemContainer, so what you see is exactly how
 * the shipped inventory packs — footprint and case-size tuning becomes WYSIWYG instead
 * of guesswork against raw GridSize numbers.
 */
class SNexusInventorySandbox : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusInventorySandbox) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	struct FPaletteEntry
	{
		TWeakObjectPtr<UNexusItemDefinition> Item;
		FString Name;
		FIntPoint Grid = FIntPoint(1, 1);
		TSharedPtr<FSlateBrush> IconBrush;
	};

	void RebuildPalette();
	void ApplyFilter();

	TSharedRef<ITableRow> OnGeneratePaletteRow(TSharedPtr<FPaletteEntry> Entry, const TSharedRef<STableViewBase>& Owner);
	void OnPaletteActivated(TSharedPtr<FPaletteEntry> Entry);
	void OnPaletteSelectionChanged(TSharedPtr<FPaletteEntry> Entry, ESelectInfo::Type SelectInfo);
	void OnSearchChanged(const FText& Text);

	FReply OnAddSelectedClicked();
	FReply OnAutoArrangeClicked();
	FReply OnClearClicked();
	FReply OnRotateClicked();
	FReply OnRefreshClicked();

	TSharedRef<SWidget> MakeCaseSizeMenu();
	/** Menu of authored Case items; choosing one sizes the grid to its GridSize. */
	TSharedRef<SWidget> MakeCaseItemMenu();
	/** Menu of Level Manifests; choosing one fills the grid with that manifest's items. */
	TSharedRef<SWidget> MakeFillMenu();
	/** Save the current packing under the name in the layout box (per-user, named slots). */
	FReply OnSaveLayoutClicked();
	/** Menu of saved layout names; choosing one restores it. */
	TSharedRef<SWidget> MakeLoadLayoutMenu();
	void SetCaseSize(int32 Width, int32 Height);

	void AddEntryToCanvas(const TSharedPtr<FPaletteEntry>& Entry);

	FText GetStatusText() const;
	FText GetCaseSizeText() const;

	TArray<TSharedPtr<FPaletteEntry>> AllPalette;
	TArray<TSharedPtr<FPaletteEntry>> FilteredPalette;
	TSharedPtr<SListView<TSharedPtr<FPaletteEntry>>> PaletteList;
	TSharedPtr<SNexusInventoryCanvas> Canvas;
	TSharedPtr<SEditableTextBox> LayoutNameBox;

	FString Filter;
	int32 CaseWidth = 10;
	int32 CaseHeight = 8;
};
