#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SWrapBox;
class FNexusAssetWatcher;
struct FSlateBrush;

/**
 * A contact sheet of every item's authored Icon, framed by category colour with its name
 * and grid footprint — an at-a-glance art-review and footprint-consistency surface
 * (missing icons jump out as empty frames). Clicking a tile selects the item so the
 * Inspector can edit it. Live-refreshes as items change.
 */
class SNexusIconSheet : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusIconSheet) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	void Rebuild();
	FReply OnRefreshClicked();
	FText GetSummaryText() const;

	TSharedPtr<SWrapBox> Wrap;
	/** Kept alive while the tiles draw them (SImage holds raw brush pointers). */
	TArray<TSharedPtr<FSlateBrush>> KeepAliveBrushes;
	FText SummaryText;
	TSharedPtr<FNexusAssetWatcher> Watcher;
};
