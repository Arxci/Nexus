#include "NexusInventoryComponent.h"

#include "Nexus/Nexus.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemContainer.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Case/NexusFragment_Case.h"
#include "Nexus/Inventory/Fragments/Charm/NexusFragment_Charm.h"

UNexusInventoryComponent::UNexusInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// The storage core is a default subobject so it exists for every instance (and the
	// CDO) before any API call; BeginPlay configures its capacity from the authoring
	// properties below.
	Container = CreateDefaultSubobject<UNexusItemContainer>(TEXT("ItemContainer"));

	// Default player-case layout: zero-cell Key Items + Treasures lists, then the spatial
	// grid as the catch-all (kept last). Designers can override per archetype; an NPC or
	// the item box can collapse this to a single section.
	{
		FNexusInventorySectionConfig KeyItems;
		KeyItems.SectionTag = NexusGameplayTags::Item_Section_KeyItems;
		KeyItems.Placement  = ENexusSectionPlacement::List;
		KeyItems.AcceptedCategoryTags.AddTag(NexusGameplayTags::Item_Category_Key);
		Sections.Add(KeyItems);

		FNexusInventorySectionConfig Treasures;
		Treasures.SectionTag = NexusGameplayTags::Item_Section_Treasures;
		Treasures.Placement  = ENexusSectionPlacement::List;
		Treasures.AcceptedCategoryTags.AddTag(NexusGameplayTags::Item_Category_Treasure);
		Sections.Add(Treasures);

		FNexusInventorySectionConfig Grid;
		Grid.SectionTag = NexusGameplayTags::Item_Section_Grid;
		Grid.Placement  = ENexusSectionPlacement::Spatial; // empty AcceptedCategoryTags = catch-all
		Sections.Add(Grid);
	}
}

void UNexusInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Container)
	{
		// Defensive: every BeginPlay starts with a clean container, in case the
		// subobject carried items in from an earlier life (a PIE leak that kept
		// the chain alive past world teardown, or any future caller that touches
		// the container before BeginPlay). The CDO is empty so a true fresh
		// instance no-ops; we only pay when there is something stale to drop.
		Container->ClearAll();
		EquippedCase = nullptr;
		SavedItems.Reset();
		SavedCase = FNexusItemSaveData();

		Container->Configure(GridWidth, GridHeight, WeightCapacity, bUnlimitedWeight, MaxItemsPerAddCall);
		Container->ConfigureSections(Sections);

		// Mirror the container's coalesced events onto the component's own delegates so
		// every existing listener (equipment's OnItemRemoved hookup, UI, Blueprints)
		// keeps binding to the component unchanged.
		Container->OnItemAdded.AddUniqueDynamic(this, &UNexusInventoryComponent::HandleContainerItemAdded);
		Container->OnItemRemoved.AddUniqueDynamic(this, &UNexusInventoryComponent::HandleContainerItemRemoved);
		Container->OnItemChanged.AddUniqueDynamic(this, &UNexusInventoryComponent::HandleContainerItemChanged);
		Container->OnInventoryChanged.AddUniqueDynamic(this, &UNexusInventoryComponent::HandleContainerInventoryChanged);
	}

	// Equip the starting case (if any) so its GridSize drives the grid. On an empty grid
	// this never overflows; a save-restore later overrides this with the saved case.
	if (!DefaultCaseDefinition.IsNull())
	{
		if (UNexusItemDefinition* CaseDef = DefaultCaseDefinition.LoadSynchronous())
		{
			SetEquippedCase(CaseDef);
		}
	}

#if !UE_BUILD_SHIPPING
	if (GridWidth <= 0 || GridHeight <= 0)
	{
		UE_LOG(LogNexusInventory, Warning,
			TEXT("%s: inventory grid is %dx%d — it can hold no items. Set positive GridWidth/GridHeight."),
			*GetName(), GridWidth, GridHeight);
	}
	if (bUnlimitedWeight && WeightCapacity > 0.0f)
	{
		UE_LOG(LogNexusInventory, Warning,
			TEXT("%s: WeightCapacity (%.1f) is set but bUnlimitedWeight is true, so it is ignored. "
				 "Set bUnlimitedWeight=false to enforce the weight limit."), *GetName(), WeightCapacity);
	}
#endif
}


void UNexusInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Symmetric to BeginPlay: drop every runtime reference the component holds so
	// the item subobjects can be reaped even when something further up the chain
	// (a leaked widget, a stray delegate, an EMS handle) keeps the component
	// resident past world teardown. Without this, the item chain pins through
	// the broadcast bindings until the next GC, and any later PIE that finds
	// the component reuses a populated grid.
	if (Container)
	{
		Container->OnItemAdded.RemoveDynamic(this, &UNexusInventoryComponent::HandleContainerItemAdded);
		Container->OnItemRemoved.RemoveDynamic(this, &UNexusInventoryComponent::HandleContainerItemRemoved);
		Container->OnItemChanged.RemoveDynamic(this, &UNexusInventoryComponent::HandleContainerItemChanged);
		Container->OnInventoryChanged.RemoveDynamic(this, &UNexusInventoryComponent::HandleContainerInventoryChanged);

		Container->ClearAll();
	}

	// External listeners (UI widgets bound from Blueprints, dropped equipment hooks)
	// are unbound here too, so a still-alive subscriber can't pull the component
	// (and the items outered to it) back into the GC root set.
	OnItemAdded.Clear();
	OnItemRemoved.Clear();
	OnItemChanged.Clear();
	OnInventoryChanged.Clear();
	OnEquippedCaseChanged.Clear();

	EquippedCase = nullptr;
	SavedItems.Reset();
	SavedCase = FNexusItemSaveData();

	Super::EndPlay(EndPlayReason);
}


// Add/Remove — forward to the storage core.
FNexusAddItemResult UNexusInventoryComponent::AddItem(UNexusItemDefinition* Definition, int32 Count)
{
	if (!Container)
	{
		FNexusAddItemResult Result;
		Result.Remainder = FMath::Max(0, Count);
		return Result;
	}
	return Container->AddItem(Definition, Count);
}

bool UNexusInventoryComponent::AddInstance(UNexusItemInstance* Instance)
{
	return Container && Container->AddInstance(Instance);
}

bool UNexusInventoryComponent::RemoveInstance(UNexusItemInstance* Instance)
{
	return Container && Container->RemoveInstance(Instance);
}

void UNexusInventoryComponent::ClearAll()
{
	if (Container) Container->ClearAll();
}

int32 UNexusInventoryComponent::RemoveFromInstance(UNexusItemInstance* Instance, int32 Count)
{
	return Container ? Container->RemoveFromInstance(Instance, Count) : 0;
}


// Utility — forward to the storage core.
const TArray<UNexusItemInstance*>& UNexusInventoryComponent::GetItems() const
{
	static const TArray<UNexusItemInstance*> Empty;
	return Container ? Container->GetItems() : Empty;
}

int32 UNexusInventoryComponent::GetTotalCountForDefinition(const UNexusItemDefinition* Definition) const
{
	return Container ? Container->GetTotalCountForDefinition(Definition) : 0;
}

int32 UNexusInventoryComponent::GetTotalCountForIdentityTag(FGameplayTag IdentityTag) const
{
	return Container ? Container->GetTotalCountForIdentityTag(IdentityTag) : 0;
}

int32 UNexusInventoryComponent::GetTotalCountForCategory(FGameplayTag CategoryTag) const
{
	return Container ? Container->GetTotalCountForCategory(CategoryTag) : 0;
}

UNexusItemInstance* UNexusInventoryComponent::FindFirstByDefinition(const UNexusItemDefinition* Definition) const
{
	return Container ? Container->FindFirstByDefinition(Definition) : nullptr;
}

UNexusItemInstance* UNexusInventoryComponent::FindFirstByIdentityTag(FGameplayTag IdentityTag) const
{
	return Container ? Container->FindFirstByIdentityTag(IdentityTag) : nullptr;
}

UNexusItemInstance* UNexusInventoryComponent::FindInstanceByGuid(FGuid InstanceGuid) const
{
	return Container ? Container->FindInstanceByGuid(InstanceGuid) : nullptr;
}


// First-pickup ceremony — player-inventory bookkeeping, kept on the component.
bool UNexusInventoryComponent::HasSeenItemDefinition(const UNexusItemDefinition* Definition) const
{
	if (!Definition) return false;
	const FPrimaryAssetId Id = Definition->GetPrimaryAssetId();
	return Id.IsValid() && SeenItemDefinitions.Contains(Id);
}

void UNexusInventoryComponent::MarkItemDefinitionSeen(const UNexusItemDefinition* Definition)
{
	if (!Definition) return;
	const FPrimaryAssetId Id = Definition->GetPrimaryAssetId();
	if (Id.IsValid())
	{
		SeenItemDefinitions.Add(Id);
	}
}


// Capacity — forward to the storage core.
float UNexusInventoryComponent::GetUsedWeight() const
{
	return Container ? Container->GetUsedWeight() : 0.0f;
}

float UNexusInventoryComponent::GetWeightCapacity() const
{
	return Container ? Container->GetWeightCapacity() : WeightCapacity;
}

int32 UNexusInventoryComponent::GetSlotCount() const
{
	return Container ? Container->GetSlotCount() : 0;
}

FIntPoint UNexusInventoryComponent::GetGridSize() const
{
	return Container ? Container->GetGridSize() : FIntPoint(GridWidth, GridHeight);
}

int32 UNexusInventoryComponent::GetRemainingCapacityForDefinition(const UNexusItemDefinition* Definition) const
{
	return Container ? Container->GetRemainingCapacityForDefinition(Definition) : 0;
}


// Grid — forward to the storage core.
bool UNexusInventoryComponent::CanPlaceAt(FIntPoint Footprint, FIntPoint TopLeft, const UNexusItemInstance* IgnoreInstance) const
{
	return Container && Container->CanPlaceAt(Footprint, TopLeft, IgnoreInstance);
}

bool UNexusInventoryComponent::MoveItemTo(UNexusItemInstance* Instance, FIntPoint TopLeft, bool bRotated)
{
	return Container && Container->MoveItemTo(Instance, TopLeft, bRotated);
}

UNexusItemInstance* UNexusInventoryComponent::GetItemAt(FIntPoint Cell) const
{
	return Container ? Container->GetItemAt(Cell) : nullptr;
}

TArray<FIntPoint> UNexusInventoryComponent::GetOccupiedCells(const UNexusItemInstance* Instance) const
{
	return Container ? Container->GetOccupiedCells(Instance) : TArray<FIntPoint>();
}

bool UNexusInventoryComponent::OptimizeSpatialSection()
{
	return Container && Container->OptimizeSpatialSection();
}


// Sections — forward to the storage core.
FGameplayTag UNexusInventoryComponent::GetSectionForInstance(const UNexusItemInstance* Instance) const
{
	return Container ? Container->GetSectionForInstance(Instance) : FGameplayTag();
}

bool UNexusInventoryComponent::IsSpatialSection(FGameplayTag SectionTag) const
{
	return Container && Container->IsSpatialSection(SectionTag);
}

TArray<UNexusItemInstance*> UNexusInventoryComponent::GetItemsInSection(FGameplayTag SectionTag) const
{
	TArray<UNexusItemInstance*> Out;
	if (Container)
	{
		Container->GetItemsInSection(SectionTag, Out);
	}
	return Out;
}


// Case & charms
UNexusItemDefinition* UNexusInventoryComponent::GetEquippedCaseDefinition() const
{
	return EquippedCase ? EquippedCase->GetDefinition() : nullptr;
}

TArray<UNexusItemInstance*> UNexusInventoryComponent::SetEquippedCase(UNexusItemDefinition* CaseDef)
{
	TArray<UNexusItemInstance*> Overflow;
	if (!CaseDef || !Container) return Overflow;

	const FNexusFragment_Case* Case = CaseDef->FindFragment<FNexusFragment_Case>();
	if (!Case)
	{
		UE_LOG(LogNexusInventory, Warning,
			TEXT("%s: SetEquippedCase rejected '%s' — it has no Case fragment."),
			*GetName(), *GetNameSafe(CaseDef));
		return Overflow;
	}

	// A different case starts with empty charm slots (charms live on their own case).
	UNexusItemInstance* NewCase = NewObject<UNexusItemInstance>(this);
	NewCase->Initialize(CaseDef, 1);
	EquippedCase = NewCase;

	// Re-size the grid to the case and collect anything that no longer fits. ResizeGrid
	// removes the overflow (firing OnItemRemoved); the caller redeposits it into the box.
	Container->ResizeGrid(Case->GridSize.X, Case->GridSize.Y, Overflow);

	OnEquippedCaseChanged.Broadcast();
	return Overflow;
}

FGameplayTagContainer UNexusInventoryComponent::GetCaseCharmSlots() const
{
	if (const UNexusItemDefinition* CaseDef = GetEquippedCaseDefinition())
	{
		if (const FNexusFragment_Case* Case = CaseDef->FindFragment<FNexusFragment_Case>())
		{
			return Case->CharmSlots;
		}
	}
	return FGameplayTagContainer();
}

bool UNexusInventoryComponent::SocketCharm(FGameplayTag SlotTag, UNexusItemDefinition* CharmDef)
{
	if (!EquippedCase || !CharmDef || !SlotTag.IsValid()) return false;

	if (!GetCaseCharmSlots().HasTagExact(SlotTag))
	{
		UE_LOG(LogNexusInventory, Warning,
			TEXT("%s: SocketCharm rejected — slot %s is not exposed by the equipped case."),
			*GetName(), *SlotTag.ToString());
		return false;
	}
	if (!CharmDef->HasFragment<FNexusFragment_Charm>())
	{
		UE_LOG(LogNexusInventory, Warning,
			TEXT("%s: SocketCharm rejected '%s' — it has no Charm fragment."),
			*GetName(), *GetNameSafe(CharmDef));
		return false;
	}

	EquippedCase->SetSocketedItem(SlotTag, TSoftObjectPtr<UNexusItemDefinition>(CharmDef));
	OnEquippedCaseChanged.Broadcast();
	return true;
}

bool UNexusInventoryComponent::UnsocketCharm(FGameplayTag SlotTag)
{
	if (!EquippedCase || !SlotTag.IsValid()) return false;
	if (EquippedCase->GetSocketedItem(SlotTag).IsNull()) return false;
	EquippedCase->ClearSocketedItem(SlotTag);
	OnEquippedCaseChanged.Broadcast();
	return true;
}

UNexusItemDefinition* UNexusInventoryComponent::GetSocketedCharm(FGameplayTag SlotTag) const
{
	if (!EquippedCase) return nullptr;
	// Restore runs behind a loading screen and charms are light data assets — a sync load
	// is acceptable for this query, matching the rest of the save-restore path.
	return EquippedCase->GetSocketedItem(SlotTag).LoadSynchronous();
}

void UNexusInventoryComponent::RestoreEquippedCaseFromSave()
{
	if (SavedCase.DefinitionRef.IsNull())
	{
		// No saved case — keep whatever BeginPlay set (default case or the fixed grid).
		return;
	}

	UNexusItemInstance* Case = NewObject<UNexusItemInstance>(this);
	if (!Case->LoadFromSaveData(SavedCase))
	{
		EquippedCase = nullptr; // saved case definition is gone from the build
		return;
	}
	EquippedCase = Case;

	if (const UNexusItemDefinition* CaseDef = Case->GetDefinition())
	{
		if (const FNexusFragment_Case* CaseFrag = CaseDef->FindFragment<FNexusFragment_Case>())
		{
			// Size the grid to the saved case without re-laying-out — the restored items
			// carry their own saved positions.
			if (Container) Container->SetGridDimensions(CaseFrag->GridSize.X, CaseFrag->GridSize.Y);
		}
	}
}


// Event re-broadcast
void UNexusInventoryComponent::HandleContainerItemAdded(UNexusItemInstance* Instance)
{
	OnItemAdded.Broadcast(Instance);
}

void UNexusInventoryComponent::HandleContainerItemRemoved(UNexusItemInstance* Instance)
{
	OnItemRemoved.Broadcast(Instance);
}

void UNexusInventoryComponent::HandleContainerItemChanged(UNexusItemInstance* Instance)
{
	OnItemChanged.Broadcast(Instance);
}

void UNexusInventoryComponent::HandleContainerInventoryChanged()
{
	OnInventoryChanged.Broadcast();
}


// Save — bridge EMS to the container's flat-descriptor capture/restore.
void UNexusInventoryComponent::ComponentPreSave_Implementation()
{
	// Snapshot the live instances into flat descriptors *before* EMS serializes the
	// component's SaveGame properties (PreSave runs ahead of serialization).
	if (Container)
	{
		Container->CaptureSaveData(SavedItems);
	}

	// Persist the equipped case (definition + charm sockets) the same way.
	SavedCase = EquippedCase ? EquippedCase->ToSaveData() : FNexusItemSaveData();
}

void UNexusInventoryComponent::ComponentLoaded_Implementation()
{
	// Restore the equipped case first so the grid is sized to it before the items (which
	// carry their own saved grid positions) are recreated.
	RestoreEquippedCaseFromSave();

	// EMS has populated SavedItems; hand them to the container to recreate the live
	// subobjects and replay them as OnItemAdded inside one broadcast scope (re-broadcast
	// to this component's delegates), exactly as a multi-item add would.
	if (Container)
	{
		Container->RestoreFromSaveData(SavedItems);
	}

	SavedItems.Reset(); // transient restore buffer; don't keep it resident

	// Announce the restored case so the charm consumer re-applies socketed charms.
	OnEquippedCaseChanged.Broadcast();
}
