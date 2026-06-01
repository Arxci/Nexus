#include "NexusAttachmentCatalogSubsystem.h"

#include "Engine/AssetManager.h"

#include "Nexus/NexusAssetManager.h"
#include "Nexus/Equipment/Attachments/NexusAssemblyComponent.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

void UNexusAttachmentCatalogSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RebuildCatalog();
}

void UNexusAttachmentCatalogSubsystem::Deinitialize()
{
	if (CatalogHandle.IsValid())
	{
		CatalogHandle->CancelHandle();
		CatalogHandle.Reset();
	}
	Catalog.Reset();
	bCatalogReady = false;

	Super::Deinitialize();
}

void UNexusAttachmentCatalogSubsystem::RebuildCatalog()
{
	bCatalogReady = false;
	Catalog.Reset();

	UAssetManager& AM = UAssetManager::Get();

	TArray<FPrimaryAssetId> Ids;
	AM.GetPrimaryAssetIdList(UNexusAssetManager::TypeAttachmentDefinition, Ids);
	if (Ids.Num() == 0)
	{
		// Nothing registered (no content yet, or the primary type isn't scanned).
		// Still signal ready so late binders don't wait forever.
		bCatalogReady = true;
		OnCatalogReady.Broadcast();
		return;
	}

	// Load the definition objects only — no bundles, so none of the heavy
	// mesh/anim payload is pulled in. The completion callback reads ProvidedTags.
	CatalogHandle = AM.LoadPrimaryAssets(
		Ids, TArray<FName>{},
		FStreamableDelegate::CreateUObject(this, &UNexusAttachmentCatalogSubsystem::HandleCatalogLoaded));

	if (!CatalogHandle.IsValid())
	{
		// Already resident — build synchronously.
		HandleCatalogLoaded();
	}
}

void UNexusAttachmentCatalogSubsystem::HandleCatalogLoaded()
{
	UAssetManager& AM = UAssetManager::Get();

	TArray<FPrimaryAssetId> Ids;
	AM.GetPrimaryAssetIdList(UNexusAssetManager::TypeAttachmentDefinition, Ids);

	Catalog.Reset();
	Catalog.Reserve(Ids.Num());
	for (const FPrimaryAssetId& Id : Ids)
	{
		if (UNexusAttachmentDefinition* Def = Cast<UNexusAttachmentDefinition>(AM.GetPrimaryAssetObject(Id)))
		{
			Catalog.Add(Def);
		}
	}

	bCatalogReady = true;
	OnCatalogReady.Broadcast();
}

TArray<UNexusAttachmentDefinition*> UNexusAttachmentCatalogSubsystem::GetCompatibleAttachments(
	const FGameplayTagContainer& SlotAcceptedTags) const
{
	TArray<UNexusAttachmentDefinition*> Out;
	for (UNexusAttachmentDefinition* Def : Catalog)
	{
		if (Def && Def->FitsSlot(SlotAcceptedTags))
		{
			Out.Add(Def);
		}
	}
	return Out;
}

TArray<UNexusAttachmentDefinition*> UNexusAttachmentCatalogSubsystem::GetAllAttachments() const
{
	TArray<UNexusAttachmentDefinition*> Out;
	Out.Reserve(Catalog.Num());
	for (UNexusAttachmentDefinition* Def : Catalog)
	{
		if (Def) Out.Add(Def);
	}
	return Out;
}

TArray<FNexusAttachmentOption> UNexusAttachmentCatalogSubsystem::GetSlotOptions(
	const UNexusAssemblyComponent* Assembly, const FGameplayTag SlotID) const
{
	TArray<FNexusAttachmentOption> Out;
	if (!Assembly || !SlotID.IsValid()) return Out;

	const FGameplayTagContainer AcceptedTags = Assembly->GetSlotAcceptedTags(SlotID);
	for (UNexusAttachmentDefinition* Def : Catalog)
	{
		if (!Def) continue;

		// Discovery filter: a slot with no AcceptedTags is treated as a wildcard
		// (offer everything); otherwise require a tag intersection. Eligibility
		// (incl. bAcceptsAny + requires/conflicts) is reported per-option below.
		if (!AcceptedTags.IsEmpty() && !Def->FitsSlot(AcceptedTags)) continue;

		FNexusAttachmentOption Option;
		Option.Definition        = Def;
		Option.PreviewStats      = Assembly->PreviewInstall(SlotID, Def);
		Option.UnmetRequirements = Assembly->GetUnmetRequirements(SlotID, Def);
		Option.Conflicts         = Assembly->GetConflictingTags(SlotID, Def);
		Option.bCanInstall       = Assembly->CanAttachItem(SlotID, Def);
		Out.Add(Option);
	}
	return Out;
}