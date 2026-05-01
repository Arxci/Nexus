#include "NexusAnimNotify_HideOutgoingEquipped.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"

UNexusAnimNotify_HideOutgoingEquipped::UNexusAnimNotify_HideOutgoingEquipped()
{
#if WITH_EDITORONLY_DATA
	// Dark red so it stands out from generic SFX / step notifies on the timeline.
	NotifyColor = FColor(180, 30, 30);
#endif
}

FString UNexusAnimNotify_HideOutgoingEquipped::GetNotifyName_Implementation() const
{
	return TEXT("Hide Outgoing Equipped");
}

void UNexusAnimNotify_HideOutgoingEquipped::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	if (UNexusEquipmentComponent* Equipment = Owner->FindComponentByClass<UNexusEquipmentComponent>())
	{
		Equipment->NotifyHideOutgoingSlot();
	}
}