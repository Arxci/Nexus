#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Text.h"

/**
 * Single source of truth for the Nexus tool tabs: tab id, menu entry id,
 * label, tooltip, longer description (for Hub cards), icon brush, and the
 * category it belongs to. The module's Tools submenu, the Hub launcher,
 * the Workbench sidebar, and the toolbar drop-down all walk this list, so
 * adding a new tool is a one-place edit.
 */
namespace NexusEditorTools
{
	enum class ECategory : uint8
	{
		Authoring,
		Inspection,
		Auditing,
	};

	struct FToolEntry
	{
		/** Tab id registered with FGlobalTabmanager. */
		FName TabName;
		/** Menu entry id (must be unique within its parent section). */
		FName MenuEntryName;
		FText Label;
		FText Tooltip;
		/** One-liner shown under the title on Hub cards. */
		FText Description;
		/** FAppStyle brush name. */
		FName IconName;
		ECategory Category;
		/** False for tools that bring their own details panel (the Creator); the Workbench then
		 *  suppresses the shared Inspector for them instead of showing two editors side by side. */
		bool bUsesSharedInspector = true;
	};

	/** Tools in display order. */
	const TArray<FToolEntry>& All();

	/** Find by tab name; null when the name isn't a Nexus tool. */
	const FToolEntry* Find(FName TabName);

	/** Localised category title used as a section header. */
	FText CategoryLabel(ECategory Category);
}
