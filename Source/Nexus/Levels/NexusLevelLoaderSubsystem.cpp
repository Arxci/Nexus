#include "NexusLevelLoaderSubsystem.h"

#include "Engine/AssetManager.h"
#include "Engine/World.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Levels/NexusWorldSettings.h"

namespace
{
	const FName EquippedBundle(TEXT("Equipped"));
}

void UNexusLevelLoaderSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	UNexusLevelManifest* Manifest = ResolveManifest();
	if (!Manifest)
	{
		// No manifest authored for this level. First equip of any item will
		// hitch (the equipment component's own per-item load is the fallback).
		// Log so the gap isn't silent during playtest.
		UE_LOG(LogTemp, Warning,
			TEXT("[LevelLoader] No NexusLevelManifest assigned for world %s; first-equip hitches possible."),
			*InWorld.GetName());
		HandleLoadFinished();
		return;
	}

	UAssetManager& AM = UAssetManager::Get();

	TArray<FPrimaryAssetId> IdsToLoad;
	IdsToLoad.Reserve(Manifest->Items.Num() + Manifest->Attachments.Num());

	auto AddSoftRef = [&](const FSoftObjectPath& Path)
	{
		if (Path.IsNull()) return;
		const FPrimaryAssetId Id = AM.GetPrimaryAssetIdForPath(Path);
		if (Id.IsValid()) IdsToLoad.Add(Id);
	};

	for (const TSoftObjectPtr<UNexusItemDefinition>& Item : Manifest->Items)
	{
		AddSoftRef(Item.ToSoftObjectPath());
	}
	for (const TSoftObjectPtr<UNexusAttachmentDefinition>& Att : Manifest->Attachments)
	{
		AddSoftRef(Att.ToSoftObjectPath());
	}

	if (IdsToLoad.Num() == 0)
	{
		HandleLoadFinished();
		return;
	}

	TWeakObjectPtr WeakSelf(this);
	LevelLoadHandle = AM.ChangeBundleStateForPrimaryAssets(
		IdsToLoad,
		TArray<FName>{ EquippedBundle },
		TArray<FName>{},
		/*bRemoveAllBundles*/ false,
		FStreamableDelegate::CreateLambda([WeakSelf]()
		{
			if (UNexusLevelLoaderSubsystem* Self = WeakSelf.Get())
			{
				Self->HandleLoadFinished();
			}
		}),
		FStreamableManager::AsyncLoadHighPriority);

	if (!LevelLoadHandle.IsValid() || LevelLoadHandle->HasLoadCompleted())
	{
		HandleLoadFinished();
	}
}

void UNexusLevelLoaderSubsystem::Deinitialize()
{
	LevelLoadHandle.Reset();
	bLoadComplete = false;
	Super::Deinitialize();
}

void UNexusLevelLoaderSubsystem::HandleLoadFinished()
{
	if (bLoadComplete) return;
	bLoadComplete = true;
	OnLoadComplete.Broadcast();
}

UNexusLevelManifest* UNexusLevelLoaderSubsystem::ResolveManifest() const
{
	const UWorld* World = GetWorld();
	if (!World) return nullptr;

	const ANexusWorldSettings* WS = Cast<ANexusWorldSettings>(World->GetWorldSettings());
	return WS ? WS->LevelManifest : nullptr;
}