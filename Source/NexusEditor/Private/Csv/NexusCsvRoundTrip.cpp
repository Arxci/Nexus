#include "Csv/NexusCsvRoundTrip.h"

#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Misc/FileHelper.h"
#include "Serialization/Csv/CsvParser.h"
#include "StructUtils/InstancedStruct.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"

#define LOCTEXT_NAMESPACE "NexusCsv"

namespace
{
	const TCHAR* HeaderRow =
		TEXT("Path,Name,GridX,GridY,Weight,Value,Sellable,Buyable,Damage,RPM,Mag,Range,Reload,RecoilV,RecoilH,MeleeDamage,MeleeRange");

	void GatherItems(TArray<UNexusItemDefinition*>& Out)
	{
		const IAssetRegistry& AssetRegistry =
			FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

		FARFilter Filter;
		Filter.ClassPaths.Add(UNexusItemDefinition::StaticClass()->GetClassPathName());
		Filter.bRecursiveClasses = true;

		TArray<FAssetData> Assets;
		AssetRegistry.GetAssets(Filter, Assets);
		for (const FAssetData& Data : Assets)
		{
			if (UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(Data.GetAsset()))
			{
				Out.Add(Item);
			}
		}
	}

	const FNexusFragment_Weapon* FindWeapon(const UNexusItemDefinition* Item)
	{
		for (const TInstancedStruct<FNexusItemFragment>& Frag : Item->Fragments)
		{
			if (!Frag.IsValid()) { continue; }
			const UScriptStruct* Type = Frag.GetScriptStruct();
			if (Type && Type->IsChildOf(FNexusFragment_Weapon::StaticStruct()))
			{
				return Frag.GetPtr<const FNexusFragment_Weapon>();
			}
		}
		return nullptr;
	}

	FNexusFragment_Weapon* FindMutableWeapon(UNexusItemDefinition* Item)
	{
		for (TInstancedStruct<FNexusItemFragment>& Frag : Item->Fragments)
		{
			if (!Frag.IsValid()) { continue; }
			const UScriptStruct* Type = Frag.GetScriptStruct();
			if (Type && Type->IsChildOf(FNexusFragment_Weapon::StaticStruct()))
			{
				return Frag.GetMutablePtr<FNexusFragment_Weapon>();
			}
		}
		return nullptr;
	}

	FString Num(float Value)        { return FString::Printf(TEXT("%g"), Value); }

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
}

int32 FNexusCsv::ExportItems(const FString& Filename, FString& OutError)
{
	TArray<UNexusItemDefinition*> Items;
	GatherItems(Items);

	FString Csv = FString(HeaderRow) + TEXT("\n");
	for (const UNexusItemDefinition* Item : Items)
	{
		if (!Item) { continue; }
		const FNexusFragment_Weapon* Weapon = FindWeapon(Item);

		TArray<FString> Cells;
		Cells.Add(Item->GetPathName());
		Cells.Add(Item->DisplayName.ToString());
		Cells.Add(FString::FromInt(Item->GridSize.X));
		Cells.Add(FString::FromInt(Item->GridSize.Y));
		Cells.Add(Num(Item->Weight));
		Cells.Add(FString::FromInt(Item->BaseValue));
		Cells.Add(Item->bSellable ? TEXT("1") : TEXT("0"));
		Cells.Add(Item->bBuyable ? TEXT("1") : TEXT("0"));

		if (Weapon && Weapon->bHasRanged)
		{
			Cells.Add(Num(Weapon->Ranged.Combat.BaseDamage));
			Cells.Add(Num(Weapon->Ranged.Combat.RoundsPerMinute));
			Cells.Add(FString::FromInt(Weapon->Ranged.Ammo.MagazineSize));
			Cells.Add(Num(Weapon->Ranged.Combat.MaxRange));
			Cells.Add(Num(Weapon->Ranged.Reload.ReloadDuration));
			Cells.Add(Num(Weapon->Ranged.Combat.RecoilVertical));
			Cells.Add(Num(Weapon->Ranged.Combat.RecoilHorizontal));
		}
		else
		{
			for (int32 i = 0; i < 7; ++i) { Cells.Add(FString()); }
		}

		if (Weapon && Weapon->bHasMelee)
		{
			Cells.Add(Num(Weapon->Melee.BaseDamage));
			Cells.Add(Num(Weapon->Melee.Range));
		}
		else
		{
			Cells.Add(FString());
			Cells.Add(FString());
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

	TMap<FString, int32> Column;
	for (int32 i = 0; i < Rows[0].Num(); ++i)
	{
		Column.Add(FString(Rows[0][i]).TrimStartAndEnd(), i);
	}
	const int32* PathColumn = Column.Find(TEXT("Path"));
	if (!PathColumn)
	{
		OutError = LOCTEXT("NoPath", "The CSV has no 'Path' column to match rows by.").ToString();
		return -1;
	}

	TSet<FString> ChangedFields;
	int32 ChangedRows = 0;

	for (int32 RowIndex = 1; RowIndex < Rows.Num(); ++RowIndex)
	{
		const TArray<const TCHAR*>& Row = Rows[RowIndex];
		if (*PathColumn >= Row.Num()) { continue; }

		const FString Path = FString(Row[*PathColumn]).TrimStartAndEnd();
		if (Path.IsEmpty()) { continue; }

		UNexusItemDefinition* Item = LoadObject<UNexusItemDefinition>(nullptr, *Path);
		if (!Item) { continue; }

		auto Cell = [&Column, &Row](const TCHAR* Name) -> FString
		{
			const int32* Index = Column.Find(Name);
			return (Index && *Index < Row.Num()) ? FString(Row[*Index]).TrimStartAndEnd() : FString();
		};

		bool bRowChanged = false;
		bool bModified = false;
		auto Touch = [&Item, bDryRun, &bModified]()
		{
			if (!bDryRun && !bModified) { Item->Modify(); bModified = true; } // capture for undo
		};

		// A field counts (and writes) only when the cell is non-empty AND differs from the
		// current value — so the dry-run summary is a real diff, not just "touched".
		auto SetFloat = [&](const TCHAR* Name, float& Field)
		{
			const FString V = Cell(Name);
			if (V.IsEmpty()) { return; }
			const float NewValue = FCString::Atof(*V);
			if (!FMath::IsNearlyEqual(Field, NewValue))
			{
				ChangedFields.Add(Name); bRowChanged = true; Touch();
				if (!bDryRun) { Field = NewValue; }
			}
		};
		auto SetInt = [&](const TCHAR* Name, int32& Field)
		{
			const FString V = Cell(Name);
			if (V.IsEmpty()) { return; }
			const int32 NewValue = FCString::Atoi(*V);
			if (Field != NewValue)
			{
				ChangedFields.Add(Name); bRowChanged = true; Touch();
				if (!bDryRun) { Field = NewValue; }
			}
		};
		auto SetBool = [&](const TCHAR* Name, bool& Field)
		{
			const FString V = Cell(Name);
			if (V.IsEmpty()) { return; }
			const bool NewValue = (V == TEXT("1")) || V.ToBool();
			if (Field != NewValue)
			{
				ChangedFields.Add(Name); bRowChanged = true; Touch();
				if (!bDryRun) { Field = NewValue; }
			}
		};

		const FString NameCell = Cell(TEXT("Name"));
		if (!NameCell.IsEmpty() && !Item->DisplayName.ToString().Equals(NameCell))
		{
			ChangedFields.Add(TEXT("Name")); bRowChanged = true; Touch();
			if (!bDryRun) { Item->DisplayName = FText::FromString(NameCell); }
		}

		SetInt(TEXT("GridX"), Item->GridSize.X);
		SetInt(TEXT("GridY"), Item->GridSize.Y);
		SetFloat(TEXT("Weight"), Item->Weight);
		SetInt(TEXT("Value"), Item->BaseValue);
		SetBool(TEXT("Sellable"), Item->bSellable);
		SetBool(TEXT("Buyable"), Item->bBuyable);

		if (FNexusFragment_Weapon* Weapon = FindMutableWeapon(Item))
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

	if (bDryRun)
	{
		const FString FieldList = ChangedFields.Num() > 0
			? FString::Join(ChangedFields.Array(), TEXT(", ")) : FString(TEXT("(none)"));
		OutSummary = FString::Printf(TEXT("%d asset(s) would change.  Fields: %s"), ChangedRows, *FieldList);
	}
	else
	{
		OutSummary = FString::Printf(TEXT("Updated %d asset(s)."), ChangedRows);
	}
	return ChangedRows;
}

#undef LOCTEXT_NAMESPACE
