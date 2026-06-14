#include "Insights/SNexusContentInsights.h"

#include "NexusEditorModule.h"
#include "Audit/NexusContentAudit.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorStyle.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/STextBlock.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Levels/NexusLevelManifest.h"

#define LOCTEXT_NAMESPACE "NexusContentInsights"

namespace
{
	/** A clickable asset-name cell that selects the asset for the Inspector. */
	TSharedRef<SWidget> NameButton(UObject* Asset, const FString& Label, const FSlateColor& Color)
	{
		TWeakObjectPtr<UObject> Weak = Asset;
		return SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
			.ContentPadding(FMargin(4.0f, 1.0f))
			.HAlign(HAlign_Left)
			.OnClicked_Lambda([Weak]()
			{
				if (UObject* Obj = Weak.Get())
				{
					FNexusEditorModule::SetSelection(Obj, FName(TEXT("NexusContentInsights")));
				}
				return FReply::Handled();
			})
			[
				SNew(STextBlock).Text(FText::FromString(Label)).ColorAndOpacity(Color)
				.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
			];
	}

	TSharedRef<SVerticalBox> ReportList()
	{
		return SNew(SVerticalBox);
	}
}

void SNexusContentInsights::Construct(const FArguments& InArgs)
{
	const auto ModeButton = [this](EMode ButtonMode, const FText& Label) -> TSharedRef<SWidget>
	{
		return SNew(SCheckBox)
			.Style(FAppStyle::Get(), "DetailsView.SectionButton")
			.Padding(FMargin(12.0f, 3.0f))
			.IsChecked_Lambda([this, ButtonMode]() { return Mode == ButtonMode ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
			.OnCheckStateChanged_Lambda([this, ButtonMode](ECheckBoxState S) { if (S == ECheckBoxState::Checked) { SetMode(ButtonMode); } })
			[ SNew(STextBlock).Text(Label) ];
	};

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		[
			NexusEditorWidgets::Toolbar(
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ ModeButton(EMode::Reachability, LOCTEXT("Reach", "Reachability")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ ModeButton(EMode::Scarcity, LOCTEXT("Scar", "Scarcity")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ ModeButton(EMode::Localization, LOCTEXT("Loc", "Localization")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ ModeButton(EMode::WhereUsed, LOCTEXT("Where", "Where-Used")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ ModeButton(EMode::Builds, LOCTEXT("Builds", "Builds")) ]
				+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
				[ SNew(STextBlock).Text_Lambda([this]() { return SummaryText; }).ColorAndOpacity(FSlateColor::UseSubduedForeground()) ]
			)
		]
		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(6.0f)
			[ SAssignNew(ContentHost, SBox) ]
		]
	];

	Refresh();

	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start(
		{ UNexusItemDefinition::StaticClass(), UNexusAttachmentDefinition::StaticClass(),
		  UNexusCombinationRecipe::StaticClass(), UNexusLevelManifest::StaticClass() },
		[this]() { Refresh(); });
}

void SNexusContentInsights::SetMode(EMode NewMode)
{
	Mode = NewMode;
	Refresh();
}

void SNexusContentInsights::Refresh()
{
	if (ContentHost.IsValid())
	{
		ContentHost->SetContent(BuildPanel());
	}
}

TSharedRef<SWidget> SNexusContentInsights::BuildPanel()
{
	switch (Mode)
	{
	case EMode::Scarcity:     return BuildScarcity();
	case EMode::Localization: return BuildLocalization();
	case EMode::WhereUsed:    return BuildWhereUsed();
	case EMode::Builds:       return BuildBuilds();
	default:                  return BuildReachability();
	}
}

TSharedRef<SWidget> SNexusContentInsights::BuildReachability()
{
	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	TArray<UNexusLevelManifest*> Manifests;
	NexusEditorUtil::GatherAssets(Manifests);
	TArray<UNexusCombinationRecipe*> Recipes;
	NexusEditorUtil::GatherAssets(Recipes);

	// Seed reachable with everything any manifest places.
	TSet<const UNexusItemDefinition*> Reachable;
	for (const UNexusLevelManifest* Manifest : Manifests)
	{
		if (!Manifest) { continue; }
		for (const TSoftObjectPtr<UNexusItemDefinition>& Soft : Manifest->Items)
		{
			if (UNexusItemDefinition* Item = Soft.LoadSynchronous())
			{
				Reachable.Add(Item);
			}
		}
	}

	// Fixpoint: add any recipe output whose every input is already reachable.
	bool bGrew = true;
	while (bGrew)
	{
		bGrew = false;
		for (const UNexusCombinationRecipe* Recipe : Recipes)
		{
			if (!Recipe || !Recipe->Output || Reachable.Contains(Recipe->Output))
			{
				continue;
			}
			bool bAllInputs = true;
			for (const FNexusRecipeInput& In : Recipe->Inputs)
			{
				if (!In.Definition || !Reachable.Contains(In.Definition))
				{
					bAllInputs = false;
					break;
				}
			}
			if (bAllInputs)
			{
				Reachable.Add(Recipe->Output);
				bGrew = true;
			}
		}
	}

	TSharedRef<SVerticalBox> List = ReportList();
	int32 Unreachable = 0;
	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item || Reachable.Contains(Item))
		{
			continue;
		}
		++Unreachable;
		List->AddSlot().AutoHeight().Padding(2.0f)
		[
			NameButton(Item, FString::Printf(TEXT("⚠ %s"), *NexusEditorUtil::DisplayLabel(Item, Item->DisplayName)),
				NexusEditorStyle::Warning())
		];
	}
	if (Unreachable == 0)
	{
		List->AddSlot().AutoHeight().Padding(6.0f)[ NexusEditorWidgets::EmptyState(
			LOCTEXT("AllReachable", "Every item is reachable — in a manifest or craftable from reachable inputs.")) ];
	}

	SummaryText = FText::Format(LOCTEXT("ReachFmt", "{0} of {1} item(s) unreachable (not placed, not craftable)."),
		FText::AsNumber(Unreachable), FText::AsNumber(Items.Num()));

	return SNew(SScrollBox) + SScrollBox::Slot()[ List ];
}

TSharedRef<SWidget> SNexusContentInsights::BuildScarcity()
{
	TArray<UNexusLevelManifest*> Manifests;
	NexusEditorUtil::GatherAssets(Manifests);

	// Supply census: count manifest placements per item category.
	TMap<FString, int32> Placements;
	TMap<FString, TSet<const UNexusItemDefinition*>> Distinct;
	int32 Total = 0;
	for (const UNexusLevelManifest* Manifest : Manifests)
	{
		if (!Manifest) { continue; }
		for (const TSoftObjectPtr<UNexusItemDefinition>& Soft : Manifest->Items)
		{
			UNexusItemDefinition* Item = Soft.LoadSynchronous();
			if (!Item) { continue; }
			FString Category = TEXT("(uncategorised)");
			for (const FGameplayTag& CatTag : Item->CategoryTags)
			{
				Category = NexusEditorStyle::StyleTagLeaf(CatTag.ToString());
				break;
			}
			Placements.FindOrAdd(Category)++;
			Distinct.FindOrAdd(Category).Add(Item);
			++Total;
		}
	}

	TArray<FString> Categories;
	Placements.GetKeys(Categories);
	Categories.Sort();

	TSharedRef<SVerticalBox> List = ReportList();
	for (const FString& Category : Categories)
	{
		List->AddSlot().AutoHeight().Padding(2.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(0.5f)[ NexusEditorWidgets::Cell(Category) ]
			+ SHorizontalBox::Slot().FillWidth(0.25f)[ NexusEditorWidgets::Cell(FString::Printf(TEXT("%d placed"), Placements[Category])) ]
			+ SHorizontalBox::Slot().FillWidth(0.25f)[ NexusEditorWidgets::Cell(FString::Printf(TEXT("%d distinct"), Distinct[Category].Num())) ]
		];
	}
	if (Categories.Num() == 0)
	{
		List->AddSlot().AutoHeight().Padding(6.0f)[ NexusEditorWidgets::EmptyState(
			LOCTEXT("NoPlacements", "No manifests place any items yet.")) ];
	}

	SummaryText = FText::Format(LOCTEXT("ScarFmt", "{0} placement(s) across {1} manifest(s) — supply by category."),
		FText::AsNumber(Total), FText::AsNumber(Manifests.Num()));

	return SNew(SScrollBox) + SScrollBox::Slot()[ List ];
}

TSharedRef<SWidget> SNexusContentInsights::BuildLocalization()
{
	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Attachments);

	TSharedRef<SVerticalBox> List = ReportList();
	int32 Missing = 0;

	auto Report = [&](UObject* Asset, const FText& DisplayName, const FText& Description, const TCHAR* Kind)
	{
		const bool bNoName = DisplayName.IsEmptyOrWhitespace();
		const bool bNoDesc = Description.IsEmptyOrWhitespace();
		if (!bNoName && !bNoDesc) { return; }
		++Missing;
		TArray<FString> Parts;
		if (bNoName) { Parts.Add(TEXT("DisplayName")); }
		if (bNoDesc) { Parts.Add(TEXT("Description")); }
		List->AddSlot().AutoHeight().Padding(2.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(0.55f)[ NameButton(Asset, Asset->GetName(), NexusEditorStyle::Neutral()) ]
			+ SHorizontalBox::Slot().FillWidth(0.15f)[ NexusEditorWidgets::Cell(Kind) ]
			+ SHorizontalBox::Slot().FillWidth(0.30f)[ NexusEditorWidgets::Cell(FString::Printf(TEXT("missing %s"), *FString::Join(Parts, TEXT(" + "))), NexusEditorStyle::Warning()) ]
		];
	};

	for (UNexusItemDefinition* Item : Items) { if (Item) { Report(Item, Item->DisplayName, Item->Description, TEXT("Item")); } }
	for (UNexusAttachmentDefinition* Att : Attachments) { if (Att) { Report(Att, Att->DisplayName, Att->Description, TEXT("Attachment")); } }

	if (Missing == 0)
	{
		List->AddSlot().AutoHeight().Padding(6.0f)[ NexusEditorWidgets::EmptyState(
			LOCTEXT("AllLoc", "Every item and attachment has a DisplayName and Description.")) ];
	}

	SummaryText = FText::Format(LOCTEXT("LocFmt", "{0} asset(s) missing localization text."), FText::AsNumber(Missing));
	return SNew(SScrollBox) + SScrollBox::Slot()[ List ];
}

TSharedRef<SWidget> SNexusContentInsights::BuildWhereUsed()
{
	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	TArray<UNexusLevelManifest*> Manifests;
	NexusEditorUtil::GatherAssets(Manifests);

	// item -> manifests that place it.
	TMap<const UNexusItemDefinition*, TArray<FString>> UsedIn;
	for (const UNexusLevelManifest* Manifest : Manifests)
	{
		if (!Manifest) { continue; }
		for (const TSoftObjectPtr<UNexusItemDefinition>& Soft : Manifest->Items)
		{
			if (UNexusItemDefinition* Item = Soft.LoadSynchronous())
			{
				UsedIn.FindOrAdd(Item).Add(Manifest->GetName());
			}
		}
	}

	TSharedRef<SVerticalBox> List = ReportList();
	int32 Orphans = 0;
	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item) { continue; }
		const TArray<FString>* Where = UsedIn.Find(Item);
		const int32 Count = Where ? Where->Num() : 0;
		if (Count == 0) { ++Orphans; }
		List->AddSlot().AutoHeight().Padding(2.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(0.6f)[ NameButton(Item, NexusEditorUtil::DisplayLabel(Item, Item->DisplayName),
				Count == 0 ? NexusEditorStyle::Warning() : NexusEditorStyle::Neutral()) ]
			+ SHorizontalBox::Slot().FillWidth(0.4f)
			[
				NexusEditorWidgets::Cell(
					Count == 0 ? FString(TEXT("not placed in any manifest")) : FString::Printf(TEXT("%d manifest(s)"), Count),
					Count == 0 ? NexusEditorStyle::Warning() : FSlateColor::UseForeground(),
					Where ? FString::Join(*Where, TEXT("\n")) : FString())
			]
		];
	}

	SummaryText = FText::Format(LOCTEXT("WhereFmt", "{0} of {1} item(s) appear in no manifest."),
		FText::AsNumber(Orphans), FText::AsNumber(Items.Num()));
	return SNew(SScrollBox) + SScrollBox::Slot()[ List ];
}

TSharedRef<SWidget> SNexusContentInsights::BuildBuilds()
{
	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Attachments);
	const FGameplayTagContainer GlobalProvided = FNexusContentAudit::GatherGlobalProvidedTags();

	TSharedRef<SVerticalBox> List = ReportList();
	int32 Uninstallable = 0;
	for (UNexusAttachmentDefinition* Att : Attachments)
	{
		if (!Att) { continue; }
		const FGameplayTagContainer Unsatisfied = FNexusContentAudit::GetUnsatisfiedRequirements(Att, GlobalProvided);
		const bool bBad = !Unsatisfied.IsEmpty();
		if (bBad) { ++Uninstallable; }
		List->AddSlot().AutoHeight().Padding(2.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(0.5f)[ NameButton(Att, Att->GetName(), bBad ? NexusEditorStyle::Error() : NexusEditorStyle::Neutral()) ]
			+ SHorizontalBox::Slot().FillWidth(0.5f)
			[
				NexusEditorWidgets::Cell(
					bBad ? FString::Printf(TEXT("can't install — needs %s"), *Unsatisfied.ToStringSimple()) : FString(TEXT("installable")),
					bBad ? NexusEditorStyle::Error() : NexusEditorStyle::Valid())
			]
		];
	}
	if (Attachments.Num() == 0)
	{
		List->AddSlot().AutoHeight().Padding(6.0f)[ NexusEditorWidgets::EmptyState(LOCTEXT("NoAtt", "No attachments found.")) ];
	}

	SummaryText = FText::Format(LOCTEXT("BuildsFmt", "{0} of {1} attachment(s) can never be installed."),
		FText::AsNumber(Uninstallable), FText::AsNumber(Attachments.Num()));
	return SNew(SScrollBox) + SScrollBox::Slot()[ List ];
}

#undef LOCTEXT_NAMESPACE
