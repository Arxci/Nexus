#pragma once

#include "CoreMinimal.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"
#include "Widgets/SWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

class UObject;

/**
 * Small Slate building blocks shared by the Nexus tool windows, so a "section
 * label", a "table cell", and a "section header band" look identical everywhere
 * and live in one place. Previously each window re-declared these in an anonymous
 * namespace. Header-only inlines — include and use.
 */
namespace NexusEditorWidgets
{
	/** Subdued bold caption used to title a control group ("TEMPLATE", "FOLDER", ...). */
	inline TSharedRef<SWidget> SectionLabel(const FText& Text)
	{
		return SNew(STextBlock)
			.Text(Text)
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground());
	}

	/** Titled band drawn above a table. */
	inline TSharedRef<SWidget> SectionHeader(const FText& Title)
	{
		return SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
			.Padding(FMargin(8.0f, 4.0f))
			[
				SNew(STextBlock)
				.Text(Title)
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
			];
	}

	/**
	 * Build a drawable image brush from a texture (pass an already-resolved UTexture2D as
	 * a UObject*). Returns null when the texture is null, so callers can branch on validity.
	 * The returned brush must be kept alive by the caller for as long as a widget draws it.
	 * One place to construct item/attachment icon brushes for every Nexus tool.
	 */
	inline TSharedPtr<FSlateBrush> IconBrush(UObject* Texture)
	{
		if (!Texture)
		{
			return nullptr;
		}
		TSharedPtr<FSlateBrush> Brush = MakeShared<FSlateBrush>();
		Brush->SetResourceObject(Texture);
		Brush->DrawAs = ESlateBrushDrawType::Image;
		Brush->ImageSize = FVector2D(64.0f, 64.0f);
		return Brush;
	}

	/** A single padded, eliding table cell with a full-value tooltip. */
	inline TSharedRef<SWidget> Cell(
		const FString& Text,
		const FSlateColor& Color = FSlateColor::UseForeground(),
		const FString& Tooltip = FString())
	{
		return SNew(SBox)
			.Padding(FMargin(6.0f, 2.0f))
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Text))
				.ColorAndOpacity(Color)
				.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
				.ToolTipText(FText::FromString(Tooltip.IsEmpty() ? Text : Tooltip))
			];
	}
}
