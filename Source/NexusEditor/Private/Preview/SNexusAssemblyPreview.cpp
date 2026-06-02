#include "Preview/SNexusAssemblyPreview.h"

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

#define LOCTEXT_NAMESPACE "NexusAssemblyPreview"

namespace NexusPreview
{
	const FName ColStat("Stat");
	const FName ColBase("Base");
	const FName ColAttach("Attach");
	const FName ColUpgrade("Upgrade");
	const FName ColFinal("Final");

	template <typename T>
	void GatherAssets(TArray<T*>& Out)
	{
		const IAssetRegistry& AssetRegistry =
			FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
		FARFilter Filter;
		Filter.ClassPaths.Add(T::StaticClass()->GetClassPathName());
		Filter.bRecursiveClasses = true;
		TArray<FAssetData> Assets;
		AssetRegistry.GetAssets(Filter, Assets);
		for (const FAssetData& Data : Assets)
		{
			if (T* Object = Cast<T>(Data.GetAsset())) { Out.Add(Object); }
		}
	}

	bool HasWeaponFragment(const UNexusItemDefinition* Item)
	{
		if (!Item) { return false; }
		for (const TInstancedStruct<FNexusItemFragment>& Frag : Item->Fragments)
		{
			if (!Frag.IsValid()) { continue; }
			const UScriptStruct* Type = Frag.GetScriptStruct();
			if (Type && Type->IsChildOf(FNexusFragment_Weapon::StaticStruct())) { return true; }
		}
		return false;
	}

	FString Leaf(const FGameplayTag& Tag)
	{
		const FString Full = Tag.ToString();
		int32 Dot = INDEX_NONE;
		return Full.FindLastChar(TEXT('.'), Dot) ? Full.RightChop(Dot + 1) : Full;
	}

	FString Num(float Value) { return FString::Printf(TEXT("%g"), Value); }

	TSharedRef<SWidget> SectionLabel(const FText& Text)
	{
		return SNew(STextBlock)
			.Text(Text)
			.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground());
	}
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

		if (Column == ColStat)    { return Make(Leaf(Stat->StatTag)); }
		if (Column == ColBase)    { return Make(Num(Stat->Base)); }
		if (Column == ColAttach)  { return Make(Num(Stat->AfterAttachments)); }
		if (Column == ColUpgrade) { return Make(Num(Stat->AfterUpgrade)); }
		if (Column == ColFinal)
		{
			return Make(Num(Stat->Final),
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
	GatherAssets(AllItems);
	for (UNexusItemDefinition* Item : AllItems)
	{
		if (!HasWeaponFragment(Item)) { continue; }
		TSharedPtr<FWeaponOption> Option = MakeShared<FWeaponOption>();
		Option->Weapon = Item;
		Option->Label = Item->DisplayName.IsEmpty() ? Item->GetName() : Item->DisplayName.ToString();
		Weapons.Add(Option);
	}

	TArray<UNexusAttachmentDefinition*> AllAttachments;
	GatherAssets(AllAttachments);
	for (UNexusAttachmentDefinition* Attachment : AllAttachments)
	{
		TSharedPtr<FAttachmentToggle> Toggle = MakeShared<FAttachmentToggle>();
		Toggle->Attachment = Attachment;
		Toggle->Label = Attachment->DisplayName.IsEmpty() ? Attachment->GetName() : Attachment->DisplayName.ToString();
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
				[ SectionLabel(LOCTEXT("WeaponLabel", "WEAPON")) ]
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
				[ SectionLabel(LOCTEXT("UpgradeLabel", "UPGRADE TIER")) ]
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
					[ SectionLabel(LOCTEXT("AttachmentsHeader", "ATTACHMENTS — tick to install")) ]
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
				SNew(SBorder)
				.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
				.Padding(4.0f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(4.0f, 2.0f, 4.0f, 4.0f)
					[ SectionLabel(LOCTEXT("StatsHeader", "RESOLVED STATS")) ]
					+ SVerticalBox::Slot().FillHeight(1.0f)
					[
						SAssignNew(StatListView, SListView<TSharedPtr<FNexusResolvedStat>>)
						.ListItemsSource(&ResultRows)
						.OnGenerateRow(this, &SNexusAssemblyPreview::OnGenerateStatRow)
						.SelectionMode(ESelectionMode::None)
						.HeaderRow(
							SNew(SHeaderRow)
							+ SHeaderRow::Column(ColStat).DefaultLabel(LOCTEXT("HStat", "Stat")).FillWidth(0.34f)
							+ SHeaderRow::Column(ColBase).DefaultLabel(LOCTEXT("HBase", "Base")).FillWidth(0.16f)
							+ SHeaderRow::Column(ColAttach).DefaultLabel(LOCTEXT("HAttach", "+Attach")).FillWidth(0.16f)
							+ SHeaderRow::Column(ColUpgrade).DefaultLabel(LOCTEXT("HUpgrade", "+Upgrade")).FillWidth(0.17f)
							+ SHeaderRow::Column(ColFinal).DefaultLabel(LOCTEXT("HFinal", "Final")).FillWidth(0.17f))
					]
				]
			]
		]
	];
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
