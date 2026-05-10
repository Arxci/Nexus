#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Engine/StreamableManager.h"

#include "GameplayTagContainer.h"

#include "NexusAttachmentTypes.h"

#include "NexusWeaponAssemblyComponent.generated.h"

class ANexusEquippedActor;
class UAnimInstance;
class UAnimMontage;
class UMeshComponent;
class UNexusAttachmentDefinition;
class UNexusItemInstance;
class USkeletalMeshComponent;
struct FNexusFragment_Weapon;


/**
 * Runtime resolution of (Stat.Weapon.* tag) -> (final float value), produced
 * by walking the attachment tree from the weapon's base values. The base value
 * map is seeded from FNexusFragment_Weapon (RPM, Damage, MagazineSize, ...);
 * each attachment's modifiers are then layered as
 * (base + sum(Add)) * product(Mul).
 */
USTRUCT(BlueprintType, DisplayName = "Resolved Weapon Stats")
struct NEXUS_API FResolvedWeaponStats
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

	/** Parent slot's SlotID, or invalid if this attachment is mounted directly on the weapon. */
	UPROPERTY()
	FGameplayTag ParentSlotID;

	UPROPERTY()
	TObjectPtr<UNexusAttachmentDefinition> Definition;

	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY()
	FName AttachSocket;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponAssemblyChanged);


/**
 * Component on ANexusEquippedActor that owns the runtime attachment tree for
 * a weapon: spawns/destroys the visual mesh components, persists the player's
 * configuration into UNexusItemInstance, and resolves the effective stat block
 * and per-action animation overrides for downstream systems (fire/reload
 * abilities, UI).
 *
 * The component is data-driven from FNexusFragment_Weapon::Slots and
 * UNexusAttachmentDefinition::ProvidedSlots — adding a new attachment is a
 * data asset author task, no code changes required.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusWeaponAssemblyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNexusWeaponAssemblyComponent();

	// Lifecycle
	/**
	 * Builds the assembly tree from the equipped instance: loads the weapon
	 * fragment, applies defaults for any slot the player hasn't customised,
	 * and reflects the persisted attachment map into spawned mesh components.
	 * Safe to call multiple times — it tears down the previous tree first.
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	void RebuildFromInstance();

	/** Tears down all attachments and their mesh components. */
	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
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
	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	bool AttachItem(FGameplayTag SlotID, UNexusAttachmentDefinition* Definition, bool bPersist = true);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	bool DetachItem(FGameplayTag SlotID);

	UFUNCTION(BlueprintPure, Category = "Weapon|Assembly")
	UNexusAttachmentDefinition* GetAttachment(FGameplayTag SlotID) const;

	UFUNCTION(BlueprintPure, Category = "Weapon|Assembly")
	bool CanAttachItem(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const;

	// Resolution
	/**
	 * Returns the cached effective stat block for the current assembly tree.
	 * The cache is rebuilt lazily after any AttachItem/DetachItem/Rebuild;
	 * BP callers get a copy, C++ callers can use ResolveStatsRef() to read in-place.
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	FResolvedWeaponStats ResolveStats() const { return ResolveStatsRef(); }

	/** C++-only ref accessor — avoids the BP-exposed copy. */
	const FResolvedWeaponStats& ResolveStatsRef() const;

	/**
	 * Returns the most-specific authored override for ActionTag across the
	 * attachment tree (deeper attachments win), falling back to the weapon's
	 * own Animations.* montage when nothing overrides. Null if neither path
	 * supplies a montage for that action.
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	UAnimMontage* ResolveActionMontage(FGameplayTag ActionTag) const;

	/** All slot IDs currently part of the tree (top-level + provided sub-slots). */
	UFUNCTION(BlueprintPure, Category = "Weapon|Assembly")
	TArray<FGameplayTag> GetAllSlotIDs() const;

	/** All currently-spawned attachment mesh components (in arbitrary order). */
	TArray<USkeletalMeshComponent*> GetAttachmentMeshes() const;

	/**
	 * C++-only accessor for iterating the live attachment tree. Used by
	 * UNexusWeaponBehaviorComponent to find magazine-fragment-bearing
	 * attachments without baking magazine slot tags into the assembly.
	 */
	const TMap<FGameplayTag, FNexusAttachmentInstance>& GetAttachedRecordsRef() const { return Attached; }

	UPROPERTY(BlueprintAssignable, Category = "Weapon|Assembly")
	FOnWeaponAssemblyChanged OnAssemblyChanged;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	ANexusEquippedActor* GetEquippedActor() const;
	UNexusItemInstance* GetSourceInstance() const;
	const FNexusFragment_Weapon* GetWeaponFragment() const;

	const FWeaponSlotDefinition* FindSlotDefinition(FGameplayTag SlotID) const;

	void RegisterSlotDefinition(const FWeaponSlotDefinition& Slot);
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
	 * top-level slots from the weapon fragment AND any ProvidedSlots
	 * contributed by currently-installed attachments.
	 */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FWeaponSlotDefinition> SlotDefinitions;

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
	mutable FResolvedWeaponStats CachedStats;
	mutable bool bStatCacheValid = false;
};