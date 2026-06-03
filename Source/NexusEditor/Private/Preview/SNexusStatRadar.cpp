#include "Preview/SNexusStatRadar.h"

#include "Fonts/SlateFontInfo.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "Shared/NexusEditorUtils.h"

#define LOCTEXT_NAMESPACE "NexusStatRadar"

namespace NexusRadar
{
	constexpr int32 RingCount = 4;
	constexpr float LabelMargin = 56.0f;
	constexpr float MinDimension = 220.0f;

	const FLinearColor RingColor(1.0f, 1.0f, 1.0f, 0.12f);
	const FLinearColor AxisColor(1.0f, 1.0f, 1.0f, 0.22f);
	const FLinearColor LabelColor(1.0f, 1.0f, 1.0f, 0.85f);

	FLinearColor BasePolygonColor()
	{
		FLinearColor C = FStyleColors::AccentGreen.GetSpecifiedColor();
		C.A = 0.9f;
		return C;
	}

	FLinearColor FinalPolygonColor()
	{
		FLinearColor C = FStyleColors::AccentBlue.GetSpecifiedColor();
		C.A = 0.9f;
		return C;
	}
}

void SNexusStatRadar::Construct(const FArguments& InArgs)
{
}

void SNexusStatRadar::SetStats(const TArray<FNexusResolvedStat>& InStats)
{
	Stats = InStats;
	Invalidate(EInvalidateWidget::Paint);
}

FVector2D SNexusStatRadar::ComputeDesiredSize(float) const
{
	return FVector2D(NexusRadar::MinDimension, NexusRadar::MinDimension);
}

int32 SNexusStatRadar::OnPaint(
	const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	int32 LayerId,
	const FWidgetStyle& InWidgetStyle,
	bool bParentEnabled) const
{
	using namespace NexusRadar;

	const FVector2D Size = AllottedGeometry.GetLocalSize();
	const FVector2D Center = Size * 0.5f;
	const float Radius = FMath::Max(0.0f, FMath::Min(Size.X, Size.Y) * 0.5f - LabelMargin);

	const FPaintGeometry PaintGeo = AllottedGeometry.ToPaintGeometry();
	const ESlateDrawEffect Effects = ESlateDrawEffect::None;
	const FSlateFontInfo LabelFont = FCoreStyle::GetDefaultFontStyle("Bold", 8);

	const int32 N = Stats.Num();
	if (N < 3 || Radius < 10.0f)
	{
		const FSlateFontInfo MsgFont = FCoreStyle::GetDefaultFontStyle("Regular", 9);
		const FText Message = (N == 0)
			? LOCTEXT("NoStats", "(no stats to graph)")
			: LOCTEXT("TooFewStats", "(need three or more stats to graph)");
		FSlateDrawElement::MakeText(
			OutDrawElements, LayerId,
			AllottedGeometry.ToOffsetPaintGeometry(Center - FVector2D(80.0f, 8.0f)),
			Message, MsgFont, Effects, LabelColor);
		return LayerId + 1;
	}

	// Per-axis unit vectors. First axis at the top, going clockwise.
	TArray<FVector2D> AxisUnit;
	AxisUnit.SetNumUninitialized(N);
	for (int32 i = 0; i < N; ++i)
	{
		const float Angle = (2.0f * PI * i) / N - HALF_PI;
		AxisUnit[i] = FVector2D(FMath::Cos(Angle), FMath::Sin(Angle));
	}

	// Per-axis normaliser: use max(Base, Final) so the bigger value lands near
	// the outer ring and the smaller one is plotted as a fraction of it.
	TArray<float> AxisMax;
	AxisMax.SetNumUninitialized(N);
	for (int32 i = 0; i < N; ++i)
	{
		AxisMax[i] = FMath::Max3(Stats[i].Base, Stats[i].Final, KINDA_SMALL_NUMBER) * 1.05f;
	}

	int32 Layer = LayerId;

	// Concentric grid rings. MakeLines draws a polyline, so we close the ring by
	// re-appending the first vertex — but TArray asserts on Add(Self[0]), so the
	// first point goes into a local before being appended again at the end.
	for (int32 r = 1; r <= RingCount; ++r)
	{
		const float Frac = static_cast<float>(r) / RingCount;
		TArray<FVector2D> Ring;
		Ring.Reserve(N + 1);
		for (int32 i = 0; i < N; ++i)
		{
			Ring.Add(Center + AxisUnit[i] * Radius * Frac);
		}
		const FVector2D RingFirst = Ring[0];
		Ring.Add(RingFirst);
		FSlateDrawElement::MakeLines(
			OutDrawElements, Layer, PaintGeo, Ring, Effects, RingColor, true, 1.0f);
	}
	++Layer;

	// Axis spokes.
	for (int32 i = 0; i < N; ++i)
	{
		TArray<FVector2D> Spoke = { Center, Center + AxisUnit[i] * Radius };
		FSlateDrawElement::MakeLines(
			OutDrawElements, Layer, PaintGeo, Spoke, Effects, AxisColor, true, 1.0f);
	}
	++Layer;

	auto BuildPolygon = [&](float FNexusResolvedStat::*Field) -> TArray<FVector2D>
	{
		TArray<FVector2D> Poly;
		Poly.Reserve(N + 1);
		for (int32 i = 0; i < N; ++i)
		{
			const float Value = Stats[i].*Field;
			const float Frac = FMath::Clamp(Value / AxisMax[i], 0.0f, 1.0f);
			Poly.Add(Center + AxisUnit[i] * Radius * Frac);
		}
		const FVector2D PolyFirst = Poly[0];
		Poly.Add(PolyFirst);
		return Poly;
	};

	// Base polygon under Final so changes from the loadout pop on top.
	const TArray<FVector2D> BasePoly = BuildPolygon(&FNexusResolvedStat::Base);
	FSlateDrawElement::MakeLines(
		OutDrawElements, Layer, PaintGeo, BasePoly, Effects, BasePolygonColor(), true, 2.0f);
	++Layer;

	const TArray<FVector2D> FinalPoly = BuildPolygon(&FNexusResolvedStat::Final);
	FSlateDrawElement::MakeLines(
		OutDrawElements, Layer, PaintGeo, FinalPoly, Effects, FinalPolygonColor(), true, 2.5f);
	++Layer;

	// Axis labels: name (top line) and "base -> final" (bottom line). Offset
	// each label horizontally based on which side of the chart its axis is on,
	// so right-side labels start at the spoke tip and left-side labels end at it.
	for (int32 i = 0; i < N; ++i)
	{
		const FString StatName = NexusEditorUtil::TagLeaf(Stats[i].StatTag);
		const FString Numbers = FString::Printf(TEXT("%s → %s"),
			*NexusEditorUtil::FormatStat(Stats[i].Base),
			*NexusEditorUtil::FormatStat(Stats[i].Final));

		const FVector2D Tip = Center + AxisUnit[i] * (Radius + 8.0f);

		// Approximate text box so we can push labels off the spoke without measuring.
		const FVector2D BoxSize(72.0f, 28.0f);
		FVector2D LabelTopLeft = Tip;
		if (AxisUnit[i].X < -0.2f)      { LabelTopLeft.X -= BoxSize.X; }
		else if (AxisUnit[i].X < 0.2f)  { LabelTopLeft.X -= BoxSize.X * 0.5f; }
		if (AxisUnit[i].Y < -0.2f)      { LabelTopLeft.Y -= BoxSize.Y; }
		else if (AxisUnit[i].Y < 0.2f)  { LabelTopLeft.Y -= BoxSize.Y * 0.5f; }

		FSlateDrawElement::MakeText(
			OutDrawElements, Layer,
			AllottedGeometry.ToOffsetPaintGeometry(LabelTopLeft),
			FText::FromString(StatName), LabelFont, Effects, LabelColor);

		FSlateDrawElement::MakeText(
			OutDrawElements, Layer,
			AllottedGeometry.ToOffsetPaintGeometry(LabelTopLeft + FVector2D(0.0f, 12.0f)),
			FText::FromString(Numbers),
			FCoreStyle::GetDefaultFontStyle("Regular", 7), Effects, LabelColor);
	}
	++Layer;

	// Legend in the top-left corner.
	const FSlateFontInfo LegendFont = FCoreStyle::GetDefaultFontStyle("Regular", 8);
	const FVector2D LegendOrigin(8.0f, 8.0f);
	FSlateDrawElement::MakeText(
		OutDrawElements, Layer,
		AllottedGeometry.ToOffsetPaintGeometry(LegendOrigin),
		LOCTEXT("LegendBase", "● Base"),
		LegendFont, Effects, BasePolygonColor());
	FSlateDrawElement::MakeText(
		OutDrawElements, Layer,
		AllottedGeometry.ToOffsetPaintGeometry(LegendOrigin + FVector2D(0.0f, 12.0f)),
		LOCTEXT("LegendFinal", "● Final"),
		LegendFont, Effects, FinalPolygonColor());

	return Layer + 1;
}

#undef LOCTEXT_NAMESPACE
