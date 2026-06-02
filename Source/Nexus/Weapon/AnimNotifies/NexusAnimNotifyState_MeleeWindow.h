#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimNotifies/AnimNotifyState.h"

#include "NexusAnimNotifyState_MeleeWindow.generated.h"


/**
 * Place this notify-STATE on a swing montage across the frames where the blade / fist is
 * live. NotifyBegin opens the active Melee ability's hit window and NotifyEnd closes it,
 * so the MeleeSweep delivery only collects targets during the authored window — the melee
 * analogue of the reload AmmoTransfer notify, and host-agnostic (it walks the owning
 * actor's ASC, so it works on the player's arms mesh and an NPC's body mesh alike).
 */
UCLASS(meta = (DisplayName = "Melee Hit Window"))
class NEXUS_API UNexusAnimNotifyState_MeleeWindow : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UNexusAnimNotifyState_MeleeWindow();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};
