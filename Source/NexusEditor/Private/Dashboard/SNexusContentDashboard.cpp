#include "Dashboard/SNexusContentDashboard.h"

#include "Editor.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Csv/NexusCsvRoundTrip.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/MessageDialog.h"
#include "Misc/Paths.h"
#include "ScopedTransaction.h"

#include "Creation/NexusAssetCreationLibrary.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

#define LOCTEXT_NAMESPACE "NexusContentDashboard"

namespace NexusDashboard
{
	// Column ids. Name/Identity are shared between the two tables.
	const FName ColName("Name");
	const FName ColIdentity("Identity");
	const FName ColCategory("Category");
	const FName ColGrid("Grid");
	const FName ColValue("Value");
	const FName ColDamage("Damage");
	const FName ColRPM("RPM");
	const FName ColMag("Mag");
	const FName ColProvided("Provided");
	const FName ColRequired("Required");
	const FName ColConflict("Conflict");
	const FName ColMesh("Mesh");
	const FName ColIssues("Issues");

	/** A single cell: padded, eliding text with a full-value tooltip. */
	TSharedRef<SWidget> Cell(const FString& Text, const FSlateColor& Color = FSlateColor::UseForeground(), const FString& Tooltip = FString())
	{
		return SNew(SBox)
			.Padding(FMargin(6.0f, 2.0f))
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Text))
				.ColorAndOpacity(Color)
				.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
				.ToolTipText(FText::FromString(Tooltip.IsEmpty() ? Text : Tooltip))
			];
	}

	/** Titled band above each table. */
	TSharedRef<SWidget> SectionHeader(const FText& Title)
	{
		return SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Header"))
			.Padding(FMargin(8.0f, 4.0f))
			[
				SNew(STextBlock)
				.Text(Title)
				.Font(FCoreStyle::GetDefaultFontStyle("Bold", 11))
			];
	}
}

/** Multi-column row for the items table. */
class SNexusItemTableRow : public SMultiColumnTableRow<TSharedPtr<FNexusItemRow>>
{
public:
	SLATE_BEGIN_ARGS(SNexusItemTableRow) {}
		SLATE_ARGUMENT(TSharedPtr<FNexusItemRow>, Row)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
	{
		Row = InArgs._Row;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), Owner);
	}

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override
	{
		using namespace NexusDashboard;
		if (Column == ColName)     { return Cell(Row->DisplayName); }
		if (Column == ColIdentity) { return Cell(Row->IdentityTag); }
		if (Column == ColCategory) { return Cell(Row->Category); }
		if (Column == ColGrid)     { return Cell(FString::Printf(TEXT("%dx%d"), Row->Grid.X, Row->Grid.Y)); }
		if (Column == ColValue)    { return Cell(FString::FromInt(Row->BaseValue)); }
		if (Column == ColDamage)   { return Cell(Row->Damage, FSlateColor::UseForeground(), Row->StatsTooltip); }
		if (Column == ColRPM)      { return Cell(Row->RPM, FSlateColor::UseForeground(), Row->StatsTooltip); }
		if (Column == ColMag)      { return Cell(Row->Mag, FSlateColor::UseForeground(), Row->StatsTooltip); }
		return SNullWidget::NullWidget;
	}

private:
	TSharedPtr<FNexusItemRow> Row;
};

/** Multi-column row for the attachments table; flags problems in colour. */
class SNexusAttachmentTableRow : public SMultiColumnTableRow<TSharedPtr<FNexusAttachmentRow>>
{
public:
	SLATE_BEGIN_ARGS(SNexusAttachmentTableRow) {}
		SLATE_ARGUMENT(TSharedPtr<FNexusAttachmentRow>, Row)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
	{
		Row = InArgs._Row;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), Owner);
	}

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override
	{
		using namespace NexusDashboard;
		if (Column == ColName)     { return Cell(Row->DisplayName); }
		if (Column == ColIdentity) { return Cell(Row->IdentityTag); }
		if (Column == ColProvided) { return Cell(Row->Provided); }
		if (Column == ColRequired) { return Cell(Row->Required); }
		if (Column == ColConflict) { return Cell(Row->Conflict); }
		if (Column == ColMesh)
		{
			return Cell(Row->bHasMesh ? TEXT("Yes") : TEXT("No"),
				Row->bHasMesh ? FSlateColor::UseForeground() : FSlateColor(FStyleColors::Error));
		}
		if (Column == ColIssues)
		{
			return Cell(Row->Issues,
				Row->Issues.IsEmpty() ? FSlateColor::UseForeground() : FSlateColor(FStyleColors::Warning));
		}
		return SNullWidget::NullWidget;
	}

private:
	TSharedPtr<FNexusAttachmentRow> Row;
};

void SNexusContentDashboard::Construct(const FArguments& InArgs)
{
	using namespace NexusDashboard;

	// Build the model before the list views bind to it (their ListItemsSource
	// points at the Audit members, whose addresses stay stable across refreshes).
	RebuildAudit();

	ChildSlot
	[
		SNew(SVerticalBox)

		// Toolbar: refresh + live summary.
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(8.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.Text(LOCTEXT("Refresh", "Refresh / Run Audit"))
				.OnClicked(this, &SNexusContentDashboard::OnRefreshClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("ExportCsv", "Export CSV"))
				.ToolTipText(LOCTEXT("ExportCsvTip", "Write the item/weapon roster to a spreadsheet for balancing."))
				.OnClicked(this, &SNexusContentDashboard::OnExportCsvClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("ImportCsv", "Import CSV"))
				.ToolTipText(LOCTEXT("ImportCsvTip", "Apply an edited spreadsheet back onto the assets (shows a confirm first; undoable)."))
				.OnClicked(this, &SNexusContentDashboard::OnImportCsvClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("AutoTagUntagged", "Auto-tag Untagged"))
				.ToolTipText(LOCTEXT("AutoTagUntaggedTip", "Derive + register an IdentityTag for every item/attachment that has none (undoable)."))
				.OnClicked(this, &SNexusContentDashboard::OnAutoTagUntaggedClicked)
			]
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.VAlign(VAlign_Center)
			.Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock).Text(this, &SNexusContentDashboard::GetSummaryText)
			]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[
				SNew(STextBlock)
				.Text(this, &SNexusContentDashboard::GetCsvStatusText)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
		]

		// Findings.
		+ SVerticalBox::Slot().AutoHeight()[ SectionHeader(LOCTEXT("FindingsHeader", "Audit Findings")) ]
		+ SVerticalBox::Slot()
		.FillHeight(0.3f)
		[
			SAssignNew(FindingListView, SListView<TSharedPtr<FNexusAuditFinding>>)
			.ListItemsSource(&Audit.Findings)
			.OnGenerateRow(this, &SNexusContentDashboard::OnGenerateFindingRow)
			.OnMouseButtonDoubleClick(this, &SNexusContentDashboard::OnFindingActivated)
			.SelectionMode(ESelectionMode::Single)
		]

		// Items.
		+ SVerticalBox::Slot().AutoHeight()[ SectionHeader(LOCTEXT("ItemsHeader", "Items")) ]
		+ SVerticalBox::Slot()
		.FillHeight(0.35f)
		[
			SAssignNew(ItemListView, SListView<TSharedPtr<FNexusItemRow>>)
			.ListItemsSource(&Audit.Items)
			.OnGenerateRow(this, &SNexusContentDashboard::OnGenerateItemRow)
			.OnMouseButtonDoubleClick(this, &SNexusContentDashboard::OnItemActivated)
			.SelectionMode(ESelectionMode::Single)
			.HeaderRow(
				SNew(SHeaderRow)
				+ SHeaderRow::Column(ColName).DefaultLabel(LOCTEXT("ColName", "Name")).FillWidth(0.2f)
				+ SHeaderRow::Column(ColIdentity).DefaultLabel(LOCTEXT("ColIdentity", "Identity")).FillWidth(0.24f)
				+ SHeaderRow::Column(ColCategory).DefaultLabel(LOCTEXT("ColCategory", "Category")).FillWidth(0.18f)
				+ SHeaderRow::Column(ColGrid).DefaultLabel(LOCTEXT("ColGrid", "Grid")).FillWidth(0.08f)
				+ SHeaderRow::Column(ColValue).DefaultLabel(LOCTEXT("ColValue", "Value")).FillWidth(0.08f)
				+ SHeaderRow::Column(ColDamage).DefaultLabel(LOCTEXT("ColDamage", "Dmg")).FillWidth(0.07f)
				+ SHeaderRow::Column(ColRPM).DefaultLabel(LOCTEXT("ColRPM", "RPM")).FillWidth(0.07f)
				+ SHeaderRow::Column(ColMag).DefaultLabel(LOCTEXT("ColMag", "Mag")).FillWidth(0.08f))
		]

		// Attachments.
		+ SVerticalBox::Slot().AutoHeight()[ SectionHeader(LOCTEXT("AttachmentsHeader", "Attachments")) ]
		+ SVerticalBox::Slot()
		.FillHeight(0.35f)
		[
			SAssignNew(AttachmentListView, SListView<TSharedPtr<FNexusAttachmentRow>>)
			.ListItemsSource(&Audit.Attachments)
			.OnGenerateRow(this, &SNexusContentDashboard::OnGenerateAttachmentRow)
			.OnMouseButtonDoubleClick(this, &SNexusContentDashboard::OnAttachmentActivated)
			.SelectionMode(ESelectionMode::Single)
			.HeaderRow(
				SNew(SHeaderRow)
				+ SHeaderRow::Column(ColName).DefaultLabel(LOCTEXT("ColName", "Name")).FillWidth(0.16f)
				+ SHeaderRow::Column(ColIdentity).DefaultLabel(LOCTEXT("ColIdentity", "Identity")).FillWidth(0.18f)
				+ SHeaderRow::Column(ColProvided).DefaultLabel(LOCTEXT("ColProvided", "Provided")).FillWidth(0.16f)
				+ SHeaderRow::Column(ColRequired).DefaultLabel(LOCTEXT("ColRequired", "Required")).FillWidth(0.14f)
				+ SHeaderRow::Column(ColConflict).DefaultLabel(LOCTEXT("ColConflict", "Conflict")).FillWidth(0.12f)
				+ SHeaderRow::Column(ColMesh).DefaultLabel(LOCTEXT("ColMesh", "Mesh")).FillWidth(0.06f)
				+ SHeaderRow::Column(ColIssues).DefaultLabel(LOCTEXT("ColIssues", "Issues")).FillWidth(0.18f))
		]
	];
}

void SNexusContentDashboard::RebuildAudit()
{
	Audit = FNexusContentAudit::Run();

	if (FindingListView.IsValid())    { FindingListView->RequestListRefresh(); }
	if (ItemListView.IsValid())       { ItemListView->RequestListRefresh(); }
	if (AttachmentListView.IsValid()) { AttachmentListView->RequestListRefresh(); }
}

TSharedRef<ITableRow> SNexusContentDashboard::OnGenerateItemRow(
	TSharedPtr<FNexusItemRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(SNexusItemTableRow, Owner).Row(Row);
}

TSharedRef<ITableRow> SNexusContentDashboard::OnGenerateAttachmentRow(
	TSharedPtr<FNexusAttachmentRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(SNexusAttachmentTableRow, Owner).Row(Row);
}

TSharedRef<ITableRow> SNexusContentDashboard::OnGenerateFindingRow(
	TSharedPtr<FNexusAuditFinding> Finding, const TSharedRef<STableViewBase>& Owner)
{
	FSlateColor Color = FSlateColor::UseForeground();
	FString Prefix = TEXT("INFO");
	if (Finding->Severity == ENexusAuditSeverity::Error)   { Color = FStyleColors::Error;   Prefix = TEXT("ERROR"); }
	else if (Finding->Severity == ENexusAuditSeverity::Warning) { Color = FStyleColors::Warning; Prefix = TEXT("WARN"); }

	return SNew(STableRow<TSharedPtr<FNexusAuditFinding>>, Owner)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(6.0f, 2.0f)
		.VAlign(VAlign_Center)
		[
			SNew(SBox).WidthOverride(52.0f)
			[
				SNew(STextBlock).ColorAndOpacity(Color).Text(FText::FromString(Prefix))
			]
		]
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.Padding(6.0f, 2.0f)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock).AutoWrapText(true).Text(Finding->Message)
		]
	];
}

void SNexusContentDashboard::OnItemActivated(TSharedPtr<FNexusItemRow> Row)
{
	if (Row.IsValid()) { OpenAsset(Row->Item.Get()); }
}

void SNexusContentDashboard::OnAttachmentActivated(TSharedPtr<FNexusAttachmentRow> Row)
{
	if (Row.IsValid()) { OpenAsset(Row->Attachment.Get()); }
}

void SNexusContentDashboard::OnFindingActivated(TSharedPtr<FNexusAuditFinding> Finding)
{
	if (Finding.IsValid()) { OpenAsset(Finding->Asset.Get()); }
}

FReply SNexusContentDashboard::OnRefreshClicked()
{
	RebuildAudit();
	return FReply::Handled();
}

FText SNexusContentDashboard::GetSummaryText() const
{
	return FText::FromString(FString::Printf(
		TEXT("Items: %d    Attachments: %d    Errors: %d    Warnings: %d"),
		Audit.Items.Num(), Audit.Attachments.Num(), Audit.NumErrors, Audit.NumWarnings));
}

void SNexusContentDashboard::OpenAsset(UObject* Asset)
{
	if (Asset && GEditor)
	{
		if (UAssetEditorSubsystem* AssetEditor = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
		{
			AssetEditor->OpenEditorForAsset(Asset);
		}
	}
}

FReply SNexusContentDashboard::OnExportCsvClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		CsvStatusText = LOCTEXT("NoDesktop", "File dialog is unavailable.");
		return FReply::Handled();
	}

	const void* ParentHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
	TArray<FString> Files;
	const bool bPicked = DesktopPlatform->SaveFileDialog(ParentHandle,
		TEXT("Export Nexus roster CSV"), FPaths::ProjectSavedDir(), TEXT("NexusRoster.csv"),
		TEXT("CSV files (*.csv)|*.csv"), EFileDialogFlags::None, Files);
	if (!bPicked || Files.Num() == 0)
	{
		return FReply::Handled();
	}

	FString Error;
	const int32 Count = FNexusCsv::ExportItems(Files[0], Error);
	CsvStatusText = (Count >= 0)
		? FText::Format(LOCTEXT("Exported", "Exported {0} item(s)."), FText::AsNumber(Count))
		: FText::FromString(Error);
	return FReply::Handled();
}

FReply SNexusContentDashboard::OnImportCsvClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		CsvStatusText = LOCTEXT("NoDesktop2", "File dialog is unavailable.");
		return FReply::Handled();
	}

	const void* ParentHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
	TArray<FString> Files;
	const bool bPicked = DesktopPlatform->OpenFileDialog(ParentHandle,
		TEXT("Import Nexus roster CSV"), FPaths::ProjectSavedDir(), TEXT(""),
		TEXT("CSV files (*.csv)|*.csv"), EFileDialogFlags::None, Files);
	if (!bPicked || Files.Num() == 0)
	{
		return FReply::Handled();
	}

	// Dry run first, then confirm the scope before touching anything.
	FString Summary, Error;
	const int32 WouldChange = FNexusCsv::ImportItems(Files[0], /*bDryRun=*/ true, Summary, Error);
	if (WouldChange < 0)
	{
		CsvStatusText = FText::FromString(Error);
		return FReply::Handled();
	}
	if (WouldChange == 0)
	{
		CsvStatusText = LOCTEXT("NoChange", "No changes — the assets already match the CSV.");
		return FReply::Handled();
	}

	const EAppReturnType::Type Choice = FMessageDialog::Open(EAppMsgType::YesNo,
		FText::Format(LOCTEXT("ConfirmImport", "{0}\n\nApply these changes? (Undoable; Save the assets afterward.)"),
			FText::FromString(Summary)));
	if (Choice != EAppReturnType::Yes)
	{
		CsvStatusText = LOCTEXT("ImportCancelled", "Import cancelled.");
		return FReply::Handled();
	}

	FScopedTransaction Transaction(LOCTEXT("ImportTransaction", "Import Nexus roster CSV"));
	FString ApplySummary, ApplyError;
	const int32 Changed = FNexusCsv::ImportItems(Files[0], /*bDryRun=*/ false, ApplySummary, ApplyError);
	CsvStatusText = (Changed >= 0) ? FText::FromString(ApplySummary) : FText::FromString(ApplyError);
	RebuildAudit();
	return FReply::Handled();
}

FReply SNexusContentDashboard::OnAutoTagUntaggedClicked()
{
	FScopedTransaction Transaction(LOCTEXT("AutoTagTransaction", "Auto-tag untagged Nexus assets"));
	int32 Tagged = 0;
	FText Error;

	for (const TSharedPtr<FNexusItemRow>& Row : Audit.Items)
	{
		UNexusItemDefinition* Item = Row.IsValid() ? Row->Item.Get() : nullptr;
		if (Item && !Item->IdentityTag.IsValid())
		{
			Item->Modify();
			if (FNexusAssetCreation::DeriveAndAssignIdentityTag(Item, Error).IsValid()) { ++Tagged; }
		}
	}
	for (const TSharedPtr<FNexusAttachmentRow>& Row : Audit.Attachments)
	{
		UNexusAttachmentDefinition* Attachment = Row.IsValid() ? Row->Attachment.Get() : nullptr;
		if (Attachment && !Attachment->IdentityTag.IsValid())
		{
			Attachment->Modify();
			if (FNexusAssetCreation::DeriveAndAssignIdentityTag(Attachment, Error).IsValid()) { ++Tagged; }
		}
	}

	CsvStatusText = FText::Format(
		LOCTEXT("AutoTagged", "Auto-tagged {0} untagged asset(s) — Save them. (Undoable.)"), FText::AsNumber(Tagged));
	RebuildAudit();
	return FReply::Handled();
}

FText SNexusContentDashboard::GetCsvStatusText() const
{
	return CsvStatusText;
}

#undef LOCTEXT_NAMESPACE
