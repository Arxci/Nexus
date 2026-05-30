#include "NexusAnimNotify_EquipmentAction.h"

#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Actor.h"

#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Equipment/NexusEquippedActor.h"

UNexusAnimNotify_EquipmentAction::UNexusAnimNotify_EquipmentAction()
{
#if WITH_EDITORONLY_DATA
	// Cool blue so it reads distinctly from the dark-red HideOutgoingEquipped notify.
	NotifyColor = FColor(50, 130, 220);
#endif
}

FString UNexusAnimNotify_EquipmentAction::GetNotifyName_Implementation() const
{
	if (ActionTag.IsValid())
	{
		return FString::Printf(TEXT("Equipment Action: %s"), *ActionTag.ToString());
	}
	return TEXT("Equipment Action (unset)");
}

void UNexusAnimNotify_EquipmentAction::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp || !ActionTag.IsValid()) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	const UNexusEquipmentComponent* Equipment = Owner->FindComponentByClass<UNexusEquipmentComponent>();
	if (!Equipment) return;

	// Animate the item mesh in lockstep with the host montage (the gun's slide / bolt /
	// mag at this frame) on whichever actor is currently active. This notify does NOT
	// advance the slot lifecycle — that is driven by the montage ending, so a draw or
	// holster always plays to completion and can't be interrupted mid-animation.
	if (ANexusEquippedActor* Active = Equipment->GetActiveActor())
	{
		Active->PlayItemActionMontage(ActionTag);
	}
}