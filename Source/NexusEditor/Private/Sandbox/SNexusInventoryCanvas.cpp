#include "Sandbox/SNexusInventoryCanvas.h"

#include "Engine/Texture2D.h"
#include "InputCoreTypes.h"
#include "Rendering/DrawElements.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateBrush.h"
#include "Styling/StyleColors.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"

#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorStyle.h"
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

	// When an item definition changes (notably its GridSize edited live in the Inspector),
	// drop the cached icon/aspect and re-validate placements so a grown item can't overlap.
	// Read-only canvases (the live PIE mirror) skip the reflow — they re-mirror each refresh.
	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start({ UNexusItemDefinition::StaticClass() }, [this]()
	{
		IconBrushCache.Reset();
		IconSizeCache.Reset();
		if (!bReadOnly)
		{
			ReflowAfterFootprintChange();
		}
		Invalidate(EInvalidateWidgetReason::Paint | EInvalidateWidgetReason::Layout);
	});
}

void SNexusInventoryCanvas::ReflowAfterFootprintChange()
{
	if (!Container.IsValid())
	{
		return;
	}

	// Copy: re-homing/removal mutates the container's item list while we iterate.
	const TArray<UNexusItemInstance*> Snapshot = Container->GetItems();
	for (UNexusItemInstance* Instance : Snapshot)
	{
		if (!Instance)
		{
			continue;
		}
		const FIntPoint Current = ItemTopLeft(Instance);
		const FIntPoint Footprint = Instance->GetGridFootprint();
		if (Container->CanPlaceAt(Footprint, Current, Instance))
		{
			continue; // still fits where it is
		}

		bool bPlaced = false;
		auto TryFit = [&](FIntPoint Foot, bool bRotated)
		{
			for (int32 Y = 0; Y + Foot.Y <= GridH && !bPlaced; ++Y)
			{
				for (int32 X = 0; X + Foot.X <= GridW && !bPlaced; ++X)
				{
					if (Container->CanPlaceAt(Foot, FIntPoint(X, Y), Instance))
					{
						Container->MoveItemTo(Instance, FIntPoint(X, Y), bRotated);
						bPlaced = true;
					}
				}
			}
		};

		// Current orientation first, then the 90°-rotated footprint.
		TryFit(Footprint, Instance->IsRotated());
		if (!bPlaced)
		{
			TryFit(FIntPoint(Footprint.Y, Footprint.X), !Instance->IsRotated());
		}
		if (!bPlaced)
		{
			// No legal spot at the new size — drop it from the grid (the case-swap spill model).
			Container->RemoveInstance(Instance);
		}
	}

	Invalidate(EInvalidateWidgetReason::Paint | EInvalidateWidgetReason::Layout);
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

void SNexusInventoryCanvas::MirrorSpatialItems(int32 InWidth, int32 InHeight, const TArray<FNexusItemSaveData>& Saved)
{
	GridW = FMath::Clamp(InWidth, 1, 40);
	GridH = FMath::Clamp(InHeight, 1, 40);
	if (Container.IsValid())
	{
		// Resize the grid, then rebuild display instances at their saved cells. RestoreFromSaveData
		// recreates each instance from its descriptor (position + rotation + stack preserved), so the
		// canvas shows the live grid exactly without re-running placement.
		Container->SetGridDimensions(GridW, GridH);
		Container->RestoreFromSaveData(Saved);
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

FVector2D SNexusInventoryCanvas::GetIconNativeSize(UNexusItemDefinition* Def) const
{
	if (!Def)
	{
		return FVector2D(1.0f, 1.0f);
	}
	if (const FVector2D* Found = IconSizeCache.Find(Def))
	{
		return *Found;
	}
	FVector2D Size(1.0f, 1.0f);
	if (UTexture2D* Texture = Def->Icon.LoadSynchronous())
	{
		const int32 W = Texture->GetSizeX();
		const int32 H = Texture->GetSizeY();
		if (W > 0 && H > 0)
		{
			Size = FVector2D(W, H);
		}
	}
	IconSizeCache.Add(Def, Size);
	return Size;
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

	// Draw an item icon centred and aspect-preserved inside a footprint rect — a non-square
	// icon in a non-square slot is letter/pillar-boxed rather than stretched.
	auto DrawIcon = [&](int32 InLayer, UNexusItemDefinition* Def, float Rx, float Ry, float Rw, float Rh, const FLinearColor& Tint)
	{
		const FSlateBrush* Icon = GetIconBrush(Def);
		if (!Icon || Rw <= 0.0f || Rh <= 0.0f)
		{
			return;
		}
		const FVector2D Native = GetIconNativeSize(Def);
		const float Aspect = (Native.Y > 0.0f) ? (Native.X / Native.Y) : 1.0f;
		float DrawW = Rw;
		float DrawH = Rh;
		if (Rw / Rh > Aspect) { DrawW = Rh * Aspect; }                                  // rect wider than icon → pillarbox
		else                  { DrawH = Rw / FMath::Max(Aspect, KINDA_SMALL_NUMBER); }  // rect taller → letterbox
		const float Ox = Rx + (Rw - DrawW) * 0.5f;
		const float Oy = Ry + (Rh - DrawH) * 0.5f;
		FSlateDrawElement::MakeBox(OutDrawElements, InLayer, BoxGeom(Ox, Oy, DrawW, DrawH), Icon, Effects, Tint);
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

	const FSlateBrush* Border = FAppStyle::Get().GetBrush("Border");          // edges only
	const FSlateFontInfo BadgeFont = FCoreStyle::GetDefaultFontStyle("Bold", 8);

	// A placed item's category colour (first CategoryTag leaf), for its frame.
	auto FrameColor = [](const UNexusItemDefinition* Def) -> FLinearColor
	{
		if (Def)
		{
			for (const FGameplayTag& CatTag : Def->CategoryTags)
			{
				return NexusEditorStyle::CategoryColorForTag(CatTag.ToString());
			}
		}
		return FLinearColor(0.45f, 0.48f, 0.55f);
	};

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
			const UNexusItemDefinition* Def = Instance->GetDefinition();
			const FIntPoint TopLeft = ItemTopLeft(Instance);
			const FIntPoint Footprint = Instance->GetGridFootprint();
			const FVector2D Origin = CellToLocal(TopLeft);
			const float W = Footprint.X * CellSize;
			const float H = Footprint.Y * CellSize;
			const float Ix = Origin.X + CellInset;
			const float Iy = Origin.Y + CellInset;
			const float Iw = W - 2.0f * CellInset;
			const float Ih = H - 2.0f * CellInset;

			// Tile backing so an icon-less item still reads as an occupied block.
			FSlateDrawElement::MakeBox(
				OutDrawElements, Layer, BoxGeom(Ix, Iy, Iw, Ih), White, Effects,
				FLinearColor(0.10f, 0.12f, 0.16f, 1.0f));

			DrawIcon(Layer + 1, Instance->GetDefinition(), Ix, Iy, Iw, Ih, FLinearColor::White);

			// Category-coloured frame (stands in for a rarity frame until rarity exists).
			FSlateDrawElement::MakeBox(
				OutDrawElements, Layer + 2, BoxGeom(Ix, Iy, Iw, Ih), Border, Effects, FrameColor(Def));

			// Stack badge (top-right) and weight badge (bottom-left).
			const int32 Stack = Instance->GetStackCount();
			if (Stack > 1)
			{
				FSlateDrawElement::MakeText(
					OutDrawElements, Layer + 3,
					BoxGeom(Ix + Iw - 22.0f, Iy + 2.0f, 20.0f, 12.0f),
					FString::Printf(TEXT("x%d"), Stack), BadgeFont, Effects, FLinearColor::White);
			}
			if (Def && Def->Weight > 0.0f)
			{
				FSlateDrawElement::MakeText(
					OutDrawElements, Layer + 3,
					BoxGeom(Ix + 3.0f, Iy + Ih - 13.0f, Iw, 12.0f),
					FString::Printf(TEXT("%.1f"), Def->Weight), BadgeFont, Effects,
					FLinearColor(0.85f, 0.85f, 0.90f, 0.9f));
			}
		}
	}
	Layer += 4;

	// 3b. Hover highlight: subtle wash over the item under the cursor (when not dragging).
	if (Container.IsValid() && !Held.IsValid() && HoverCell != FIntPoint(-1, -1))
	{
		if (UNexusItemInstance* Hovered = Container->GetItemAt(HoverCell))
		{
			const FIntPoint TopLeft = ItemTopLeft(Hovered);
			const FIntPoint Footprint = Hovered->GetGridFootprint();
			const FVector2D Origin = CellToLocal(TopLeft);
			FSlateDrawElement::MakeBox(
				OutDrawElements, Layer,
				BoxGeom(Origin.X + CellInset, Origin.Y + CellInset,
					Footprint.X * CellSize - 2.0f * CellInset, Footprint.Y * CellSize - 2.0f * CellInset),
				White, Effects, FLinearColor(1.0f, 1.0f, 1.0f, 0.10f));
		}
	}
	++Layer;

	// 4. Drag ghost: a soft drop-shadow, then green where it fits / red where it doesn't.
	if (Container.IsValid() && Held.IsValid())
	{
		const FIntPoint Footprint = HeldFootprint();
		const FIntPoint TopLeft = HeldTargetTopLeft();
		const bool bValid = Container->CanPlaceAt(Footprint, TopLeft, Held.Get());
		const FVector2D Origin = CellToLocal(TopLeft);
		const float W = Footprint.X * CellSize;
		const float H = Footprint.Y * CellSize;

		// Drop shadow (offset, dark, translucent) for a "picked up" feel.
		FSlateDrawElement::MakeBox(
			OutDrawElements, Layer, BoxGeom(Origin.X + 4.0f, Origin.Y + 4.0f, W, H), White, Effects,
			FLinearColor(0.0f, 0.0f, 0.0f, 0.35f));

		const FLinearColor Tint = bValid
			? FLinearColor(0.20f, 0.85f, 0.30f, 0.35f)
			: FLinearColor(0.90f, 0.25f, 0.25f, 0.35f);
		FSlateDrawElement::MakeBox(OutDrawElements, Layer + 1, BoxGeom(Origin.X, Origin.Y, W, H), White, Effects, Tint);

		DrawIcon(Layer + 2, Held->GetDefinition(),
			Origin.X + CellInset, Origin.Y + CellInset, W - 2.0f * CellInset, H - 2.0f * CellInset,
			FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));

		// Invalid-drop reason, drawn just above the ghost.
		const FString Reason = HeldInvalidReason();
		if (!Reason.IsEmpty())
		{
			FSlateDrawElement::MakeText(
				OutDrawElements, Layer + 3,
				BoxGeom(Origin.X, Origin.Y - 14.0f, FMath::Max(W, 160.0f), 12.0f),
				Reason, BadgeFont, Effects, FLinearColor(1.0f, 0.45f, 0.45f, 1.0f));
		}
		Layer += 4;
	}

	return Layer;
}

FString SNexusInventoryCanvas::HeldInvalidReason() const
{
	if (!Container.IsValid() || !Held.IsValid())
	{
		return FString();
	}
	const FIntPoint Footprint = HeldFootprint();
	const FIntPoint TopLeft = HeldTargetTopLeft();
	if (Container->CanPlaceAt(Footprint, TopLeft, Held.Get()))
	{
		return FString();   // valid drop
	}
	// Out of bounds vs. overlap — the two ways CanPlaceAt fails.
	if (TopLeft.X < 0 || TopLeft.Y < 0 || TopLeft.X + Footprint.X > GridW || TopLeft.Y + Footprint.Y > GridH)
	{
		return TEXT("Doesn't fit the case (out of bounds)");
	}
	return TEXT("Overlaps another item");
}

FReply SNexusInventoryCanvas::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	const FVector2D Local = FVector2D(MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition()));
	const FIntPoint Cell = LocalToCell(Local);

	// Read-only (live inspector): never mutate; a left-click just reports the item under the cursor.
	if (bReadOnly)
	{
		if (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && Container.IsValid() && Cell != FIntPoint(-1, -1))
		{
			if (UNexusItemInstance* Instance = Container->GetItemAt(Cell))
			{
				if (OnItemClicked)
				{
					OnItemClicked(Instance->GetDefinition());
				}
			}
		}
		return FReply::Handled();
	}

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
		// Repaint on any hover change — drives both the drag ghost and the hover highlight.
		Invalidate(EInvalidateWidgetReason::Paint);
	}
	return Held.IsValid() ? FReply::Handled() : FReply::Unhandled();
}

FReply SNexusInventoryCanvas::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bReadOnly)
	{
		return FReply::Unhandled();
	}
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

FString SNexusInventoryCanvas::SerializeLayout() const
{
	if (!Container.IsValid())
	{
		return FString();
	}
	TArray<FString> Tokens;
	for (const UNexusItemInstance* Instance : Container->GetItems())
	{
		const UNexusItemDefinition* Def = Instance ? Instance->GetDefinition() : nullptr;
		if (!Def)
		{
			continue;
		}
		const FIntPoint TopLeft = ItemTopLeft(Instance);
		Tokens.Add(FString::Printf(TEXT("%s|%d|%d|%d"),
			*Def->GetPathName(), TopLeft.X, TopLeft.Y, Instance->IsRotated() ? 1 : 0));
	}
	return FString::Join(Tokens, TEXT(";"));
}

void SNexusInventoryCanvas::DeserializeLayout(const FString& Data)
{
	if (!Container.IsValid())
	{
		return;
	}
	Container->ClearAll();
	Held.Reset();

	TArray<FString> Tokens;
	Data.ParseIntoArray(Tokens, TEXT(";"), /*InCullEmpty=*/ true);
	for (const FString& Token : Tokens)
	{
		TArray<FString> Parts;
		Token.ParseIntoArray(Parts, TEXT("|"), /*InCullEmpty=*/ false);
		if (Parts.Num() != 4)
		{
			continue;
		}
		UNexusItemDefinition* Def = LoadObject<UNexusItemDefinition>(nullptr, *Parts[0]);
		if (!Def)
		{
			continue;   // a definition that no longer exists is simply skipped
		}
		const FIntPoint TopLeft(FCString::Atoi(*Parts[1]), FCString::Atoi(*Parts[2]));
		const bool bRot = Parts[3] == TEXT("1");

		// Add (first-fit), then move it to the saved cell/rotation if that's legal.
		const FNexusAddItemResult Result = Container->AddItem(Def, 1);
		if (Result.NewInstances.Num() > 0)
		{
			UNexusItemInstance* New = Result.NewInstances[0];
			const FIntPoint Footprint = bRot ? FIntPoint(FMath::Max(1, Def->GridSize.Y), FMath::Max(1, Def->GridSize.X))
											 : FIntPoint(FMath::Max(1, Def->GridSize.X), FMath::Max(1, Def->GridSize.Y));
			if (New && Container->CanPlaceAt(Footprint, TopLeft, New))
			{
				Container->MoveItemTo(New, TopLeft, bRot);
			}
		}
	}
	Invalidate(EInvalidateWidgetReason::Paint);
}

FReply SNexusInventoryCanvas::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent)
{
	if (bReadOnly)
	{
		return FReply::Unhandled();
	}
	if (KeyEvent.GetKey() == EKeys::R && Held.IsValid())
	{
		RotateHeld();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}
