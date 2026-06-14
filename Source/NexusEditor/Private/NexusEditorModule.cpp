#include "NexusEditorModule.h"

#include "Dashboard/SNexusContentDashboard.h"
#include "Creation/SNexusCreatorWindow.h"
#include "Preview/SNexusAssemblyPreview.h"
#include "Crafting/SNexusCraftingTree.h"
#include "Matrix/SNexusAttachmentMatrix.h"
#include "Grid/SNexusGridPreview.h"
#include "Sandbox/SNexusInventorySandbox.h"
#include "Inventory/SNexusInventoryWorkspace.h"
#include "Tags/SNexusTagAudit.h"
#include "Economy/SNexusEconomyView.h"
#include "Docs/SNexusDocsBrowser.h"
#include "Insights/SNexusIconSheet.h"
#include "Insights/SNexusContentInsights.h"
#include "Workbench/SNexusWorkbench.h"
#include "Manifest/NexusManifestBuilder.h"
#include "Shared/NexusEditorSelection.h"
#include "Shared/NexusEditorTools.h"

#include "Editor.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Commands/UIAction.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Styling/AppStyle.h"
#include "Textures/SlateIcon.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "NexusEditor"

const FName FNexusEditorModule::WorkbenchTabName(TEXT("NexusWorkbench"));
const FName FNexusEditorModule::DashboardTabName(TEXT("NexusContentDashboard"));
const FName FNexusEditorModule::CreatorTabName(TEXT("NexusAssetCreator"));
const FName FNexusEditorModule::PreviewTabName(TEXT("NexusAssemblyPreview"));
const FName FNexusEditorModule::CraftingTabName(TEXT("NexusCraftingTree"));
const FName FNexusEditorModule::MatrixTabName(TEXT("NexusAttachmentMatrix"));
const FName FNexusEditorModule::GridTabName(TEXT("NexusGridPreview"));
const FName FNexusEditorModule::SandboxTabName(TEXT("NexusInventorySandbox"));
const FName FNexusEditorModule::InventoryTabName(TEXT("NexusInventoryWorkspace"));
const FName FNexusEditorModule::TagAuditTabName(TEXT("NexusTagAudit"));
const FName FNexusEditorModule::EconomyTabName(TEXT("NexusEconomyView"));
const FName FNexusEditorModule::DocsTabName(TEXT("NexusDocsBrowser"));
const FName FNexusEditorModule::IconSheetTabName(TEXT("NexusIconSheet"));
const FName FNexusEditorModule::InsightsTabName(TEXT("NexusContentInsights"));
TWeakPtr<SNexusCreatorWindow> FNexusEditorModule::ActiveCreator;
TUniquePtr<FNexusSelectionService> FNexusEditorModule::SelectionService;

void FNexusEditorModule::StartupModule()
{
	// Shared selection model, available to every tool for the module's lifetime.
	SelectionService = MakeUnique<FNexusSelectionService>();

	// Each tool is a nomad tab, hidden from the generic Window menu; we surface them
	// from a dedicated Tools → Nexus submenu and from the Workbench (its Home page
	// folds in the old Hub's cards). Individual tabs remain as optional tear-offs.
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			WorkbenchTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnWorkbenchTab))
		.SetDisplayName(LOCTEXT("WorkbenchTitle", "Nexus Workbench"))
		.SetTooltipText(LOCTEXT("WorkbenchTooltip", "Every Nexus tool hosted inside one window."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			DashboardTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnDashboardTab))
		.SetDisplayName(LOCTEXT("DashboardTitle", "Nexus Content Dashboard"))
		.SetTooltipText(LOCTEXT("DashboardTooltip", "Audit Nexus items and attachments for data issues."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			CreatorTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnCreatorTab))
		.SetDisplayName(LOCTEXT("CreatorTitle", "Nexus Asset Creator"))
		.SetTooltipText(LOCTEXT("CreatorTooltip", "Create items and attachments in one window."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			PreviewTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnPreviewTab))
		.SetDisplayName(LOCTEXT("PreviewTitle", "Nexus Assembly Preview"))
		.SetTooltipText(LOCTEXT("PreviewTooltip", "Preview resolved weapon stats with attachments and upgrade tiers."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			CraftingTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnCraftingTab))
		.SetDisplayName(LOCTEXT("CraftingTitle", "Nexus Crafting Tree"))
		.SetTooltipText(LOCTEXT("CraftingTooltip", "Browse crafting recipes and their dependency chains."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			MatrixTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnMatrixTab))
		.SetDisplayName(LOCTEXT("MatrixTitle", "Nexus Attachment Matrix"))
		.SetTooltipText(LOCTEXT("MatrixTooltip", "Attachment compatibility matrix (provides / requires / conflicts)."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			GridTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnGridTab))
		.SetDisplayName(LOCTEXT("GridTitle", "Nexus Grid Preview"))
		.SetTooltipText(LOCTEXT("GridTooltip", "Visualise each item's inventory grid footprint."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			SandboxTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnSandboxTab))
		.SetDisplayName(LOCTEXT("SandboxTitle", "Nexus Inventory Sandbox"))
		.SetTooltipText(LOCTEXT("SandboxTooltip", "Drag real items onto a real attaché grid — footprint and case-size tuning, live."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			InventoryTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnInventoryTab))
		.SetDisplayName(LOCTEXT("InventoryTitle", "Nexus Inventory"))
		.SetTooltipText(LOCTEXT("InventoryTooltip", "Audit item footprints and pack a real attaché case — one workspace."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			TagAuditTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnTagAuditTab))
		.SetDisplayName(LOCTEXT("TagAuditTitle", "Nexus Tag Audit"))
		.SetTooltipText(LOCTEXT("TagAuditTooltip", "Find orphaned identity tags no asset uses."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			EconomyTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnEconomyTab))
		.SetDisplayName(LOCTEXT("EconomyTitle", "Nexus Economy View"))
		.SetTooltipText(LOCTEXT("EconomyTooltip", "Item value-per-cell balance sheet with outliers flagged."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			DocsTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnDocsTab))
		.SetDisplayName(LOCTEXT("DocsTitle", "Nexus API Reference"))
		.SetTooltipText(LOCTEXT("DocsTooltip", "Browse every Nexus class, struct, and Blueprint-callable function — designer-friendly API docs auto-generated from C++."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			IconSheetTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnIconSheetTab))
		.SetDisplayName(LOCTEXT("IconSheetTitle", "Nexus Icon Sheet"))
		.SetTooltipText(LOCTEXT("IconSheetTooltip", "Contact sheet of every item icon at its grid footprint."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
			InsightsTabName,
			FOnSpawnTab::CreateRaw(this, &FNexusEditorModule::SpawnInsightsTab))
		.SetDisplayName(LOCTEXT("InsightsTitle", "Nexus Content Insights"))
		.SetTooltipText(LOCTEXT("InsightsTooltip", "Reachability, scarcity, localization, where-used, and attachment-build audits."))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	// ToolMenus may not be ready this early in startup; defer menu wiring.
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNexusEditorModule::RegisterMenus));
}

void FNexusEditorModule::ShutdownModule()
{
	// Drop the selection service first so any Inspector torn down during shutdown finds
	// it gone (TrySelection() returns null) and unsubscribes harmlessly.
	SelectionService.Reset();

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WorkbenchTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DashboardTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CreatorTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PreviewTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CraftingTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MatrixTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GridTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SandboxTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(InventoryTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TagAuditTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EconomyTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DocsTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(IconSheetTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(InsightsTabName);
	}
}

void FNexusEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	// === Tools → Nexus submenu ==============================================
	if (UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools"))
	{
		FToolMenuSection& Section = ToolsMenu->FindOrAddSection("Nexus");
		Section.AddSubMenu(
			"NexusSubmenu",
			LOCTEXT("NexusSubmenuLabel", "Nexus"),
			LOCTEXT("NexusSubmenuTooltip", "Authoring, inspection, and auditing tools for Nexus content."),
			FNewToolMenuDelegate::CreateRaw(this, &FNexusEditorModule::FillNexusMenu),
			false,
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Box"));
	}

	// === Level Editor toolbar: split combo button ===========================
	// Primary click opens the Workbench (the suite's home); drop-down shows the same submenu.
	if (UToolMenu* UserToolbar = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User"))
	{
		FToolMenuSection& Section = UserToolbar->FindOrAddSection("Nexus");
		FToolMenuEntry Entry = FToolMenuEntry::InitComboButton(
			"NexusToolsCombo",
			FUIAction(FExecuteAction::CreateLambda([]()
			{
				FGlobalTabmanager::Get()->TryInvokeTab(WorkbenchTabName);
			})),
			FNewToolMenuChoice(FNewToolMenuDelegate::CreateRaw(this, &FNexusEditorModule::FillNexusMenu)),
			LOCTEXT("NexusToolbarLabel", "Nexus"),
			LOCTEXT("NexusToolbarTooltip", "Open the Nexus Workbench.  Drop-down opens individual tools."),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Box"),
			false);
		Section.AddEntry(Entry);
	}

	// === Content Browser "+ Add" menu =======================================
	// Designers reach for the green Add button (or right-click empty space) to make
	// assets; the bare factories there create blank assets. Surface the Creator right
	// where that instinct lives so the better, template-driven path is one click away.
	if (UToolMenu* AddMenu = UToolMenus::Get()->ExtendMenu("ContentBrowser.AddNewContextMenu"))
	{
		FToolMenuSection& Section = AddMenu->FindOrAddSection("Nexus", LOCTEXT("CBNexusSection", "Nexus"));
		Section.AddMenuEntry(
			"OpenNexusCreatorFromAdd",
			LOCTEXT("CBCreatorLabel", "Nexus Asset Creator..."),
			LOCTEXT("CBCreatorTooltip", "Open the Nexus Creator to stamp items/attachments/recipes with templates and smart defaults (instead of a blank asset)."),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Plus"),
			FUIAction(FExecuteAction::CreateLambda([]()
			{
				FGlobalTabmanager::Get()->TryInvokeTab(CreatorTabName);
			})));
	}
}

void FNexusEditorModule::FillNexusMenu(UToolMenu* Menu)
{
	if (!Menu)
	{
		return;
	}

	// Helper to add one entry that invokes a registered tab.
	auto AddTabEntry = [](FToolMenuSection& Section, const FName EntryName, const FText& Label,
		const FText& Tooltip, const FName IconName, const FName TabName)
	{
		Section.AddMenuEntry(
			EntryName, Label, Tooltip,
			FSlateIcon(FAppStyle::GetAppStyleSetName(), IconName),
			FUIAction(FExecuteAction::CreateLambda([TabName]()
			{
				FGlobalTabmanager::Get()->TryInvokeTab(TabName);
			})));
	};

	// --- The Workbench (the suite's single home) at the top ----------------
	{
		FToolMenuSection& Section = Menu->FindOrAddSection(
			"NexusLaunchers", LOCTEXT("NexusLaunchersHeader", "Home"));
		AddTabEntry(Section, "OpenNexusWorkbench",
			LOCTEXT("OpenWorkbenchLabel", "Open Nexus Workbench"),
			LOCTEXT("OpenWorkbenchTooltip", "The Nexus suite in one window — Home page, every tool, and a shared Inspector."),
			TEXT("Icons.Layout"), WorkbenchTabName);
	}

	// --- One section per category, ordered by the registry -----------------
	auto AddCategorySection = [Menu, &AddTabEntry](NexusEditorTools::ECategory Category, const FName SectionId)
	{
		FToolMenuSection& Section = Menu->FindOrAddSection(SectionId, NexusEditorTools::CategoryLabel(Category));
		for (const NexusEditorTools::FToolEntry& Tool : NexusEditorTools::All())
		{
			if (Tool.Category == Category)
			{
				AddTabEntry(Section, Tool.MenuEntryName, Tool.Label, Tool.Tooltip, Tool.IconName, Tool.TabName);
			}
		}
	};
	AddCategorySection(NexusEditorTools::ECategory::Authoring,  "NexusAuthoring");
	AddCategorySection(NexusEditorTools::ECategory::Inspection, "NexusInspection");
	AddCategorySection(NexusEditorTools::ECategory::Auditing,   "NexusAuditing");

	// --- Cross-cutting action: build a level manifest ----------------------
	{
		FToolMenuSection& Section = Menu->FindOrAddSection(
			"NexusActions", LOCTEXT("NexusActionsHeader", "Actions"));
		Section.AddMenuEntry(
			"BuildNexusLevelManifest",
			LOCTEXT("ManifestMenuEntry", "Build Level Manifest from Current Level"),
			LOCTEXT("ManifestMenuEntryTooltip", "Scan the open level for items/attachments and create or update its manifest."),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Save"),
			FUIAction(FExecuteAction::CreateLambda([]()
			{
				FString Message;
				UNexusLevelManifest* Manifest = FNexusManifestBuilder::BuildFromCurrentLevel(Message);

				FNotificationInfo Info(FText::FromString(Message));
				Info.ExpireDuration = 7.0f;
				FSlateNotificationManager::Get().AddNotification(Info);

				if (Manifest)
				{
					FNexusEditorModule::OpenCreatorWith(Manifest);
				}
			})));
	}
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnWorkbenchTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusWorkbench)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnDashboardTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusContentDashboard)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnCreatorTab(const FSpawnTabArgs& Args)
{
	TSharedRef<SNexusCreatorWindow> Creator = SNew(SNexusCreatorWindow);
	RegisterCreator(Creator);
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			Creator
		];
}

void FNexusEditorModule::RegisterCreator(TSharedRef<SNexusCreatorWindow> Creator)
{
	ActiveCreator = Creator;
}

FNexusSelectionService* FNexusEditorModule::TrySelection()
{
	return SelectionService.Get();
}

void FNexusEditorModule::SetSelection(UObject* Asset, FName SourceTool)
{
	if (SelectionService.IsValid())
	{
		SelectionService->SetSelection(Asset, SourceTool);
	}
}

void FNexusEditorModule::SetSelection(const TArray<UObject*>& Assets, FName SourceTool)
{
	if (SelectionService.IsValid())
	{
		SelectionService->SetSelection(Assets, SourceTool);
	}
}

void FNexusEditorModule::OpenCreatorWith(UObject* Asset)
{
	if (!Asset)
	{
		return;
	}
	// If a Creator already exists (standalone tab or inside the Workbench), reuse it.
	// Only spawn the standalone tab when no Creator is live, so opening from the Hub
	// while the Workbench is up doesn't pop a competing window.
	if (!ActiveCreator.IsValid())
	{
		FGlobalTabmanager::Get()->TryInvokeTab(CreatorTabName);
	}
	if (TSharedPtr<SNexusCreatorWindow> Creator = ActiveCreator.Pin())
	{
		Creator->LoadAsset(Asset);
	}
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnPreviewTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusAssemblyPreview)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnCraftingTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusCraftingTree)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnMatrixTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusAttachmentMatrix)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnGridTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusGridPreview)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnSandboxTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusInventorySandbox)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnInventoryTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusInventoryWorkspace)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnTagAuditTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusTagAudit)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnEconomyTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusEconomyView)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnDocsTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusDocsBrowser)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnIconSheetTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusIconSheet)
		];
}

TSharedRef<SDockTab> FNexusEditorModule::SpawnInsightsTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SNexusContentInsights)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNexusEditorModule, NexusEditor)
