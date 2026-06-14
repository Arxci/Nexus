#include "Workbench/SNexusWorkbench.h"

#include "NexusEditorModule.h"
#include "Manifest/NexusManifestBuilder.h"
#include "Shared/NexusEditorTools.h"
#include "Shared/NexusEditorWidgets.h"

#include "Crafting/SNexusCraftingTree.h"
#include "Creation/SNexusCreatorWindow.h"
#include "Dashboard/SNexusContentDashboard.h"
#include "Docs/SNexusDocsBrowser.h"
#include "Economy/SNexusEconomyView.h"
#include "Grid/SNexusGridPreview.h"
#include "Sandbox/SNexusInventorySandbox.h"
#include "Matrix/SNexusAttachmentMatrix.h"
#include "Preview/SNexusAssemblyPreview.h"
#include "Tags/SNexusTagAudit.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "NexusWorkbench"

void SNexusWorkbench::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(0.0f)
		[
			SNew(SVerticalBox)

			// === Header band: workbench branding ================================
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
				.Padding(FMargin(12.0f, 6.0f))
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("WorkbenchTitle", "Nexus Workbench"))
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
					]
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					.VAlign(VAlign_Center)
					.Padding(12.0f, 0.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(this, &SNexusWorkbench::GetCurrentToolLabel)
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					]
				]
			]

			// === Sidebar + content split ========================================
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SSplitter)
				.Orientation(Orient_Horizontal)

				+ SSplitter::Slot()
				.Value(0.22f)
				[
					BuildSidebar()
				]

				+ SSplitter::Slot()
				.Value(0.78f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
					.Padding(0.0f)
					[
						SAssignNew(ContentBox, SBox)
						[
							SNew(SBox)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							.Padding(32.0f)
							[
								SNew(STextBlock)
								.Text(LOCTEXT("WorkbenchEmpty", "Pick a tool from the sidebar to get started."))
								.ColorAndOpacity(FSlateColor::UseSubduedForeground())
							]
						]
					]
				]
			]
		]
	];
}

TSharedRef<SWidget> SNexusWorkbench::BuildSidebar()
{
	TSharedRef<SVerticalBox> Stack = SNew(SVerticalBox);

	auto AddCategoryHeader = [this, &Stack](NexusEditorTools::ECategory Category)
	{
		Stack->AddSlot()
			.AutoHeight()
			.Padding(8.0f, 12.0f, 8.0f, 4.0f)
			[
				NexusEditorWidgets::SectionLabel(
					NexusEditorTools::CategoryLabel(Category).ToUpper())
			];

		for (const NexusEditorTools::FToolEntry& Entry : NexusEditorTools::All())
		{
			if (Entry.Category == Category)
			{
				Stack->AddSlot()
					.AutoHeight()
					.Padding(4.0f, 1.0f)
					[
						BuildSidebarEntry(Entry.TabName, Entry.Label, Entry.IconName, Entry.Tooltip)
					];
			}
		}
	};

	AddCategoryHeader(NexusEditorTools::ECategory::Authoring);
	AddCategoryHeader(NexusEditorTools::ECategory::Inspection);
	AddCategoryHeader(NexusEditorTools::ECategory::Auditing);

	// Footer: cross-cutting actions that don't have their own tab.
	Stack->AddSlot()
		.AutoHeight()
		.Padding(8.0f, 12.0f, 8.0f, 4.0f)
		[
			NexusEditorWidgets::SectionLabel(LOCTEXT("ActionsLabel", "ACTIONS"))
		];

	Stack->AddSlot()
		.AutoHeight()
		.Padding(4.0f, 1.0f)
		[
			SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
			.ContentPadding(FMargin(8.0f, 6.0f))
			.HAlign(HAlign_Left)
			.ToolTipText(LOCTEXT("BuildManifestTip", "Scan the open level for items/attachments and create or update its manifest."))
			.OnClicked_Lambda([]()
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
				return FReply::Handled();
			})
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.0f, 0.0f, 8.0f, 0.0f)
				[
					SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.Save"))
				]
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(LOCTEXT("BuildManifest", "Build Level Manifest"))
				]
			]
		];

	return SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(0.0f)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				Stack
			]
		];
}

TSharedRef<SWidget> SNexusWorkbench::BuildSidebarEntry(FName TabName, const FText& Label, const FName IconName, const FText& Tooltip)
{
	return SNew(SCheckBox)
		.Style(FAppStyle::Get(), "DetailsView.SectionButton")
		.Padding(FMargin(10.0f, 6.0f))
		.ToolTipText(Tooltip)
		.IsChecked_Lambda([this, TabName]()
		{
			return CurrentTab == TabName ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		})
		.OnCheckStateChanged_Lambda([this, TabName](ECheckBoxState NewState)
		{
			if (NewState == ECheckBoxState::Checked)
			{
				ShowTool(TabName);
			}
		})
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.0f, 0.0f, 8.0f, 0.0f)
			[
				SNew(SBox)
				.WidthOverride(16.0f)
				.HeightOverride(16.0f)
				[
					SNew(SImage).Image(FAppStyle::Get().GetBrush(IconName))
				]
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock).Text(Label)
			]
		];
}

void SNexusWorkbench::ShowTool(FName TabName)
{
	if (!ContentBox.IsValid())
	{
		return;
	}

	TSharedPtr<SWidget>& Cached = ToolCache.FindOrAdd(TabName);
	if (!Cached.IsValid())
	{
		Cached = ConstructToolWidget(TabName);
	}

	if (Cached.IsValid())
	{
		CurrentTab = TabName;
		ContentBox->SetContent(Cached.ToSharedRef());
	}
}

TSharedPtr<SWidget> SNexusWorkbench::ConstructToolWidget(FName TabName) const
{
	if (TabName == FNexusEditorModule::DashboardTabName) { return SNew(SNexusContentDashboard); }
	if (TabName == FNexusEditorModule::CreatorTabName)
	{
		// Reassigns the module's ActiveCreator weak ptr so hand-offs target this instance.
		TSharedRef<SNexusCreatorWindow> Creator = SNew(SNexusCreatorWindow);
		FNexusEditorModule::RegisterCreator(Creator);
		return Creator;
	}
	if (TabName == FNexusEditorModule::PreviewTabName)  { return SNew(SNexusAssemblyPreview); }
	if (TabName == FNexusEditorModule::CraftingTabName) { return SNew(SNexusCraftingTree); }
	if (TabName == FNexusEditorModule::MatrixTabName)   { return SNew(SNexusAttachmentMatrix); }
	if (TabName == FNexusEditorModule::GridTabName)     { return SNew(SNexusGridPreview); }
	if (TabName == FNexusEditorModule::SandboxTabName)  { return SNew(SNexusInventorySandbox); }
	if (TabName == FNexusEditorModule::TagAuditTabName) { return SNew(SNexusTagAudit); }
	if (TabName == FNexusEditorModule::EconomyTabName)  { return SNew(SNexusEconomyView); }
	if (TabName == FNexusEditorModule::DocsTabName)     { return SNew(SNexusDocsBrowser); }
	return nullptr;
}

FText SNexusWorkbench::GetCurrentToolLabel() const
{
	if (CurrentTab.IsNone())
	{
		return FText::GetEmpty();
	}
	if (const NexusEditorTools::FToolEntry* Entry = NexusEditorTools::Find(CurrentTab))
	{
		return Entry->Label;
	}
	return FText::GetEmpty();
}

#undef LOCTEXT_NAMESPACE
