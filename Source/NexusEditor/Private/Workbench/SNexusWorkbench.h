#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SBox;
class SButton;

/**
 * The Nexus Workbench — every Nexus tool hosted inside a single dockable window.
 *
 * A left-hand sidebar lists the tools (grouped by category, same data the Hub
 * uses); selecting one swaps the right-hand content area to that tool's widget.
 * Tool widgets are constructed lazily on first selection so opening the
 * Workbench is cheap even though it potentially hosts eight panels.
 *
 * The Workbench's Creator instance reassigns the module's ActiveCreator pointer
 * when it's constructed (same way the standalone Creator tab does), so other
 * tools' "Open in Creator" hand-offs route to whichever Creator was most
 * recently shown.
 */
class SNexusWorkbench : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusWorkbench) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	/** Swap the content area to the tool registered under TabName, constructing it on first use. */
	void ShowTool(FName TabName);

	/** Construct a fresh widget for the given tool tab; null if TabName isn't recognised. */
	TSharedPtr<SWidget> ConstructToolWidget(FName TabName) const;

	/** Bound to the title above the content panel. */
	FText GetCurrentToolLabel() const;

	/** Build the sidebar (categorised stack of tool buttons + footer actions). */
	TSharedRef<SWidget> BuildSidebar();

	/** Build one sidebar button for a tool entry, with checked state when it's active. */
	TSharedRef<SWidget> BuildSidebarEntry(FName TabName, const FText& Label, const FName IconName, const FText& Tooltip);

	/** Currently shown tool's TabName; NAME_None when nothing has been shown yet. */
	FName CurrentTab;

	/** Tool widgets cached by tab name — built on first selection, reused after. */
	TMap<FName, TSharedPtr<SWidget>> ToolCache;

	/** Right-hand content host. */
	TSharedPtr<SBox> ContentBox;
};
