#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NexusAbilitySystemInterface.generated.h"


UINTERFACE(MinimalAPI)
class UNexusAbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};


class NEXUS_API INexusAbilitySystemInterface
{
	GENERATED_BODY()

public:

	virtual class UNexusAbilitySystemComponent* GetNexusAbilityComponent() const = 0;
};