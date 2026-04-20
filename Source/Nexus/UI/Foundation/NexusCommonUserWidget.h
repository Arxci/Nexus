

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "NexusCommonUserWidget.generated.h"


UCLASS(Abstract, Blueprintable)
class NEXUS_API UNexusCommonUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	UNexusCommonUserWidget(const FObjectInitializer& ObjectInitializer);
};
