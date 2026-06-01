#include "NexusItemCombinationSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemEconomyLibrary.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"

UNexusItemCombinationSubsystem* UNexusItemCombinationSubsystem::Get(const UObject* WorldContext)
{
	if (!WorldContext || !GEngine) return nullptr;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			return GI->GetSubsystem<UNexusItemCombinationSubsystem>();
		}
	}
	return nullptr;
}

bool UNexusItemCombinationSubsystem::CanCraft(const UNexusInventoryComponent* Inventory, const UNexusCombinationRecipe* Recipe) const
{
	if (!Inventory || !Recipe || Recipe->Inputs.Num() == 0) return false;

	for (const FNexusRecipeInput& Input : Recipe->Inputs)
	{
		if (!Input.Definition || Input.Count <= 0) return false;
		if (Inventory->GetTotalCountForDefinition(Input.Definition) < Input.Count) return false;
	}
	return true;
}

bool UNexusItemCombinationSubsystem::Craft(UNexusInventoryComponent* Inventory, const UNexusCombinationRecipe* Recipe)
{
	if (!CanCraft(Inventory, Recipe)) return false;

	// Consume every input (CanCraft already verified availability).
	for (const FNexusRecipeInput& Input : Recipe->Inputs)
	{
		ConsumeCountOfDefinition(Inventory, Input.Definition, Input.Count);
	}

	// Produce the output through the one acquire façade.
	if (Recipe->Output && Recipe->OutputCount > 0)
	{
		if (APawn* Pawn = Cast<APawn>(Inventory->GetOwner()))
		{
			FNexusAcquireParams Params;
			Params.bAutoEquipIfPossible = false;
			UNexusInventoryAcquireLibrary::AcquireItem(Pawn, Recipe->Output, Recipe->OutputCount, Params);
		}
	}
	return true;
}

bool UNexusItemCombinationSubsystem::CombineGemIntoTreasure(UNexusInventoryComponent* Inventory,
	UNexusItemInstance* Treasure, FGameplayTag SocketTag, UNexusItemDefinition* GemDef)
{
	if (!Inventory || !Treasure || !GemDef) return false;

	// Validate before consuming so a rejected socket never eats the gem.
	if (!UNexusItemEconomyLibrary::CanSocketGem(Treasure, SocketTag, GemDef)) return false;
	if (ConsumeCountOfDefinition(Inventory, GemDef, 1) < 1) return false;

	return UNexusItemEconomyLibrary::SocketGem(Treasure, SocketTag, GemDef);
}

int32 UNexusItemCombinationSubsystem::ConsumeCountOfDefinition(UNexusInventoryComponent* Inventory,
	const UNexusItemDefinition* Definition, int32 Count)
{
	if (!Inventory || !Definition || Count <= 0) return 0;

	int32 Remaining = Count;
	// Snapshot: RemoveFromInstance mutates the live Items array, so iterate a copy.
	TArray<UNexusItemInstance*> Snapshot = Inventory->GetItems();
	for (UNexusItemInstance* Instance : Snapshot)
	{
		if (Remaining <= 0) break;
		if (!Instance || Instance->GetDefinition() != Definition) continue;
		Remaining -= Inventory->RemoveFromInstance(Instance, Remaining);
	}
	return Count - Remaining;
}
