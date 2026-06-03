#pragma once

#include "CoreMinimal.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateColor.h"
#include "Widgets/SWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

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
