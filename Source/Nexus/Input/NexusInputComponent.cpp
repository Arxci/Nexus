#include "NexusInputComponent.h"

#include "InputAction.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "Nexus/Input/NexusInputManager.h"

void UNexusInputComponent::InitializeBinder(UNexusInputManager* InManager)
{
	Manager = InManager;
	if (!InManager)
	{
		return;
	}

	BindingsChangedHandle = InManager->OnActiveBindingsChanged.AddUObject(this, &UNexusInputComponent::HandleActiveBindingsChanged);
	// Immediate here: setup runs from the host's possession handling, not mid-dispatch.
	RebindFromManager();
}

void UNexusInputComponent::TearDownBinder()
{
	if (UNexusInputManager* M = Manager.Get())
	{
		M->OnActiveBindingsChanged.Remove(BindingsChangedHandle);
	}
	BindingsChangedHandle.Reset();
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(RebindTimerHandle);
	}
	bRebindScheduled = false;
	ClearActionBindings();
	Manager = nullptr;
}

void UNexusInputComponent::HandleActiveBindingsChanged()
{
	// Defer to next tick so a context push/pop fired from inside an input handler doesn't
	// mutate our action bindings while Enhanced Input is iterating them.
	if (bRebindScheduled)
	{
		return;
	}
	if (UWorld* World = GetWorld())
	{
		bRebindScheduled = true;
		World->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &UNexusInputComponent::RebindFromManager));
	}
	else
	{
		RebindFromManager();
	}
}

void UNexusInputComponent::RebindFromManager()
{
	bRebindScheduled = false;

	// This component is dedicated to the input layer, so clearing every action binding is
	// safe and simpler than tracking individual handles.
	ClearActionBindings();

	UNexusInputManager* M = Manager.Get();
	if (!M)
	{
		return;
	}

	// Bind every active action's four trigger phases to the manager, carrying the verb tag as
	// the payload. The manager resolves the binding (style / ability / listeners) by verb and
	// decides what each phase means; this component never knows.
	for (const FNexusBoundActionEntry& Entry : M->GetActiveBoundActions())
	{
		if (!Entry.Action)
		{
			continue;
		}
		BindAction(Entry.Action, ETriggerEvent::Started,   M, &UNexusInputManager::HandleInputStarted,   Entry.Verb);
		BindAction(Entry.Action, ETriggerEvent::Triggered, M, &UNexusInputManager::HandleInputTriggered, Entry.Verb);
		BindAction(Entry.Action, ETriggerEvent::Completed, M, &UNexusInputManager::HandleInputCompleted, Entry.Verb);
		BindAction(Entry.Action, ETriggerEvent::Canceled,  M, &UNexusInputManager::HandleInputCanceled,  Entry.Verb);
	}
}
