#include "Inventory/SNexusInventoryWorkspace.h"

#include "Grid/SNexusGridPreview.h"
#include "Sandbox/SNexusInventorySandbox.h"
#include "Inventory/SNexusCaseDesigner.h"
#include "Shared/NexusEditorWidgets.h"

#include "Styling/AppStyle.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "NexusInventoryWorkspace"

void SNexusInventoryWorkspace::Construct(const FArguments& InArgs)
{
	// A mode toggle button styled as a segment (mirrors the Creator's mode toggle).
	const auto ModeButton = [this](EMode ButtonMode, const FText& Label, const FText& Tip) -> TSharedRef<SWidget>
	{
		return SNew(SCheckBox)
			.Style(FAppStyle::Get(), "DetailsView.SectionButton")
			.Padding(FMargin(16.0f, 4.0f))
			.ToolTipText(Tip)
			.IsChecked_Lambda([this, ButtonMode]()
			{
				return Mode == ButtonMode ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
			})
			.OnCheckStateChanged_Lambda([this, ButtonMode](ECheckBoxState NewState)
			{
				if (NewState == ECheckBoxState::Checked) { Mode = ButtonMode; }
			})
			[
				SNew(STextBlock).Text(Label).Justification(ETextJustify::Center)
			];
	};

	ChildSlot
	[
		SNew(SVerticalBox)

		// === Mode toggle =====================================================
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
			.Padding(FMargin(10.0f, 6.0f))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[ NexusEditorWidgets::SectionLabel(LOCTEXT("ModeLabel", "MODE")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
				[ ModeButton(EMode::Audit, LOCTEXT("ModeAudit", "Audit"),
					LOCTEXT("ModeAuditTip", "Every item by footprint, with mis-sized items flagged.")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[ ModeButton(EMode::Pack, LOCTEXT("ModePack", "Pack"),
					LOCTEXT("ModePackTip", "Drag real items into a real case and tune its size.")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[ ModeButton(EMode::Cases, LOCTEXT("ModeCases", "Cases"),
					LOCTEXT("ModeCasesTip", "Browse attaché cases — the grid and charm slots each provides.")) ]
			]
		]

		// === Mode content ====================================================
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SNew(SWidgetSwitcher)
			.WidgetIndex(this, &SNexusInventoryWorkspace::GetModeIndex)

			+ SWidgetSwitcher::Slot()
			[ SNew(SNexusGridPreview) ]

			+ SWidgetSwitcher::Slot()
			[ SNew(SNexusInventorySandbox) ]

			+ SWidgetSwitcher::Slot()
			[ SNew(SNexusCaseDesigner) ]
		]
	];
}

#undef LOCTEXT_NAMESPACE
