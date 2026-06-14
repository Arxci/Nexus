#pragma once

#include "CoreMinimal.h"
#include "Misc/ConfigCacheIni.h"

/**
 * Tiny per-user persistence for the Nexus tools' UI state (last tool, splitter sizes,
 * last case size, ...). Writes to GEditorPerProjectIni under a single [NexusWorkbench]
 * section, so it's per-developer and never pollutes the team-shared DefaultEditor.ini that
 * UNexusEditorSettings uses.
 *
 * Header-only inlines over GConfig — include and use. Every setter flushes so state
 * survives an editor crash; these fire on user actions (tool switch, splitter drag), not
 * per frame, so the cost is irrelevant.
 */
namespace NexusEditorPersistence
{
	inline const TCHAR* Section() { return TEXT("NexusWorkbench"); }

	inline void SetString(const TCHAR* Key, const FString& Value)
	{
		if (GConfig)
		{
			GConfig->SetString(Section(), Key, *Value, GEditorPerProjectIni);
			GConfig->Flush(false, GEditorPerProjectIni);
		}
	}

	inline FString GetString(const TCHAR* Key, const FString& Default = FString())
	{
		FString Value;
		return (GConfig && GConfig->GetString(Section(), Key, Value, GEditorPerProjectIni)) ? Value : Default;
	}

	inline void SetFloat(const TCHAR* Key, float Value)
	{
		if (GConfig)
		{
			GConfig->SetFloat(Section(), Key, Value, GEditorPerProjectIni);
			GConfig->Flush(false, GEditorPerProjectIni);
		}
	}

	inline float GetFloat(const TCHAR* Key, float Default)
	{
		float Value = Default;
		return (GConfig && GConfig->GetFloat(Section(), Key, Value, GEditorPerProjectIni)) ? Value : Default;
	}

	inline void SetInt(const TCHAR* Key, int32 Value)
	{
		if (GConfig)
		{
			GConfig->SetInt(Section(), Key, Value, GEditorPerProjectIni);
			GConfig->Flush(false, GEditorPerProjectIni);
		}
	}

	inline int32 GetInt(const TCHAR* Key, int32 Default)
	{
		int32 Value = Default;
		return (GConfig && GConfig->GetInt(Section(), Key, Value, GEditorPerProjectIni)) ? Value : Default;
	}
}
