#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

#include "Preview/NexusAssemblyPreview.h"

class ITableRow;
class SNexusStatRadar;
class STableViewBase;
class SWidget;
class UNexusItemDefinition;
class UNexusAttachmentDefinition;

/**
 * The Nexus Assembly Preview: pick a weapon, tick the attachments to install, drag the
 * upgrade tier, and watch the resolved effective stats update live — base, after
 * attachments, after upgrade, and the final clamped value, side by side. The numbers come
 * from FNexusAssemblyPreview (which reuses the game's own SeedStatTags / SeedStatClamps),
 * so it shows exactly what the runtime assembly would compute.
 */
class SNexusAssemblyPreview : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusAssemblyPreview) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	struct FWeaponOption
	{
		TWeakObjectPtr<UNexusItemDefinition> Weapon;
		FString Label;
	};

	struct FAttachmentToggle
	{
		TWeakObjectPtr<UNexusAttachmentDefinition> Attachment;
		FString Label;
		bool bInstalled = false;
	};

	void Recompute();

	TSharedRef<SWidget> OnGenerateWeaponOption(TSharedPtr<FWeaponOption> InOption);
	void OnWeaponChanged(TSharedPtr<FWeaponOption> InOption, ESelectInfo::Type SelectInfo);
	FText GetWeaponText() const;

	TSharedRef<ITableRow> OnGenerateAttachmentRow(TSharedPtr<FAttachmentToggle> InToggle, const TSharedRef<STableViewBase>& Owner);
	TSharedRef<ITableRow> OnGenerateStatRow(TSharedPtr<FNexusResolvedStat> InStat, const TSharedRef<STableViewBase>& Owner);

	int32 GetUpgradeTier() const { return UpgradeTier; }
	TOptional<int32> GetMaxUpgradeTier() const { return MaxTier; } // SSpinBox::MaxValue is a TOptional
	void OnUpgradeTierChanged(int32 NewTier);

	TArray<TSharedPtr<FWeaponOption>> Weapons;
	TSharedPtr<FWeaponOption> SelectedWeapon;
	TArray<TSharedPtr<FAttachmentToggle>> Attachments;
	TArray<TSharedPtr<FNexusResolvedStat>> ResultRows;

	TSharedPtr<SListView<TSharedPtr<FAttachmentToggle>>> AttachmentListView;
	TSharedPtr<SListView<TSharedPtr<FNexusResolvedStat>>> StatListView;
	TSharedPtr<SNexusStatRadar> StatRadar;

	int32 UpgradeTier = 0;
	int32 MaxTier = 0;
};
