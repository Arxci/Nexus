#include "Sandbox/SNexusInventoryCanvas.h"

#include "Engine/Texture2D.h"
#include "InputCoreTypes.h"
#include "Rendering/DrawElements.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateBrush.h"
#include "Styling/StyleColors.h"
#include "UObject/Package.h"

#include "Shared/NexusEditorWidgets.h"

#include "Nexus/Inventory/NexusItemContainer.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"

namespace NexusSandbox
{
	constexpr float Pad = 6.0f;       // gutter between the widget edge and the grid
	constexpr float CellInset = 2.0f; // shrink each drawn icon so neighbours don't touch
}

void SNexusInventoryCanvas::Construct(const FArguments& InArgs)
{
	Container.Reset(NewObject<UNexusItemContainer>(GetTransientPackage()));
	if (Container.IsValid())
	{
		Container->Configure(GridW, GridH, /*WeightCapacity=*/ 0.0f, /*bUnlimitedWeight=*/ true, MAX_int32);
		// Empty section list normalises to a single Spatial catch-all, so everything we
		// add lands on the grid (the sandbox is about footprints, not list sections).
		Container->ConfigureSections(TArray<FNexusInventorySectionConfig>());
	}
}

void SNexusInventoryCanvas::ResetGrid(int32 InWidth, int32 InHeight)
{
	GridW = FMath::Clamp(InWidth, 1, 40);
	GridH = FMath::Clamp(InHeight, 1, 40);
	if (Container.IsValid())
	{
		Container->ClearAll();
		Container->Configure(GridW, GridH, 0.0f, true, MAX_int32);
		Container->ConfigureSections(TArray<FNexusInventorySectionConfig>());
	}
	Held.Reset();
	Invalidate(EInvalidateWidgetReason::Paint | EInvalidateWidgetReason::Layout);
}

bool SNexusInventoryCanvas::AddItem(UNexusItemDefinition* Def)
{
	if (!Def || !Container.IsValid())
	{
		return false;
	}
	const FNexusAddItemResult Result = Container->AddItem(Def, 1);
	Invalidate(EInvalidateWidgetReason::Paint);
	return Result.AmountAdded > 0;
}

void SNexusInventoryCanvas::AutoArrange()
{
	if (Container.IsValid())
	{
		Container->OptimizeSpatialSection();
		Invalidate(EInvalidateWidgetReason::Paint);
	}
}

void SNexusInventoryCanvas::ClearAll()
{
	if (Container.IsValid())
	{
		Container->ClearAll();
	}
	Held.Reset();
	Invalidate(EInvalidateWidgetReason::Paint);
}

void SNexusInventoryCanvas::RotateHeld()
{
	if (Held.IsValid())
	{
		bHeldRotated = !bHeldRotated;
		Invalidate(EInvalidateWidgetReason::Paint);
	}
}

int32 SNexusInventoryCanvas::GetItemCount() const
{
	return Container.IsValid() ? Container->GetItems().Num() : 0;
}

int32 SNexusInventoryCanvas::GetUsedCellCount() const
{
	if (!Container.IsValid())
	{
		return 0;
	}
	int32 Used = 0;
	for (const UNexusItemInstance* Instance : Container->GetItems())
	{
		Used += Container->GetOccupiedCells(Instance).Num();
	}
	return Used;
}

FVector2D SNexusInventoryCanvas::CellToLocal(FIntPoint Cell) const
{
	return FVector2D(NexusSandbox::Pad + Cell.X * CellSize, NexusSandbox::Pad + Cell.Y * CellSize);
}

FIntPoint SNexusInventoryCanvas::LocalToCell(const FVector2D& Local) const
{
	const FVector2D Rel = Local - FVector2D(NexusSandbox::Pad, NexusSandbox::Pad);
	if (Rel.X < 0.0f || Rel.Y < 0.0f)
	{
		return FIntPoint(-1, -1);
	}
	const int32 X = FMath::FloorToInt(Rel.X / CellSize);
	const int32 Y = FMath::FloorToInt(Rel.Y / CellSize);
	if (X < 0 || Y < 0 || X >= GridW || Y >= GridH)
	{
		return FIntPoint(-1, -1);
	}
	return FIntPoint(X, Y);
}

FIntPoint SNexusInventoryCanvas::HeldFootprint() const
{
	const UNexusItemInstance* H = Held.Get();
	const UNexusItemDefinition* Def = H ? H->GetDefinition() : nullptr;
	FIntPoint Size(1, 1);
	if (Def)
	{
		Size.X = FMath::Max(1, Def->GridSize.X);
		Size.Y = FMath::Max(1, Def->GridSize.Y);
	}
	if (bHeldRotated)
	{
		Swap(Size.X, Size.Y);
	}
	return Size;
}

FIntPoint SNexusInventoryCanvas::ItemTopLeft(const UNexusItemInstance* Instance) const
{
	if (!Container.IsValid() || !Instance)
	{
		return FIntPoint(0, 0);
	}
	const TArray<FIntPoint> Cells = Container->GetOccupiedCells(Instance);
	if (Cells.Num() == 0)
	{
		return FIntPoint(0, 0);
	}
	FIntPoint TopLeft(MAX_int32, MAX_int32);
	for (const FIntPoint& Cell : Cells)
	{
		TopLeft.X = FMath::Min(TopLeft.X, Cell.X);
		TopLeft.Y = FMath::Min(TopLeft.Y, Cell.Y);
	}
	return TopLeft;
}

FIntPoint SNexusInventoryCanvas::HeldTargetTopLeft() const
{
	return HoverCell - GrabOffset;
}

const FSlateBrush* SNexusInventoryCanvas::GetIconBrush(UNexusItemDefinition* Def) const
{
	if (!Def)
	{
		return nullptr;
	}
	if (TSharedPtr<FSlateBrush>* Found = IconBrushCache.Find(Def))
	{
		return Found->Get();
	}
	TSharedPtr<FSlateBrush> Brush = NexusEditorWidgets::IconBrush(Def->Icon.LoadSynchronous());
	IconBrushCache.Add(Def, Brush); // caches "no icon" as null too, so we only try once
	return Brush.Get();
}

FVector2D SNexusInventoryCanvas::ComputeDesiredSize(float) const
{
	return FVector2D(GridW * CellSize + 2.0f * NexusSandbox::Pad, GridH * CellSize + 2.0f * NexusSandbox::Pad);
}

int32 SNexusInventoryCanvas::OnPaint(
	const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	int32 LayerId,
	const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	using namespace NexusSandbox;

	const ESlateDrawEffect Effects = ESlateDrawEffect::None;
	const FSlateBrush* White = FAppStyle::Get().GetBrush("WhiteBrush");

	auto BoxGeom = [&AllottedGeometry](float Px, float Py, float Sx, float Sy)
	{
		return AllottedGeometry.ToPaintGeometry(FVector2D(Sx, Sy), FSlateLayoutTransform(FVector2D(Px, Py)));
	};

	int32 Layer = LayerId;

	// 1. Grid backdrop.
	const float BoardW = GridW * CellSize;
	const float BoardH = GridH * CellSize;
	FSlateDrawElement::MakeBox(
		OutDrawElements, Layer, BoxGeom(Pad, Pad, BoardW, BoardH), White, Effects,
		FLinearColor(0.02f, 0.02f, 0.03f, 1.0f));
	++Layer;

	// 2. Cell grid lines.
	const FLinearColor LineColor(1.0f, 1.0f, 1.0f, 0.10f);
	for (int32 X = 0; X <= GridW; ++X)
	{
		const float Lx = Pad + X * CellSize;
		TArray<FVector2D> Pts = { FVector2D(Lx, Pad), FVector2D(Lx, Pad + BoardH) };
		FSlateDrawElement::MakeLines(OutDrawElements, Layer, AllottedGeometry.ToPaintGeometry(), Pts, Effects, LineColor, true, 1.0f);
	}
	for (int32 Y = 0; Y <= GridH; ++Y)
	{
		const float Ly = Pad + Y * CellSize;
		TArray<FVector2D> Pts = { FVector2D(Pad, Ly), FVector2D(Pad + BoardW, Ly) };
		FSlateDrawElement::MakeLines(OutDrawElements, Layer, AllottedGeometry.ToPaintGeometry(), Pts, Effects, LineColor, true, 1.0f);
	}
	++Layer;

	// 3. Placed items (skip the one being dragged — it's drawn as the ghost).
	if (Container.IsValid())
	{
		UNexusItemInstance* HeldPtr = Held.Get();
		for (UNexusItemInstance* Instance : Container->GetItems())
		{
			if (!Instance || Instance == HeldPtr)
			{
				continue;
			}
			const FIntPoint TopLeft = ItemTopLeft(Instance);
			const FIntPoint Footprint = Instance->GetGridFootprint();
			const FVector2D Origin = CellToLocal(TopLeft);
			const float W = Footprint.X * CellSize;
			const float H = Footprint.Y * CellSize;

			// Tile backing so an icon-less item still reads as an occupied block.
			FSlateDrawElement::MakeBox(
				OutDrawElements, Layer,
				BoxGeom(Origin.X + CellInset, Origin.Y + CellInset, W - 2.0f * CellInset, H - 2.0f * CellInset),
				White, Effects, FLinearColor(0.10f, 0.12f, 0.16f, 1.0f));

			if (const FSlateBrush* Icon = GetIconBrush(Instance->GetDefinition()))
			{
				FSlateDrawElement::MakeBox(
					OutDrawElements, Layer + 1,
					BoxGeom(Origin.X + CellInset, Origin.Y + CellInset, W - 2.0f * CellInset, H - 2.0f * CellInset),
					Icon, Effects, FLinearColor::White);
			}
		}
	}
	Layer += 2;

	// 4. Drag ghost: green where it fits, red where it doesn't.
	if (Container.IsValid() && Held.IsValid())
	{
		const FIntPoint Footprint = HeldFootprint();
		const FIntPoint TopLeft = HeldTargetTopLeft();
		const bool bValid = Container->CanPlaceAt(Footprint, TopLeft, Held.Get());
		const FVector2D Origin = CellToLocal(TopLeft);
		const float W = Footprint.X * CellSize;
		const float H = Footprint.Y * CellSize;

		const FLinearColor Tint = bValid
			? FLinearColor(0.20f, 0.85f, 0.30f, 0.35f)
			: FLinearColor(0.90f, 0.25f, 0.25f, 0.35f);
		FSlateDrawElement::MakeBox(OutDrawElements, Layer, BoxGeom(Origin.X, Origin.Y, W, H), White, Effects, Tint);

		if (const FSlateBrush* Icon = GetIconBrush(Held->GetDefinition()))
		{
			FSlateDrawElement::MakeBox(
				OutDrawElements, Layer + 1,
				BoxGeom(Origin.X + CellInset, Origin.Y + CellInset, W - 2.0f * CellInset, H - 2.0f * CellInset),
				Icon, Effects, FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
		}
		Layer += 2;
	}

	return Layer;
}

FReply SNexusInventoryCanvas::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	const FVector2D Local = FVector2D(MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()));
	const FIntPoint Cell = LocalToCell(Local);

	if (MouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		if (!Held.IsValid() && Container.IsValid() && Cell != FIntPoint(-1, -1))
		{
			if (UNexusItemInstance* Instance = Container->GetItemAt(Cell))
			{
				Container->RemoveInstance(Instance);
				Invalidate(EInvalidateWidgetReason::Paint);
			}
		}
		return FReply::Handled();
	}

	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (Container.IsValid() && !Held.IsValid() && Cell != FIntPoint(-1, -1))
		{
			if (UNexusItemInstance* Instance = Container->GetItemAt(Cell))
			{
				Held = Instance;
				bHeldRotated = Instance->IsRotated();
				GrabOffset = Cell - ItemTopLeft(Instance);
				HoverCell = Cell;
				Invalidate(EInvalidateWidgetReason::Paint);
				return FReply::Handled().CaptureMouse(AsShared()).SetUserFocus(AsShared(), EFocusCause::Mouse);
			}
		}
		// Take focus so R-to-rotate works even on an empty click.
		return FReply::Handled().SetUserFocus(AsShared(), EFocusCause::Mouse);
	}

	return FReply::Unhandled();
}

FReply SNexusInventoryCanvas::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	const FVector2D Local = FVector2D(MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()));
	const FIntPoint Cell = LocalToCell(Local);
	if (Cell != HoverCell)
	{
		HoverCell = Cell;
		if (Held.IsValid())
		{
			Invalidate(EInvalidateWidgetReason::Paint);
		}
	}
	return Held.IsValid() ? FReply::Handled() : FReply::Unhandled();
}

FReply SNexusInventoryCanvas::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && Held.IsValid())
	{
		UNexusItemInstance* H = Held.Get();
		const FIntPoint Footprint = HeldFootprint();
		const FIntPoint TopLeft = HeldTargetTopLeft();
		if (Container.IsValid() && H && Container->CanPlaceAt(Footprint, TopLeft, H))
		{
			Container->MoveItemTo(H, TopLeft, bHeldRotated);
		}
		Held.Reset();
		Invalidate(EInvalidateWidgetReason::Paint);
		return FReply::Handled().ReleaseMouseCapture();
	}
	return FReply::Unhandled();
}

FReply SNexusInventoryCanvas::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	if (KeyEvent.GetKey() == EKeys::R && Held.IsValid())
	{
		RotateHeld();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}
