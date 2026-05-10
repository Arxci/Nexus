#pragma once

#include "CoreMinimal.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentFragment.h"

#include "NexusAttachmentFragment_Magazine.generated.h"

class USkeletalMesh;


/**
 * Magazine-specific attachment data. Authored on a magazine UNexusAttachmentDefinition
 * via Fragments. Carries the loaded/empty mesh pair for binary ammo visualization;
 * the weapon behavior swaps SetSkeletalMesh() between them in response to
 * Stat.Ammo.InMagazine transitions across zero. Leader Pose Component on the
 * magazine mesh persists across the swap, so animations don't desync.
 *
 * Both meshes are optional. If either is unset, the swap is skipped for that
 * direction (the magazine retains its current visual). For per-round visibility
 * (e.g. 4 visible bullets popping one at a time) the asset would need each
 * round on its own bone or socket — this fragment is binary by design and
 * matches the marketplace pack's two-mesh authoring.
 */
USTRUCT(BlueprintType, DisplayName = "Magazine")
struct NEXUS_API FNexusAttachmentFragment_Magazine : public FNexusAttachmentFragment
{
	GENERATED_BODY()

	/** Mesh shown while the weapon has at least one round in the magazine. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magazine|Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USkeletalMesh> LoadedMesh;

	/** Mesh shown when the magazine is empty (0 rounds). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magazine|Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USkeletalMesh> EmptyMesh;
};