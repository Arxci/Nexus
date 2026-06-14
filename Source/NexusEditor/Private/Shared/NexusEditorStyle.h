#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateColor.h"
#include "Styling/StyleColors.h"

/**
 * The Nexus tools' shared colour vocabulary — one place every tool reads its semantic
 * colours from, so "valid" is the same green, "conflicts" the same red, and a category
 * tints the same way in the dashboard, the grid, and the sandbox.
 *
 * Header-only inlines: include and use. Pair with NexusEditorWidgets.h (the matching
 * widget kit — chips, empty-states, toolbar bands).
 */
namespace NexusEditorStyle
{
	// --- Validity --------------------------------------------------------------
	inline FSlateColor Valid()    { return FStyleColors::Success; }
	inline FSlateColor Warning()  { return FStyleColors::Warning; }
	inline FSlateColor Error()    { return FStyleColors::Error; }
	inline FSlateColor Neutral()  { return FSlateColor::UseForeground(); }
	inline FSlateColor Subdued()  { return FSlateColor::UseSubduedForeground(); }

	// --- Attachment graph: Provides / Requires / Conflicts ---------------------
	// (Matches the Attachment Matrix's long-standing P / R / C colouring.)
	inline FSlateColor Provides()  { return FStyleColors::AccentGreen; }
	inline FSlateColor Requires()  { return FStyleColors::AccentBlue; }
	inline FSlateColor Conflicts() { return FStyleColors::Error; }

	/** Accent for weapon items (matches the Grid / Economy weapon highlight). */
	inline FSlateColor Weapon() { return FStyleColors::AccentBlue; }

	/** Last segment of a dotted tag string ("Item.Category.Weapon" -> "Weapon"), lower-cased. */
	inline FString StyleTagLeaf(const FString& TagString)
	{
		int32 Dot = INDEX_NONE;
		const FString Leaf = TagString.FindLastChar(TEXT('.'), Dot) ? TagString.RightChop(Dot + 1) : TagString;
		return Leaf.ToLower();
	}

	/**
	 * Stable colour for an item category leaf ("Weapon", "Consumable", ...). A handful of
	 * known categories get hand-picked hues; anything else gets a stable hash-based hue so
	 * new categories still read as distinct without a code change.
	 */
	inline FLinearColor CategoryColor(const FString& Leaf)
	{
		const FString L = Leaf.ToLower();
		if (L.Contains(TEXT("weapon")))     { return FLinearColor(0.30f, 0.55f, 0.95f); } // blue
		if (L.Contains(TEXT("consumable"))) { return FLinearColor(0.35f, 0.80f, 0.45f); } // green
		if (L.Contains(TEXT("ammo")))       { return FLinearColor(0.95f, 0.65f, 0.25f); } // orange
		if (L.Contains(TEXT("treasure")))   { return FLinearColor(0.95f, 0.82f, 0.30f); } // gold
		if (L.Contains(TEXT("key")))        { return FLinearColor(0.70f, 0.45f, 0.90f); } // purple
		if (L.Contains(TEXT("charm")))      { return FLinearColor(0.95f, 0.45f, 0.70f); } // pink

		// Stable hash-based hue fallback so unknown categories stay visually distinct.
		const uint32 Hash = GetTypeHash(L);
		const uint8 Hue = static_cast<uint8>(Hash % 256);
		return FLinearColor::MakeFromHSV8(Hue, 150, 220);
	}

	/** Convenience: colour for a category tag string (handles the leaf extraction). */
	inline FLinearColor CategoryColorForTag(const FString& CategoryTagString)
	{
		return CategoryColor(StyleTagLeaf(CategoryTagString));
	}

	/**
	 * Colour for a rarity tier 0..4 (Common, Uncommon, Rare, Epic, Legendary). The runtime
	 * has no rarity field yet, so this is forward-looking — tools that derive a tier (or
	 * fall back to CategoryColor) can frame items consistently when one lands.
	 */
	inline FLinearColor RarityColor(int32 Tier)
	{
		switch (FMath::Clamp(Tier, 0, 4))
		{
		case 0:  return FLinearColor(0.62f, 0.62f, 0.62f); // common — gray
		case 1:  return FLinearColor(0.35f, 0.80f, 0.45f); // uncommon — green
		case 2:  return FLinearColor(0.30f, 0.55f, 0.95f); // rare — blue
		case 3:  return FLinearColor(0.70f, 0.45f, 0.90f); // epic — purple
		default: return FLinearColor(0.95f, 0.72f, 0.25f); // legendary — gold
		}
	}
}
