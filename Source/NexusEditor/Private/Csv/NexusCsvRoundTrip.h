#pragma once

#include "CoreMinimal.h"

/**
 * Spreadsheet round-trip for the item/weapon roster — how a team actually balances.
 * ExportItems writes one row per UNexusItemDefinition (identity, footprint, economy, and
 * the headline weapon stats pulled out of the weapon fragment) keyed by asset path.
 * ImportItems reads a sheet back, matches each row to its asset by that path, and writes
 * the changed cells back into the asset (marking it dirty for a normal Save).
 *
 * Blank cells are left untouched on import, so you can hand-edit a subset. Editor-only.
 */
struct FNexusCsv
{
	/** Write the roster to Filename. Returns the row count, or -1 + OutError on failure. */
	static int32 ExportItems(const FString& Filename, FString& OutError);

	/**
	 * Apply a previously exported sheet back onto the assets, matched by path. With
	 * bDryRun it only counts how many assets would change and which fields (into
	 * OutSummary) without mutating — for a confirm step. Without bDryRun it calls
	 * Modify() (so the change is undoable) and writes the differing cells. Returns the
	 * number of assets that (would) change, or -1 + OutError.
	 */
	static int32 ImportItems(const FString& Filename, bool bDryRun, FString& OutSummary, FString& OutError);
};
