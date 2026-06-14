#include "Docs/SNexusDocsBrowser.h"

#include "Docs/NexusMarkdown.h"
#include "Shared/NexusEditorWidgets.h"

#include "Framework/Application/SlateApplication.h"
#include "Shared/NexusEditorPersistence.h"
#include "Framework/Notifications/NotificationManager.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformApplicationMisc.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"
#include "SourceCodeNavigation.h"
#include "Misc/FileHelper.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateTypes.h"
#include "Styling/StyleColors.h"

#include "Widgets/SWindow.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "NexusDocsBrowser"

namespace
{
	// Badge palette: subdued backgrounds, white-on-dark text so they read like
	// the Blueprint editor's pin colours without being too loud.
	const FLinearColor BadgeBlue   (0.18f, 0.42f, 0.70f, 1.0f); // Callable
	const FLinearColor BadgeGreen  (0.20f, 0.55f, 0.30f, 1.0f); // Pure / Readable
	const FLinearColor BadgeOrange (0.75f, 0.45f, 0.10f, 1.0f); // Event
	const FLinearColor BadgePurple (0.45f, 0.30f, 0.70f, 1.0f); // Net (Server/Client/Multicast)
	const FLinearColor BadgeTeal   (0.15f, 0.55f, 0.55f, 1.0f); // Latent
	const FLinearColor BadgeGray   (0.35f, 0.35f, 0.35f, 1.0f); // Static / Misc
	const FLinearColor BadgeRed    (0.65f, 0.20f, 0.20f, 1.0f); // Replicated / out param
	const FLinearColor BadgeIndigo (0.30f, 0.30f, 0.55f, 1.0f); // Saved / Const

	// Type-chip palette: one stable colour per kind so designers learn the map
	// and can scan the tree by colour alone. All slightly desaturated so a row
	// of chips doesn't compete with the row's text.
	const FLinearColor ChipClass      (0.32f, 0.36f, 0.42f, 1.0f); // neutral steel
	const FLinearColor ChipComponent  (0.22f, 0.48f, 0.72f, 1.0f); // blue
	const FLinearColor ChipSubsystem  (0.50f, 0.32f, 0.70f, 1.0f); // purple
	const FLinearColor ChipLibrary    (0.18f, 0.55f, 0.55f, 1.0f); // teal
	const FLinearColor ChipInterface  (0.74f, 0.55f, 0.18f, 1.0f); // amber
	const FLinearColor ChipActor      (0.74f, 0.34f, 0.20f, 1.0f); // rust
	const FLinearColor ChipStruct     (0.28f, 0.55f, 0.32f, 1.0f); // green

	bool TextContains(const FString& Haystack, const FString& Needle)
	{
		return !Needle.IsEmpty() && Haystack.Contains(Needle, ESearchCase::IgnoreCase);
	}

	void Notify(const FText& Message)
	{
		FNotificationInfo Info(Message);
		Info.ExpireDuration = 2.5f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}

	/**
	 * Friendly title for the architecture markdown files. We display them in the
	 * Reading Guide footer as click-to-open links. "AttachmentArchitecture.md"
	 * becomes "Attachment Architecture".
	 */
	FString TitleFromMarkdownFile(const FString& FileName)
	{
		FString Base = FPaths::GetBaseFilename(FileName);
		FString Out;
		Out.Reserve(Base.Len() + 4);
		for (int32 Index = 0; Index < Base.Len(); ++Index)
		{
			const TCHAR Ch = Base[Index];
			if (Index > 0 && FChar::IsUpper(Ch))
			{
				const TCHAR Prev = Base[Index - 1];
				if (FChar::IsLower(Prev) || FChar::IsDigit(Prev))
				{
					Out.AppendChar(TEXT(' '));
				}
			}
			Out.AppendChar(Ch);
		}
		return Out;
	}
}

// =============================================================================
// Construction
// =============================================================================

void SNexusDocsBrowser::Construct(const FArguments& InArgs)
{
	RebuildModel();

	// Restore pinned types + navigation history across editor restarts (per-user).
	{
		TArray<FString> PinnedList;
		NexusEditorPersistence::GetString(TEXT("DocsPinned")).ParseIntoArray(PinnedList, TEXT(";"), /*CullEmpty=*/ true);
		Pinned.Append(PinnedList);
		NexusEditorPersistence::GetString(TEXT("DocsHistory")).ParseIntoArray(History, TEXT(";"), /*CullEmpty=*/ true);
		HistoryIndex = History.Num() - 1;
	}

	RebuildTree();
	DiscoverArchDocs();

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(0.0f)
		[
			SNew(SVerticalBox)

			// === Header band ====================================================
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
				.Padding(FMargin(16.0f, 10.0f))
				[
					SNew(SVerticalBox)

					// Title row -------------------------------------------------
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(0.0f, 0.0f, 12.0f, 0.0f)
						[
							SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.Help"))
						]
						+ SHorizontalBox::Slot()
						.FillWidth(1.0f)
						.VAlign(VAlign_Center)
						[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.AutoHeight()
							[
								SNew(STextBlock)
								.Text(LOCTEXT("DocsTitle", "Nexus API Reference"))
								.Font(FCoreStyle::GetDefaultFontStyle("Bold", 14))
							]
							+ SVerticalBox::Slot()
							.AutoHeight()
							.Padding(0.0f, 2.0f, 0.0f, 0.0f)
							[
								SAssignNew(StatsText, STextBlock)
								.Text(this, &SNexusDocsBrowser::GetStatsText)
								.ColorAndOpacity(FSlateColor::UseSubduedForeground())
							]
						]

						// Back / forward / refresh / show internal -----------
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(8.0f, 0.0f, 4.0f, 0.0f)
						[
							SNew(SButton)
							.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
							.ToolTipText(LOCTEXT("BackTip", "Back: revisit the previous class."))
							.IsEnabled(this, &SNexusDocsBrowser::CanGoBack)
							.OnClicked(this, &SNexusDocsBrowser::OnBackClicked)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("BackArrow", "◀"))
								.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
							]
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(0.0f, 0.0f, 8.0f, 0.0f)
						[
							SNew(SButton)
							.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
							.ToolTipText(LOCTEXT("ForwardTip", "Forward: replay a back-tracked step."))
							.IsEnabled(this, &SNexusDocsBrowser::CanGoForward)
							.OnClicked(this, &SNexusDocsBrowser::OnForwardClicked)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("ForwardArrow", "▶"))
								.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
							]
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(8.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(SCheckBox)
							.ToolTipText(LOCTEXT("InternalApiTip", "Include classes that have no Blueprint-callable functions or readable properties."))
							.IsChecked(this, &SNexusDocsBrowser::GetInternalToggleState)
							.OnCheckStateChanged(this, &SNexusDocsBrowser::OnInternalToggleChanged)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("ShowInternal", "Show internal API"))
								.Margin(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
							]
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(8.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(SButton)
							.Text(LOCTEXT("Refresh", "Refresh"))
							.ToolTipText(LOCTEXT("RefreshTip", "Re-scan the reflection database. Use after recompiling C++."))
							.OnClicked(this, &SNexusDocsBrowser::OnRefreshClicked)
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Center)
						.Padding(8.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(SButton)
							.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
							.ToolTipText(LOCTEXT("ExportTip", "Write the whole reference to a single Markdown file under Saved/NexusDocs and reveal it — for sharing, diffing, or committing."))
							.OnClicked(this, &SNexusDocsBrowser::OnExportMarkdownClicked)
							[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
								[ SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.Save")) ]
								+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
								[ SNew(STextBlock).Text(LOCTEXT("ExportMarkdown", "Export Markdown")) ]
							]
						]
					]

					// Type-filter pills -----------------------------------------
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 10.0f, 0.0f, 0.0f)
					[
						BuildKindFilterRow()
					]
				]
			]

			// === Tree / detail split ==========================================
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SSplitter)
				.Orientation(Orient_Horizontal)

				// --- Left: search + class tree --------------------------------
				+ SSplitter::Slot()
				.Value(0.30f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
					.Padding(0.0f)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(8.0f, 8.0f, 8.0f, 4.0f)
						[
							SAssignNew(SearchBox, SSearchBox)
							.HintText(LOCTEXT("SearchHint", "Search classes, functions, properties..."))
							.OnTextChanged(this, &SNexusDocsBrowser::OnSearchTextChanged)
						]

						// Expand / collapse / clear-filters tool row -----------
						+ SVerticalBox::Slot()
						.AutoHeight()
						.Padding(8.0f, 0.0f, 8.0f, 4.0f)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.Padding(0.0f, 0.0f, 4.0f, 0.0f)
							[
								SNew(SButton)
								.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
								.ToolTipText(LOCTEXT("ExpandAllTip", "Expand every category."))
								.OnClicked(this, &SNexusDocsBrowser::OnExpandAllClicked)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("ExpandAll", "Expand all"))
									.Font(FCoreStyle::GetDefaultFontStyle("Regular", 9))
									.ColorAndOpacity(FSlateColor::UseSubduedForeground())
								]
							]
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.Padding(0.0f, 0.0f, 4.0f, 0.0f)
							[
								SNew(SButton)
								.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
								.ToolTipText(LOCTEXT("CollapseAllTip", "Collapse every category."))
								.OnClicked(this, &SNexusDocsBrowser::OnCollapseAllClicked)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("CollapseAll", "Collapse all"))
									.Font(FCoreStyle::GetDefaultFontStyle("Regular", 9))
									.ColorAndOpacity(FSlateColor::UseSubduedForeground())
								]
							]
							+ SHorizontalBox::Slot()
							.FillWidth(1.0f)
							[
								SNullWidget::NullWidget
							]
							+ SHorizontalBox::Slot()
							.AutoWidth()
							[
								SNew(SButton)
								.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
								.ToolTipText(LOCTEXT("ClearFiltersTip", "Reset the search box and the type filter pills."))
								.OnClicked(this, &SNexusDocsBrowser::OnClearFiltersClicked)
								[
									SNew(STextBlock)
									.Text(LOCTEXT("ClearFilters", "Clear filters"))
									.Font(FCoreStyle::GetDefaultFontStyle("Regular", 9))
									.ColorAndOpacity(FSlateColor::UseSubduedForeground())
								]
							]
						]

						+ SVerticalBox::Slot()
						.FillHeight(1.0f)
						[
							SAssignNew(TreeView, STreeView<FNodePtr>)
							.TreeItemsSource(&RootNodes)
							.SelectionMode(ESelectionMode::Single)
							.OnGenerateRow(this, &SNexusDocsBrowser::OnGenerateTreeRow)
							.OnGetChildren(this, &SNexusDocsBrowser::OnGetChildren)
							.OnSelectionChanged(this, &SNexusDocsBrowser::OnSelectionChanged)
						]
					]
				]

				// --- Right: detail pane ---------------------------------------
				+ SSplitter::Slot()
				.Value(0.70f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
					.Padding(0.0f)
					[
						SAssignNew(DetailScroll, SScrollBox)
						+ SScrollBox::Slot()
						[
							BuildEmptyState()
						]
					]
				]
			]
		]
	];

	ExpandAll(RootNodes);

	// Resume where the user left off: re-select the last-viewed type if it still
	// exists in the freshly-walked collection.
	const FString LastType = NexusEditorPersistence::GetString(TEXT("DocsLastType"));
	if (!LastType.IsEmpty())
	{
		if (TSharedPtr<FNexusDocClass> Last = NexusDocs::FindByTypeName(Collection, LastType))
		{
			SelectedClass = Last;
			SelectAndExpandForClass(Last);
			RefreshDetailPane();
		}
	}

	// Drop the cursor into the search box once the widget has been laid out, so a
	// designer can start typing a class name the instant the tool opens.
	RegisterActiveTimer(0.0f, FWidgetActiveTimerDelegate::CreateSP(this, &SNexusDocsBrowser::FocusSearchBox));
}

EActiveTimerReturnType SNexusDocsBrowser::FocusSearchBox(double /*InCurrentTime*/, float /*InDeltaTime*/)
{
	if (SearchBox.IsValid())
	{
		FSlateApplication::Get().SetKeyboardFocus(SearchBox, EFocusCause::SetDirectly);
	}
	return EActiveTimerReturnType::Stop;
}

// =============================================================================
// Model + tree assembly
// =============================================================================

void SNexusDocsBrowser::RebuildModel()
{
	Collection = NexusDocs::BuildFromNexusModule();
}

void SNexusDocsBrowser::DiscoverArchDocs()
{
	ArchDocs.Reset();

	const FString DocsRoot = FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::ProjectDir(), TEXT("Docs")));
	if (!FPaths::DirectoryExists(DocsRoot))
	{
		return;
	}

	TArray<FString> Found;
	IFileManager::Get().FindFiles(Found, *(DocsRoot / TEXT("*.md")), /*Files=*/true, /*Dirs=*/false);
	Found.Sort();
	for (const FString& FileName : Found)
	{
		FArchDoc Doc;
		Doc.DisplayName = TitleFromMarkdownFile(FileName);
		Doc.AbsolutePath = FPaths::Combine(DocsRoot, FileName);
		ArchDocs.Add(MoveTemp(Doc));
	}
}

bool SNexusDocsBrowser::ClassMatchesFilters(const FNexusDocClass& Entry) const
{
	// "Internal" = exposes nothing to Blueprint and isn't a struct. Toggle hides them.
	if (!bShowInternalApi && !Entry.bIsStruct)
	{
		const bool bHasAny = Entry.Functions.Num() > 0 || Entry.Properties.Num() > 0 || Entry.Events.Num() > 0;
		if (!bHasAny)
		{
			return false;
		}
	}
	// Kind filter (All == UINT8_MAX bypasses the check).
	if (ActiveKindFilter != TNumericLimits<uint8>::Max())
	{
		if (static_cast<uint8>(Entry.Kind()) != ActiveKindFilter)
		{
			return false;
		}
	}
	if (CurrentSearch.IsEmpty())
	{
		return true;
	}
	if (TextContains(Entry.DisplayName, CurrentSearch) || TextContains(Entry.TypeName, CurrentSearch)
		|| TextContains(Entry.Tooltip, CurrentSearch))
	{
		return true;
	}
	for (const FNexusDocFunction& Func : Entry.Functions)
	{
		if (TextContains(Func.DisplayName, CurrentSearch) || TextContains(Func.FunctionName, CurrentSearch)
			|| TextContains(Func.Tooltip, CurrentSearch) || TextContains(Func.Keywords, CurrentSearch))
		{
			return true;
		}
	}
	for (const FNexusDocProperty& Prop : Entry.Properties)
	{
		if (TextContains(Prop.DisplayName, CurrentSearch) || TextContains(Prop.Tooltip, CurrentSearch))
		{
			return true;
		}
	}
	for (const FNexusDocProperty& Event : Entry.Events)
	{
		if (TextContains(Event.DisplayName, CurrentSearch) || TextContains(Event.Tooltip, CurrentSearch))
		{
			return true;
		}
	}
	return false;
}

void SNexusDocsBrowser::RebuildTree()
{
	RootNodes.Reset();

	// One FNode per category, with its filtered class leaves underneath.
	TMap<FString, FNodePtr> CategoryNodes;
	for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
	{
		if (!Entry.IsValid() || !ClassMatchesFilters(*Entry))
		{
			continue;
		}
		FNodePtr& CategoryNode = CategoryNodes.FindOrAdd(Entry->Category);
		if (!CategoryNode.IsValid())
		{
			CategoryNode = MakeShared<FNode>();
			CategoryNode->Label = Entry->Category;
		}
		FNodePtr Leaf = MakeShared<FNode>();
		Leaf->Label = Entry->DisplayName;
		Leaf->ClassEntry = Entry;
		CategoryNode->Children.Add(MoveTemp(Leaf));
	}

	// Promote pinned classes into a synthetic "Pinned" category at the top so a
	// designer's favourites are one click away regardless of the active filter.
	if (Pinned.Num() > 0)
	{
		FNodePtr PinnedRoot = MakeShared<FNode>();
		PinnedRoot->Label = TEXT("★ Pinned");
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (!Entry.IsValid() || !Pinned.Contains(Entry->TypeName))
			{
				continue;
			}
			// Pinned entries ignore the kind/internal filters but still respect search.
			if (!CurrentSearch.IsEmpty() && !ClassMatchesFilters(*Entry))
			{
				continue;
			}
			FNodePtr Leaf = MakeShared<FNode>();
			Leaf->Label = Entry->DisplayName;
			Leaf->ClassEntry = Entry;
			PinnedRoot->Children.Add(MoveTemp(Leaf));
		}
		if (PinnedRoot->Children.Num() > 0)
		{
			RootNodes.Add(MoveTemp(PinnedRoot));
		}
	}

	TArray<FString> Keys;
	CategoryNodes.GetKeys(Keys);
	Keys.Sort();
	for (const FString& Key : Keys)
	{
		RootNodes.Add(CategoryNodes[Key]);
	}

	if (TreeView.IsValid())
	{
		TreeView->RequestTreeRefresh();
		// Auto-expand everything when a search is active so matches are visible
		// without the user manually drilling in.
		if (!CurrentSearch.IsEmpty())
		{
			ExpandAll(RootNodes);
		}
	}
}

void SNexusDocsBrowser::ExpandAll(const TArray<FNodePtr>& Nodes)
{
	if (!TreeView.IsValid())
	{
		return;
	}
	for (const FNodePtr& Node : Nodes)
	{
		if (!Node.IsValid())
		{
			continue;
		}
		TreeView->SetItemExpansion(Node, true);
		if (Node->Children.Num() > 0)
		{
			ExpandAll(Node->Children);
		}
	}
}

void SNexusDocsBrowser::CollapseAll(const TArray<FNodePtr>& Nodes)
{
	if (!TreeView.IsValid())
	{
		return;
	}
	for (const FNodePtr& Node : Nodes)
	{
		if (!Node.IsValid())
		{
			continue;
		}
		TreeView->SetItemExpansion(Node, false);
		if (Node->Children.Num() > 0)
		{
			CollapseAll(Node->Children);
		}
	}
}

// =============================================================================
// Tree view callbacks
// =============================================================================

TSharedRef<ITableRow> SNexusDocsBrowser::OnGenerateTreeRow(FNodePtr Node, const TSharedRef<STableViewBase>& Owner)
{
	const bool bIsCategory = !Node->ClassEntry.IsValid();
	TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox);

	if (bIsCategory)
	{
		// Category header: one fixed folder icon for every row (consistent),
		// the label in caps, and the member count as a subdued chip on the right.
		const int32 Count = Node->Children.Num();
		Row->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 6.0f, 0.0f)
			[
				SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.FolderClosed"))
			];
		Row->AddSlot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Node->Label.ToUpper()))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			];
		Row->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(4.0f, 0.0f, 4.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(TEXT("%d"), Count)))
				.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.ToolTipText(FText::Format(LOCTEXT("CategoryCountTip", "{0} type(s) in this folder."), FText::AsNumber(Count)))
			];
	}
	else
	{
		// Leaf: consistent type chip on the left (every entry gets one — no more
		// inconsistent icons), the display name, and a small pin glyph on the
		// right if the user has favourited the class.
		const FNexusDocClass& Entry = *Node->ClassEntry;

		Row->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 8.0f, 0.0f)
			[
				BuildTypeChip(Entry.Kind(), /*bSmall=*/true)
			];
		Row->AddSlot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Entry.DisplayName))
				.ToolTipText(FText::FromString(FString::Printf(TEXT("%s\n%s"),
					*Entry.TypeName,
					Entry.Tooltip.IsEmpty() ? TEXT("No description") : *Entry.Tooltip)))
			];
		if (Entry.bIsAbstract)
		{
			Row->AddSlot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(4.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("AbstractGlyph", "abstract"))
					.Font(FCoreStyle::GetDefaultFontStyle("Italic", 7))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					.ToolTipText(LOCTEXT("AbstractTip", "Abstract — cannot be instantiated directly; use a derived class."))
				];
		}
		if (Pinned.Contains(Entry.TypeName))
		{
			Row->AddSlot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(4.0f, 0.0f, 4.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("PinnedGlyph", "★"))
					.ColorAndOpacity(FSlateColor(FStyleColors::AccentYellow))
				];
		}
	}

	return SNew(STableRow<FNodePtr>, Owner)
		.Padding(FMargin(2.0f, 3.0f))
		[
			Row
		];
}

void SNexusDocsBrowser::OnGetChildren(FNodePtr Node, TArray<FNodePtr>& OutChildren)
{
	if (Node.IsValid())
	{
		OutChildren.Append(Node->Children);
	}
}

void SNexusDocsBrowser::OnSelectionChanged(FNodePtr Node, ESelectInfo::Type SelectInfo)
{
	if (!Node.IsValid() || !Node->ClassEntry.IsValid())
	{
		return;
	}
	SelectedClass = Node->ClassEntry;
	// Direct user clicks (Mouse / OnKeyPress) record history; programmatic
	// selection paths use NavigateToType which records its own entries.
	if (SelectInfo == ESelectInfo::OnMouseClick || SelectInfo == ESelectInfo::OnKeyPress)
	{
		PushHistory(SelectedClass->TypeName);
	}
	RefreshDetailPane();
}

// =============================================================================
// Header controls
// =============================================================================

void SNexusDocsBrowser::OnSearchTextChanged(const FText& NewText)
{
	CurrentSearch = NewText.ToString();
	LastSearchKeystrokeTime = FSlateApplication::Get().GetCurrentTime();
	// Coalesce keystrokes: (re)start one idle timer rather than rebuilding the whole tree
	// on every character (the rebuild walks every type).
	if (!bSearchTimerActive)
	{
		bSearchTimerActive = true;
		RegisterActiveTimer(0.05f, FWidgetActiveTimerDelegate::CreateSP(this, &SNexusDocsBrowser::TickSearchDebounce));
	}
}

EActiveTimerReturnType SNexusDocsBrowser::TickSearchDebounce(double InCurrentTime, float /*InDeltaTime*/)
{
	if (InCurrentTime - LastSearchKeystrokeTime >= 0.2)
	{
		bSearchTimerActive = false;
		RebuildTree();
		return EActiveTimerReturnType::Stop;
	}
	return EActiveTimerReturnType::Continue;
}

FReply SNexusDocsBrowser::OnRefreshClicked()
{
	RebuildModel();
	RebuildTree();
	DiscoverArchDocs();
	// The selected class survives the rebuild only if its type is still present in
	// the new collection — re-resolve by name through the rebuilt lookup cache.
	if (SelectedClass.IsValid())
	{
		SelectedClass = NexusDocs::FindByTypeName(Collection, SelectedClass->TypeName);
	}
	RefreshDetailPane();
	return FReply::Handled();
}

FReply SNexusDocsBrowser::OnExpandAllClicked()
{
	ExpandAll(RootNodes);
	return FReply::Handled();
}

FReply SNexusDocsBrowser::OnCollapseAllClicked()
{
	CollapseAll(RootNodes);
	return FReply::Handled();
}

FReply SNexusDocsBrowser::OnClearFiltersClicked()
{
	CurrentSearch.Reset();
	ActiveKindFilter = TNumericLimits<uint8>::Max();
	if (SearchBox.IsValid())
	{
		SearchBox->SetText(FText::GetEmpty());
	}
	RebuildTree();
	return FReply::Handled();
}

void SNexusDocsBrowser::OnInternalToggleChanged(ECheckBoxState NewState)
{
	bShowInternalApi = (NewState == ECheckBoxState::Checked);
	RebuildTree();
}

ECheckBoxState SNexusDocsBrowser::GetInternalToggleState() const
{
	return bShowInternalApi ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

// =============================================================================
// Navigation history
// =============================================================================

void SNexusDocsBrowser::PushHistory(const FString& TypeName)
{
	if (TypeName.IsEmpty())
	{
		return;
	}
	// Discard the forward stack — we just took a new fork.
	if (HistoryIndex >= 0 && HistoryIndex < History.Num() - 1)
	{
		History.SetNum(HistoryIndex + 1);
	}
	// Skip a duplicate at the top of the stack (e.g. clicking the same row twice).
	if (History.Num() > 0 && History.Last() == TypeName)
	{
		HistoryIndex = History.Num() - 1;
		return;
	}
	History.Add(TypeName);
	HistoryIndex = History.Num() - 1;

	// Cap and persist (per-user) so history survives an editor restart.
	constexpr int32 MaxHistory = 50;
	if (History.Num() > MaxHistory)
	{
		History.RemoveAt(0, History.Num() - MaxHistory);
		HistoryIndex = History.Num() - 1;
	}
	NexusEditorPersistence::SetString(TEXT("DocsHistory"), FString::Join(History, TEXT(";")));
}

void SNexusDocsBrowser::NavigateToType(const FString& TypeName)
{
	TSharedPtr<FNexusDocClass> Found = NexusDocs::FindByTypeName(Collection, TypeName);
	if (!Found.IsValid())
	{
		Notify(FText::Format(LOCTEXT("TypeNotFoundFmt", "{0} is not a Nexus type."), FText::FromString(TypeName)));
		return;
	}
	SelectedClass = Found;
	PushHistory(TypeName);

	// If the target type is hidden by the active type filter, drop the filter
	// to "All" so the tree highlights the destination — chasing a Used By link
	// to a Struct shouldn't fail silently because the user is filtered to
	// Components.
	if (ActiveKindFilter != TNumericLimits<uint8>::Max()
		&& ActiveKindFilter != static_cast<uint8>(Found->Kind()))
	{
		ActiveKindFilter = TNumericLimits<uint8>::Max();
		RebuildTree();
	}

	SelectAndExpandForClass(Found);
	RefreshDetailPane();
}

FReply SNexusDocsBrowser::OnBackClicked()
{
	if (!CanGoBack())
	{
		return FReply::Handled();
	}
	--HistoryIndex;
	const FString TypeName = History[HistoryIndex];
	SelectedClass = NexusDocs::FindByTypeName(Collection, TypeName);
	SelectAndExpandForClass(SelectedClass);
	RefreshDetailPane();
	return FReply::Handled();
}

FReply SNexusDocsBrowser::OnForwardClicked()
{
	if (!CanGoForward())
	{
		return FReply::Handled();
	}
	++HistoryIndex;
	const FString TypeName = History[HistoryIndex];
	SelectedClass = NexusDocs::FindByTypeName(Collection, TypeName);
	SelectAndExpandForClass(SelectedClass);
	RefreshDetailPane();
	return FReply::Handled();
}

bool SNexusDocsBrowser::CanGoBack() const
{
	return HistoryIndex > 0;
}

bool SNexusDocsBrowser::CanGoForward() const
{
	return HistoryIndex >= 0 && HistoryIndex < History.Num() - 1;
}

void SNexusDocsBrowser::SelectAndExpandForClass(const TSharedPtr<FNexusDocClass>& Entry)
{
	if (!TreeView.IsValid() || !Entry.IsValid())
	{
		return;
	}
	for (const FNodePtr& Category : RootNodes)
	{
		if (!Category.IsValid())
		{
			continue;
		}
		for (const FNodePtr& Leaf : Category->Children)
		{
			if (Leaf.IsValid() && Leaf->ClassEntry.IsValid() && Leaf->ClassEntry->TypeName == Entry->TypeName)
			{
				TreeView->SetItemExpansion(Category, true);
				// Setting selection re-fires OnSelectionChanged; pass Direct so we
				// don't double-push to history.
				TreeView->SetSelection(Leaf, ESelectInfo::Direct);
				TreeView->RequestScrollIntoView(Leaf);
				return;
			}
		}
	}
}

// =============================================================================
// Type filter pills
// =============================================================================

bool SNexusDocsBrowser::IsKindFilterActive(uint8 Kind) const
{
	return ActiveKindFilter == Kind;
}

void SNexusDocsBrowser::SetKindFilter(uint8 Kind)
{
	ActiveKindFilter = Kind;
	RebuildTree();
	// Tapping a filter pill should surface the matches, not bury them — the
	// tree refresh resets every category to collapsed, so re-expand them so the
	// designer immediately sees what the filter let through.
	ExpandAll(RootNodes);
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildKindFilterRow()
{
	TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox);
	Row->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("FilterLabel", "Show:"))
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground())
		];

	// "All" first, then one pill per kind.
	auto AddPill = [&Row, this](const FText& Label, uint8 Kind, const FText& Tip)
	{
		Row->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 4.0f, 0.0f)
			[
				BuildKindFilterPill(Label, Kind, Tip)
			];
	};

	AddPill(LOCTEXT("KindAll", "All"),                TNumericLimits<uint8>::Max(),                        LOCTEXT("KindAllTip", "Show every Nexus type."));
	AddPill(LOCTEXT("KindComp", "Components"),        static_cast<uint8>(ENexusDocKind::Component),        LOCTEXT("KindCompTip", "Actor Components — gameplay behaviour attached to actors."));
	AddPill(LOCTEXT("KindSub", "Subsystems"),         static_cast<uint8>(ENexusDocKind::Subsystem),        LOCTEXT("KindSubTip", "Engine / GameInstance / World subsystems — global services."));
	AddPill(LOCTEXT("KindLib", "Libraries"),          static_cast<uint8>(ENexusDocKind::Library),          LOCTEXT("KindLibTip", "Blueprint Function Libraries — static helper functions."));
	AddPill(LOCTEXT("KindIface", "Interfaces"),       static_cast<uint8>(ENexusDocKind::Interface),        LOCTEXT("KindIfaceTip", "Interfaces — contracts any actor or component can implement."));
	AddPill(LOCTEXT("KindAct", "Actors"),             static_cast<uint8>(ENexusDocKind::Actor),            LOCTEXT("KindActTip", "Placeable / spawnable actors."));
	AddPill(LOCTEXT("KindClass", "Other Classes"),    static_cast<uint8>(ENexusDocKind::Class),            LOCTEXT("KindClassTip", "Plain UObject classes that aren't actors, components, subsystems, or libraries."));
	AddPill(LOCTEXT("KindStruct", "Structs"),         static_cast<uint8>(ENexusDocKind::Struct),           LOCTEXT("KindStructTip", "UScriptStruct value types — data blobs passed by value."));

	Row->AddSlot().FillWidth(1.0f)[ SNullWidget::NullWidget ];

	return Row;
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildKindFilterPill(const FText& Label, uint8 Kind, const FText& Tooltip)
{
	const FLinearColor BaseColor = (Kind == TNumericLimits<uint8>::Max())
		? FLinearColor(0.35f, 0.35f, 0.42f)
		: ColorForKind(static_cast<ENexusDocKind>(Kind));

	return SNew(SCheckBox)
		.Style(FAppStyle::Get(), "DetailsView.SectionButton")
		.ToolTipText(Tooltip)
		.IsChecked_Lambda([this, Kind]()
		{
			return IsKindFilterActive(Kind) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		})
		.OnCheckStateChanged_Lambda([this, Kind](ECheckBoxState)
		{
			SetKindFilter(Kind);
		})
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(2.0f, 2.0f, 6.0f, 2.0f)
			[
				SNew(SBox)
				.WidthOverride(8.0f)
				.HeightOverride(8.0f)
				[
					SNew(SImage)
					.Image(FAppStyle::Get().GetBrush("WhiteBrush"))
					.ColorAndOpacity(FSlateColor(BaseColor))
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 2.0f, 6.0f, 2.0f)
			[
				SNew(STextBlock)
				.Text(Label)
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
			]
		];
}

// =============================================================================
// Bookmarks
// =============================================================================

bool SNexusDocsBrowser::IsPinned(const FString& TypeName) const
{
	return Pinned.Contains(TypeName);
}

FReply SNexusDocsBrowser::OnTogglePinned(FString TypeName)
{
	if (TypeName.IsEmpty())
	{
		return FReply::Handled();
	}
	if (Pinned.Contains(TypeName))
	{
		Pinned.Remove(TypeName);
		Notify(FText::Format(LOCTEXT("UnpinnedFmt", "Unpinned {0}"), FText::FromString(TypeName)));
	}
	else
	{
		Pinned.Add(TypeName);
		Notify(FText::Format(LOCTEXT("PinnedFmt", "Pinned {0} — find it in the ★ Pinned section."), FText::FromString(TypeName)));
	}
	NexusEditorPersistence::SetString(TEXT("DocsPinned"), FString::Join(Pinned.Array(), TEXT(";")));
	RebuildTree();
	RefreshDetailPane();
	return FReply::Handled();
}

// =============================================================================
// Member filter
// =============================================================================

void SNexusDocsBrowser::OnMemberFilterChanged(const FText& NewText)
{
	MemberFilter = NewText.ToString();
	// Repopulate ONLY the member-section stack. Rebuilding the whole detail pane
	// (as this used to) re-created the filter SSearchBox on every keystroke, which
	// dropped focus and wiped the text after a single character.
	RefreshMemberSections();
}

bool SNexusDocsBrowser::MemberMatchesFilter(const FString& Name, const FString& Tooltip, const FString& Category) const
{
	if (MemberFilter.IsEmpty())
	{
		return true;
	}
	return TextContains(Name, MemberFilter)
		|| TextContains(Tooltip, MemberFilter)
		|| TextContains(Category, MemberFilter);
}

// =============================================================================
// Right pane
// =============================================================================

void SNexusDocsBrowser::RefreshDetailPane()
{
	if (!DetailScroll.IsValid())
	{
		return;
	}

	// Section anchors and the member container belong to the pane we're about to
	// discard; clear them so a stale weak ref can't be scrolled to.
	MembersContainer.Reset();
	FunctionsAnchor.Reset();
	EventsAnchor.Reset();
	PropertiesAnchor.Reset();

	// Reset the per-class member filter only when the selection actually changed,
	// so it doesn't fight a user who is mid-type, but never leaks an old filter
	// onto a different class (which left the box looking empty while it filtered).
	if (SelectedClass.IsValid() && SelectedClass->TypeName != DetailedTypeName)
	{
		MemberFilter.Reset();
		DetailedTypeName = SelectedClass->TypeName;
		// Remember the last-viewed type so the tool reopens where the user left off.
		NexusEditorPersistence::SetString(TEXT("DocsLastType"), DetailedTypeName);
	}
	else if (!SelectedClass.IsValid())
	{
		DetailedTypeName.Reset();
	}

	DetailScroll->ClearChildren();
	if (SelectedClass.IsValid())
	{
		DetailScroll->AddSlot()
		[
			BuildClassDetail(*SelectedClass)
		];
	}
	else
	{
		DetailScroll->AddSlot()
		[
			BuildEmptyState()
		];
	}
}

void SNexusDocsBrowser::RefreshMemberSections()
{
	if (MembersContainer.IsValid() && SelectedClass.IsValid())
	{
		MembersContainer->ClearChildren();
		PopulateMemberSections(MembersContainer.ToSharedRef(), *SelectedClass);
	}
}

void SNexusDocsBrowser::ScrollToAnchor(TWeakPtr<SWidget> Anchor)
{
	if (!DetailScroll.IsValid())
	{
		return;
	}
	if (TSharedPtr<SWidget> Target = Anchor.Pin())
	{
		DetailScroll->ScrollDescendantIntoView(Target, /*InAnimateScroll=*/true);
	}
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildEmptyState()
{
	// Welcome card: stats summary, top categories by count, architecture-doc
	// shortcuts, and a friendly nudge to use the search box. Doubles as a "first
	// time you open the tool" experience.
	TSharedRef<SVerticalBox> Stack = SNew(SVerticalBox);

	// Heading -----------------------------------------------------------------
	Stack->AddSlot()
		.AutoHeight()
		.Padding(FMargin(28.0f, 28.0f, 28.0f, 6.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("EmptyTitle", "Welcome to the Nexus API Reference"))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 16))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("EmptyHint", "Pick a class on the left, or use the search box above to find a function, property, or class by name. Click the coloured chip in the tree to filter by type."))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.AutoWrapText(true)
			]
		];

	// Stats panel -------------------------------------------------------------
	{
		const int32 ClassCount    = Collection.TotalClasses;
		const int32 StructCount   = Collection.TotalStructs;
		const int32 FuncCount     = Collection.TotalFunctions;
		const int32 PropCount     = Collection.TotalProperties + Collection.TotalEvents;
		const int32 DocsClasses   = Collection.DocumentedClasses;
		const int32 DocsMembers   = Collection.DocumentedMembers;
		const int32 AllClasses    = ClassCount + StructCount;
		const int32 AllMembers    = Collection.TotalMembers;
		const float ClassCoverage = AllClasses > 0 ? (100.0f * DocsClasses / AllClasses) : 0.0f;
		const float MemberCoverage= AllMembers > 0 ? (100.0f * DocsMembers / AllMembers) : 0.0f;

		Stack->AddSlot()
			.AutoHeight()
			.Padding(FMargin(28.0f, 16.0f, 28.0f, 6.0f))
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
				.Padding(FMargin(16.0f, 12.0f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						NexusEditorWidgets::SectionLabel(LOCTEXT("StatsHeader", "AT A GLANCE"))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 8.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::Format(LOCTEXT("StatsLineFmt",
							"{0} classes  ·  {1} structs  ·  {2} functions  ·  {3} properties/events"),
							FText::AsNumber(ClassCount), FText::AsNumber(StructCount),
							FText::AsNumber(FuncCount), FText::AsNumber(PropCount)))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 6.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::Format(LOCTEXT("CoverageLineFmt",
							"Documentation coverage: {0}/{1} classes ({2}%), {3}/{4} members ({5}%)."),
							FText::AsNumber(DocsClasses), FText::AsNumber(AllClasses),
							FText::AsNumber(FMath::FloorToInt(ClassCoverage)),
							FText::AsNumber(DocsMembers), FText::AsNumber(AllMembers),
							FText::AsNumber(FMath::FloorToInt(MemberCoverage))))
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					]
				]
			];
	}

	// Top categories by class count -------------------------------------------
	{
		TMap<FString, int32> CategoryCounts;
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (Entry.IsValid())
			{
				CategoryCounts.FindOrAdd(Entry->Category) += 1;
			}
		}
		TArray<TPair<FString, int32>> Sorted;
		for (const TPair<FString, int32>& Pair : CategoryCounts)
		{
			Sorted.Add(Pair);
		}
		Sorted.Sort([](const TPair<FString, int32>& A, const TPair<FString, int32>& B)
		{
			return A.Value > B.Value;
		});

		TSharedRef<SWrapBox> Wrap = SNew(SWrapBox).UseAllottedSize(true).InnerSlotPadding(FVector2D(6.0f, 6.0f));
		const int32 Show = FMath::Min<int32>(Sorted.Num(), 12);
		for (int32 Index = 0; Index < Show; ++Index)
		{
			const FString Cat = Sorted[Index].Key;
			const int32 Count = Sorted[Index].Value;
			Wrap->AddSlot()
			[
				SNew(SBorder)
				.BorderImage(GetPillBrush(FLinearColor(0.18f, 0.20f, 0.24f, 1.0f), 8.0f))
				.Padding(FMargin(10.0f, 4.0f))
				[
					SNew(STextBlock)
					.Text(FText::FromString(FString::Printf(TEXT("%s · %d"), *Cat, Count)))
					.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
					.ColorAndOpacity(FLinearColor::White)
				]
			];
		}

		Stack->AddSlot()
			.AutoHeight()
			.Padding(FMargin(28.0f, 16.0f, 28.0f, 6.0f))
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
				.Padding(FMargin(16.0f, 12.0f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						NexusEditorWidgets::SectionLabel(LOCTEXT("CategoriesHeader", "CATEGORIES BY SIZE"))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 8.0f, 0.0f, 0.0f)
					[
						Wrap
					]
				]
			];
	}

	// Architecture doc shortcuts (if any) -------------------------------------
	if (ArchDocs.Num() > 0)
	{
		Stack->AddSlot()
			.AutoHeight()
			.Padding(FMargin(28.0f, 16.0f, 28.0f, 6.0f))
			[
				BuildArchDocsRow()
			];
	}

	// Reading guide -----------------------------------------------------------
	Stack->AddSlot()
		.AutoHeight()
		.Padding(FMargin(28.0f, 16.0f, 28.0f, 28.0f))
		[
			BuildReadingGuide()
		];

	return Stack;
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildBadge(const FString& Label, const FLinearColor& Color) const
{
	return SNew(SBorder)
		.BorderImage(GetPillBrush(Color, 6.0f))
		.Padding(FMargin(8.0f, 2.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromString(Label))
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 8))
			.ColorAndOpacity(FLinearColor::White)
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildBadgeRow(const TArray<TPair<FString, FLinearColor>>& Badges) const
{
	if (Badges.Num() == 0)
	{
		return SNullWidget::NullWidget;
	}
	TSharedRef<SWrapBox> Wrap = SNew(SWrapBox).UseAllottedSize(true).InnerSlotPadding(FVector2D(4.0f, 4.0f));
	for (const TPair<FString, FLinearColor>& Badge : Badges)
	{
		Wrap->AddSlot()
		[
			BuildBadge(Badge.Key, Badge.Value)
		];
	}
	return Wrap;
}

FLinearColor SNexusDocsBrowser::ColorForKind(ENexusDocKind Kind)
{
	switch (Kind)
	{
	case ENexusDocKind::Class:     return ChipClass;
	case ENexusDocKind::Component: return ChipComponent;
	case ENexusDocKind::Subsystem: return ChipSubsystem;
	case ENexusDocKind::Library:   return ChipLibrary;
	case ENexusDocKind::Interface: return ChipInterface;
	case ENexusDocKind::Actor:     return ChipActor;
	case ENexusDocKind::Struct:    return ChipStruct;
	}
	return ChipClass;
}

const FSlateBrush* SNexusDocsBrowser::GetPillBrush(const FLinearColor& Color, float Radius) const
{
	// Cache key packs the 8-bit-quantised RGB and the radius into a single
	// uint64. 8 bits per channel is plenty for chip backgrounds (the eye can't
	// see sub-1/256 differences here) and lets us key the cache without writing
	// a hash for FLinearColor.
	const uint8 R = (uint8)FMath::Clamp(FMath::RoundToInt(Color.R * 255.0f), 0, 255);
	const uint8 G = (uint8)FMath::Clamp(FMath::RoundToInt(Color.G * 255.0f), 0, 255);
	const uint8 B = (uint8)FMath::Clamp(FMath::RoundToInt(Color.B * 255.0f), 0, 255);
	const uint8 A = (uint8)FMath::Clamp(FMath::RoundToInt(Color.A * 255.0f), 0, 255);
	const uint8 RadiusByte = (uint8)FMath::Clamp(FMath::RoundToInt(Radius), 0, 255);
	const uint64 Key = ((uint64)R << 32) | ((uint64)G << 24) | ((uint64)B << 16) | ((uint64)A << 8) | (uint64)RadiusByte;

	if (TSharedPtr<FSlateBrush>* Existing = PillBrushCache.Find(Key))
	{
		return Existing->Get();
	}

	// FSlateBrush with DrawAs = RoundedBox draws a solid rounded rectangle with
	// no texture sampling, so it's both crisp at any size and immune to the
	// "missing brush" checker pattern engine versions show when a named brush
	// like "RoundedFilledBorder" isn't registered.
	TSharedRef<FSlateBrush> NewBrush = MakeShared<FSlateBrush>();
	NewBrush->DrawAs = ESlateBrushDrawType::RoundedBox;
	NewBrush->TintColor = FSlateColor(Color);
	NewBrush->OutlineSettings.CornerRadii = FVector4(Radius, Radius, Radius, Radius);
	NewBrush->OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	NewBrush->OutlineSettings.Color = FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
	NewBrush->OutlineSettings.Width = 0.0f;
	PillBrushCache.Add(Key, NewBrush);
	return &NewBrush.Get();
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildTypeChip(ENexusDocKind Kind, bool bSmall) const
{
	const FString Label = NexusDocs::KindShortLabel(Kind);
	const FLinearColor Color = ColorForKind(Kind);
	const int32 FontSize = bSmall ? 7 : 9;
	const FMargin Padding = bSmall ? FMargin(5.0f, 1.0f) : FMargin(8.0f, 3.0f);
	const float MinWidth = bSmall ? 36.0f : 56.0f;
	const float Radius = bSmall ? 6.0f : 8.0f;

	return SNew(SBox)
		.MinDesiredWidth(MinWidth)
		.ToolTipText(FText::FromString(NexusDocs::KindLongLabel(Kind)))
		[
			SNew(SBorder)
			.BorderImage(GetPillBrush(Color, Radius))
			.Padding(Padding)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Label))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", FontSize))
				.ColorAndOpacity(FLinearColor::White)
				.Justification(ETextJustify::Center)
			]
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildTypeLink(const FString& TypeName)
{
	// A subtle hyperlink-style button. Resolves on click; falls back to an
	// uneditable label when the type isn't a Nexus type (e.g. UActorComponent).
	TSharedPtr<FNexusDocClass> Found = NexusDocs::FindByTypeName(Collection, TypeName);
	if (!Found.IsValid())
	{
		return SNew(STextBlock)
			.Text(FText::FromString(TypeName))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			.ToolTipText(LOCTEXT("ExternalTypeTip", "External type — not declared in the Nexus module."));
	}
	const FString CapturedName = TypeName;
	return SNew(SButton)
		.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
		.ContentPadding(FMargin(2.0f, 0.0f))
		.ToolTipText(FText::Format(LOCTEXT("JumpToTypeTipFmt", "Jump to {0}"), FText::FromString(TypeName)))
		.OnClicked_Lambda([this, CapturedName]()
		{
			NavigateToType(CapturedName);
			return FReply::Handled();
		})
		[
			SNew(STextBlock)
			.Text(FText::FromString(Found->DisplayName))
			.ColorAndOpacity(FSlateColor(FStyleColors::AccentBlue))
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildCopyButton(const FString& ToolTipText, FString TextToCopy)
{
	// Compact "copy this value to the clipboard" button, with a short confirmation
	// toast so the action is visibly acknowledged.
	return SNew(SButton)
		.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
		.ToolTipText(FText::FromString(ToolTipText))
		.OnClicked_Lambda([TextToCopy]()
		{
			FPlatformApplicationMisc::ClipboardCopy(*TextToCopy);
			Notify(FText::Format(LOCTEXT("CopiedFmt", "Copied: {0}"), FText::FromString(TextToCopy)));
			return FReply::Handled();
		})
		[
			SNew(STextBlock)
			.Text(LOCTEXT("CopyGlyph", "⧉"))
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground())
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildClassHeader(const FNexusDocClass& Entry)
{
	// Title row: type chip + display name + abstract glyph + pin button + copy buttons + open source.
	TSharedRef<SHorizontalBox> Title = SNew(SHorizontalBox);
	Title->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 10.0f, 0.0f)
		[
			BuildTypeChip(Entry.Kind(), /*bSmall=*/false)
		];
	Title->AddSlot()
		.FillWidth(1.0f)
		.VAlign(VAlign_Center)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(Entry.DisplayName))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 18))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 2.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Entry.TypeName))
				.Font(FCoreStyle::GetDefaultFontStyle("Mono", 10))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
		];

	if (Entry.bIsAbstract)
	{
		Title->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(8.0f, 0.0f)
			[
				BuildBadge(TEXT("ABSTRACT"), BadgeIndigo)
			];
	}

	// Pin / unpin toggle.
	const FString CapturedName = Entry.TypeName;
	const bool bIsPinnedNow = IsPinned(CapturedName);
	Title->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(4.0f, 0.0f, 0.0f, 0.0f)
		[
			SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
			.ToolTipText(bIsPinnedNow
				? LOCTEXT("UnpinTip", "Remove this class from the Pinned section.")
				: LOCTEXT("PinTip", "Pin this class — it appears in a ★ Pinned section at the top of the tree."))
			.OnClicked_Lambda([this, CapturedName]()
			{
				return OnTogglePinned(CapturedName);
			})
			[
				SNew(STextBlock)
				.Text(bIsPinnedNow ? LOCTEXT("Unpin", "★ Pinned") : LOCTEXT("Pin", "☆ Pin"))
				.ColorAndOpacity(bIsPinnedNow ? FSlateColor(FStyleColors::AccentYellow) : FSlateColor::UseForeground())
			]
		];

	// Copy class name.
	Title->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(4.0f, 0.0f, 0.0f, 0.0f)
		[
			BuildCopyButton(TEXT("Show the C++ type name in a notification you can read or copy from."), Entry.TypeName)
		];

	// Meta row: parent class link, source path, open in IDE.
	TSharedRef<SHorizontalBox> MetaRow = SNew(SHorizontalBox);
	if (!Entry.ParentTypeName.IsEmpty())
	{
		MetaRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 8.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("InheritsLabel", "Inherits:"))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			];
		MetaRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 16.0f, 0.0f)
			[
				BuildTypeLink(Entry.ParentTypeName)
			];
	}
	if (!Entry.HeaderPath.IsEmpty())
	{
		MetaRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 4.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(TEXT("Header: Nexus/%s"), *Entry.HeaderPath)))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.Font(FCoreStyle::GetDefaultFontStyle("Mono", 9))
				.ToolTipText(LOCTEXT("HeaderTip", "Source header path (relative to the Nexus runtime module)."))
			];
		MetaRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 16.0f, 0.0f)
			[
				BuildCopyButton(TEXT("Show the header path in a notification you can read or copy from."),
					FString::Printf(TEXT("Nexus/%s"), *Entry.HeaderPath))
			];
	}
	// Open-in-IDE.
	TWeakObjectPtr<UStruct> ClickedStruct = Entry.Struct;
	const FString ClickedHeader = Entry.HeaderPath;
	MetaRow->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
			.ToolTipText(LOCTEXT("OpenSourceTip", "Open this class's header file in your IDE."))
			.OnClicked_Lambda([ClickedStruct, ClickedHeader]()
			{
				if (UStruct* Resolved = ClickedStruct.Get())
				{
					if (UClass* AsClass = Cast<UClass>(Resolved))
					{
						FSourceCodeNavigation::NavigateToClass(AsClass);
					}
					else if (!ClickedHeader.IsEmpty())
					{
						const FString AbsolutePath = FPaths::ConvertRelativePathToFull(
							FPaths::Combine(FPaths::GameSourceDir(), TEXT("Nexus"), ClickedHeader));
						FSourceCodeNavigation::OpenSourceFile(AbsolutePath);
					}
				}
				return FReply::Handled();
			})
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[ SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.BrowseContent")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
				[ SNew(STextBlock).Text(LOCTEXT("OpenSource", "Open Source")) ]
			]
		];

	// Description prose.
	const FString DescText = Entry.Tooltip.IsEmpty()
		? FString(TEXT("No description provided. Add a /** doc comment */ above the class declaration to populate this section."))
		: Entry.Tooltip;
	const FSlateColor DescColor = Entry.Tooltip.IsEmpty()
		? FSlateColor::UseSubduedForeground()
		: FSlateColor::UseForeground();

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
		.Padding(FMargin(20.0f, 14.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				Title
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 10.0f, 0.0f, 0.0f)
			[
				MetaRow
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 12.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(DescText))
				.AutoWrapText(true)
				.ColorAndOpacity(DescColor)
			]
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildJumpRow(const FNexusDocClass& Entry)
{
	// At-a-glance pill row above the sections: each chip shows a member count and,
	// clicked, scrolls the detail pane to that section. Designers get both a
	// glance ("lots of properties, a few functions") and one-click navigation.
	TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox);
	Row->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0.0f, 0.0f, 8.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("OnThisPage", "Summary:"))
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground())
		];

	// Anchor is a pointer to one of the TWeakPtr<SWidget> members (set later while
	// the sections are built); the chip reads it lazily on click.
	auto AddChip = [this, &Row](const FText& Label, int32 Count, FLinearColor Color, TWeakPtr<SWidget>* Anchor)
	{
		if (Count <= 0)
		{
			return;
		}
		TSharedRef<SWidget> Pill =
			SNew(SBorder)
			.BorderImage(GetPillBrush(Color, 6.0f))
			.Padding(FMargin(8.0f, 2.0f))
			[
				SNew(STextBlock)
				.Text(FText::Format(LOCTEXT("AnchorFmt", "{0} ({1})"), Label, FText::AsNumber(Count)))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
				.ColorAndOpacity(FLinearColor::White)
			];

		Row->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 6.0f, 0.0f)
			[
				SNew(SButton)
				.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("NoBorder"))
				.ContentPadding(FMargin(0.0f))
				.ToolTipText(FText::Format(LOCTEXT("JumpToSectionFmt", "Jump to {0}"), Label))
				.OnClicked_Lambda([this, Anchor]()
				{
					ScrollToAnchor(*Anchor);
					return FReply::Handled();
				})
				[
					Pill
				]
			];
	};

	AddChip(LOCTEXT("AnchorFuncs",  "Functions"),  Entry.Functions.Num(),             BadgeBlue,   &FunctionsAnchor);
	AddChip(LOCTEXT("AnchorEvents", "Events"),     Entry.Events.Num(),                BadgeOrange, &EventsAnchor);
	AddChip(LOCTEXT("AnchorProps",  "Properties"), Entry.Properties.Num(),            BadgeGreen,  &PropertiesAnchor);
	AddChip(LOCTEXT("AnchorDerived","Derived"),    Entry.DerivedTypeNames.Num(),      BadgeIndigo, &InheritanceAnchor);
	AddChip(LOCTEXT("AnchorUsedBy", "Used By"),    Entry.ReferencedByTypeNames.Num(), BadgeGray,   &ReferencesAnchor);

	Row->AddSlot().FillWidth(1.0f)[ SNullWidget::NullWidget ];

	return Row;
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildInheritanceSection(const FNexusDocClass& Entry)
{
	if (Entry.DerivedTypeNames.Num() == 0 && Entry.ParentTypeName.IsEmpty())
	{
		return SNullWidget::NullWidget;
	}

	TSharedRef<SVerticalBox> Body = SNew(SVerticalBox);

	if (!Entry.ParentTypeName.IsEmpty())
	{
		TSharedRef<SHorizontalBox> ParentRow = SNew(SHorizontalBox);
		ParentRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 8.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("InheritsLabel2", "Inherits from:"))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			];
		ParentRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				BuildTypeLink(Entry.ParentTypeName)
			];

		Body->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 6.0f)
			[
				ParentRow
			];
	}

	if (Entry.DerivedTypeNames.Num() > 0)
	{
		TSharedRef<SWrapBox> Wrap = SNew(SWrapBox).UseAllottedSize(true).InnerSlotPadding(FVector2D(6.0f, 4.0f));
		for (const FString& Derived : Entry.DerivedTypeNames)
		{
			Wrap->AddSlot()
			[
				BuildTypeLink(Derived)
			];
		}
		Body->AddSlot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Top)
				.Padding(0.0f, 2.0f, 8.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("DerivedLabel", "Derived types:"))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					Wrap
				]
			];
	}

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(FMargin(14.0f, 10.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("InheritanceSection", "INHERITANCE"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 0.0f)
			[
				Body
			]
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildReferencesSection(const FNexusDocClass& Entry)
{
	if (Entry.ReferencedByTypeNames.Num() == 0)
	{
		return SNullWidget::NullWidget;
	}

	TSharedRef<SWrapBox> Wrap = SNew(SWrapBox).UseAllottedSize(true).InnerSlotPadding(FVector2D(6.0f, 4.0f));
	for (const FString& Caller : Entry.ReferencedByTypeNames)
	{
		Wrap->AddSlot()
		[
			BuildTypeLink(Caller)
		];
	}

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(FMargin(14.0f, 10.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("UsedBySection", "USED BY"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 4.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("UsedByHint", "Classes that hold this type as a property:"))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 2.0f, 0.0f, 0.0f)
			[
				Wrap
			]
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildMemberFilterRow()
{
	// Small "pill" sort toggle implemented as two SCheckBoxes. Two reasons not
	// to use SSegmentedControl: it varies subtly across UE versions, and a pair
	// of pill-styled checkboxes matches the type-filter row in the header band
	// so the tool reads as one product.
	auto MakeSortPill = [this](const FText& Label, const FText& Tip, EMemberSort Value)
	{
		return SNew(SCheckBox)
			.Style(FAppStyle::Get(), "DetailsView.SectionButton")
			.ToolTipText(Tip)
			.IsChecked_Lambda([this, Value]()
			{
				return MemberSort == Value ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
			})
			.OnCheckStateChanged_Lambda([this, Value](ECheckBoxState)
			{
				MemberSort = Value;
				RefreshMemberSections();
			})
			[
				SNew(STextBlock)
				.Text(Label)
				.Margin(FMargin(6.0f, 2.0f))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
			];
	};

	TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox);
	Row->AddSlot()
		.FillWidth(1.0f)
		.VAlign(VAlign_Center)
		[
			SAssignNew(MemberFilterBox, SSearchBox)
			.HintText(LOCTEXT("MemberFilterHint", "Filter members within this class..."))
			.OnTextChanged(this, &SNexusDocsBrowser::OnMemberFilterChanged)
		];
	Row->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(8.0f, 0.0f, 0.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("SortLabel", "Sort:"))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
		];
	Row->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(6.0f, 0.0f, 4.0f, 0.0f)
		[
			MakeSortPill(LOCTEXT("SortByCategory", "By Category"),
				LOCTEXT("SortByCategoryTip", "Group members by their UFUNCTION/UPROPERTY Category metadata."),
				EMemberSort::ByCategory)
		];
	Row->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			MakeSortPill(LOCTEXT("SortByName", "A → Z"),
				LOCTEXT("SortByNameTip", "Sort members alphabetically by display name."),
				EMemberSort::ByName)
		];

	return Row;
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildClassDetail(const FNexusDocClass& Entry)
{
	TSharedRef<SVerticalBox> Sections = SNew(SVerticalBox);

	// Header card.
	Sections->AddSlot()
		.AutoHeight()
		[
			BuildClassHeader(Entry)
		];

	// Summary chip row — built first, but its chips read the section anchors
	// lazily on click, by which point PopulateMemberSections has set them.
	Sections->AddSlot()
		.AutoHeight()
		.Padding(FMargin(20.0f, 14.0f, 20.0f, 8.0f))
		[
			BuildJumpRow(Entry)
		];

	// Inheritance + references rows, captured as scroll anchors for the chips.
	if (!Entry.ParentTypeName.IsEmpty() || Entry.DerivedTypeNames.Num() > 0)
	{
		TSharedRef<SWidget> Inheritance = BuildInheritanceSection(Entry);
		InheritanceAnchor = Inheritance;
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 4.0f, 20.0f, 8.0f))
			[
				Inheritance
			];
	}
	if (Entry.ReferencedByTypeNames.Num() > 0)
	{
		TSharedRef<SWidget> References = BuildReferencesSection(Entry);
		ReferencesAnchor = References;
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 4.0f, 20.0f, 8.0f))
			[
				References
			];
	}

	// Member filter / sort.
	if (Entry.Functions.Num() + Entry.Properties.Num() + Entry.Events.Num() > 0)
	{
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 8.0f, 20.0f, 8.0f))
			[
				BuildMemberFilterRow()
			];
	}

	// The Functions / Events / Properties stack lives in a container we keep, so
	// the member quick-filter and sort toggle can repopulate just this part
	// without tearing down (and unfocusing) the filter box above it.
	Sections->AddSlot()
		.AutoHeight()
		[
			SAssignNew(MembersContainer, SVerticalBox)
		];
	PopulateMemberSections(MembersContainer.ToSharedRef(), Entry);

	// --- Architecture docs (always on, helps designers discover them) -------
	if (ArchDocs.Num() > 0)
	{
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 8.0f, 20.0f, 20.0f))
			[
				BuildArchDocsRow()
			];
	}

	return Sections;
}

void SNexusDocsBrowser::PopulateMemberSections(const TSharedRef<SVerticalBox>& Into, const FNexusDocClass& Entry)
{
	// Helper: sort a copied array per the current MemberSort.
	auto SortFuncs = [this](TArray<FNexusDocFunction> Items) -> TArray<FNexusDocFunction>
	{
		if (MemberSort == EMemberSort::ByName)
		{
			Items.Sort([](const FNexusDocFunction& A, const FNexusDocFunction& B)
			{
				return A.DisplayName < B.DisplayName;
			});
		}
		return Items;
	};
	auto SortProps = [this](TArray<FNexusDocProperty> Items) -> TArray<FNexusDocProperty>
	{
		if (MemberSort == EMemberSort::ByName)
		{
			Items.Sort([](const FNexusDocProperty& A, const FNexusDocProperty& B)
			{
				return A.DisplayName < B.DisplayName;
			});
		}
		return Items;
	};

	// Adds a "Functions (3 of 5 shown)" band and returns it so the caller can
	// register it as the scroll target for the matching Summary chip.
	auto AddSection = [&Into](const FText& Title, int32 ShowingCount, int32 TotalCount) -> TSharedRef<SWidget>
	{
		const FString Header = (ShowingCount == TotalCount)
			? FString::Printf(TEXT("%s (%d)"), *Title.ToString(), TotalCount)
			: FString::Printf(TEXT("%s (%d of %d shown)"), *Title.ToString(), ShowingCount, TotalCount);
		TSharedRef<SWidget> HeaderWidget = NexusEditorWidgets::SectionHeader(FText::FromString(Header));
		Into->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 10.0f, 20.0f, 4.0f))
			[
				HeaderWidget
			];
		return HeaderWidget;
	};

	// --- Functions ----------------------------------------------------------
	if (Entry.Functions.Num() > 0)
	{
		TArray<FNexusDocFunction> Funcs = SortFuncs(Entry.Functions);
		TArray<FNexusDocFunction> ShownFuncs;
		ShownFuncs.Reserve(Funcs.Num());
		for (const FNexusDocFunction& Func : Funcs)
		{
			if (MemberMatchesFilter(Func.DisplayName, Func.Tooltip, Func.Category))
			{
				ShownFuncs.Add(Func);
			}
		}
		FunctionsAnchor = AddSection(LOCTEXT("FunctionsHeader", "Functions"), ShownFuncs.Num(), Funcs.Num());

		TSharedRef<SVerticalBox> FuncStack = SNew(SVerticalBox);
		if (ShownFuncs.Num() == 0)
		{
			FuncStack->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("NoMatchingFuncs", "No functions match the current filter."))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				];
		}
		else
		{
			for (const FNexusDocFunction& Func : ShownFuncs)
			{
				FuncStack->AddSlot()
					.AutoHeight()
					.Padding(0.0f, 4.0f)
					[
						BuildFunctionCard(Func)
					];
			}
		}
		Into->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 0.0f, 20.0f, 8.0f))
			[
				FuncStack
			];
	}

	// --- Events (BlueprintAssignable delegates) -----------------------------
	if (Entry.Events.Num() > 0)
	{
		TArray<FNexusDocProperty> Events = SortProps(Entry.Events);
		TArray<FNexusDocProperty> ShownEvents;
		ShownEvents.Reserve(Events.Num());
		for (const FNexusDocProperty& Event : Events)
		{
			if (MemberMatchesFilter(Event.DisplayName, Event.Tooltip, Event.Category))
			{
				ShownEvents.Add(Event);
			}
		}
		EventsAnchor = AddSection(LOCTEXT("EventsHeader", "Events"), ShownEvents.Num(), Events.Num());

		TSharedRef<SVerticalBox> EventStack = SNew(SVerticalBox);
		if (ShownEvents.Num() == 0)
		{
			EventStack->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("NoMatchingEvents", "No events match the current filter."))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				];
		}
		else
		{
			for (const FNexusDocProperty& Event : ShownEvents)
			{
				EventStack->AddSlot()
					.AutoHeight()
					.Padding(0.0f, 4.0f)
					[
						BuildPropertyCard(Event, /*bIsEvent=*/true)
					];
			}
		}
		Into->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 0.0f, 20.0f, 8.0f))
			[
				EventStack
			];
	}

	// --- Properties ---------------------------------------------------------
	if (Entry.Properties.Num() > 0)
	{
		TArray<FNexusDocProperty> Props = SortProps(Entry.Properties);
		TArray<FNexusDocProperty> ShownProps;
		ShownProps.Reserve(Props.Num());
		for (const FNexusDocProperty& Prop : Props)
		{
			if (MemberMatchesFilter(Prop.DisplayName, Prop.Tooltip, Prop.Category))
			{
				ShownProps.Add(Prop);
			}
		}
		PropertiesAnchor = AddSection(LOCTEXT("PropertiesHeader", "Properties"), ShownProps.Num(), Props.Num());

		TSharedRef<SVerticalBox> PropStack = SNew(SVerticalBox);
		if (ShownProps.Num() == 0)
		{
			PropStack->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("NoMatchingProps", "No properties match the current filter."))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				];
		}
		else
		{
			for (const FNexusDocProperty& Prop : ShownProps)
			{
				PropStack->AddSlot()
					.AutoHeight()
					.Padding(0.0f, 4.0f)
					[
						BuildPropertyCard(Prop, /*bIsEvent=*/false)
					];
			}
		}
		Into->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 0.0f, 20.0f, 20.0f))
			[
				PropStack
			];
	}

	// --- Empty surface fallback ---------------------------------------------
	if (Entry.Functions.Num() == 0 && Entry.Properties.Num() == 0 && Entry.Events.Num() == 0)
	{
		Into->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 8.0f, 20.0f, 20.0f))
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
				.Padding(16.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("NoMembers", "No Blueprint-exposed members. Toggle \"Show internal API\" to see the full surface."))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					.AutoWrapText(true)
				]
			];
	}
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildFunctionCard(const FNexusDocFunction& Func)
{
	TArray<TPair<FString, FLinearColor>> Badges;
	if (Func.bIsBlueprintPure)     { Badges.Emplace(TEXT("PURE"),      BadgeGreen); }
	else if (Func.bIsBlueprintEvent){ Badges.Emplace(TEXT("EVENT"),    BadgeOrange); }
	else if (Func.bIsBlueprintCallable){ Badges.Emplace(TEXT("CALLABLE"),BadgeBlue); }
	if (Func.bIsStatic)            { Badges.Emplace(TEXT("STATIC"),    BadgeGray); }
	if (Func.bIsLatent)            { Badges.Emplace(TEXT("LATENT"),    BadgeTeal); }
	if (Func.bIsNetMulticast)      { Badges.Emplace(TEXT("MULTICAST"), BadgePurple); }
	else if (Func.bIsServer)       { Badges.Emplace(TEXT("SERVER"),    BadgePurple); }
	else if (Func.bIsClient)       { Badges.Emplace(TEXT("CLIENT"),    BadgePurple); }
	if (Func.bIsReliable && (Func.bIsServer || Func.bIsClient || Func.bIsNetMulticast))
	{
		Badges.Emplace(TEXT("RELIABLE"), BadgePurple);
	}

	TSharedRef<SVerticalBox> Body = SNew(SVerticalBox);

	// Title row: pretty display name + badges + category chip + copy.
	{
		TSharedRef<SHorizontalBox> Title = SNew(SHorizontalBox);
		Title->AddSlot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Func.DisplayName))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
			];
		if (!Func.Category.IsEmpty())
		{
			Title->AddSlot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(8.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString(Func.Category))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					.Font(FCoreStyle::GetDefaultFontStyle("Italic", 9))
				];
		}
		Title->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				BuildBadgeRow(Badges)
			];
		Title->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(6.0f, 0.0f, 0.0f, 0.0f)
			[
				BuildCopyButton(TEXT("Show the function signature in a notification you can read or copy from."), Func.Signature)
			];
		Body->AddSlot()
			.AutoHeight()
			[
				Title
			];
	}

	// Signature (monospace).
	Body->AddSlot()
		.AutoHeight()
		.Padding(0.0f, 6.0f, 0.0f, 0.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(FMargin(8.0f, 4.0f))
			[
				SNew(STextBlock)
				.Text(FText::FromString(Func.Signature))
				.Font(FCoreStyle::GetDefaultFontStyle("Mono", 10))
				.AutoWrapText(true)
			]
		];

	// Description.
	const FString DescText = Func.Tooltip.IsEmpty()
		? FString(TEXT("No description provided. Add a /** doc comment */ above the UFUNCTION to populate this."))
		: Func.Tooltip;
	const FSlateColor DescColor = Func.Tooltip.IsEmpty()
		? FSlateColor::UseSubduedForeground()
		: FSlateColor::UseForeground();
	Body->AddSlot()
		.AutoHeight()
		.Padding(0.0f, 8.0f, 0.0f, 0.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(DescText))
			.AutoWrapText(true)
			.ColorAndOpacity(DescColor)
		];

	// Inputs.
	if (Func.Parameters.Num() > 0)
	{
		TSharedRef<SVerticalBox> InputList = SNew(SVerticalBox);
		InputList->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 10.0f, 0.0f, 2.0f)
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("InputsLabel", "INPUTS"))
			];
		for (const FNexusDocParam& Param : Func.Parameters)
		{
			TArray<TPair<FString, FLinearColor>> ParamBadges;
			if (Param.bIsOut)        { ParamBadges.Emplace(TEXT("OUT"),       BadgeRed); }
			if (Param.bIsReference)  { ParamBadges.Emplace(TEXT("BY REF"),    BadgeIndigo); }
			if (Param.bHasDefault)   { ParamBadges.Emplace(TEXT("OPTIONAL"),  BadgeGray); }

			TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox);
			Row->AddSlot()
				.AutoWidth()
				.VAlign(VAlign_Top)
				.Padding(0.0f, 0.0f, 12.0f, 0.0f)
				[
					SNew(SBox)
					.MinDesiredWidth(180.0f)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(Param.Name))
							.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(Param.DisplayType))
							.ColorAndOpacity(FSlateColor::UseSubduedForeground())
							.Font(FCoreStyle::GetDefaultFontStyle("Italic", 9))
						]
					]
				];
			Row->AddSlot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Top)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						BuildBadgeRow(ParamBadges)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 2.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(Param.Tooltip.IsEmpty()
							? FString(TEXT("(no description)"))
							: Param.Tooltip))
						.ColorAndOpacity(Param.Tooltip.IsEmpty()
							? FSlateColor::UseSubduedForeground()
							: FSlateColor::UseForeground())
						.AutoWrapText(true)
					]
				];
			if (Param.bHasDefault)
			{
				Row->AddSlot()
					.AutoWidth()
					.VAlign(VAlign_Top)
					.Padding(8.0f, 0.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(FString::Printf(TEXT("Default: %s"), *Param.DefaultValue)))
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						.Font(FCoreStyle::GetDefaultFontStyle("Mono", 9))
					];
			}

			InputList->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					Row
				];
		}
		Body->AddSlot()
			.AutoHeight()
			[
				InputList
			];
	}

	// Returns.
	if (!Func.ReturnValue.Name.IsEmpty())
	{
		Body->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 10.0f, 0.0f, 2.0f)
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("ReturnsLabel", "RETURNS"))
			];
		Body->AddSlot()
			.AutoHeight()
			.Padding(0.0f, 2.0f, 0.0f, 0.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Top)
				.Padding(0.0f, 0.0f, 12.0f, 0.0f)
				[
					SNew(SBox)
					.MinDesiredWidth(180.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(Func.ReturnValue.DisplayType))
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
					]
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Top)
				[
					SNew(STextBlock)
					.Text(FText::FromString(Func.ReturnValue.Tooltip.IsEmpty()
						? FString(TEXT("(no description)"))
						: Func.ReturnValue.Tooltip))
					.ColorAndOpacity(Func.ReturnValue.Tooltip.IsEmpty()
						? FSlateColor::UseSubduedForeground()
						: FSlateColor::UseForeground())
					.AutoWrapText(true)
				]
			];
	}

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(FMargin(14.0f, 10.0f))
		[
			Body
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildPropertyCard(const FNexusDocProperty& Prop, bool bIsEvent)
{
	TArray<TPair<FString, FLinearColor>> Badges;
	if (bIsEvent)
	{
		Badges.Emplace(TEXT("EVENT"), BadgeOrange);
	}
	else
	{
		if (Prop.bBlueprintWritable)     { Badges.Emplace(TEXT("READ / WRITE"), BadgeGreen); }
		else if (Prop.bBlueprintReadable){ Badges.Emplace(TEXT("READ ONLY"),    BadgeBlue); }
		if (Prop.bEditAnywhere)          { Badges.Emplace(TEXT("EDIT ANYWHERE"),BadgeGray); }
		else if (Prop.bEditDefaultsOnly) { Badges.Emplace(TEXT("DEFAULTS ONLY"),BadgeGray); }
		else if (Prop.bEditInstanceOnly) { Badges.Emplace(TEXT("INSTANCE ONLY"),BadgeGray); }
		if (Prop.bSaveGame)              { Badges.Emplace(TEXT("SAVED"),        BadgeIndigo); }
		if (Prop.bIsReplicated)          { Badges.Emplace(TEXT("REPLICATED"),   BadgePurple); }
	}

	TSharedRef<SHorizontalBox> Title = SNew(SHorizontalBox);
	Title->AddSlot()
		.FillWidth(1.0f)
		.VAlign(VAlign_Center)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(Prop.DisplayName))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(bIsEvent ? FString(TEXT("Multicast Event")) : Prop.DisplayType))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.Font(FCoreStyle::GetDefaultFontStyle("Italic", 10))
			]
		];
	if (!Prop.Category.IsEmpty())
	{
		Title->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(8.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Prop.Category))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.Font(FCoreStyle::GetDefaultFontStyle("Italic", 9))
			];
	}
	Title->AddSlot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			BuildBadgeRow(Badges)
		];

	// If the property references a Nexus type, expose a "Go to type" link so
	// designers can chase a "this returns a UNexusItemDefinition — show me that"
	// flow without backtracking to the tree.
	if (!Prop.ReferencedTypeName.IsEmpty())
	{
		TSharedPtr<FNexusDocClass> Target = NexusDocs::FindByTypeName(Collection, Prop.ReferencedTypeName);
		if (Target.IsValid())
		{
			Title->AddSlot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(8.0f, 0.0f, 0.0f, 0.0f)
				[
					BuildTypeLink(Prop.ReferencedTypeName)
				];
		}
	}

	const FString DescText = Prop.Tooltip.IsEmpty()
		? FString(TEXT("No description provided. Add a /** doc comment */ above the UPROPERTY to populate this."))
		: Prop.Tooltip;
	const FSlateColor DescColor = Prop.Tooltip.IsEmpty()
		? FSlateColor::UseSubduedForeground()
		: FSlateColor::UseForeground();

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(FMargin(14.0f, 10.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				Title
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(DescText))
				.AutoWrapText(true)
				.ColorAndOpacity(DescColor)
			]
		];
}

// =============================================================================
// Architecture-doc shortcuts + reading guide
// =============================================================================

TSharedRef<SWidget> SNexusDocsBrowser::BuildArchDocsRow()
{
	TSharedRef<SWrapBox> Wrap = SNew(SWrapBox).UseAllottedSize(true).InnerSlotPadding(FVector2D(8.0f, 8.0f));
	for (const FArchDoc& Doc : ArchDocs)
	{
		const FString CapturedPath = Doc.AbsolutePath;
		const FString CapturedName = Doc.DisplayName;
		Wrap->AddSlot()
		[
			SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
			.ToolTipText(FText::FromString(FString::Printf(TEXT("Open %s in an in-editor reader."), *Doc.DisplayName)))
			.OnClicked_Lambda([this, CapturedPath, CapturedName]()
			{
				OpenArchDocViewer(CapturedPath, CapturedName);
				return FReply::Handled();
			})
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.0f, 0.0f, 6.0f, 0.0f)
				[
					SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.Help"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(FText::FromString(Doc.DisplayName))
				]
			]
		];
	}

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(FMargin(16.0f, 12.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("ArchDocsHeader", "ARCHITECTURE DOCS"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 8.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ArchDocsBlurb", "Hand-written design notes for each system. Click one to read it inline — headings, lists, blockquotes, and code blocks render right inside the editor."))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.AutoWrapText(true)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				Wrap
			]
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildReadingGuide()
{
	auto Legend = [this](ENexusDocKind Kind, const FText& Description)
	{
		return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 10.0f, 0.0f)
			[
				BuildTypeChip(Kind, /*bSmall=*/false)
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(Description)
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			];
	};

	auto BadgeLegend = [this](const FString& Label, const FLinearColor& Color, const FText& Description)
	{
		return SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 10.0f, 0.0f)
			[
				BuildBadge(Label, Color)
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(Description)
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			];
	};

	TSharedRef<SVerticalBox> KindList = SNew(SVerticalBox);
	KindList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ Legend(ENexusDocKind::Component, LOCTEXT("LegendComp", "Actor Component — gameplay behaviour attached to an actor at runtime.")) ];
	KindList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ Legend(ENexusDocKind::Subsystem, LOCTEXT("LegendSub",  "Subsystem — engine / world / game-instance service, always available.")) ];
	KindList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ Legend(ENexusDocKind::Library,   LOCTEXT("LegendLib",  "Function Library — static helpers callable from anywhere.")) ];
	KindList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ Legend(ENexusDocKind::Interface, LOCTEXT("LegendIface","Interface — contract any actor or component can implement.")) ];
	KindList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ Legend(ENexusDocKind::Actor,     LOCTEXT("LegendAct",  "Actor — placeable / spawnable into the world.")) ];
	KindList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ Legend(ENexusDocKind::Class,     LOCTEXT("LegendCls",  "Other Class — a plain UObject, often a data asset or definition.")) ];
	KindList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ Legend(ENexusDocKind::Struct,    LOCTEXT("LegendStr",  "Struct — a value type passed by value (no UObject lifetime).")) ];

	TSharedRef<SVerticalBox> BadgeList = SNew(SVerticalBox);
	BadgeList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ BadgeLegend(TEXT("CALLABLE"),  BadgeBlue,   LOCTEXT("LegendCallable", "A function you can call from a Blueprint graph.")) ];
	BadgeList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ BadgeLegend(TEXT("PURE"),      BadgeGreen,  LOCTEXT("LegendPure",     "A pure function — no side effects, safe to read every frame.")) ];
	BadgeList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ BadgeLegend(TEXT("EVENT"),     BadgeOrange, LOCTEXT("LegendEvent",    "Either an implementable event or a delegate you can bind to in BP.")) ];
	BadgeList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ BadgeLegend(TEXT("STATIC"),    BadgeGray,   LOCTEXT("LegendStatic",   "Static — no target needed; call it directly.")) ];
	BadgeList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ BadgeLegend(TEXT("LATENT"),    BadgeTeal,   LOCTEXT("LegendLatent",   "Latent — runs across multiple frames (delays, timelines).")) ];
	BadgeList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ BadgeLegend(TEXT("SAVED"),     BadgeIndigo, LOCTEXT("LegendSaved",    "Persists through save / load.")) ];
	BadgeList->AddSlot().AutoHeight().Padding(0.0f, 3.0f)[ BadgeLegend(TEXT("REPLICATED"),BadgePurple, LOCTEXT("LegendReplicated","Replicated — value/event mirrors to networked clients.")) ];

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(FMargin(16.0f, 12.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("GuideHeader", "READING GUIDE"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 8.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("GuideBlurb",
					"Every entry in the tree on the left shows a coloured chip that tells you what kind of type it is. "
					"Inside each class detail, badges on functions and properties tell you how Blueprint sees them. "
					"Click the chip in the header or the Used By links to chase relationships."))
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 0.0f)
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("TypeChipsSection", "TYPE CHIPS"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 6.0f)
			[
				KindList
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 0.0f)
			[
				NexusEditorWidgets::SectionLabel(LOCTEXT("BadgesSection", "MEMBER BADGES"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 0.0f)
			[
				BadgeList
			]
		];
}

// =============================================================================
// In-editor markdown reader + export
// =============================================================================

void SNexusDocsBrowser::OpenArchDocViewer(const FString& AbsolutePath, const FString& DisplayName)
{
	FString Content;
	if (!FFileHelper::LoadFileToString(Content, *AbsolutePath))
	{
		Notify(FText::Format(LOCTEXT("ArchDocReadFailFmt",
			"Couldn't read {0}. Check the path under <Project>/Docs/."),
			FText::FromString(DisplayName)));
		return;
	}

	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(FText::FromString(DisplayName))
		.ClientSize(FVector2D(960.0f, 760.0f))
		.SizingRule(ESizingRule::UserSized)
		.SupportsMinimize(true)
		.SupportsMaximize(true);

	Window->SetContent(
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
		.Padding(0.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
				.Padding(FMargin(20.0f, 12.0f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(FText::FromString(DisplayName))
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 16))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 4.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(FString::Printf(TEXT("Source: %s"), *AbsolutePath)))
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						.Font(FCoreStyle::GetDefaultFontStyle("Mono", 9))
					]
				]
			]
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				.Padding(FMargin(28.0f, 20.0f))
				[
					NexusMarkdown::BuildDocument(Content)
				]
			]
		]);

	FSlateApplication::Get().AddWindow(Window);
}

FReply SNexusDocsBrowser::OnExportMarkdownClicked()
{
	const FString Markdown = NexusDocs::ExportMarkdown(Collection);

	const FString OutDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("NexusDocs"));
	IFileManager::Get().MakeDirectory(*OutDir, /*Tree=*/true);
	const FString OutPath = FPaths::Combine(OutDir, TEXT("NexusAPIReference.md"));

	if (!FFileHelper::SaveStringToFile(Markdown, *OutPath))
	{
		Notify(FText::Format(LOCTEXT("ExportFailFmt", "Couldn't write {0}."), FText::FromString(OutPath)));
		return FReply::Handled();
	}

	const FString FullPath = FPaths::ConvertRelativePathToFull(OutPath);

	// Success toast with a "Show in folder" link straight to the file.
	FNotificationInfo Info(FText::Format(
		LOCTEXT("ExportOkFmt", "Exported the API reference to {0}"), FText::FromString(FullPath)));
	Info.ExpireDuration = 8.0f;
	Info.bUseSuccessFailIcons = true;
	Info.Hyperlink = FSimpleDelegate::CreateLambda([FullPath]()
	{
		FPlatformProcess::ExploreFolder(*FullPath);
	});
	Info.HyperlinkText = LOCTEXT("RevealExport", "Show in folder");

	TSharedPtr<SNotificationItem> Item = FSlateNotificationManager::Get().AddNotification(Info);
	if (Item.IsValid())
	{
		Item->SetCompletionState(SNotificationItem::CS_Success);
	}
	return FReply::Handled();
}

// =============================================================================
// Stats text + misc
// =============================================================================

FText SNexusDocsBrowser::GetStatsText() const
{
	const int32 ClassCount = Collection.TotalClasses + Collection.TotalStructs;
	const int32 MemberCount = Collection.TotalMembers;
	const float Coverage = MemberCount > 0
		? (100.0f * Collection.DocumentedMembers / MemberCount)
		: 0.0f;
	return FText::Format(
		LOCTEXT("StatsBandFmt", "{0} types  ·  {1} functions  ·  {2} properties  ·  {3}% members documented"),
		FText::AsNumber(ClassCount),
		FText::AsNumber(Collection.TotalFunctions),
		FText::AsNumber(Collection.TotalProperties + Collection.TotalEvents),
		FText::AsNumber(FMath::FloorToInt(Coverage)));
}

#undef LOCTEXT_NAMESPACE
