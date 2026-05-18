#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimNotifies/AnimNotify.h"

#include "GameplayTagContainer.h"

#include "NexusAnimNotify_EquipmentAction.generated.h"


/**
 * Place this notify on an arms-side AnimMontage (Unholster, Reload, Fire,
 * Ceremony, ...) at the exact frame where the equipped item should react.
 * The notify walks through the owning character's UNexusEquipmentComponent to
 * the active ANexusEquippedActor and calls PlayItemActionMontage(ActionTag);
 * the assembly resolves the item-mesh stream of the action (attachment
 * ActionOverrides take precedence, deeper attachments win, then falls back
 * to the equippable fragment's Actions map). The resolved montage plays on
 * the item's own AnimInstance.
 *
 * Picker is filtered to Action.Equipment.* so generic actions
 * (Unholster/Holster/Ceremony/Inspect) AND weapon-specific actions under
 * Action.Equipment.Weapon.* (Fire/Reload/MagOut/etc.) are all selectable —
 * the notify itself doesn't care which subspace; resolution is data-driven.
 *
 * Author example: place this notify at frame 7 of a pistol's reload
 * animation with ActionTag = Action.Equipment.Weapon.MagOut. The arms drop
 * the magazine visually; the gun's mesh plays the matching mag-eject
 * animation in lockstep.
 */
UCLASS(meta = (DisplayName = "Equipment Action"))
class NEXUS_API UNexusAnimNotify_EquipmentAction : public UAnimNotify
{
	GENERATED_BODY()

public:
	UNexusAnimNotify_EquipmentAction();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (Categories = "Action.Equipment"))
	FGameplayTag ActionTag;
};