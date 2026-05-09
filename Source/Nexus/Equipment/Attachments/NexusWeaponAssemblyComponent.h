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
	 * overlap the slot's AcceptedTags. On success, the change is persisted to
	 * the source UNexusItemInstance so it survives unequip/save/load.
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	bool AttachItem(FGameplayTag SlotID, UNexusAttachmentDefinition* Definition);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	bool DetachItem(FGameplayTag SlotID);

	UFUNCTION(BlueprintPure, Category = "Weapon|Assembly")
	UNexusAttachmentDefinition* GetAttachment(FGameplayTag SlotID) const;

	UFUNCTION(BlueprintPure, Category = "Weapon|Assembly")
	bool CanAttachItem(FGameplayTag SlotID, const UNexusAttachmentDefinition* Definition) const;

	// Resolution
	UFUNCTION(BlueprintCallable, Category = "Weapon|Assembly")
	FResolvedWeaponStats ResolveStats() const;

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

	UPROPERTY(BlueprintAssignable, Category = "Weapon|Assembly")
	FOnWeaponAssemblyChanged OnAssemblyChanged;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	ANexusEquippedActor* GetEquippedActor() const;
	UNexusItemInstance* GetSourceInstance() const;
	const FNexusFragment_Weapon* GetWeaponFragment() const;

	const FWeaponSlotDefinition* FindSlotDefinition(FGameplayTag SlotID) const;

	void RegisterSlotDefinition(const FWeaponSlotDefinition& Slot, FGameplayTag ParentSlotID);
	void DetachSubtree(FGameplayTag SlotID);

	void SpawnMeshForAttachment(FNexusAttachmentInstance& Record);
	void HandleAttachmentLoaded(FGameplayTag SlotID);

	UMeshComponent* GetParentMeshComponentForSlot(FGameplayTag ParentSlotID) const;

	void BroadcastChanged();

	/**
	 * Flattened slot definitions in the current tree, keyed by SlotID. Includes
	 * top-level slots from the weapon fragment AND any ProvidedSlots
	 * contributed by currently-installed attachments.
	 */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FWeaponSlotDefinition> SlotDefinitions;

	/**
	 * Currently-installed attachments, keyed by SlotID. ParentSlotID inside
	 * each record reconstructs the tree.
	 */
	UPROPERTY(Transient)
	TMap<FGameplayTag, FNexusAttachmentInstance> Attached;

	/** Streamable handles keep loaded attachment bundles resident while attached. */
	TMap<FGameplayTag, TSharedPtr<FStreamableHandle>> SlotLoadHandles;
};