#pragma once

#include "CoreMinimal.h"
#include "UObject/StrongObjectPtr.h"
#include "Widgets/SLeafWidget.h"

// Full type needed: TStrongObjectPtr<UNexusItemContainer> below requires a complete type.
#include "Nexus/Inventory/NexusItemContainer.h"

class UNexusItemDefinition;
class UNexusItemInstance;
class FNexusAssetWatcher;
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

	/**
	 * Read-only display mode: when set, the canvas ignores drag / remove / rotate input and a
	 * left-click only reports the item under the cursor (see SetOnItemClicked). Used by the live
	 * PIE inventory inspector, which reflects the real container and must not mutate it.
	 */
	void SetReadOnly(bool bInReadOnly) { bReadOnly = bInReadOnly; }

	/**
	 * Mirror an external container's spatially-placed items into this canvas for read-only
	 * display. Saved are FNexusItemSaveData snapshots (definition + grid position + rotation +
	 * stack); each lands at its saved cell, so the canvas shows the exact live grid. Holds no
	 * reference to the source container — it rebuilds transient display instances each call.
	 */
	void MirrorSpatialItems(int32 InWidth, int32 InHeight, const TArray<FNexusItemSaveData>& Saved);

	/** Invoked with the item definition under the cursor on a left-click while in read-only mode. */
	void SetOnItemClicked(TFunction<void(UNexusItemDefinition*)> InHandler) { OnItemClicked = MoveTemp(InHandler); }

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

	/** Serialise the current placement to a compact string (def path | x | y | rot, ';'-joined). */
	FString SerializeLayout() const;
	/** Clear and rebuild the grid from a string produced by SerializeLayout(). */
	void DeserializeLayout(const FString& Data);
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
	/** Empty when the held item's current target is a legal drop; else a short why-not string. */
	FString HeldInvalidReason() const;
	FIntPoint ItemTopLeft(const UNexusItemInstance* Instance) const;
	/** Where the held item's top-left would land for the current cursor cell. */
	FIntPoint HeldTargetTopLeft() const;
	const FSlateBrush* GetIconBrush(UNexusItemDefinition* Def) const;
	/** The icon texture's native pixel size (cached), for aspect-preserving draw. (1,1) when unknown. */
	FVector2D GetIconNativeSize(UNexusItemDefinition* Def) const;

	/**
	 * Re-validate every placed item after a footprint (GridSize) change: items whose new size
	 * no longer fits where they are get re-homed to the first free spot (trying rotation), and
	 * any that can't fit anywhere are removed. Keeps the grid legal when an item is resized
	 * live in the Inspector. No-op in read-only mode.
	 */
	void ReflowAfterFootprintChange();

	TStrongObjectPtr<UNexusItemContainer> Container;

	/** When true, input is read-only (live PIE inspector); a left-click just selects an item. */
	bool bReadOnly = false;
	/** Read-only left-click callback (the item definition under the cursor). */
	TFunction<void(UNexusItemDefinition*)> OnItemClicked;

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
	/** Per-definition icon native pixel size, for aspect-preserving draw. mutable: OnPaint is const. */
	mutable TMap<TWeakObjectPtr<UNexusItemDefinition>, FVector2D> IconSizeCache;

	/** Rebuilds icon caches and reflows placements when an item definition changes (e.g. a resized GridSize). */
	TSharedPtr<FNexusAssetWatcher> Watcher;
};
