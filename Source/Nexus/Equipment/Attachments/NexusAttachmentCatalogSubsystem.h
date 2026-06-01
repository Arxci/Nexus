#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "GameplayTagContainer.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "NexusResolvedItemStats.h"

#include "NexusAttachmentCatalogSubsystem.generated.h"

class UNexusAttachmentDefinition;
class UNexusAssemblyComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNexusAttachmentCatalogReady);


/**
 * One gunsmith menu entry for a slot: an attachment that fits the slot, paired
 * with the effective stats it WOULD produce if installed (diff against the live
 * ResolveStats for the "+8 dmg, -0.2s reload" delta) and whether it can be
 * installed right now (cross-slot requires/conflicts). Built by
 * UNexusAttachmentCatalogSubsystem::GetSlotOptions against a live assembly.
 */
USTRUCT(BlueprintType, DisplayName = "Attachment Option")
struct NEXUS_API FNexusAttachmentOption
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UNexusAttachmentDefinition> Definition = nullptr;

	/** Effective stats if this option were installed in the queried slot (preview, no mutation). */
	UPROPERTY(BlueprintReadOnly)
	FResolvedItemStats PreviewStats;

	/** True if it can be installed now: slot-compatible AND requires/conflicts satisfied. */
	UPROPERTY(BlueprintReadOnly)
	bool bCanInstall = false;

	/** RequiredTags not currently satisfied (non-empty => grey out, "needs: ..."). */
	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer UnmetRequirements;

	/** Tags by which this option conflicts with the current tree (non-empty => grey out). */
	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer Conflicts;
};


/**
 * Game-instance-wide index of every UNexusAttachmentDefinition, keyed for
 * "what fits this slot" lookups. This is the *discovery* layer the gunsmith /
 * workbench UI needs — the assembly component only does *validation*
 * (CanAttachItem on a single candidate). Without this, every UI widget would
 * have to scan the Asset Manager itself.
 *
 * The index is the lightweight definition objects only — their mesh / anim
 * payload stays behind the "Equipped" bundle soft pointers and is not loaded
 * here. Built asynchronously on Initialize; rebuildable via RebuildCatalog if
 * content is mounted at runtime.
 */
UCLASS()
class NEXUS_API UNexusAttachmentCatalogSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Attachment definitions whose ProvidedTags overlap SlotAcceptedTags (pass a slot's AcceptedTags). */
	UFUNCTION(BlueprintCallable, Category = "Attachments|Catalog")
	TArray<UNexusAttachmentDefinition*> GetCompatibleAttachments(const FGameplayTagContainer& SlotAcceptedTags) const;

	/** Every known attachment definition. */
	UFUNCTION(BlueprintCallable, Category = "Attachments|Catalog")
	TArray<UNexusAttachmentDefinition*> GetAllAttachments() const;

	/**
	 * Gunsmith hook: every catalog attachment that fits SlotID on Assembly, each
	 * paired with its installed-stats preview and install-eligibility (requires/
	 * conflicts). One call backs a "choose a part for this slot, see the delta"
	 * menu. Discovery filters by the slot's AcceptedTags (empty = offer all, e.g.
	 * a wildcard slot); bCanInstall reflects the full assembly check. Installs go
	 * through the merchant / the assembly's public AttachItem — this only previews.
	 */
	UFUNCTION(BlueprintCallable, Category = "Attachments|Catalog")
	TArray<FNexusAttachmentOption> GetSlotOptions(const UNexusAssemblyComponent* Assembly, FGameplayTag SlotID) const;

	/** Re-scan the Asset Manager and rebuild the index. Normally only needed if content was mounted at runtime. */
	UFUNCTION(BlueprintCallable, Category = "Attachments|Catalog")
	void RebuildCatalog();

	UFUNCTION(BlueprintPure, Category = "Attachments|Catalog")
	bool IsCatalogReady() const { return bCatalogReady; }

	/** Fires once the async definition load finishes (or immediately if there's nothing to load). */
	UPROPERTY(BlueprintAssignable, Category = "Attachments|Catalog")
	FOnNexusAttachmentCatalogReady OnCatalogReady;

private:
	void HandleCatalogLoaded();

	UPROPERTY(Transient)
	TArray<TObjectPtr<UNexusAttachmentDefinition>> Catalog;

	TSharedPtr<FStreamableHandle> CatalogHandle;
	bool bCatalogReady = false;
};