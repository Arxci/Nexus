#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FSpawnTabArgs;
class SDockTab;
class SNexusCreatorWindow;

/**
 * Editor module entry point. On startup it registers the Nexus Content
 * Dashboard as a nomad tab and adds an entry to the level editor's Tools menu;
 * the cross-asset validator (UNexusContentGraphValidator) needs no manual
 * registration — the editor's validation subsystem discovers UEditorValidatorBase
 * subclasses by reflection once this module is loaded.
 */
class FNexusEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** Open (or focus) the Creator tab and hand it Asset to add to its working set. */
	static void OpenCreatorWith(UObject* Asset);

private:
	void RegisterMenus();
	TSharedRef<SDockTab> SpawnDashboardTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnCreatorTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnPreviewTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnCraftingTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnMatrixTab(const FSpawnTabArgs& Args);

	/** Tab ids used to register each spawner and invoke it from the Tools menu. */
	static const FName DashboardTabName;
	static const FName CreatorTabName;
	static const FName PreviewTabName;
	static const FName CraftingTabName;
	static const FName MatrixTabName;

	/** The live Creator window, so other tools can hand assets to it. */
	static TWeakPtr<SNexusCreatorWindow> ActiveCreator;
};
