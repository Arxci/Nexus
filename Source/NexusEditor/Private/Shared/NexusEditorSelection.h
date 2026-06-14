#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"

/**
 * The shared, editor-session-wide "currently selected Nexus asset".
 *
 * Every Nexus tool used to keep its selection to itself and only ever surfaced an
 * asset's properties by opening the full asset editor in a separate window. This is the
 * one place a selection lives so the Workbench's Inspector (and any other interested
 * tool) can show and edit whatever the designer just clicked, no matter which tool they
 * clicked it in.
 *
 * A tool *produces* a selection with FNexusEditorModule::SetSelection(Asset, MyTabName);
 * the Inspector *consumes* it by subscribing to the service. The existing
 * FNexusAssetWatcher already pushes any edit made through the Inspector back into every
 * open tool, so editing grid-size / weight / value on the right refreshes the tools on
 * the left for free.
 *
 * Lifetime: the service is owned by FNexusEditorModule (created on startup, destroyed on
 * shutdown). Subscribers store the returned FDelegateHandle and Unsubscribe() it in their
 * destructor — exactly the pattern FNexusAssetWatcher establishes — so a callback can
 * never fire into a dead widget.
 */
struct FNexusSelection
{
	/** The selected item(s) / attachment(s) / recipe(s); empty when cleared. Index 0 is primary. */
	TArray<TWeakObjectPtr<UObject>> Objects;

	/** Tab name of the tool that set the selection — for reveal-in-source and loop avoidance. */
	FName SourceTool = NAME_None;

	/** The primary (first live) object, or null. */
	UObject* Get() const
	{
		return Objects.Num() > 0 ? Objects[0].Get() : nullptr;
	}
	bool IsValid() const { return Get() != nullptr; }
	int32 Num() const { return Objects.Num(); }

	/** Live objects, in order — for multi-object Inspector edits. */
	TArray<UObject*> Resolve() const
	{
		TArray<UObject*> Out;
		Out.Reserve(Objects.Num());
		for (const TWeakObjectPtr<UObject>& Weak : Objects)
		{
			if (UObject* Obj = Weak.Get())
			{
				Out.Add(Obj);
			}
		}
		return Out;
	}
};

DECLARE_MULTICAST_DELEGATE_OneParam(FNexusOnSelectionChanged, const FNexusSelection&);

class FNexusSelectionService
{
public:
	/**
	 * Set the current selection and broadcast it. No broadcast when the object is unchanged
	 * (unless bForce) — this keeps a tool that re-applies its existing row selection after a
	 * live rebuild from echoing back into a feedback loop.
	 */
	void SetSelection(UObject* InObject, FName InSourceTool = NAME_None, bool bForce = false);

	/** Set a multi-object selection (e.g. for bulk-editing in the Inspector). */
	void SetSelection(const TArray<UObject*>& InObjects, FName InSourceTool = NAME_None, bool bForce = false);

	/** Clear the selection (broadcasts a null selection). */
	void ClearSelection(FName InSourceTool = NAME_None);

	const FNexusSelection& GetSelection() const { return Current; }

	/** Subscribe to selection changes; keep the handle and Unsubscribe() it in your destructor. */
	FDelegateHandle Subscribe(const FNexusOnSelectionChanged::FDelegate& Delegate);
	void Unsubscribe(FDelegateHandle Handle);

private:
	FNexusSelection Current;
	FNexusOnSelectionChanged OnChangedEvent;

	/** Guards against re-entrant broadcasts if a subscriber sets the selection while we broadcast. */
	bool bBroadcasting = false;
};
