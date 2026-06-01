#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "EMSCustomSaveGame.h"

#include "Nexus/Inventory/NexusItemInstance.h"

#include "NexusItemContainerSubsystem.generated.h"

class UNexusItemContainer;
class UNexusItemDefinition;
class UNexusItemInstance;
class UNexusInventoryComponent;


/**
 * Per-save-slot persistence blob for the item box + currency wallet. Stored through EMS's
 * custom-save system (UEMSObject::SaveCustom), scoped to the current save slot
 * (bUseSaveSlot), so it survives level transitions and is shared across every save room —
 * exactly the box's required scope, with no world actor involved.
 */
UCLASS()
class NEXUS_API UNexusItemBoxSaveGame : public UEMSCustomSaveGame
{
	GENERATED_BODY()

public:
	UNexusItemBoxSaveGame()
	{
		SaveGameName = TEXT("NexusItemBox");
		bUseSaveSlot = true; // one box per save slot
	}

	/** Flat descriptors of the box contents (same model the inventory component persists). */
	UPROPERTY()
	TArray<FNexusItemSaveData> BoxItems;

	/** The currency wallet (Pesetas/Spinels), kept at save scope alongside the box. */
	UPROPERTY()
	int32 Currency = 0;
};


/**
 * Owns the cross-container concerns the inventory leaf must not: the **item box** (a
 * subsystem-owned UNexusItemContainer that lives off any world actor, persists per save
 * slot, and is shared across save rooms), the **currency wallet**, the **stable-handle
 * resolver** across every container, and the **case-swap spill** orchestration.
 *
 * The same UNexusItemContainer class backs both the player's case and this box — they
 * differ only by section config (the box is one unlimited non-spatial list). Inventory
 * components never reference this subsystem (one-way coupling); this subsystem reaches
 * inventories through their public API and discovers them via FindComponentByClass, and
 * moves items only through the public AddInstance / RemoveInstance adoption primitives.
 *
 * Persistence is self-contained: the box lazy-loads/refreshes for the current save slot on
 * each access (EnsureBoxCurrent), and writes through on every mutation, so it stays correct
 * across new-game / load / slot-switch without depending on a particular save-manager hook.
 */
UCLASS()
class NEXUS_API UNexusItemContainerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/** Convenience accessor from any world-context object. */
	static UNexusItemContainerSubsystem* Get(const UObject* WorldContext);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Item box
	/** The item box container (refreshed for the current save slot). For UI queries / binding. */
	UFUNCTION(BlueprintPure, Category = "Inventory|Box")
	UNexusItemContainer* GetBox();

	/** Move a held instance from From's inventory into the box. Rolls back if the box refuses it. */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Box")
	bool DepositInstance(UNexusInventoryComponent* From, UNexusItemInstance* Instance);

	/** Move an instance from the box into To's inventory. Rolls back into the box if To can't take it. */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Box")
	bool WithdrawInstance(UNexusInventoryComponent* To, UNexusItemInstance* Instance);

	// Currency wallet
	UFUNCTION(BlueprintPure, Category = "Inventory|Currency")
	int32 GetCurrency();

	UFUNCTION(BlueprintCallable, Category = "Inventory|Currency")
	void AddCurrency(int32 Amount);

	/** Spend Amount if affordable. Returns false (no change) if the wallet is short. */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Currency")
	bool SpendCurrency(int32 Amount);

	// Cross-container resolution (stable handle -> live instance)
	/**
	 * Resolve a stable handle to the live instance, searching the box then every discovered
	 * player inventory. This is what makes a cross-system reference survive a transfer
	 * between containers and a save->load: the GUID is stable, the pointer is not.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory|Handles")
	UNexusItemInstance* ResolveHandle(FNexusItemHandle Handle);

	// Case swap (spill policy: overflow -> box)
	/**
	 * Equip NewCase on PlayerInventory and auto-send anything that no longer fits to the
	 * box (the chosen spill policy). The single high-level entry point for changing the
	 * attaché case.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory|Case")
	void SwapCase(UNexusInventoryComponent* PlayerInventory, UNexusItemDefinition* NewCase);

	// Persistence (also driven automatically: lazy load on access, write-through on mutation)
	UFUNCTION(BlueprintCallable, Category = "Inventory|Box")
	void SaveBox();

	UFUNCTION(BlueprintCallable, Category = "Inventory|Box")
	void LoadBox();

private:
	/** Lazy-load or refresh the box for the current save slot before any box/currency op. */
	void EnsureBoxCurrent();
	FString GetCurrentSlotName() const;
	void DiscoverPlayerInventories(TArray<UNexusInventoryComponent*>& OutInventories) const;

	/** The item box. Subsystem-owned UObject — never a world-actor component. */
	UPROPERTY()
	TObjectPtr<UNexusItemContainer> Box;

	int32 Currency = 0;

	bool bBoxLoaded = false;
	FString LoadedSlotName;
};
