#include "Tags/SNexusTagAudit.h"

#include "GameplayTagsManager.h"

#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

DEFINE_LOG_CATEGORY_STATIC(LogNexusTagAudit, Log, All);

#define LOCTEXT_NAMESPACE "NexusTagAudit"

namespace NexusTagAudit
{
	const TCHAR* ItemIdentityRoot = TEXT("Item.Identity.");
	const TCHAR* AttachmentIdentityRoot = TEXT("Attachment.Identity.");

	bool IsIdentityTag(const FString& TagString)
	{
		return TagString.StartsWith(ItemIdentityRoot) || TagString.StartsWith(AttachmentIdentityRoot);
	}
}

void SNexusTagAudit::Construct(const FArguments& InArgs)
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
				.OnClicked(this, &SNexusTagAudit::OnRefreshClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("Log", "Log orphan list"))
				.ToolTipText(LOCTEXT("LogTip", "Print the orphaned tags to the Output Log so you can clean them from the tag config."))
				.OnClicked(this, &SNexusTagAudit::OnLogClicked)
			]
			+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[ SNew(STextBlock).Text(this, &SNexusTagAudit::GetSummaryText) ]
		]

		+ SVerticalBox::Slot().AutoHeight()
		[ NexusEditorWidgets::SectionHeader(LOCTEXT("OrphansHeader", "Orphaned Identity Tags (registered, used by no asset)")) ]

		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f, 0.0f, 8.0f, 8.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(4.0f)
			[
				SAssignNew(ListView, SListView<TSharedPtr<FString>>)
				.ListItemsSource(&Orphans)
				.OnGenerateRow(this, &SNexusTagAudit::OnGenerateRow)
				.SelectionMode(ESelectionMode::Single)
			]
		]
	];
}

void SNexusTagAudit::Rebuild()
{
	// Tags actually used as an identity by some item / attachment.
	TSet<FGameplayTag> Used;
	int32 Untagged = 0;

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	for (const UNexusItemDefinition* Item : Items)
	{
		if (!Item) { continue; }
		if (Item->IdentityTag.IsValid()) { Used.Add(Item->IdentityTag); } else { ++Untagged; }
	}

	TArray<UNexusAttachmentDefinition*> Attachments;
	NexusEditorUtil::GatherAssets(Attachments);
	for (const UNexusAttachmentDefinition* Attachment : Attachments)
	{
		if (!Attachment) { continue; }
		if (Attachment->IdentityTag.IsValid()) { Used.Add(Attachment->IdentityTag); } else { ++Untagged; }
	}

	// Every registered identity-rooted tag the project knows about.
	FGameplayTagContainer All;
	UGameplayTagsManager::Get().RequestAllGameplayTags(All, /*OnlyIncludeDictionaryTags=*/ false);

	Orphans.Reset();
	for (const FGameplayTag& RegisteredTag : All)
	{
		const FString TagString = RegisteredTag.ToString();
		if (NexusTagAudit::IsIdentityTag(TagString) && !Used.Contains(RegisteredTag))
		{
			Orphans.Add(MakeShared<FString>(TagString));
		}
	}
	Orphans.Sort([](const TSharedPtr<FString>& A, const TSharedPtr<FString>& B)
	{
		return (A.IsValid() ? *A : FString()) < (B.IsValid() ? *B : FString());
	});

	SummaryText = FText::Format(
		LOCTEXT("Summary", "{0} orphaned identity tag(s).   {1} asset(s) still untagged."),
		FText::AsNumber(Orphans.Num()), FText::AsNumber(Untagged));

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SNexusTagAudit::OnGenerateRow(
	TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(STableRow<TSharedPtr<FString>>, Owner)
	[
		SNew(SBox).Padding(FMargin(6.0f, 3.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromString(Item.IsValid() ? *Item : FString()))
			.ColorAndOpacity(FSlateColor(FStyleColors::Warning))
		]
	];
}

FReply SNexusTagAudit::OnRefreshClicked()
{
	Rebuild();
	return FReply::Handled();
}

FReply SNexusTagAudit::OnLogClicked()
{
	UE_LOG(LogNexusTagAudit, Display, TEXT("--- Orphaned Nexus identity tags (%d) ---"), Orphans.Num());
	for (const TSharedPtr<FString>& Orphan : Orphans)
	{
		if (Orphan.IsValid())
		{
			UE_LOG(LogNexusTagAudit, Display, TEXT("  %s"), **Orphan);
		}
	}
	UE_LOG(LogNexusTagAudit, Display,
		TEXT("Remove these from Config/DefaultGameplayTags.ini (or via Project Settings -> GameplayTags) once you're sure nothing references them."));
	return FReply::Handled();
}

FText SNexusTagAudit::GetSummaryText() const
{
	return SummaryText;
}

#undef LOCTEXT_NAMESPACE
