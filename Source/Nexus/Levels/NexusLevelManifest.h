#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "NexusLevelManifest.generated.h"

class UNexusAttachmentDefinition;
class UNexusItemDefinition;


/**
 * Per-level/chapter list of every item and attachment reachable in that
 * gameplay scope. UNexusLevelLoaderSubsystem keeps each listed primary asset's
 * "Equipped" bundle resident from the start of the level until the level
 * tears down — so first-equip never hits a cold load.
 *
 * Lyra's "Experience" pattern: scope the resident asset set to the current
 * play scope, not the full game roster. Items not reachable in this level
 * stay on disk; memory grows with chapter complexity, not with total project
 * content.
 *
 * Authoring rule: every item that can be picked up, dropped, granted by a
 * quest, or spawned by debug commands in this level must appear here. Items
 * not listed still function (the equipment component's own async load is the
 * fallback) but the first equip will hitch.
 */
UCLASS(BlueprintType)
class NEXUS_API UNexusLevelManifest : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

	/**
	 * Items reachable in this level. The loader preloads each with the
	 * "Equipped" bundle. Includes pickup-spawned items, loot drops, quest
	 * rewards, and any item the player can carry.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Manifest")
	TArray<TSoftObjectPtr<UNexusItemDefinition>> Items;

	/**
	 * Attachments reachable as standalone pickups or as player-swappable
	 * customisation options. Default attachments on listed items are
	 * transitively loaded via their host item's Equipped bundle, but
	 * player-swappable attachments not referenced by any listed item must
	 * appear here explicitly.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Manifest")
	TArray<TSoftObjectPtr<UNexusAttachmentDefinition>> Attachments;
};