#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Engine/StreamableManager.h"

#include "GameplayTagContainer.h"

#include "NexusAttachmentTypes.h"

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
 * Runtime resolution of (Stat.* tag) -> (final float value), produced by walking
 * the attachment tree from the equipped item's base values. Base values are
 * contributed by each FNexusItemFragment via SeedStatTags — the assembly itself
 * is fragment-agnostic. Attachment modifiers are layered as
 * (base + sum(Add)) * product(Mul).
 *
 * Retained as "FResolvedItemStats" (not WeaponStats) so the type name reflects
 * its actual scope: any modular equippable can have a resolved stat block, not
 * just weapons. Stat keys are still data-driven (Stat.Weapon.*, Stat.Flashlight.*,
 * etc.) — the struct is just the (key -> value) container.
 */
USTRUCT(BlueprintType, DisplayName = "Resolved Item Stats")
struct NEXUS_API FResolvedItemStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, float> Values;

	float Get(const FGameplayTag StatTag, const float Default = 0.0f) const
	{
		const float* Found = Values.Find(StatTag);
		return Found ? *Found : Default;
	}
};


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
	 * When bPersist is true (the default — runtime/UI path), the change is
	 * written to the source UNexusItemInstance so it survives unequip/save/load.
	 * When false (default-fill path during Rebuild), the install is treated as
	 * "what the slot already wants" and is NOT persisted, so future updates to
	 * a slot's DefaultAttachment continue to apply.
	 *
	 * Sub-slots introduced by the new attachment are auto-filled with their own
	 * defaults (or the player's persisted choice for those sub-slots).
	 */
	UFUNCTION(BlueprintCallable, Category = "Assembly")
	bool AttachItem(FGameplayTag SlotID, UNexusAttachmentDefinition* Definition, bool bPersist = true);

	UFUNCTION(BlueprintCallable, Category = "Assembly")
	bool DetachItem(FGameplayTag SlotID);

	UFUNCTION(BlueprintPure, Category = "Assembly")
	UNexusAttachmentDefinition* GetAttachment(FGameplayTag SlotID) const;

	UFUNCTION(BlueprintPure, Category = "Assembly")
	bool CanAttachItem(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const;

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

	/** All slot IDs currently part of the tree (top-level + provided sub-slots). */
	UFUNCTION(BlueprintPure, Category = "Assembly")
	TArray<FGameplayTag> GetAllSlotIDs() const;

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

	/** Walk SlotDefinitions and install persisted/default attachments for any unfilled slot. Fix-point. */
	void FillMissingDefaults();

	void SpawnMeshForAttachment(FNexusAttachmentInstance& Record);
	void HandleAttachmentLoaded(FGameplayTag SlotID);

	UMeshComponent* GetParentMeshComponentForSlot(FGameplayTag ParentSlotID) const;

	/** Slot of the attachment that contributes SlotID, or invalid if SlotID is a top-level slot. */
	FGameplayTag FindParentSlotFor(FGameplayTag SlotID) const;

	void RebuildStatCache() const;
	void InvalidateStatCache();

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
};
