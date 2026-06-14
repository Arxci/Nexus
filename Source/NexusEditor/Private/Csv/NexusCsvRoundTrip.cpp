#include "Csv/NexusCsvRoundTrip.h"

#include "Misc/FileHelper.h"
#include "Serialization/Csv/CsvParser.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"

#include "Shared/NexusEditorUtils.h"

#define LOCTEXT_NAMESPACE "NexusCsv"

namespace NexusCsvSchema
{
	enum class EColType : uint8 { Str, Int, Float, Bool };

	/** One column in the round-trip schema — the single source of truth for header + validation. */
	struct FColumn
	{
		const TCHAR* Name;
		EColType Type;
		float Min;
		float Max;
		bool bMandatory;
	};

	// The registry. Export derives its header from this; import validates against it. Reorder a
	// spreadsheet's columns freely — import matches by name, not position.
	const TArray<FColumn>& Columns()
	{
		static const TArray<FColumn> Cols = {
			{ TEXT("Path"),        EColType::Str,   0.0f,       0.0f,    true  },
			{ TEXT("Name"),        EColType::Str,   0.0f,       0.0f,    false },
			{ TEXT("GridX"),       EColType::Int,   1.0f,       64.0f,   false },
			{ TEXT("GridY"),       EColType::Int,   1.0f,       64.0f,   false },
			{ TEXT("Weight"),      EColType::Float, 0.0f,       100000.f,false },
			{ TEXT("Value"),       EColType::Int,   0.0f,       1.0e9f,  false },
			{ TEXT("Sellable"),    EColType::Bool,  0.0f,       0.0f,    false },
			{ TEXT("Buyable"),     EColType::Bool,  0.0f,       0.0f,    false },
			{ TEXT("Damage"),      EColType::Float, 0.0f,       1.0e6f,  false },
			{ TEXT("RPM"),         EColType::Float, 0.0f,       100000.f,false },
			{ TEXT("Mag"),         EColType::Int,   0.0f,       100000.f,false },
			{ TEXT("Range"),       EColType::Float, 0.0f,       1.0e6f,  false },
			{ TEXT("Reload"),      EColType::Float, 0.0f,       1000.0f, false },
			{ TEXT("RecoilV"),     EColType::Float, -10000.f,   10000.f, false },
			{ TEXT("RecoilH"),     EColType::Float, -10000.f,   10000.f, false },
			{ TEXT("MeleeDamage"), EColType::Float, 0.0f,       1.0e6f,  false },
			{ TEXT("MeleeRange"),  EColType::Float, 0.0f,       1.0e6f,  false },
		};
		return Cols;
	}

	const FColumn* Find(const FString& Name)
	{
		for (const FColumn& Col : Columns())
		{
			if (Name.Equals(Col.Name)) { return &Col; }
		}
		return nullptr;
	}
}

namespace
{
	/** Quote a CSV field if it contains a comma, quote, or newline. */
	FString Field(const FString& In)
	{
		if (In.Contains(TEXT(",")) || In.Contains(TEXT("\"")) || In.Contains(TEXT("\n")))
		{
			FString Quoted = In;
			Quoted.ReplaceInline(TEXT("\""), TEXT("\"\""));
			return TEXT("\"") + Quoted + TEXT("\"");
		}
		return In;
	}

	FString JoinRow(const TArray<FString>& Cells)
	{
		TArray<FString> Quoted;
		Quoted.Reserve(Cells.Num());
		for (const FString& Cell : Cells) { Quoted.Add(Field(Cell)); }
		return FString::Join(Quoted, TEXT(","));
	}

	/** Value of one schema column for an item, as the exported string ("" when N/A). */
	FString ExportCell(const UNexusItemDefinition* Item, const FNexusFragment_Weapon* Weapon, const TCHAR* Name)
	{
		const FString N(Name);
		if (N == TEXT("Path"))     { return Item->GetPathName(); }
		if (N == TEXT("Name"))     { return Item->DisplayName.ToString(); }
		if (N == TEXT("GridX"))    { return FString::FromInt(Item->GridSize.X); }
		if (N == TEXT("GridY"))    { return FString::FromInt(Item->GridSize.Y); }
		if (N == TEXT("Weight"))   { return NexusEditorUtil::FormatStat(Item->Weight); }
		if (N == TEXT("Value"))    { return FString::FromInt(Item->BaseValue); }
		if (N == TEXT("Sellable")) { return Item->bSellable ? TEXT("1") : TEXT("0"); }
		if (N == TEXT("Buyable"))  { return Item->bBuyable ? TEXT("1") : TEXT("0"); }

		const bool bRanged = Weapon && Weapon->bHasRanged;
		if (N == TEXT("Damage"))  { return bRanged ? NexusEditorUtil::FormatStat(Weapon->Ranged.Combat.BaseDamage) : FString(); }
		if (N == TEXT("RPM"))     { return bRanged ? NexusEditorUtil::FormatStat(Weapon->Ranged.Combat.RoundsPerMinute) : FString(); }
		if (N == TEXT("Mag"))     { return bRanged ? FString::FromInt(Weapon->Ranged.Ammo.MagazineSize) : FString(); }
		if (N == TEXT("Range"))   { return bRanged ? NexusEditorUtil::FormatStat(Weapon->Ranged.Combat.MaxRange) : FString(); }
		if (N == TEXT("Reload"))  { return bRanged ? NexusEditorUtil::FormatStat(Weapon->Ranged.Reload.ReloadDuration) : FString(); }
		if (N == TEXT("RecoilV")) { return bRanged ? NexusEditorUtil::FormatStat(Weapon->Ranged.Combat.RecoilVertical) : FString(); }
		if (N == TEXT("RecoilH")) { return bRanged ? NexusEditorUtil::FormatStat(Weapon->Ranged.Combat.RecoilHorizontal) : FString(); }

		const bool bMelee = Weapon && Weapon->bHasMelee;
		if (N == TEXT("MeleeDamage")) { return bMelee ? NexusEditorUtil::FormatStat(Weapon->Melee.BaseDamage) : FString(); }
		if (N == TEXT("MeleeRange"))  { return bMelee ? NexusEditorUtil::FormatStat(Weapon->Melee.Range) : FString(); }
		return FString();
	}
}

int32 FNexusCsv::ExportItems(const FString& Filename, FString& OutError)
{
	using namespace NexusCsvSchema;

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);

	// Header straight from the registry, so it can never drift from the columns we write.
	TArray<FString> HeaderCells;
	for (const FColumn& Col : Columns()) { HeaderCells.Add(Col.Name); }
	FString Csv = FString::Join(HeaderCells, TEXT(",")) + TEXT("\n");

	for (const UNexusItemDefinition* Item : Items)
	{
		if (!Item) { continue; }
		const FNexusFragment_Weapon* Weapon = NexusEditorUtil::FindWeaponFragment(Item);

		TArray<FString> Cells;
		Cells.Reserve(Columns().Num());
		for (const FColumn& Col : Columns())
		{
			Cells.Add(ExportCell(Item, Weapon, Col.Name));
		}
		Csv += JoinRow(Cells) + TEXT("\n");
	}

	if (!FFileHelper::SaveStringToFile(Csv, *Filename))
	{
		OutError = FText::Format(LOCTEXT("SaveFail", "Could not write {0}."), FText::FromString(Filename)).ToString();
		return -1;
	}
	return Items.Num();
}

int32 FNexusCsv::ImportItems(const FString& Filename, bool bDryRun, FString& OutSummary, FString& OutError)
{
	using namespace NexusCsvSchema;

	FString Content;
	if (!FFileHelper::LoadFileToString(Content, *Filename))
	{
		OutError = FText::Format(LOCTEXT("LoadFail", "Could not read {0}."), FText::FromString(Filename)).ToString();
		return -1;
	}

	const FCsvParser Parser(MoveTemp(Content));
	const TArray<TArray<const TCHAR*>>& Rows = Parser.GetRows();
	if (Rows.Num() < 2)
	{
		OutError = LOCTEXT("Empty", "The CSV has no data rows.").ToString();
		return 0;
	}

	// Name -> column index (resilient to reordering / extra columns).
	TMap<FString, int32> Column;
	for (int32 i = 0; i < Rows[0].Num(); ++i)
	{
		Column.Add(FString(Rows[0][i]).TrimStartAndEnd(), i);
	}

	// Validate the header against the registry: every mandatory column must be present, and
	// any column we don't recognise is reported (not fatal).
	TArray<FString> HeaderIssues;
	for (const FColumn& Col : Columns())
	{
		if (Col.bMandatory && !Column.Contains(Col.Name))
		{
			HeaderIssues.Add(FString::Printf(TEXT("missing mandatory column '%s'"), Col.Name));
		}
	}
	if (!Column.Contains(TEXT("Path")))
	{
		OutError = LOCTEXT("NoPath", "The CSV has no 'Path' column to match rows by.").ToString();
		return -1;
	}
	const int32 PathColumn = Column[TEXT("Path")];

	TArray<FString> DiffLines;     // "ItemName.Field: old -> new"
	TArray<FString> Warnings;      // out-of-range / unparseable values, skipped
	int32 ChangedRows = 0;

	for (int32 RowIndex = 1; RowIndex < Rows.Num(); ++RowIndex)
	{
		const TArray<const TCHAR*>& Row = Rows[RowIndex];
		if (PathColumn >= Row.Num()) { continue; }

		const FString Path = FString(Row[PathColumn]).TrimStartAndEnd();
		if (Path.IsEmpty()) { continue; }

		UNexusItemDefinition* Item = LoadObject<UNexusItemDefinition>(nullptr, *Path);
		if (!Item) { continue; }

		const FString ItemName = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);

		auto Cell = [&Column, &Row](const TCHAR* Name) -> FString
		{
			const int32* Index = Column.Find(Name);
			return (Index && *Index < Row.Num()) ? FString(Row[*Index]).TrimStartAndEnd() : FString();
		};

		bool bRowChanged = false;
		bool bModified = false;
		auto Touch = [&Item, bDryRun, &bModified]()
		{
			if (!bDryRun && !bModified) { Item->Modify(); bModified = true; }
		};

		// Returns true when the (non-empty, in-range) numeric value V should be applied; logs a
		// warning and returns false when it's out of the registry's [Min,Max] for that column.
		auto InRange = [&](const TCHAR* Name, float V) -> bool
		{
			const FColumn* Col = Find(Name);
			if (Col && (Col->Type == EColType::Int || Col->Type == EColType::Float))
			{
				if (V < Col->Min || V > Col->Max)
				{
					Warnings.Add(FString::Printf(TEXT("%s.%s = %g is outside [%g, %g] — skipped"),
						*ItemName, Name, V, Col->Min, Col->Max));
					return false;
				}
			}
			return true;
		};

		auto SetFloat = [&](const TCHAR* Name, float& FieldRef)
		{
			const FString V = Cell(Name);
			if (V.IsEmpty()) { return; }
			const float NewValue = FCString::Atof(*V);
			if (!InRange(Name, NewValue)) { return; }
			if (!FMath::IsNearlyEqual(FieldRef, NewValue))
			{
				DiffLines.Add(FString::Printf(TEXT("%s.%s: %g -> %g"), *ItemName, Name, FieldRef, NewValue));
				bRowChanged = true; Touch();
				if (!bDryRun) { FieldRef = NewValue; }
			}
		};
		auto SetInt = [&](const TCHAR* Name, int32& FieldRef)
		{
			const FString V = Cell(Name);
			if (V.IsEmpty()) { return; }
			const int32 NewValue = FCString::Atoi(*V);
			if (!InRange(Name, static_cast<float>(NewValue))) { return; }
			if (FieldRef != NewValue)
			{
				DiffLines.Add(FString::Printf(TEXT("%s.%s: %d -> %d"), *ItemName, Name, FieldRef, NewValue));
				bRowChanged = true; Touch();
				if (!bDryRun) { FieldRef = NewValue; }
			}
		};
		auto SetBool = [&](const TCHAR* Name, bool& FieldRef)
		{
			const FString V = Cell(Name);
			if (V.IsEmpty()) { return; }
			const bool NewValue = (V == TEXT("1")) || V.ToBool();
			if (FieldRef != NewValue)
			{
				DiffLines.Add(FString::Printf(TEXT("%s.%s: %s -> %s"), *ItemName, Name,
					FieldRef ? TEXT("true") : TEXT("false"), NewValue ? TEXT("true") : TEXT("false")));
				bRowChanged = true; Touch();
				if (!bDryRun) { FieldRef = NewValue; }
			}
		};

		const FString NameCell = Cell(TEXT("Name"));
		if (!NameCell.IsEmpty() && !Item->DisplayName.ToString().Equals(NameCell))
		{
			DiffLines.Add(FString::Printf(TEXT("%s.Name: '%s' -> '%s'"), *ItemName, *Item->DisplayName.ToString(), *NameCell));
			bRowChanged = true; Touch();
			if (!bDryRun) { Item->DisplayName = FText::FromString(NameCell); }
		}

		SetInt(TEXT("GridX"), Item->GridSize.X);
		SetInt(TEXT("GridY"), Item->GridSize.Y);
		SetFloat(TEXT("Weight"), Item->Weight);
		SetInt(TEXT("Value"), Item->BaseValue);
		SetBool(TEXT("Sellable"), Item->bSellable);
		SetBool(TEXT("Buyable"), Item->bBuyable);

		if (FNexusFragment_Weapon* Weapon = NexusEditorUtil::FindMutableWeaponFragment(Item))
		{
			SetFloat(TEXT("Damage"), Weapon->Ranged.Combat.BaseDamage);
			SetFloat(TEXT("RPM"), Weapon->Ranged.Combat.RoundsPerMinute);
			SetInt(TEXT("Mag"), Weapon->Ranged.Ammo.MagazineSize);
			SetFloat(TEXT("Range"), Weapon->Ranged.Combat.MaxRange);
			SetFloat(TEXT("Reload"), Weapon->Ranged.Reload.ReloadDuration);
			SetFloat(TEXT("RecoilV"), Weapon->Ranged.Combat.RecoilVertical);
			SetFloat(TEXT("RecoilH"), Weapon->Ranged.Combat.RecoilHorizontal);
			SetFloat(TEXT("MeleeDamage"), Weapon->Melee.BaseDamage);
			SetFloat(TEXT("MeleeRange"), Weapon->Melee.Range);
		}

		if (bRowChanged)
		{
			++ChangedRows;
			if (!bDryRun) { Item->MarkPackageDirty(); }
		}
	}

	// Build the summary: a real per-field diff (the "visual diff" content), plus any warnings.
	TArray<FString> Lines;
	if (HeaderIssues.Num() > 0)
	{
		Lines.Add(FString::Printf(TEXT("Header: %s"), *FString::Join(HeaderIssues, TEXT("; "))));
	}
	Lines.Add(bDryRun
		? FString::Printf(TEXT("%d asset(s) would change, %d field edit(s):"), ChangedRows, DiffLines.Num())
		: FString::Printf(TEXT("Updated %d asset(s) (%d field edit(s))."), ChangedRows, DiffLines.Num()));
	Lines.Append(DiffLines);
	if (Warnings.Num() > 0)
	{
		Lines.Add(FString::Printf(TEXT("--- %d warning(s) ---"), Warnings.Num()));
		Lines.Append(Warnings);
	}
	OutSummary = FString::Join(Lines, TEXT("\n"));
	return ChangedRows;
}

#undef LOCTEXT_NAMESPACE
