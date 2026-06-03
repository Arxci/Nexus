#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

#include "Creation/NexusAssetCreationLibrary.h"

class IDetailsView;
class ITableRow;
class STableViewBase;
class SComboButton;
class SEditableTextBox;
class SNexusItemViewport;
class SWidget;
class UNexusItemDefinition;
struct FPropertyChangedEvent;

/**
 * The Nexus Asset Creator: one window for stamping out Nexus assets and editing
 * them in place.
 *
 * A mode toggle splits creation into two clean lanes — Item (Ranged Weapon,
 * Consumable, …) and Attachment (Sight, Barrel, …) — so you only ever see the
 * controls for what you're making. Everything you create lands in a working-set
 * list on the left and opens in an embedded Details panel on the right.
 *
 * The inline flow: create a weapon, then switch to Attachment and create a Sight —
 * it's auto-slotted onto that weapon (a slot is added if the weapon doesn't have
 * one yet). Save All writes the working set to disk; Delete discards the selected
 * asset; Browse picks the destination folder from the content tree.
 */
class SNexusCreatorWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusCreatorWindow) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** Add an existing asset to the working set and select it (other tools hand off through this). */
	void LoadAsset(UObject* Asset);

private:
	enum class ECreateMode : uint8 { Item, Attachment, Recipe, Manifest, Loadout };

	/** One stamped asset in this session's working set. */
	struct FCreatedEntry
	{
		TWeakObjectPtr<UObject> Asset;
		FString Label;
	};

	/** One selectable attachment type in the Attachment-mode combo. */
	struct FAttachmentType
	{
		FText Label;
		FGameplayTag Tag;
	};

	// Mode.
	ECreateMode GetMode() const { return Mode; }
	void SetMode(ECreateMode NewMode) { Mode = NewMode; }
	int32 GetModePanelIndex() const
	{
		switch (Mode)
		{
		case ECreateMode::Attachment: return 1;
		case ECreateMode::Recipe:     return 2;
		case ECreateMode::Manifest:   return 3;
		case ECreateMode::Loadout:    return 4;
		default:                      return 0;
		}
	}

	// Create.
	FReply OnCreateClicked();
	void CreateItem(ENexusItemTemplate Template);
	void CreateAttachment(const FGameplayTag& TypeTag, const FText& TypeLabel);
	void CreateRecipeAsset();
	void CreateBlankManifest();
	void BuildManifestFromLevel();
	void CreateLoadoutAsset();

	// Item-template combo.
	TSharedRef<SWidget> OnGenerateItemTemplateRow(TSharedPtr<ENexusItemTemplate> InItem);
	void OnItemTemplateChanged(TSharedPtr<ENexusItemTemplate> NewItem, ESelectInfo::Type SelectInfo);
	FText GetItemTemplateText() const;

	// Attachment-type combo.
	TSharedRef<SWidget> OnGenerateAttachmentTypeRow(TSharedPtr<FAttachmentType> InItem);
	void OnAttachmentTypeChanged(TSharedPtr<FAttachmentType> NewItem, ESelectInfo::Type SelectInfo);
	FText GetAttachmentTypeText() const;

	// Working set.
	/** Returns true if a new entry was added; false if the asset was already in the working set (in which case it's just re-selected). */
	bool AddEntry(UObject* Asset, const FString& Label);
	void SelectEntry(TSharedPtr<FCreatedEntry> Entry);
	TSharedRef<ITableRow> OnGenerateEntryRow(TSharedPtr<FCreatedEntry> Entry, const TSharedRef<STableViewBase>& Owner);
	void OnEntrySelectionChanged(TSharedPtr<FCreatedEntry> Entry, ESelectInfo::Type SelectInfo);

	// Toolbar actions.
	FReply OnSaveAllClicked();
	FReply OnDeleteSelectedClicked();
	FReply OnDuplicateClicked();
	FReply OnLoadFromContentBrowserClicked();
	FReply OnAutoTagClicked();

	// Folder picker.
	TSharedRef<SWidget> MakeFolderPickerMenu();
	void OnFolderPicked(const FString& Path);

	// Bound text.
	FText GetStatusText() const;
	FText GetActiveHostText() const;

	// Live validation + "where used" banner over the details panel.
	void Inspect(UObject* Asset);
	void RefreshValidation();
	void OnInspectedPropertyChanged(const FPropertyChangedEvent& Event);
	FText GetValidationText() const;
	FSlateColor GetValidationColor() const;
	FText GetReferencesTooltip() const;
	EVisibility GetBannerVisibility() const;

	/** Banner click action — opens the Reference Viewer for the inspected asset. */
	FReply OnBannerClicked();
	FString CurrentFolder() const;
	FString CurrentName() const;

	/** Folder a new asset of the given type lands in (CurrentFolder, plus a type subfolder if routing is on). */
	FString CreateFolderFor(const FString& Subfolder) const;
	ECheckBoxState GetRouteByTypeState() const;
	void OnRouteByTypeChanged(ECheckBoxState NewState);

	ECreateMode Mode = ECreateMode::Item;
	bool bRouteByType = true;

	TArray<TSharedPtr<ENexusItemTemplate>> ItemTemplates;
	TSharedPtr<ENexusItemTemplate> SelectedItemTemplate;

	TArray<TSharedPtr<FAttachmentType>> AttachmentTypes;
	TSharedPtr<FAttachmentType> SelectedAttachmentType;

	TSharedPtr<SEditableTextBox> FolderBox;
	TSharedPtr<SEditableTextBox> NameBox;
	TSharedPtr<SComboButton> FolderPickerButton;
	TSharedPtr<IDetailsView> DetailsView;
	TSharedPtr<SNexusItemViewport> PreviewViewport;

	TArray<TSharedPtr<FCreatedEntry>> Entries;
	TSharedPtr<SListView<TSharedPtr<FCreatedEntry>>> EntryListView;

	/** Item new attachments auto-attach to — the last item created or selected. */
	TWeakObjectPtr<UNexusItemDefinition> ActiveSlotHost;

	/** The asset currently shown in the details panel (drives the validation/references banner). */
	TWeakObjectPtr<UObject> Inspected;
	FText ValidationSummary;
	FSlateColor ValidationColor = FSlateColor::UseForeground();
	FText ReferencesTooltip;

	FText StatusText;
};
