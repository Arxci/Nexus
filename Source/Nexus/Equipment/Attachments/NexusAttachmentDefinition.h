#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "StructUtils/InstancedStruct.h"

#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "NexusAttachmentFragment.h"
#include "NexusAttachmentTypes.h"

#include "NexusAttachmentDefinition.generated.h"

class UAnimInstance;
class USkeletalMesh;
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

	// Visual
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<USkeletalMesh> Mesh;
	
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
	 * see UNexusWeaponAssemblyComponent::ResolveArmsMontage / ResolveItemMontage.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation",
		meta = (AssetBundles = "Equipped",
			Categories = "Action",
			ForceInlineRow))
	TMap<FGameplayTag, FEquipmentActionAnim> ActionOverrides;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slots")
	TArray<FWeaponSlotDefinition> ProvidedSlots;

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