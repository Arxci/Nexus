#include "NexusLevelLoaderSubsystem.h"

#include "Engine/AssetManager.h"
#include "Engine/Level.h"
#include "Engine/LevelStreaming.h"
#include "Engine/World.h"
#include "Nexus/NexusAssetManager.h"

#include "Streaming/LevelStreamingDelegates.h"

#include "Nexus/Nexus.h" 
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Levels/NexusWorldSettings.h"


namespace
{
	TArray<FPrimaryAssetId> CollectManifestIds(const UNexusLevelManifest& Manifest)
	{
		UAssetManager& AM = UAssetManager::Get();
		TArray<FPrimaryAssetId> Ids;
		Ids.Reserve(Manifest.Items.Num() + Manifest.Attachments.Num());

		int32 Unresolved = 0;
		auto Add = [&](const FSoftObjectPath& Path)
		{
			if (Path.IsNull()) return;
			const FPrimaryAssetId Id = AM.GetPrimaryAssetIdForPath(Path);
			if (Id.IsValid())
			{
				Ids.Add(Id);
			}
			else
			{
				// A non-null path that doesn't resolve to a primary asset id means
				// the AssetManager's PrimaryAssetTypesToScan rules don't cover this
				// asset's folder. The bundle preload will silently skip it.
				++Unresolved;
				UE_LOG(LogNexusLevelLoader, Warning,
					TEXT("[Manifest %s] Path %s did not resolve to a valid FPrimaryAssetId. "
						 "Check Project Settings -> Asset Manager -> Primary Asset Types To Scan "
						 "covers this asset's folder."),
					*Manifest.GetName(), *Path.ToString());
			}
		};

		for (const TSoftObjectPtr<UNexusItemDefinition>& Item : Manifest.Items)
		{
			Add(Item.ToSoftObjectPath());
		}
		for (const TSoftObjectPtr<UNexusAttachmentDefinition>& Att : Manifest.Attachments)
		{
			Add(Att.ToSoftObjectPath());
		}

		UE_LOG(LogNexusLevelLoader, Log,
			TEXT("[Manifest %s] Resolved %d/%d entries to primary asset ids (%d items + %d attachments, %d unresolved)."),
			*Manifest.GetName(),
			Ids.Num(),
			Manifest.Items.Num() + Manifest.Attachments.Num(),
			Manifest.Items.Num(),
			Manifest.Attachments.Num(),
			Unresolved);

		return Ids;
	}

	/** Returns the manifest authored on Level's WorldSettings, or null. Distinguishes
	 *  "wrong WorldSettings class" (bug — log) from "no manifest authored" (intentional). */
	const UNexusLevelManifest* GetManifestForLevel(const ULevel* Level, bool& bOutWasNexusSettings)
	{
		bOutWasNexusSettings = false;
		if (!Level) return nullptr;

		const ANexusWorldSettings* WS = Cast<ANexusWorldSettings>(Level->GetWorldSettings());
		if (!WS) return nullptr;

		bOutWasNexusSettings = true;
		return WS->LevelManifest;
	}
}

void UNexusLevelLoaderSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	StreamingStateHandle = FLevelStreamingDelegates::OnLevelStreamingStateChanged.AddUObject(
		this, &UNexusLevelLoaderSubsystem::HandleLevelStreamingStateChanged);

	LoadPersistentManifest();

	// Already-streamed-in sub-levels (always-loaded, or loaded during world init)
	// don't fire OnLevelStreamingStateChanged — handle them directly.
	for (ULevelStreaming* Streaming : InWorld.GetStreamingLevels())
	{
		if (!Streaming) continue;
		if (ULevel* Loaded = Streaming->GetLoadedLevel())
		{
			LoadManifestForSubLevel(Streaming, Loaded);
		}
	}
}

void UNexusLevelLoaderSubsystem::Deinitialize()
{
	FLevelStreamingDelegates::OnLevelStreamingStateChanged.Remove(StreamingStateHandle);
	StreamingStateHandle.Reset();

	SubLevelHandles.Reset();
	PendingPersistentLoadCallbacks.Reset();
	PersistentHandle.Reset();
	bPersistentLoadComplete = false;

	Super::Deinitialize();
}

void UNexusLevelLoaderSubsystem::LoadPersistentManifest()
{
	const UWorld* World = GetWorld();
	if (!World) { MarkPersistentLoadComplete(); return; }

	bool bWasNexusSettings = false;
	const UNexusLevelManifest* Manifest = GetManifestForLevel(World->PersistentLevel, bWasNexusSettings);

	if (!bWasNexusSettings)
	{
		UE_LOG(LogNexusLevelLoader, Warning,
			TEXT("Persistent level %s has non-Nexus WorldSettings; no manifest will be preloaded. "
			     "Convert WorldSettings actor to ANexusWorldSettings to fix."),
			*World->GetName());
	}
	if (!Manifest)
	{
		MarkPersistentLoadComplete();
		return;
	}

	const TArray<FPrimaryAssetId> Ids = CollectManifestIds(*Manifest);
	if (Ids.Num() == 0)
	{
		MarkPersistentLoadComplete();
		return;
	}

	UAssetManager& AM = UAssetManager::Get();
	TWeakObjectPtr WeakSelf(this);
	PersistentHandle = AM.ChangeBundleStateForPrimaryAssets(
		Ids,
		TArray<FName>{ UNexusAssetManager::BundleEquipped },
		TArray<FName>{},
		false,
		FStreamableDelegate::CreateLambda([WeakSelf]()
		{
			if (UNexusLevelLoaderSubsystem* Self = WeakSelf.Get())
			{
				Self->MarkPersistentLoadComplete();
			}
		}),
		FStreamableManager::AsyncLoadHighPriority);

	if (!PersistentHandle.IsValid() || PersistentHandle->HasLoadCompleted())
	{
		MarkPersistentLoadComplete();
	}
}

void UNexusLevelLoaderSubsystem::MarkPersistentLoadComplete()
{
	if (bPersistentLoadComplete) return;
	bPersistentLoadComplete = true;

	OnPersistentLoadComplete.Broadcast();

	for (const FOnNexusPersistentLoadCallback& Cb : PendingPersistentLoadCallbacks)
	{
		if (Cb.IsBound()) Cb.Execute();
	}
	PendingPersistentLoadCallbacks.Reset();
}

void UNexusLevelLoaderSubsystem::CallOrRegisterOnPersistentLoadComplete(
	const FOnNexusPersistentLoadCallback& Callback)
{
	if (!Callback.IsBound()) return;

	if (bPersistentLoadComplete)
	{
		Callback.Execute();
		return;
	}
	PendingPersistentLoadCallbacks.Add(Callback);
}

bool UNexusLevelLoaderSubsystem::IsSubLevelLoaded(const ULevelStreaming* StreamingLevel) const
{
	if (!StreamingLevel) return false;
	const TSharedPtr<FStreamableHandle>* Handle = SubLevelHandles.Find(StreamingLevel);
	if (!Handle || !Handle->IsValid()) return false;
	return (*Handle)->HasLoadCompleted();
}

void UNexusLevelLoaderSubsystem::HandleLevelStreamingStateChanged(
	UWorld* StreamingWorld,
	const ULevelStreaming* StreamingLevel,
	ULevel* LevelIfLoaded,
	ELevelStreamingState PreviousState,
	ELevelStreamingState NewState)
{
	if (StreamingWorld != GetWorld() || !StreamingLevel) return;

	// Idempotent: if NewState indicates "loaded," try to load. LoadManifestForSubLevel
	// already guards with SubLevelHandles.Contains() so repeat calls are no-ops.
	// Avoids relying on PreviousState — which can reorder between engine versions.
	const bool bLoaded =
		(NewState == ELevelStreamingState::LoadedNotVisible ||
		 NewState == ELevelStreamingState::LoadedVisible);

	const bool bUnloaded =
		(NewState == ELevelStreamingState::Unloaded ||
		 NewState == ELevelStreamingState::Removed);

	if (bLoaded && LevelIfLoaded)
	{
		LoadManifestForSubLevel(StreamingLevel, LevelIfLoaded);
	}
	else if (bUnloaded)
	{
		ReleaseManifestForSubLevel(StreamingLevel);
	}
}

void UNexusLevelLoaderSubsystem::LoadManifestForSubLevel(
	const ULevelStreaming* StreamingLevel, ULevel* Level)
{
	if (!StreamingLevel || !Level) return;

	PruneStaleSubLevelHandles();

	if (SubLevelHandles.Contains(StreamingLevel)) return;

	bool bWasNexusSettings = false;
	const UNexusLevelManifest* Manifest = GetManifestForLevel(Level, bWasNexusSettings);

	if (!bWasNexusSettings)
	{
		UE_LOG(LogNexusLevelLoader, Warning,
			TEXT("Sub-level %s has non-Nexus WorldSettings; nothing preloaded. "
			     "Convert WorldSettings actor to ANexusWorldSettings to enable per-sub-level manifests."),
			*Level->GetOuter()->GetName());
		return;
	}
	if (!Manifest) return;   // Authored correctly but no items in this sub-level. Silent — intentional.

	const TArray<FPrimaryAssetId> Ids = CollectManifestIds(*Manifest);
	if (Ids.Num() == 0) return;

	UAssetManager& AM = UAssetManager::Get();
	TWeakObjectPtr WeakSelf(this);
	TWeakObjectPtr<const ULevelStreaming> WeakLevel(StreamingLevel);

	const TSharedPtr<FStreamableHandle> Handle = AM.ChangeBundleStateForPrimaryAssets(
		Ids,
		TArray<FName>{ UNexusAssetManager::BundleEquipped },
		TArray<FName>{},
		false,
		FStreamableDelegate::CreateLambda([WeakSelf, WeakLevel]()
		{
			UNexusLevelLoaderSubsystem* Self = WeakSelf.Get();
			if (!Self) return;
			Self->OnSubLevelLoaded.Broadcast(const_cast<ULevelStreaming*>(WeakLevel.Get()));
		}),
		FStreamableManager::AsyncLoadHighPriority);

	if (Handle.IsValid())
	{
		SubLevelHandles.Add(StreamingLevel, Handle);
	}
}

void UNexusLevelLoaderSubsystem::ReleaseManifestForSubLevel(const ULevelStreaming* StreamingLevel)
{
	SubLevelHandles.Remove(StreamingLevel);
	PruneStaleSubLevelHandles();
}

void UNexusLevelLoaderSubsystem::PruneStaleSubLevelHandles()
{
	for (auto It = SubLevelHandles.CreateIterator(); It; ++It)
	{
		if (!It.Key().IsValid())
		{
			It.RemoveCurrent();
		}
	}
}