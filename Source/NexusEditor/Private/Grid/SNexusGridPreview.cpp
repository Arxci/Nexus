#include "Grid/SNexusGridPreview.h"

#include "Editor.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"

#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#define LOCTEXT_NAMESPACE "NexusGridPreview"

namespace NexusGrid
{
	// One cell of the footprint; capped so a pathological 50x50 can't blow up the panel.
	constexpr float CellSize = 26.0f;
	constexpr int32 MaxDrawn = 16;
}

void SNexusGridPreview::Construct(const FArguments& InArgs)
{
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
				.OnClicked(this, &SNexusGridPreview::OnRefreshClicked)
			]
			+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[ SNew(STextBlock).Text(this, &SNexusGridPreview::GetSummaryText) ]
		]

		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f, 0.0f, 8.0f, 8.0f)
		[
			SNew(SSplitter)

			// Roster, sorted by footprint area.
			+ SSplitter::Slot().Value(0.45f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(4.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
					[ NexusEditorWidgets::SectionLabel(LOCTEXT("RosterHeader", "ITEMS — by footprint")) ]
					+ SVerticalBox::Slot().FillHeight(1.0f)
					[
						SAssignNew(ListView, SListView<TSharedPtr<FGridRow>>)
						.ListItemsSource(&Rows)
						.OnGenerateRow(this, &SNexusGridPreview::OnGenerateRow)
						.OnSelectionChanged(this, &SNexusGridPreview::OnSelectionChanged)
						.OnMouseButtonDoubleClick(this, &SNexusGridPreview::OnRowDoubleClicked)
						.SelectionMode(ESelectionMode::Single)
					]
				]
			]

			// Footprint visual for the selected item.
			+ SSplitter::Slot().Value(0.55f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(8.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(2.0f, 2.0f, 2.0f, 8.0f)
					[
						SNew(STextBlock)
						.Text(this, &SNexusGridPreview::GetFootprintText)
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
					]
					+ SVerticalBox::Slot().FillHeight(1.0f)
					[
						SNew(SScrollBox)
						.Orientation(Orient_Vertical)
						+ SScrollBox::Slot()
						[
							SAssignNew(GridContainer, SBox)
							.HAlign(HAlign_Left)
							.VAlign(VAlign_Top)
						]
					]
				]
			]
		]
	];

	if (Rows.Num() > 0 && ListView.IsValid())
	{
		ListView->SetSelection(Rows[0]);
	}
}

void SNexusGridPreview::Rebuild()
{
	Rows.Reset();

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);

	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item)
		{
			continue;
		}
		TSharedPtr<FGridRow> Row = MakeShared<FGridRow>();
		Row->Item = Item;
		Row->Name = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);
		Row->Grid = FIntPoint(FMath::Max(1, Item->GridSize.X), FMath::Max(1, Item->GridSize.Y));
		Row->bWeapon = NexusEditorUtil::HasWeaponFragment(Item);
		Rows.Add(Row);
	}

	// Largest footprints first — the items most likely to be mis-sized.
	Rows.Sort([](const TSharedPtr<FGridRow>& A, const TSharedPtr<FGridRow>& B)
	{
		const int32 AreaA = A.IsValid() ? A->Grid.X * A->Grid.Y : 0;
		const int32 AreaB = B.IsValid() ? B->Grid.X * B->Grid.Y : 0;
		if (AreaA != AreaB) { return AreaA > AreaB; }
		return (A.IsValid() ? A->Name : FString()) < (B.IsValid() ? B->Name : FString());
	});

	SummaryText = FText::Format(LOCTEXT("Summary", "{0} item(s)."), FText::AsNumber(Rows.Num()));

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

void SNexusGridPreview::RebuildGridVisual(const TSharedPtr<FGridRow>& Row)
{
	if (!GridContainer.IsValid())
	{
		return;
	}

	if (!Row.IsValid())
	{
		FootprintText = LOCTEXT("PickItem", "Select an item to preview its grid footprint.");
		GridContainer->SetContent(SNullWidget::NullWidget);
		return;
	}

	const int32 W = Row->Grid.X;
	const int32 H = Row->Grid.Y;
	FootprintText = FText::Format(
		LOCTEXT("Footprint", "{0}  —  {1} x {2}  ({3} cells)"),
		FText::FromString(Row->Name), FText::AsNumber(W), FText::AsNumber(H), FText::AsNumber(W * H));

	if (W > NexusGrid::MaxDrawn || H > NexusGrid::MaxDrawn)
	{
		GridContainer->SetContent(
			SNew(STextBlock)
			.Text(LOCTEXT("TooBig", "Footprint is too large to draw — check the dimensions above; this is almost certainly a typo."))
			.ColorAndOpacity(FSlateColor(FStyleColors::Warning))
			.AutoWrapText(true));
		return;
	}

	const FSlateColor CellColor = Row->bWeapon
		? FSlateColor(FStyleColors::AccentBlue)
		: FSlateColor(FStyleColors::AccentGreen);

	TSharedRef<SVerticalBox> Column = SNew(SVerticalBox);
	for (int32 Y = 0; Y < H; ++Y)
	{
		TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);
		for (int32 X = 0; X < W; ++X)
		{
			RowBox->AddSlot().AutoWidth()
			[
				SNew(SBox)
				.WidthOverride(NexusGrid::CellSize)
				.HeightOverride(NexusGrid::CellSize)
				.Padding(2.0f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("WhiteBrush"))
					.BorderBackgroundColor(CellColor)
				]
			];
		}
		Column->AddSlot().AutoHeight()[ RowBox ];
	}

	GridContainer->SetContent(Column);
}

TSharedRef<ITableRow> SNexusGridPreview::OnGenerateRow(
	TSharedPtr<FGridRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	const FString Label = Row.IsValid()
		? FString::Printf(TEXT("%dx%d   %s"), Row->Grid.X, Row->Grid.Y, *Row->Name)
		: FString();

	return SNew(STableRow<TSharedPtr<FGridRow>>, Owner)
	[
		SNew(SBox).Padding(FMargin(6.0f, 3.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromString(Label))
			.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
			.ColorAndOpacity((Row.IsValid() && Row->bWeapon)
				? FSlateColor(FStyleColors::AccentBlue) : FSlateColor::UseForeground())
		]
	];
}

void SNexusGridPreview::OnSelectionChanged(TSharedPtr<FGridRow> Row, ESelectInfo::Type SelectInfo)
{
	RebuildGridVisual(Row);
}

void SNexusGridPreview::OnRowDoubleClicked(TSharedPtr<FGridRow> Row)
{
	if (Row.IsValid() && Row->Item.IsValid() && GEditor)
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Row->Item.Get());
	}
}

FReply SNexusGridPreview::OnRefreshClicked()
{
	Rebuild();
	if (Rows.Num() > 0 && ListView.IsValid())
	{
		ListView->SetSelection(Rows[0]);
	}
	else
	{
		RebuildGridVisual(nullptr);
	}
	return FReply::Handled();
}

FText SNexusGridPreview::GetSummaryText() const { return SummaryText; }
FText SNexusGridPreview::GetFootprintText() const { return FootprintText; }

#undef LOCTEXT_NAMESPACE
