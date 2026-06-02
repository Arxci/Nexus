#include "NexusEditorModule.h"

#include "Dashboard/SNexusContentDashboard.h"
#include "Creation/SNexusCreatorWindow.h"
#include "Preview/SNexusAssemblyPreview.h"
#include "Crafting/SNexusCraftingTree.h"
#include "Matrix/SNexusAttachmentMatrix.h"
#include "Manifest/NexusManifestBuilder.h"

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

const FName FNexusEditorModule::DashboardTabName(TEXT("NexusContentDashboard"));
const FName FNexusEditorModule::CreatorTabName(TEXT("NexusAssetCreator"));
const FName FNexusEditorModule::PreviewTabName(TEXT("NexusAssemblyPreview"));
const FName FNexusEditorModule::CraftingTabName(TEXT("NexusCraftingTree"));
const FName FNexusEditorModule::MatrixTabName(TEXT("NexusAttachmentMatrix"));
TWeakPtr<SNexusCreatorWindow> FNexusEditorModule::ActiveCreator;

void FNexusEditorModule::StartupModule()
{
	// The tab itself is hidden from the generic Window menu; we surface it from a
	// dedicated Tools entry instead (see RegisterMenus).
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

	// ToolMenus may not be ready this early in startup; defer menu wiring.
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNexusEditorModule::RegisterMenus));
}

void FNexusEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DashboardTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CreatorTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PreviewTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CraftingTabName);
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MatrixTabName);
	}
}

void FNexusEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
	if (!ToolsMenu)
	{
		return;
	}

	FToolMenuSection& Section = ToolsMenu->FindOrAddSection("Nexus");
	Section.AddMenuEntry(
		"OpenNexusContentDashboard",
		LOCTEXT("MenuEntry", "Nexus Content Dashboard"),
		LOCTEXT("MenuEntryTooltip", "Audit items and attachments for data issues."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Search"),
		FUIAction(FExecuteAction::CreateLambda([]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FNexusEditorModule::DashboardTabName);
		})));

	Section.AddMenuEntry(
		"OpenNexusAssetCreator",
		LOCTEXT("CreatorMenuEntry", "Nexus Asset Creator"),
		LOCTEXT("CreatorMenuEntryTooltip", "Create items and attachments in one window."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Plus"),
		FUIAction(FExecuteAction::CreateLambda([]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FNexusEditorModule::CreatorTabName);
		})));

	Section.AddMenuEntry(
		"OpenNexusAssemblyPreview",
		LOCTEXT("PreviewMenuEntry", "Nexus Assembly Preview"),
		LOCTEXT("PreviewMenuEntryTooltip", "Preview resolved weapon stats with attachments and upgrade tiers."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Layout"),
		FUIAction(FExecuteAction::CreateLambda([]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FNexusEditorModule::PreviewTabName);
		})));

	Section.AddMenuEntry(
		"OpenNexusCraftingTree",
		LOCTEXT("CraftingMenuEntry", "Nexus Crafting Tree"),
		LOCTEXT("CraftingMenuEntryTooltip", "Browse crafting recipes and their dependency chains."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Layout"),
		FUIAction(FExecuteAction::CreateLambda([]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FNexusEditorModule::CraftingTabName);
		})));

	Section.AddMenuEntry(
		"OpenNexusAttachmentMatrix",
		LOCTEXT("MatrixMenuEntry", "Nexus Attachment Matrix"),
		LOCTEXT("MatrixMenuEntryTooltip", "Attachment compatibility matrix (provides / requires / conflicts)."),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Layout"),
		FUIAction(FExecuteAction::CreateLambda([]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FNexusEditorModule::MatrixTabName);
		})));

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
	ActiveCreator = Creator;
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			Creator
		];
}

void FNexusEditorModule::OpenCreatorWith(UObject* Asset)
{
	if (!Asset)
	{
		return;
	}
	FGlobalTabmanager::Get()->TryInvokeTab(CreatorTabName);
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

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNexusEditorModule, NexusEditor)
