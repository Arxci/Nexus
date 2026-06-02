#include "Matrix/SNexusAttachmentMatrix.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

#include "Editor.h"
#include "Subsystems/AssetEditorSubsystem.h"

#include "Styling/AppStyle.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SHeaderRow.h"
#include "Widgets/Views/STableRow.h"

#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

#define LOCTEXT_NAMESPACE "NexusAttachmentMatrix"

namespace NexusMatrix
{
	const FName ColAttachment("Attachment");

	FString Leaf(const FGameplayTag& Tag)
	{
		const FString Full = Tag.ToString();
		int32 Dot = INDEX_NONE;
		return Full.FindLastChar(TEXT('.'), Dot) ? Full.RightChop(Dot + 1) : Full;
	}

	TSharedRef<SWidget> Cell(const FString& Text, const FSlateColor& Color)
	{
		return SNew(SBox).Padding(FMargin(6.0f, 2.0f)).VAlign(VAlign_Center)
			[ SNew(STextBlock).Text(FText::FromString(Text)).ColorAndOpacity(Color) ];
	}
}

/** One attachment row; each type column shows P / R / C for that attachment. */
class SNexusMatrixRow : public SMultiColumnTableRow<TSharedPtr<SNexusAttachmentMatrix::FMatrixRow>>
{
public:
	SLATE_BEGIN_ARGS(SNexusMatrixRow) {}
		SLATE_ARGUMENT(TSharedPtr<SNexusAttachmentMatrix::FMatrixRow>, Row)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& Owner)
	{
		Row = InArgs._Row;
		SMultiColumnTableRow::Construct(FSuperRowType::FArguments(), Owner);
	}

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& Column) override
	{
		using namespace NexusMatrix;
		if (!Row.IsValid()) { return SNullWidget::NullWidget; }
		if (Column == ColAttachment) { return Cell(Row->Name, FSlateColor::UseForeground()); }

		const UNexusAttachmentDefinition* Attachment = Row->Attachment.Get();
		if (!Attachment) { return SNullWidget::NullWidget; }

		const FGameplayTag ColumnTag = FGameplayTag::RequestGameplayTag(Column, /*ErrorIfNotFound=*/ false);
		if (!ColumnTag.IsValid()) { return SNullWidget::NullWidget; }

		FString Marks;
		const bool bProvides = Attachment->ProvidedTags.HasTagExact(ColumnTag);
		const bool bRequires = Attachment->RequiredTags.HasTagExact(ColumnTag);
		const bool bConflicts = Attachment->ConflictTags.HasTagExact(ColumnTag);
		if (bProvides)  { Marks += TEXT("P"); }
		if (bRequires)  { Marks += Marks.IsEmpty() ? TEXT("R") : TEXT(" R"); }
		if (bConflicts) { Marks += Marks.IsEmpty() ? TEXT("C") : TEXT(" C"); }

		FSlateColor Color = FSlateColor::UseForeground();
		if (Marks == TEXT("P"))      { Color = FStyleColors::AccentGreen; }
		else if (Marks == TEXT("R")) { Color = FStyleColors::AccentBlue; }
		else if (Marks == TEXT("C")) { Color = FStyleColors::Error; }

		return Cell(Marks, Color);
	}

private:
	TSharedPtr<SNexusAttachmentMatrix::FMatrixRow> Row;
};

void SNexusAttachmentMatrix::Construct(const FArguments& InArgs)
{
	SAssignNew(HeaderRow, SHeaderRow);

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot().AutoHeight().Padding(8.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
			[ SNew(SButton).Text(LOCTEXT("Refresh", "Refresh")).OnClicked(this, &SNexusAttachmentMatrix::OnRefreshClicked) ]
			+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
			[ SNew(STextBlock).Text(this, &SNexusAttachmentMatrix::GetSummaryText) ]
			+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
			[ SNew(STextBlock).Text(LOCTEXT("Legend", "P = provides   R = requires   C = conflicts")).ColorAndOpacity(FSlateColor::UseSubduedForeground()) ]
		]

		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f, 0.0f, 8.0f, 8.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(4.0f)
			[
				SAssignNew(ListView, SListView<TSharedPtr<FMatrixRow>>)
				.ListItemsSource(&Rows)
				.OnGenerateRow(this, &SNexusAttachmentMatrix::OnGenerateRow)
				.OnMouseButtonDoubleClick(this, &SNexusAttachmentMatrix::OnRowDoubleClicked)
				.SelectionMode(ESelectionMode::Single)
				.HeaderRow(HeaderRow.ToSharedRef())
			]
		]
	];

	Rebuild();
}

void SNexusAttachmentMatrix::Rebuild()
{
	using namespace NexusMatrix;

	const IAssetRegistry& AssetRegistry =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	FARFilter Filter;
	Filter.ClassPaths.Add(UNexusAttachmentDefinition::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = true;
	TArray<FAssetData> Assets;
	AssetRegistry.GetAssets(Filter, Assets);

	Rows.Reset();
	TSet<FGameplayTag> ColumnSet;
	for (const FAssetData& Data : Assets)
	{
		UNexusAttachmentDefinition* Attachment = Cast<UNexusAttachmentDefinition>(Data.GetAsset());
		if (!Attachment) { continue; }

		TSharedPtr<FMatrixRow> Row = MakeShared<FMatrixRow>();
		Row->Attachment = Attachment;
		Row->Name = Attachment->DisplayName.IsEmpty() ? Attachment->GetName() : Attachment->DisplayName.ToString();
		Rows.Add(Row);

		for (const FGameplayTag& ProvidedTag : Attachment->ProvidedTags) { ColumnSet.Add(ProvidedTag); }
		for (const FGameplayTag& RequiredTag : Attachment->RequiredTags) { ColumnSet.Add(RequiredTag); }
		for (const FGameplayTag& ConflictTag : Attachment->ConflictTags) { ColumnSet.Add(ConflictTag); }
	}

	TypeColumns = ColumnSet.Array();
	TypeColumns.Sort([](const FGameplayTag& A, const FGameplayTag& B) { return A.ToString() < B.ToString(); });

	Rows.Sort([](const TSharedPtr<FMatrixRow>& A, const TSharedPtr<FMatrixRow>& B)
	{
		return (A.IsValid() ? A->Name : FString()) < (B.IsValid() ? B->Name : FString());
	});

	// Rebuild the dynamic columns: one per type tag.
	if (HeaderRow.IsValid())
	{
		HeaderRow->ClearColumns();
		HeaderRow->AddColumn(SHeaderRow::Column(ColAttachment)
			.DefaultLabel(LOCTEXT("AttachmentCol", "Attachment")).FillWidth(0.25f));
		for (const FGameplayTag& ColumnTag : TypeColumns)
		{
			HeaderRow->AddColumn(SHeaderRow::Column(FName(*ColumnTag.ToString()))
				.DefaultLabel(FText::FromString(Leaf(ColumnTag)))
				.HAlignHeader(HAlign_Center)
				.HAlignCell(HAlign_Center)
				.FillWidth(0.1f));
		}
	}

	SummaryText = FText::Format(LOCTEXT("Summary", "{0} attachment(s), {1} type(s)."),
		FText::AsNumber(Rows.Num()), FText::AsNumber(TypeColumns.Num()));

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SNexusAttachmentMatrix::OnGenerateRow(
	TSharedPtr<FMatrixRow> Row, const TSharedRef<STableViewBase>& Owner)
{
	return SNew(SNexusMatrixRow, Owner).Row(Row);
}

void SNexusAttachmentMatrix::OnRowDoubleClicked(TSharedPtr<FMatrixRow> Row)
{
	if (Row.IsValid() && Row->Attachment.IsValid() && GEditor)
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Row->Attachment.Get());
	}
}

FReply SNexusAttachmentMatrix::OnRefreshClicked()
{
	Rebuild();
	return FReply::Handled();
}

FText SNexusAttachmentMatrix::GetSummaryText() const
{
	return SummaryText;
}

#undef LOCTEXT_NAMESPACE
