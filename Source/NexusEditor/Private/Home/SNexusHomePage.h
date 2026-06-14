#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Audit/NexusContentAudit.h"

/** Raised when a Home card is clicked; the Workbench routes it to its own ShowTool(). */
DECLARE_DELEGATE_OneParam(FNexusOnActivateTool, FName);

/**
 * The Workbench Home page — the old Nexus Hub, folded inside the Workbench.
 *
 * Same front door (title, an audit-health summary, and a card for every tool grouped by
 * category) but the cards no longer spawn floating tabs: they raise OnActivateTool so the
 * Workbench swaps the centre pane in place. This is how the suite stops window-hopping.
 */
class SNexusHomePage : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusHomePage) {}
		/** Called with a tool's tab name when its card is clicked. */
		SLATE_EVENT(FNexusOnActivateTool, OnActivateTool)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FReply OnRefreshAuditClicked();
	FText GetAuditSummaryText() const;
	FSlateColor GetAuditSummaryColor() const;
	void Activate(FName TabName);

	FNexusOnActivateTool OnActivateTool;

	/** True once we've ever run the audit; gates the summary text. */
	bool bHasAuditResult = false;
	FNexusAuditResult LastAudit;
};
