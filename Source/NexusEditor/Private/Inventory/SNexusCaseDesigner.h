#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class STableViewBase;
class SBox;
class UNexusItemDefinition;
class FNexusAssetWatcher;

/**
 * The Case Designer: lists every attaché *case* item (anything with a Case fragment) with
 * the grid it provides and the charm slots it exposes, and previews the selected case's
 * footprint and slots — so "what does upgrading the case actually buy you" is legible.
 * Selecting a case also drops it in the Inspector for editing. Live-refreshes.
 */
class SNexusCaseDesigner : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusCaseDesigner) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	struct FCaseRow
	{
		TWeakObjectPtr<UNexusItemDefinition> Item;
		FString Name;
		FIntPoint Grid = FIntPoint(8, 6);
		int32 CharmSlots = 0;
		bool bDefault = false;
	};

	void Rebuild();
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FCaseRow> Row, const TSharedRef<STableViewBase>& Owner);
	void OnSelectionChanged(TSharedPtr<FCaseRow> Row, ESelectInfo::Type SelectInfo);
	void ShowDetail(const TSharedPtr<FCaseRow>& Row);
	FText GetSummaryText() const;

	TArray<TSharedPtr<FCaseRow>> Rows;
	TSharedPtr<SListView<TSharedPtr<FCaseRow>>> ListView;
	TSharedPtr<SBox> DetailBox;
	FText SummaryText;
	TSharedPtr<FNexusAssetWatcher> Watcher;
};
