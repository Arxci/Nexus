#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimNotifies/AnimNotifyState.h"

#include "NexusAnimNotifyState_ShowChamberRound.generated.h"


/**
 * Place this notify state on an arms-side AnimMontage (Unholster, Reload,
 * etc.) spanning the window where a chambered round should be visible. On
 * NotifyBegin the active equipped actor's UNexusWeaponBehaviorComponent
 * shows its transient round mesh; on NotifyEnd it hides it. The mesh's
 * world transform is driven by the gun's ammo bone via socket attachment,
 * mirroring sequencer authoring.
 *
 * The mesh and socket name are data on FNexusFragment_Weapon::AmmoVisual,
 * so different weapons pick different rounds without code changes. If the
 * active item has no weapon behavior (a non-weapon equippable), this notify
 * is a silent no-op.
 */
UCLASS(meta = (DisplayName = "Show Chamber Round"))
class NEXUS_API UNexusAnimNotifyState_ShowChamberRound : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UNexusAnimNotifyState_ShowChamberRound();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		float TotalDuration,
		const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

private:
	void SetVisible(USkeletalMeshComponent* MeshComp, bool bVisible) const;
};