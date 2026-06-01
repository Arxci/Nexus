#include "NexusInteractionEffect.h"

#include "NiagaraFunctionLibrary.h"

#include "GameFramework/Pawn.h"

#include "Kismet/GameplayStatics.h"

#include "Nexus/Interaction/NexusExamineComponent.h"

#include "Nexus/Interaction/NexusInteractionContext.h"
#include "Nexus/Interaction/NexusInteractableComponent.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemContainerSubsystem.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/NexusItemPickup.h"
#include "Nexus/Game/NexusWorldStateSubsystem.h"
#include "Nexus/Game/NexusUIRequestSubsystem.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"

#include "Engine/World.h"

// GiveItem
void FNexusInteractionEffect_GiveItem::Execute(const FNexusInteractionContext& Context) const
{
	if (!Definition) return;

	APawn* Pawn = Context.GetInteractorPawn();
	if (!Pawn) return;

	FNexusAcquireParams Params;
	Params.bAutoEquipIfPossible = bAutoEquipIfPossible;
	Params.bSkipCeremony        = bSkipCeremony;
	Params.InitialStatTags      = InitialStatTags;

	const FNexusAcquireResult AcquireResult = UNexusInventoryAcquireLibrary::AcquireItem(Pawn, Definition, Count, Params);

	// Report what landed so a completion listener (e.g. a pickup) can tear down or
	// leave a remainder. Partial fill is preserved: AcquireItem places what fits.
	if (Context.Result)
	{
		Context.Result->ItemsAdded     += AcquireResult.AmountAdded;
		Context.Result->ItemsRemaining += AcquireResult.Remainder;
	}
}

// ConsumeItem
void FNexusInteractionEffect_ConsumeItem::Execute(const FNexusInteractionContext& Context) const
{
	UNexusInventoryComponent* Inventory = Context.GetInteractorInventory();
	if (!Inventory || !IdentityTag.IsValid()) return;

	int32 Remaining = FMath::Max(1, Count);
	while (Remaining > 0)
	{
		UNexusItemInstance* Instance = Inventory->FindFirstByIdentityTag(IdentityTag);
		if (!Instance) break;

		const int32 Removed = Inventory->RemoveFromInstance(Instance, Remaining);
		if (Removed <= 0) break;
		Remaining -= Removed;
	}
}

// AwardCurrency
void FNexusInteractionEffect_AwardCurrency::Execute(const FNexusInteractionContext& Context) const
{
	if (Amount == 0) return;
	if (UNexusItemContainerSubsystem* Container = UNexusItemContainerSubsystem::Get(Context.GetWorldContextObject()))
	{
		Container->AddCurrency(Amount);
	}
}

// PlaySound
void FNexusInteractionEffect_PlaySound::Execute(const FNexusInteractionContext& Context) const
{
	if (!Sound) return;
	const AActor* Owner = Context.GetInteractableOwner();
	if (!Owner) return;
	UGameplayStatics::PlaySoundAtLocation(Owner, Sound, Owner->GetActorLocation());
}

// PlayFX
void FNexusInteractionEffect_PlayFX::Execute(const FNexusInteractionContext& Context) const
{
	if (!Effect) return;
	const AActor* Owner = Context.GetInteractableOwner();
	if (!Owner) return;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		Owner, Effect, Owner->GetActorLocation(), Owner->GetActorRotation());
}

// MarkConsumed
void FNexusInteractionEffect_MarkConsumed::Execute(const FNexusInteractionContext& Context) const
{
	UNexusInteractableComponent* Interactable = Context.Interactable.Get();
	if (!Interactable) return;

	const FGameplayTag Key = StateKeyOverride.IsValid() ? StateKeyOverride : Context.StateKey;
	Interactable->MarkInteractionConsumed(Key);
}

// SetWorldState
void FNexusInteractionEffect_SetWorldState::Execute(const FNexusInteractionContext& Context) const
{
	if (!Key.IsValid()) return;

	UNexusWorldStateSubsystem* WorldState = UNexusWorldStateSubsystem::Get(Context.GetWorldContextObject());
	if (!WorldState) return;

	if (bToggle)
	{
		WorldState->ToggleFlag(Key);
	}
	else
	{
		WorldState->SetValue(Key, Value);
	}
}

// BeginExamine
void FNexusInteractionEffect_BeginExamine::Execute(const FNexusInteractionContext& Context) const
{
	APawn* Pawn = Context.GetInteractorPawn();
	if (!Pawn) return;

	UNexusExamineComponent* ExamineComp = Pawn->FindComponentByClass<UNexusExamineComponent>();
	if (!ExamineComp) return;

	ExamineComp->BeginExamine(Examine);
}

// OpenUI
void FNexusInteractionEffect_OpenUI::Execute(const FNexusInteractionContext& Context) const
{
	if (!PanelTag.IsValid()) return;

	if (UNexusUIRequestSubsystem* UI = UNexusUIRequestSubsystem::Get(Context.GetWorldContextObject()))
	{
		UI->RequestPanel(PanelTag, Context.GetInteractableOwner());
	}
}

// SpawnPickup
void FNexusInteractionEffect_SpawnPickup::Execute(const FNexusInteractionContext& Context) const
{
	if (!Definition) return;

	AActor* Source = Context.GetInteractableOwner();
	UWorld* World = Context.GetWorld();
	if (!Source || !World) return;

	UClass* SpawnClass = PickupClass ? PickupClass.Get() : ANexusItemPickup::StaticClass();

	const FRotator Rotation = Source->GetActorRotation();
	const FVector Location = Source->GetActorLocation() + Rotation.RotateVector(SpawnOffset);
	const FTransform SpawnTransform(Rotation, Location);

	ANexusItemPickup* Pickup = World->SpawnActorDeferred<ANexusItemPickup>(
		SpawnClass, SpawnTransform, nullptr, nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (!Pickup) return;

	Pickup->ConfigurePickup(Definition, FMath::Max(1, Count));
	Pickup->FinishSpawning(SpawnTransform);
}

// ActivateAbility
void FNexusInteractionEffect_ActivateAbility::Execute(const FNexusInteractionContext& Context) const
{
	if (!AbilityTag.IsValid()) return;

	AActor* Target = bTargetInteractable ? Context.GetInteractableOwner() : Context.GetInteractorPawn();
	if (!Target) return;

	if (UNexusAbilitySystemComponent* ASC = Target->FindComponentByClass<UNexusAbilitySystemComponent>())
	{
		ASC->TryActivateAbilityByTag(AbilityTag);
	}
}
