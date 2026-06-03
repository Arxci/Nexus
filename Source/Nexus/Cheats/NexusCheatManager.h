// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "NexusCheatManager.generated.h"

class UNexusItemDefinition;

/**
 * Dev/QA cheat console for Nexus. Wired in by setting
 * ANexusPlayerController::CheatClass = UNexusCheatManager::StaticClass() (see the
 * integration note). UCheatManager is only instantiated when cheats are enabled
 * (PIE, or `EnableCheats`), so none of this reaches a shipping player.
 *
 * Everything goes through the real runtime façades — UNexusInventoryAcquireLibrary,
 * UNexusMerchantSubsystem, UNexusItemContainerSubsystem — so a cheat exercises the
 * same paths as real gameplay (and can't drift into a parallel give/equip flow).
 *
 * Console (backtick) examples:
 *   Nexus_ListItems handgun        list item definitions whose name contains "handgun"
 *   Nexus_GiveItem  handgun 1      give one matching item to the controlled pawn
 *   Nexus_AddCurrency 5000         credit the wallet
 *   Nexus_Heal                     refill the pawn's health
 *   Nexus_MaxUpgradeEquipped       buy every upgrade tier on the active weapon, free
 */
UCLASS()
class NEXUS_API UNexusCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	/** List item definitions whose asset name contains Filter (empty = all). Discovery aid for GiveItem. */
	UFUNCTION(Exec)
	void Nexus_ListItems(const FString& Filter);

	/** Give Count of the item whose name best matches NamePart to the controlled pawn. */
	UFUNCTION(Exec)
	void Nexus_GiveItem(const FString& NamePart, int32 Count = 1);

	/** Credit Amount to the currency wallet. */
	UFUNCTION(Exec)
	void Nexus_AddCurrency(int32 Amount);

	/** Print the current wallet balance. */
	UFUNCTION(Exec)
	void Nexus_Currency();

	/** Refill the controlled pawn's health to max. */
	UFUNCTION(Exec)
	void Nexus_Heal();

	/** Buy every upgrade tier on every track of the active weapon, for free. */
	UFUNCTION(Exec)
	void Nexus_MaxUpgradeEquipped();

private:
	/** Best item-definition match for NamePart (exact name wins over a substring), or null. */
	UNexusItemDefinition* FindItemByName(const FString& NamePart) const;

	/** The pawn the cheating player currently controls, or null. */
	APawn* GetControlledPawn() const;
};
