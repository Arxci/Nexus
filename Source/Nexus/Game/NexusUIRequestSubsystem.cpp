#include "NexusUIRequestSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include "Nexus/Nexus.h"

UNexusUIRequestSubsystem* UNexusUIRequestSubsystem::Get(const UObject* WorldContext)
{
	if (!WorldContext || !GEngine) return nullptr;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull))
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			return GI->GetSubsystem<UNexusUIRequestSubsystem>();
		}
	}
	return nullptr;
}

void UNexusUIRequestSubsystem::RequestPanel(FGameplayTag PanelTag, AActor* Source)
{
	if (!PanelTag.IsValid()) return;

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInteraction, Verbose, TEXT("[UI] Panel requested: %s (source=%s)."),
		*PanelTag.ToString(), *GetNameSafe(Source));
#endif

	OnUIPanelRequested.Broadcast(PanelTag, Source);
}
