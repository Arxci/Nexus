#include "NexusItemContainer.h"

#include "Nexus/Nexus.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/Stackable/NexusFragment_Stackable.h"

namespace
{
	float GetWeightContribution(const UNexusItemInstance* Instance)
	{
		if (!Instance) return 0.0f;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		return Def ? Def->Weight * Instance->GetStackCount() : 0.0f;
	}

	// First-fit-decreasing order: largest footprint first packs tightest. Shared by the two
	// repack paths (OptimizeSpatialSection / ResizeGrid). TArray::Sort dereferences pointer
	// elements, so the predicate takes instances by reference.
	bool FootprintAreaDescending(const UNexusItemInstance& A, const UNexusItemInstance& B)
	{
		const FIntPoint FA = A.GetGridFootprint();
		const FIntPoint FB = B.GetGridFootprint();
		return (FA.X * FA.Y) > (FB.X * FB.Y);
	}
}

void UNexusItemContainer::Configure(int32 InGridWidth, int32 InGridHeight, float InWeightCapacity,
	bool bInUnlimitedWeight, int32 InMaxItemsPerAddCall)
{
	GridWidth          = InGridWidth;
	GridHeight         = InGridHeight;
	WeightCapacity     = InWeightCapacity;
	bUnlimitedWeight   = bInUnlimitedWeight;
	MaxItemsPerAddCall = FMath::Max(1, InMaxItemsPerAddCall);
}

void UNexusItemContainer::ConfigureSections(const TArray<FNexusInventorySectionConfig>& InSections)
{
	Sections = InSections;
	if (Sections.Num() == 0)
	{
		// Unconfigured: one spatial catch-all, so the container behaves like the old
		// fixed grid (every item packs into the attaché).
		FNexusInventorySectionConfig Grid;
		Grid.SectionTag = NexusGameplayTags::Item_Section_Grid;
		Grid.Placement  = ENexusSectionPlacement::Spatial;
		Sections.Add(Grid);
	}
}


// Section routing
int32 UNexusItemContainer::ResolveSectionIndexForDefinition(const UNexusItemDefinition* Definition) const
{
	if (Sections.Num() == 0) return INDEX_NONE;

	if (Definition)
	{
		for (int32 i = 0; i < Sections.Num(); ++i)
		{
			const FNexusInventorySectionConfig& S = Sections[i];
			if (S.AcceptedCategoryTags.IsEmpty()) return i;                       // catch-all (kept last by convention)
			if (Definition->CategoryTags.HasAny(S.AcceptedCategoryTags)) return i; // first accepting section wins
		}
	}

	// No definition, or no section accepts it and there's no catch-all: prefer the first
	// spatial section, else fall back to section 0 so an item always has a home.
	for (int32 i = 0; i < Sections.Num(); ++i)
	{
		if (Sections[i].Placement == ENexusSectionPlacement::Spatial) return i;
	}
	return 0;
}

bool UNexusItemContainer::IsDefinitionSpatial(const UNexusItemDefinition* Definition) const
{
	const int32 Idx = ResolveSectionIndexForDefinition(Definition);
	return Sections.IsValidIndex(Idx) && Sections[Idx].Placement == ENexusSectionPlacement::Spatial;
}

FGameplayTag UNexusItemContainer::GetSectionForDefinition(const UNexusItemDefinition* Definition) const
{
	const int32 Idx = ResolveSectionIndexForDefinition(Definition);
	return Sections.IsValidIndex(Idx) ? Sections[Idx].SectionTag : FGameplayTag();
}

FGameplayTag UNexusItemContainer::GetSectionForInstance(const UNexusItemInstance* Instance) const
{
	return Instance ? GetSectionForDefinition(Instance->GetDefinition()) : FGameplayTag();
}

bool UNexusItemContainer::IsSpatialSection(FGameplayTag SectionTag) const
{
	for (const FNexusInventorySectionConfig& S : Sections)
	{
		if (S.SectionTag.MatchesTagExact(SectionTag))
		{
			return S.Placement == ENexusSectionPlacement::Spatial;
		}
	}
	return false;
}

void UNexusItemContainer::GetItemsInSection(FGameplayTag SectionTag, TArray<UNexusItemInstance*>& OutItems) const
{
	OutItems.Reset();
	if (!SectionTag.IsValid()) return;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && GetSectionForInstance(Instance).MatchesTagExact(SectionTag))
		{
			OutItems.Add(Instance);
		}
	}
}


// Add/Remove
FNexusAddItemResult UNexusItemContainer::AddItem(UNexusItemDefinition* Definition, int32 Count)
{
	FNexusAddItemResult Result;
	if (!Definition || Count <= 0)
	{
		Result.Remainder = FMath::Max(0, Count);
		return Result;
	}

	const int32 OriginalCount = Count;

	if (!bUnlimitedWeight && Definition->Weight > 0.0f)
	{
		const float Available     = WeightCapacity - GetUsedWeight();
		const int32 MaxByWeight   = Available > 0.0f
			? FMath::FloorToInt(Available / Definition->Weight)
			: 0;
		Count = FMath::Min(Count, MaxByWeight);
	}

	Count = FMath::Min(Count, MaxItemsPerAddCall);

	if (Count <= 0)
	{
		Result.Remainder = OriginalCount;
		return Result;
	}

	const int32 MaxStack = GetMaxStackForDefinition(Definition);

	FBroadcastScope Scope(this);

	int32 Placed = 0;

	if (MaxStack > 1)
	{
		// Safe to iterate Items directly: the only mutation in this loop is
		// ModifyStack on an existing element (no add/remove), and EnqueueChange
		// only defers a broadcast — nothing fires until the FBroadcastScope exits.
		for (UNexusItemInstance* Existing : Items)
		{
			const int32 Remaining = Count - Placed;
			if (Remaining <= 0) break;
			if (!Existing || Existing->GetDefinition() != Definition) continue;
			if (Existing->GetStackCount() >= MaxStack) continue;
			if (!Existing->IsMergeableStack()) continue;

			const int32 Applied = Existing->ModifyStack(Remaining, MaxStack);
			if (Applied > 0)
			{
				Placed += Applied;
				CachedUsedWeight += Applied * Definition->Weight;
				Result.AffectedInstances.Add(Existing);
				EnqueueChange(Existing, false, false);
			}
		}
	}

	const bool bSpatial = IsDefinitionSpatial(Definition);
	const FIntPoint DefFootprint(FMath::Max(1, Definition->GridSize.X), FMath::Max(1, Definition->GridSize.Y));

	while (Placed < Count)
	{
		// List sections have no spatial footprint: the instance stays unplaced (-1,-1) and
		// placement never fails for lack of room. Spatial sections first-fit with rotation.
		FIntPoint PlacePos(-1, -1);
		bool bPlaceRotated = false;
		if (bSpatial && !FindFreePlacement(DefFootprint, PlacePos, bPlaceRotated)) break; // grid full

		const int32 Remaining = Count - Placed;
		const int32 ToPlace   = FMath::Min(Remaining, MaxStack);

		UNexusItemInstance* NewInstance = NewObject<UNexusItemInstance>(this);
		NewInstance->Initialize(Definition, ToPlace);
		NewInstance->SetGridPlacement(PlacePos, bPlaceRotated);
		Items.Add(NewInstance);
		BindInstance(NewInstance);

		Placed += ToPlace;
		CachedUsedWeight += ToPlace * Definition->Weight;
		Result.AffectedInstances.Add(NewInstance);
		Result.NewInstances.Add(NewInstance);
		EnqueueChange(NewInstance, true, false);
	}

	Result.AmountAdded = Placed;
	Result.Remainder   = OriginalCount - Placed;
	return Result;
}

bool UNexusItemContainer::AddInstance(UNexusItemInstance* Instance)
{
	if (!Instance || !Instance->GetDefinition()) return false;
	if (Items.Contains(Instance)) return false;

	const UNexusItemDefinition* Def = Instance->GetDefinition();

	if (!bUnlimitedWeight)
	{
		const float Adding = Def->Weight * Instance->GetStackCount();
		if (Adding > 0.0f && GetUsedWeight() + Adding > WeightCapacity)
		{
			return false;
		}
	}

	// Route by section. A transferred instance's prior position from another grid is
	// meaningless here: spatial sections first-fit a fresh region, list sections take it
	// unplaced (-1,-1) and never reject for lack of room.
	const bool bSpatial = IsDefinitionSpatial(Def);
	FIntPoint PlacePos(-1, -1);
	bool bPlaceRotated = false;
	if (bSpatial)
	{
		const FIntPoint Footprint(FMath::Max(1, Def->GridSize.X), FMath::Max(1, Def->GridSize.Y));
		if (!FindFreePlacement(Footprint, PlacePos, bPlaceRotated)) return false; // no room
	}

	FBroadcastScope Scope(this);

	if (Instance->GetOuter() != this)
	{
		Instance->Rename(nullptr, this, REN_DontCreateRedirectors);
	}
	Instance->SetGridPlacement(PlacePos, bPlaceRotated);
	Items.Add(Instance);
	BindInstance(Instance);
	CachedUsedWeight += GetWeightContribution(Instance);
	EnqueueChange(Instance, true, false);
	return true;
}

bool UNexusItemContainer::RemoveInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return false;

	FBroadcastScope Scope(this);

	const float Contribution = GetWeightContribution(Instance);
	const int32 Removed = Items.Remove(Instance);
	if (Removed > 0)
	{
		UnbindInstance(Instance);
		CachedUsedWeight = FMath::Max(0.0f, CachedUsedWeight - Contribution);
		EnqueueChange(Instance, false, true);
		return true;
	}

	return false;
}

void UNexusItemContainer::ClearAll()
{
	if (Items.Num() == 0) return;

	FBroadcastScope Scope(this);

	TArray<TObjectPtr<UNexusItemInstance>> Removed = MoveTemp(Items);
	CachedUsedWeight = 0.0f;

	for (UNexusItemInstance* Instance : Removed)
	{
		UnbindInstance(Instance);
		EnqueueChange(Instance, false, true);
	}
}

int32 UNexusItemContainer::RemoveFromInstance(UNexusItemInstance* Instance, int32 Count)
{
	if (!Instance || Count <= 0 || !Items.Contains(Instance)) return 0;

	FBroadcastScope Scope(this);

	const UNexusItemDefinition* Def = Instance->GetDefinition();
	const float UnitWeight = Def ? Def->Weight : 0.0f;

	const int32 Removed = -Instance->ModifyStack(-Count);
	CachedUsedWeight = FMath::Max(0.0f, CachedUsedWeight - Removed * UnitWeight);

	if (Instance->IsEmpty())
	{
		UnbindInstance(Instance);
		Items.RemoveSingle(Instance);
		EnqueueChange(Instance, false, true);
	}
	else if (Removed > 0)
	{
		EnqueueChange(Instance, false, false);
	}
	return Removed;
}


// Broadcast
void UNexusItemContainer::EnqueueChange(UNexusItemInstance* Instance, const bool bAdded, const bool bRemoved)
{
	PendingChanges.Add({ Instance, bAdded, bRemoved });
}

void UNexusItemContainer::FlushPendingChanges()
{
	if (bFlushInProgress) return;
	if (PendingChanges.Num() == 0) return;

	TGuardValue InProgress(bFlushInProgress, true);

	while (PendingChanges.Num() > 0)
	{
		TArray<FPendingChange> ToFire = MoveTemp(PendingChanges);
		PendingChanges.Reset();

		bool bAnyChange = false;
		for (const FPendingChange& Change : ToFire)
		{
			UNexusItemInstance* Inst = Change.Instance.Get();
			if (!Inst) continue;

			if (Change.bAdded)
			{
				OnItemAdded.Broadcast(Inst);
			}
			else if (Change.bRemoved)
			{
				OnItemRemoved.Broadcast(Inst);
			}
			else if (Items.Contains(Inst))
			{
				OnItemChanged.Broadcast(Inst);
			}
			else
			{
				// A "changed" enqueued for an instance that a prior listener removed
				// within this same flush batch. The weak ptr is still resolvable but
				// the item is gone — don't report a phantom change on it.
				continue;
			}
			bAnyChange = true;
		}

		if (bAnyChange) OnInventoryChanged.Broadcast();
	}

#if !UE_BUILD_SHIPPING
	VerifyWeightInvariant();
#endif
}

void UNexusItemContainer::BindInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return;
	Instance->OnInstanceChanged.AddUniqueDynamic(this, &UNexusItemContainer::HandleInstanceChanged);
}

void UNexusItemContainer::UnbindInstance(UNexusItemInstance* Instance)
{
	if (!Instance) return;
	Instance->OnInstanceChanged.RemoveDynamic(this, &UNexusItemContainer::HandleInstanceChanged);
}

void UNexusItemContainer::HandleInstanceChanged(UNexusItemInstance* Instance)
{
	if (!Instance || !Items.Contains(Instance)) return;

	FBroadcastScope Scope(this);
	EnqueueChange(Instance, false, false);
}


// Utility
int32 UNexusItemContainer::GetTotalCountForDefinition(const UNexusItemDefinition* Definition) const
{
	if (!Definition) return 0;
	int32 Total = 0;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetDefinition() == Definition)
		{
			Total += Instance->GetStackCount();
		}
	}
	return Total;
}

int32 UNexusItemContainer::GetTotalCountForIdentityTag(FGameplayTag IdentityTag) const
{
	if (!IdentityTag.IsValid()) return 0;
	int32 Total = 0;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetIdentityTag().MatchesTagExact(IdentityTag))
		{
			Total += Instance->GetStackCount();
		}
	}
	return Total;
}

int32 UNexusItemContainer::GetTotalCountForCategory(FGameplayTag CategoryTag) const
{
	if (!CategoryTag.IsValid()) return 0;
	int32 Total = 0;
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const UNexusItemDefinition* Def = Instance->GetDefinition();
		if (Def && Def->CategoryTags.HasTag(CategoryTag))
		{
			Total += Instance->GetStackCount();
		}
	}
	return Total;
}

UNexusItemInstance* UNexusItemContainer::FindFirstByDefinition(const UNexusItemDefinition* Definition) const
{
	if (!Definition) return nullptr;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetDefinition() == Definition) return Instance;
	}
	return nullptr;
}

UNexusItemInstance* UNexusItemContainer::FindFirstByIdentityTag(FGameplayTag IdentityTag) const
{
	if (!IdentityTag.IsValid()) return nullptr;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetIdentityTag().MatchesTagExact(IdentityTag)) return Instance;
	}
	return nullptr;
}

UNexusItemInstance* UNexusItemContainer::FindInstanceByGuid(FGuid InstanceGuid) const
{
	if (!InstanceGuid.IsValid()) return nullptr;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && Instance->GetInstanceGuid() == InstanceGuid) return Instance;
	}
	return nullptr;
}

int32 UNexusItemContainer::GetMaxStackForDefinition(const UNexusItemDefinition* Definition)
{
	if (!Definition) return 1;
	if (const FNexusFragment_Stackable* Stack = Definition->FindFragment<FNexusFragment_Stackable>())
	{
		return FMath::Max(1, Stack->MaxStackSize);
	}
	return 1;
}


// Capacity
int32 UNexusItemContainer::GetRemainingCapacityForDefinition(const UNexusItemDefinition* Definition) const
{
	if (!Definition) return 0;

	// Weight ceiling first — mirrors AddItem's weight clamp.
	int32 WeightCap = MAX_int32;
	if (!bUnlimitedWeight && Definition->Weight > 0.0f)
	{
		const float Available = WeightCapacity - GetUsedWeight();
		WeightCap = Available > 0.0f ? FMath::FloorToInt(Available / Definition->Weight) : 0;
	}
	if (WeightCap <= 0) return 0;

	// List sections have no spatial bound — weight is the only limit (MAX_int32 when off),
	// so a key-item / treasure pickup is never greyed out for lack of cells.
	if (!IsDefinitionSpatial(Definition)) return WeightCap;

	if (GridWidth <= 0 || GridHeight <= 0) return 0;

	const int32 MaxStack = GetMaxStackForDefinition(Definition);

	// Scratch occupancy + stack room, computed exactly as AddItem would: merge into
	// existing mergeable stacks first, then first-fit new footprints into free cells.
	TArray<bool> Occupied;
	Occupied.Init(false, GridWidth * GridHeight);

	int32 StackRoom = 0;
	for (const UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const FIntPoint Pos  = Instance->GetGridPosition();
		const FIntPoint Foot = Instance->GetGridFootprint();
		if (Pos.X >= 0 && Pos.Y >= 0)
		{
			for (int32 Y = 0; Y < Foot.Y; ++Y)
			{
				for (int32 X = 0; X < Foot.X; ++X)
				{
					const int32 CX = Pos.X + X;
					const int32 CY = Pos.Y + Y;
					if (CX >= 0 && CX < GridWidth && CY >= 0 && CY < GridHeight)
					{
						Occupied[CY * GridWidth + CX] = true;
					}
				}
			}
		}

		if (MaxStack > 1 && Instance->GetDefinition() == Definition && Instance->IsMergeableStack())
		{
			StackRoom += FMath::Max(0, MaxStack - Instance->GetStackCount());
		}
	}

	const int32 BaseW = FMath::Max(1, Definition->GridSize.X);
	const int32 BaseH = FMath::Max(1, Definition->GridSize.Y);

	int32 NewStacks = 0;
	const int32 MaxStacksByGrid = GridWidth * GridHeight; // hard upper bound on iterations
	FIntPoint ScratchPos;
	for (int32 i = 0; i < MaxStacksByGrid; ++i)
	{
		// Reuse the shared first-fit scratch placement (also used by the repack paths)
		// rather than re-implementing the row-major free-region scan inline.
		if (ScratchPlace(Occupied, BaseW, BaseH, ScratchPos)
			|| (BaseW != BaseH && ScratchPlace(Occupied, BaseH, BaseW, ScratchPos)))
		{
			++NewStacks;
		}
		else
		{
			break;
		}
	}

	const int64 Capacity = static_cast<int64>(StackRoom) + static_cast<int64>(NewStacks) * MaxStack;
	return static_cast<int32>(FMath::Min<int64>(Capacity, WeightCap));
}


// Grid
bool UNexusItemContainer::CanPlaceAt(FIntPoint Footprint, FIntPoint TopLeft, const UNexusItemInstance* IgnoreInstance) const
{
	if (Footprint.X <= 0 || Footprint.Y <= 0) return false;
	if (TopLeft.X < 0 || TopLeft.Y < 0) return false;
	if (TopLeft.X + Footprint.X > GridWidth)  return false;
	if (TopLeft.Y + Footprint.Y > GridHeight) return false;

	for (const UNexusItemInstance* Other : Items)
	{
		if (!Other || Other == IgnoreInstance) continue;
		const FIntPoint OPos = Other->GetGridPosition();
		if (OPos.X < 0 || OPos.Y < 0) continue; // unplaced — occupies nothing

		const FIntPoint OFoot = Other->GetGridFootprint();
		const bool bDisjoint =
			TopLeft.X + Footprint.X <= OPos.X ||
			OPos.X    + OFoot.X     <= TopLeft.X ||
			TopLeft.Y + Footprint.Y <= OPos.Y ||
			OPos.Y    + OFoot.Y     <= TopLeft.Y;
		if (!bDisjoint) return false;
	}
	return true;
}

bool UNexusItemContainer::FindFreePlacement(FIntPoint UnrotatedSize, FIntPoint& OutTopLeft, bool& bOutRotated) const
{
	const int32 W = FMath::Max(1, UnrotatedSize.X);
	const int32 H = FMath::Max(1, UnrotatedSize.Y);

	for (int32 Pass = 0; Pass < 2; ++Pass)
	{
		const bool bRot = (Pass == 1);
		if (bRot && W == H) continue; // rotation is a no-op for square footprints

		const FIntPoint Foot = bRot ? FIntPoint(H, W) : FIntPoint(W, H);
		for (int32 Y = 0; Y + Foot.Y <= GridHeight; ++Y)
		{
			for (int32 X = 0; X + Foot.X <= GridWidth; ++X)
			{
				if (CanPlaceAt(Foot, FIntPoint(X, Y)))
				{
					OutTopLeft  = FIntPoint(X, Y);
					bOutRotated = bRot;
					return true;
				}
			}
		}
	}
	return false;
}

bool UNexusItemContainer::MoveItemTo(UNexusItemInstance* Instance, FIntPoint TopLeft, bool bRotated)
{
	if (!Instance || !Items.Contains(Instance)) return false;

	FIntPoint Footprint(1, 1);
	if (const UNexusItemDefinition* Def = Instance->GetDefinition())
	{
		Footprint.X = FMath::Max(1, Def->GridSize.X);
		Footprint.Y = FMath::Max(1, Def->GridSize.Y);
	}
	if (bRotated) { Swap(Footprint.X, Footprint.Y); }

	// Exclude the instance itself so it doesn't collide with its own current cells.
	if (!CanPlaceAt(Footprint, TopLeft, Instance)) return false;
	if (Instance->GetGridPosition() == TopLeft && Instance->IsRotated() == bRotated) return true;

	FBroadcastScope Scope(this);
	Instance->SetGridPlacement(TopLeft, bRotated);
	EnqueueChange(Instance, false, false);
	return true;
}

UNexusItemInstance* UNexusItemContainer::GetItemAt(FIntPoint Cell) const
{
	if (Cell.X < 0 || Cell.Y < 0 || Cell.X >= GridWidth || Cell.Y >= GridHeight) return nullptr;

	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		const FIntPoint Pos = Instance->GetGridPosition();
		if (Pos.X < 0 || Pos.Y < 0) continue; // unplaced — occupies nothing

		const FIntPoint Foot = Instance->GetGridFootprint();
		if (Cell.X >= Pos.X && Cell.X < Pos.X + Foot.X &&
			Cell.Y >= Pos.Y && Cell.Y < Pos.Y + Foot.Y)
		{
			return Instance;
		}
	}
	return nullptr;
}

TArray<FIntPoint> UNexusItemContainer::GetOccupiedCells(const UNexusItemInstance* Instance) const
{
	TArray<FIntPoint> Cells;
	if (!Instance) return Cells;

	bool bHeld = false;
	for (const UNexusItemInstance* Held : Items)
	{
		if (Held == Instance) { bHeld = true; break; }
	}
	if (!bHeld) return Cells;

	const FIntPoint Pos = Instance->GetGridPosition();
	if (Pos.X < 0 || Pos.Y < 0) return Cells; // unplaced

	const FIntPoint Foot = Instance->GetGridFootprint();
	Cells.Reserve(Foot.X * Foot.Y);
	for (int32 Y = 0; Y < Foot.Y; ++Y)
	{
		for (int32 X = 0; X < Foot.X; ++X)
		{
			Cells.Add(FIntPoint(Pos.X + X, Pos.Y + Y));
		}
	}
	return Cells;
}


bool UNexusItemContainer::ScratchPlace(TArray<bool>& Occupied, int32 W, int32 H, FIntPoint& OutPos) const
{
	for (int32 Y = 0; Y + H <= GridHeight; ++Y)
	{
		for (int32 X = 0; X + W <= GridWidth; ++X)
		{
			bool bFree = true;
			for (int32 dy = 0; dy < H && bFree; ++dy)
				for (int32 dx = 0; dx < W && bFree; ++dx)
					if (Occupied[(Y + dy) * GridWidth + (X + dx)]) bFree = false;
			if (bFree)
			{
				for (int32 dy = 0; dy < H; ++dy)
					for (int32 dx = 0; dx < W; ++dx)
						Occupied[(Y + dy) * GridWidth + (X + dx)] = true;
				OutPos = FIntPoint(X, Y);
				return true;
			}
		}
	}
	return false;
}

bool UNexusItemContainer::OptimizeSpatialSection()
{
	if (GridWidth <= 0 || GridHeight <= 0) return false;

	// Gather currently-placed spatial items.
	TArray<UNexusItemInstance*> Spatial;
	for (UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		if (!IsDefinitionSpatial(Instance->GetDefinition())) continue;
		const FIntPoint Pos = Instance->GetGridPosition();
		if (Pos.X < 0 || Pos.Y < 0) continue; // unplaced — nothing to repack
		Spatial.Add(Instance);
	}
	if (Spatial.Num() == 0) return true;

	// First-fit-decreasing: largest footprint first packs tightest. TArray::Sort
	// dereferences the pointers, so the predicate takes instances by reference.
	Spatial.Sort(FootprintAreaDescending);

	// Plan placements on a scratch occupancy grid; mutate nothing until every item fits.
	TArray<bool> Occupied;
	Occupied.Init(false, GridWidth * GridHeight);

	struct FPlanned { UNexusItemInstance* Inst; FIntPoint Pos; bool bRotated; };
	TArray<FPlanned> Plan;
	Plan.Reserve(Spatial.Num());

	for (UNexusItemInstance* Instance : Spatial)
	{
		FIntPoint Base(1, 1);
		if (const UNexusItemDefinition* Def = Instance->GetDefinition())
		{
			Base.X = FMath::Max(1, Def->GridSize.X);
			Base.Y = FMath::Max(1, Def->GridSize.Y);
		}

		FIntPoint Pos;
		if (ScratchPlace(Occupied, Base.X, Base.Y, Pos))
		{
			Plan.Add({ Instance, Pos, false });
		}
		else if (Base.X != Base.Y && ScratchPlace(Occupied, Base.Y, Base.X, Pos))
		{
			Plan.Add({ Instance, Pos, true });
		}
		else
		{
			return false; // can't repack everything — leave the existing layout untouched
		}
	}

	// Apply, coalescing the moves into one broadcast batch.
	FBroadcastScope Scope(this);
	for (const FPlanned& P : Plan)
	{
		if (P.Inst->GetGridPosition() != P.Pos || P.Inst->IsRotated() != P.bRotated)
		{
			P.Inst->SetGridPlacement(P.Pos, P.bRotated);
			EnqueueChange(P.Inst, false, false);
		}
	}
	return true;
}

void UNexusItemContainer::SetGridDimensions(int32 NewWidth, int32 NewHeight)
{
	GridWidth  = FMath::Max(1, NewWidth);
	GridHeight = FMath::Max(1, NewHeight);
}

void UNexusItemContainer::ResizeGrid(int32 NewWidth, int32 NewHeight, TArray<UNexusItemInstance*>& OutOverflow)
{
	OutOverflow.Reset();
	GridWidth  = FMath::Max(1, NewWidth);
	GridHeight = FMath::Max(1, NewHeight);

	// Every spatial-routed item needs a home in the resized grid — include currently
	// unplaced ones (e.g. a prior overflow) so growing the case re-homes them.
	TArray<UNexusItemInstance*> Spatial;
	for (UNexusItemInstance* Instance : Items)
	{
		if (Instance && IsDefinitionSpatial(Instance->GetDefinition()))
		{
			Spatial.Add(Instance);
		}
	}
	if (Spatial.Num() == 0) return;

	// First-fit-decreasing pack into the new dimensions.
	Spatial.Sort(FootprintAreaDescending);

	TArray<bool> Occupied;
	Occupied.Init(false, GridWidth * GridHeight);

	FBroadcastScope Scope(this);

	for (UNexusItemInstance* Instance : Spatial)
	{
		FIntPoint Base(1, 1);
		if (const UNexusItemDefinition* Def = Instance->GetDefinition())
		{
			Base.X = FMath::Max(1, Def->GridSize.X);
			Base.Y = FMath::Max(1, Def->GridSize.Y);
		}

		FIntPoint Pos;
		if (ScratchPlace(Occupied, Base.X, Base.Y, Pos))
		{
			Instance->SetGridPlacement(Pos, false);
			EnqueueChange(Instance, false, false);
		}
		else if (Base.X != Base.Y && ScratchPlace(Occupied, Base.Y, Base.X, Pos))
		{
			Instance->SetGridPlacement(Pos, true);
			EnqueueChange(Instance, false, false);
		}
		else
		{
			OutOverflow.Add(Instance); // doesn't fit the new case — spill
		}
	}

	// Remove the overflow (the caller redeposits it, e.g. into the item box). Done after
	// the pack so the broadcast batch carries the repack 'changed' events + spill 'removed'
	// events together, then one aggregate.
	for (UNexusItemInstance* Over : OutOverflow)
	{
		CachedUsedWeight = FMath::Max(0.0f, CachedUsedWeight - GetWeightContribution(Over));
		UnbindInstance(Over);
		Items.RemoveSingle(Over);
		EnqueueChange(Over, false, true);
	}
}


// Save bridge
void UNexusItemContainer::CaptureSaveData(TArray<FNexusItemSaveData>& OutSaved) const
{
	OutSaved.Reset();
	OutSaved.Reserve(Items.Num());
	for (const UNexusItemInstance* Instance : Items)
	{
		if (!Instance) continue;
		OutSaved.Add(Instance->ToSaveData());
	}
}

void UNexusItemContainer::RestoreFromSaveData(const TArray<FNexusItemSaveData>& InSaved)
{
	// The live per-item subobjects can't round-trip through a UObject*-as-path save;
	// persistence rides on the flat descriptors and we own recreation here. Rebuild each
	// instance from its descriptor, dropping any whose definition asset is gone.
	for (UNexusItemInstance* Old : Items)
	{
		UnbindInstance(Old);
	}
	Items.Reset();
	Items.Reserve(InSaved.Num());
	CachedUsedWeight = 0.0f;

	{
		// Replay each restored item as an "added" change so a UI built on the runtime
		// OnItemAdded path repopulates on load. The scope coalesces these into per-item
		// OnItemAdded + a single OnInventoryChanged, exactly like a multi-item add.
		FBroadcastScope Scope(this);
		for (const FNexusItemSaveData& Saved : InSaved)
		{
			UNexusItemInstance* Instance = NewObject<UNexusItemInstance>(this);
			if (!Instance->LoadFromSaveData(Saved))
			{
				continue; // definition missing from build — already logged, skip
			}
			Items.Add(Instance);
			BindInstance(Instance);
			CachedUsedWeight += GetWeightContribution(Instance);
			EnqueueChange(Instance, /*bAdded*/ true, /*bRemoved*/ false);
		}
	}

	// An empty restore enqueues nothing, so the scope's flush won't fire. Still signal a
	// load completed so a bound UI can clear any pre-load contents.
	if (Items.Num() == 0)
	{
		OnInventoryChanged.Broadcast();
	}
}

#if !UE_BUILD_SHIPPING
void UNexusItemContainer::VerifyWeightInvariant() const
{
	float Recomputed = 0.0f;
	for (const UNexusItemInstance* Instance : Items)
	{
		Recomputed += GetWeightContribution(Instance);
	}
	ensureMsgf(FMath::IsNearlyEqual(Recomputed, CachedUsedWeight, 0.01f),
		TEXT("Inventory CachedUsedWeight (%.3f) drifted from recomputed sum (%.3f). "
			 "A mutator changed a stack without updating the cache."),
		CachedUsedWeight, Recomputed);
}
#endif
