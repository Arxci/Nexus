#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class STableViewBase;
class FNexusAssetWatcher;

/**
 * The Nexus Tag Audit: finds orphaned identity tags — Item.Identity.* /
 * Attachment.Identity.* tags that are registered in the project but no asset uses.
 *
 * The Creator's Auto-tag derives and registers a project tag from an asset's name;
 * rename or delete that asset and the tag is stranded in the config, cluttering
 * every tag picker forever. This lists those strays (and counts still-untagged
 * assets), lets you select and delete them straight from the config (no INI
 * archaeology), and refreshes live as assets change.
 */
class SNexusTagAudit : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusTagAudit) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	void Rebuild();
	void ApplyFilter();
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& Owner);
	void OnSearchChanged(const FText& Text);
	FReply OnRefreshClicked();
	FReply OnLogClicked();
	FReply OnRemoveSelectedClicked();
	FReply OnRemoveAllClicked();
	/** Delete each tag string from the tag config; returns how many were removed. */
	int32 RemoveTags(const TArray<TSharedPtr<FString>>& Tags);
	FText GetSummaryText() const;

	/** All orphans (built per Rebuild). */
	TArray<TSharedPtr<FString>> Orphans;
	/** Filtered view bound to the list. */
	TArray<TSharedPtr<FString>> VisibleOrphans;
	TSharedPtr<SListView<TSharedPtr<FString>>> ListView;
	FText SummaryText;
	FString Filter;

	TSharedPtr<FNexusAssetWatcher> Watcher;
};
