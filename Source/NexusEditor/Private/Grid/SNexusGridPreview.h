#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class STableViewBase;
class SBox;
class UNexusItemDefinition;

/**
 * The Nexus Grid Preview: every item listed with its grid footprint, and a live
 * visual of the selected item's WxH cells — the attaché-case model made legible.
 *
 * Designers tune GridSize blind today; this shows the actual shape a pistol (1x2),
 * an herb (1x1), or a rifle (1x3) occupies, so footprint inconsistencies ("why does
 * this SMG eat four cells?") jump out at a glance. Double-click a row to open the item.
 */
class SNexusGridPreview : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusGridPreview) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	struct FGridRow
	{
		TWeakObjectPtr<UNexusItemDefinition> Item;
		FString Name;
		FIntPoint Grid = FIntPoint(1, 1);
		bool bWeapon = false;
	};

	void Rebuild();
	void RebuildGridVisual(const TSharedPtr<FGridRow>& Row);

	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FGridRow> Row, const TSharedRef<STableViewBase>& Owner);
	void OnSelectionChanged(TSharedPtr<FGridRow> Row, ESelectInfo::Type SelectInfo);
	void OnRowDoubleClicked(TSharedPtr<FGridRow> Row);
	FReply OnRefreshClicked();
	FText GetSummaryText() const;
	FText GetFootprintText() const;

	TArray<TSharedPtr<FGridRow>> Rows;
	TSharedPtr<SListView<TSharedPtr<FGridRow>>> ListView;
	TSharedPtr<SBox> GridContainer;
	FText SummaryText;
	FText FootprintText;
};
