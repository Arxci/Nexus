#pragma once

#include "CoreMinimal.h"
#include "AssetDefinitionDefault.h"
#include "NexusAssetDefinitions.generated.h"

/**
 * Custom Asset Definitions for the Nexus data-asset types. These give each type a
 * distinct content-browser colour, a friendly display name, and a shared **Nexus**
 * category, so the roster stops being a wall of identical grey "Data Asset" icons.
 *
 * The matching UFactory subclasses (NexusAssetFactories.h) put each type in the
 * right-click **Create → Nexus** menu. Both are discovered by reflection once the
 * editor module is loaded — no manual registration.
 *
 * UE 5.2+ Asset Definition system (replaces the older FAssetTypeActions). On an older
 * engine you'd port these to IAssetTypeActions instead.
 */

UCLASS()
class UAssetDefinition_NexusItem : public UAssetDefinitionDefault
{
	GENERATED_BODY()
public:
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
};

UCLASS()
class UAssetDefinition_NexusAttachment : public UAssetDefinitionDefault
{
	GENERATED_BODY()
public:
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
};

UCLASS()
class UAssetDefinition_NexusRecipe : public UAssetDefinitionDefault
{
	GENERATED_BODY()
public:
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
};

UCLASS()
class UAssetDefinition_NexusManifest : public UAssetDefinitionDefault
{
	GENERATED_BODY()
public:
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
};

UCLASS()
class UAssetDefinition_NexusLoadout : public UAssetDefinitionDefault
{
	GENERATED_BODY()
public:
	virtual FText GetAssetDisplayName() const override;
	virtual FLinearColor GetAssetColor() const override;
	virtual TSoftClassPtr<UObject> GetAssetClass() const override;
	virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;
};
