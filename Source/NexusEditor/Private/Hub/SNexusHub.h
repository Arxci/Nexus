#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Audit/NexusContentAudit.h"

/**
 * The Nexus Hub — a launcher window that gives the suite a single front door.
 * Tools are grouped into categorised cards (Authoring / Inspection / Auditing);
 * clicking a card invokes the corresponding tab via FGlobalTabmanager. A
 * "Run audit" / "Refresh" header pulls FNexusContentAudit summary counts so
 * content health is visible without having to open the dashboard.
 *
 * Spawned by FNexusEditorModule from the Tools → Nexus → Open Nexus Hub menu
 * entry and from the Level Editor toolbar button.
 */
class SNexusHub : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusHub) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	/** Run a fresh audit, update the counts, and refresh the summary text. */
	FReply OnRefreshAuditClicked();

	/** Open the dashboard so the user can drill into the findings. */
	FReply OnOpenDashboardClicked();

	/** Open the workbench (all tools in one window). */
	FReply OnOpenWorkbenchClicked();

	/** Build a manifest from the open level, then open the Creator with the result. */
	FReply OnBuildLevelManifestClicked();

	/** Bound: "0 errors · 0 warnings · 27 items · 12 attachments" — or "Audit not yet run". */
	FText GetAuditSummaryText() const;
	FSlateColor GetAuditSummaryColor() const;

	/** True once we've ever run the audit; gates the "open dashboard" hint visibility. */
	bool bHasAuditResult = false;
	FNexusAuditResult LastAudit;
};
