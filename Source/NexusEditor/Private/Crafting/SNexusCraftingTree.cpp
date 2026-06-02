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

#define LOCTEXT_NAMESPACE "NexusCraftingTree"

namespace
{
	constexpr int32 MaxDepth = 16;

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
		for (const FAssetData& Data : Assets)
		{
			if (T* Object = Cast<T>(Data.GetAsset())) { Out.Add(Object); }
		}
	}

	FString NodeLabel(const UNexusItemDefinition* Item, int32 Count, bool bCycle)
	{
		const FString Name = (Item && !Item->DisplayName.IsEmpty())
			? Item->DisplayName.ToString()
			: (Item ? Item->GetName() : TEXT("(none)"));
		FString Text = FString::Printf(TEXT("%d x  %s"), Count, *Name);
		if (bCycle) { Text += TEXT("   (cycle — stopped)"); }
		return Text;
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
}

void SNexusCraftingTree::Rebuild()
{
	RootNodes.Reset();

	TArray<UNexusCombinationRecipe*> Recipes;
	GatherAssets(Recipes);

	// First recipe that produces each item (multiple producers: first wins).
	TMap<UNexusItemDefinition*, UNexusCombinationRecipe*> OutputToRecipe;
	for (UNexusCombinationRecipe* Recipe : Recipes)
	{
		if (Recipe && Recipe->Output && !OutputToRecipe.Contains(Recipe->Output))
		{
			OutputToRecipe.Add(Recipe->Output, Recipe);
		}
	}

	// One root per craftable output.
	for (const TPair<UNexusItemDefinition*, UNexusCombinationRecipe*>& Pair : OutputToRecipe)
	{
		TSet<UNexusItemDefinition*> AncestorPath;
		const int32 Count = Pair.Value ? Pair.Value->OutputCount : 1;
		RootNodes.Add(BuildNode(Pair.Key, Count, OutputToRecipe, AncestorPath, 0));
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
	const TMap<UNexusItemDefinition*, UNexusCombinationRecipe*>& OutputToRecipe,
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

	if (UNexusCombinationRecipe* const* RecipePtr = OutputToRecipe.Find(Item))
	{
		UNexusCombinationRecipe* Recipe = *RecipePtr;
		Node->Recipe = Recipe;

		AncestorPath.Add(Item);
		for (const FNexusRecipeInput& Input : Recipe->Inputs)
		{
			if (Input.Definition)
			{
				Node->Children.Add(BuildNode(Input.Definition, Input.Count, OutputToRecipe, AncestorPath, Depth + 1));
			}
		}
		AncestorPath.Remove(Item);
	}

	return Node;
}

TSharedRef<ITableRow> SNexusCraftingTree::OnGenerateRow(
	TSharedPtr<FCraftNode> Node, const TSharedRef<STableViewBase>& Owner)
{
	TSharedRef<STableRow<TSharedPtr<FCraftNode>>> Row =
		SNew(STableRow<TSharedPtr<FCraftNode>>, Owner);

	const FSlateColor Color = (Node.IsValid() && Node->bCycle)
		? FSlateColor(FStyleColors::Warning) : FSlateColor::UseForeground();

	Row->SetContent(
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
		[ SNew(SExpanderArrow, Row) ]
		+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(2.0f, 2.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Node.IsValid()
				? NodeLabel(Node->Item.Get(), Node->Count, Node->bCycle) : FString()))
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
		TEXT("/Game/Nexus/Blueprint/Data/Recipes"), TEXT("NewRecipe"), SeedOutput, Error);
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
