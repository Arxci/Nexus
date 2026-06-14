#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FSpawnTabArgs;
class SDockTab;
class SNexusCreatorWindow;
class UToolMenu;

/**
 * Editor module entry point. On startup it registers the Nexus tool tabs as
 * nomad tabs and adds entries to the level editor's Tools menu (as a single
 * Tools → Nexus submenu) plus a "Nexus" combo button on the Level Editor
 * toolbar. The Hub and the Workbench are first-class tabs in their own right:
 * the Hub is a launcher with categorised tool cards and an audit summary; the
 * Workbench hosts every tool inside one window via a sidebar selector. The
 * cross-asset validator (UNexusContentGraphValidator) needs no manual
 * registration — the editor's validation subsystem discovers
 * UEditorValidatorBase subclasses by reflection once this module is loaded.
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

	/** Tab ids used to register each spawner and invoke it from menus / Hub / Workbench. */
	static const FName HubTabName;
	static const FName WorkbenchTabName;
	static const FName DashboardTabName;
	static const FName CreatorTabName;
	static const FName PreviewTabName;
	static const FName CraftingTabName;
	static const FName MatrixTabName;
	static const FName GridTabName;
	static const FName SandboxTabName;
	static const FName TagAuditTabName;
	static const FName EconomyTabName;
	static const FName DocsTabName;

private:
	void RegisterMenus();

	/** Populate the Tools → Nexus submenu (and the toolbar combo's drop-down) with sectioned entries. */
	void FillNexusMenu(UToolMenu* Menu);

	TSharedRef<SDockTab> SpawnHubTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnWorkbenchTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnDashboardTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnCreatorTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnPreviewTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnCraftingTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnMatrixTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnGridTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnSandboxTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTagAuditTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnEconomyTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnDocsTab(const FSpawnTabArgs& Args);

	/** The live Creator window, so other tools can hand assets to it. */
	static TWeakPtr<SNexusCreatorWindow> ActiveCreator;
};
