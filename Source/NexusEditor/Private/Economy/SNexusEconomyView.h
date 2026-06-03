#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class STableViewBase;
class UNexusItemDefinition;

/**
 * The Nexus Economy View: the item roster as a balance sheet — base value, grid
 * footprint, value-per-cell, and sell/buy flags — with the outliers called out.
 *
 * In a grid-inventory survival game the real currency is *space*, so value-per-cell
 * is the number that matters; this flags items whose value-per-cell is wildly off
 * the median (a treasure worth nothing per cell, a 1x1 worth a fortune) and catches
 * tradability mistakes (sellable-but-priced-zero, buy-only, sell-only). Pairs with
 * the dashboard's Export CSV for the actual number-tuning pass.
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

private:
	void Rebuild();
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FEconomyRow> Row, const TSharedRef<STableViewBase>& Owner);
	void OnRowDoubleClicked(TSharedPtr<FEconomyRow> Row);
	FReply OnRefreshClicked();
	FText GetSummaryText() const;

	TArray<TSharedPtr<FEconomyRow>> Rows;
	TSharedPtr<SListView<TSharedPtr<FEconomyRow>>> ListView;
	FText SummaryText;
};
