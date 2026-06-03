#pragma once

#include "CoreMinimal.h"
#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"

/**
 * Shared editor-only helpers, extracted so the audit, dashboard, creator, preview,
 * crafting tree, attachment matrix, CSV round-trip, and the new designer tools all
 * call ONE implementation instead of carrying their own copy.
 *
 * Before this header the project had ~5 copies of GatherAssets<T>, ~4 copies of the
 * tag-leaf helper, and ~3 copies of the weapon-fragment finder. Centralising them
 * mirrors the design choice already made for FNexusContentAudit / FNexusStatResolver:
 * one source of truth so the tools can't drift from each other.
 *
 * Header-only on purpose: every function is a template or a trivial inline, so there
 * is nothing to link and any tool can include it freely.
 */
namespace NexusEditorUtil
{
	/**
	 * Load every asset of class T (and subclasses) the asset registry knows about.
	 * Appends to Out so a caller can accumulate across several types. Synchronous —
	 * this is the editor-side "scan all content" primitive every Nexus tool uses.
	 */
	template <typename T>
	void GatherAssets(TArray<T*>& Out)
	{
		const IAssetRegistry& AssetRegistry =
			FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

		FARFilter Filter;
		Filter.ClassPaths.Add(T::StaticClass()->GetClassPathName());
		Filter.bRecursiveClasses = true;

		TArray<FAssetData> Assets;
		AssetRegistry.GetAssets(Filter, Assets);

		Out.Reserve(Out.Num() + Assets.Num());
		for (const FAssetData& Data : Assets)
		{
			if (T* Obj = Cast<T>(Data.GetAsset()))
			{
				Out.Add(Obj);
			}
		}
	}

	/** Last segment of a tag, e.g. Stat.Weapon.Damage -> "Damage", for compact display. */
	inline FString TagLeaf(const FGameplayTag& Tag)
	{
		const FString Full = Tag.ToString();
		int32 Dot = INDEX_NONE;
		return Full.FindLastChar(TEXT('.'), Dot) ? Full.RightChop(Dot + 1) : Full;
	}

	/** "%g" formatting for a stat/number cell (trims trailing zeros). */
	inline FString FormatStat(float Value)
	{
		return FString::Printf(TEXT("%g"), Value);
	}

	/** The first weapon fragment on an item, or null. Const view for read-only tools. */
	inline const FNexusFragment_Weapon* FindWeaponFragment(const UNexusItemDefinition* Item)
	{
		if (!Item)
		{
			return nullptr;
		}
		for (const TInstancedStruct<FNexusItemFragment>& Frag : Item->Fragments)
		{
			if (!Frag.IsValid())
			{
				continue;
			}
			const UScriptStruct* Type = Frag.GetScriptStruct();
			if (Type && Type->IsChildOf(FNexusFragment_Weapon::StaticStruct()))
			{
				return Frag.GetPtr<const FNexusFragment_Weapon>();
			}
		}
		return nullptr;
	}

	/** True when the item carries a weapon fragment (it's a gun/melee weapon). */
	inline bool HasWeaponFragment(const UNexusItemDefinition* Item)
	{
		return FindWeaponFragment(Item) != nullptr;
	}

	/** Display label for an item/attachment: its DisplayName, falling back to the asset name. */
	inline FString DisplayLabel(const UObject* Asset, const FText& DisplayName)
	{
		return DisplayName.IsEmpty() ? (Asset ? Asset->GetName() : FString()) : DisplayName.ToString();
	}
}
