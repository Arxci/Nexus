#include "Shared/NexusEditorTools.h"

#include "NexusEditorModule.h"

#define LOCTEXT_NAMESPACE "NexusEditorTools"

namespace NexusEditorTools
{
	const TArray<FToolEntry>& All()
	{
		static const TArray<FToolEntry> Entries = {
			// Authoring -------------------------------------------------------
			{
				FNexusEditorModule::CreatorTabName,
				TEXT("OpenNexusAssetCreator"),
				LOCTEXT("CreatorLabel", "Asset Creator"),
				LOCTEXT("CreatorTooltip", "Create items and attachments in one window."),
				LOCTEXT("CreatorDesc", "Stamp out items, attachments, recipes, manifests, and loadouts."),
				TEXT("Icons.Plus"),
				ECategory::Authoring,
				/*bUsesSharedInspector=*/ false,   // the Creator embeds its own Details panel
			},

			// Inspection ------------------------------------------------------
			{
				FNexusEditorModule::PreviewTabName,
				TEXT("OpenNexusAssemblyPreview"),
				LOCTEXT("PreviewLabel", "Assembly Preview"),
				LOCTEXT("PreviewTooltip", "Preview resolved weapon stats with attachments and upgrade tiers."),
				LOCTEXT("PreviewDesc", "Resolved weapon stats with attachments and upgrade tiers."),
				TEXT("Icons.Adjust"),
				ECategory::Inspection,
			},
			{
				FNexusEditorModule::CraftingTabName,
				TEXT("OpenNexusCraftingTree"),
				LOCTEXT("CraftingLabel", "Crafting Tree"),
				LOCTEXT("CraftingTooltip", "Browse crafting recipes and their dependency chains."),
				LOCTEXT("CraftingDesc", "Recipes and their input / output dependency chains."),
				TEXT("Icons.Layout"),
				ECategory::Inspection,
			},
			{
				FNexusEditorModule::MatrixTabName,
				TEXT("OpenNexusAttachmentMatrix"),
				LOCTEXT("MatrixLabel", "Attachment Matrix"),
				LOCTEXT("MatrixTooltip", "Attachment compatibility matrix (provides / requires / conflicts)."),
				LOCTEXT("MatrixDesc", "Compatibility grid of provides / requires / conflicts."),
				TEXT("Icons.Filter"),
				ECategory::Inspection,
			},
			{
				FNexusEditorModule::InventoryTabName,
				TEXT("OpenNexusInventory"),
				LOCTEXT("InventoryLabel", "Inventory"),
				LOCTEXT("InventoryTooltip", "Audit item footprints (mis-sized flagged) and pack a real attaché case — one workspace."),
				LOCTEXT("InventoryDesc", "Audit footprints and pack the real inventory grid — footprint and case-size tuning, live."),
				TEXT("Icons.Box"),
				ECategory::Inspection,
			},
			{
				FNexusEditorModule::IconSheetTabName,
				TEXT("OpenNexusIconSheet"),
				LOCTEXT("IconSheetLabel", "Icon Sheet"),
				LOCTEXT("IconSheetTooltip", "Contact sheet of every item icon, framed by category — spot missing/odd art fast."),
				LOCTEXT("IconSheetDesc", "Every item's icon at its grid footprint, framed by category."),
				TEXT("Icons.Layout"),
				ECategory::Inspection,
			},
			{
				FNexusEditorModule::LiveInventoryTabName,
				TEXT("OpenNexusLiveInventory"),
				LOCTEXT("LiveInventoryLabel", "Live Inventory"),
				LOCTEXT("LiveInventoryTooltip", "Inspect the player's real inventory during Play-In-Editor — grid, weight, case, charms — and spawn items / swap the case live."),
				LOCTEXT("LiveInventoryDesc", "The player's real runtime container during PIE: grid, weight, case, charms — read-only until you spawn or swap."),
				TEXT("Icons.Box"),
				ECategory::Inspection,
			},
			{
				FNexusEditorModule::DocsTabName,
				TEXT("OpenNexusDocs"),
				LOCTEXT("DocsLabel", "API Reference"),
				LOCTEXT("DocsTooltip", "Designer-friendly docs for every Nexus class, struct, and Blueprint-callable function — auto-generated from C++."),
				LOCTEXT("DocsDesc", "Auto-generated reference for every Blueprint-callable function and exposed property."),
				TEXT("Icons.Help"),
				ECategory::Inspection,
			},

			// Auditing --------------------------------------------------------
			{
				FNexusEditorModule::DashboardTabName,
				TEXT("OpenNexusContentDashboard"),
				LOCTEXT("DashboardLabel", "Content Dashboard"),
				LOCTEXT("DashboardTooltip", "Audit items and attachments for data issues."),
				LOCTEXT("DashboardDesc", "Cross-asset audit findings, plus items and attachments tables."),
				TEXT("Icons.Search"),
				ECategory::Auditing,
			},
			{
				FNexusEditorModule::TagAuditTabName,
				TEXT("OpenNexusTagAudit"),
				LOCTEXT("TagAuditLabel", "Tag Audit"),
				LOCTEXT("TagAuditTooltip", "Find orphaned identity tags no asset uses."),
				LOCTEXT("TagAuditDesc", "Identity tags that no asset references."),
				TEXT("Icons.Warning"),
				ECategory::Auditing,
			},
			{
				FNexusEditorModule::EconomyTabName,
				TEXT("OpenNexusEconomyView"),
				LOCTEXT("EconomyLabel", "Economy View"),
				LOCTEXT("EconomyTooltip", "Item value-per-cell balance sheet with outliers flagged."),
				LOCTEXT("EconomyDesc", "Value-per-cell balance sheet with outliers flagged."),
				TEXT("Icons.Star"),
				ECategory::Auditing,
			},
			{
				FNexusEditorModule::InsightsTabName,
				TEXT("OpenNexusContentInsights"),
				LOCTEXT("InsightsLabel", "Content Insights"),
				LOCTEXT("InsightsTooltip", "Reachability (soft-lock catcher), scarcity, localization, where-used, and attachment-build audits."),
				LOCTEXT("InsightsDesc", "Reachability, scarcity, localization, where-used, and buildability — one place."),
				TEXT("Icons.Search"),
				ECategory::Auditing,
			},
		};
		return Entries;
	}

	const FToolEntry* Find(FName TabName)
	{
		for (const FToolEntry& Entry : All())
		{
			if (Entry.TabName == TabName)
			{
				return &Entry;
			}
		}
		return nullptr;
	}

	FText CategoryLabel(ECategory Category)
	{
		switch (Category)
		{
		case ECategory::Authoring:  return LOCTEXT("CategoryAuthoring",  "Authoring");
		case ECategory::Inspection: return LOCTEXT("CategoryInspection", "Inspection");
		case ECategory::Auditing:   return LOCTEXT("CategoryAuditing",   "Auditing");
		}
		return FText::GetEmpty();
	}
}

#undef LOCTEXT_NAMESPACE
