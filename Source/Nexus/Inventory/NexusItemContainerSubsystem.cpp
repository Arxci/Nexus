#include "NexusItemContainerSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

#include "EMSObject.h"

#include "Nexus/Nexus.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemContainer.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"

UNexusItemContainerSubsystem* UNexusItemContainerSubsystem::Get(const UObject* WorldContext)
{
	if (!WorldContext || !GEngine) return nullptr;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			return GI->GetSubsystem<UNexusItemContainerSubsystem>();
		}
	}
	return nullptr;
}

void UNexusItemContainerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// The box is the same container class as the player case, configured as one unlimited
	// non-spatial list (a stash has no grid scarcity). Dimensions are irrelevant for a list
	// section; weight is off.
	Box = NewObject<UNexusItemContainer>(this);
	Box->Configure(/*GridW*/ 1, /*GridH*/ 1, /*WeightCap*/ 0.0f, /*bUnlimitedWeight*/ true, /*MaxPerAdd*/ 100000);

	FNexusInventorySectionConfig BoxSection;
	BoxSection.SectionTag = NexusGameplayTags::Item_Section_Box;
	BoxSection.Placement  = ENexusSectionPlacement::List; // empty AcceptedCategoryTags = catch-all
	Box->ConfigureSections({ BoxSection });
}

void UNexusItemContainerSubsystem::Deinitialize()
{
	// Best-effort flush so a quit-to-desktop right after a box op doesn't lose it.
	if (bBoxLoaded)
	{
		SaveBox();
	}
	Super::Deinitialize();
}


// Item box
UNexusItemContainer* UNexusItemContainerSubsystem::GetBox()
{
	EnsureBoxCurrent();
	return Box;
}

bool UNexusItemContainerSubsystem::DepositInstance(UNexusInventoryComponent* From, UNexusItemInstance* Instance)
{
	EnsureBoxCurrent();
	if (!Box || !From || !Instance) return false;
	if (!From->GetItems().Contains(Instance)) return false;

	if (!From->RemoveInstance(Instance)) return false;
	if (!Box->AddInstance(Instance))
	{
		From->AddInstance(Instance); // box refused (shouldn't happen for a list) — put it back
		return false;
	}

	SaveBox();
	return true;
}

bool UNexusItemContainerSubsystem::WithdrawInstance(UNexusInventoryComponent* To, UNexusItemInstance* Instance)
{
	EnsureBoxCurrent();
	if (!Box || !To || !Instance) return false;
	if (!Box->GetItems().Contains(Instance)) return false;

	if (!Box->RemoveInstance(Instance)) return false;
	if (!To->AddInstance(Instance))
	{
		Box->AddInstance(Instance); // player can't take it (full) — return it to the box
		return false;
	}

	SaveBox();
	return true;
}


// Currency wallet
int32 UNexusItemContainerSubsystem::GetCurrency()
{
	EnsureBoxCurrent();
	return Currency;
}

void UNexusItemContainerSubsystem::AddCurrency(int32 Amount)
{
	if (Amount <= 0) return;
	EnsureBoxCurrent();
	Currency += Amount;
	SaveBox();
}

bool UNexusItemContainerSubsystem::SpendCurrency(int32 Amount)
{
	if (Amount <= 0) return true;
	EnsureBoxCurrent();
	if (Currency < Amount) return false;
	Currency -= Amount;
	SaveBox();
	return true;
}


// Handle resolution
UNexusItemInstance* UNexusItemContainerSubsystem::ResolveHandle(FNexusItemHandle Handle)
{
	if (!Handle.IsValid()) return nullptr;

	EnsureBoxCurrent();
	if (Box)
	{
		if (UNexusItemInstance* Found = Box->FindInstanceByGuid(Handle.InstanceId))
		{
			return Found;
		}
	}

	TArray<UNexusInventoryComponent*> Inventories;
	DiscoverPlayerInventories(Inventories);
	for (UNexusInventoryComponent* Inv : Inventories)
	{
		if (Inv)
		{
			if (UNexusItemInstance* Found = Inv->FindInstanceByGuid(Handle.InstanceId))
			{
				return Found;
			}
		}
	}
	return nullptr;
}


// Case swap (overflow -> box)
void UNexusItemContainerSubsystem::SwapCase(UNexusInventoryComponent* PlayerInventory, UNexusItemDefinition* NewCase)
{
	EnsureBoxCurrent();
	if (!PlayerInventory || !NewCase) return;

	// The inventory resizes its grid to the new case and hands back what no longer fits
	// (already removed from the inventory, firing OnItemRemoved). Adopt the overflow into
	// the box — the chosen spill policy.
	TArray<UNexusItemInstance*> Overflow = PlayerInventory->SetEquippedCase(NewCase);
	if (Overflow.Num() == 0) return;

	for (UNexusItemInstance* Item : Overflow)
	{
		if (Item && Box)
		{
			Box->AddInstance(Item);
		}
	}
	SaveBox();
}


// Persistence
void UNexusItemContainerSubsystem::EnsureBoxCurrent()
{
	const FString CurrentSlot = GetCurrentSlotName();
	if (bBoxLoaded && CurrentSlot == LoadedSlotName) return;

	LoadBox();
	LoadedSlotName = CurrentSlot;
	bBoxLoaded     = true;
}

FString UNexusItemContainerSubsystem::GetCurrentSlotName() const
{
	if (UEMSObject* EMS = UEMSObject::Get(this))
	{
		return EMS->GetCurrentSaveGameName();
	}
	return FString();
}

void UNexusItemContainerSubsystem::LoadBox()
{
	if (!Box) return;

	UEMSObject* EMS = UEMSObject::Get(this);
	UNexusItemBoxSaveGame* Save = EMS
		? Cast<UNexusItemBoxSaveGame>(EMS->GetCustomSave(
			UNexusItemBoxSaveGame::StaticClass(), FString(), FString()))
		: nullptr;

	if (!Save)
	{
		// No EMS / no save yet — start from an empty box for this slot.
		Box->RestoreFromSaveData(TArray<FNexusItemSaveData>());
		Currency = 0;
		return;
	}

	Box->RestoreFromSaveData(Save->BoxItems);
	Currency = Save->Currency;
}

void UNexusItemContainerSubsystem::SaveBox()
{
	if (!Box) return;

	UEMSObject* EMS = UEMSObject::Get(this);
	if (!EMS) return;

	UNexusItemBoxSaveGame* Save = Cast<UNexusItemBoxSaveGame>(EMS->GetCustomSave(
		UNexusItemBoxSaveGame::StaticClass(), FString(), FString()));
	if (!Save) return;

	Box->CaptureSaveData(Save->BoxItems);
	Save->Currency = Currency;
	EMS->SaveCustom(Save);
}


// Discovery
void UNexusItemContainerSubsystem::DiscoverPlayerInventories(TArray<UNexusInventoryComponent*>& OutInventories) const
{
	OutInventories.Reset();

	const UGameInstance* GI = GetGameInstance();
	const UWorld* World = GI ? GI->GetWorld() : nullptr;
	if (!World) return;

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		const APlayerController* PC = It->Get();
		APawn* Pawn = PC ? PC->GetPawn() : nullptr;
		if (!Pawn) continue;
		if (UNexusInventoryComponent* Inv = Pawn->FindComponentByClass<UNexusInventoryComponent>())
		{
			OutInventories.Add(Inv);
		}
	}
}
