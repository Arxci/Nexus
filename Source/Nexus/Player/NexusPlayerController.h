// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EMSActorSaveInterface.h"

#include "GameFramework/PlayerController.h"

#include "Templates/SubclassOf.h"

#include "Nexus/UI/Foundation/NexusUILayoutSubsystem.h" // FNexusUIPanelDef

#include "NexusPlayerController.generated.h"

class UNexusPrimaryGameLayout;


UCLASS()
class NEXUS_API ANexusPlayerController : public APlayerController, public IEMSActorSaveInterface
{
	GENERATED_BODY()

public:
	ANexusPlayerController();

protected:
	virtual void BeginPlay() override;

protected:
	/** The primary UI layout (Common UI activatable layers) created for this local player on BeginPlay. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UNexusPrimaryGameLayout> RootLayoutClass;

	/**
	 * The C++ <-> Blueprint bridge for "open UI by tag": maps a panel tag (what gameplay /
	 * interaction requests) to the widget + layer that opens. A merchant interaction firing
	 * UI.Panel.Merchant opens the widget you point that tag at here — interaction never
	 * references the widget. Leave empty until you have screens to map.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (Categories = "UI.Panel"))
	TMap<FGameplayTag, FNexusUIPanelDef> PanelMap;
};