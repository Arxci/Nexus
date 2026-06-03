#include "Docs/SNexusDocsBrowser.h"

#include "Shared/NexusEditorWidgets.h"

#include "Framework/Application/SlateApplication.h"
#include "SourceCodeNavigation.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateColor.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SWrapBox.h"
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

	bool TextContains(const FString& Haystack, const FString& Needle)
	{
		return !Needle.IsEmpty() && Haystack.Contains(Needle, ESearchCase::IgnoreCase);
	}
}

// =============================================================================
// Construction
// =============================================================================

void SNexusDocsBrowser::Construct(const FArguments& InArgs)
{
	RebuildModel();
	RebuildTree();

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
							SNew(STextBlock)
							.Text(LOCTEXT("DocsTagline", "Browse every Nexus component, subsystem, library, and struct exposed to Blueprint."))
							.ColorAndOpacity(FSlateColor::UseSubduedForeground())
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
				.Value(0.28f)
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
				.Value(0.72f)
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
}

// =============================================================================
// Model + tree assembly
// =============================================================================

void SNexusDocsBrowser::RebuildModel()
{
	Collection = NexusDocs::BuildFromNexusModule();
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

// =============================================================================
// Tree view callbacks
// =============================================================================

TSharedRef<ITableRow> SNexusDocsBrowser::OnGenerateTreeRow(FNodePtr Node, const TSharedRef<STableViewBase>& Owner)
{
	const bool bIsCategory = !Node->ClassEntry.IsValid();
	TSharedRef<SHorizontalBox> Row = SNew(SHorizontalBox);

	if (bIsCategory)
	{
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
	}
	else
	{
		const FNexusDocClass& Entry = *Node->ClassEntry;
		FName IconName = TEXT("Icons.Box");
		if (Entry.bIsStruct)              { IconName = TEXT("Icons.Adjust"); }
		else if (Entry.bIsComponent)      { IconName = TEXT("Icons.Box"); }
		else if (Entry.bIsSubsystem)      { IconName = TEXT("Icons.Server"); }
		else if (Entry.bIsFunctionLibrary){ IconName = TEXT("Icons.Filter"); }
		else if (Entry.bIsInterface)      { IconName = TEXT("Icons.Link"); }
		else if (Entry.bIsActor)          { IconName = TEXT("Icons.Layout"); }

		Row->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 6.0f, 0.0f)
			[
				SNew(SBox)
				.WidthOverride(16.0f)
				.HeightOverride(16.0f)
				[
					SNew(SImage).Image(FAppStyle::Get().GetBrush(IconName))
				]
			];
		Row->AddSlot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Entry.DisplayName))
				.ToolTipText(FText::FromString(Entry.TypeName))
			];
	}

	return SNew(STableRow<FNodePtr>, Owner)
		.Padding(FMargin(2.0f))
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

void SNexusDocsBrowser::OnSelectionChanged(FNodePtr Node, ESelectInfo::Type)
{
	if (Node.IsValid() && Node->ClassEntry.IsValid())
	{
		SelectedClass = Node->ClassEntry;
		RefreshDetailPane();
	}
}

// =============================================================================
// Header controls
// =============================================================================

void SNexusDocsBrowser::OnSearchTextChanged(const FText& NewText)
{
	CurrentSearch = NewText.ToString();
	RebuildTree();
}

FReply SNexusDocsBrowser::OnRefreshClicked()
{
	RebuildModel();
	RebuildTree();
	// The selected class survives the rebuild only if its UStruct* is still alive
	// in the new collection — re-resolve by type name.
	if (SelectedClass.IsValid())
	{
		const FString PreviousName = SelectedClass->TypeName;
		SelectedClass.Reset();
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (Entry.IsValid() && Entry->TypeName == PreviousName)
			{
				SelectedClass = Entry;
				break;
			}
		}
	}
	RefreshDetailPane();
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
// Right pane
// =============================================================================

void SNexusDocsBrowser::RefreshDetailPane()
{
	if (!DetailScroll.IsValid())
	{
		return;
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

TSharedRef<SWidget> SNexusDocsBrowser::BuildEmptyState() const
{
	return SNew(SBox)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(40.0f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("EmptyTitle", "Pick a class on the left to see its API"))
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Center)
			.Padding(0.0f, 6.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("EmptyHint", "Use the search box to find a function or property by name."))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
		];
}

TSharedRef<SWidget> SNexusDocsBrowser::BuildBadge(const FString& Label, const FLinearColor& Color) const
{
	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("RoundedFilledBorder"))
		.BorderBackgroundColor(FSlateColor(Color))
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

TSharedRef<SWidget> SNexusDocsBrowser::BuildClassDetail(const FNexusDocClass& Entry)
{
	TArray<TPair<FString, FLinearColor>> Badges;
	if (Entry.bIsStruct)            { Badges.Emplace(TEXT("STRUCT"),           BadgeGray); }
	else if (Entry.bIsInterface)    { Badges.Emplace(TEXT("INTERFACE"),        BadgeGray); }
	else if (Entry.bIsComponent)    { Badges.Emplace(TEXT("COMPONENT"),        BadgeBlue); }
	else if (Entry.bIsSubsystem)    { Badges.Emplace(TEXT("SUBSYSTEM"),        BadgePurple); }
	else if (Entry.bIsFunctionLibrary){Badges.Emplace(TEXT("FUNCTION LIBRARY"),BadgeTeal); }
	else if (Entry.bIsActor)        { Badges.Emplace(TEXT("ACTOR"),            BadgeOrange); }
	else                            { Badges.Emplace(TEXT("CLASS"),            BadgeGray); }
	if (Entry.bIsAbstract)          { Badges.Emplace(TEXT("ABSTRACT"),         BadgeIndigo); }

	TSharedRef<SVerticalBox> Sections = SNew(SVerticalBox);

	// --- Header: title, badges, parent / source path, description --------
	Sections->AddSlot()
		.AutoHeight()
		.Padding(FMargin(20.0f, 20.0f, 20.0f, 4.0f))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString(Entry.DisplayName))
					.Font(FCoreStyle::GetDefaultFontStyle("Bold", 18))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					BuildBadgeRow(Badges)
				]
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

	// Meta row: parent class, source file, open-in-IDE button.
	TSharedRef<SHorizontalBox> MetaRow = SNew(SHorizontalBox);
	if (!Entry.ParentTypeName.IsEmpty())
	{
		MetaRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 16.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(TEXT("Inherits: %s"), *Entry.ParentTypeName)))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			];
	}
	if (!Entry.HeaderPath.IsEmpty())
	{
		MetaRow->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 16.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(FString::Printf(TEXT("Header: Nexus/%s"), *Entry.HeaderPath)))
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.Font(FCoreStyle::GetDefaultFontStyle("Mono", 9))
			];
	}
	// Capture the bits OpenInIDE needs by value — Entry is a local reference
	// that dies when this function returns, so capturing it would dangle once
	// the user clicks. TWeakObjectPtr handles GC of the underlying UStruct.
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
	Sections->AddSlot()
		.AutoHeight()
		.Padding(FMargin(20.0f, 8.0f, 20.0f, 0.0f))
		[
			MetaRow
		];

	// Description prose.
	{
		const FString DescText = Entry.Tooltip.IsEmpty()
			? FString(TEXT("No description provided. Add a /** doc comment */ above the class declaration to populate this section."))
			: Entry.Tooltip;
		const FSlateColor DescColor = Entry.Tooltip.IsEmpty()
			? FSlateColor::UseSubduedForeground()
			: FSlateColor::UseForeground();
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 12.0f, 20.0f, 16.0f))
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
				.Padding(FMargin(12.0f, 10.0f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						NexusEditorWidgets::SectionLabel(LOCTEXT("DescriptionLabel", "DESCRIPTION"))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 4.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(DescText))
						.AutoWrapText(true)
						.ColorAndOpacity(DescColor)
					]
				]
			];
	}

	auto AddSection = [&Sections](const FText& Title, int32 Count)
	{
		const FString Header = FString::Printf(TEXT("%s (%d)"), *Title.ToString(), Count);
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 8.0f, 20.0f, 4.0f))
			[
				NexusEditorWidgets::SectionHeader(FText::FromString(Header))
			];
	};

	// --- Functions ------------------------------------------------------
	if (Entry.Functions.Num() > 0)
	{
		AddSection(LOCTEXT("FunctionsHeader", "Functions"), Entry.Functions.Num());
		TSharedRef<SVerticalBox> FuncStack = SNew(SVerticalBox);
		for (const FNexusDocFunction& Func : Entry.Functions)
		{
			FuncStack->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					BuildFunctionCard(Func)
				];
		}
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 0.0f, 20.0f, 8.0f))
			[
				FuncStack
			];
	}

	// --- Events (BlueprintAssignable delegates) -------------------------
	if (Entry.Events.Num() > 0)
	{
		AddSection(LOCTEXT("EventsHeader", "Events"), Entry.Events.Num());
		TSharedRef<SVerticalBox> EventStack = SNew(SVerticalBox);
		for (const FNexusDocProperty& Event : Entry.Events)
		{
			EventStack->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					BuildPropertyCard(Event, /*bIsEvent=*/true)
				];
		}
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 0.0f, 20.0f, 8.0f))
			[
				EventStack
			];
	}

	// --- Properties -----------------------------------------------------
	if (Entry.Properties.Num() > 0)
	{
		AddSection(LOCTEXT("PropertiesHeader", "Properties"), Entry.Properties.Num());
		TSharedRef<SVerticalBox> PropStack = SNew(SVerticalBox);
		for (const FNexusDocProperty& Prop : Entry.Properties)
		{
			PropStack->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f)
				[
					BuildPropertyCard(Prop, /*bIsEvent=*/false)
				];
		}
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 0.0f, 20.0f, 20.0f))
			[
				PropStack
			];
	}

	// --- Empty surface fallback -----------------------------------------
	if (Entry.Functions.Num() == 0 && Entry.Properties.Num() == 0 && Entry.Events.Num() == 0)
	{
		Sections->AddSlot()
			.AutoHeight()
			.Padding(FMargin(20.0f, 0.0f, 20.0f, 20.0f))
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

	return Sections;
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

	// Title row: pretty display name + badges + category chip.
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
		? FString(TEXT("No description provided."))
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

	const FString DescText = Prop.Tooltip.IsEmpty()
		? FString(TEXT("No description provided."))
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

#undef LOCTEXT_NAMESPACE
