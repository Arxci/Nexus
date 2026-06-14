#include "Inventory/SNexusCaseDesigner.h"

#include "NexusEditorModule.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorStyle.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/Fragments/Case/NexusFragment_Case.h"

#define LOCTEXT_NAMESPACE "NexusCaseDesigner"

namespace NexusCaseUI
{
	constexpr float CellSize = 22.0f;
	constexpr int32 MaxDrawn = 24;
}

void SNexusCaseDesigner::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		[
			NexusEditorWidgets::Toolbar(
				SNew(STextBlock).Text(this, &SNexusCaseDesigner::GetSummaryText))
		]
		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f)
		[
			SNew(SSplitter)
			+ SSplitter::Slot().Value(0.4f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(4.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
					[ NexusEditorWidgets::SectionLabel(LOCTEXT("CasesHeader", "CASES")) ]
					+ SVerticalBox::Slot().FillHeight(1.0f)
					[
						SAssignNew(ListView, SListView<TSharedPtr<FCaseRow>>)
						.ListItemsSource(&Rows)
						.OnGenerateRow(this, &SNexusCaseDesigner::OnGenerateRow)
						.OnSelectionChanged(this, &SNexusCaseDesigner::OnSelectionChanged)
						.SelectionMode(ESelectionMode::Single)
					]
				]
			]
			+ SSplitter::Slot().Value(0.6f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(8.0f)
				[ SAssignNew(DetailBox, SBox) ]
			]
		]
	];

	Rebuild();
	if (Rows.Num() > 0 && ListView.IsValid())
	{
		ListView->SetSelection(Rows[0]);
	}

	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start({ UNexusItemDefinition::StaticClass() }, [this]()
	{
		Rebuild();
		if (Rows.Num() > 0 && ListView.IsValid()) { ListView->SetSelection(Rows[0]); }
	});
}

void SNexusCaseDesigner::Rebuild()
{
	Rows.Reset();

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	for (UNexusItemDefinition* Item : Items)
	{
		const FNexusFragment_Case* Case = NexusEditorUtil::FindCaseFragment(Item);
		if (!Case)
		{
			continue;
		}
		TSharedPtr<FCaseRow> Row = MakeShared<FCaseRow>();
		Row->Item = Item;
		Row->Name = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);
		Row->Grid = FIntPoint(FMath::Max(1, Case->GridSize.X), FMath::Max(1, Case->GridSize.Y));
		Row->CharmSlots = Case->CharmSlots.Num();
		Row->bDefault = Case->bDefaultCase;
		Rows.Add(Row);
	}

	Rows.Sort([](const TSharedPtr<FCaseRow>& A, const TSharedPtr<FCaseRow>& B)
	{
		const int32 AreaA = A.IsValid() ? A->Grid.X * A->Grid.Y : 0;
		const int32 AreaB = B.IsValid() ? B->Grid.X * B->Grid.Y : 0;
		return AreaA > AreaB;
	});

	SummaryText = FText::Format(LOCTEXT("Summary", "{0} case(s)."), FText::AsNumber(Rows.Num()));
	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SNexusCaseDesigner::OnGenerateRow(
	TSharedPtr<FCaseRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	const FString Label = Row.IsValid()
		? FString::Printf(TEXT("%s%s   %dx%d   ·   %d charm slot(s)"),
			Row->bDefault ? TEXT("★ ") : TEXT(""), *Row->Name, Row->Grid.X, Row->Grid.Y, Row->CharmSlots)
		: FString();
	return SNew(STableRow<TSharedPtr<FCaseRow>>, Owner)
	[
		SNew(SBox).Padding(FMargin(6.0f, 3.0f))
		[ SNew(STextBlock).Text(FText::FromString(Label)).OverflowPolicy(ETextOverflowPolicy::Ellipsis) ]
	];
}

void SNexusCaseDesigner::OnSelectionChanged(TSharedPtr<FCaseRow> Row, ESelectInfo::Type SelectInfo)
{
	ShowDetail(Row);
	if (Row.IsValid() && Row->Item.IsValid())
	{
		FNexusEditorModule::SetSelection(Row->Item.Get(), FName(TEXT("NexusCaseDesigner")));
	}
}

void SNexusCaseDesigner::ShowDetail(const TSharedPtr<FCaseRow>& Row)
{
	if (!DetailBox.IsValid())
	{
		return;
	}
	if (!Row.IsValid())
	{
		DetailBox->SetContent(NexusEditorWidgets::EmptyState(LOCTEXT("PickCase", "Select a case to preview its grid and charm slots.")));
		return;
	}

	const int32 W = Row->Grid.X;
	const int32 H = Row->Grid.Y;

	TSharedRef<SVerticalBox> Panel = SNew(SVerticalBox);
	Panel->AddSlot().AutoHeight().Padding(0.0f, 0.0f, 0.0f, 8.0f)
	[
		SNew(STextBlock)
		.Text(FText::FromString(FString::Printf(TEXT("%s  —  %d x %d grid  (%d cells)  ·  %d charm slot(s)"),
			*Row->Name, W, H, W * H, Row->CharmSlots)))
		.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
	];

	// Grid footprint visual (capped so a pathological size can't blow up the panel).
	if (W <= NexusCaseUI::MaxDrawn && H <= NexusCaseUI::MaxDrawn)
	{
		const FSlateBrush* Outline = FAppStyle::Get().GetBrush("Border");
		TSharedRef<SVerticalBox> Grid = SNew(SVerticalBox);
		for (int32 Y = 0; Y < H; ++Y)
		{
			TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);
			for (int32 X = 0; X < W; ++X)
			{
				RowBox->AddSlot().AutoWidth()
				[
					SNew(SBox).WidthOverride(NexusCaseUI::CellSize).HeightOverride(NexusCaseUI::CellSize)
					[
						SNew(SBorder).BorderImage(Outline).BorderBackgroundColor(FLinearColor(0.4f, 0.55f, 0.85f, 0.5f))
					]
				];
			}
			Grid->AddSlot().AutoHeight()[ RowBox ];
		}
		Panel->AddSlot().AutoHeight()[ Grid ];
	}
	else
	{
		Panel->AddSlot().AutoHeight()
		[
			SNew(STextBlock).Text(LOCTEXT("CaseTooBig", "Grid too large to draw — check the dimensions."))
			.ColorAndOpacity(NexusEditorStyle::Warning()).AutoWrapText(true)
		];
	}

	DetailBox->SetContent(
		SNew(SScrollBox) + SScrollBox::Slot()[ Panel ]);
}

FText SNexusCaseDesigner::GetSummaryText() const
{
	return SummaryText;
}

#undef LOCTEXT_NAMESPACE
