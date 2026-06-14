#include "Sandbox/SNexusInventorySandbox.h"

#include "NexusEditorModule.h"
#include "Sandbox/SNexusInventoryCanvas.h"
#include "Shared/NexusEditorPersistence.h"
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
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Levels/NexusLevelManifest.h"

#define LOCTEXT_NAMESPACE "NexusInventorySandbox"

void SNexusInventorySandbox::Construct(const FArguments& InArgs)
{
	RebuildPalette();

	// Restore the last case size used (per-user).
	CaseWidth = FMath::Clamp(NexusEditorPersistence::GetInt(TEXT("CaseWidth"), CaseWidth), 1, 40);
	CaseHeight = FMath::Clamp(NexusEditorPersistence::GetInt(TEXT("CaseHeight"), CaseHeight), 1, 40);

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
				// SWrapBox so the toolbar wraps to a new row in a narrow tool pane instead of
				// overflowing past the pane edge into the Inspector. InnerSlotPadding gives the
				// uniform spacing the old per-slot Padding used to.
				SNew(SWrapBox)
				.UseAllottedSize(true)
				.InnerSlotPadding(FVector2D(6.0f, 4.0f))
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[ NexusEditorWidgets::SectionLabel(LOCTEXT("CaseLabel", "CASE")) ]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SComboButton)
					.OnGetMenuContent(this, &SNexusInventorySandbox::MakeCaseSizeMenu)
					.ToolTipText(LOCTEXT("CaseTip", "Pick a preset case size; the grid resizes (and clears) to match."))
					.ButtonContent()
					[ SNew(STextBlock).Text(this, &SNexusInventorySandbox::GetCaseSizeText) ]
				]
				// Custom W x H entry.
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SBox).WidthOverride(56.0f)
					[
						SNew(SSpinBox<int32>)
						.MinValue(1).MaxValue(40)
						.ToolTipText(LOCTEXT("CustomWTip", "Custom case width (cells)."))
						.Value_Lambda([this]() { return CaseWidth; })
						.OnValueChanged_Lambda([this](int32 V) { CaseWidth = FMath::Clamp(V, 1, 40); })
					]
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[ SNew(STextBlock).Text(LOCTEXT("ByX", "×")) ]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SBox).WidthOverride(56.0f)
					[
						SNew(SSpinBox<int32>)
						.MinValue(1).MaxValue(40)
						.ToolTipText(LOCTEXT("CustomHTip", "Custom case height (cells)."))
						.Value_Lambda([this]() { return CaseHeight; })
						.OnValueChanged_Lambda([this](int32 V) { CaseHeight = FMath::Clamp(V, 1, 40); })
					]
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SButton)
					.Text(LOCTEXT("Apply", "Apply"))
					.ToolTipText(LOCTEXT("ApplyTip", "Resize (and clear) the grid to the custom width × height."))
					.OnClicked_Lambda([this]() { SetCaseSize(CaseWidth, CaseHeight); return FReply::Handled(); })
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SComboButton)
					.OnGetMenuContent(this, &SNexusInventorySandbox::MakeCaseItemMenu)
					.ToolTipText(LOCTEXT("LoadCaseTip", "Load the grid dimensions from an authored Case item's GridSize."))
					.ButtonContent()
					[ SNew(STextBlock).Text(LOCTEXT("LoadCase", "Load from Case…")) ]
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SComboButton)
					.OnGetMenuContent(this, &SNexusInventorySandbox::MakeFillMenu)
					.ToolTipText(LOCTEXT("FillTip", "Fill the grid with the items from a Level Manifest."))
					.ButtonContent()
					[ SNew(STextBlock).Text(LOCTEXT("Fill", "Fill from…")) ]
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SBox).WidthOverride(110.0f)
					[
						SAssignNew(LayoutNameBox, SEditableTextBox)
						.HintText(LOCTEXT("LayoutNameHint", "layout name"))
						.ToolTipText(LOCTEXT("LayoutNameTip", "Name to save the current packing under."))
					]
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SButton)
					.Text(LOCTEXT("SaveLayout", "Save"))
					.ToolTipText(LOCTEXT("SaveLayoutTip", "Save the current packing under the name on the left (per-user)."))
					.OnClicked(this, &SNexusInventorySandbox::OnSaveLayoutClicked)
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SComboButton)
					.OnGetMenuContent(this, &SNexusInventorySandbox::MakeLoadLayoutMenu)
					.ToolTipText(LOCTEXT("LoadLayoutTip", "Restore a saved packing layout."))
					.ButtonContent()
					[ SNew(STextBlock).Text(LOCTEXT("LoadLayout", "Load ▾")) ]
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SButton)
					.Text(LOCTEXT("AutoArrange", "Auto-arrange"))
					.ToolTipText(LOCTEXT("AutoArrangeTip", "Run the runtime first-fit-decreasing repack (the in-game Optimize)."))
					.OnClicked(this, &SNexusInventorySandbox::OnAutoArrangeClicked)
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SButton)
					.Text(LOCTEXT("Rotate", "Rotate"))
					.ToolTipText(LOCTEXT("RotateTip", "Rotate the item you're currently dragging 90° (or press R)."))
					.OnClicked(this, &SNexusInventorySandbox::OnRotateClicked)
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
				[
					SNew(SButton)
					.Text(LOCTEXT("Clear", "Clear"))
					.ToolTipText(LOCTEXT("ClearTip", "Empty the grid."))
					.OnClicked(this, &SNexusInventorySandbox::OnClearClicked)
				]
				+ SWrapBox::Slot().VAlign(VAlign_Center)
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
						.OnSelectionChanged(this, &SNexusInventorySandbox::OnPaletteSelectionChanged)
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

	// Apply the restored case size to the freshly-built canvas.
	if (Canvas.IsValid())
	{
		Canvas->ResetGrid(CaseWidth, CaseHeight);
	}
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

void SNexusInventorySandbox::OnPaletteSelectionChanged(TSharedPtr<FPaletteEntry> Entry, ESelectInfo::Type SelectInfo)
{
	// Surface the highlighted palette item in the Workbench Inspector so its GridSize
	// can be tuned inline; the canvas re-reads footprints live via the watcher.
	if (Entry.IsValid() && Entry->Item.IsValid())
	{
		FNexusEditorModule::SetSelection(Entry->Item.Get(), FNexusEditorModule::SandboxTabName);
	}
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

TSharedRef<SWidget> SNexusInventorySandbox::MakeCaseItemMenu()
{
	FMenuBuilder MenuBuilder(/*bShouldCloseWindowAfterMenuSelection=*/ true, nullptr);

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);

	bool bAny = false;
	for (UNexusItemDefinition* Item : Items)
	{
		const FNexusFragment_Case* Case = NexusEditorUtil::FindCaseFragment(Item);
		if (!Case)
		{
			continue;
		}
		bAny = true;
		const int32 W = FMath::Max(1, Case->GridSize.X);
		const int32 H = FMath::Max(1, Case->GridSize.Y);
		const FText Label = FText::FromString(FString::Printf(TEXT("%s   (%d × %d)"),
			*NexusEditorUtil::DisplayLabel(Item, Item->DisplayName), W, H));
		MenuBuilder.AddMenuEntry(
			Label, FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([this, W, H]() { SetCaseSize(W, H); })));
	}

	if (!bAny)
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("NoCases", "No Case items found"), FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction(), FCanExecuteAction::CreateLambda([]() { return false; })));
	}

	return MenuBuilder.MakeWidget();
}

TSharedRef<SWidget> SNexusInventorySandbox::MakeFillMenu()
{
	FMenuBuilder MenuBuilder(/*bShouldCloseWindowAfterMenuSelection=*/ true, nullptr);

	TArray<UNexusLevelManifest*> Manifests;
	NexusEditorUtil::GatherAssets(Manifests);

	if (Manifests.Num() == 0)
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("NoManifests", "No Level Manifests found"), FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction(), FCanExecuteAction::CreateLambda([]() { return false; })));
		return MenuBuilder.MakeWidget();
	}

	for (UNexusLevelManifest* Manifest : Manifests)
	{
		if (!Manifest)
		{
			continue;
		}
		TWeakObjectPtr<UNexusLevelManifest> WeakManifest = Manifest;
		const FText Label = FText::FromString(FString::Printf(TEXT("%s   (%d items)"),
			*Manifest->GetName(), Manifest->Items.Num()));
		MenuBuilder.AddMenuEntry(
			Label, FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([this, WeakManifest]()
			{
				UNexusLevelManifest* M = WeakManifest.Get();
				if (!M || !Canvas.IsValid())
				{
					return;
				}
				for (const TSoftObjectPtr<UNexusItemDefinition>& SoftItem : M->Items)
				{
					if (UNexusItemDefinition* Item = SoftItem.LoadSynchronous())
					{
						Canvas->AddItem(Item);
					}
				}
			})));
	}

	return MenuBuilder.MakeWidget();
}

namespace
{
	/** Per-user config key for a named Sandbox layout. */
	FString LayoutKey(const FString& Name)
	{
		FString Safe = Name;
		Safe.TrimStartAndEndInline();
		if (Safe.IsEmpty())
		{
			Safe = TEXT("Default");
		}
		// Keep the key INI-safe.
		Safe.ReplaceInline(TEXT(" "), TEXT("_"));
		Safe.ReplaceInline(TEXT("="), TEXT("_"));
		return FString::Printf(TEXT("Layout_%s"), *Safe);
	}
}

FReply SNexusInventorySandbox::OnSaveLayoutClicked()
{
	if (!Canvas.IsValid())
	{
		return FReply::Handled();
	}
	FString Name = LayoutNameBox.IsValid() ? LayoutNameBox->GetText().ToString() : FString();
	Name.TrimStartAndEndInline();
	if (Name.IsEmpty())
	{
		Name = TEXT("Default");
	}

	NexusEditorPersistence::SetString(*LayoutKey(Name), Canvas->SerializeLayout());

	// Maintain the index of saved layout names.
	TArray<FString> Names;
	NexusEditorPersistence::GetString(TEXT("LayoutNames")).ParseIntoArray(Names, TEXT(";"), /*CullEmpty=*/ true);
	Names.AddUnique(Name);
	NexusEditorPersistence::SetString(TEXT("LayoutNames"), FString::Join(Names, TEXT(";")));
	return FReply::Handled();
}

TSharedRef<SWidget> SNexusInventorySandbox::MakeLoadLayoutMenu()
{
	FMenuBuilder MenuBuilder(/*bShouldCloseWindowAfterMenuSelection=*/ true, nullptr);

	TArray<FString> Names;
	NexusEditorPersistence::GetString(TEXT("LayoutNames")).ParseIntoArray(Names, TEXT(";"), /*CullEmpty=*/ true);

	if (Names.Num() == 0)
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("NoLayouts", "No saved layouts"), FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction(), FCanExecuteAction::CreateLambda([]() { return false; })));
		return MenuBuilder.MakeWidget();
	}

	for (const FString& Name : Names)
	{
		MenuBuilder.AddMenuEntry(
			FText::FromString(Name), FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([this, Name]()
			{
				if (Canvas.IsValid())
				{
					Canvas->DeserializeLayout(NexusEditorPersistence::GetString(*LayoutKey(Name)));
				}
				if (LayoutNameBox.IsValid())
				{
					LayoutNameBox->SetText(FText::FromString(Name));
				}
			})));
	}

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
	// Remember it for next session.
	NexusEditorPersistence::SetInt(TEXT("CaseWidth"), CaseWidth);
	NexusEditorPersistence::SetInt(TEXT("CaseHeight"), CaseHeight);
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
	const int32 Used = Canvas->GetUsedCellCount();
	const int32 Total = FMath::Max(1, Canvas->GetTotalCellCount());
	const int32 Free = FMath::Max(0, Total - Used);
	const int32 Percent = FMath::RoundToInt(100.0f * Used / Total);
	return FText::Format(
		LOCTEXT("StatusFmt", "{0} item(s)  ·  {1}/{2} cells ({3}% full, {4} free)     drag to move · R to rotate · right-click to remove"),
		FText::AsNumber(Canvas->GetItemCount()),
		FText::AsNumber(Used), FText::AsNumber(Total),
		FText::AsNumber(Percent), FText::AsNumber(Free));
}

#undef LOCTEXT_NAMESPACE
