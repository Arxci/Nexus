#include "Crafting/SNexusCraftingTree.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

#include "Editor.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SExpanderArrow.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"

#include "Creation/NexusAssetCreationLibrary.h"
#include "NexusEditorModule.h"

#include "Settings/NexusEditorSettings.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorUtils.h"

#define LOCTEXT_NAMESPACE "NexusCraftingTree"

namespace
{
	constexpr int32 MaxDepth = 16;

	FString ItemName(const UNexusItemDefinition* Item)
	{
		return (Item && !Item->DisplayName.IsEmpty())
			? Item->DisplayName.ToString()
			: (Item ? Item->GetName() : TEXT("(none)"));
	}

	/** Compact "a + b + c" summary of a recipe's inputs, for a variant node's label. */
	FString RecipeInputSummary(const UNexusCombinationRecipe* Recipe)
	{
		if (!Recipe || Recipe->Inputs.Num() == 0)
		{
			return TEXT("(no inputs)");
		}
		TArray<FString> Parts;
		for (const FNexusRecipeInput& Input : Recipe->Inputs)
		{
			if (Input.Definition)
			{
				Parts.Add(FString::Printf(TEXT("%dx %s"), Input.Count, *ItemName(Input.Definition)));
			}
		}
		return FString::Join(Parts, TEXT(" + "));
	}
}

void SNexusCraftingTree::Construct(const FArguments& InArgs)
{
	Rebuild();

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot().AutoHeight().Padding(8.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(LOCTEXT("Refresh", "Refresh"))
				.OnClicked(this, &SNexusCraftingTree::OnRefreshClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("NewRecipe", "New Recipe"))
				.ToolTipText(LOCTEXT("NewRecipeTip", "Create a recipe (output seeded from the selected node) and open it in the Creator."))
				.OnClicked(this, &SNexusCraftingTree::OnNewRecipeClicked)
			]
			+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[ SNew(STextBlock).Text(this, &SNexusCraftingTree::GetSummaryText) ]
		]

		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f, 0.0f, 8.0f, 8.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(4.0f)
			[
				SAssignNew(TreeView, STreeView<TSharedPtr<FCraftNode>>)
				.TreeItemsSource(&RootNodes)
				.OnGenerateRow(this, &SNexusCraftingTree::OnGenerateRow)
				.OnGetChildren(this, &SNexusCraftingTree::OnGetChildren)
				.OnMouseButtonDoubleClick(this, &SNexusCraftingTree::OnNodeDoubleClicked)
				.SelectionMode(ESelectionMode::Single)
			]
		]
	];

	// Live: rebuild when recipes or items change.
	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start(
		{ UNexusCombinationRecipe::StaticClass(), UNexusItemDefinition::StaticClass() },
		[this]() { Rebuild(); });
}

void SNexusCraftingTree::Rebuild()
{
	RootNodes.Reset();

	TArray<UNexusCombinationRecipe*> Recipes;
	NexusEditorUtil::GatherAssets(Recipes);

	// EVERY recipe that produces each item — alternative recipes used to be silently
	// dropped (first-wins), hiding real content. Now they all surface as variant nodes.
	TMap<UNexusItemDefinition*, TArray<UNexusCombinationRecipe*>> OutputToRecipes;
	for (UNexusCombinationRecipe* Recipe : Recipes)
	{
		if (Recipe && Recipe->Output)
		{
			OutputToRecipes.FindOrAdd(Recipe->Output).Add(Recipe);
		}
	}

	// One root per craftable output. OutputCount comes from the first recipe; multi-recipe
	// outputs show per-variant counts on their children.
	for (const TPair<UNexusItemDefinition*, TArray<UNexusCombinationRecipe*>>& Pair : OutputToRecipes)
	{
		TSet<UNexusItemDefinition*> AncestorPath;
		const int32 Count = (Pair.Value.Num() > 0 && Pair.Value[0]) ? Pair.Value[0]->OutputCount : 1;
		RootNodes.Add(BuildNode(Pair.Key, Count, OutputToRecipes, AncestorPath, 0));
	}

	RootNodes.Sort([](const TSharedPtr<FCraftNode>& A, const TSharedPtr<FCraftNode>& B)
	{
		const UNexusItemDefinition* IA = A.IsValid() ? A->Item.Get() : nullptr;
		const UNexusItemDefinition* IB = B.IsValid() ? B->Item.Get() : nullptr;
		return GetNameSafe(IA) < GetNameSafe(IB);
	});

	SummaryText = FText::Format(LOCTEXT("Summary", "{0} recipe(s), {1} craftable item(s)."),
		FText::AsNumber(Recipes.Num()), FText::AsNumber(RootNodes.Num()));

	if (TreeView.IsValid())
	{
		TreeView->RequestTreeRefresh();
	}
}

TSharedPtr<SNexusCraftingTree::FCraftNode> SNexusCraftingTree::BuildNode(
	UNexusItemDefinition* Item, int32 Count,
	const TMap<UNexusItemDefinition*, TArray<UNexusCombinationRecipe*>>& OutputToRecipes,
	TSet<UNexusItemDefinition*>& AncestorPath, int32 Depth)
{
	TSharedPtr<FCraftNode> Node = MakeShared<FCraftNode>();
	Node->Item = Item;
	Node->Count = Count;

	if (!Item || Depth >= MaxDepth || AncestorPath.Contains(Item))
	{
		Node->bCycle = (Item && AncestorPath.Contains(Item));
		return Node;
	}

	const TArray<UNexusCombinationRecipe*>* RecipesPtr = OutputToRecipes.Find(Item);
	if (!RecipesPtr || RecipesPtr->Num() == 0)
	{
		return Node; // raw / uncraftable input — a leaf
	}

	Node->RecipeCount = RecipesPtr->Num();

	if (RecipesPtr->Num() == 1)
	{
		// Single producer: inputs hang directly off the item node, as before.
		UNexusCombinationRecipe* Recipe = (*RecipesPtr)[0];
		Node->Recipe = Recipe;
		BuildRecipeInputs(Node, Recipe, OutputToRecipes, AncestorPath, Depth);
	}
	else
	{
		// Several producers: one variant child per recipe, each expandable to its inputs,
		// so a designer can compare "Ammo via Gunpowder" vs "Ammo via Saltpeter + Coal".
		for (int32 i = 0; i < RecipesPtr->Num(); ++i)
		{
			UNexusCombinationRecipe* Recipe = (*RecipesPtr)[i];
			if (!Recipe) { continue; }

			TSharedPtr<FCraftNode> Variant = MakeShared<FCraftNode>();
			Variant->Item = Item;
			Variant->Recipe = Recipe;
			Variant->bRecipeVariant = true;
			Variant->Count = Recipe->OutputCount;
			Variant->VariantLabel = FString::Printf(
				TEXT("via: %s"), *RecipeInputSummary(Recipe));
			BuildRecipeInputs(Variant, Recipe, OutputToRecipes, AncestorPath, Depth);
			Node->Children.Add(Variant);
		}
	}

	return Node;
}

void SNexusCraftingTree::BuildRecipeInputs(
	TSharedPtr<FCraftNode>& OutNode, UNexusCombinationRecipe* Recipe,
	const TMap<UNexusItemDefinition*, TArray<UNexusCombinationRecipe*>>& OutputToRecipes,
	TSet<UNexusItemDefinition*>& AncestorPath, int32 Depth)
{
	if (!OutNode.IsValid() || !Recipe)
	{
		return;
	}

	UNexusItemDefinition* Output = OutNode->Item.Get();
	if (Output) { AncestorPath.Add(Output); }
	for (const FNexusRecipeInput& Input : Recipe->Inputs)
	{
		if (Input.Definition)
		{
			OutNode->Children.Add(
				BuildNode(Input.Definition, Input.Count, OutputToRecipes, AncestorPath, Depth + 1));
		}
	}
	if (Output) { AncestorPath.Remove(Output); }
}

TSharedRef<ITableRow> SNexusCraftingTree::OnGenerateRow(
	TSharedPtr<FCraftNode> Node, const TSharedRef<STableViewBase>& Owner)
{
	TSharedRef<STableRow<TSharedPtr<FCraftNode>>> Row =
		SNew(STableRow<TSharedPtr<FCraftNode>>, Owner);

	const FSlateColor Color = (Node.IsValid() && Node->bCycle)
		? FSlateColor(FStyleColors::Warning)
		: ((Node.IsValid() && Node->bRecipeVariant)
			? FSlateColor::UseSubduedForeground()
			: FSlateColor::UseForeground());

	FString Label;
	if (Node.IsValid())
	{
		if (Node->bRecipeVariant)
		{
			// A recipe alternative under a multi-producer item.
			Label = (Node->Count > 1)
				? FString::Printf(TEXT("%s   (yields %dx)"), *Node->VariantLabel, Node->Count)
				: Node->VariantLabel;
		}
		else
		{
			Label = FString::Printf(TEXT("%d x  %s"), Node->Count, *ItemName(Node->Item.Get()));
			if (Node->RecipeCount > 1) { Label += FString::Printf(TEXT("   (%d recipes)"), Node->RecipeCount); }
			if (Node->bCycle) { Label += TEXT("   (cycle — stopped)"); }
		}
	}

	Row->SetContent(
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
		[ SNew(SExpanderArrow, Row) ]
		+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(2.0f, 2.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Label))
			.ColorAndOpacity(Color)
		]);

	return Row;
}

void SNexusCraftingTree::OnGetChildren(TSharedPtr<FCraftNode> Node, TArray<TSharedPtr<FCraftNode>>& OutChildren)
{
	if (Node.IsValid())
	{
		OutChildren = Node->Children;
	}
}

void SNexusCraftingTree::OnNodeDoubleClicked(TSharedPtr<FCraftNode> Node)
{
	if (!Node.IsValid() || !GEditor)
	{
		return;
	}
	UObject* Target = Node->Recipe.IsValid()
		? static_cast<UObject*>(Node->Recipe.Get())
		: static_cast<UObject*>(Node->Item.Get());
	if (Target)
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Target);
	}
}

FReply SNexusCraftingTree::OnRefreshClicked()
{
	Rebuild();
	return FReply::Handled();
}

FReply SNexusCraftingTree::OnNewRecipeClicked()
{
	UNexusItemDefinition* SeedOutput = nullptr;
	if (TreeView.IsValid())
	{
		const TArray<TSharedPtr<FCraftNode>> Selected = TreeView->GetSelectedItems();
		if (Selected.Num() > 0 && Selected[0].IsValid())
		{
			SeedOutput = Selected[0]->Item.Get();
		}
	}

	FText Error;
	UNexusCombinationRecipe* Recipe = FNexusAssetCreation::CreateRecipe(
		UNexusEditorSettings::Get().RecipeFolder, TEXT("NewRecipe"), SeedOutput, Error);
	if (Recipe)
	{
		FNexusEditorModule::OpenCreatorWith(Recipe);
		Rebuild();
	}
	return FReply::Handled();
}

FText SNexusCraftingTree::GetSummaryText() const
{
	return SummaryText;
}

#undef LOCTEXT_NAMESPACE
