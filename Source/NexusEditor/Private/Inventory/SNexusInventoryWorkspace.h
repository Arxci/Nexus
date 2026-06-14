#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * The Nexus Inventory workspace — the former Grid Preview and Inventory Sandbox folded
 * into one tool with two modes:
 *
 *   Audit — every item listed by footprint, with mis-sized items (degenerate dimensions
 *           or area outliers) flagged, and a live footprint visual of the selection.
 *   Pack  — the interactive attaché grid: drag real items into a real case, swap case
 *           sizes (presets, custom W×H, or load from an authored Case item), auto-arrange.
 *
 * Both modes publish their selection to the shared selection service, so an item's GridSize
 * is editable inline in the Workbench Inspector and both views refresh live.
 */
class SNexusInventoryWorkspace : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusInventoryWorkspace) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	enum class EMode : uint8 { Audit, Pack, Cases };

	int32 GetModeIndex() const
	{
		switch (Mode)
		{
		case EMode::Pack:  return 1;
		case EMode::Cases: return 2;
		default:           return 0;
		}
	}

	EMode Mode = EMode::Audit;
};
