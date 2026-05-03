#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimNotifies/AnimNotify.h"

#include "NexusAnimNotify_HideOutgoingEquipped.generated.h"


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