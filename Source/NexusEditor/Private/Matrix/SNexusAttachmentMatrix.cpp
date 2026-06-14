#include "Matrix/SNexusAttachmentMatrix.h"

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

#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#define LOCTEXT_NAMESPACE "NexusAttachmentMatrix"

namespace NexusMatrix
{
	const FName ColAttachment("Attachment");
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
		if (Column == ColAttachment)
		{
			return NexusEditorWidgets::Cell(Row->Name);
		}

		const UNexusAttachmentDefinition* Attachment = Row->Attachment.Get();
		if (!Attachment) { return SNullWidget::NullWidget; }

		const FGameplayTag ColumnTag = FGameplayTag::RequestGameplayTag(Column, /*ErrorIfNotFound=*/ false);
		if (!ColumnTag.IsValid()) { return SNullWidget::NullWidget; }

		FString Marks;
		TArray<FString> TooltipParts;
		const bool bProvides = Attachment->ProvidedTags.HasTagExact(ColumnTag);
		const bool bRequires = Attachment->RequiredTags.HasTagExact(ColumnTag);
		const bool bConflicts = Attachment->ConflictTags.HasTagExact(ColumnTag);
		const FString FullTag = ColumnTag.ToString();
		if (bProvides)  { Marks += TEXT("P"); TooltipParts.Add(FString::Printf(TEXT("Provides %s"), *FullTag)); }
		if (bRequires)  { Marks += Marks.IsEmpty() ? TEXT("R") : TEXT(" R"); TooltipParts.Add(FString::Printf(TEXT("Requires %s"), *FullTag)); }
		if (bConflicts) { Marks += Marks.IsEmpty() ? TEXT("C") : TEXT(" C"); TooltipParts.Add(FString::Printf(TEXT("Conflicts with %s"), *FullTag)); }

		FSlateColor Color = FSlateColor::UseForeground();
		if (Marks == TEXT("P"))      { Color = FStyleColors::AccentGreen; }
		else if (Marks == TEXT("R")) { Color = FStyleColors::AccentBlue; }
		else if (Marks == TEXT("C")) { Color = FStyleColors::Error; }

		// Tooltip spells out the full tag so a cryptic leaf ("NATO") is unambiguous.
		return NexusEditorWidgets::Cell(Marks, Color, FString::Join(TooltipParts, TEXT("\n")));
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

	// Live: rebuild when attachments change.
	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start({ UNexusAttachmentDefinition::StaticClass() }, [this]() { Rebuild(); });
}

void SNexusAttachmentMatrix::Rebuild()
{
	using namespace NexusMatrix;

	TArray<UNexusAttachmentDefinition*> AllAttachments;
	NexusEditorUtil::GatherAssets(AllAttachments);

	Rows.Reset();
	TSet<FGameplayTag> ColumnSet;
	int32 Inconsistent = 0;
	for (UNexusAttachmentDefinition* Attachment : AllAttachments)
	{
		if (!Attachment) { continue; }

		TSharedPtr<FMatrixRow> Row = MakeShared<FMatrixRow>();
		Row->Attachment = Attachment;
		Row->Name = NexusEditorUtil::DisplayLabel(Attachment, Attachment->DisplayName);
		Rows.Add(Row);

		for (const FGameplayTag& ProvidedTag : Attachment->ProvidedTags) { ColumnSet.Add(ProvidedTag); }
		for (const FGameplayTag& RequiredTag : Attachment->RequiredTags) { ColumnSet.Add(RequiredTag); }
		for (const FGameplayTag& ConflictTag : Attachment->ConflictTags) { ColumnSet.Add(ConflictTag); }

		// A tag both required and conflicted-with can never be satisfied — flag it.
		if (Attachment->RequiredTags.HasAnyExact(Attachment->ConflictTags))
		{
			++Inconsistent;
		}
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
				.DefaultLabel(FText::FromString(NexusEditorUtil::TagLeaf(ColumnTag)))
				.DefaultTooltip(FText::FromString(ColumnTag.ToString())) // full tag on hover
				.HAlignHeader(HAlign_Center)
				.HAlignCell(HAlign_Center)
				.FillWidth(0.1f));
		}
	}

	SummaryText = (Inconsistent > 0)
		? FText::Format(LOCTEXT("SummaryBad", "{0} attachment(s), {1} type(s).   ⚠ {2} with required+conflicting tags."),
			FText::AsNumber(Rows.Num()), FText::AsNumber(TypeColumns.Num()), FText::AsNumber(Inconsistent))
		: FText::Format(LOCTEXT("Summary", "{0} attachment(s), {1} type(s)."),
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
