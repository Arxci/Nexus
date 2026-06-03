#include "Hub/SNexusHub.h"

#include "NexusEditorModule.h"
#include "Manifest/NexusManifestBuilder.h"
#include "Shared/NexusEditorTools.h"
#include "Shared/NexusEditorWidgets.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateColor.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "NexusHub"

namespace
{
	/**
	 * One tool card: a click-anywhere button with an icon, bold title, and a one-liner.
	 * Used uniformly for every tool in the Hub so the suite reads as one product.
	 */
	TSharedRef<SWidget> MakeToolCard(const NexusEditorTools::FToolEntry& Entry)
	{
		const FName Captured = Entry.TabName;
		return SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
			.ContentPadding(FMargin(10.0f, 8.0f))
			.ToolTipText(Entry.Tooltip)
			.OnClicked_Lambda([Captured]()
			{
				FGlobalTabmanager::Get()->TryInvokeTab(Captured);
				return FReply::Handled();
			})
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				.Padding(0.0f, 0.0f, 12.0f, 0.0f)
				[
					SNew(SBox)
					.WidthOverride(24.0f)
					.HeightOverride(24.0f)
					[
						SNew(SImage)
						.Image(FAppStyle::Get().GetBrush(Entry.IconName))
						.ColorAndOpacity(FSlateColor::UseForeground())
					]
				]

				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(Entry.Label)
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 2.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(Entry.Description)
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						.Font(FCoreStyle::GetDefaultFontStyle("Regular", 9))
					]
				]
			];
	}

	/** Build one categorised section: a section header above a vertical stack of cards. */
	TSharedRef<SWidget> MakeCategorySection(NexusEditorTools::ECategory Category)
	{
		TSharedRef<SVerticalBox> Stack = SNew(SVerticalBox);
		for (const NexusEditorTools::FToolEntry& Entry : NexusEditorTools::All())
		{
			if (Entry.Category == Category)
			{
				Stack->AddSlot()
					.AutoHeight()
					.Padding(0.0f, 2.0f)
					[
						MakeToolCard(Entry)
					];
			}
		}

		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				NexusEditorWidgets::SectionHeader(NexusEditorTools::CategoryLabel(Category))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 12.0f)
			[
				Stack
			];
	}
}

void SNexusHub::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
		.Padding(0.0f)
		[
			SNew(SScrollBox)

			// === Header band: title + tagline ====================================
			+ SScrollBox::Slot()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
				.Padding(FMargin(16.0f, 12.0f))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HubTitle", "Nexus Authoring Suite"))
						.Font(FCoreStyle::GetDefaultFontStyle("Bold", 14))
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(0.0f, 2.0f, 0.0f, 0.0f)
					[
						SNew(STextBlock)
						.Text(LOCTEXT("HubTagline", "Tools for items, attachments, weapons, recipes, and content health."))
						.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					]
				]
			]

			// === Audit summary row ==============================================
			+ SScrollBox::Slot()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(FMargin(16.0f, 8.0f))
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Text(this, &SNexusHub::GetAuditSummaryText)
						.ColorAndOpacity(this, &SNexusHub::GetAuditSummaryColor)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(4.0f, 0.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("RunAudit", "Run Audit"))
						.ToolTipText(LOCTEXT("RunAuditTip", "Scan every Nexus item and attachment and refresh the summary."))
						.OnClicked(this, &SNexusHub::OnRefreshAuditClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(4.0f, 0.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("OpenDashboard", "Open Dashboard"))
						.ToolTipText(LOCTEXT("OpenDashboardTip", "Open the Content Dashboard to drill into findings."))
						.OnClicked(this, &SNexusHub::OnOpenDashboardClicked)
					]
				]
			]

			// === Categorised tool cards =========================================
			+ SScrollBox::Slot()
			.Padding(FMargin(16.0f, 12.0f, 16.0f, 0.0f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[ MakeCategorySection(NexusEditorTools::ECategory::Authoring) ]
				+ SVerticalBox::Slot().AutoHeight()
				[ MakeCategorySection(NexusEditorTools::ECategory::Inspection) ]
				+ SVerticalBox::Slot().AutoHeight()
				[ MakeCategorySection(NexusEditorTools::ECategory::Auditing) ]
			]

			// === Footer: cross-cutting actions ==================================
			+ SScrollBox::Slot()
			.Padding(FMargin(16.0f, 4.0f, 16.0f, 16.0f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[
					NexusEditorWidgets::SectionHeader(LOCTEXT("CategoryActions", "Actions"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0.0f, 6.0f, 0.0f, 0.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(0.0f, 0.0f, 8.0f, 0.0f)
					[
						SNew(SButton)
						.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
						.OnClicked(this, &SNexusHub::OnOpenWorkbenchClicked)
						.ToolTipText(LOCTEXT("OpenWorkbenchTip", "Open every Nexus tool inside a single Workbench window."))
						[
							SNew(STextBlock).Text(LOCTEXT("OpenWorkbench", "Open Workbench"))
						]
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.OnClicked(this, &SNexusHub::OnBuildLevelManifestClicked)
						.ToolTipText(LOCTEXT("BuildManifestTip", "Scan the open level for items/attachments and create or update its manifest, then open it in the Creator."))
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							.Padding(0.0f, 0.0f, 6.0f, 0.0f)
							[
								SNew(SImage).Image(FAppStyle::Get().GetBrush("Icons.Save"))
							]
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Center)
							[
								SNew(STextBlock).Text(LOCTEXT("BuildManifest", "Build Level Manifest"))
							]
						]
					]
				]
			]
		]
	];
}

FReply SNexusHub::OnRefreshAuditClicked()
{
	LastAudit = FNexusContentAudit::Run();
	bHasAuditResult = true;
	return FReply::Handled();
}

FReply SNexusHub::OnOpenDashboardClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FNexusEditorModule::DashboardTabName);
	return FReply::Handled();
}

FReply SNexusHub::OnOpenWorkbenchClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FNexusEditorModule::WorkbenchTabName);
	return FReply::Handled();
}

FReply SNexusHub::OnBuildLevelManifestClicked()
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
}

FText SNexusHub::GetAuditSummaryText() const
{
	if (!bHasAuditResult)
	{
		return LOCTEXT("AuditNotRun", "Audit not yet run — press Run Audit for a content-health snapshot.");
	}
	return FText::Format(
		LOCTEXT("AuditSummaryFmt", "{0} errors  ·  {1} warnings  ·  {2} items  ·  {3} attachments"),
		FText::AsNumber(LastAudit.NumErrors),
		FText::AsNumber(LastAudit.NumWarnings),
		FText::AsNumber(LastAudit.Items.Num()),
		FText::AsNumber(LastAudit.Attachments.Num()));
}

FSlateColor SNexusHub::GetAuditSummaryColor() const
{
	if (!bHasAuditResult)
	{
		return FSlateColor::UseSubduedForeground();
	}
	if (LastAudit.NumErrors > 0)
	{
		return FStyleColors::Error;
	}
	if (LastAudit.NumWarnings > 0)
	{
		return FStyleColors::Warning;
	}
	return FStyleColors::Success;
}

#undef LOCTEXT_NAMESPACE
