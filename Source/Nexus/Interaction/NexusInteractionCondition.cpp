#include "NexusInteractionCondition.h"

#include "Nexus/Interaction/NexusInteractionContext.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Game/NexusWorldStateSubsystem.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"

#define LOCTEXT_NAMESPACE "NexusInteraction"

FText FNexusInteractionCondition::GetFailReason(const FNexusInteractionContext& Context) const
{
	return FText::GetEmpty();
}

// RequiresItem
bool FNexusInteractionCondition_RequiresItem::IsMet(const FNexusInteractionContext& Context) const
{
	const UNexusInventoryComponent* Inventory = Context.GetInteractorInventory();
	if (!Inventory) return false;
	return Inventory->GetTotalCountForIdentityTag(IdentityTag) >= FMath::Max(1, Count);
}

FText FNexusInteractionCondition_RequiresItem::GetFailReason(const FNexusInteractionContext& Context) const
{
	if (!FailReasonOverride.IsEmpty()) return FailReasonOverride;
	return LOCTEXT("Locked", "Locked");
}

// RequiresFreeSpace
bool FNexusInteractionCondition_RequiresFreeSpace::IsMet(const FNexusInteractionContext& Context) const
{
	const UNexusInventoryComponent* Inventory = Context.GetInteractorInventory();
	if (!Inventory) return false;

	// No definition to measure against → don't block; the effect itself no-ops if
	// it can't place. With a definition, gate only when nothing at all would fit.
	if (!Definition) return true;
	return Inventory->GetRemainingCapacityForDefinition(Definition) > 0;
}

FText FNexusInteractionCondition_RequiresFreeSpace::GetFailReason(const FNexusInteractionContext& Context) const
{
	if (!FailReasonOverride.IsEmpty()) return FailReasonOverride;
	return LOCTEXT("NoSpace", "No room");
}

// NotConsumed
bool FNexusInteractionCondition_NotConsumed::IsMet(const FNexusInteractionContext& Context) const
{
	const UNexusInteractableComponent* Interactable = Context.Interactable.Get();
	if (!Interactable) return true;

	const FGameplayTag Key = StateKeyOverride.IsValid() ? StateKeyOverride : Context.StateKey;
	return !Interactable->IsInteractionConsumed(Key);
}

// RequiresWorldState
bool FNexusInteractionCondition_RequiresWorldState::IsMet(const FNexusInteractionContext& Context) const
{
	UNexusWorldStateSubsystem* WorldState = UNexusWorldStateSubsystem::Get(Context.GetWorldContextObject());
	const int32 Current = WorldState ? WorldState->GetValue(Key) : 0;

	switch (Comparison)
	{
	case ENexusWorldStateComparison::Equal:          return Current == Value;
	case ENexusWorldStateComparison::NotEqual:       return Current != Value;
	case ENexusWorldStateComparison::GreaterOrEqual: return Current >= Value;
	case ENexusWorldStateComparison::LessOrEqual:    return Current <= Value;
	case ENexusWorldStateComparison::Greater:        return Current >  Value;
	case ENexusWorldStateComparison::Less:           return Current <  Value;
	default:                                         return false;
	}
}

FText FNexusInteractionCondition_RequiresWorldState::GetFailReason(const FNexusInteractionContext& Context) const
{
	if (!FailReasonOverride.IsEmpty()) return FailReasonOverride;
	return LOCTEXT("Locked", "Locked");
}

// RequiresInteractableState
bool FNexusInteractionCondition_RequiresInteractableState::IsMet(const FNexusInteractionContext& Context) const
{
	if (!RequiredTag.IsValid()) return true;

	const AActor* Owner = Context.GetInteractableOwner();
	const UNexusAbilitySystemComponent* ASC = Owner
		? Owner->FindComponentByClass<UNexusAbilitySystemComponent>() : nullptr;
	return ASC && ASC->HasTag(RequiredTag);
}

FText FNexusInteractionCondition_RequiresInteractableState::GetFailReason(const FNexusInteractionContext& Context) const
{
	// Usually empty: a contextual action simply doesn't surface when its state is absent.
	return FailReasonOverride;
}

#undef LOCTEXT_NAMESPACE
