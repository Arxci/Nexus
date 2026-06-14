#include "Inspector/SNexusInspector.h"

#include "NexusEditorModule.h"
#include "Shared/NexusEditorSelection.h"
#include "Shared/NexusEditorWidgets.h"

#include "Audit/NexusContentAudit.h"

#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "AssetManagerEditorModule.h"
#include "Misc/DataValidation.h"
#include "Modules/ModuleManager.h"

#include "Editor.h"
#include "Framework/Docking/TabManager.h"

#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Text/STextBlock.h"

#include "AssetRegistry/AssetData.h"
#include "UObject/Package.h"

#define LOCTEXT_NAMESPACE "NexusInspector"

void SNexusInspector::Construct(const FArguments& InArgs)
{
	OnJumpToTool = InArgs._OnJumpToTool;

	// Embedded details panel — same configuration the Creator uses.
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsArgs;
	DetailsArgs.bAllowSearch = true;
	DetailsArgs.bHideSelectionTip = true;
	DetailsArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsView = PropertyModule.CreateDetailView(DetailsArgs);
	DetailsView->OnFinishedChangingProperties().AddSP(this, &SNexusInspector::OnInspectedPropertyChanged);

	ChildSlot
	[
		SNew(SVerticalBox)

		// Header.
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			NexusEditorWidgets::SectionHeader(LOCTEXT("InspectorTitle", "Inspector"))
		]

		// Live validation + "where used" banner. The whole row is a button: clicking it
		// opens the Reference Viewer for the inspected asset.
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SButton)
			.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
			.ContentPadding(FMargin(0))
			.Visibility(this, &SNexusInspector::GetBannerVisibility)
			.ToolTipText(this, &SNexusInspector::GetReferencesTooltip)
			.OnClicked(this, &SNexusInspector::OnBannerClicked)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
				.BorderBackgroundColor(this, &SNexusInspector::GetValidationColor)
				.Padding(FMargin(8.0f, 4.0f))
				[
					SNew(STextBlock)
					.Text(this, &SNexusInspector::GetValidationText)
				]
			]
		]

		// Cross-tool jump row — act on the current selection elsewhere.
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(4.0f, 2.0f))
		[
			SNew(SHorizontalBox)
			.Visibility(this, &SNexusInspector::GetJumpVisibility)
			+ SHorizontalBox::Slot().AutoWidth().Padding(2.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("OpenEconomy", "Economy"))
				.ToolTipText(LOCTEXT("OpenEconomyTip", "Show this item in the Economy balance sheet."))
				.OnClicked_Lambda([this]() { Jump(FNexusEditorModule::EconomyTabName); return FReply::Handled(); })
			]
			+ SHorizontalBox::Slot().AutoWidth().Padding(2.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("OpenAssembly", "Assembly"))
				.ToolTipText(LOCTEXT("OpenAssemblyTip", "Open the Assembly Preview (for weapons)."))
				.OnClicked_Lambda([this]() { Jump(FNexusEditorModule::PreviewTabName); return FReply::Handled(); })
			]
			+ SHorizontalBox::Slot().AutoWidth().Padding(2.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("OpenRefs", "References"))
				.ToolTipText(LOCTEXT("OpenRefsTip", "Open the Reference Viewer for this asset."))
				.OnClicked(this, &SNexusInspector::OnBannerClicked)
			]
			+ SHorizontalBox::Slot().AutoWidth().Padding(2.0f, 0.0f)
			[
				SNew(SButton)
				.Text(LOCTEXT("Browse", "Browse"))
				.ToolTipText(LOCTEXT("BrowseTip", "Reveal this asset in the Content Browser."))
				.OnClicked(this, &SNexusInspector::OnBrowseClicked)
			]
		]

		// Body: empty-state prompt until something is selected, then the details panel.
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SNew(SWidgetSwitcher)
			.WidgetIndex(this, &SNexusInspector::GetContentIndex)

			// 0 — nothing selected.
			+ SWidgetSwitcher::Slot()
			[
				SNew(SBox)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.Padding(24.0f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Empty", "Select an item in any tool to edit it here."))
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					.AutoWrapText(true)
					.Justification(ETextJustify::Center)
				]
			]

			// 1 — details panel.
			+ SWidgetSwitcher::Slot()
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(2.0f)
				[
					DetailsView.ToSharedRef()
				]
			]

			// 2 — this tool brings its own editor (e.g. the Creator).
			+ SWidgetSwitcher::Slot()
			[
				NexusEditorWidgets::EmptyState(
					LOCTEXT("OwnEditor", "This tool has its own editor — use the panel on the left."))
			]
		]
	];

	// Pick up whatever is already selected, and follow future changes.
	if (FNexusSelectionService* Service = FNexusEditorModule::TrySelection())
	{
		SelectionHandle = Service->Subscribe(
			FNexusOnSelectionChanged::FDelegate::CreateSP(this, &SNexusInspector::OnGlobalSelectionChanged));
		SetInspected(Service->GetSelection().Get());
	}
}

SNexusInspector::~SNexusInspector()
{
	if (FNexusSelectionService* Service = FNexusEditorModule::TrySelection())
	{
		Service->Unsubscribe(SelectionHandle);
	}
}

void SNexusInspector::SetInspected(UObject* Asset)
{
	Inspected = Asset;
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject(Asset);
	}
	RefreshValidation();
}

void SNexusInspector::SetSuppressed(bool bInSuppressed)
{
	bSuppressed = bInSuppressed;
}

void SNexusInspector::OnGlobalSelectionChanged(const FNexusSelection& Selection)
{
	const TArray<UObject*> Objects = Selection.Resolve();
	if (Objects.Num() > 1 && DetailsView.IsValid())
	{
		// Multi-object bulk edit: the Details panel edits the shared properties across all.
		DetailsView->SetObjects(Objects);
		Inspected = Objects[0];          // banner / jump act on the primary
		RefreshValidation();
	}
	else
	{
		SetInspected(Selection.Get());
	}
}

void SNexusInspector::OnInspectedPropertyChanged(const FPropertyChangedEvent& Event)
{
	// Other tools refresh themselves through their own FNexusAssetWatcher; we just need to
	// re-evaluate the validation / references banner for the asset we're showing.
	RefreshValidation();
}

void SNexusInspector::RefreshValidation()
{
	UObject* Object = Inspected.Get();
	if (!Object)
	{
		ValidationSummary = FText::GetEmpty();
		ReferencesTooltip = FText::GetEmpty();
		ValidationColor = FSlateColor::UseForeground();
		return;
	}

	FDataValidationContext Context;
	const UObject* ConstObject = Object;       // resolve to the const IsDataValid overload (UE 5.7)
	ConstObject->IsDataValid(Context);
	const int32 Errors = Context.GetNumErrors();
	const int32 Warnings = Context.GetNumWarnings();

	FString ValidationPart;
	if (Errors > 0)
	{
		ValidationColor = FStyleColors::Error;
		ValidationPart = FString::Printf(TEXT("%d error(s), %d warning(s)"), Errors, Warnings);
	}
	else if (Warnings > 0)
	{
		ValidationColor = FStyleColors::Warning;
		ValidationPart = FString::Printf(TEXT("%d warning(s)"), Warnings);
	}
	else
	{
		ValidationColor = FStyleColors::Success;
		ValidationPart = TEXT("Valid");
	}

	// Where-used: how many assets point at this one (recipes, manifests, slots, ...).
	const TArray<FAssetData> Referencers = FNexusContentAudit::GetReferencers(Object);
	ValidationSummary = FText::FromString(FString::Printf(
		TEXT("%s      Referenced by %d      (click to open Reference Viewer)"),
		*ValidationPart, Referencers.Num()));

	TArray<FString> Lines;
	if (Errors > 0 || Warnings > 0)
	{
		Lines.Add(TEXT("Right-click the asset in the Content Browser → 'Asset Actions' → 'Validate Assets' to see the issue details."));
		Lines.Add(FString());
	}
	if (Referencers.Num() > 0)
	{
		Lines.Add(TEXT("Referenced by:"));
		for (const FAssetData& Data : Referencers)
		{
			Lines.Add(TEXT("  ") + Data.AssetName.ToString());
		}
	}
	else
	{
		Lines.Add(TEXT("Nothing references this asset yet."));
	}
	ReferencesTooltip = FText::FromString(FString::Join(Lines, TEXT("\n")));
}

FReply SNexusInspector::OnBannerClicked()
{
	UObject* Asset = Inspected.Get();
	if (!Asset)
	{
		return FReply::Handled();
	}

	const UPackage* Package = Asset->GetPackage();
	if (!Package)
	{
		return FReply::Handled();
	}

	TArray<FAssetIdentifier> Identifiers;
	Identifiers.Add(FAssetIdentifier(Package->GetFName()));
	IAssetManagerEditorModule::Get().OpenReferenceViewerUI(Identifiers);
	return FReply::Handled();
}

void SNexusInspector::Jump(FName TabName)
{
	// Selection is already shared, so whichever view we land on shows this asset.
	if (OnJumpToTool.IsBound())
	{
		OnJumpToTool.Execute(TabName);
	}
	else
	{
		FGlobalTabmanager::Get()->TryInvokeTab(TabName);
	}
}

FReply SNexusInspector::OnBrowseClicked()
{
	UObject* Asset = Inspected.Get();
	if (Asset && GEditor)
	{
		GEditor->SyncBrowserToObjects(TArray<UObject*>{ Asset });
	}
	return FReply::Handled();
}

EVisibility SNexusInspector::GetJumpVisibility() const
{
	return (!bSuppressed && Inspected.IsValid()) ? EVisibility::Visible : EVisibility::Collapsed;
}

FText SNexusInspector::GetValidationText() const { return ValidationSummary; }
FSlateColor SNexusInspector::GetValidationColor() const { return ValidationColor; }
FText SNexusInspector::GetReferencesTooltip() const { return ReferencesTooltip; }

EVisibility SNexusInspector::GetBannerVisibility() const
{
	return (!bSuppressed && Inspected.IsValid()) ? EVisibility::Visible : EVisibility::Collapsed;
}

int32 SNexusInspector::GetContentIndex() const
{
	if (bSuppressed)
	{
		return 2;
	}
	return Inspected.IsValid() ? 1 : 0;
}

#undef LOCTEXT_NAMESPACE
