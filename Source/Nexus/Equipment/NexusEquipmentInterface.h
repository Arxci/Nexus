#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "NexusEquipmentInterface.generated.h"

class USkeletalMeshComponent;
class UAnimInstance;
class UAnimMontage;


UINTERFACE(MinimalAPI)
class UNexusEquipmentInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * Host contract for any actor that carries equipment. Mirrors
 * INexusAbilitySystemInterface in style: UNexusEquipmentComponent and the weapon
 * abilities talk to their owner through this interface, never to a concrete
 * character class, so a turret, a deployable, or an NPC can host equipment
 * exactly as the controlled pawn does.
 *
 * ANexusCharacterBase implements it and returns the body mesh; a view-space pawn
 * overrides GetEquipmentAttachMesh to return its viewmodel mesh instead. The
 * component asks the host where to attach the active item and which AnimInstance
 * to play montages on — it has no opinion about the host's shape.
 */
class NEXUS_API INexusEquipmentInterface
{
	GENERATED_BODY()

public:
	/**
	 * Mesh the active in-world equipped actor attaches to; its hand_ik_gun socket
	 * lives here. Defaults to the body mesh on the base character; a view-space
	 * pawn returns its own mesh so the held item renders in the viewmodel.
	 */
	virtual USkeletalMeshComponent* GetEquipmentAttachMesh() const = 0;

	/** AnimInstance equipment / weapon montages play on (the host's animated mesh). */
	virtual UAnimInstance* GetAnimInstance() const = 0;

	/**
	 * Non-virtual convenience on the I-class: play Montage on the host's
	 * AnimInstance. Returns the montage play length (seconds), or 0 if there was
	 * no montage or no AnimInstance to play it on.
	 */
	float PlayMontage(UAnimMontage* Montage) const;
};