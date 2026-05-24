#pragma once

#include "CoreMinimal.h"

#include "Engine/StreamableManager.h"

#include "GameplayTagContainer.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "NexusAttachmentCatalogSubsystem.generated.h"

class UNexusAttachmentDefinition;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNexusAttachmentCatalogReady);


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