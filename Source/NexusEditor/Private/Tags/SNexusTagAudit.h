#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class STableViewBase;

/**
 * The Nexus Tag Audit: finds orphaned identity tags — Item.Identity.* /
 * Attachment.Identity.* tags that are registered in the project but no asset uses.
 *
 * The Creator's Auto-tag derives and registers a project tag from an asset's name;
 * rename or delete that asset and the tag is stranded in the config, cluttering
 * every tag picker forever. This lists those strays (and counts still-untagged
 * assets) so tag hygiene is a glance, not an archaeology dig.
 */
class SNexusTagAudit : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusTagAudit) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	void Rebuild();
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& Owner);
	FReply OnRefreshClicked();
	FReply OnLogClicked();
	FText GetSummaryText() const;

	TArray<TSharedPtr<FString>> Orphans;
	TSharedPtr<SListView<TSharedPtr<FString>>> ListView;
	FText SummaryText;
};
