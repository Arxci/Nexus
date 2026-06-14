#include "Workbench/SNexusWorkbench.h"

#include "NexusEditorModule.h"
#include "Manifest/NexusManifestBuilder.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorPersistence.h"
#include "Shared/NexusEditorSelection.h"
#include "Shared/NexusEditorStyle.h"
#include "Shared/NexusEditorTools.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#include "Home/SNexusHomePage.h"
#include "Inspector/SNexusInspector.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"

#include "Crafting/SNexusCraftingTree.h"
#include "Creation/SNexusCreatorWindow.h"
#include "Dashboard/SNexusContentDashboard.h"
#include "Docs/SNexusDocsBrowser.h"
#include "Economy/SNexusEconomyView.h"
#include "Insights/SNexusIconSheet.h"
#include "Insights/SNexusContentInsights.h"
#include "Live/SNexusLiveInventory.h"
#include "Grid/SNexusGridPreview.h"
#include "Sandbox/SNexusInventorySandbox.h"
#include "Inventory/SNexusInventoryWorkspace.h"
#include "Matrix/SNexusAttachmentMatrix.h"
#include "Preview/SNexusAssemblyPreview.h"
#include "Tags/SNexusTagAudit.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "InputCoreTypes.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"

#define LOCTEXT_NAMESPACE "NexusWorkbench"

const FName SNexusWorkbench::HomeTabName(TEXT("NexusWorkbenchHome"));

void SNexusWorkbench::Construct(const FArguments& InArgs)
{
	// Restore per-user splitter weights.
	NavValue = NexusEditorPersistence::GetFloat(TEXT("NavSize"), NavValue);
	ToolValue = NexusEditorPersistence::GetFloat(TEXT("ToolSize"), ToolValue);
	InspectorValue = NexusEditorPersistence::GetFloat(TEXT("InspectorSize"), InspectorValue);

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(0.0f)
		[
			SNew(SVerticalBox)

			// === Header band: workbench branding ================================
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
				.Padding(FMargin(12.0f, 6.0f))
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("WorkbenchTitle", "Nexus Workbench"))
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					.VAlign(VAlign_Center)
					.Padding(12.0f, 0.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(this, &SNexusWorkbench::GetCurrentToolLabel)
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					]
				]
			]

			// === Navigator | Tool | Inspector ===================================
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SSplitter)
				.Orientation(Orient_Horizontal)

				// Navigator.
				+ SSplitter::Slot()
				.Value(NavValue)
				.OnSlotResized_Lambda([this](float NewSize)
				{
					NavValue = NewSize;
					NexusEditorPersistence::SetFloat(TEXT("NavSize"), NewSize);
				})
				[
					BuildNavigator()
				]

				// Active tool.
				+ SSplitter::Slot()
				.Value(ToolValue)
				.OnSlotResized_Lambda([this](float NewSize)
				{
					ToolValue = NewSize;
					NexusEditorPersistence::SetFloat(TEXT("ToolSize"), NewSize);
				})
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
					.Padding(0.0f)
					[
						SAssignNew(ContentBox, SBox)
					]
				]

				// Inspector.
				+ SSplitter::Slot()
				.Value(InspectorValue)
				.OnSlotResized_Lambda([this](float NewSize)
				{
					InspectorValue = NewSize;
					NexusEditorPersistence::SetFloat(TEXT("InspectorSize"), NewSize);
				})
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
					.Padding(0.0f)
					[
						SAssignNew(Inspector, SNexusInspector)
						.OnJumpToTool(FNexusInspectorJump::CreateSP(this, &SNexusWorkbench::ShowTool))
					]
				]
			]
		]
	];

	// Build the searchable index and keep it fresh as content changes.
	BuildSearchIndex();
	SearchWatcher = MakeShared<FNexusAssetWatcher>();
	SearchWatcher->Start(
		{ UNexusItemDefinition::StaticClass(), UNexusAttachmentDefinition::StaticClass(), UNexusCombinationRecipe::StaticClass() },
		[this]() { BuildSearchIndex(); ApplySearchFilter(); RebuildQuickAccess(); });

	// Restore pinned + recent quick-access, and record future selections as recents.
	NexusEditorPersistence::GetString(TEXT("Pinned")).ParseIntoArray(PinnedPaths, TEXT(";"), /*CullEmpty=*/ true);
	NexusEditorPersistence::GetString(TEXT("Recent")).ParseIntoArray(RecentPaths, TEXT(";"), /*CullEmpty=*/ true);
	if (FNexusSelectionService* Service = FNexusEditorModule::TrySelection())
	{
		SelectionHandle = Service->Subscribe(
			FNexusOnSelectionChanged::FDelegate::CreateSP(this, &SNexusWorkbench::OnGlobalSelectionChanged));
	}
	RebuildQuickAccess();

	// Restore the last tool shown (per-user), defaulting to Home.
	const FString LastTool = NexusEditorPersistence::GetString(TEXT("LastTool"));
	const FName LastTab = LastTool.IsEmpty() ? HomeTabName : FName(*LastTool);
	const bool bKnown = (LastTab == HomeTabName) || (NexusEditorTools::Find(LastTab) != nullptr);
	ShowTool(bKnown ? LastTab : HomeTabName);
}

SNexusWorkbench::~SNexusWorkbench()
{
	if (FNexusSelectionService* Service = FNexusEditorModule::TrySelection())
	{
		Service->Unsubscribe(SelectionHandle);
	}
}

FReply SNexusWorkbench::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::K && InKeyEvent.IsControlDown())
	{
		FocusSearch();
		return FReply::Handled();
	}
	return SCompoundWidget::OnKeyDown(MyGeometry, InKeyEvent);
}

TSharedRef<SWidget> SNexusWorkbench::BuildNavigator()
{
	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(0.0f)
		[
			SNew(SVerticalBox)

			// Global search box (Ctrl-K focuses it).
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(6.0f, 6.0f, 6.0f, 4.0f)
			[
				SAssignNew(SearchBox, SSearchBox)
				.HintText(LOCTEXT("SearchHint", "Search items, attachments, recipes  (Ctrl-K)"))
				.OnTextChanged(this, &SNexusWorkbench::OnSearchTextChanged)
			]

			// Pinned + recent quick-access (collapses when empty).
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBox)
				.Visibility(this, &SNexusWorkbench::GetQuickAccessVisibility)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(8.0f, 4.0f, 8.0f, 2.0f)
					[ NexusEditorWidgets::SectionLabel(LOCTEXT("QuickLabel", "PINNED & RECENT")) ]
					+ SVerticalBox::Slot().AutoHeight()
					[
						SNew(SBox).MaxDesiredHeight(160.0f)
						[
							SAssignNew(QuickList, SListView<TSharedPtr<FSearchEntry>>)
							.ListItemsSource(&QuickAccess)
							.OnGenerateRow(this, &SNexusWorkbench::OnGenerateQuickRow)
							.OnSelectionChanged(this, &SNexusWorkbench::OnSearchSelectionChanged)
							.SelectionMode(ESelectionMode::Single)
						]
					]
				]
			]

			// Tool list, or search results when a query is typed.
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SWidgetSwitcher)
				.WidgetIndex(this, &SNexusWorkbench::GetNavIndex)

				// 0 — the tool list.
				+ SWidgetSwitcher::Slot()
				[
					BuildSidebar()
				]

				// 1 — search results.
				+ SWidgetSwitcher::Slot()
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
					.Padding(2.0f)
					[
						SAssignNew(SearchListView, SListView<TSharedPtr<FSearchEntry>>)
						.ListItemsSource(&SearchResults)
						.OnGenerateRow(this, &SNexusWorkbench::OnGenerateSearchRow)
						.OnSelectionChanged(this, &SNexusWorkbench::OnSearchSelectionChanged)
						.SelectionMode(ESelectionMode::Single)
					]
				]
			]
		];
}

TSharedRef<SWidget> SNexusWorkbench::BuildSidebar()
{
	TSharedRef<SVerticalBox> Stack = SNew(SVerticalBox);

	// Home sits above the categories — the suite's front door.
	Stack->AddSlot()
		.AutoHeight()
		.Padding(4.0f, 8.0f, 4.0f, 1.0f)
		[
			BuildSidebarEntry(HomeTabName,
				LOCTEXT("HomeEntry", "Home"),
				TEXT("Icons.Home"),
				LOCTEXT("HomeEntryTip", "The suite's front door: tool cards and a content-health summary."))
		];

	auto AddCategoryHeader = [this, &Stack](NexusEditorTools::ECategory Category)
	{
		Stack->AddSlot()
			.AutoHeight()
			.Padding(8.0f, 12.0f, 8.0f, 4.0f)
			[
				NexusEditorWidgets::SectionLabel(
					NexusEditorTools::CategoryLabel(Category).ToUpper())
			];

		for (const NexusEditorTools::FToolEntry& Entry : NexusEditorTools::All())
		{
			if (Entry.Category == Category)
			{
				Stack->AddSlot()
					.AutoHeight()
					.Padding(4.0f, 1.0f)
					[
						BuildSidebarEntry(Entry.TabName, Entry.Label, Entry.IconName, Entry.Tooltip)
					];
			}
		}
	};

	AddCategoryHeader(NexusEditorTools::ECategory::Authoring);
	AddCategoryHeader(NexusEditorTools::ECategory::Inspection);
	AddCategoryHeader(NexusEditorTools::ECategory::Auditing);

	// Footer: cross-cutting actions that don't have their own tab.
	Stack->AddSlot()
		.AutoHeight()
		.Padding(8.0f, 12.0f, 8.0f, 4.0f)
		[
			NexusEditorWidgets::SectionLabel(LOCTEXT("ActionsLabel", "ACTIONS"))
		];

	Stack->AddSlot()
		.AutoHeight()
		.Padding(4.0f, 1.0f)
		[
			SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
			.ContentPadding(FMargin(8.0f, 6.0f))
			.HAlign(HAlign_Left)
			.ToolTipText(LOCTEXT("BuildManifestTip", "Scan the open level for items/attachments and create or update its manifest."))
			.OnClicked_Lambda([]()
			{
				FString Message;
				UNexusLevelManifest* Manifest = FNexusManifestBuilder::BuildFromCurrentLevel(Message);

				FNotificationInfo Info(FText::FromString(Message));
				Info.ExpireDuration = 7.0f;
				FSlateNotificationManager::Get().AddNotification(Info);

				if (Manifest)
				{
					FNexusEditorModule::OpenCreatorWith(Manifest);
				}
				return FReply::Handled();
			})
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.0f, 0.0f, 8.0f, 0.0f)
				[
					SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.Save"))
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(LOCTEXT("BuildManifest", "Build Level Manifest"))
				]
			]
		];

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(0.0f)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				Stack
			]
		];
}

TSharedRef<SWidget> SNexusWorkbench::BuildSidebarEntry(FName TabName, const FText& Label, const FName IconName, const FText& Tooltip)
{
	return SNew(SCheckBox)
		.Style(FAppStyle::Get(), "DetailsView.SectionButton")
		.Padding(FMargin(10.0f, 6.0f))
		.ToolTipText(Tooltip)
		.IsChecked_Lambda([this, TabName]()
		{
			return CurrentTab == TabName ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		})
		.OnCheckStateChanged_Lambda([this, TabName](ECheckBoxState NewState)
		{
			if (NewState == ECheckBoxState::Checked)
			{
				ShowTool(TabName);
			}
		})
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 8.0f, 0.0f)
			[
				SNew(SBox)
				.WidthOverride(16.0f)
				.HeightOverride(16.0f)
				[
					SNew(SImage).Image(FAppStyle::Get().GetBrush(IconName))
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock).Text(Label)
			]
		];
}

void SNexusWorkbench::ShowTool(FName TabName)
{
	if (!ContentBox.IsValid())
	{
		return;
	}

	TSharedPtr<SWidget>& Cached = ToolCache.FindOrAdd(TabName);
	if (!Cached.IsValid())
	{
		Cached = ConstructToolWidget(TabName);
	}

	if (Cached.IsValid())
	{
		CurrentTab = TabName;
		ContentBox->SetContent(Cached.ToSharedRef());
		NexusEditorPersistence::SetString(TEXT("LastTool"), TabName.ToString());

		// Suppress the shared Inspector for tools that bring their own editor (the Creator).
		if (Inspector.IsValid())
		{
			const NexusEditorTools::FToolEntry* Entry = NexusEditorTools::Find(TabName);
			Inspector->SetSuppressed(Entry != nullptr && !Entry->bUsesSharedInspector);
		}
	}
}

TSharedPtr<SWidget> SNexusWorkbench::ConstructToolWidget(FName TabName)
{
	if (TabName == HomeTabName)
	{
		return SNew(SNexusHomePage)
			.OnActivateTool(FNexusOnActivateTool::CreateSP(this, &SNexusWorkbench::ShowTool));
	}
	if (TabName == FNexusEditorModule::DashboardTabName) { return SNew(SNexusContentDashboard); }
	if (TabName == FNexusEditorModule::CreatorTabName)
	{
		// Reassigns the module's ActiveCreator weak ptr so hand-offs target this instance.
		TSharedRef<SNexusCreatorWindow> Creator = SNew(SNexusCreatorWindow);
		FNexusEditorModule::RegisterCreator(Creator);
		return Creator;
	}
	if (TabName == FNexusEditorModule::PreviewTabName)  { return SNew(SNexusAssemblyPreview); }
	if (TabName == FNexusEditorModule::CraftingTabName) { return SNew(SNexusCraftingTree); }
	if (TabName == FNexusEditorModule::MatrixTabName)   { return SNew(SNexusAttachmentMatrix); }
	if (TabName == FNexusEditorModule::GridTabName)     { return SNew(SNexusGridPreview); }
	if (TabName == FNexusEditorModule::SandboxTabName)  { return SNew(SNexusInventorySandbox); }
	if (TabName == FNexusEditorModule::InventoryTabName) { return SNew(SNexusInventoryWorkspace); }
	if (TabName == FNexusEditorModule::TagAuditTabName) { return SNew(SNexusTagAudit); }
	if (TabName == FNexusEditorModule::EconomyTabName)  { return SNew(SNexusEconomyView); }
	if (TabName == FNexusEditorModule::DocsTabName)     { return SNew(SNexusDocsBrowser); }
	if (TabName == FNexusEditorModule::IconSheetTabName) { return SNew(SNexusIconSheet); }
	if (TabName == FNexusEditorModule::InsightsTabName) { return SNew(SNexusContentInsights); }
	if (TabName == FNexusEditorModule::LiveInventoryTabName) { return SNew(SNexusLiveInventory); }
	return nullptr;
}

void SNexusWorkbench::BuildSearchIndex()
{
	SearchIndex.Reset();

	auto AddEntry = [this](UObject* Object, const FString& Name, const FString& Type, const FLinearColor& Color)
	{
		if (!Object)
		{
			return;
		}
		TSharedPtr<FSearchEntry> Entry = MakeShared<FSearchEntry>();
		Entry->Object = Object;
		Entry->Name = Name;
		Entry->Type = Type;
		Entry->Path = Object->GetPathName();
		Entry->TypeColor = Color;
		SearchIndex.Add(Entry);
	};

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	for (UNexusItemDefinition* Item : Items)
	{
		const FLinearColor Color = NexusEditorUtil::HasWeaponFragment(Item)
			? FLinearColor(0.30f, 0.55f, 0.95f)
			: NexusEditorStyle::CategoryColor(TEXT("item"));
		AddEntry(Item, NexusEditorUtil::DisplayLabel(Item, Item ? Item->DisplayName : FText::GetEmpty()), TEXT("Item"), Color);
	}

	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Attachments);
	for (UNexusAttachmentDefinition* Attachment : Attachments)
	{
		AddEntry(Attachment, Attachment ? Attachment->GetName() : FString(), TEXT("Attachment"), FLinearColor(0.35f, 0.80f, 0.45f));
	}

	TArray<UNexusCombinationRecipe*> Recipes;
	NexusEditorUtil::GatherAssets(Recipes);
	for (UNexusCombinationRecipe* Recipe : Recipes)
	{
		AddEntry(Recipe, Recipe ? Recipe->GetName() : FString(), TEXT("Recipe"), FLinearColor(0.95f, 0.72f, 0.25f));
	}

	SearchIndex.Sort([](const TSharedPtr<FSearchEntry>& A, const TSharedPtr<FSearchEntry>& B)
	{
		return (A.IsValid() ? A->Name : FString()) < (B.IsValid() ? B->Name : FString());
	});
}

void SNexusWorkbench::OnSearchTextChanged(const FText& Text)
{
	SearchQuery = Text.ToString();
	ApplySearchFilter();
}

void SNexusWorkbench::ApplySearchFilter()
{
	SearchResults.Reset();
	if (!SearchQuery.IsEmpty())
	{
		for (const TSharedPtr<FSearchEntry>& Entry : SearchIndex)
		{
			if (Entry.IsValid() && Entry->Object.IsValid() && Entry->Name.Contains(SearchQuery))
			{
				SearchResults.Add(Entry);
				if (SearchResults.Num() >= 50)
				{
					break;   // cap — this is a jump-to, not a browser
				}
			}
		}
	}
	if (SearchListView.IsValid())
	{
		SearchListView->RequestListRefresh();
	}
}

int32 SNexusWorkbench::GetNavIndex() const
{
	return SearchQuery.IsEmpty() ? 0 : 1;
}

TSharedRef<ITableRow> SNexusWorkbench::OnGenerateSearchRow(
	TSharedPtr<FSearchEntry> Entry, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(STableRow<TSharedPtr<FSearchEntry>>, Owner)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			MakePinButton(Entry)
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.VAlign(VAlign_Center)
		.Padding(FMargin(4.0f, 3.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromString(Entry.IsValid() ? Entry->Name : FString()))
			.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(FMargin(4.0f, 2.0f, 6.0f, 2.0f))
		[
			Entry.IsValid()
				? NexusEditorWidgets::Chip(FText::FromString(Entry->Type), Entry->TypeColor)
				: SNullWidget::NullWidget
		]
	];
}

TSharedRef<ITableRow> SNexusWorkbench::OnGenerateQuickRow(
	TSharedPtr<FSearchEntry> Entry, const TSharedRef<STableViewBase>& Owner)
{
	// Same row shape as search results (pin · name · type chip).
	return OnGenerateSearchRow(Entry, Owner);
}

TSharedRef<SWidget> SNexusWorkbench::MakePinButton(TSharedPtr<FSearchEntry> Entry)
{
	const FString Path = Entry.IsValid() ? Entry->Path : FString();
	return SNew(SButton)
		.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
		.ContentPadding(FMargin(4.0f, 0.0f))
		.ToolTipText(LOCTEXT("PinTip", "Pin / unpin this asset for quick access."))
		.OnClicked_Lambda([this, Path]() { TogglePin(Path); return FReply::Handled(); })
		[
			SNew(STextBlock)
			.Text_Lambda([this, Path]()
			{
				return FText::FromString(IsPinned(Path) ? TEXT("★") : TEXT("☆"));
			})
			.ColorAndOpacity_Lambda([this, Path]()
			{
				return IsPinned(Path) ? FSlateColor(FStyleColors::AccentYellow) : FSlateColor::UseSubduedForeground();
			})
		];
}

TSharedPtr<SNexusWorkbench::FSearchEntry> SNexusWorkbench::FindIndexed(const FString& Path) const
{
	for (const TSharedPtr<FSearchEntry>& Entry : SearchIndex)
	{
		if (Entry.IsValid() && Entry->Path == Path)
		{
			return Entry;
		}
	}
	return nullptr;
}

bool SNexusWorkbench::IsPinned(const FString& Path) const
{
	return PinnedPaths.Contains(Path);
}

void SNexusWorkbench::TogglePin(const FString& Path)
{
	if (Path.IsEmpty())
	{
		return;
	}
	if (PinnedPaths.Contains(Path))
	{
		PinnedPaths.Remove(Path);
	}
	else
	{
		PinnedPaths.Insert(Path, 0);
	}
	NexusEditorPersistence::SetString(TEXT("Pinned"), FString::Join(PinnedPaths, TEXT(";")));
	RebuildQuickAccess();
}

void SNexusWorkbench::OnGlobalSelectionChanged(const FNexusSelection& Selection)
{
	UObject* Object = Selection.Get();
	if (!Object)
	{
		return;
	}
	const FString Path = Object->GetPathName();
	RecentPaths.Remove(Path);
	RecentPaths.Insert(Path, 0);
	constexpr int32 MaxRecent = 10;
	if (RecentPaths.Num() > MaxRecent)
	{
		RecentPaths.SetNum(MaxRecent);
	}
	NexusEditorPersistence::SetString(TEXT("Recent"), FString::Join(RecentPaths, TEXT(";")));
	RebuildQuickAccess();
}

void SNexusWorkbench::RebuildQuickAccess()
{
	QuickAccess.Reset();
	for (const FString& Path : PinnedPaths)
	{
		if (TSharedPtr<FSearchEntry> Entry = FindIndexed(Path))
		{
			QuickAccess.Add(Entry);
		}
	}
	for (const FString& Path : RecentPaths)
	{
		if (!PinnedPaths.Contains(Path))
		{
			if (TSharedPtr<FSearchEntry> Entry = FindIndexed(Path))
			{
				QuickAccess.Add(Entry);
			}
		}
	}
	if (QuickList.IsValid())
	{
		QuickList->RequestListRefresh();
	}
}

EVisibility SNexusWorkbench::GetQuickAccessVisibility() const
{
	return QuickAccess.Num() > 0 ? EVisibility::Visible : EVisibility::Collapsed;
}

void SNexusWorkbench::OnSearchSelectionChanged(TSharedPtr<FSearchEntry> Entry, ESelectInfo::Type SelectInfo)
{
	// A click counts; ignore the programmatic clear on refresh.
	if (SelectInfo == ESelectInfo::Direct)
	{
		return;
	}
	if (Entry.IsValid() && Entry->Object.IsValid())
	{
		FNexusEditorModule::SetSelection(Entry->Object.Get(), NAME_None);
	}
}

void SNexusWorkbench::FocusSearch()
{
	if (SearchBox.IsValid())
	{
		FSlateApplication::Get().SetKeyboardFocus(SearchBox);
	}
}

FText SNexusWorkbench::GetCurrentToolLabel() const
{
	if (CurrentTab.IsNone())
	{
		return FText::GetEmpty();
	}
	if (CurrentTab == HomeTabName)
	{
		return LOCTEXT("HomeLabel", "Home");
	}
	if (const NexusEditorTools::FToolEntry* Entry = NexusEditorTools::Find(CurrentTab))
	{
		return Entry->Label;
	}
	return FText::GetEmpty();
}

#undef LOCTEXT_NAMESPACE
