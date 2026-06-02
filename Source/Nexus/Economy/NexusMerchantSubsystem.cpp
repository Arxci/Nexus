#include "NexusMerchantSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "GameFramework/Pawn.h"

#include "Nexus/Equipment/Attachments/NexusAssemblyComponent.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemContainerSubsystem.h"
#include "Nexus/Inventory/NexusItemEconomyLibrary.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"

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

bool UNexusMerchantSubsystem::UpgradeInstanceStat(UNexusItemInstance* Instance, FGameplayTag StatTag,
	float Delta, int32 Cost, UNexusAssemblyComponent* LiveAssembly)
{
	if (!Instance || !StatTag.IsValid()) return false;

	UNexusItemContainerSubsystem* Wallet = UNexusItemContainerSubsystem::Get(this);
	if (!Wallet) return false;

	if (!Wallet->SpendCurrency(Cost)) return false;

	// Persistent instance stat tag: saves + broadcasts automatically (no new
	// storage) and folds into the effective-stat resolution as a final additive tier.
	Instance->ModifyStat(StatTag, Delta);

	// On a live (equipped) weapon, poke the assembly so GetEffectiveStat reflects
	// the tune-up immediately — no respawn. The instance broadcast above doesn't
	// invalidate the assembly's stat cache (that's deliberately off the per-shot
	// ammo path), so the merchant signals it explicitly here.
	if (LiveAssembly)
	{
		LiveAssembly->NotifyUpgradesChanged();
	}
	return true;
}


// Attachments
bool UNexusMerchantSubsystem::InstallAttachment(UNexusAssemblyComponent* Assembly, FGameplayTag SlotID,
	UNexusAttachmentDefinition* Definition, int32 Cost)
{
	if (!Assembly || !Definition || !SlotID.IsValid()) return false;

	// Compatibility + cross-slot constraints gate the purchase before any charge.
	if (!Assembly->CanAttachItem(SlotID, Definition)) return false;

	UNexusItemContainerSubsystem* Wallet = UNexusItemContainerSubsystem::Get(this);
	if (!Wallet) return false;
	if (Cost > 0 && !Wallet->SpendCurrency(Cost)) return false;

	// Public assembly API: persists the choice to the instance and updates the live
	// weapon (mesh + stats + montage overrides) without a respawn. Source defaults
	// to PlayerAction, so it persists.
	if (!Assembly->AttachItem(SlotID, Definition))
	{
		if (Cost > 0) Wallet->AddCurrency(Cost); // refund — unreachable after CanAttachItem, defensive
		return false;
	}
	return true;
}

bool UNexusMerchantSubsystem::UninstallAttachment(UNexusAssemblyComponent* Assembly, FGameplayTag SlotID)
{
	if (!Assembly) return false;
	// Merchant-unlock model: removal is free and returns nothing to inventory.
	return Assembly->DetachItem(SlotID);
}


// Upgrades
FNexusWeaponUpgradeState UNexusMerchantSubsystem::GetUpgradeState(
	const UNexusItemInstance* Instance, FGameplayTag StatTag) const
{
	FNexusWeaponUpgradeState State;
	State.StatTag = StatTag;
	if (!Instance || !StatTag.IsValid()) return State;

	const UNexusItemDefinition* Definition = Instance->GetDefinition();
	const FNexusFragment_Weapon* Weapon = Definition ? Definition->FindFragment<FNexusFragment_Weapon>() : nullptr;
	const FNexusWeaponUpgradeTrack* Track = Weapon ? Weapon->FindUpgradeTrack(StatTag) : nullptr;
	if (!Track || Track->Tiers.Num() == 0) return State;

	State.MaxTier      = Track->Tiers.Num();
	State.CurrentValue = Instance->GetStat(StatTag, 0.0f);

	// Current tier = highest tier whose cumulative Value the stored delta has
	// reached (tiers authored with strictly increasing Value).
	int32 Level = 0;
	for (int32 i = 0; i < Track->Tiers.Num(); ++i)
	{
		if (State.CurrentValue + KINDA_SMALL_NUMBER >= Track->Tiers[i].Value) Level = i + 1;
		else break;
	}
	State.CurrentTier = Level;
	State.bAtCap      = (Level >= Track->Tiers.Num());

	if (!State.bAtCap)
	{
		State.NextCost  = Track->Tiers[Level].Cost;
		State.NextValue = Track->Tiers[Level].Value;
	}
	else
	{
		State.NextValue = State.CurrentValue;
	}
	return State;
}

bool UNexusMerchantSubsystem::PurchaseNextUpgradeTier(UNexusItemInstance* Instance, FGameplayTag StatTag,
	UNexusAssemblyComponent* LiveAssembly)
{
	const FNexusWeaponUpgradeState State = GetUpgradeState(Instance, StatTag);
	if (State.MaxTier == 0 || State.bAtCap) return false; // no track / already maxed (cap)

	// Apply only the step from the current cumulative value to the next tier's.
	const float Delta = State.NextValue - State.CurrentValue;
	return UpgradeInstanceStat(Instance, StatTag, Delta, State.NextCost, LiveAssembly);
}
