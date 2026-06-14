#pragma once

#include "CoreMinimal.h"
#include "UObject/StrongObjectPtr.h"
#include "Widgets/SLeafWidget.h"

// Full type needed: TStrongObjectPtr<UNexusItemContainer> below requires a complete type.
#include "Nexus/Inventory/NexusItemContainer.h"

class UNexusItemDefinition;
class UNexusItemInstance;
struct FSlateBrush;

/**
 * The interactive grid surface of the Nexus Inventory Sandbox.
 *
 * Backed by a transient UNexusItemContainer — the SAME class the shipped attaché case
 * and item box use — so placement, packing, rotation, and overflow behave exactly as
 * they do in game; the preview can't drift from runtime. Designers drag the real item
 * icons around their real footprints, press R to rotate the held item, right-click to
 * remove, and hit Auto-arrange to run the runtime first-fit-decreasing repack. It turns
 * "tune GridSize blind" into "play the inventory without entering PIE".
 *
 * Custom-drawn (icons, grid lines, validity ghost) and mouse/keyboard driven rather than
 * a tree of child widgets, so a free-form drag reads naturally.
 */
class SNexusInventoryCanvas : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusInventoryCanvas) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** (Re)create the backing container at WxH cells. Existing contents are cleared. */
	void ResetGrid(int32 InWidth, int32 InHeight);

	/** Spawn an instance of Def and let the container place it (first free slot). */
	bool AddItem(UNexusItemDefinition* Def);

	/** Runtime first-fit-decreasing repack — the in-game "Optimize" button. */
	void AutoArrange();

	/** Empty the grid. */
	void ClearAll();

	/** Rotate the currently-held (mid-drag) item 90°; no-op when nothing is held. */
	void RotateHeld();

	bool IsHolding() const { return Held.IsValid(); }
	int32 GetItemCount() const;
	FIntPoint GetGridSize() const { return FIntPoint(GridW, GridH); }
	int32 GetUsedCellCount() const;
	int32 GetTotalCellCount() const { return GridW * GridH; }

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

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;
	virtual bool SupportsKeyboardFocus() const override { return true; }

private:
	FIntPoint LocalToCell(const FVector2D& Local) const;
	FVector2D CellToLocal(FIntPoint Cell) const;
	FIntPoint HeldFootprint() const;
	FIntPoint ItemTopLeft(const UNexusItemInstance* Instance) const;
	/** Where the held item's top-left would land for the current cursor cell. */
	FIntPoint HeldTargetTopLeft() const;
	const FSlateBrush* GetIconBrush(UNexusItemDefinition* Def) const;

	TStrongObjectPtr<UNexusItemContainer> Container;

	int32 GridW = 10;
	int32 GridH = 8;
	float CellSize = 48.0f;

	/** Item picked up under the cursor and following the mouse until released. */
	TWeakObjectPtr<UNexusItemInstance> Held;
	bool bHeldRotated = false;
	/** Grabbed-cell minus item-top-left, so the item keeps its grab anchor while dragging. */
	FIntPoint GrabOffset = FIntPoint(0, 0);
	FIntPoint HoverCell = FIntPoint(-1, -1);

	/** Per-definition icon brushes, built on demand. mutable: OnPaint is const. */
	mutable TMap<TWeakObjectPtr<UNexusItemDefinition>, TSharedPtr<FSlateBrush>> IconBrushCache;
};
