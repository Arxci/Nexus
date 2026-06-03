#include "Economy/SNexusEconomyView.h"

#include "Editor.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"

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

	// A value-per-cell this many times off the median is worth a designer's eye.
	constexpr float OutlierFactor = 3.0f;
}

/** Multi-column balance-sheet row; outliers and tradability mistakes show in colour. */
class SNexusEconomyRow : public SMultiColumnTableRow<TSharedPtr<SNexusEconomyView::FEconomyRow>>
{
public:
	SLATE_BEGIN_ARGS(SNexusEconomyRow) {}
		SLATE_ARGUMENT(TSharedPtr<SNexusEconomyView::FEconomyRow>, Row)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
	{
		Row = InArgs._Row;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), Owner);
	}

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override
	{
		using namespace NexusEconomy;
		using namespace NexusEditorWidgets;
		if (!Row.IsValid()) { return SNullWidget::NullWidget; }

		if (Column == ColName)  { return Cell(Row->Name); }
		if (Column == ColValue) { return Cell(FString::FromInt(Row->Value)); }
		if (Column == ColCells) { return Cell(FString::FromInt(Row->Cells)); }
		if (Column == ColPerCell)
		{
			return Cell(FString::Printf(TEXT("%.1f"), Row->ValuePerCell),
				Row->bOutlier ? FSlateColor(FStyleColors::Warning) : FSlateColor::UseForeground());
		}
		if (Column == ColSell) { return Cell(Row->bSellable ? TEXT("Yes") : TEXT("-")); }
		if (Column == ColBuy)  { return Cell(Row->bBuyable ? TEXT("Yes") : TEXT("-")); }
		if (Column == ColFlags)
		{
			return Cell(Row->Flags,
				Row->Flags.IsEmpty() ? FSlateColor::UseForeground() : FSlateColor(FStyleColors::Error));
		}
		return SNullWidget::NullWidget;
	}

private:
	TSharedPtr<SNexusEconomyView::FEconomyRow> Row;
};

void SNexusEconomyView::Construct(const FArguments& InArgs)
{
	using namespace NexusEconomy;

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
				.ListItemsSource(&Rows)
				.OnGenerateRow(this, &SNexusEconomyView::OnGenerateRow)
				.OnMouseButtonDoubleClick(this, &SNexusEconomyView::OnRowDoubleClicked)
				.SelectionMode(ESelectionMode::Single)
				.HeaderRow(
					SNew(SHeaderRow)
					+ SHeaderRow::Column(ColName).DefaultLabel(LOCTEXT("CName", "Name")).FillWidth(0.30f)
					+ SHeaderRow::Column(ColValue).DefaultLabel(LOCTEXT("CValue", "Value")).FillWidth(0.10f)
					+ SHeaderRow::Column(ColCells).DefaultLabel(LOCTEXT("CCells", "Cells")).FillWidth(0.08f)
					+ SHeaderRow::Column(ColPerCell).DefaultLabel(LOCTEXT("CPerCell", "Value/Cell")).FillWidth(0.13f)
					+ SHeaderRow::Column(ColSell).DefaultLabel(LOCTEXT("CSell", "Sell")).FillWidth(0.08f)
					+ SHeaderRow::Column(ColBuy).DefaultLabel(LOCTEXT("CBuy", "Buy")).FillWidth(0.08f)
					+ SHeaderRow::Column(ColFlags).DefaultLabel(LOCTEXT("CFlags", "Flags")).FillWidth(0.23f))
			]
		]
	];
}

void SNexusEconomyView::Rebuild()
{
	using namespace NexusEconomy;

	Rows.Reset();

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

	// Worst offenders (anything flagged) float to the top, then by value/cell.
	Rows.Sort([](const TSharedPtr<FEconomyRow>& A, const TSharedPtr<FEconomyRow>& B)
	{
		const bool FlagA = A.IsValid() && !A->Flags.IsEmpty();
		const bool FlagB = B.IsValid() && !B->Flags.IsEmpty();
		if (FlagA != FlagB) { return FlagA; }
		return (A.IsValid() ? A->ValuePerCell : 0.0f) > (B.IsValid() ? B->ValuePerCell : 0.0f);
	});

	SummaryText = FText::Format(
		LOCTEXT("Summary", "{0} item(s)   median {1}/cell   {2} value/cell outlier(s)"),
		FText::AsNumber(Rows.Num()), FText::AsNumber(FMath::RoundToInt(Median)), FText::AsNumber(Outliers));

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SNexusEconomyView::OnGenerateRow(
	TSharedPtr<FEconomyRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(SNexusEconomyRow, Owner).Row(Row);
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
