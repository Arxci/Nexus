#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "StructUtils/InstancedStruct.h"

#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "NexusAttachmentFragment.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusAttachmentTypes.h"

#include "NexusAttachmentDefinition.generated.h"

class UAnimInstance;
class USkeletalMesh;
class UStaticMesh;
class UTexture2D;


UCLASS(BlueprintType)
class NEXUS_API UNexusAttachmentDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	// Identity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity",
		meta = (Categories = "Attachment.Identity"))
	FGameplayTag IdentityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity",
		meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity",
		meta = (AssetBundles = "UI"))
	TSoftObjectPtr<UTexture2D> Icon;

	// Compatibility
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Compatibility",
		meta = (Categories = "Attachment.Type"))
	FGameplayTagContainer ProvidedTags;

	/**
	 * Cross-slot prerequisites: every tag here must be supplied (via ProvidedTags)
	 * by some OTHER attachment already installed on the same equippable, or this one
	 * can't be attached. E.g. a magnified scope whose RequiredTags name a mount type
	 * that a rail attachment provides. Empty = no prerequisite. Evaluated by
	 * UNexusAssemblyComponent::CanAttachItem against the live tree; if a provider is
	 * later removed, the dependent is pruned (its persisted choice is kept).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Compatibility",
		meta = (Categories = "Attachment.Type"))
	FGameplayTagContainer RequiredTags;

	/**
	 * Mutual exclusions: this attachment can't coexist with any installed attachment
	 * that provides one of these tags. Symmetric — another part's own ConflictTags
	 * are honoured against this one's ProvidedTags too. E.g. a suppressor that
	 * conflicts with a muzzle brake. Empty = conflicts with nothing.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Compatibility",
		meta = (Categories = "Attachment.Type"))
	FGameplayTagContainer ConflictTags;

	// Visual — author EITHER SkeletalMesh OR StaticMesh. Skeletal wins if both
	// are set (and AnimInstanceClass applies); StaticMesh is then ignored.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UStaticMesh> StaticMesh;

	/** Only applies when SkeletalMesh is authored and the mesh isn't driven by the host's leader-pose. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftClassPtr<UAnimInstance> AnimInstanceClass;

	// Stat modifiers — applied on top of the weapon's base stats by the assembly.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TArray<FAttachmentStatModifier> Modifiers;
	
	/**
	 * Per-action (Arms, Item) overrides. Mirror of FEquippableAnimationSet::Actions —
	 * an attachment may supply either the arms montage, the item montage, or both
	 * for any given action. Deeper attachments in the tree win over shallower ones;
	 * see UNexusAssemblyComponent::ResolveArmsMontage / ResolveItemMontage.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation",
		meta = (AssetBundles = "Equipped",
			Categories = "Action",
			ForceInlineRow))
	TMap<FGameplayTag, FEquipmentActionAnim> ActionOverrides;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slots")
	TArray<FAssemblySlotDefinition> ProvidedSlots;

	/**
	 * Attachment-type-specific data, authored by the designer via instanced
	 * structs. Mirrors UNexusItemDefinition::Fragments — keeps this base class
	 * free of one-off magazine/scope/laser fields and lets new attachment
	 * categories ship as data-only additions.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fragments",
		meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FNexusAttachmentFragment>> Fragments;

	bool FitsSlot(const FGameplayTagContainer& SlotAcceptedTags) const
	{
		return ProvidedTags.HasAny(SlotAcceptedTags);
	}

	template <typename T>
	const T* FindFragment() const
	{
		static_assert(TIsDerivedFrom<T, FNexusAttachmentFragment>::IsDerived,
			"T must derive from FNexusAttachmentFragment");

		const UScriptStruct* Target = T::StaticStruct();
		for (const TInstancedStruct<FNexusAttachmentFragment>& Frag : Fragments)
		{
			if (!Frag.IsValid()) continue;
			const UScriptStruct* Type = Frag.GetScriptStruct();
			if (Type && Type->IsChildOf(Target))
			{
				return Frag.GetPtr<const T>();
			}
		}
		return nullptr;
	}

	template <typename T>
	bool HasFragment() const
	{
		return FindFragment<T>() != nullptr;
	}
};