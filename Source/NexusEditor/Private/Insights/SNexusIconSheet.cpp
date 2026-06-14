#include "Insights/SNexusIconSheet.h"

#include "NexusEditorModule.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorStyle.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SWrapBox.h"
#include "Widgets/Text/STextBlock.h"

#include "Nexus/Inventory/NexusItemDefinition.h"

#define LOCTEXT_NAMESPACE "NexusIconSheet"

void SNexusIconSheet::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot().AutoHeight()
		[
			NexusEditorWidgets::Toolbar(
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[
					SNew(SButton).Text(LOCTEXT("Refresh", "Refresh")).OnClicked(this, &SNexusIconSheet::OnRefreshClicked)
				]
				+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
				[ SNew(STextBlock).Text(this, &SNexusIconSheet::GetSummaryText) ]
			)
		]

		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(6.0f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SAssignNew(Wrap, SWrapBox)
					.UseAllottedSize(true)
					.InnerSlotPadding(FVector2D(8.0f, 8.0f))
				]
			]
		]
	];

	Rebuild();

	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start({ UNexusItemDefinition::StaticClass() }, [this]() { Rebuild(); });
}

void SNexusIconSheet::Rebuild()
{
	if (!Wrap.IsValid())
	{
		return;
	}
	Wrap->ClearChildren();
	KeepAliveBrushes.Reset();

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	Items.Sort([](const UNexusItemDefinition& A, const UNexusItemDefinition& B)
	{
		return A.GetName() < B.GetName();
	});

	int32 Missing = 0;
	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item)
		{
			continue;
		}

		// Category-colour frame.
		FLinearColor Frame(0.45f, 0.48f, 0.55f);
		for (const FGameplayTag& CatTag : Item->CategoryTags)
		{
			Frame = NexusEditorStyle::CategoryColorForTag(CatTag.ToString());
			break;
		}

		TSharedPtr<FSlateBrush> Icon = NexusEditorWidgets::IconBrush(Item->Icon.LoadSynchronous());
		if (Icon.IsValid())
		{
			KeepAliveBrushes.Add(Icon);
		}
		else
		{
			++Missing;
		}

		const FString Name = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);
		const FString Footprint = FString::Printf(TEXT("%dx%d"),
			FMath::Max(1, Item->GridSize.X), FMath::Max(1, Item->GridSize.Y));
		UNexusItemDefinition* Captured = Item;

		Wrap->AddSlot()
		[
			SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
			.ContentPadding(FMargin(2.0f))
			.ToolTipText(FText::FromString(Name))
			.OnClicked_Lambda([Captured]()
			{
				FNexusEditorModule::SetSelection(Captured, FName(TEXT("NexusIconSheet")));
				return FReply::Handled();
			})
			[
				SNew(SBox).WidthOverride(92.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
					[
						SNew(SBox).WidthOverride(80.0f).HeightOverride(80.0f)
						[
							SNew(SBorder)
							.BorderImage(FAppStyle::Get().GetBrush("Border"))
							.BorderBackgroundColor(FSlateColor(Frame))
							.Padding(2.0f)
							[
								Icon.IsValid()
									? StaticCastSharedRef<SWidget>(SNew(SImage).Image(Icon.Get()))
									: StaticCastSharedRef<SWidget>(SNew(STextBlock)
										.Text(LOCTEXT("NoIcon", "no icon"))
										.ColorAndOpacity(NexusEditorStyle::Warning())
										.Justification(ETextJustify::Center))
							]
						]
					]
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center).Padding(0.0f, 2.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(Name))
						.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
						.Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
					]
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Center)
					[
						SNew(STextBlock)
						.Text(FText::FromString(Footprint))
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						.Font(FCoreStyle::GetDefaultFontStyle("Regular", 7))
					]
				]
			]
		];
	}

	SummaryText = (Missing > 0)
		? FText::Format(LOCTEXT("SummaryMissing", "{0} item(s)  ·  {1} missing an icon."),
			FText::AsNumber(Items.Num()), FText::AsNumber(Missing))
		: FText::Format(LOCTEXT("Summary", "{0} item(s)  ·  all have icons."), FText::AsNumber(Items.Num()));
}

FReply SNexusIconSheet::OnRefreshClicked()
{
	Rebuild();
	return FReply::Handled();
}

FText SNexusIconSheet::GetSummaryText() const
{
	return SummaryText;
}

#undef LOCTEXT_NAMESPACE
