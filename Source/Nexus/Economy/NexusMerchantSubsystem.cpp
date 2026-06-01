#include "NexusMerchantSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemContainerSubsystem.h"
#include "Nexus/Inventory/NexusItemEconomyLibrary.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"

UNexusMerchantSubsystem* UNexusMerchantSubsystem::Get(const UObject* WorldContext)
{
	if (!WorldContext || !GEngine) return nullptr;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			return GI->GetSubsystem<UNexusMerchantSubsystem>();
		}
	}
	return nullptr;
}


// Pricing
int32 UNexusMerchantSubsystem::GetSellPrice(const UNexusItemInstance* Instance, int32 Count) const
{
	if (!Instance) return 0;
	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition || !Definition->bSellable) return 0;

	// A fungible stack prices per unit; a customized/socketed instance prices whole (its
	// sockets are part of the one indivisible item).
	if (Instance->IsMergeableStack())
	{
		const int32 Units = FMath::Clamp(Count, 1, Instance->GetStackCount());
		return Definition->BaseValue * Units;
	}
	return UNexusItemEconomyLibrary::GetSellValue(Instance);
}

int32 UNexusMerchantSubsystem::GetBuyPrice(const UNexusItemDefinition* Definition, int32 Count) const
{
	if (!Definition || !Definition->bBuyable || Count <= 0) return 0;
	return Definition->BaseValue * Count;
}


// Transactions
bool UNexusMerchantSubsystem::SellInstance(UNexusInventoryComponent* PlayerInventory, UNexusItemInstance* Instance, int32 Count)
{
	if (!PlayerInventory || !Instance) return false;
	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	if (!Definition || !Definition->bSellable) return false;
	if (!PlayerInventory->GetItems().Contains(Instance)) return false;

	UNexusItemContainerSubsystem* Wallet = UNexusItemContainerSubsystem::Get(this);
	if (!Wallet) return false;

	if (Instance->IsMergeableStack())
	{
		const int32 Units   = FMath::Clamp(Count, 1, Instance->GetStackCount());
		const int32 Removed = PlayerInventory->RemoveFromInstance(Instance, Units);
		if (Removed <= 0) return false;
		Wallet->AddCurrency(Definition->BaseValue * Removed);
		return true;
	}

	// Customized / socketed: sell the whole instance at its combined value.
	const int32 Price = UNexusItemEconomyLibrary::GetSellValue(Instance);
	if (!PlayerInventory->RemoveInstance(Instance)) return false;
	Wallet->AddCurrency(Price);
	return true;
}

bool UNexusMerchantSubsystem::BuyDefinition(UNexusInventoryComponent* PlayerInventory, UNexusItemDefinition* Definition, int32 Count)
{
	if (!PlayerInventory || !Definition || Count <= 0) return false;
	if (!Definition->bBuyable) return false;

	UNexusItemContainerSubsystem* Wallet = UNexusItemContainerSubsystem::Get(this);
	if (!Wallet) return false;

	APawn* Pawn = Cast<APawn>(PlayerInventory->GetOwner());
	if (!Pawn) return false;

	const int32 UnitPrice  = Definition->BaseValue;
	const int32 Affordable = UnitPrice > 0 ? (Wallet->GetCurrency() / UnitPrice) : Count;
	const int32 CanFit     = PlayerInventory->GetRemainingCapacityForDefinition(Definition);
	const int32 ToBuy      = FMath::Min3(Count, Affordable, CanFit);
	if (ToBuy <= 0) return false;

	// Give through the one acquire façade, then charge only for what actually landed.
	FNexusAcquireParams Params;
	Params.bAutoEquipIfPossible = false;
	const FNexusAcquireResult Result = UNexusInventoryAcquireLibrary::AcquireItem(Pawn, Definition, ToBuy, Params);
	if (Result.AmountAdded <= 0) return false;

	Wallet->SpendCurrency(UnitPrice * Result.AmountAdded);
	return true;
}

bool UNexusMerchantSubsystem::UpgradeInstanceStat(UNexusItemInstance* Instance, FGameplayTag StatTag, float Delta, int32 Cost)
{
	if (!Instance || !StatTag.IsValid()) return false;

	UNexusItemContainerSubsystem* Wallet = UNexusItemContainerSubsystem::Get(this);
	if (!Wallet) return false;

	if (!Wallet->SpendCurrency(Cost)) return false;

	// Persistent instance stat tag: saves + broadcasts automatically (no new storage).
	Instance->ModifyStat(StatTag, Delta);
	return true;
}
