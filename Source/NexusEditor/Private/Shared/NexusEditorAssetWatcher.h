#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"

class UClass;
struct FAssetData;

/**
 * "A Nexus asset changed — refresh yourself" for editor tools.
 *
 * Every Nexus inspection tool used to build a one-shot snapshot and only update on a
 * manual Refresh, so editing an item's value or grid size left open tools stale. Own one
 * of these as a member, Start() it with the classes you care about and a rebuild
 * callback, and the tool re-reads itself whenever a matching asset's property changes or
 * an asset is added/removed/updated in the registry.
 *
 * Lifetime: the destructor unhooks every delegate, so the callback (which typically
 * captures the owning widget's `this`) can never fire after the tool is gone — provided
 * the watcher is a member of that widget, which is the intended use.
 */
class FNexusAssetWatcher
{
public:
	FNexusAssetWatcher() = default;
	~FNexusAssetWatcher();

	FNexusAssetWatcher(const FNexusAssetWatcher&) = delete;
	FNexusAssetWatcher& operator=(const FNexusAssetWatcher&) = delete;

	/**
	 * Begin watching. ClassFilter restricts which assets matter (empty = react to any
	 * Nexus-relevant change). OnChanged runs on the game thread when a match changes.
	 */
	void Start(const TArray<UClass*>& ClassFilter, TFunction<void()> OnChanged);
	void Stop();

private:
	bool MatchesObject(const UObject* Object) const;
	bool MatchesAsset(const FAssetData& Data) const;
	void Fire();

	TArray<TWeakObjectPtr<UClass>> Classes;
	TFunction<void()> Callback;

	FDelegateHandle PropertyChangedHandle;
	FDelegateHandle AssetAddedHandle;
	FDelegateHandle AssetRemovedHandle;
	FDelegateHandle AssetUpdatedHandle;
	bool bStarted = false;
};
