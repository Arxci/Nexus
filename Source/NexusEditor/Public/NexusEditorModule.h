#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FNexusSelectionService;
class FSpawnTabArgs;
class SDockTab;
class SNexusCreatorWindow;
class UToolMenu;

/**
 * Editor module entry point. On startup it registers the Nexus tool tabs as
 * nomad tabs and adds entries to the level editor's Tools menu (as a single
 * Tools → Nexus submenu) plus a "Nexus" combo button on the Level Editor
 * toolbar. The Workbench is the suite's single home: a three-pane window
 * (Navigator | Tool | Inspector) with a Home page that folds in the old Hub's
 * cards and audit summary; the toolbar and Tools menu open it. The individual
 * tool tabs stay registered as optional tear-offs. The module also owns the
 * shared selection service (FNexusSelectionService) so a click in any tool
 * surfaces that asset in the Workbench's Inspector. The cross-asset validator
 * (UNexusContentGraphValidator) needs no manual registration — the editor's
 * validation subsystem discovers UEditorValidatorBase subclasses by reflection
 * once this module is loaded.
 */
class FNexusEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Open (or focus) the Creator tab and hand it Asset to add to its working set. */
	static void OpenCreatorWith(UObject* Asset);

	/**
	 * Register Creator as the current hand-off target so OpenCreatorWith routes
	 * subsequent assets to it. The Workbench calls this when it constructs its
	 * own Creator instance so that "open in Creator" actions stay coherent.
	 */
	static void RegisterCreator(TSharedRef<SNexusCreatorWindow> Creator);

	/**
	 * The module-owned shared selection service, or null before startup / after shutdown.
	 * Consumers (the Inspector) subscribe through this; producers should prefer SetSelection().
	 */
	static FNexusSelectionService* TrySelection();

	/**
	 * Convenience for a tool to publish "the designer just selected this asset" — null-safe,
	 * so a tool can call it without worrying about the service's lifetime. SourceTool is the
	 * caller's tab name (used for loop avoidance / reveal-in-source).
	 */
	static void SetSelection(UObject* Asset, FName SourceTool = NAME_None);

	/** Multi-object variant (bulk-edit): publishes several assets at once. Null-safe. */
	static void SetSelection(const TArray<UObject*>& Assets, FName SourceTool = NAME_None);

	/** Tab ids used to register each spawner and invoke it from menus / Workbench. */
	static const FName WorkbenchTabName;
	static const FName DashboardTabName;
	static const FName CreatorTabName;
	static const FName PreviewTabName;
	static const FName CraftingTabName;
	static const FName MatrixTabName;
	static const FName GridTabName;
	static const FName SandboxTabName;
	static const FName InventoryTabName;
	static const FName TagAuditTabName;
	static const FName EconomyTabName;
	static const FName DocsTabName;
	static const FName IconSheetTabName;
	static const FName InsightsTabName;

private:
	void RegisterMenus();

	/** Populate the Tools → Nexus submenu (and the toolbar combo's drop-down) with sectioned entries. */
	void FillNexusMenu(UToolMenu* Menu);

	TSharedRef<SDockTab> SpawnWorkbenchTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnDashboardTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnCreatorTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnPreviewTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnCraftingTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnMatrixTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnGridTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnSandboxTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnInventoryTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTagAuditTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnEconomyTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnDocsTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnIconSheetTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnInsightsTab(const FSpawnTabArgs& Args);

	/** The live Creator window, so other tools can hand assets to it. */
	static TWeakPtr<SNexusCreatorWindow> ActiveCreator;

	/** Shared selection model, owned for the module's lifetime (see TrySelection / SetSelection). */
	static TUniquePtr<FNexusSelectionService> SelectionService;
};
