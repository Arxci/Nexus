#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Engine/StreamableManager.h"

#include "GameplayTagContainer.h"

#include "NexusAttachmentTypes.h"
#include "NexusResolvedItemStats.h"

#include "NexusAssemblyComponent.generated.h"

class ANexusEquippedActor;
class UAnimInstance;
class UAnimMontage;
class UMeshComponent;
class UNexusAttachmentDefinition;
class UNexusItemInstance;
class USkeletalMeshComponent;
struct FNexusFragment_Equippable;


/**
 * Runtime record of one attached item in the assembly tree. Stored privately;
 * external callers manipulate slots through the public AttachItem/DetachItem API.
 */
USTRUCT()
struct FNexusAttachmentInstance
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag SlotID;

	/** Parent slot's SlotID, or invalid if this attachment is mounted directly on the host equipped actor. */
	UPROPERTY()
	FGameplayTag ParentSlotID;

	UPROPERTY()
	TObjectPtr<UNexusAttachmentDefinition> Definition;

	UPROPERTY()
	TObjectPtr<UMeshComponent> Mesh;

	UPROPERTY()
	FName AttachSocket;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAssemblyChanged);


/**
 * Component on ANexusEquippedActor that owns the runtime attachment tree for
 * any modular equippable: spawns/destroys the visual mesh components, persists
 * the player's configuration into UNexusItemInstance, and resolves the effective
 * stat block and per-action animation overrides for downstream systems.
 *
 * The component is *equippable-agnostic* — it reads slots from
 * FNexusFragment_Equippable::Slots and seeds base stats by walking the item
 * definition's fragments and calling SeedStatTags on each. A weapon, a
 * flashlight, or any other equippable with attachment points works the same way;
 * there's no fragment-type check anywhere in this file.
 *
 * Adding a new attachment is a data-asset author task — no code changes required.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusAssemblyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNexusAssemblyComponent();

	// Lifecycle
	/**
	 * Builds the assembly tree from the equipped instance: loads the equippable
	 * fragment's slots, applies defaults for any slot the player hasn't customised,
	 * and reflects the persisted attachment map into spawned mesh components.
	 * Safe to call multiple times — it tears down the previous tree first.
	 */
	UFUNCTION(BlueprintCallable, Category = "Assembly")
	void RebuildFromInstance();

	/** Tears down all attachments and their mesh components. */
	UFUNCTION(BlueprintCallable, Category = "Assembly")
	void ClearAssembly();

	// Authoring
	/**
	 * Attempt to install Definition into SlotID. Returns false if the slot
	 * isn't part of the current tree, or the attachment's ProvidedTags don't
	 * overlap the slot's AcceptedTags.
	 *
	* Source = PlayerAction (the default — runtime/UI path) writes the change to
	 * the source UNexusItemInstance so it survives unequip/save/load. Source =
	 * Default (the default-fill path during Rebuild) treats the install as "what
	 * the slot already wants" and does NOT persist it, so future updates to a
	 * slot's DefaultAttachment continue to apply.
	 *
	 * Sub-slots introduced by the new attachment are auto-filled with their own
	 * defaults (or the player's persisted choice for those sub-slots).
	 */
	UFUNCTION(BlueprintCallable, Category = "Assembly")
	bool AttachItem(FGameplayTag SlotID, UNexusAttachmentDefinition* Definition, ENexusAttachSource Source = ENexusAttachSource::PlayerAction);

	UFUNCTION(BlueprintCallable, Category = "Assembly")
	bool DetachItem(FGameplayTag SlotID);

	UFUNCTION(BlueprintPure, Category = "Assembly")
	UNexusAttachmentDefinition* GetAttachment(FGameplayTag SlotID) const;

	UFUNCTION(BlueprintPure, Category = "Assembly")
	bool CanAttachItem(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const;

	/**
	 * UI helper: the RequiredTags that installing Definition in SlotID would leave
	 * unsatisfied given the current tree (empty = all prerequisites met). Lets a
	 * gunsmith grey out an option and show "needs: <tag>" without committing.
	 */
	UFUNCTION(BlueprintPure, Category = "Assembly")
	FGameplayTagContainer GetUnmetRequirements(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const;

	/**
	 * UI helper: the tags by which Definition would conflict with the current tree
	 * if installed in SlotID (empty = no conflict). Symmetric — covers both this
	 * attachment's ConflictTags and other installed parts' ConflictTags.
	 */
	UFUNCTION(BlueprintPure, Category = "Assembly")
	FGameplayTagContainer GetConflictingTags(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const;

	// Resolution
	/**
	 * Returns the cached effective stat block for the current assembly tree.
	 * The cache is rebuilt lazily after any AttachItem/DetachItem/Rebuild;
	 * BP callers get a copy, C++ callers can use ResolveStatsRef() to read in-place.
	 */
	UFUNCTION(BlueprintCallable, Category = "Assembly")
	FResolvedItemStats ResolveStats() const { return ResolveStatsRef(); }

	/** C++-only ref accessor — avoids the BP-exposed copy. */
	const FResolvedItemStats& ResolveStatsRef() const;

	UFUNCTION(BlueprintCallable, Category = "Assembly")
	UAnimMontage* ResolveArmsMontage(FGameplayTag ActionTag) const;

	UFUNCTION(BlueprintCallable, Category = "Assembly")
	UAnimMontage* ResolveItemMontage(FGameplayTag ActionTag) const;

	// Preview (gunsmith try-before-buy)
	/**
	 * Resolve the effective stats the assembly WOULD have if Definition were
	 * installed in SlotID, without mutating the live tree, caches, or instance.
	 * Replaces whatever currently occupies SlotID (and its sub-tree). Sub-slot
	 * defaults the candidate would introduce are not simulated — this is the
	 * first-order delta the gunsmith shows before committing; the real AttachItem
	 * fills sub-slots and re-resolves. Diff against ResolveStats() for "+8 dmg".
	 */
	UFUNCTION(BlueprintCallable, Category = "Assembly|Preview")
	FResolvedItemStats PreviewInstall(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const;

	/**
	 * Resolve the effective stats the assembly WOULD have if a persistent upgrade
	 * of Delta were applied to StatTag, without mutating anything. Diff against
	 * ResolveStats() to show the gunsmith a tune-up's stat delta before purchase.
	 */
	UFUNCTION(BlueprintCallable, Category = "Assembly|Preview")
	FResolvedItemStats PreviewUpgrade(FGameplayTag StatTag, float Delta) const;

	/**
	 * Signal that the source instance's persistent upgrade stat tags changed
	 * (a merchant tune-up). Invalidates only the stat cache — montage resolutions
	 * are upgrade-independent — and broadcasts so a live weapon's HUD/UI re-read
	 * without a respawn. Kept off the instance's OnInstanceChanged delegate on
	 * purpose: that fires every shot (ammo), which the stat fold ignores anyway.
	 */
	UFUNCTION(BlueprintCallable, Category = "Assembly")
	void NotifyUpgradesChanged();

	/** All slot IDs currently part of the tree (top-level + provided sub-slots). */
	UFUNCTION(BlueprintPure, Category = "Assembly")
	TArray<FGameplayTag> GetAllSlotIDs() const;

	/**
	 * The AcceptedTags authored on SlotID (empty if the slot is unknown or accepts
	 * any). A gunsmith passes this to the catalog's GetCompatibleAttachments /
	 * GetSlotOptions to discover what fits the slot.
	 */
	UFUNCTION(BlueprintPure, Category = "Assembly")
	FGameplayTagContainer GetSlotAcceptedTags(FGameplayTag SlotID) const;

	/** All currently-spawned attachment mesh components (in arbitrary order). */
	TArray<UMeshComponent*> GetAttachmentMeshes() const;

	/**
	 * C++-only accessor for iterating the live attachment tree. Used by
	 * UNexusWeaponBehaviorComponent to find magazine-fragment-bearing
	 * attachments without baking magazine slot tags into the assembly.
	 */
	const TMap<FGameplayTag, FNexusAttachmentInstance>& GetAttachedRecordsRef() const { return Attached; }

	UPROPERTY(BlueprintAssignable, Category = "Assembly")
	FOnAssemblyChanged OnAssemblyChanged;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	ANexusEquippedActor* GetEquippedActor() const;
	UNexusItemInstance*  GetSourceInstance() const;
	const FNexusFragment_Equippable* GetEquippableFragment() const;

	/**
	 * Shared worker for ResolveArmsMontage / ResolveItemMontage. bArmsStream
	 * picks which field of FEquipmentActionAnim the resolver reads — both
	 * streams share the same depth-first attachment walk and equippable
	 * fragment fallback, only the source field differs.
	 */
	UAnimMontage* ResolveActionStream(FGameplayTag ActionTag, bool bArmsStream) const;

	const FAssemblySlotDefinition* FindSlotDefinition(FGameplayTag SlotID) const;

	void RegisterSlotDefinition(const FAssemblySlotDefinition& Slot);
	void DetachSubtree(FGameplayTag SlotID);

	/**
	 * Cross-slot constraint check for installing Definition in SlotID against the
	 * rest of the tree: fills OutUnmetRequired (RequiredTags no other attachment
	 * provides) and OutConflicting (symmetric ConflictTags violations). The subtree
	 * at SlotID is excluded — an attachment can't satisfy/conflict with itself, and
	 * a replace must not see the part it replaces.
	 */
	void ComputeConstraintViolations(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition,
		FGameplayTagContainer& OutUnmetRequired, FGameplayTagContainer& OutConflicting) const;

	/**
	 * After a removal/replace, detach any attachment whose constraints are no longer
	 * met (a required provider went away). Runtime teardown only — the player's
	 * persisted choice is kept, so re-adding the provider restores the dependent.
	 * Fix-point: pruning one can invalidate another.
	 */
	void PruneUnsatisfiedAttachments();

	/** Walk SlotDefinitions and install persisted/default attachments for any unfilled slot. Fix-point. */
	void FillMissingDefaults();

	void SpawnMeshForAttachment(FNexusAttachmentInstance& Record);
	void HandleAttachmentLoaded(FGameplayTag SlotID);

	UMeshComponent* GetParentMeshComponentForSlot(FGameplayTag ParentSlotID) const;

	/** Slot of the attachment that contributes SlotID, or invalid if SlotID is a top-level slot. */
	FGameplayTag FindParentSlotFor(FGameplayTag SlotID) const;

	void RebuildStatCache() const;

	/**
	 * Single source of truth for effective-stat resolution, shared by the live
	 * cache (RebuildStatCache) and the preview paths. Folds, in order:
	 *   base (fragment SeedStatTags) + Σ(attachment Add), then × Π(attachment Mul),
	 *   then + persistent upgrade tags (final additive tier), then clamp to the
	 *   fragment-authored [min,max]. Modifiers/upgrades against unseeded keys are
	 *   ignored. AttachmentDefs is the contributor set; UpgradeStatTags is the
	 *   instance's persistent stat tags (filtered to seeded keys internally).
	 */
	void ResolveStatsInternal(FResolvedItemStats& Out,
		const TArray<const UNexusAttachmentDefinition*>& AttachmentDefs,
		const TMap<FGameplayTag, float>& UpgradeStatTags) const;

	/** Collect the definitions of every installed attachment, optionally excluding the subtree rooted at ExcludeSubtreeRoot. */
	void GatherAttachmentDefs(TArray<const UNexusAttachmentDefinition*>& Out, FGameplayTag ExcludeSubtreeRoot) const;

	/** True if Slot is ExcludeSubtreeRoot or any descendant of it (walks ParentSlotID). */
	bool IsSlotInSubtree(FGameplayTag Slot, FGameplayTag Root) const;

	/**
	 * Wipes every lazy-resolved cache on the component (stats + per-action
	 * arms/item montages). Called from every mutation point — Attach, Detach,
	 * ClearAssembly, Rebuild — so the next read recomputes against the
	 * post-mutation tree.
	 */
	void InvalidateCaches();

	void BroadcastChanged();

	/**
	 * Flattened slot definitions in the current tree, keyed by SlotID. Includes
	 * top-level slots from the equippable fragment AND any ProvidedSlots
	 * contributed by currently-installed attachments.
	 */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FAssemblySlotDefinition> SlotDefinitions;

	/**
	 * Reverse map: child SlotID -> the parent SlotID whose attachment
	 * contributes it (invalid for top-level slots). Maintained alongside
	 * SlotDefinitions so AttachItem doesn't need to scan Attached.
	 */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FGameplayTag> SlotParents;

	/**
	 * Currently-installed attachments, keyed by SlotID. ParentSlotID inside
	 * each record reconstructs the tree.
	 */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FNexusAttachmentInstance> Attached;

	/** Streamable handles keep loaded attachment bundles resident while attached. */
	TMap<FGameplayTag, TSharedPtr<FStreamableHandle>> SlotLoadHandles;

	/**
	 * Coalescing flag: while true, BroadcastChanged is a no-op so we can
	 * batch a multi-step rebuild into a single delegate fire at the end.
	 */
	mutable bool bSuppressBroadcasts = false;

	/** Lazy-resolved effective stats; rebuilt on read after invalidation. */
	mutable FResolvedItemStats CachedStats;
	mutable bool bStatCacheValid = false;

	/**
	 * Lazy-resolved per-action montage caches. Keys present indicate "resolved
	 * once" — a null value means "no override or fallback authored," which is a
	 * valid result we don't want to re-resolve on every shot. Stored as raw
	 * UAnimMontage* because the live attachment streamable handles in
	 * SlotLoadHandles + the item instance's EquippedBundleHandle keep every
	 * cached montage resident between cache invalidations.
	 */
	mutable TMap<FGameplayTag, UAnimMontage*> CachedArmsMontages;
	mutable TMap<FGameplayTag, UAnimMontage*> CachedItemMontages;
};
