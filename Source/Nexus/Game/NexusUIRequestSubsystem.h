#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "NexusUIRequestSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNexusUIPanelRequested, FGameplayTag, PanelTag, AActor*, Source);


/**
 * The one-way seam interaction uses to ask the UI layer to open a panel — a
 * merchant, the save screen, a map, the dialogue system. Interaction REQUESTS;
 * it never owns those flows. An OpenUI effect calls RequestPanel; the HUD / UI
 * manager subscribes to OnUIPanelRequested and opens the actual widget.
 *
 * Decoupled both ways: interaction depends on this subsystem's public request;
 * the UI depends on the delegate. Neither reaches into the other's internals.
 */
UCLASS()
class NEXUS_API UNexusUIRequestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UNexusUIRequestSubsystem* Get(const UObject* WorldContext);

	/**
	 * Ask the UI layer to open the panel identified by PanelTag, opened "from"
	 * Source (e.g. the merchant NPC / save typewriter the player interacted with).
	 * Broadcasts OnUIPanelRequested; opening the panel is the UI layer's job.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI")
	void RequestPanel(FGameplayTag PanelTag, AActor* Source);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnNexusUIPanelRequested OnUIPanelRequested;
};
