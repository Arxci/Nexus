#include "NexusAnimNotify_WeaponAction.h"

#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Actor.h"

#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Equipment/NexusEquippedActor.h"

UNexusAnimNotify_WeaponAction::UNexusAnimNotify_WeaponAction()
{
#if WITH_EDITORONLY_DATA
	// Cool blue so it reads distinctly from the dark-red HideOutgoingEquipped notify.
	NotifyColor = FColor(50, 130, 220);
#endif
}

FString UNexusAnimNotify_WeaponAction::GetNotifyName_Implementation() const
{
	if (ActionTag.IsValid())
	{
		return FString::Printf(TEXT("Weapon Action: %s"), *ActionTag.ToString());
	}
	return TEXT("Weapon Action (unset)");
}

void UNexusAnimNotify_WeaponAction::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp || !ActionTag.IsValid()) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	const UNexusEquipmentComponent* Equipment = Owner->FindComponentByClass<UNexusEquipmentComponent>();
	if (!Equipment) return;

	if (ANexusEquippedActor* Active = Equipment->GetActiveActor())
	{
		Active->PlayItemActionMontage(ActionTag);
	}
}