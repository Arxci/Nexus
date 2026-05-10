#include "NexusAnimNotifyState_ShowChamberRound.h"

#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Actor.h"

#include "Nexus/Weapon/NexusWeaponBehaviorComponent.h"
#include "Nexus/Equipment/NexusEquipmentComponent.h"
#include "Nexus/Equipment/NexusEquippedActor.h"

UNexusAnimNotifyState_ShowChamberRound::UNexusAnimNotifyState_ShowChamberRound()
{
#if WITH_EDITORONLY_DATA
	// Warm gold so it reads distinctly from the blue WeaponAction notify and
	// the dark red HideOutgoingEquipped notify on the timeline.
	NotifyColor = FColor(220, 170, 40);
#endif
}

FString UNexusAnimNotifyState_ShowChamberRound::GetNotifyName_Implementation() const
{
	return TEXT("Show Chamber Round");
}

void UNexusAnimNotifyState_ShowChamberRound::NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	SetVisible(MeshComp, true);
}

void UNexusAnimNotifyState_ShowChamberRound::NotifyEnd(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	SetVisible(MeshComp, false);
}

void UNexusAnimNotifyState_ShowChamberRound::SetVisible(USkeletalMeshComponent* MeshComp, bool bVisible) const
{
	if (!MeshComp) return;

	const AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	const UNexusEquipmentComponent* Equipment = Owner->FindComponentByClass<UNexusEquipmentComponent>();
	if (!Equipment) return;

	ANexusEquippedActor* Active = Equipment->GetActiveActor();
	if (!Active) return;

	if (UNexusWeaponBehaviorComponent* Behavior = Active->FindComponentByClass<UNexusWeaponBehaviorComponent>())
	{
		Behavior->SetChamberRoundVisible(bVisible);
	}
}