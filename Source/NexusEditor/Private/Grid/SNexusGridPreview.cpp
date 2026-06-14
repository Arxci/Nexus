#include "Grid/SNexusGridPreview.h"

#include "NexusEditorModule.h"

#include "Editor.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"

#include "Engine/Texture2D.h"
#include "Styling/SlateBrush.h"

#include "Nexus/Inventory/NexusItemDefinition.h"

#include "Audit/NexusContentAudit.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#define LOCTEXT_NAMESPACE "NexusGridPreview"

namespace NexusGrid
{
	// One cell of the footprint; capped so a pathological 50x50 can't blow up the panel.
	constexpr float CellSize = 40.0f;
	constexpr int32 MaxDrawn = 16;
}

TSharedPtr<FSlateBrush> SNexusGridPreview::MakeIconBrush(const UNexusItemDefinition* Item)
{
	if (!Item)
	{
		return nullptr;
	}
	// Sync-load the soft icon — fine in an editor tool, mirrors the other previews.
	return NexusEditorWidgets::IconBrush(Item->Icon.LoadSynchronous());
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

	// Live: rebuild the roster when items are added/removed/edited.
	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start({ UNexusItemDefinition::StaticClass() }, [this]()
	{
		Rebuild();
		if (Rows.Num() > 0 && ListView.IsValid())
		{
			ListView->SetSelection(Rows[0]);
		}
	});
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
		Row->IconBrush = MakeIconBrush(Item);
		Rows.Add(Row);
	}

	// Mis-size flagging (degenerate dimension + footprint-area outliers) runs through the
	// shared audit classifier, so the live roster, the dashboard, and CI agree on what's odd.
	FlagAreaOutliers();

	// Largest footprints first — the items most likely to be mis-sized.
	Rows.Sort([](const TSharedPtr<FGridRow>& A, const TSharedPtr<FGridRow>& B)
	{
		const int32 AreaA = A.IsValid() ? A->Grid.X * A->Grid.Y : 0;
		const int32 AreaB = B.IsValid() ? B->Grid.X * B->Grid.Y : 0;
		if (AreaA != AreaB) { return AreaA > AreaB; }
		return (A.IsValid() ? A->Name : FString()) < (B.IsValid() ? B->Name : FString());
	});

	int32 Flagged = 0;
	for (const TSharedPtr<FGridRow>& Row : Rows)
	{
		if (Row.IsValid() && Row->bFlagged) { ++Flagged; }
	}
	SummaryText = (Flagged > 0)
		? FText::Format(LOCTEXT("SummaryFlagged", "{0} item(s)  ·  {1} flagged as mis-sized."),
			FText::AsNumber(Rows.Num()), FText::AsNumber(Flagged))
		: FText::Format(LOCTEXT("Summary", "{0} item(s)  ·  none flagged."), FText::AsNumber(Rows.Num()));

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

void SNexusGridPreview::FlagAreaOutliers()
{
	// Roster median: the baseline the shared outlier rule compares against. Needs a few items
	// before it means anything (0 = don't judge outliers; degenerate dims are still flagged).
	int32 Median = 0;
	if (Rows.Num() >= 4)
	{
		TArray<int32> Areas;
		Areas.Reserve(Rows.Num());
		for (const TSharedPtr<FGridRow>& Row : Rows)
		{
			if (Row.IsValid())
			{
				Areas.Add(FMath::Max(1, Row->Grid.X * Row->Grid.Y));
			}
		}
		Areas.Sort();
		Median = Areas[Areas.Num() / 2];
	}

	for (const TSharedPtr<FGridRow>& Row : Rows)
	{
		if (!Row.IsValid() || !Row->Item.IsValid())
		{
			continue;
		}
		FString Reason;
		// Classify the *authored* GridSize (Row->Grid is clamped) so a degenerate dimension reads.
		if (FNexusContentAudit::ClassifyFootprint(Row->Item->GridSize, Median, Reason) != ENexusFootprintFlag::Ok)
		{
			Row->bFlagged = true;
			Row->FlagReason = Reason;
		}
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
	FootprintText = Row->bFlagged
		? FText::Format(
			LOCTEXT("FootprintFlagged", "⚠ {0}  —  {1} x {2}  ({3} cells)   ·   {4}"),
			FText::FromString(Row->Name), FText::AsNumber(W), FText::AsNumber(H), FText::AsNumber(W * H),
			FText::FromString(Row->FlagReason))
		: FText::Format(
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

	// Hairline cell-division grid laid over the art so the footprint stays countable.
	// "Border" draws box edges only (transparent centre), unlike a filled WhiteBrush.
	const FSlateBrush* CellOutline = FAppStyle::Get().GetBrush("Border");
	TSharedRef<SVerticalBox> CellGrid = SNew(SVerticalBox);
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
				[
					SNew(SBorder)
					.BorderImage(CellOutline)
					.BorderBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.25f))
				]
			];
		}
		CellGrid->AddSlot().AutoHeight()[ RowBox ];
	}

	// Keep the brush alive for as long as the SImage below references it.
	SelectedIconBrush = Row->IconBrush;

	// Base layer: the item's real icon stretched across the whole footprint when it has
	// one; otherwise the original type-coloured block so footprint-only items still read.
	TSharedRef<SWidget> BaseLayer = SelectedIconBrush.IsValid()
		? StaticCastSharedRef<SWidget>(
			SNew(SImage)
			.Image(SelectedIconBrush.Get())
			.ToolTipText(LOCTEXT("IconTip", "The item's authored Icon, drawn at its real grid footprint.")))
		: StaticCastSharedRef<SWidget>(
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("WhiteBrush"))
			.BorderBackgroundColor(CellColor));

	GridContainer->SetContent(
		SNew(SBox)
		.WidthOverride(W * NexusGrid::CellSize)
		.HeightOverride(H * NexusGrid::CellSize)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()[ BaseLayer ]
			+ SOverlay::Slot()[ CellGrid ]
		]);
}

TSharedRef<ITableRow> SNexusGridPreview::OnGenerateRow(
	TSharedPtr<FGridRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	const bool bFlagged = Row.IsValid() && Row->bFlagged;
	const FString Label = Row.IsValid()
		? FString::Printf(TEXT("%s%dx%d   %s"), bFlagged ? TEXT("⚠ ") : TEXT(""), Row->Grid.X, Row->Grid.Y, *Row->Name)
		: FString();

	// Thumbnail (when the item has an icon) sits left of the label so the roster reads
	// like an inventory, not just a list of dimensions. The brush lives on the row, which
	// outlives the widget (Rows owns it), so the raw pointer stays valid.
	const bool bHasIcon = Row.IsValid() && Row->IconBrush.IsValid();

	const FSlateColor LabelColor = bFlagged
		? FSlateColor(FStyleColors::Warning)
		: ((Row.IsValid() && Row->bWeapon) ? FSlateColor(FStyleColors::AccentBlue) : FSlateColor::UseForeground());
	const FText RowTip = bFlagged ? FText::FromString(Row->FlagReason) : FText::GetEmpty();

	return SNew(STableRow<TSharedPtr<FGridRow>>, Owner)
	.ToolTipText(RowTip)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(FMargin(4.0f, 2.0f, 6.0f, 2.0f))
		[
			SNew(SBox).WidthOverride(24.0f).HeightOverride(24.0f)
			[
				bHasIcon
					? StaticCastSharedRef<SWidget>(SNew(SImage).Image(Row->IconBrush.Get()))
					: SNullWidget::NullWidget
			]
		]
		+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(FMargin(0.0f, 3.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromString(Label))
			.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
			.ColorAndOpacity(LabelColor)
		]
	];
}

void SNexusGridPreview::OnSelectionChanged(TSharedPtr<FGridRow> Row, ESelectInfo::Type SelectInfo)
{
	RebuildGridVisual(Row);

	// Surface the picked item in the Workbench Inspector.
	if (Row.IsValid() && Row->Item.IsValid())
	{
		FNexusEditorModule::SetSelection(Row->Item.Get(), FNexusEditorModule::GridTabName);
	}
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
