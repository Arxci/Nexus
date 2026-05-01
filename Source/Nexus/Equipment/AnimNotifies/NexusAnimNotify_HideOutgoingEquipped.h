#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NexusAnimNotify_HideOutgoingEquipped.generated.h"

/**
 * Anim Notify — drop on an unequip / holster montage at the exact frame the
 * weapon should disappear (e.g. when the hand passes off-camera). Looks up
 * UNexusEquipmentComponent on the mesh's owning actor and tells it to hide
 * whatever slot's unequip montage is currently in-flight.
 *
 * If a designer forgets to add this notify, equipment's swap-lockout-end
 * safety net hides the slot once the lockout window expires.
 */
UCLASS(meta = (DisplayName = "Hide Outgoing Equipped Slot"))
class NEXUS_API UNexusAnimNotify_HideOutgoingEquipped : public UAnimNotify
{
	GENERATED_BODY()

public:
	UNexusAnimNotify_HideOutgoingEquipped();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
};