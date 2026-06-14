#include "Sandbox/SNexusInventorySandbox.h"

#include "Sandbox/SNexusInventoryCanvas.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#include "Framework/Commands/UIAction.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"
#include "Textures/SlateIcon.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"

#define LOCTEXT_NAMESPACE "NexusInventorySandbox"

void SNexusInventorySandbox::Construct(const FArguments& InArgs)
{
	RebuildPalette();

	ChildSlot
	[
		SNew(SVerticalBox)

		// === Toolbar =========================================================
		+ SVerticalBox::Slot().AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
			.Padding(10.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[ NexusEditorWidgets::SectionLabel(LOCTEXT("CaseLabel", "CASE")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
				[
					SNew(SComboButton)
					.OnGetMenuContent(this, &SNexusInventorySandbox::MakeCaseSizeMenu)
					.ToolTipText(LOCTEXT("CaseTip", "Pick a case size; the grid resizes (and clears) to match."))
					.ButtonContent()
					[ SNew(STextBlock).Text(this, &SNexusInventorySandbox::GetCaseSizeText) ]
				]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(SButton)
					.Text(LOCTEXT("AutoArrange", "Auto-arrange"))
					.ToolTipText(LOCTEXT("AutoArrangeTip", "Run the runtime first-fit-decreasing repack (the in-game Optimize)."))
					.OnClicked(this, &SNexusInventorySandbox::OnAutoArrangeClicked)
				]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(SButton)
					.Text(LOCTEXT("Rotate", "Rotate"))
					.ToolTipText(LOCTEXT("RotateTip", "Rotate the item you're currently dragging 90° (or press R)."))
					.OnClicked(this, &SNexusInventorySandbox::OnRotateClicked)
				]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(SButton)
					.Text(LOCTEXT("Clear", "Clear"))
					.ToolTipText(LOCTEXT("ClearTip", "Empty the grid."))
					.OnClicked(this, &SNexusInventorySandbox::OnClearClicked)
				]
				+ SHorizontalBox::Slot().FillWidth(1.0f)[ SNullWidget::NullWidget ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[
					SNew(SButton)
					.Text(LOCTEXT("Refresh", "Refresh"))
					.ToolTipText(LOCTEXT("RefreshTip", "Rescan the project for items (after creating new ones)."))
					.OnClicked(this, &SNexusInventorySandbox::OnRefreshClicked)
				]
			]
		]

		// Status line.
		+ SVerticalBox::Slot().AutoHeight().Padding(10.0f, 6.0f)
		[ SNew(STextBlock).Text(this, &SNexusInventorySandbox::GetStatusText).AutoWrapText(true) ]

		// === Body: palette | grid ===========================================
		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f, 0.0f, 8.0f, 8.0f)
		[
			SNew(SSplitter)

			+ SSplitter::Slot().Value(0.32f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(4.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
					[ NexusEditorWidgets::SectionLabel(LOCTEXT("Palette", "ITEMS — double-click to add")) ]
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 0.0f, 4.0f, 4.0f)
					[
						SNew(SSearchBox)
						.HintText(LOCTEXT("SearchHint", "Filter items..."))
						.OnTextChanged(this, &SNexusInventorySandbox::OnSearchChanged)
					]
					+ SVerticalBox::Slot().FillHeight(1.0f)
					[
						SAssignNew(PaletteList, SListView<TSharedPtr<FPaletteEntry>>)
						.ListItemsSource(&FilteredPalette)
						.OnGenerateRow(this, &SNexusInventorySandbox::OnGeneratePaletteRow)
						.OnMouseButtonDoubleClick(this, &SNexusInventorySandbox::OnPaletteActivated)
						.SelectionMode(ESelectionMode::Single)
					]
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f)
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.Text(LOCTEXT("AddSelected", "Add Selected →"))
						.OnClicked(this, &SNexusInventorySandbox::OnAddSelectedClicked)
					]
				]
			]

			+ SSplitter::Slot().Value(0.68f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(4.0f)
				[
					SNew(SScrollBox)
					.Orientation(Orient_Vertical)
					+ SScrollBox::Slot()
					[
						SNew(SBox).HAlign(HAlign_Left).VAlign(VAlign_Top)
						[ SAssignNew(Canvas, SNexusInventoryCanvas) ]
					]
				]
			]
		]
	];
}

void SNexusInventorySandbox::RebuildPalette()
{
	AllPalette.Reset();

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item)
		{
			continue;
		}
		TSharedPtr<FPaletteEntry> Entry = MakeShared<FPaletteEntry>();
		Entry->Item = Item;
		Entry->Name = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);
		Entry->Grid = FIntPoint(FMath::Max(1, Item->GridSize.X), FMath::Max(1, Item->GridSize.Y));
		Entry->IconBrush = NexusEditorWidgets::IconBrush(Item->Icon.LoadSynchronous());
		AllPalette.Add(Entry);
	}

	AllPalette.Sort([](const TSharedPtr<FPaletteEntry>& A, const TSharedPtr<FPaletteEntry>& B)
	{
		return (A.IsValid() ? A->Name : FString()) < (B.IsValid() ? B->Name : FString());
	});

	ApplyFilter();
}

void SNexusInventorySandbox::ApplyFilter()
{
	FilteredPalette.Reset();
	for (const TSharedPtr<FPaletteEntry>& Entry : AllPalette)
	{
		if (!Entry.IsValid())
		{
			continue;
		}
		if (Filter.IsEmpty() || Entry->Name.Contains(Filter))
		{
			FilteredPalette.Add(Entry);
		}
	}
	if (PaletteList.IsValid())
	{
		PaletteList->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SNexusInventorySandbox::OnGeneratePaletteRow(
	TSharedPtr<FPaletteEntry> Entry, const TSharedRef<STableViewBase>& Owner)
{
	const bool bHasIcon = Entry.IsValid() && Entry->IconBrush.IsValid();
	const FString Label = Entry.IsValid()
		? FString::Printf(TEXT("%s   (%dx%d)"), *Entry->Name, Entry->Grid.X, Entry->Grid.Y)
		: FString();

	return SNew(STableRow<TSharedPtr<FPaletteEntry>>, Owner)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(FMargin(4.0f, 2.0f, 8.0f, 2.0f))
		[
			SNew(SBox).WidthOverride(28.0f).HeightOverride(28.0f)
			[
				bHasIcon
					? StaticCastSharedRef<SWidget>(SNew(SImage).Image(Entry->IconBrush.Get()))
					: SNullWidget::NullWidget
			]
		]
		+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Label))
			.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
		]
	];
}

void SNexusInventorySandbox::OnPaletteActivated(TSharedPtr<FPaletteEntry> Entry)
{
	AddEntryToCanvas(Entry);
}

void SNexusInventorySandbox::OnSearchChanged(const FText& Text)
{
	Filter = Text.ToString();
	ApplyFilter();
}

void SNexusInventorySandbox::AddEntryToCanvas(const TSharedPtr<FPaletteEntry>& Entry)
{
	if (Canvas.IsValid() && Entry.IsValid() && Entry->Item.IsValid())
	{
		Canvas->AddItem(Entry->Item.Get());
	}
}

FReply SNexusInventorySandbox::OnAddSelectedClicked()
{
	if (PaletteList.IsValid())
	{
		const TArray<TSharedPtr<FPaletteEntry>> Selected = PaletteList->GetSelectedItems();
		if (Selected.Num() > 0)
		{
			AddEntryToCanvas(Selected[0]);
		}
	}
	return FReply::Handled();
}

FReply SNexusInventorySandbox::OnAutoArrangeClicked()
{
	if (Canvas.IsValid()) { Canvas->AutoArrange(); }
	return FReply::Handled();
}

FReply SNexusInventorySandbox::OnClearClicked()
{
	if (Canvas.IsValid()) { Canvas->ClearAll(); }
	return FReply::Handled();
}

FReply SNexusInventorySandbox::OnRotateClicked()
{
	if (Canvas.IsValid()) { Canvas->RotateHeld(); }
	return FReply::Handled();
}

FReply SNexusInventorySandbox::OnRefreshClicked()
{
	RebuildPalette();
	return FReply::Handled();
}

TSharedRef<SWidget> SNexusInventorySandbox::MakeCaseSizeMenu()
{
	FMenuBuilder MenuBuilder(/*bShouldCloseWindowAfterMenuSelection=*/ true, nullptr);

	auto AddSize = [this, &MenuBuilder](int32 W, int32 H, const FText& Label)
	{
		MenuBuilder.AddMenuEntry(
			Label, FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([this, W, H]() { SetCaseSize(W, H); })));
	};

	AddSize(6, 4, LOCTEXT("Case6x4", "6 × 4  (Starter)"));
	AddSize(8, 6, LOCTEXT("Case8x6", "8 × 6"));
	AddSize(10, 8, LOCTEXT("Case10x8", "10 × 8  (Default)"));
	AddSize(12, 10, LOCTEXT("Case12x10", "12 × 10"));
	AddSize(14, 12, LOCTEXT("Case14x12", "14 × 12  (Large)"));

	return MenuBuilder.MakeWidget();
}

void SNexusInventorySandbox::SetCaseSize(int32 Width, int32 Height)
{
	CaseWidth = Width;
	CaseHeight = Height;
	if (Canvas.IsValid())
	{
		Canvas->ResetGrid(Width, Height);
	}
}

FText SNexusInventorySandbox::GetCaseSizeText() const
{
	return FText::Format(LOCTEXT("CaseSizeFmt", "{0} × {1}"),
		FText::AsNumber(CaseWidth), FText::AsNumber(CaseHeight));
}

FText SNexusInventorySandbox::GetStatusText() const
{
	if (!Canvas.IsValid())
	{
		return FText::GetEmpty();
	}
	return FText::Format(
		LOCTEXT("StatusFmt", "{0} item(s)  ·  {1}/{2} cells used     drag to move · R to rotate · right-click to remove"),
		FText::AsNumber(Canvas->GetItemCount()),
		FText::AsNumber(Canvas->GetUsedCellCount()),
		FText::AsNumber(Canvas->GetTotalCellCount()));
}

#undef LOCTEXT_NAMESPACE
