#include "Tags/SNexusTagAudit.h"

#include "GameplayTagsEditorModule.h"
#include "GameplayTagsManager.h"
#include "Misc/MessageDialog.h"

#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

#include "Shared/NexusEditorAssetWatcher.h"
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
				.Text(LOCTEXT("RemoveSelected", "Remove Selected"))
				.ToolTipText(LOCTEXT("RemoveSelTip", "Delete the selected orphan tags from the project's tag config."))
				.OnClicked(this, &SNexusTagAudit::OnRemoveSelectedClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("RemoveAll", "Remove All"))
				.ToolTipText(LOCTEXT("RemoveAllTip", "Delete every listed orphan tag from the project's tag config (asks first)."))
				.OnClicked(this, &SNexusTagAudit::OnRemoveAllClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("Log", "Log"))
				.ToolTipText(LOCTEXT("LogTip", "Print the orphaned tags to the Output Log."))
				.OnClicked(this, &SNexusTagAudit::OnLogClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SBox).WidthOverride(200.0f)
				[
					SNew(SSearchBox)
					.HintText(LOCTEXT("SearchHint", "Filter tags..."))
					.OnTextChanged(this, &SNexusTagAudit::OnSearchChanged)
				]
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
				.ListItemsSource(&VisibleOrphans)
				.OnGenerateRow(this, &SNexusTagAudit::OnGenerateRow)
				.SelectionMode(ESelectionMode::Multi)
			]
		]
	];

	// Live: an asset being (re)tagged or deleted changes what's orphaned.
	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start(
		{ UNexusItemDefinition::StaticClass(), UNexusAttachmentDefinition::StaticClass() },
		[this]() { Rebuild(); });
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

	ApplyFilter();
}

void SNexusTagAudit::ApplyFilter()
{
	VisibleOrphans.Reset();
	for (const TSharedPtr<FString>& Orphan : Orphans)
	{
		if (Orphan.IsValid() && (Filter.IsEmpty() || Orphan->Contains(Filter)))
		{
			VisibleOrphans.Add(Orphan);
		}
	}
	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

void SNexusTagAudit::OnSearchChanged(const FText& Text)
{
	Filter = Text.ToString();
	ApplyFilter();
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
		TEXT("Use Remove Selected / Remove All to delete these from the tag config once you're sure nothing references them."));
	return FReply::Handled();
}

int32 SNexusTagAudit::RemoveTags(const TArray<TSharedPtr<FString>>& Tags)
{
	IGameplayTagsEditorModule& TagsEditor = IGameplayTagsEditorModule::Get();
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();

	int32 Removed = 0;
	for (const TSharedPtr<FString>& TagPtr : Tags)
	{
		if (!TagPtr.IsValid())
		{
			continue;
		}
		// Resolve the registered node and delete its config source. Safe: these are
		// orphans, so no asset references them.
		TSharedPtr<FGameplayTagNode> Node = Manager.FindTagNode(FName(**TagPtr));
		if (Node.IsValid() && TagsEditor.DeleteTagFromINI(Node))
		{
			++Removed;
		}
	}

	if (Removed > 0)
	{
		Rebuild();
	}
	return Removed;
}

FReply SNexusTagAudit::OnRemoveSelectedClicked()
{
	const TArray<TSharedPtr<FString>> Selected =
		ListView.IsValid() ? ListView->GetSelectedItems() : TArray<TSharedPtr<FString>>();
	if (Selected.Num() == 0)
	{
		SummaryText = LOCTEXT("RemoveNone", "Select one or more orphan tags first.");
		return FReply::Handled();
	}

	const FText Prompt = FText::Format(
		LOCTEXT("ConfirmRemoveSel", "Delete {0} orphan tag(s) from the project's tag config? This edits DefaultGameplayTags.ini."),
		FText::AsNumber(Selected.Num()));
	if (FMessageDialog::Open(EAppMsgType::YesNo, Prompt) != EAppReturnType::Yes)
	{
		return FReply::Handled();
	}

	const int32 Removed = RemoveTags(Selected);
	SummaryText = FText::Format(LOCTEXT("RemovedSel", "Removed {0} orphan tag(s)."), FText::AsNumber(Removed));
	return FReply::Handled();
}

FReply SNexusTagAudit::OnRemoveAllClicked()
{
	if (Orphans.Num() == 0)
	{
		SummaryText = LOCTEXT("NoneToRemove", "No orphan tags to remove.");
		return FReply::Handled();
	}

	const FText Prompt = FText::Format(
		LOCTEXT("ConfirmRemoveAll", "Delete ALL {0} orphan tag(s) from the project's tag config? This edits DefaultGameplayTags.ini."),
		FText::AsNumber(Orphans.Num()));
	if (FMessageDialog::Open(EAppMsgType::YesNo, Prompt) != EAppReturnType::Yes)
	{
		return FReply::Handled();
	}

	const int32 Removed = RemoveTags(Orphans);
	SummaryText = FText::Format(LOCTEXT("RemovedAll", "Removed {0} orphan tag(s)."), FText::AsNumber(Removed));
	return FReply::Handled();
}

FText SNexusTagAudit::GetSummaryText() const
{
	return SummaryText;
}

#undef LOCTEXT_NAMESPACE
