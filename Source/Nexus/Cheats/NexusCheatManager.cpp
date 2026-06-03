// Fill out your copyright notice in the Description page of Project Settings.

#include "Nexus/Cheats/NexusCheatManager.h"

#include "Engine/AssetManager.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#include "Nexus/NexusAssetManager.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemContainerSubsystem.h"
#include "Nexus/Economy/NexusMerchantSubsystem.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Equipment/Attachments/NexusAssemblyComponent.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"
#include "Nexus/Combat/NexusHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogNexusCheats, Log, All);

namespace
{
	/** Echo to the log and to the player's console/HUD so a cheat gives visible feedback. */
	void Report(UNexusCheatManager* Cheat, const FString& Message)
	{
		UE_LOG(LogNexusCheats, Display, TEXT("%s"), *Message);
		if (Cheat)
		{
			if (APlayerController* PC = Cheat->GetOuterAPlayerController())
			{
				PC->ClientMessage(Message);
			}
		}
	}
}

APawn* UNexusCheatManager::GetControlledPawn() const
{
	APlayerController* PC = GetOuterAPlayerController();
	return PC ? PC->GetPawn() : nullptr;
}

UNexusItemDefinition* UNexusCheatManager::FindItemByName(const FString& NamePart) const
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Ids;
	AssetManager.GetPrimaryAssetIdList(UNexusAssetManager::TypeItemDefinition, Ids);

	UNexusItemDefinition* SubstringMatch = nullptr;
	for (const FPrimaryAssetId& Id : Ids)
	{
		const FString Name = Id.PrimaryAssetName.ToString();
		const bool bExact = Name.Equals(NamePart, ESearchCase::IgnoreCase);
		const bool bContains = Name.Contains(NamePart, ESearchCase::IgnoreCase);
		if (!bExact && !bContains)
		{
			continue;
		}

		UNexusItemDefinition* Def = Cast<UNexusItemDefinition>(AssetManager.GetPrimaryAssetPath(Id).TryLoad());
		if (!Def)
		{
			continue;
		}
		if (bExact)
		{
			return Def; // exact name beats any substring hit
		}
		if (!SubstringMatch)
		{
			SubstringMatch = Def;
		}
	}
	return SubstringMatch;
}

void UNexusCheatManager::Nexus_ListItems(const FString& Filter)
{
	UAssetManager& AssetManager = UAssetManager::Get();
	TArray<FPrimaryAssetId> Ids;
	AssetManager.GetPrimaryAssetIdList(UNexusAssetManager::TypeItemDefinition, Ids);

	if (Ids.Num() == 0)
	{
		Report(this, TEXT("No NexusItemDefinition primary assets are scanned — check the Asset Manager scan settings."));
		return;
	}

	int32 Shown = 0;
	for (const FPrimaryAssetId& Id : Ids)
	{
		const FString Name = Id.PrimaryAssetName.ToString();
		if (Filter.IsEmpty() || Name.Contains(Filter, ESearchCase::IgnoreCase))
		{
			UE_LOG(LogNexusCheats, Display, TEXT("  %s"), *Name);
			++Shown;
		}
	}
	Report(this, FString::Printf(TEXT("%d item(s) listed in the log%s."),
		Shown, Filter.IsEmpty() ? TEXT("") : *FString::Printf(TEXT(" matching '%s'"), *Filter)));
}

void UNexusCheatManager::Nexus_GiveItem(const FString& NamePart, int32 Count)
{
	APawn* Pawn = GetControlledPawn();
	if (!Pawn)
	{
		Report(this, TEXT("GiveItem: no controlled pawn."));
		return;
	}

	UNexusItemDefinition* Def = FindItemByName(NamePart);
	if (!Def)
	{
		Report(this, FString::Printf(TEXT("GiveItem: no item matching '%s' (try Nexus_ListItems)."), *NamePart));
		return;
	}

	FNexusAcquireParams Params;
	Params.bSkipCeremony = true; // silent give — no cinematic first-acquire flourish

	const int32 Want = FMath::Max(1, Count);
	const FNexusAcquireResult Result = UNexusInventoryAcquireLibrary::AcquireItem(Pawn, Def, Want, Params);

	Report(this, FString::Printf(TEXT("Gave %s x%d  (added %d, remainder %d)."),
		*Def->GetName(), Want, Result.AmountAdded, Result.Remainder));
}

void UNexusCheatManager::Nexus_AddCurrency(int32 Amount)
{
	if (UNexusItemContainerSubsystem* Container = UNexusItemContainerSubsystem::Get(this))
	{
		Container->AddCurrency(Amount);
		Report(this, FString::Printf(TEXT("Currency: %d (%+d)."), Container->GetCurrency(), Amount));
	}
	else
	{
		Report(this, TEXT("AddCurrency: no item-container subsystem."));
	}
}

void UNexusCheatManager::Nexus_Currency()
{
	if (UNexusItemContainerSubsystem* Container = UNexusItemContainerSubsystem::Get(this))
	{
		Report(this, FString::Printf(TEXT("Currency: %d."), Container->GetCurrency()));
	}
}

void UNexusCheatManager::Nexus_Heal()
{
	APawn* Pawn = GetControlledPawn();
	if (!Pawn)
	{
		Report(this, TEXT("Heal: no controlled pawn."));
		return;
	}

	if (UNexusHealthComponent* Health = Pawn->FindComponentByClass<UNexusHealthComponent>())
	{
		Health->Heal(Health->GetMaxHealth());
		Report(this, FString::Printf(TEXT("Healed to %g / %g."), Health->GetHealth(), Health->GetMaxHealth()));
	}
	else
	{
		Report(this, TEXT("Heal: pawn has no health component."));
	}
}

void UNexusCheatManager::Nexus_MaxUpgradeEquipped()
{
	APawn* Pawn = GetControlledPawn();
	if (!Pawn)
	{
		Report(this, TEXT("MaxUpgrade: no controlled pawn."));
		return;
	}

	UNexusEquipmentComponent* Equipment = Pawn->FindComponentByClass<UNexusEquipmentComponent>();
	if (!Equipment)
	{
		Report(this, TEXT("MaxUpgrade: pawn has no equipment component."));
		return;
	}

	UNexusItemInstance* Instance = Equipment->GetActiveInstance();
	UNexusItemDefinition* Def = Instance ? Instance->GetDefinition() : nullptr;
	const FNexusFragment_Weapon* Weapon = Def ? Def->FindFragment<FNexusFragment_Weapon>() : nullptr;
	if (!Instance || !Weapon)
	{
		Report(this, TEXT("MaxUpgrade: no active weapon (draw a weapon first)."));
		return;
	}

	// Refresh the live weapon (mesh/stats) as each tier applies, if it's drawn.
	UNexusAssemblyComponent* Assembly = nullptr;
	if (ANexusEquippedActor* Actor = Equipment->GetActiveActor())
	{
		Assembly = Actor->FindComponentByClass<UNexusAssemblyComponent>();
	}

	UNexusMerchantSubsystem* Merchant = UNexusMerchantSubsystem::Get(this);
	if (!Merchant)
	{
		Report(this, TEXT("MaxUpgrade: no merchant subsystem."));
		return;
	}

	int32 Applied = 0;
	for (const FNexusWeaponUpgradeTrack& Track : Weapon->UpgradeTracks)
	{
		if (!Track.StatTag.IsValid())
		{
			continue;
		}

		// Walk the track to its cap, applying each tier's delta for free (Cost 0).
		int32 Guard = 0;
		while (Guard++ < 64)
		{
			const FNexusWeaponUpgradeState State = Merchant->GetUpgradeState(Instance, Track.StatTag);
			if (State.MaxTier == 0 || State.bAtCap)
			{
				break;
			}
			Merchant->UpgradeInstanceStat(Instance, Track.StatTag, State.NextValue - State.CurrentValue, /*Cost=*/ 0, Assembly);
			++Applied;
		}
	}

	Report(this, FString::Printf(TEXT("Maxed %s: applied %d tier(s) across %d track(s)."),
		*Def->GetName(), Applied, Weapon->UpgradeTracks.Num()));
}
