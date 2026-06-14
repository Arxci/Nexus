#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class STableViewBase;
class UNexusItemDefinition;
class FNexusAssetWatcher;

/**
 * The Nexus Economy View: the item roster as a balance sheet — base value, grid
 * footprint, value-per-cell, and sell/buy flags — with the outliers called out.
 *
 * In a grid-inventory survival game the real currency is *space*, so value-per-cell
 * is the number that matters; this flags items whose value-per-cell is wildly off
 * the median (a treasure worth nothing per cell, a 1x1 worth a fortune) and catches
 * tradability mistakes (sellable-but-priced-zero, buy-only, sell-only). The outlier
 * sensitivity is a project setting; Value / Sell / Buy are editable in place; a search
 * box and sortable columns make a big roster navigable; and the sheet refreshes live
 * as items change. Pairs with the dashboard's Export CSV for a bulk number-tuning pass.
 */
class SNexusEconomyView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusEconomyView) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** One row of the balance sheet (public so the multi-column row widget can reference it). */
	struct FEconomyRow
	{
		TWeakObjectPtr<UNexusItemDefinition> Item;
		FString Name;
		int32 Value = 0;
		int32 Cells = 1;
		float ValuePerCell = 0.0f;
		bool bSellable = false;
		bool bBuyable = false;
		FString Flags;
		bool bOutlier = false;
	};

	// Inline-edit commits, called by the row widgets. Each writes the asset under a
	// transaction; the live watcher then re-reads the sheet.
	void CommitValue(TSharedPtr<FEconomyRow> Row, int32 NewValue);
	void CommitSellable(TSharedPtr<FEconomyRow> Row, bool bNewSellable);
	void CommitBuyable(TSharedPtr<FEconomyRow> Row, bool bNewBuyable);

private:
	void Rebuild();
	void ApplyView();

	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FEconomyRow> Row, const TSharedRef<STableViewBase>& Owner);
	void OnRowSelectionChanged(TSharedPtr<FEconomyRow> Row, ESelectInfo::Type SelectInfo);
	void OnRowDoubleClicked(TSharedPtr<FEconomyRow> Row);
	FReply OnRefreshClicked();
	void OnSearchChanged(const FText& Text);
	void OnSort(EColumnSortPriority::Type Priority, const FName& Column, EColumnSortMode::Type Mode);
	EColumnSortMode::Type GetSortModeForColumn(FName Column) const;
	FText GetSummaryText() const;

	/** All rows (built once per Rebuild). */
	TArray<TSharedPtr<FEconomyRow>> Rows;
	/** Filtered + sorted view bound to the list. */
	TArray<TSharedPtr<FEconomyRow>> VisibleRows;
	TSharedPtr<SListView<TSharedPtr<FEconomyRow>>> ListView;
	FText SummaryText;

	FString Filter;
	FName SortColumn;
	EColumnSortMode::Type SortMode = EColumnSortMode::None;

	TSharedPtr<FNexusAssetWatcher> Watcher;
};
