#include "NexusEquipmentInterface.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

float INexusEquipmentInterface::PlayMontage(UAnimMontage* Montage) const
{
	if (!Montage) return 0.0f;

	UAnimInstance* AnimInstance = GetAnimInstance();
	return AnimInstance ? AnimInstance->Montage_Play(Montage) : 0.0f;
}