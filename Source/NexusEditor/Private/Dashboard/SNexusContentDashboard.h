#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

#include "Audit/NexusContentAudit.h"

class ITableRow;
class STableViewBase;
class FNexusAssetWatcher;

/**
 * The Nexus Content Dashboard: a dockable tab that runs FNexusContentAudit and
 * shows the result as three tables — audit findings, items (with their resolved
 * base Stat.* values), and attachments (with provided/required/conflict tags and
 * a per-row issue summary). Double-click any row to open the asset; hit Refresh
 * to re-run the audit after editing content.
 *
 * Spawned by FNexusEditorModule from the Tools menu entry.
 */
class SNexusContentDashboard : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusContentDashboard) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	/** Re-run the audit into Audit and refresh the three list views. */
	void RebuildAudit();
	/** Refill the filtered item/attachment views from Audit by the current search text. */
	void ApplyFilter();
	void OnSearchChanged(const FText& Text);

	TSharedRef<ITableRow> OnGenerateItemRow(TSharedPtr<FNexusItemRow> Row, const TSharedRef<STableViewBase>& Owner);
	TSharedRef<ITableRow> OnGenerateAttachmentRow(TSharedPtr<FNexusAttachmentRow> Row, const TSharedRef<STableViewBase>& Owner);
	TSharedRef<ITableRow> OnGenerateFindingRow(TSharedPtr<FNexusAuditFinding> Finding, const TSharedRef<STableViewBase>& Owner);

	void OnItemActivated(TSharedPtr<FNexusItemRow> Row);
	void OnAttachmentActivated(TSharedPtr<FNexusAttachmentRow> Row);
	void OnFindingActivated(TSharedPtr<FNexusAuditFinding> Finding);

	FReply OnRefreshClicked();
	FReply OnExportCsvClicked();
	FReply OnImportCsvClicked();
	FReply OnAutoTagUntaggedClicked();
	FText GetSummaryText() const;
	FText GetCsvStatusText() const;

	/** Open the given asset in its editor (double-click handler target). */
	static void OpenAsset(UObject* Asset);

	FNexusAuditResult Audit;
	FText CsvStatusText;

	/** Filtered views bound to the item/attachment tables (findings bind to Audit directly). */
	TArray<TSharedPtr<FNexusItemRow>> VisibleItems;
	TArray<TSharedPtr<FNexusAttachmentRow>> VisibleAttachments;
	FString Filter;

	TSharedPtr<SListView<TSharedPtr<FNexusItemRow>>> ItemListView;
	TSharedPtr<SListView<TSharedPtr<FNexusAttachmentRow>>> AttachmentListView;
	TSharedPtr<SListView<TSharedPtr<FNexusAuditFinding>>> FindingListView;

	/** Live refresh when items/attachments change. */
	TSharedPtr<FNexusAssetWatcher> Watcher;
};
