#include "Shared/NexusEditorAssetWatcher.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "UObject/UObjectGlobals.h"

FNexusAssetWatcher::~FNexusAssetWatcher()
{
	Stop();
}

void FNexusAssetWatcher::Start(const TArray<UClass*>& ClassFilter, TFunction<void()> OnChanged)
{
	Stop();

	Classes.Reset();
	for (UClass* Class : ClassFilter)
	{
		if (Class)
		{
			Classes.Add(Class);
		}
	}
	Callback = MoveTemp(OnChanged);
	if (!Callback)
	{
		return;
	}

	// Property edits on a live object (covers tuning a value in any details panel).
	PropertyChangedHandle = FCoreUObjectDelegates::OnObjectPropertyChanged.AddLambda(
		[this](UObject* Object, FPropertyChangedEvent&)
		{
			if (MatchesObject(Object))
			{
				Fire();
			}
		});

	// Registry churn (create / delete / save) so newly-authored assets appear and deleted
	// ones drop without a manual Refresh.
	if (FModuleManager::Get().IsModuleLoaded("AssetRegistry"))
	{
		IAssetRegistry& AssetRegistry =
			FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

		AssetAddedHandle = AssetRegistry.OnAssetAdded().AddLambda(
			[this](const FAssetData& Data) { if (MatchesAsset(Data)) { Fire(); } });
		AssetRemovedHandle = AssetRegistry.OnAssetRemoved().AddLambda(
			[this](const FAssetData& Data) { if (MatchesAsset(Data)) { Fire(); } });
		AssetUpdatedHandle = AssetRegistry.OnAssetUpdated().AddLambda(
			[this](const FAssetData& Data) { if (MatchesAsset(Data)) { Fire(); } });
	}

	bStarted = true;
}

void FNexusAssetWatcher::Stop()
{
	if (!bStarted)
	{
		return;
	}

	FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(PropertyChangedHandle);
	PropertyChangedHandle.Reset();

	if (FModuleManager::Get().IsModuleLoaded("AssetRegistry"))
	{
		IAssetRegistry& AssetRegistry =
			FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
		AssetRegistry.OnAssetAdded().Remove(AssetAddedHandle);
		AssetRegistry.OnAssetRemoved().Remove(AssetRemovedHandle);
		AssetRegistry.OnAssetUpdated().Remove(AssetUpdatedHandle);
	}
	AssetAddedHandle.Reset();
	AssetRemovedHandle.Reset();
	AssetUpdatedHandle.Reset();

	Callback = nullptr;
	bStarted = false;
}

bool FNexusAssetWatcher::MatchesObject(const UObject* Object) const
{
	if (!Object)
	{
		return false;
	}
	if (Classes.Num() == 0)
	{
		return true;
	}
	for (const TWeakObjectPtr<UClass>& Class : Classes)
	{
		if (Class.IsValid() && Object->IsA(Class.Get()))
		{
			return true;
		}
	}
	return false;
}

bool FNexusAssetWatcher::MatchesAsset(const FAssetData& Data) const
{
	if (Classes.Num() == 0)
	{
		return true;
	}
	for (const TWeakObjectPtr<UClass>& Class : Classes)
	{
		// Exact concrete-class match by path — avoids loading the asset just to test type,
		// which is all the Nexus data-asset types (concrete leaf classes) need.
		if (Class.IsValid() && Data.AssetClassPath == Class->GetClassPathName())
		{
			return true;
		}
	}
	return false;
}

void FNexusAssetWatcher::Fire()
{
	if (Callback)
	{
		Callback();
	}
}
