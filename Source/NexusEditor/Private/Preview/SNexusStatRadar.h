#pragma once

#include "CoreMinimal.h"
#include "Widgets/SLeafWidget.h"

#include "Preview/NexusAssemblyPreview.h"

/**
 * Radar / spider chart over a TArray<FNexusResolvedStat>: two polygons (base and
 * final) overlaid on per-stat axes, so the shape change tells you at a glance
 * whether the current attachment loadout produced a balanced upgrade or just
 * shifted weight between stats.
 *
 * Each axis is normalised independently to max(Base, Final) — so a stat that
 * went up reaches further out and one that went down pulls inward, regardless
 * of absolute magnitudes (Damage 30→50 and AmmoCap 20→18 are both readable on
 * the same chart). Concentric rings give a visual scale; labels at each vertex
 * carry the stat name and the after/before numbers.
 *
 * Degenerates gracefully: fewer than 3 stats renders an empty grid with a
 * message ("need three or more stats to graph") since a 2-axis polygon is
 * just a line. The table next to it is the source of truth — the radar is
 * the at-a-glance.
 */
class SNexusStatRadar : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusStatRadar) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** Re-render with these resolved stats (sorted is fine; we render in the order given). */
	void SetStats(const TArray<FNexusResolvedStat>& InStats);

protected:
	virtual int32 OnPaint(
		const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override;

	virtual FVector2D ComputeDesiredSize(float) const override;

private:
	TArray<FNexusResolvedStat> Stats;
};
