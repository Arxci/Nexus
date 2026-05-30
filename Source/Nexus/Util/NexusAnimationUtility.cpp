#include "NexusAnimationUtility.h"

#include "Animation/AnimInstance.h"
#include "Nexus/Character/NexusCharacterBase.h"

UAnimInstance* UNexusAnimationUtility::PlayMontageOnOwner(const AActor* Owner, UAnimMontage* Montage, float& OutDuration)
{
	OutDuration = 0.0f;
	if (!Montage) return nullptr;

	const ANexusCharacterBase* Character = Cast<ANexusCharacterBase>(Owner);
	UAnimInstance* AnimInstance = Character ? Character->GetAnimInstance() : nullptr;
	if (!AnimInstance) return nullptr;

	OutDuration = AnimInstance->Montage_Play(Montage);
	return OutDuration > 0.0f ? AnimInstance : nullptr;
}