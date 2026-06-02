#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"

class ITableRow;
class STableViewBase;
class SWidget;
class SHeaderRow;
class UNexusAttachmentDefinition;

/**
 * The attachment compatibility matrix: attachments down the rows, every Attachment.Type.*
 * tag across the columns, and a P / R / C marker in each cell (Provides / Requires /
 * Conflicts). Read a column to see who provides a mount; read a row to see what a scope
 * needs and fights with. The tag graph — your signature system — made legible.
 * Double-click a row to open the attachment.
 */
class SNexusAttachmentMatrix : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusAttachmentMatrix) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** One attachment row (public so the multi-column row widget can reference it). */
	struct FMatrixRow
	{
		TWeakObjectPtr<UNexusAttachmentDefinition> Attachment;
		FString Name;
	};

private:
	void Rebuild();
	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FMatrixRow> Row, const TSharedRef<STableViewBase>& Owner);
	void OnRowDoubleClicked(TSharedPtr<FMatrixRow> Row);
	FReply OnRefreshClicked();
	FText GetSummaryText() const;

	TArray<FGameplayTag> TypeColumns;
	TArray<TSharedPtr<FMatrixRow>> Rows;
	TSharedPtr<SListView<TSharedPtr<FMatrixRow>>> ListView;
	TSharedPtr<SHeaderRow> HeaderRow;
	FText SummaryText;
};
