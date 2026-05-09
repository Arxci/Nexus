#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimNotifies/AnimNotify.h"

#include "GameplayTagContainer.h"

#include "NexusAnimNotify_WeaponAction.generated.h"


/**
 * Place this notify on an arms-side AnimMontage (Unholster, Reload, Fire, ...)
 * at the exact frame where the weapon mesh should react. The notify walks
 * through the owning character's UNexusEquipmentComponent to the active
 * ANexusEquippedActor and calls PlayWeaponAction(ActionTag), which resolves
 * the right montage through the weapon assembly (so attachment overrides win
 * automatically) and plays it on the gun's own AnimInstance.
 *
 * Author authoring example: place this notify at frame 7 of a pistol's reload
 * animation with ActionTag = Action.Weapon.MagOut. The arms drop the magazine
 * visually; the gun's mesh plays the matching mag-eject animation in lockstep.
 */
UCLASS(meta = (DisplayName = "Weapon Action"))
class NEXUS_API UNexusAnimNotify_WeaponAction : public UAnimNotify
{
	GENERATED_BODY()

public:
	UNexusAnimNotify_WeaponAction();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,
		meta = (Categories = "Action.Weapon"))
	FGameplayTag ActionTag;
};