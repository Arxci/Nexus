#include "NexusAnimNotifyState_MeleeWindow.h"

#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Actor.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "Nexus/Weapon/Abilities/NexusAbility_WeaponMelee.h"

namespace
{
	UNexusAbility_WeaponMelee* FindActiveMelee(USkeletalMeshComponent* MeshComp)
	{
		if (!MeshComp) return nullptr;

		// The owner of the animated mesh (player character or NPC) carries the ASC.
		const INexusAbilitySystemInterface* ASCOwner = Cast<INexusAbilitySystemInterface>(MeshComp->GetOwner());
		UNexusAbilitySystemComponent* ASC = ASCOwner ? ASCOwner->GetNexusAbilitySystemComponent() : nullptr;
		if (!ASC) return nullptr;

		return Cast<UNexusAbility_WeaponMelee>(
			ASC->FindAbilityByClass(UNexusAbility_WeaponMelee::StaticClass()));
	}
}

UNexusAnimNotifyState_MeleeWindow::UNexusAnimNotifyState_MeleeWindow()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(220, 120, 40); // warm orange — reads as a "live blade" window
#endif
}

FString UNexusAnimNotifyState_MeleeWindow::GetNotifyName_Implementation() const
{
	return TEXT("Melee Hit Window");
}

void UNexusAnimNotifyState_MeleeWindow::NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (UNexusAbility_WeaponMelee* Melee = FindActiveMelee(MeshComp))
	{
		Melee->OpenHitWindow();
	}
}

void UNexusAnimNotifyState_MeleeWindow::NotifyEnd(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (UNexusAbility_WeaponMelee* Melee = FindActiveMelee(MeshComp))
	{
		Melee->CloseHitWindow();
	}
}
