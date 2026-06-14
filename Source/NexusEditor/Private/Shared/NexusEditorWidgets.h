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

	/** Panel band used to wrap a tool's toolbar row, so every tool's toolbar sits the same. */
	inline TSharedRef<SWidget> Toolbar(const TSharedRef<SWidget>& Content)
	{
		return SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
			.Padding(FMargin(10.0f, 6.0f))
			[
				Content
			];
	}

	/** Centred, subdued, wrapping prompt for "nothing here yet" states. */
	inline TSharedRef<SWidget> EmptyState(const FText& Message)
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Padding(24.0f)
			[
				SNew(STextBlock)
				.Text(Message)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
				.AutoWrapText(true)
				.Justification(ETextJustify::Center)
			];
	}

	/**
	 * A small tinted pill for a tag / flag / status word. Pass a semantic colour
	 * (NexusEditorStyle::Provides(), CategoryColor(...), ...); the fill is a translucent
	 * wash of it and the text is the solid colour.
	 */
	inline TSharedRef<SWidget> Chip(const FText& Text, const FLinearColor& Color)
	{
		return SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("WhiteBrush"))
			.BorderBackgroundColor(FLinearColor(Color.R, Color.G, Color.B, 0.18f))
			.Padding(FMargin(6.0f, 1.0f))
			[
				SNew(STextBlock)
				.Text(Text)
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 8))
				.ColorAndOpacity(FSlateColor(Color))
			];
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
