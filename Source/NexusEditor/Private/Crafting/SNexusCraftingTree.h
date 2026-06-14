#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"

class ITableRow;
class STableViewBase;
class SWidget;
class UNexusItemDefinition;
class UNexusCombinationRecipe;
class FNexusAssetWatcher;

/**
 * The Nexus Crafting Tree: every craftable item as a root, expandable to show what it's
 * made from (its recipe's inputs), recursively — so you can read a full crafting chain
 * (gunpowder + resource → ammo) at a glance. Cycles and runaway depth are guarded.
 * Double-click a node to open its recipe (or the item).
 */
class SNexusCraftingTree : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusCraftingTree) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	struct FCraftNode
	{
		TWeakObjectPtr<UNexusItemDefinition> Item;
		TWeakObjectPtr<UNexusCombinationRecipe> Recipe; // the recipe that produces Item, if any
		int32 Count = 1;
		bool bCycle = false;
		/** True when this node is one alternative recipe under an item with several producers. */
		bool bRecipeVariant = false;
		/** Number of recipes that produce Item (>1 means the item fans out into variant nodes). */
		int32 RecipeCount = 0;
		/** Label for a recipe-variant node ("via: Gunpowder + Casing"). */
		FString VariantLabel;
		TArray<TSharedPtr<FCraftNode>> Children;
	};

	void Rebuild();
	TSharedPtr<FCraftNode> BuildNode(
		UNexusItemDefinition* Item, int32 Count,
		const TMap<UNexusItemDefinition*, TArray<UNexusCombinationRecipe*>>& OutputToRecipes,
		TSet<UNexusItemDefinition*>& AncestorPath, int32 Depth);
	/** Build the input children of Recipe under OutNode (shared by single- and multi-recipe paths). */
	void BuildRecipeInputs(
		TSharedPtr<FCraftNode>& OutNode, UNexusCombinationRecipe* Recipe,
		const TMap<UNexusItemDefinition*, TArray<UNexusCombinationRecipe*>>& OutputToRecipes,
		TSet<UNexusItemDefinition*>& AncestorPath, int32 Depth);

	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FCraftNode> Node, const TSharedRef<STableViewBase>& Owner);
	void OnGetChildren(TSharedPtr<FCraftNode> Node, TArray<TSharedPtr<FCraftNode>>& OutChildren);
	void OnNodeDoubleClicked(TSharedPtr<FCraftNode> Node);
	FReply OnRefreshClicked();
	FReply OnNewRecipeClicked();
	FText GetSummaryText() const;

	TArray<TSharedPtr<FCraftNode>> RootNodes;
	TSharedPtr<STreeView<TSharedPtr<FCraftNode>>> TreeView;
	FText SummaryText;

	/** Live refresh when recipes or items change. */
	TSharedPtr<FNexusAssetWatcher> Watcher;
};
