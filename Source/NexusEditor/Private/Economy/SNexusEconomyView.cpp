#include "Economy/SNexusEconomyView.h"

#include "NexusEditorModule.h"

#include "Editor.h"
#include "ScopedTransaction.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"

#include "Settings/NexusEditorSettings.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorPersistence.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#define LOCTEXT_NAMESPACE "NexusEconomyView"

namespace NexusEconomy
{
	const FName ColName("Name");
	const FName ColValue("Value");
	const FName ColCells("Cells");
	const FName ColPerCell("PerCell");
	const FName ColSell("Sell");
	const FName ColBuy("Buy");
	const FName ColFlags("Flags");
}

/** Multi-column balance-sheet row; outliers/mistakes show in colour, key fields edit inline. */
class SNexusEconomyRow : public SMultiColumnTableRow<TSharedPtr<SNexusEconomyView::FEconomyRow>>
{
public:
	SLATE_BEGIN_ARGS(SNexusEconomyRow) {}
		SLATE_ARGUMENT(TSharedPtr<SNexusEconomyView::FEconomyRow>, Row)
		SLATE_ARGUMENT(SNexusEconomyView*, View)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
	{
		Row = InArgs._Row;
		View = InArgs._View;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), Owner);
	}

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override
	{
		using namespace NexusEconomy;
		using namespace NexusEditorWidgets;
		if (!Row.IsValid()) { return SNullWidget::NullWidget; }

		if (Column == ColName)  { return Cell(Row->Name); }
		if (Column == ColValue)
		{
			// Editable: tune base value without leaving the sheet.
			return SNew(SBox).Padding(FMargin(4.0f, 1.0f)).VAlign(VAlign_Center)
			[
				SNew(SSpinBox<int32>)
				.MinValue(0)
				.MinDesiredWidth(48.0f)
				.Value(Row->Value)
				.OnValueCommitted_Lambda([this](int32 NewValue, ETextCommit::Type)
				{
					if (View) { View->CommitValue(Row, NewValue); }
				})
			];
		}
		if (Column == ColCells) { return Cell(FString::FromInt(Row->Cells)); }
		if (Column == ColPerCell)
		{
			return Cell(FString::Printf(TEXT("%.1f"), Row->ValuePerCell),
				Row->bOutlier ? FSlateColor(FStyleColors::Warning) : FSlateColor::UseForeground());
		}
		if (Column == ColSell)
		{
			return SNew(SBox).Padding(FMargin(6.0f, 1.0f)).HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(SCheckBox)
				.IsChecked(Row->bSellable ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
				.OnCheckStateChanged_Lambda([this](ECheckBoxState State)
				{
					if (View) { View->CommitSellable(Row, State == ECheckBoxState::Checked); }
				})
			];
		}
		if (Column == ColBuy)
		{
			return SNew(SBox).Padding(FMargin(6.0f, 1.0f)).HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(SCheckBox)
				.IsChecked(Row->bBuyable ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
				.OnCheckStateChanged_Lambda([this](ECheckBoxState State)
				{
					if (View) { View->CommitBuyable(Row, State == ECheckBoxState::Checked); }
				})
			];
		}
		if (Column == ColFlags)
		{
			return Cell(Row->Flags,
				Row->Flags.IsEmpty() ? FSlateColor::UseForeground() : FSlateColor(FStyleColors::Error));
		}
		return SNullWidget::NullWidget;
	}

private:
	TSharedPtr<SNexusEconomyView::FEconomyRow> Row;
	SNexusEconomyView* View = nullptr;
};

void SNexusEconomyView::Construct(const FArguments& InArgs)
{
	using namespace NexusEconomy;

	// Restore the last sort (per-user) so the sheet opens the way you left it.
	SortColumn = FName(*NexusEditorPersistence::GetString(TEXT("EconomySortColumn")));
	SortMode = static_cast<EColumnSortMode::Type>(
		NexusEditorPersistence::GetInt(TEXT("EconomySortMode"), static_cast<int32>(EColumnSortMode::None)));

	Rebuild();

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot().AutoHeight().Padding(8.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(LOCTEXT("Refresh", "Refresh"))
				.OnClicked(this, &SNexusEconomyView::OnRefreshClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SBox).WidthOverride(220.0f)
				[
					SNew(SSearchBox)
					.HintText(LOCTEXT("SearchHint", "Filter by name..."))
					.OnTextChanged(this, &SNexusEconomyView::OnSearchChanged)
				]
			]
			+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[ SNew(STextBlock).Text(this, &SNexusEconomyView::GetSummaryText) ]
		]

		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f, 0.0f, 8.0f, 8.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(4.0f)
			[
				SAssignNew(ListView, SListView<TSharedPtr<FEconomyRow>>)
				.ListItemsSource(&VisibleRows)
				.OnGenerateRow(this, &SNexusEconomyView::OnGenerateRow)
				.OnSelectionChanged(this, &SNexusEconomyView::OnRowSelectionChanged)
				.OnMouseButtonDoubleClick(this, &SNexusEconomyView::OnRowDoubleClicked)
				.SelectionMode(ESelectionMode::Multi)
				.HeaderRow(
					SNew(SHeaderRow)
					+ SHeaderRow::Column(ColName).DefaultLabel(LOCTEXT("CName", "Name")).FillWidth(0.30f)
						.SortMode_Lambda([this]() { return GetSortModeForColumn(ColName); })
						.OnSort(this, &SNexusEconomyView::OnSort)
					+ SHeaderRow::Column(ColValue).DefaultLabel(LOCTEXT("CValue", "Value")).FillWidth(0.10f)
						.SortMode_Lambda([this]() { return GetSortModeForColumn(ColValue); })
						.OnSort(this, &SNexusEconomyView::OnSort)
					+ SHeaderRow::Column(ColCells).DefaultLabel(LOCTEXT("CCells", "Cells")).FillWidth(0.08f)
						.SortMode_Lambda([this]() { return GetSortModeForColumn(ColCells); })
						.OnSort(this, &SNexusEconomyView::OnSort)
					+ SHeaderRow::Column(ColPerCell).DefaultLabel(LOCTEXT("CPerCell", "Value/Cell")).FillWidth(0.13f)
						.SortMode_Lambda([this]() { return GetSortModeForColumn(ColPerCell); })
						.OnSort(this, &SNexusEconomyView::OnSort)
					+ SHeaderRow::Column(ColSell).DefaultLabel(LOCTEXT("CSell", "Sell")).FillWidth(0.08f)
					+ SHeaderRow::Column(ColBuy).DefaultLabel(LOCTEXT("CBuy", "Buy")).FillWidth(0.08f)
					+ SHeaderRow::Column(ColFlags).DefaultLabel(LOCTEXT("CFlags", "Flags")).FillWidth(0.23f))
			]
		]
	];

	// Live: re-read the sheet whenever any item changes (inc. our own inline edits).
	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start({ UNexusItemDefinition::StaticClass() }, [this]() { Rebuild(); });
}

void SNexusEconomyView::Rebuild()
{
	using namespace NexusEconomy;

	Rows.Reset();

	// Outlier sensitivity is a project setting now, not a magic constant.
	const float OutlierFactor = FMath::Max(1.5f, UNexusEditorSettings::Get().EconomyOutlierFactor);

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);

	// First pass: build rows and collect value-per-cell of the priced items for a median.
	TArray<float> PricedPerCell;
	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item) { continue; }

		TSharedPtr<FEconomyRow> Row = MakeShared<FEconomyRow>();
		Row->Item = Item;
		Row->Name = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);
		Row->Value = Item->BaseValue;
		Row->Cells = FMath::Max(1, Item->GridSize.X) * FMath::Max(1, Item->GridSize.Y);
		Row->ValuePerCell = static_cast<float>(Row->Value) / static_cast<float>(Row->Cells);
		Row->bSellable = Item->bSellable;
		Row->bBuyable = Item->bBuyable;

		if (Row->Value > 0)
		{
			PricedPerCell.Add(Row->ValuePerCell);
		}
		Rows.Add(Row);
	}

	float Median = 0.0f;
	if (PricedPerCell.Num() > 0)
	{
		PricedPerCell.Sort();
		Median = PricedPerCell[PricedPerCell.Num() / 2];
	}

	// Second pass: flag outliers and tradability mistakes.
	int32 Outliers = 0;
	int32 Mistakes = 0;
	for (const TSharedPtr<FEconomyRow>& Row : Rows)
	{
		if (!Row.IsValid()) { continue; }

		TArray<FString> Flags;

		if ((Row->bSellable || Row->bBuyable) && Row->Value == 0)
		{
			Flags.Add(TEXT("tradable but priced 0"));
		}
		if (Row->bBuyable && !Row->bSellable) { Flags.Add(TEXT("buy-only")); }
		if (Row->bSellable && !Row->bBuyable) { Flags.Add(TEXT("sell-only")); }

		if (Median > 0.0f && Row->Value > 0)
		{
			if (Row->ValuePerCell > Median * OutlierFactor)       { Row->bOutlier = true; Flags.Add(TEXT("high value/cell")); }
			else if (Row->ValuePerCell < Median / OutlierFactor)  { Row->bOutlier = true; Flags.Add(TEXT("low value/cell")); }
		}

		Row->Flags = FString::Join(Flags, TEXT("; "));
		if (Row->bOutlier) { ++Outliers; }
		if (!Row->Flags.IsEmpty() && !Row->bOutlier) { ++Mistakes; }
		else if (Row->bOutlier && Flags.Num() > 1) { ++Mistakes; }
	}

	SummaryText = FText::Format(
		LOCTEXT("Summary", "{0} item(s)   median {1}/cell   {2} value/cell outlier(s)"),
		FText::AsNumber(Rows.Num()), FText::AsNumber(FMath::RoundToInt(Median)), FText::AsNumber(Outliers));

	ApplyView();
}

void SNexusEconomyView::ApplyView()
{
	using namespace NexusEconomy;

	VisibleRows.Reset();
	for (const TSharedPtr<FEconomyRow>& Row : Rows)
	{
		if (Row.IsValid() && (Filter.IsEmpty() || Row->Name.Contains(Filter)))
		{
			VisibleRows.Add(Row);
		}
	}

	if (SortMode == EColumnSortMode::None)
	{
		// Default: worst offenders (anything flagged) on top, then by value/cell.
		VisibleRows.Sort([](const TSharedPtr<FEconomyRow>& A, const TSharedPtr<FEconomyRow>& B)
		{
			const bool FlagA = A.IsValid() && !A->Flags.IsEmpty();
			const bool FlagB = B.IsValid() && !B->Flags.IsEmpty();
			if (FlagA != FlagB) { return FlagA; }
			return (A.IsValid() ? A->ValuePerCell : 0.0f) > (B.IsValid() ? B->ValuePerCell : 0.0f);
		});
	}
	else
	{
		const bool bAsc = (SortMode == EColumnSortMode::Ascending);
		const FName Col = SortColumn;
		VisibleRows.Sort([bAsc, Col](const TSharedPtr<FEconomyRow>& A, const TSharedPtr<FEconomyRow>& B)
		{
			if (!A.IsValid() || !B.IsValid()) { return false; }
			bool bLess;
			if (Col == ColValue)        { bLess = A->Value < B->Value; }
			else if (Col == ColCells)   { bLess = A->Cells < B->Cells; }
			else if (Col == ColPerCell) { bLess = A->ValuePerCell < B->ValuePerCell; }
			else                        { bLess = A->Name < B->Name; } // ColName / fallback
			return bAsc ? bLess : !bLess;
		});
	}

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SNexusEconomyView::OnGenerateRow(
	TSharedPtr<FEconomyRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(SNexusEconomyRow, Owner).Row(Row).View(this);
}

void SNexusEconomyView::OnSearchChanged(const FText& Text)
{
	Filter = Text.ToString();
	ApplyView();
}

void SNexusEconomyView::OnSort(EColumnSortPriority::Type /*Priority*/, const FName& Column, EColumnSortMode::Type Mode)
{
	SortColumn = Column;
	SortMode = Mode;
	NexusEditorPersistence::SetString(TEXT("EconomySortColumn"), SortColumn.ToString());
	NexusEditorPersistence::SetInt(TEXT("EconomySortMode"), static_cast<int32>(SortMode));
	ApplyView();
}

EColumnSortMode::Type SNexusEconomyView::GetSortModeForColumn(FName Column) const
{
	return (Column == SortColumn) ? SortMode : EColumnSortMode::None;
}

void SNexusEconomyView::CommitValue(TSharedPtr<FEconomyRow> Row, int32 NewValue)
{
	UNexusItemDefinition* Item = Row.IsValid() ? Row->Item.Get() : nullptr;
	if (!Item || Item->BaseValue == NewValue)
	{
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("EditValue", "Edit Item Value"));
	Item->Modify();
	Item->BaseValue = FMath::Max(0, NewValue);
	Item->MarkPackageDirty();
	Rebuild(); // the watcher also fires; Rebuild is idempotent and never mutates assets
}

void SNexusEconomyView::CommitSellable(TSharedPtr<FEconomyRow> Row, bool bNewSellable)
{
	UNexusItemDefinition* Item = Row.IsValid() ? Row->Item.Get() : nullptr;
	if (!Item || Item->bSellable == bNewSellable)
	{
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("EditSellable", "Edit Item Sellable"));
	Item->Modify();
	Item->bSellable = bNewSellable;
	Item->MarkPackageDirty();
	Rebuild();
}

void SNexusEconomyView::CommitBuyable(TSharedPtr<FEconomyRow> Row, bool bNewBuyable)
{
	UNexusItemDefinition* Item = Row.IsValid() ? Row->Item.Get() : nullptr;
	if (!Item || Item->bBuyable == bNewBuyable)
	{
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("EditBuyable", "Edit Item Buyable"));
	Item->Modify();
	Item->bBuyable = bNewBuyable;
	Item->MarkPackageDirty();
	Rebuild();
}

void SNexusEconomyView::OnRowSelectionChanged(TSharedPtr<FEconomyRow> Row, ESelectInfo::Type SelectInfo)
{
	if (!ListView.IsValid())
	{
		return;
	}
	// Publish every selected item so the Inspector can bulk-edit shared properties
	// (e.g. set Weight/Value across a whole category at once).
	TArray<UObject*> Selected;
	for (const TSharedPtr<FEconomyRow>& Selected_Row : ListView->GetSelectedItems())
	{
		if (Selected_Row.IsValid() && Selected_Row->Item.IsValid())
		{
			Selected.Add(Selected_Row->Item.Get());
		}
	}
	FNexusEditorModule::SetSelection(Selected, FNexusEditorModule::EconomyTabName);
}

void SNexusEconomyView::OnRowDoubleClicked(TSharedPtr<FEconomyRow> Row)
{
	if (Row.IsValid() && Row->Item.IsValid() && GEditor)
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Row->Item.Get());
	}
}

FReply SNexusEconomyView::OnRefreshClicked()
{
	Rebuild();
	return FReply::Handled();
}

FText SNexusEconomyView::GetSummaryText() const
{
	return SummaryText;
}

#undef LOCTEXT_NAMESPACE
