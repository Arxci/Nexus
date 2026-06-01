#include "NexusItemEconomyLibrary.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Treasure/NexusFragment_Treasure.h"

int32 UNexusItemEconomyLibrary::GetSellValue(const UNexusItemInstance* Instance)
{
	if (!Instance) return 0;
	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition) return 0;

	int32 Value = Definition->BaseValue * FMath::Max(1, Instance->GetStackCount());

	// Treasures add the value of their socketed gems, plus a completion bonus when full.
	if (const FNexusFragment_Treasure* Treasure = Definition->FindFragment<FNexusFragment_Treasure>())
	{
		int32 Filled = 0;
		for (const FNexusTreasureSocket& Socket : Treasure->Sockets)
		{
			const TSoftObjectPtr<UNexusItemDefinition> GemRef = Instance->GetSocketedItem(Socket.SocketTag);
			if (GemRef.IsNull()) continue;

			++Filled;
			// Sync load: value queries run in menus / save rooms; gems are light data assets.
			if (const UNexusItemDefinition* Gem = GemRef.LoadSynchronous())
			{
				Value += Gem->BaseValue;
			}
		}
		if (Treasure->Sockets.Num() > 0 && Filled == Treasure->Sockets.Num())
		{
			Value += Treasure->FullSocketBonus;
		}
	}

	return Value;
}

int32 UNexusItemEconomyLibrary::GetUnitValue(const UNexusItemDefinition* Definition)
{
	return Definition ? Definition->BaseValue : 0;
}

bool UNexusItemEconomyLibrary::IsSellable(const UNexusItemDefinition* Definition)
{
	return Definition && Definition->bSellable;
}

bool UNexusItemEconomyLibrary::IsBuyable(const UNexusItemDefinition* Definition)
{
	return Definition && Definition->bBuyable;
}

bool UNexusItemEconomyLibrary::CanSocketGem(const UNexusItemInstance* Treasure, FGameplayTag SocketTag,
	const UNexusItemDefinition* GemDef)
{
	if (!Treasure || !GemDef || !SocketTag.IsValid()) return false;

	const UNexusItemDefinition* TreasureDef = Treasure->GetDefinition();
	const FNexusFragment_Treasure* Frag = TreasureDef
		? TreasureDef->FindFragment<FNexusFragment_Treasure>() : nullptr;
	if (!Frag) return false;

	const FNexusTreasureSocket* Socket = Frag->Sockets.FindByPredicate(
		[SocketTag](const FNexusTreasureSocket& S) { return S.SocketTag.MatchesTagExact(SocketTag); });
	if (!Socket) return false;

	// The socket must be empty.
	if (!Treasure->GetSocketedItem(SocketTag).IsNull()) return false;

	// The gem must satisfy the socket's accepted category (empty = accepts anything).
	if (Socket->AcceptedGemCategory.IsValid()
		&& !GemDef->CategoryTags.HasTag(Socket->AcceptedGemCategory))
	{
		return false;
	}
	return true;
}

bool UNexusItemEconomyLibrary::SocketGem(UNexusItemInstance* Treasure, FGameplayTag SocketTag, UNexusItemDefinition* GemDef)
{
	if (!CanSocketGem(Treasure, SocketTag, GemDef)) return false;
	Treasure->SetSocketedItem(SocketTag, TSoftObjectPtr<UNexusItemDefinition>(GemDef));
	return true;
}
