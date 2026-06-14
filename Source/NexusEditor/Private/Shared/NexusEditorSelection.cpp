#include "Shared/NexusEditorSelection.h"

void FNexusSelectionService::SetSelection(UObject* InObject, FName InSourceTool, bool bForce)
{
	TArray<UObject*> One;
	if (InObject)
	{
		One.Add(InObject);
	}
	SetSelection(One, InSourceTool, bForce);
}

void FNexusSelectionService::SetSelection(const TArray<UObject*>& InObjects, FName InSourceTool, bool bForce)
{
	// Unchanged? (same objects in the same order) — refresh the source tag but don't
	// re-broadcast. Tools re-apply their current row selection after a live rebuild; this
	// is what stops the echo.
	bool bSame = !bForce && Current.Objects.Num() == InObjects.Num();
	if (bSame)
	{
		for (int32 Index = 0; Index < InObjects.Num(); ++Index)
		{
			if (Current.Objects[Index].Get() != InObjects[Index])
			{
				bSame = false;
				break;
			}
		}
	}
	if (bSame)
	{
		Current.SourceTool = InSourceTool;
		return;
	}

	Current.Objects.Reset(InObjects.Num());
	for (UObject* Obj : InObjects)
	{
		Current.Objects.Add(Obj);
	}
	Current.SourceTool = InSourceTool;

	if (bBroadcasting)
	{
		// A subscriber changed the selection while we were broadcasting. State is updated;
		// skip the recursive broadcast and let the in-flight one settle.
		return;
	}

	bBroadcasting = true;
	OnChangedEvent.Broadcast(Current);
	bBroadcasting = false;
}

void FNexusSelectionService::ClearSelection(FName InSourceTool)
{
	SetSelection(static_cast<UObject*>(nullptr), InSourceTool);
}

FDelegateHandle FNexusSelectionService::Subscribe(const FNexusOnSelectionChanged::FDelegate& Delegate)
{
	return OnChangedEvent.Add(Delegate);
}

void FNexusSelectionService::Unsubscribe(FDelegateHandle Handle)
{
	OnChangedEvent.Remove(Handle);
}
