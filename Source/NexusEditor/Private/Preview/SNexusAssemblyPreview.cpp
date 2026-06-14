#include "Preview/SNexusAssemblyPreview.h"
#include "Preview/SNexusStatRadar.h"

#include "NexusEditorModule.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "StructUtils/InstancedStruct.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"

#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#define LOCTEXT_NAMESPACE "NexusAssemblyPreview"

namespace NexusPreview
{
	// Column ids only — the asset-gather, tag-leaf, stat-format, and section-label helpers
	// this file used to carry locally now live in NexusEditorUtil / NexusEditorWidgets.
	const FName ColStat("Stat");
	const FName ColBase("Base");
	const FName ColAttach("Attach");
	const FName ColUpgrade("Upgrade");
	const FName ColDelta("Delta");
	const FName ColFinal("Final");
}

/** Resolved-stat row: shows each step of the fold across columns. */
class SNexusStatRow : public SMultiColumnTableRow<TSharedPtr<FNexusResolvedStat>>
{
public:
	SLATE_BEGIN_ARGS(SNexusStatRow) {}
		SLATE_ARGUMENT(TSharedPtr<FNexusResolvedStat>, Stat)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
	{
		Stat = InArgs._Stat;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), Owner);
	}

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override
	{
		using namespace NexusPreview;
		auto Make = [](const FString& Text, const FSlateColor& Color = FSlateColor::UseForeground())
		{
			return SNew(SBox).Padding(FMargin(6.0f, 2.0f)).VAlign(VAlign_Center)
				[ SNew(STextBlock).Text(FText::FromString(Text)).ColorAndOpacity(Color) ];
		};

		if (Column == ColStat)    { return Make(NexusEditorUtil::TagLeaf(Stat->StatTag)); }
		if (Column == ColBase)    { return Make(NexusEditorUtil::FormatStat(Stat->Base)); }
		if (Column == ColAttach)  { return Make(NexusEditorUtil::FormatStat(Stat->AfterAttachments)); }
		if (Column == ColUpgrade) { return Make(NexusEditorUtil::FormatStat(Stat->AfterUpgrade)); }
		if (Column == ColDelta)
		{
			// Net change from base to final, with direction — the at-a-glance "did this
			// loadout help?" column.
			const float Delta = Stat->Final - Stat->Base;
			if (FMath::IsNearlyZero(Delta))
			{
				return Make(TEXT("—"), FSlateColor::UseSubduedForeground());
			}
			const FString Text = FString::Printf(TEXT("%s %s"),
				Delta > 0.0f ? TEXT("▲") : TEXT("▼"),
				*NexusEditorUtil::FormatStat(FMath::Abs(Delta)));
			return Make(Text, FSlateColor(Delta > 0.0f ? FStyleColors::AccentGreen : FStyleColors::Error));
		}
		if (Column == ColFinal)
		{
			return Make(NexusEditorUtil::FormatStat(Stat->Final),
				Stat->bClamped ? FSlateColor(FStyleColors::Warning) : FSlateColor::UseForeground());
		}
		return SNullWidget::NullWidget;
	}

private:
	TSharedPtr<FNexusResolvedStat> Stat;
};

void SNexusAssemblyPreview::Construct(const FArguments& InArgs)
{
	using namespace NexusPreview;

	// Weapons = items that carry a weapon fragment; attachments = all of them.
	TArray<UNexusItemDefinition*> AllItems;
	NexusEditorUtil::GatherAssets(AllItems);
	for (UNexusItemDefinition* Item : AllItems)
	{
		if (!NexusEditorUtil::HasWeaponFragment(Item)) { continue; }
		TSharedPtr<FWeaponOption> Option = MakeShared<FWeaponOption>();
		Option->Weapon = Item;
		Option->Label = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);
		Weapons.Add(Option);
	}

	TArray<UNexusAttachmentDefinition*> AllAttachments;
	NexusEditorUtil::GatherAssets(AllAttachments);
	for (UNexusAttachmentDefinition* Attachment : AllAttachments)
	{
		TSharedPtr<FAttachmentToggle> Toggle = MakeShared<FAttachmentToggle>();
		Toggle->Attachment = Attachment;
		Toggle->Label = NexusEditorUtil::DisplayLabel(Attachment, Attachment->DisplayName);
		Attachments.Add(Toggle);
	}

	if (Weapons.Num() > 0) { SelectedWeapon = Weapons[0]; }
	Recompute();

	ChildSlot
	[
		SNew(SVerticalBox)

		// Toolbar: weapon + upgrade tier.
		+ SVerticalBox::Slot().AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
			.Padding(10.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
				[ NexusEditorWidgets::SectionLabel(LOCTEXT("WeaponLabel", "WEAPON")) ]
				+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(8.0f, 0.0f)
				[
					SNew(SComboBox<TSharedPtr<FWeaponOption>>)
					.OptionsSource(&Weapons)
					.OnGenerateWidget(this, &SNexusAssemblyPreview::OnGenerateWeaponOption)
					.OnSelectionChanged(this, &SNexusAssemblyPreview::OnWeaponChanged)
					.InitiallySelectedItem(SelectedWeapon)
					[ SNew(STextBlock).Text(this, &SNexusAssemblyPreview::GetWeaponText) ]
				]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(16.0f, 0.0f, 0.0f, 0.0f)
				[ NexusEditorWidgets::SectionLabel(LOCTEXT("UpgradeLabel", "UPGRADE TIER")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(8.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(SSpinBox<int32>)
					.MinValue(0)
					.MaxValue(this, &SNexusAssemblyPreview::GetMaxUpgradeTier)
					.Value(this, &SNexusAssemblyPreview::GetUpgradeTier)
					.OnValueChanged(this, &SNexusAssemblyPreview::OnUpgradeTierChanged)
					.MinDesiredWidth(60.0f)
				]
			]
		]

		// Body: attachments | resolved stats.
		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f)
		[
			SNew(SSplitter)
			+ SSplitter::Slot().Value(0.35f)
			[
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(4.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
					[ NexusEditorWidgets::SectionLabel(LOCTEXT("AttachmentsHeader", "ATTACHMENTS — tick to install")) ]
					+ SVerticalBox::Slot().FillHeight(1.0f)
					[
						SAssignNew(AttachmentListView, SListView<TSharedPtr<FAttachmentToggle>>)
						.ListItemsSource(&Attachments)
						.OnGenerateRow(this, &SNexusAssemblyPreview::OnGenerateAttachmentRow)
						.SelectionMode(ESelectionMode::None)
					]
				]
			]
			+ SSplitter::Slot().Value(0.65f)
			[
				SNew(SSplitter)
				.Orientation(Orient_Vertical)
				+ SSplitter::Slot().Value(0.45f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
					.Padding(4.0f)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
						[ NexusEditorWidgets::SectionLabel(LOCTEXT("RadarHeader", "STAT RADAR — base vs final")) ]
						+ SVerticalBox::Slot().FillHeight(1.0f)
						[ SAssignNew(StatRadar, SNexusStatRadar) ]
					]
				]
				+ SSplitter::Slot().Value(0.55f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
					.Padding(4.0f)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
						[ NexusEditorWidgets::SectionLabel(LOCTEXT("StatsHeader", "RESOLVED STATS")) ]
						+ SVerticalBox::Slot().FillHeight(1.0f)
						[
							SAssignNew(StatListView, SListView<TSharedPtr<FNexusResolvedStat>>)
							.ListItemsSource(&ResultRows)
							.OnGenerateRow(this, &SNexusAssemblyPreview::OnGenerateStatRow)
							.SelectionMode(ESelectionMode::None)
							.HeaderRow(
								SNew(SHeaderRow)
								+ SHeaderRow::Column(ColStat).DefaultLabel(LOCTEXT("HStat", "Stat")).FillWidth(0.30f)
								+ SHeaderRow::Column(ColBase).DefaultLabel(LOCTEXT("HBase", "Base")).FillWidth(0.14f)
								+ SHeaderRow::Column(ColAttach).DefaultLabel(LOCTEXT("HAttach", "+Attach")).FillWidth(0.14f)
								+ SHeaderRow::Column(ColUpgrade).DefaultLabel(LOCTEXT("HUpgrade", "+Upgrade")).FillWidth(0.14f)
								+ SHeaderRow::Column(ColFinal).DefaultLabel(LOCTEXT("HFinal", "Final")).FillWidth(0.14f)
								+ SHeaderRow::Column(ColDelta).DefaultLabel(LOCTEXT("HDelta", "Δ Net")).FillWidth(0.14f))
						]
					]
				]
			]
		]
	];

	// Recompute once more now that StatRadar (which keeps its own copy of the
	// rendered stats, unlike the list view's bound source) exists.
	Recompute();
}

void SNexusAssemblyPreview::Recompute()
{
	UNexusItemDefinition* Weapon = SelectedWeapon.IsValid() ? SelectedWeapon->Weapon.Get() : nullptr;

	MaxTier = FNexusAssemblyPreview::GetMaxUpgradeTier(Weapon);
	UpgradeTier = FMath::Clamp(UpgradeTier, 0, MaxTier);

	TArray<UNexusAttachmentDefinition*> Installed;
	for (const TSharedPtr<FAttachmentToggle>& Toggle : Attachments)
	{
		if (Toggle.IsValid() && Toggle->bInstalled && Toggle->Attachment.IsValid())
		{
			Installed.Add(Toggle->Attachment.Get());
		}
	}

	const TArray<FNexusResolvedStat> Stats = FNexusAssemblyPreview::Resolve(Weapon, Installed, UpgradeTier);
	ResultRows.Reset(Stats.Num());
	for (const FNexusResolvedStat& Stat : Stats)
	{
		ResultRows.Add(MakeShared<FNexusResolvedStat>(Stat));
	}
	if (StatListView.IsValid())
	{
		StatListView->RequestListRefresh();
	}
	if (StatRadar.IsValid())
	{
		StatRadar->SetStats(Stats);
	}
}

TSharedRef<SWidget> SNexusAssemblyPreview::OnGenerateWeaponOption(TSharedPtr<FWeaponOption> InOption)
{
	return SNew(STextBlock).Text(FText::FromString(InOption.IsValid() ? InOption->Label : FString()));
}

void SNexusAssemblyPreview::OnWeaponChanged(TSharedPtr<FWeaponOption> InOption, ESelectInfo::Type SelectInfo)
{
	if (InOption.IsValid())
	{
		SelectedWeapon = InOption;
		Recompute();

		// Surface the chosen weapon in the Workbench Inspector.
		if (SelectedWeapon->Weapon.IsValid())
		{
			FNexusEditorModule::SetSelection(SelectedWeapon->Weapon.Get(), FNexusEditorModule::PreviewTabName);
		}
	}
}

FText SNexusAssemblyPreview::GetWeaponText() const
{
	return FText::FromString(SelectedWeapon.IsValid() ? SelectedWeapon->Label : TEXT("(no weapons found)"));
}

void SNexusAssemblyPreview::OnUpgradeTierChanged(int32 NewTier)
{
	UpgradeTier = NewTier;
	Recompute();
}

TSharedRef<ITableRow> SNexusAssemblyPreview::OnGenerateAttachmentRow(
	TSharedPtr<FAttachmentToggle> InToggle, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(STableRow<TSharedPtr<FAttachmentToggle>>, Owner)
	[
		SNew(SCheckBox)
		.Padding(FMargin(6.0f, 3.0f))
		.IsChecked_Lambda([InToggle]()
		{
			return (InToggle.IsValid() && InToggle->bInstalled) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		})
		.OnCheckStateChanged_Lambda([this, InToggle](ECheckBoxState NewState)
		{
			if (InToggle.IsValid())
			{
				InToggle->bInstalled = (NewState == ECheckBoxState::Checked);
				Recompute();
			}
		})
		[
			SNew(STextBlock).Text(FText::FromString(InToggle.IsValid() ? InToggle->Label : FString()))
		]
	];
}

TSharedRef<ITableRow> SNexusAssemblyPreview::OnGenerateStatRow(
	TSharedPtr<FNexusResolvedStat> InStat, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(SNexusStatRow, Owner).Stat(InStat);
}

#undef LOCTEXT_NAMESPACE
