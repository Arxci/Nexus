#include "AssetDefinitions/NexusAssetDefinitions.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Equipment/NexusEquipmentLoadout.h"
#include "Nexus/Input/NexusInputContext.h"
#include "Nexus/Input/NexusInputConfig.h"

#define LOCTEXT_NAMESPACE "NexusAssetDefinitions"

namespace NexusAssetDef
{
	// One shared category so all Nexus types group together in the content browser
	// filter and the right-click Create menu.
	static TConstArrayView<FAssetCategoryPath> NexusCategory()
	{
		static const TArray<FAssetCategoryPath> Categories = { FAssetCategoryPath(LOCTEXT("NexusCategory", "Nexus")) };
		return Categories;
	}
}

// --- Item --------------------------------------------------------------------
FText UAssetDefinition_NexusItem::GetAssetDisplayName() const { return LOCTEXT("Item", "Nexus Item"); }
FLinearColor UAssetDefinition_NexusItem::GetAssetColor() const { return FLinearColor(0.20f, 0.70f, 0.35f); } // green
TSoftClassPtr<UObject> UAssetDefinition_NexusItem::GetAssetClass() const { return UNexusItemDefinition::StaticClass(); }
TConstArrayView<FAssetCategoryPath> UAssetDefinition_NexusItem::GetAssetCategories() const { return NexusAssetDef::NexusCategory(); }

// --- Attachment --------------------------------------------------------------
FText UAssetDefinition_NexusAttachment::GetAssetDisplayName() const { return LOCTEXT("Attachment", "Nexus Attachment"); }
FLinearColor UAssetDefinition_NexusAttachment::GetAssetColor() const { return FLinearColor(0.25f, 0.55f, 0.95f); } // blue
TSoftClassPtr<UObject> UAssetDefinition_NexusAttachment::GetAssetClass() const { return UNexusAttachmentDefinition::StaticClass(); }
TConstArrayView<FAssetCategoryPath> UAssetDefinition_NexusAttachment::GetAssetCategories() const { return NexusAssetDef::NexusCategory(); }

// --- Recipe ------------------------------------------------------------------
FText UAssetDefinition_NexusRecipe::GetAssetDisplayName() const { return LOCTEXT("Recipe", "Nexus Combination Recipe"); }
FLinearColor UAssetDefinition_NexusRecipe::GetAssetColor() const { return FLinearColor(0.95f, 0.60f, 0.20f); } // orange
TSoftClassPtr<UObject> UAssetDefinition_NexusRecipe::GetAssetClass() const { return UNexusCombinationRecipe::StaticClass(); }
TConstArrayView<FAssetCategoryPath> UAssetDefinition_NexusRecipe::GetAssetCategories() const { return NexusAssetDef::NexusCategory(); }

// --- Level Manifest ----------------------------------------------------------
FText UAssetDefinition_NexusManifest::GetAssetDisplayName() const { return LOCTEXT("Manifest", "Nexus Level Manifest"); }
FLinearColor UAssetDefinition_NexusManifest::GetAssetColor() const { return FLinearColor(0.65f, 0.40f, 0.90f); } // purple
TSoftClassPtr<UObject> UAssetDefinition_NexusManifest::GetAssetClass() const { return UNexusLevelManifest::StaticClass(); }
TConstArrayView<FAssetCategoryPath> UAssetDefinition_NexusManifest::GetAssetCategories() const { return NexusAssetDef::NexusCategory(); }

// --- Equipment Loadout -------------------------------------------------------
FText UAssetDefinition_NexusLoadout::GetAssetDisplayName() const { return LOCTEXT("Loadout", "Nexus Equipment Loadout"); }
FLinearColor UAssetDefinition_NexusLoadout::GetAssetColor() const { return FLinearColor(0.20f, 0.75f, 0.75f); } // teal
TSoftClassPtr<UObject> UAssetDefinition_NexusLoadout::GetAssetClass() const { return UNexusEquipmentLoadout::StaticClass(); }
TConstArrayView<FAssetCategoryPath> UAssetDefinition_NexusLoadout::GetAssetCategories() const { return NexusAssetDef::NexusCategory(); }

// --- Input Context -----------------------------------------------------------
FText UAssetDefinition_NexusInputContext::GetAssetDisplayName() const { return LOCTEXT("InputContext", "Nexus Input Context"); }
FLinearColor UAssetDefinition_NexusInputContext::GetAssetColor() const { return FLinearColor(0.95f, 0.85f, 0.25f); } // gold
TSoftClassPtr<UObject> UAssetDefinition_NexusInputContext::GetAssetClass() const { return UNexusInputContext::StaticClass(); }
TConstArrayView<FAssetCategoryPath> UAssetDefinition_NexusInputContext::GetAssetCategories() const { return NexusAssetDef::NexusCategory(); }

// --- Input Config ------------------------------------------------------------
FText UAssetDefinition_NexusInputConfig::GetAssetDisplayName() const { return LOCTEXT("InputConfig", "Nexus Input Config"); }
FLinearColor UAssetDefinition_NexusInputConfig::GetAssetColor() const { return FLinearColor(0.80f, 0.62f, 0.15f); } // amber
TSoftClassPtr<UObject> UAssetDefinition_NexusInputConfig::GetAssetClass() const { return UNexusInputConfig::StaticClass(); }
TConstArrayView<FAssetCategoryPath> UAssetDefinition_NexusInputConfig::GetAssetCategories() const { return NexusAssetDef::NexusCategory(); }

#undef LOCTEXT_NAMESPACE
