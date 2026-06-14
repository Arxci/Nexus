#include "Creation/SNexusCreatorWindow.h"

#include "NexusEditorModule.h"
#include "Creation/NexusAssetCreationLibrary.h"
#include "Preview/SNexusItemViewport.h"

#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "FileHelpers.h"
#include "ObjectTools.h"

#include "Audit/NexusContentAudit.h"
#include "Misc/DataValidation.h"

#include "ContentBrowserModule.h"
#include "AssetManagerEditorModule.h"
#include "IContentBrowserSingleton.h"

#include "Framework/Application/SlateApplication.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"

#include "AssetRegistry/AssetData.h"
#include "Misc/PackageName.h"
#include "UObject/Package.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Equipment/NexusEquipmentLoadout.h"
#include "Manifest/NexusManifestBuilder.h"

#include "Settings/NexusEditorSettings.h"

#define LOCTEXT_NAMESPACE "NexusCreatorWindow"

namespace
{
	/** A labelled section heading row. */
	TSharedRef<SWidget> SectionLabel(const FText& Text)
	{
		return SNew(STextBlock)
			.Text(Text)
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground());
	}
}

void SNexusCreatorWindow::Construct(const FArguments& InArgs)
{
	bRouteByType = UNexusEditorSettings::Get().bRouteIntoTypeFoldersByDefault;

	// --- Combo sources --------------------------------------------------------
	ItemTemplates =
	{
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::RangedWeapon),
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::MeleeWeapon),
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::Consumable),
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::Ammo),
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::Treasure),
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::KeyItem),
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::Charm),
		MakeShared<ENexusItemTemplate>(ENexusItemTemplate::Generic),
	};
	SelectedItemTemplate = ItemTemplates[0];

	const auto MakeType = [](const FText& Label, const FGameplayTag& InTag)
	{
		TSharedPtr<FAttachmentType> Type = MakeShared<FAttachmentType>();
		Type->Label = Label;
		Type->Tag = InTag;
		return Type;
	};
	AttachmentTypes =
	{
		MakeType(LOCTEXT("Sight", "Sight"), NexusGameplayTags::Attachment_Type_Sight),
		MakeType(LOCTEXT("Barrel", "Barrel"), NexusGameplayTags::Attachment_Type_Barrel),
		MakeType(LOCTEXT("Magazine", "Magazine"), NexusGameplayTags::Attachment_Type_Magazine),
		MakeType(LOCTEXT("Slide", "Slide"), NexusGameplayTags::Attachment_Type_Slide),
		MakeType(LOCTEXT("Trigger", "Trigger"), NexusGameplayTags::Attachment_Type_Trigger),
	};
	SelectedAttachmentType = AttachmentTypes[0];

	// --- Embedded details panel ----------------------------------------------
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsArgs;
	DetailsArgs.bAllowSearch = true;
	DetailsArgs.bHideSelectionTip = true;
	DetailsArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsView = PropertyModule.CreateDetailView(DetailsArgs);
	DetailsView->OnFinishedChangingProperties().AddSP(this, &SNexusCreatorWindow::OnInspectedPropertyChanged);

	StatusText = LOCTEXT("Ready", "Choose Item or Attachment, set a folder, then Create.");

	// A mode toggle button styled as a segment.
	const auto ModeButton = [this](ECreateMode ButtonMode, const FText& Label) -> TSharedRef<SWidget>
	{
		return SNew(SCheckBox)
			.Style(FAppStyle::Get(), "DetailsView.SectionButton")
			.Padding(FMargin(14.0f, 4.0f))
			.IsChecked_Lambda([this, ButtonMode]()
			{
				return Mode == ButtonMode ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
			})
			.OnCheckStateChanged_Lambda([this, ButtonMode](ECheckBoxState NewState)
			{
				if (NewState == ECheckBoxState::Checked) { SetMode(ButtonMode); }
			})
			[
				SNew(STextBlock).Text(Label).Justification(ETextJustify::Center)
			];
	};

	ChildSlot
	[
		SNew(SVerticalBox)

		// === Toolbar panel ====================================================
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
			.Padding(10.0f)
			[
				SNew(SVerticalBox)

				// Mode toggle + Save / Delete.
				+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 0.0f, 0.0f, 8.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[ SectionLabel(LOCTEXT("CreateColon", "CREATE")) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
					[ ModeButton(ECreateMode::Item, LOCTEXT("ModeItem", "Item")) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[ ModeButton(ECreateMode::Attachment, LOCTEXT("ModeAttachment", "Attachment")) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[ ModeButton(ECreateMode::Recipe, LOCTEXT("ModeRecipe", "Recipe")) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[ ModeButton(ECreateMode::Manifest, LOCTEXT("ModeManifest", "Manifest")) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[ ModeButton(ECreateMode::Loadout, LOCTEXT("ModeLoadout", "Loadout")) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[ ModeButton(ECreateMode::Suite, LOCTEXT("ModeSuite", "Weapon Suite")) ]

					+ SHorizontalBox::Slot().FillWidth(1.0f)[ SNullWidget::NullWidget ]

					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("Duplicate", "Duplicate"))
						.ToolTipText(LOCTEXT("DuplicateTip", "Clone the selected asset as a variant."))
						.OnClicked(this, &SNexusCreatorWindow::OnDuplicateClicked)
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("LoadSel", "Load Selected"))
						.ToolTipText(LOCTEXT("LoadSelTip", "Add the items/attachments selected in the Content Browser so you can edit them here."))
						.OnClicked(this, &SNexusCreatorWindow::OnLoadFromContentBrowserClicked)
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("AutoTag", "Auto-tag"))
						.ToolTipText(LOCTEXT("AutoTagTip", "Derive a unique IdentityTag from the selected asset's name and register it."))
						.OnClicked(this, &SNexusCreatorWindow::OnAutoTagClicked)
					]

					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f)
					[
						SNew(SButton)
						.Text(LOCTEXT("Delete", "Delete"))
						.ToolTipText(LOCTEXT("DeleteTip", "Discard the asset selected in the list below."))
						.OnClicked(this, &SNexusCreatorWindow::OnDeleteSelectedClicked)
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
					[
						SNew(SButton)
						.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
						.Text(LOCTEXT("SaveAll", "Save All"))
						.ToolTipText(LOCTEXT("SaveAllTip", "Write every asset created this session to disk in its folder. Until then they exist only in memory."))
						.OnClicked(this, &SNexusCreatorWindow::OnSaveAllClicked)
					]
				]

				// Folder + name.
				+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 0.0f, 0.0f, 8.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[ SectionLabel(LOCTEXT("FolderColon", "FOLDER")) ]
					+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(8.0f, 0.0f)
					[ SAssignNew(FolderBox, SEditableTextBox).Text(FText::FromString(UNexusEditorSettings::Get().AuthoringRootFolder)) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[
						SAssignNew(FolderPickerButton, SComboButton)
						.OnGetMenuContent(this, &SNexusCreatorWindow::MakeFolderPickerMenu)
						.ButtonContent()[ SNew(STextBlock).Text(LOCTEXT("Browse", "Browse")) ]
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(16.0f, 0.0f, 0.0f, 0.0f)
					[ SectionLabel(LOCTEXT("NameColon", "NAME")) ]
					+ SHorizontalBox::Slot().FillWidth(0.5f).VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
					[ SAssignNew(NameBox, SEditableTextBox).HintText(LOCTEXT("NameHint", "auto")) ]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(16.0f, 0.0f, 0.0f, 0.0f)
					[
						SNew(SCheckBox)
						.IsChecked(this, &SNexusCreatorWindow::GetRouteByTypeState)
						.OnCheckStateChanged(this, &SNexusCreatorWindow::OnRouteByTypeChanged)
						.ToolTipText(LOCTEXT("RouteTip", "Save into a per-type subfolder (Weapons, Attachments, ...) under the folder above."))
						[ SNew(STextBlock).Text(LOCTEXT("RouteByType", "Sort into type folders")).Margin(FMargin(4.0f, 0.0f, 0.0f, 0.0f)) ]
					]
				]

				// Mode-specific creation row.
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(SWidgetSwitcher)
					.WidgetIndex(this, &SNexusCreatorWindow::GetModePanelIndex)

					// Index 0 — Item.
					+ SWidgetSwitcher::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
						[ SectionLabel(LOCTEXT("TemplateColon", "TEMPLATE")) ]
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
						[
							SNew(SComboBox<TSharedPtr<ENexusItemTemplate>>)
							.OptionsSource(&ItemTemplates)
							.OnGenerateWidget(this, &SNexusCreatorWindow::OnGenerateItemTemplateRow)
							.OnSelectionChanged(this, &SNexusCreatorWindow::OnItemTemplateChanged)
							.InitiallySelectedItem(SelectedItemTemplate)
							[ SNew(STextBlock).Text(this, &SNexusCreatorWindow::GetItemTemplateText) ]
						]
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
						[
							SNew(SButton)
							.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
							.Text(LOCTEXT("CreateItemBtn", "Create Item"))
							.OnClicked(this, &SNexusCreatorWindow::OnCreateClicked)
						]
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(SComboButton)
							.OnGetMenuContent(this, &SNexusCreatorWindow::MakePresetsMenu)
							.ToolTipText(LOCTEXT("PresetsTip", "Stamp a preconfigured item from a named preset (Project Settings → Nexus Authoring Tools → Presets)."))
							.ButtonContent()
							[ SNew(STextBlock).Text(LOCTEXT("Presets", "Presets ▾")) ]
						]
					]

					// Index 1 — Attachment.
					+ SWidgetSwitcher::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
							[ SectionLabel(LOCTEXT("TypeColon", "TYPE")) ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
							[
								SNew(SComboBox<TSharedPtr<FAttachmentType>>)
								.OptionsSource(&AttachmentTypes)
								.OnGenerateWidget(this, &SNexusCreatorWindow::OnGenerateAttachmentTypeRow)
								.OnSelectionChanged(this, &SNexusCreatorWindow::OnAttachmentTypeChanged)
								.InitiallySelectedItem(SelectedAttachmentType)
								[ SNew(STextBlock).Text(this, &SNexusCreatorWindow::GetAttachmentTypeText) ]
							]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
							[
								SNew(SButton)
								.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
								.Text(LOCTEXT("CreateAttachmentBtn", "Create Attachment"))
								.OnClicked(this, &SNexusCreatorWindow::OnCreateClicked)
							]
						]
						+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 4.0f, 0.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(this, &SNexusCreatorWindow::GetActiveHostText)
							.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						]
					]

					// Index 2 — Recipe.
					+ SWidgetSwitcher::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
						[ SectionLabel(LOCTEXT("RecipeColon", "RECIPE")) ]
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
						[
							SNew(SButton)
							.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
							.Text(LOCTEXT("CreateRecipeBtn", "Create Recipe"))
							.OnClicked_Lambda([this]() { CreateRecipeAsset(); return FReply::Handled(); })
						]
						+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("RecipeHint", "Then set its inputs / output on the right."))
							.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						]
					]

					// Index 3 — Manifest.
					+ SWidgetSwitcher::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
						[ SectionLabel(LOCTEXT("ManifestColon", "MANIFEST")) ]
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
						[
							SNew(SButton)
							.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
							.Text(LOCTEXT("BuildManifestBtn", "Build from Current Level"))
							.ToolTipText(LOCTEXT("BuildManifestTip", "Scan the open level for items/attachments and fill a manifest, then review it here."))
							.OnClicked_Lambda([this]() { BuildManifestFromLevel(); return FReply::Handled(); })
						]
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(4.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(SButton)
							.Text(LOCTEXT("BlankManifestBtn", "Create Blank"))
							.OnClicked_Lambda([this]() { CreateBlankManifest(); return FReply::Handled(); })
						]
					]

					// Index 4 — Loadout.
					+ SWidgetSwitcher::Slot()
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
						[ SectionLabel(LOCTEXT("LoadoutColon", "LOADOUT")) ]
						+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
						[
							SNew(SButton)
							.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
							.Text(LOCTEXT("CreateLoadoutBtn", "Create Loadout"))
							.OnClicked_Lambda([this]() { CreateLoadoutAsset(); return FReply::Handled(); })
						]
						+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
						[
							SNew(STextBlock)
							.Text(LOCTEXT("LoadoutHint", "Then add the character's equipment slots on the right."))
							.ColorAndOpacity(FSlateColor::UseSubduedForeground())
						]
					]

					// Index 5 — Weapon Suite wizard.
					+ SWidgetSwitcher::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight()
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
							[ SectionLabel(LOCTEXT("SuiteColon", "WEAPON SUITE")) ]
							// Ranged / Melee toggle.
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
							[
								SNew(SCheckBox)
								.Style(FAppStyle::Get(), "DetailsView.SectionButton")
								.Padding(FMargin(10.0f, 2.0f))
								.IsChecked_Lambda([this]() { return bSuiteRanged ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
								.OnCheckStateChanged_Lambda([this](ECheckBoxState S) { if (S == ECheckBoxState::Checked) { bSuiteRanged = true; } })
								[ SNew(STextBlock).Text(LOCTEXT("SuiteRanged", "Ranged")) ]
							]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
							[
								SNew(SCheckBox)
								.Style(FAppStyle::Get(), "DetailsView.SectionButton")
								.Padding(FMargin(10.0f, 2.0f))
								.IsChecked_Lambda([this]() { return !bSuiteRanged ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
								.OnCheckStateChanged_Lambda([this](ECheckBoxState S) { if (S == ECheckBoxState::Checked) { bSuiteRanged = false; } })
								[ SNew(STextBlock).Text(LOCTEXT("SuiteMelee", "Melee")) ]
							]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
							[
								SNew(SButton)
								.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
								.Text(LOCTEXT("CreateSuiteBtn", "Create All"))
								.ToolTipText(LOCTEXT("CreateSuiteTip", "Stamp the weapon, create + auto-slot the checked attachments, and optionally ammo + a recipe — all loaded here for editing."))
								.OnClicked_Lambda([this]() { CreateWeaponSuite(); return FReply::Handled(); })
							]
						]
						// Attachment + extras checkboxes.
						+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 6.0f, 0.0f, 0.0f)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
							[ SectionLabel(LOCTEXT("SuiteInclude", "INCLUDE")) ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
							[ SNew(SCheckBox).IsChecked_Lambda([this]() { return bSuiteSight ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }).OnCheckStateChanged_Lambda([this](ECheckBoxState S) { bSuiteSight = (S == ECheckBoxState::Checked); })[ SNew(STextBlock).Text(LOCTEXT("OptSight", "Sight")).Margin(FMargin(4, 0, 0, 0)) ] ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
							[ SNew(SCheckBox).IsChecked_Lambda([this]() { return bSuiteBarrel ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }).OnCheckStateChanged_Lambda([this](ECheckBoxState S) { bSuiteBarrel = (S == ECheckBoxState::Checked); })[ SNew(STextBlock).Text(LOCTEXT("OptBarrel", "Barrel")).Margin(FMargin(4, 0, 0, 0)) ] ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
							[ SNew(SCheckBox).IsChecked_Lambda([this]() { return bSuiteMagazine ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }).OnCheckStateChanged_Lambda([this](ECheckBoxState S) { bSuiteMagazine = (S == ECheckBoxState::Checked); })[ SNew(STextBlock).Text(LOCTEXT("OptMag", "Magazine")).Margin(FMargin(4, 0, 0, 0)) ] ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
							[ SNew(SCheckBox).IsChecked_Lambda([this]() { return bSuiteSlide ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }).OnCheckStateChanged_Lambda([this](ECheckBoxState S) { bSuiteSlide = (S == ECheckBoxState::Checked); })[ SNew(STextBlock).Text(LOCTEXT("OptSlide", "Slide")).Margin(FMargin(4, 0, 0, 0)) ] ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
							[ SNew(SCheckBox).IsChecked_Lambda([this]() { return bSuiteTrigger ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }).OnCheckStateChanged_Lambda([this](ECheckBoxState S) { bSuiteTrigger = (S == ECheckBoxState::Checked); })[ SNew(STextBlock).Text(LOCTEXT("OptTrigger", "Trigger")).Margin(FMargin(4, 0, 0, 0)) ] ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(16.0f, 0.0f, 0.0f, 0.0f)
							[ SNew(SCheckBox).IsChecked_Lambda([this]() { return bSuiteAmmo ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }).OnCheckStateChanged_Lambda([this](ECheckBoxState S) { bSuiteAmmo = (S == ECheckBoxState::Checked); })[ SNew(STextBlock).Text(LOCTEXT("OptAmmo", "Ammo")).Margin(FMargin(4, 0, 0, 0)) ] ]
							+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f)
							[ SNew(SCheckBox).IsChecked_Lambda([this]() { return bSuiteRecipe ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; }).OnCheckStateChanged_Lambda([this](ECheckBoxState S) { bSuiteRecipe = (S == ECheckBoxState::Checked); })[ SNew(STextBlock).Text(LOCTEXT("OptRecipe", "Recipe")).Margin(FMargin(4, 0, 0, 0)) ] ]
						]
					]
				]
			]
		]

		// Status line.
		+ SVerticalBox::Slot().AutoHeight().Padding(10.0f, 6.0f)
		[ SNew(STextBlock).Text(this, &SNexusCreatorWindow::GetStatusText).AutoWrapText(true) ]

		// === Body: working set | details =====================================
		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f, 0.0f, 8.0f, 8.0f)
		[
			SNew(SSplitter)
			+ SSplitter::Slot().Value(0.3f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(4.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
					[ SectionLabel(LOCTEXT("CreatedHeader", "CREATED THIS SESSION")) ]
					+ SVerticalBox::Slot().FillHeight(1.0f)
					[
						SAssignNew(EntryListView, SListView<TSharedPtr<FCreatedEntry>>)
						.ListItemsSource(&Entries)
						.OnGenerateRow(this, &SNexusCreatorWindow::OnGenerateEntryRow)
						.OnSelectionChanged(this, &SNexusCreatorWindow::OnEntrySelectionChanged)
						.SelectionMode(ESelectionMode::Single)
					]
				]
			]
			+ SSplitter::Slot().Value(0.7f)
			[
				SNew(SVerticalBox)

				// Live validation + "where used" banner. The whole row is a
				// button: clicking it opens the Reference Viewer for the
				// inspected asset, so the count has somewhere to take you.
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(SButton)
					.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("HoverHintOnly"))
					.ContentPadding(FMargin(0))
					.Visibility(this, &SNexusCreatorWindow::GetBannerVisibility)
					.ToolTipText(this, &SNexusCreatorWindow::GetReferencesTooltip)
					.OnClicked(this, &SNexusCreatorWindow::OnBannerClicked)
					[
						SNew(SBorder)
						.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
						.BorderBackgroundColor(this, &SNexusCreatorWindow::GetValidationColor)
						.Padding(FMargin(8.0f, 4.0f))
						[
							SNew(STextBlock)
							.Text(this, &SNexusCreatorWindow::GetValidationText)
						]
					]
				]

				+ SVerticalBox::Slot().FillHeight(1.0f)
				[
					SNew(SSplitter)
					+ SSplitter::Slot().Value(0.6f)
					[
						SNew(SBorder)
						.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
						.Padding(2.0f)
						[ DetailsView.ToSharedRef() ]
					]
					+ SSplitter::Slot().Value(0.4f)
					[
						SNew(SBorder)
						.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
						.Padding(2.0f)
						[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
							[ SectionLabel(LOCTEXT("PreviewHeader", "PREVIEW")) ]
							+ SVerticalBox::Slot().FillHeight(1.0f)
							[ SAssignNew(PreviewViewport, SNexusItemViewport) ]
						]
					]
				]
			]
		]
	];
}

FReply SNexusCreatorWindow::OnCreateClicked()
{
	if (Mode == ECreateMode::Item)
	{
		CreateItem(SelectedItemTemplate.IsValid() ? *SelectedItemTemplate : ENexusItemTemplate::Generic);
	}
	else if (SelectedAttachmentType.IsValid())
	{
		CreateAttachment(SelectedAttachmentType->Tag, SelectedAttachmentType->Label);
	}
	return FReply::Handled();
}

void SNexusCreatorWindow::CreateItem(ENexusItemTemplate Template)
{
	FText Error;
	UNexusItemDefinition* Asset = FNexusAssetCreation::CreateItem(
		Template, CreateFolderFor(FNexusAssetCreation::SubfolderForTemplate(Template)), CurrentName(), Error);
	if (!Asset)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("ItemFail", "Could not create the item.") : Error;
		return;
	}

	ActiveSlotHost = Asset;
	AddEntry(Asset, FString::Printf(TEXT("%s  (%s)"),
		*Asset->GetName(), *FNexusAssetCreation::TemplateLabel(Template).ToString()));
	StatusText = FText::Format(
		LOCTEXT("ItemMade", "Created '{0}' (unsaved — edit it on the right, then Save All)."),
		FText::FromString(Asset->GetName()));
}

void SNexusCreatorWindow::CreateAttachment(const FGameplayTag& TypeTag, const FText& TypeLabel)
{
	FText Error;
	UNexusAttachmentDefinition* Asset = FNexusAssetCreation::CreateAttachment(
		TypeTag, CreateFolderFor(TEXT("Attachments")), CurrentName(), Error);
	if (!Asset)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("AttFail", "Could not create the attachment.") : Error;
		return;
	}

	UNexusItemDefinition* Host = ActiveSlotHost.Get();
	FString SlotName;
	const ENexusAttachResult Result = Host
		? FNexusAssetCreation::AssignOrCreateSlot(Host, Asset, TypeTag, SlotName)
		: ENexusAttachResult::NoEquippable;

	AddEntry(Asset, FString::Printf(TEXT("%s  (%s attachment)"), *Asset->GetName(), *TypeLabel.ToString()));

	const FText AssetName = FText::FromString(Asset->GetName());
	const FText HostName = Host ? FText::FromString(Host->GetName()) : FText::GetEmpty();

	switch (Result)
	{
	case ENexusAttachResult::Assigned:
		StatusText = FText::Format(LOCTEXT("AttAssigned",
			"Created '{0}' and set it as {1}'s {2} attachment — configure it on the right."),
			AssetName, HostName, FText::FromString(SlotName));
		break;
	case ENexusAttachResult::CreatedSlot:
		StatusText = FText::Format(LOCTEXT("AttCreatedSlot",
			"Created '{0}', added a {2} slot to {1}, and filled it — configure it on the right."),
			AssetName, HostName, FText::FromString(SlotName));
		break;
	case ENexusAttachResult::AllFilled:
		StatusText = FText::Format(LOCTEXT("AttAllFilled",
			"Created '{0}', but {1}'s {2} slot(s) are already filled — free one or assign manually."),
			AssetName, HostName, TypeLabel);
		break;
	case ENexusAttachResult::NoEquippable:
	default:
		StatusText = Host
			? FText::Format(LOCTEXT("AttNoEquippable",
				"Created '{0}'. {1} has no Equippable fragment to attach to — add one, or keep it standalone."),
				AssetName, HostName)
			: FText::Format(LOCTEXT("AttNoHost",
				"Created '{0}'. Create or select an item first and it'll auto-attach."), AssetName);
		break;
	}
}

TSharedRef<SWidget> SNexusCreatorWindow::OnGenerateItemTemplateRow(TSharedPtr<ENexusItemTemplate> InItem)
{
	return SNew(STextBlock).Text(InItem.IsValid() ? FNexusAssetCreation::TemplateLabel(*InItem) : FText::GetEmpty());
}

void SNexusCreatorWindow::OnItemTemplateChanged(TSharedPtr<ENexusItemTemplate> NewItem, ESelectInfo::Type SelectInfo)
{
	if (NewItem.IsValid()) { SelectedItemTemplate = NewItem; }
}

FText SNexusCreatorWindow::GetItemTemplateText() const
{
	return SelectedItemTemplate.IsValid() ? FNexusAssetCreation::TemplateLabel(*SelectedItemTemplate) : FText::GetEmpty();
}

TSharedRef<SWidget> SNexusCreatorWindow::OnGenerateAttachmentTypeRow(TSharedPtr<FAttachmentType> InItem)
{
	return SNew(STextBlock).Text(InItem.IsValid() ? InItem->Label : FText::GetEmpty());
}

void SNexusCreatorWindow::OnAttachmentTypeChanged(TSharedPtr<FAttachmentType> NewItem, ESelectInfo::Type SelectInfo)
{
	if (NewItem.IsValid()) { SelectedAttachmentType = NewItem; }
}

FText SNexusCreatorWindow::GetAttachmentTypeText() const
{
	return SelectedAttachmentType.IsValid() ? SelectedAttachmentType->Label : FText::GetEmpty();
}

bool SNexusCreatorWindow::AddEntry(UObject* Asset, const FString& Label)
{
	if (!Asset)
	{
		return false;
	}

	// Dedupe: if this asset is already in the working set, just select that
	// entry instead of adding a duplicate row.
	for (const TSharedPtr<FCreatedEntry>& Existing : Entries)
	{
		if (Existing.IsValid() && Existing->Asset.Get() == Asset)
		{
			SelectEntry(Existing);
			return false;
		}
	}

	TSharedPtr<FCreatedEntry> Entry = MakeShared<FCreatedEntry>();
	Entry->Asset = Asset;
	Entry->Label = Label;
	Entries.Add(Entry);

	if (EntryListView.IsValid())
	{
		EntryListView->RequestListRefresh();
	}
	SelectEntry(Entry);
	return true;
}

void SNexusCreatorWindow::SelectEntry(TSharedPtr<FCreatedEntry> Entry)
{
	if (!Entry.IsValid())
	{
		return;
	}
	if (EntryListView.IsValid())
	{
		EntryListView->SetSelection(Entry);
	}
	Inspect(Entry->Asset.Get());
}

TSharedRef<ITableRow> SNexusCreatorWindow::OnGenerateEntryRow(
	TSharedPtr<FCreatedEntry> Entry, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(STableRow<TSharedPtr<FCreatedEntry>>, Owner)
	[
		SNew(SBox).Padding(FMargin(6.0f, 3.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromString(Entry.IsValid() ? Entry->Label : FString()))
			.OverflowPolicy(ETextOverflowPolicy::Ellipsis)
		]
	];
}

void SNexusCreatorWindow::OnEntrySelectionChanged(TSharedPtr<FCreatedEntry> Entry, ESelectInfo::Type SelectInfo)
{
	UObject* Object = Entry.IsValid() ? Entry->Asset.Get() : nullptr;
	Inspect(Object);

	// Keep the shared selection in step so a torn-off Creator still drives the Workbench Inspector.
	FNexusEditorModule::SetSelection(Object, FNexusEditorModule::CreatorTabName);

	// Clicking an item makes it the host new attachments attach to; selecting an attachment
	// leaves the last item as the host so you can keep adding parts to it.
	if (UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(Object))
	{
		ActiveSlotHost = Item;
	}
}

FReply SNexusCreatorWindow::OnSaveAllClicked()
{
	TArray<UPackage*> Packages;
	for (const TSharedPtr<FCreatedEntry>& Entry : Entries)
	{
		if (Entry.IsValid() && Entry->Asset.IsValid())
		{
			Packages.AddUnique(Entry->Asset->GetPackage());
		}
	}

	if (Packages.Num() == 0)
	{
		StatusText = LOCTEXT("NothingToSave", "Nothing to save yet.");
		return FReply::Handled();
	}

	const FEditorFileUtils::EPromptReturnCode Result =
		FEditorFileUtils::PromptForCheckoutAndSave(Packages, /*bCheckDirty=*/ false, /*bPromptToSave=*/ false);
	StatusText = (Result == FEditorFileUtils::PR_Success)
		? FText::Format(LOCTEXT("Saved", "Saved {0} asset(s) to disk."), FText::AsNumber(Packages.Num()))
		: LOCTEXT("SaveCancelled", "Save cancelled or failed.");
	return FReply::Handled();
}

FReply SNexusCreatorWindow::OnDeleteSelectedClicked()
{
	const TArray<TSharedPtr<FCreatedEntry>> Selected =
		EntryListView.IsValid() ? EntryListView->GetSelectedItems() : TArray<TSharedPtr<FCreatedEntry>>();
	if (Selected.Num() == 0)
	{
		StatusText = LOCTEXT("DeleteNone", "Select an asset in the list below, then Delete.");
		return FReply::Handled();
	}

	TSharedPtr<FCreatedEntry> Entry = Selected[0];
	UObject* Asset = Entry.IsValid() ? Entry->Asset.Get() : nullptr;
	const FString Name = Asset ? Asset->GetName() : TEXT("(asset)");

	Inspect(nullptr);
	Entries.Remove(Entry);
	if (Asset && ActiveSlotHost.Get() == Asset)
	{
		ActiveSlotHost = nullptr;
	}
	if (Asset)
	{
		ObjectTools::DeleteObjects({ Asset }, /*bShowConfirmation=*/ false);
	}
	if (EntryListView.IsValid())
	{
		EntryListView->RequestListRefresh();
	}

	StatusText = FText::Format(LOCTEXT("Deleted", "Deleted '{0}'."), FText::FromString(Name));
	return FReply::Handled();
}

TSharedRef<SWidget> SNexusCreatorWindow::MakeFolderPickerMenu()
{
	FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	FPathPickerConfig PathConfig;
	PathConfig.DefaultPath = CurrentFolder();
	PathConfig.bAllowContextMenu = false;
	PathConfig.bAddDefaultPath = true;
	PathConfig.OnPathSelected = FOnPathSelected::CreateSP(this, &SNexusCreatorWindow::OnFolderPicked);

	return SNew(SBox)
		.WidthOverride(320.0f)
		.HeightOverride(450.0f)
		[ ContentBrowser.Get().CreatePathPicker(PathConfig) ];
}

void SNexusCreatorWindow::OnFolderPicked(const FString& Path)
{
	if (FolderBox.IsValid())
	{
		FolderBox->SetText(FText::FromString(Path));
	}
	if (FolderPickerButton.IsValid())
	{
		FolderPickerButton->SetIsOpen(false);
	}
}

FText SNexusCreatorWindow::GetStatusText() const
{
	return StatusText;
}

FText SNexusCreatorWindow::GetActiveHostText() const
{
	const UNexusItemDefinition* Host = ActiveSlotHost.Get();
	return Host
		? FText::Format(LOCTEXT("AttachTo", "Attaches to:  {0}"), FText::FromString(Host->GetName()))
		: LOCTEXT("AttachToNone", "Attaches to:  (create or select an item first)");
}

FString SNexusCreatorWindow::CurrentFolder() const
{
	return FolderBox.IsValid() ? FolderBox->GetText().ToString() : UNexusEditorSettings::Get().AuthoringRootFolder;
}

FString SNexusCreatorWindow::CurrentName() const
{
	return NameBox.IsValid() ? NameBox->GetText().ToString() : FString();
}

void SNexusCreatorWindow::CreateRecipeAsset()
{
	FText Error;
	UNexusCombinationRecipe* Asset =
		FNexusAssetCreation::CreateRecipe(CreateFolderFor(TEXT("Recipes")), CurrentName(), nullptr, Error);
	if (!Asset)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("RecipeFail", "Could not create the recipe.") : Error;
		return;
	}
	AddEntry(Asset, FString::Printf(TEXT("%s  (recipe)"), *Asset->GetName()));
	StatusText = FText::Format(
		LOCTEXT("RecipeMade", "Created recipe '{0}' — set its inputs / output on the right, then Save All."),
		FText::FromString(Asset->GetName()));
}

void SNexusCreatorWindow::CreateBlankManifest()
{
	FText Error;
	UNexusLevelManifest* Asset =
		FNexusAssetCreation::CreateManifest(CreateFolderFor(TEXT("Manifests")), CurrentName(), Error);
	if (!Asset)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("ManifestFail", "Could not create the manifest.") : Error;
		return;
	}
	AddEntry(Asset, FString::Printf(TEXT("%s  (manifest)"), *Asset->GetName()));
	StatusText = FText::Format(LOCTEXT("ManifestMade", "Created blank manifest '{0}'."), FText::FromString(Asset->GetName()));
}

void SNexusCreatorWindow::BuildManifestFromLevel()
{
	FString Message;
	UNexusLevelManifest* Manifest = FNexusManifestBuilder::BuildFromCurrentLevel(Message);
	if (Manifest)
	{
		AddEntry(Manifest, FString::Printf(TEXT("%s  (manifest)"), *Manifest->GetName()));
	}
	StatusText = FText::FromString(Message);
}

void SNexusCreatorWindow::CreateLoadoutAsset()
{
	FText Error;
	UNexusEquipmentLoadout* Asset =
		FNexusAssetCreation::CreateLoadout(CreateFolderFor(TEXT("Loadouts")), CurrentName(), Error);
	if (!Asset)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("LoadoutFail", "Could not create the loadout.") : Error;
		return;
	}
	AddEntry(Asset, FString::Printf(TEXT("%s  (loadout)"), *Asset->GetName()));
	StatusText = FText::Format(
		LOCTEXT("LoadoutMade", "Created loadout '{0}' — add slots on the right, then Save All."),
		FText::FromString(Asset->GetName()));
}

void SNexusCreatorWindow::LoadAsset(UObject* Asset)
{
	if (!Asset)
	{
		return;
	}
	const bool bAdded = AddEntry(Asset, FString::Printf(TEXT("%s  (%s)"), *Asset->GetName(), *Asset->GetClass()->GetName()));
	StatusText = bAdded
		? FText::Format(LOCTEXT("LoadedOne", "Loaded '{0}' for editing."), FText::FromString(Asset->GetName()))
		: FText::Format(LOCTEXT("AlreadyLoaded", "'{0}' is already loaded — selecting it."), FText::FromString(Asset->GetName()));
}

FString SNexusCreatorWindow::CreateFolderFor(const FString& Subfolder) const
{
	const FString Base = CurrentFolder();
	return (bRouteByType && !Subfolder.IsEmpty()) ? (Base / Subfolder) : Base;
}

ECheckBoxState SNexusCreatorWindow::GetRouteByTypeState() const
{
	return bRouteByType ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SNexusCreatorWindow::OnRouteByTypeChanged(ECheckBoxState NewState)
{
	bRouteByType = (NewState == ECheckBoxState::Checked);
}

FReply SNexusCreatorWindow::OnDuplicateClicked()
{
	const TArray<TSharedPtr<FCreatedEntry>> Selected =
		EntryListView.IsValid() ? EntryListView->GetSelectedItems() : TArray<TSharedPtr<FCreatedEntry>>();
	UObject* Source = (Selected.Num() > 0 && Selected[0].IsValid()) ? Selected[0]->Asset.Get() : nullptr;
	if (!Source)
	{
		StatusText = LOCTEXT("DupNone", "Select an asset in the list to duplicate.");
		return FReply::Handled();
	}

	const FString Folder = FPackageName::GetLongPackagePath(Source->GetPackage()->GetName());
	FText Error;
	UObject* Copy = FNexusAssetCreation::DuplicateAsset(Source, Folder, Error);
	if (!Copy)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("DupFail2", "Duplication failed.") : Error;
		return FReply::Handled();
	}

	if (UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(Copy)) { ActiveSlotHost = Item; }
	AddEntry(Copy, FString::Printf(TEXT("%s  (copy)"), *Copy->GetName()));
	StatusText = FText::Format(LOCTEXT("Duped", "Duplicated to '{0}'."), FText::FromString(Copy->GetName()));
	return FReply::Handled();
}

FReply SNexusCreatorWindow::OnLoadFromContentBrowserClicked()
{
	FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	TArray<FAssetData> Selected;
	ContentBrowser.Get().GetSelectedAssets(Selected);

	int32 Added = 0;
	for (const FAssetData& Data : Selected)
	{
		UObject* Object = Data.GetAsset();
		if (!Object)
		{
			continue;
		}

		const bool bItem = Object->IsA<UNexusItemDefinition>();
		const bool bAttachment = Object->IsA<UNexusAttachmentDefinition>();
		if (!bItem && !bAttachment)
		{
			continue;
		}

		if (AddEntry(Object, FString::Printf(TEXT("%s  (%s)"), *Object->GetName(), bItem ? TEXT("item") : TEXT("attachment"))))
		{
			++Added;
		}
	}

	StatusText = (Added > 0)
		? FText::Format(LOCTEXT("Loaded", "Loaded {0} asset(s) from the Content Browser for editing."), FText::AsNumber(Added))
		: LOCTEXT("LoadedNone", "Select Nexus item/attachment assets in the Content Browser, then Load Selected (already-loaded assets are re-selected, not duplicated).");
	return FReply::Handled();
}

FReply SNexusCreatorWindow::OnAutoTagClicked()
{
	const TArray<TSharedPtr<FCreatedEntry>> Selected =
		EntryListView.IsValid() ? EntryListView->GetSelectedItems() : TArray<TSharedPtr<FCreatedEntry>>();
	UObject* Asset = (Selected.Num() > 0 && Selected[0].IsValid()) ? Selected[0]->Asset.Get() : nullptr;
	if (!Asset)
	{
		StatusText = LOCTEXT("TagNone", "Select an asset in the list to auto-tag.");
		return FReply::Handled();
	}

	FText Error;
	const FGameplayTag NewTag = FNexusAssetCreation::DeriveAndAssignIdentityTag(Asset, Error);
	if (!NewTag.IsValid())
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("TagFail", "Could not derive a tag.") : Error;
		return FReply::Handled();
	}

	if (DetailsView.IsValid())
	{
		DetailsView->ForceRefresh();
	}
	RefreshValidation();
	StatusText = FText::Format(LOCTEXT("Tagged", "Set identity tag to {0}."), FText::FromString(NewTag.ToString()));
	return FReply::Handled();
}

TSharedRef<SWidget> SNexusCreatorWindow::MakePresetsMenu()
{
	FMenuBuilder MenuBuilder(/*bShouldCloseWindowAfterMenuSelection=*/ true, nullptr);

	const TArray<FNexusCreatorPreset>& Presets = UNexusEditorSettings::Get().CreatorPresets;
	if (Presets.Num() == 0)
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("NoPresets", "No presets — add some in Project Settings → Nexus Authoring Tools"),
			FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction(), FCanExecuteAction::CreateLambda([]() { return false; })));
		return MenuBuilder.MakeWidget();
	}

	for (const FNexusCreatorPreset& Preset : Presets)
	{
		const FString Label = Preset.Name.IsEmpty()
			? FString::Printf(TEXT("Preset (%dx%d)"), Preset.GridSize.X, Preset.GridSize.Y)
			: Preset.Name;
		const FNexusCreatorPreset Captured = Preset;
		MenuBuilder.AddMenuEntry(
			FText::FromString(Label), FText::GetEmpty(), FSlateIcon(),
			FUIAction(FExecuteAction::CreateLambda([this, Captured]() { CreateFromPreset(Captured); })));
	}

	return MenuBuilder.MakeWidget();
}

void SNexusCreatorWindow::CreateFromPreset(const FNexusCreatorPreset& Preset)
{
	const ENexusItemTemplate Template =
		static_cast<ENexusItemTemplate>(FMath::Clamp<int32>(Preset.Template, 0, 7));

	FText Error;
	UNexusItemDefinition* Item = FNexusAssetCreation::CreateItem(
		Template, CreateFolderFor(FNexusAssetCreation::SubfolderForTemplate(Template)), CurrentName(), Error);
	if (!Item)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("PresetFail", "Could not create from the preset.") : Error;
		return;
	}

	// Apply the preset's smart defaults over the template's.
	Item->Modify();
	if (Preset.GridSize.X > 0 && Preset.GridSize.Y > 0)
	{
		Item->GridSize = Preset.GridSize;
	}
	Item->Weight = Preset.Weight;
	Item->BaseValue = Preset.BaseValue;
	Item->MarkPackageDirty();

	ActiveSlotHost = Item;
	AddEntry(Item, FString::Printf(TEXT("%s  (%s preset)"),
		*Item->GetName(), *(Preset.Name.IsEmpty() ? FString(TEXT("item")) : Preset.Name)));
	StatusText = FText::Format(
		LOCTEXT("PresetMade", "Created '{0}' from preset (unsaved — edit on the right, then Save All)."),
		FText::FromString(Item->GetName()));
}

void SNexusCreatorWindow::CreateWeaponSuite()
{
	const ENexusItemTemplate WeaponTemplate = bSuiteRanged
		? ENexusItemTemplate::RangedWeapon : ENexusItemTemplate::MeleeWeapon;

	FText Error;
	UNexusItemDefinition* Weapon = FNexusAssetCreation::CreateItem(
		WeaponTemplate, CreateFolderFor(FNexusAssetCreation::SubfolderForTemplate(WeaponTemplate)), CurrentName(), Error);
	if (!Weapon)
	{
		StatusText = Error.IsEmpty() ? LOCTEXT("SuiteWeaponFail", "Could not create the weapon.") : Error;
		return;
	}
	ActiveSlotHost = Weapon;
	AddEntry(Weapon, FString::Printf(TEXT("%s  (weapon)"), *Weapon->GetName()));

	const FString Base = Weapon->GetName();
	int32 Made = 1;

	// Create each checked attachment and auto-slot it onto the weapon.
	auto MakeAtt = [&](bool bWant, const FGameplayTag& TypeTag, const TCHAR* Suffix)
	{
		if (!bWant)
		{
			return;
		}
		FText AttErr;
		UNexusAttachmentDefinition* Att = FNexusAssetCreation::CreateAttachment(
			TypeTag, CreateFolderFor(TEXT("Attachments")), FString::Printf(TEXT("%s_%s"), *Base, Suffix), AttErr);
		if (Att)
		{
			FString SlotName;
			FNexusAssetCreation::AssignOrCreateSlot(Weapon, Att, TypeTag, SlotName);
			AddEntry(Att, FString::Printf(TEXT("%s  (%s attachment)"), *Att->GetName(), Suffix));
			++Made;
		}
	};

	MakeAtt(bSuiteSight,    NexusGameplayTags::Attachment_Type_Sight,    TEXT("Sight"));
	MakeAtt(bSuiteBarrel,   NexusGameplayTags::Attachment_Type_Barrel,   TEXT("Barrel"));
	MakeAtt(bSuiteMagazine, NexusGameplayTags::Attachment_Type_Magazine, TEXT("Magazine"));
	MakeAtt(bSuiteSlide,    NexusGameplayTags::Attachment_Type_Slide,    TEXT("Slide"));
	MakeAtt(bSuiteTrigger,  NexusGameplayTags::Attachment_Type_Trigger,  TEXT("Trigger"));

	if (bSuiteAmmo)
	{
		FText AmmoErr;
		UNexusItemDefinition* Ammo = FNexusAssetCreation::CreateItem(
			ENexusItemTemplate::Ammo,
			CreateFolderFor(FNexusAssetCreation::SubfolderForTemplate(ENexusItemTemplate::Ammo)),
			FString::Printf(TEXT("%s_Ammo"), *Base), AmmoErr);
		if (Ammo)
		{
			AddEntry(Ammo, FString::Printf(TEXT("%s  (ammo)"), *Ammo->GetName()));
			++Made;
		}
	}

	if (bSuiteRecipe)
	{
		FText RecErr;
		UNexusCombinationRecipe* Recipe = FNexusAssetCreation::CreateRecipe(
			UNexusEditorSettings::Get().RecipeFolder, FString::Printf(TEXT("%s_Recipe"), *Base), Weapon, RecErr);
		if (Recipe)
		{
			AddEntry(Recipe, FString::Printf(TEXT("%s  (recipe)"), *Recipe->GetName()));
			++Made;
		}
	}

	// Leave the weapon itself selected for editing.
	for (const TSharedPtr<FCreatedEntry>& EntryIt : Entries)
	{
		if (EntryIt.IsValid() && EntryIt->Asset.Get() == Weapon)
		{
			SelectEntry(EntryIt);
			break;
		}
	}

	StatusText = FText::Format(
		LOCTEXT("SuiteMade", "Created a {0}-asset weapon suite around '{1}' (unsaved — review on the right, then Save All)."),
		FText::AsNumber(Made), FText::FromString(Weapon->GetName()));
}

void SNexusCreatorWindow::Inspect(UObject* Asset)
{
	Inspected = Asset;
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject(Asset);
	}
	if (PreviewViewport.IsValid())
	{
		PreviewViewport->SetPreviewAsset(Asset);
	}
	RefreshValidation();
}

void SNexusCreatorWindow::OnInspectedPropertyChanged(const FPropertyChangedEvent& Event)
{
	// Re-apply the asset so a freshly-picked mesh appears in the viewport without
	// the user having to reselect the entry.
	if (PreviewViewport.IsValid())
	{
		PreviewViewport->RefreshPreview();
	}
	RefreshValidation();
}

void SNexusCreatorWindow::RefreshValidation()
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

FReply SNexusCreatorWindow::OnBannerClicked()
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

FText SNexusCreatorWindow::GetValidationText() const { return ValidationSummary; }
FSlateColor SNexusCreatorWindow::GetValidationColor() const { return ValidationColor; }
FText SNexusCreatorWindow::GetReferencesTooltip() const { return ReferencesTooltip; }

EVisibility SNexusCreatorWindow::GetBannerVisibility() const
{
	return Inspected.IsValid() ? EVisibility::Visible : EVisibility::Collapsed;
}

#undef LOCTEXT_NAMESPACE
