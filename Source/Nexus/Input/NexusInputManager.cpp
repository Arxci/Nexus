#include "NexusInputManager.h"

#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "CommonInputSubsystem.h"

#include "Containers/Ticker.h"

#include "Misc/StringBuilder.h"

#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#include "Nexus/Nexus.h"
#include "Nexus/Input/NexusInputConfig.h"
#include "Nexus/Input/NexusInputContext.h"
#include "Nexus/Input/NexusInputRebindFacade.h"
#include "Nexus/Input/NexusInputUserOptions.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/AbilitySystem/NexusAbilitySystemInterface.h"
#include "Nexus/Game/NexusUIRequestSubsystem.h"
#include "Nexus/Util/NexusUIUtility.h"

#if !UE_BUILD_SHIPPING
namespace
{
	TAutoConsoleVariable<int32> CVarNexusInputDebug(
		TEXT("nexus.input.debug"),
		0,
		TEXT("0: off\n1: overlay the active input stack, applied IMCs, last fired/refused verb, and device."),
		ECVF_Cheat);

	const TCHAR* LexTriggerEvent(ENexusInputTriggerEvent Event)
	{
		switch (Event)
		{
		case ENexusInputTriggerEvent::Started:   return TEXT("Started");
		case ENexusInputTriggerEvent::Triggered: return TEXT("Triggered");
		case ENexusInputTriggerEvent::Completed: return TEXT("Completed");
		case ENexusInputTriggerEvent::Canceled:  return TEXT("Canceled");
		default:                                 return TEXT("?");
		}
	}

	const TCHAR* LexDevice(ECommonInputType Device)
	{
		switch (Device)
		{
		case ECommonInputType::MouseAndKeyboard: return TEXT("KB&M");
		case ECommonInputType::Gamepad:          return TEXT("Gamepad");
		case ECommonInputType::Touch:            return TEXT("Touch");
		default:                                 return TEXT("?");
		}
	}
}
#endif // !UE_BUILD_SHIPPING


// ── Subsystem lifecycle ──────────────────────────────────────────────────────────

void UNexusInputManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Best-effort device subscription; the Common Input subsystem may not exist yet during
	// our own Initialize, so it's re-attempted lazily from GetCommonInputSubsystem().
	if (UCommonInputSubsystem* Common = GetCommonInputSubsystem())
	{
		CurrentDevice = Common->GetCurrentInputType();
	}

	RebindFacade = NewObject<UNexusInputRebindFacade>(this);
	RebindFacade->Initialize(GetLocalPlayer<ULocalPlayer>());

	LoadUserOptions();

#if !UE_BUILD_SHIPPING
	DebugTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &UNexusInputManager::TickDebugOverlay));
#endif
}

void UNexusInputManager::Deinitialize()
{
#if !UE_BUILD_SHIPPING
	if (DebugTickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(DebugTickerHandle);
		DebugTickerHandle.Reset();
	}
#endif

	if (UCommonInputSubsystem* Common = CommonInput.Get())
	{
		Common->OnInputMethodChangedNative.RemoveAll(this);
	}

	if (UEnhancedInputLocalPlayerSubsystem* EI = GetEnhancedInputSubsystem())
	{
		for (UInputMappingContext* IMC : AppliedMappingContexts)
		{
			if (IMC)
			{
				EI->RemoveMappingContext(IMC);
			}
		}
	}
	AppliedMappingContexts.Reset();
	ContextStack.Reset();
	ActiveBindings.Reset();
	ActiveBoundActions.Reset();
	Listeners.Reset();

	Super::Deinitialize();
}

UNexusInputManager* UNexusInputManager::GetForController(const APlayerController* PC)
{
	if (!PC)
	{
		return nullptr;
	}
	if (ULocalPlayer* LP = PC->GetLocalPlayer())
	{
		return LP->GetSubsystem<UNexusInputManager>();
	}
	return nullptr;
}

UNexusInputManager* UNexusInputManager::GetForPawn(const APawn* Pawn)
{
	return Pawn ? GetForController(Cast<APlayerController>(Pawn->GetController())) : nullptr;
}

UNexusInputManager* UNexusInputManager::GetForActor(const AActor* Actor)
{
	if (!Actor)
	{
		return nullptr;
	}
	const AController* Controller = nullptr;
	if (const APawn* Pawn = Cast<APawn>(Actor))
	{
		Controller = Pawn->GetController();
	}
	else
	{
		Controller = Actor->GetInstigatorController();
	}
	return GetForController(Cast<APlayerController>(Controller));
}


// ── Pawn registration ────────────────────────────────────────────────────────────

void UNexusInputManager::RegisterInputPawn(APawn* Pawn, const TArray<UNexusInputContext*>& DefaultContexts)
{
	if (!Pawn)
	{
		return;
	}

	// Robust against an out-of-order swap (a new pawn registering before the old one
	// unregistered): drop any contexts the previous pawn pushed before adopting this one.
	for (int32 HandleId : PawnContextHandleIds)
	{
		const int32 Index = IndexOfHandle(HandleId);
		if (Index != INDEX_NONE)
		{
			ContextStack.RemoveAt(Index);
		}
	}
	PawnContextHandleIds.Reset();

	ActivePawn = Pawn;

	// Re-attempt the device subscription now that play has started.
	GetCommonInputSubsystem();

	// Push the pawn's default contexts, then rebuild once.
	for (UNexusInputContext* Context : DefaultContexts)
	{
		if (!Context)
		{
			continue;
		}
		const int32 HandleId = NextContextHandleId++;
		InsertContextSorted(Context, HandleId);
		PawnContextHandleIds.Add(HandleId);
	}

	RebuildActiveInput();

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Registered pawn %s with %d default context(s)."),
		*GetNameSafe(Pawn), DefaultContexts.Num());
#endif
}

void UNexusInputManager::UnregisterInputPawn(APawn* Pawn)
{
	// Only the active pawn's host unregisters; ignore a stale unpossess from a pawn we already replaced.
	if (ActivePawn.Get() != Pawn)
	{
		return;
	}

	// Boot reset: dismiss the entire stack (Gameplay re-pushes on the next possess) and clear caches.
	ContextStack.Reset();
	PawnContextHandleIds.Reset();
	ActivePawn = nullptr;
	CachedAxisValues.Reset();
	CachedBoolValues.Reset();

	RebuildActiveInput();

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Unregistered pawn %s; stack reset to boot state."), *GetNameSafe(Pawn));
#endif
}


// ── Context stack ────────────────────────────────────────────────────────────────

int32 UNexusInputManager::IndexOfHandle(int32 HandleId) const
{
	for (int32 Index = 0; Index < ContextStack.Num(); ++Index)
	{
		if (ContextStack[Index].HandleId == HandleId)
		{
			return Index;
		}
	}
	return INDEX_NONE;
}

void UNexusInputManager::InsertContextSorted(UNexusInputContext* Context, int32 HandleId)
{
	FNexusActiveContext Entry;
	Entry.Context = Context;
	Entry.HandleId = HandleId;

	// Keep ascending by priority (Gameplay at the front). Equal priorities preserve push order.
	int32 InsertAt = ContextStack.Num();
	for (int32 Index = 0; Index < ContextStack.Num(); ++Index)
	{
		if (ContextStack[Index].Context && ContextStack[Index].Context->Priority > Context->Priority)
		{
			InsertAt = Index;
			break;
		}
	}
	ContextStack.Insert(Entry, InsertAt);
}

FNexusInputContextHandle UNexusInputManager::PushContext(UNexusInputContext* Context)
{
	FNexusInputContextHandle Handle;
	if (!Context)
	{
		return Handle;
	}

	Handle.Id = NextContextHandleId++;
	InsertContextSorted(Context, Handle.Id);
	RebuildActiveInput();

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Push context %s (priority %d, %s)."),
		*Context->ContextTag.ToString(), Context->Priority, Context->bModal ? TEXT("modal") : TEXT("overlay"));
#endif
	return Handle;
}

bool UNexusInputManager::PopContext(FNexusInputContextHandle Handle)
{
	if (!Handle.IsValid())
	{
		return false;
	}
	const int32 Index = IndexOfHandle(Handle.Id);
	if (Index == INDEX_NONE)
	{
		return false;
	}

#if !UE_BUILD_SHIPPING
	const FGameplayTag PoppedTag = ContextStack[Index].Context ? ContextStack[Index].Context->ContextTag : FGameplayTag();
#endif
	ContextStack.RemoveAt(Index);
	PawnContextHandleIds.Remove(Handle.Id);
	RebuildActiveInput();

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Pop context %s."), *PoppedTag.ToString());
#endif
	return true;
}

FNexusInputContextHandle UNexusInputManager::ReplaceContext(FNexusInputContextHandle Handle, UNexusInputContext* NewContext)
{
	if (!Handle.IsValid())
	{
		return PushContext(NewContext);
	}
	const int32 Index = IndexOfHandle(Handle.Id);
	if (Index == INDEX_NONE)
	{
		return PushContext(NewContext);
	}
	if (!NewContext)
	{
		PopContext(Handle);
		return FNexusInputContextHandle();
	}

	// Re-insert under the same handle id so the caller's handle keeps owning it, in case
	// the new context's priority changes its place in the stack.
	ContextStack.RemoveAt(Index);
	InsertContextSorted(NewContext, Handle.Id);
	RebuildActiveInput();
	return Handle;
}

bool UNexusInputManager::IsContextActive(FGameplayTag ContextTag) const
{
	for (const FNexusActiveContext& Active : ContextStack)
	{
		if (Active.Context && Active.Context->ContextTag.MatchesTagExact(ContextTag))
		{
			return true;
		}
	}
	return false;
}


// ── Applied-set computation + rebuild ─────────────────────────────────────────────

void UNexusInputManager::GetAppliedContexts(TArray<UNexusInputContext*>& OutApplied) const
{
	OutApplied.Reset();

	// The topmost modal context (highest priority modal) and everything at or above it is
	// live; everything strictly below is suppressed (its IMC is removed entirely).
	bool bHasModal = false;
	int32 TopModalPriority = TNumericLimits<int32>::Lowest();
	for (const FNexusActiveContext& Active : ContextStack)
	{
		if (Active.Context && Active.Context->bModal)
		{
			bHasModal = true;
			TopModalPriority = FMath::Max(TopModalPriority, Active.Context->Priority);
		}
	}

	for (const FNexusActiveContext& Active : ContextStack)
	{
		if (!Active.Context)
		{
			continue;
		}
		if (!bHasModal || Active.Context->Priority >= TopModalPriority)
		{
			OutApplied.Add(Active.Context);
		}
	}

	// Highest priority first so it claims a verb / action a lower context also references.
	OutApplied.Sort([](const UNexusInputContext& A, const UNexusInputContext& B)
	{
		return A.Priority > B.Priority;
	});
}

void UNexusInputManager::RebuildActiveInput()
{
	UEnhancedInputLocalPlayerSubsystem* EI = GetEnhancedInputSubsystem();

	// 1. Remove the previously applied IMCs.
	if (EI)
	{
		for (UInputMappingContext* IMC : AppliedMappingContexts)
		{
			if (IMC)
			{
				EI->RemoveMappingContext(IMC);
			}
		}
	}
	AppliedMappingContexts.Reset();

	// 2. Rebuild the whole-stack verb -> action map for glyph lookups (even suppressed verbs
	//    keep a glyph). Lower-priority duplicates are ignored.
	VerbToAction.Reset();
	TArray<FNexusTaggedInputAction> Gathered;
	for (const FNexusActiveContext& Active : ContextStack)
	{
		if (!Active.Context)
		{
			continue;
		}
		Active.Context->GatherBindings(Gathered);
		for (const FNexusTaggedInputAction& Binding : Gathered)
		{
			if (Binding.InputTag.IsValid() && Binding.InputAction && !VerbToAction.Contains(Binding.InputTag))
			{
				VerbToAction.Add(Binding.InputTag, Binding.InputAction);
			}
		}
	}

	// 3. Apply IMCs for the live set and build the dispatch table.
	TArray<UNexusInputContext*> Applied;
	GetAppliedContexts(Applied);

	ActiveBindings.Reset();
	ActiveBoundActions.Reset();
	TSet<TObjectPtr<UInputAction>> ClaimedActions;

	for (UNexusInputContext* Context : Applied)
	{
		if (EI)
		{
			if (UInputMappingContext* IMC = Context->ResolveMappingContext(CurrentDevice))
			{
				EI->AddMappingContext(IMC, Context->Priority);
				AppliedMappingContexts.Add(IMC);
			}
		}

		Context->GatherBindings(Gathered);
		for (const FNexusTaggedInputAction& Binding : Gathered)
		{
			if (!Binding.InputTag.IsValid() || !Binding.InputAction)
			{
				continue;
			}
			if (ActiveBindings.Contains(Binding.InputTag) || ClaimedActions.Contains(Binding.InputAction))
			{
				continue; // a higher-priority context already owns this verb / action
			}

			FNexusResolvedBinding Resolved;
			Resolved.InputTag = Binding.InputTag;
			Resolved.InputAction = Binding.InputAction;
			Resolved.ActivationStyle = Binding.ActivationStyle;
			Resolved.ActivateAbilityTag = Binding.ActivateAbilityTag;
			Resolved.ToggleDeactivateIntentTag = Binding.ToggleDeactivateIntentTag;
			Resolved.RequestUIPanelTag = Binding.RequestUIPanelTag;
			Resolved.PayloadTag = Binding.PayloadTag;
			Resolved.OwningContextTag = Context->ContextTag;
			Resolved.OwningContextPriority = Context->Priority;

			ActiveBindings.Add(Binding.InputTag, Resolved);
			ClaimedActions.Add(Binding.InputAction);

			FNexusBoundActionEntry Entry;
			Entry.Action = Binding.InputAction;
			Entry.Verb = Binding.InputTag;
			ActiveBoundActions.Add(Entry);
		}
	}

	// 4. The pawn's binder re-pulls and rebinds.
	OnActiveBindingsChanged.Broadcast();

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Rebuilt: %d active context(s), %d applied IMC(s), %d verb(s)."),
		ContextStack.Num(), AppliedMappingContexts.Num(), ActiveBindings.Num());
#endif
}


// ── Dispatch ─────────────────────────────────────────────────────────────────────

void UNexusInputManager::HandleInputStarted(const FInputActionInstance& Instance, FGameplayTag Verb)
{
	Dispatch(Instance, Verb, ENexusInputTriggerEvent::Started);
}

void UNexusInputManager::HandleInputTriggered(const FInputActionInstance& Instance, FGameplayTag Verb)
{
	Dispatch(Instance, Verb, ENexusInputTriggerEvent::Triggered);
}

void UNexusInputManager::HandleInputCompleted(const FInputActionInstance& Instance, FGameplayTag Verb)
{
	Dispatch(Instance, Verb, ENexusInputTriggerEvent::Completed);
}

void UNexusInputManager::HandleInputCanceled(const FInputActionInstance& Instance, FGameplayTag Verb)
{
	Dispatch(Instance, Verb, ENexusInputTriggerEvent::Canceled);
}

void UNexusInputManager::Dispatch(const FInputActionInstance& Instance, FGameplayTag Verb, ENexusInputTriggerEvent Event)
{
	const FInputActionValue Value = Instance.GetValue();

	// Keep the per-verb cache live for the Anim BP getters. A release zeroes it so a poller
	// reads "no input", matching how GetBoundActionValue read 0 once an action stopped triggering.
	const bool bReleased = (Event == ENexusInputTriggerEvent::Completed || Event == ENexusInputTriggerEvent::Canceled);
	CachedAxisValues.Add(Verb, bReleased ? FVector2D::ZeroVector : Value.Get<FVector2D>());
	CachedBoolValues.Add(Verb, bReleased ? false : Value.Get<bool>());

	const FNexusResolvedBinding* Binding = ActiveBindings.Find(Verb);
	if (!Binding)
	{
		return; // only verbs in the applied set are bound, so this should not normally hit
	}

	// Input-mode gate: an overlay context above this verb's owner can suppress it (a modal
	// context above already removed this binding from the applied set entirely).
	FGameplayTag Suppressor;
	if (IsVerbSuppressed(Verb, Binding->OwningContextPriority, Suppressor))
	{
		if (Event == ENexusInputTriggerEvent::Started)
		{
			RecordRefusal(Verb, FString::Printf(TEXT("input-mode: suppressed by %s"), *Suppressor.ToString()));
		}
		return;
	}

	LastFiredVerb = Verb;
	LastFiredEvent = Event;

	if (Binding->ActivationStyle == ENexusInputActivationStyle::Listener)
	{
		FNexusInputActionPayload Payload;
		Payload.InputTag = Verb;
		Payload.TriggerEvent = Event;
		Payload.AxisValue = Value.Get<FVector2D>();
		Payload.bBoolValue = Value.Get<bool>();
		Payload.ElapsedSeconds = Instance.GetElapsedTime();
		Payload.TriggeredSeconds = Instance.GetTriggeredTime();
		Payload.PayloadTag = Binding->PayloadTag;
		FireListeners(Verb, Payload);
	}
	else
	{
		RouteDeclarative(*Binding, Event);
	}
}

bool UNexusInputManager::FireListeners(FGameplayTag Verb, const FNexusInputActionPayload& Payload)
{
	APawn* Active = ActivePawn.Get();

	// Snapshot the matching handle ids in priority order, then re-find each before firing: a
	// handler is free to register/unregister handlers (even destroy its own owner) during its
	// call, so we never hold a pointer into Listeners across an Execute.
	struct FMatch { int32 HandleId; int32 Priority; };
	TArray<FMatch, TInlineAllocator<4>> Matches;
	for (const FNexusInputListener& Listener : Listeners)
	{
		if (Listener.Verb == Verb)
		{
			Matches.Add({ Listener.HandleId, Listener.Priority });
		}
	}
	Matches.Sort([](const FMatch& A, const FMatch& B) { return A.Priority > B.Priority; });

	bool bHandled = false;
	int32 Fired = 0;
	for (const FMatch& Match : Matches)
	{
		const FNexusInputListener* Listener = Listeners.FindByPredicate(
			[&](const FNexusInputListener& L) { return L.HandleId == Match.HandleId; });
		if (!Listener || !Listener->Delegate.IsBound())
		{
			continue; // unregistered by an earlier handler this dispatch
		}
		// A scoped handler only fires while its pawn is the active pawn (a pawn swap silently
		// stops a stale pawn's handlers); an unscoped handler is player-global.
		if (Listener->bScoped && Listener->Scope.Get() != Active)
		{
			continue;
		}
		if (const UObject* BoundObject = Listener->Delegate.GetUObject())
		{
			if (!IsValid(BoundObject))
			{
				continue; // owner destroyed since registration
			}
		}

		++Fired;
		if (Listener->Delegate.Execute(Payload))
		{
			bHandled = true;
			break;
		}
	}

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, VeryVerbose, TEXT("[Input] Verb %s (%d) -> %d listener(s), handled=%d."),
		*Verb.ToString(), static_cast<int32>(Payload.TriggerEvent), Fired, bHandled ? 1 : 0);
#endif
	return bHandled;
}

bool UNexusInputManager::IsVerbSuppressed(FGameplayTag Verb, int32 OwningContextPriority, FGameplayTag& OutSuppressorContext) const
{
	for (const FNexusActiveContext& Active : ContextStack)
	{
		const UNexusInputContext* Context = Active.Context;
		if (!Context || Context->Priority <= OwningContextPriority)
		{
			continue; // only contexts strictly above the verb's owner can suppress it
		}
		// A modal context blocks everything below it; an overlay blocks only its listed verbs.
		// Checking modal here (not just relying on the suspended IMC) also closes the one-frame
		// window between a context being pushed mid-dispatch and the deferred binder rebind.
		if (Context->bModal || Context->SuppressedVerbsBelow.HasTag(Verb))
		{
			OutSuppressorContext = Context->ContextTag;
			return true;
		}
	}
	return false;
}


// ── Declarative routing ──────────────────────────────────────────────────────────

UNexusAbilitySystemComponent* UNexusInputManager::GetActiveASC() const
{
	if (APawn* Pawn = ActivePawn.Get())
	{
		if (INexusAbilitySystemInterface* AbilityInterface = Cast<INexusAbilitySystemInterface>(Pawn))
		{
			return AbilityInterface->GetNexusAbilitySystemComponent();
		}
	}
	return nullptr;
}

void UNexusInputManager::RouteDeclarative(const FNexusResolvedBinding& Binding, ENexusInputTriggerEvent Event)
{
	const bool bPressed = (Event == ENexusInputTriggerEvent::Started);
	const bool bReleased = (Event == ENexusInputTriggerEvent::Completed || Event == ENexusInputTriggerEvent::Canceled);

	// The menu path is independent of ability routing: open the panel on press; the opened
	// activatable widget owns the input mode (no SetInputMode here).
	if (Binding.RequestUIPanelTag.IsValid() && bPressed)
	{
		RequestUIPanel(Binding.RequestUIPanelTag);
	}

	if (!Binding.ActivateAbilityTag.IsValid())
	{
		return; // panel-only binding
	}

	UNexusAbilitySystemComponent* ASC = GetActiveASC();
	if (!ASC)
	{
		if (bPressed)
		{
			RecordRefusal(Binding.InputTag, TEXT("no ability system on the active pawn"));
		}
		return;
	}

	auto TryActivate = [&]()
	{
		// The ability owns the gameplay gate (ammo / cooldown / reloading); we forward the
		// press and record the refusal for the HUD if it declines.
		if (!ASC->TryActivateAbilityByTag(Binding.ActivateAbilityTag))
		{
			RecordRefusal(Binding.InputTag, FString::Printf(TEXT("ability %s refused (gameplay gate)"), *Binding.ActivateAbilityTag.ToString()));
		}
	};

	switch (Binding.ActivationStyle)
	{
	case ENexusInputActivationStyle::Press:
		if (bPressed)
		{
			TryActivate();
		}
		break;

	case ENexusInputActivationStyle::HoldActive:
		if (bPressed)
		{
			TryActivate();
		}
		else if (bReleased)
		{
			ASC->TryDeactivateAbilityByTag(Binding.ActivateAbilityTag);
		}
		break;

	case ENexusInputActivationStyle::Toggle:
		if (bPressed)
		{
			ToggleAbility(ASC, Binding.ActivateAbilityTag, Binding.ToggleDeactivateIntentTag);
		}
		break;

	case ENexusInputActivationStyle::HoldOrToggle:
		if (ResolveHoldToggleMode(Binding.InputTag) == ENexusHoldToggleMode::Toggle)
		{
			if (bPressed)
			{
				ToggleAbility(ASC, Binding.ActivateAbilityTag, Binding.ToggleDeactivateIntentTag);
			}
		}
		else // Hold
		{
			if (bPressed)
			{
				TryActivate();
			}
			else if (bReleased)
			{
				ASC->TryDeactivateAbilityByTag(Binding.ActivateAbilityTag);
			}
		}
		break;

	default:
		break;
	}
}

void UNexusInputManager::ToggleAbility(UNexusAbilitySystemComponent* ASC, FGameplayTag AbilityTag, FGameplayTag DeactivateIntentTag)
{
	// Verbatim port of the hero's HandleToggleAbilityInput, preserving the existing
	// Ability.*.Intent.* loose-tag handshake (Walk / UnCrouch / Unaim).
	if (DeactivateIntentTag.IsValid() && ASC->HasTag(DeactivateIntentTag))
	{
		ASC->RemoveLooseGameplayTag(DeactivateIntentTag);
	}
	else if (ASC->IsAbilityActiveByTag(AbilityTag))
	{
		ASC->TryDeactivateAbilityByTag(AbilityTag);
	}
	else
	{
		ASC->TryActivateAbilityByTag(AbilityTag);
	}
}

ENexusHoldToggleMode UNexusInputManager::ResolveHoldToggleMode(FGameplayTag Verb) const
{
	if (const ENexusHoldToggleMode* Override = VerbModeOverrides.Find(Verb))
	{
		return *Override;
	}
	return ENexusHoldToggleMode::Hold; // binding default when the player hasn't overridden it
}

void UNexusInputManager::LoadUserOptions()
{
	VerbModeOverrides.Reset();
	VerbRepeatAsHold.Reset();

	const UNexusInputUserOptions* Options = UNexusInputUserOptions::Get();
	if (!Options)
	{
		return;
	}
	for (const TPair<FName, uint8>& Pair : Options->VerbHoldToggleModes)
	{
		const FGameplayTag Verb = FGameplayTag::RequestGameplayTag(Pair.Key, /*ErrorIfNotFound*/ false);
		if (Verb.IsValid())
		{
			VerbModeOverrides.Add(Verb, static_cast<ENexusHoldToggleMode>(Pair.Value));
		}
	}
	for (const TPair<FName, bool>& Pair : Options->VerbRepeatedAsHold)
	{
		const FGameplayTag Verb = FGameplayTag::RequestGameplayTag(Pair.Key, false);
		if (Verb.IsValid())
		{
			VerbRepeatAsHold.Add(Verb, Pair.Value);
		}
	}
}

void UNexusInputManager::SetVerbMode(FGameplayTag Verb, ENexusHoldToggleMode Mode)
{
	if (!Verb.IsValid())
	{
		return;
	}
	VerbModeOverrides.Add(Verb, Mode);

	if (UNexusInputUserOptions* Options = UNexusInputUserOptions::Get())
	{
		Options->VerbHoldToggleModes.Add(Verb.GetTagName(), static_cast<uint8>(Mode));
		Options->SaveConfig();
	}
}

bool UNexusInputManager::GetRepeatedInputAsHold(FGameplayTag Verb) const
{
	return VerbRepeatAsHold.FindRef(Verb);
}

void UNexusInputManager::SetRepeatedInputAsHold(FGameplayTag Verb, bool bEnabled)
{
	if (!Verb.IsValid())
	{
		return;
	}
	VerbRepeatAsHold.Add(Verb, bEnabled);

	if (UNexusInputUserOptions* Options = UNexusInputUserOptions::Get())
	{
		Options->VerbRepeatedAsHold.Add(Verb.GetTagName(), bEnabled);
		Options->SaveConfig();
	}
}

void UNexusInputManager::RequestUIPanel(FGameplayTag PanelTag)
{
	UObject* WorldContext = ActivePawn.IsValid() ? static_cast<UObject*>(ActivePawn.Get()) : static_cast<UObject*>(GetLocalPlayer<ULocalPlayer>());
	if (UNexusUIRequestSubsystem* UI = UNexusUIRequestSubsystem::Get(WorldContext))
	{
		UI->RequestPanel(PanelTag, ActivePawn.Get());
	}
}


// ── Cached values ────────────────────────────────────────────────────────────────

void UNexusInputManager::ReconcileHoldVerbsAfterLoad()
{
	UNexusAbilitySystemComponent* ASC = GetActiveASC();
	if (!ASC)
	{
		return;
	}

	for (const TPair<FGameplayTag, FNexusResolvedBinding>& Pair : ActiveBindings)
	{
		const FNexusResolvedBinding& Binding = Pair.Value;
		if (!Binding.ActivateAbilityTag.IsValid())
		{
			continue;
		}

		// Only verbs that are "active while held": HoldActive always, HoldOrToggle when the
		// player's option resolves to Hold. A Toggle verb legitimately persists across a load.
		const bool bHoldStyle =
			Binding.ActivationStyle == ENexusInputActivationStyle::HoldActive ||
			(Binding.ActivationStyle == ENexusInputActivationStyle::HoldOrToggle &&
			 ResolveHoldToggleMode(Binding.InputTag) == ENexusHoldToggleMode::Hold);
		if (!bHoldStyle)
		{
			continue;
		}

		// Restored active but the player isn't holding the key now -> end it (matches the abilities'
		// own load reconciliation; CachedBoolValues is empty right after load, so this reads false).
		if (ASC->IsAbilityActiveByTag(Binding.ActivateAbilityTag) && !GetCachedBool(Binding.InputTag))
		{
			ASC->TryDeactivateAbilityByTag(Binding.ActivateAbilityTag);
		}
	}
}

FVector2D UNexusInputManager::GetCachedAxis(FGameplayTag Verb) const
{
	return CachedAxisValues.FindRef(Verb);
}

bool UNexusInputManager::GetCachedBool(FGameplayTag Verb) const
{
	return CachedBoolValues.FindRef(Verb);
}


// ── Listeners ────────────────────────────────────────────────────────────────────

FNexusInputListenerHandle UNexusInputManager::RegisterInputHandler(FGameplayTag Verb, FNexusInputHandlerSignature Handler, AActor* Scope, int32 Priority)
{
	FNexusInputListenerHandle Handle;
	if (!Verb.IsValid() || !Handler.IsBound())
	{
		return Handle;
	}

	FNexusInputListener Listener;
	Listener.HandleId = NextListenerHandleId++;
	Listener.Verb = Verb;
	Listener.Delegate = MoveTemp(Handler);
	Listener.Priority = Priority;
	Listener.bScoped = (Scope != nullptr);
	Listener.Scope = Scope;
	Listeners.Add(MoveTemp(Listener));

	Handle.Id = Listener.HandleId;
	return Handle;
}

void UNexusInputManager::UnregisterInputHandler(FNexusInputListenerHandle Handle)
{
	if (!Handle.IsValid())
	{
		return;
	}
	Listeners.RemoveAll([&](const FNexusInputListener& Listener) { return Listener.HandleId == Handle.Id; });
}


// ── Device ───────────────────────────────────────────────────────────────────────

UEnhancedInputLocalPlayerSubsystem* UNexusInputManager::GetEnhancedInputSubsystem() const
{
	if (const ULocalPlayer* LP = GetLocalPlayer<ULocalPlayer>())
	{
		return LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	}
	return nullptr;
}

UCommonInputSubsystem* UNexusInputManager::GetCommonInputSubsystem() const
{
	UNexusInputManager* MutableThis = const_cast<UNexusInputManager*>(this);
	if (UCommonInputSubsystem* Cached = MutableThis->CommonInput.Get())
	{
		return Cached;
	}
	if (const ULocalPlayer* LP = GetLocalPlayer<ULocalPlayer>())
	{
		if (UCommonInputSubsystem* Common = LP->GetSubsystem<UCommonInputSubsystem>())
		{
			MutableThis->CommonInput = Common;
			// Subscribe once. The auto-swap of per-device IMCs + the HUD glyph refresh both ride this.
			Common->OnInputMethodChangedNative.AddUObject(MutableThis, &UNexusInputManager::HandleInputMethodChanged);
			MutableThis->CurrentDevice = Common->GetCurrentInputType();
			return Common;
		}
	}
	return nullptr;
}

void UNexusInputManager::HandleInputMethodChanged(ECommonInputType NewType)
{
	if (NewType == CurrentDevice)
	{
		return;
	}
	CurrentDevice = NewType;

	// Swap any per-device IMCs and refresh glyph subscribers.
	RebuildActiveInput();
	OnInputDeviceChanged.Broadcast(NewType);
	OnInputDeviceChangedDynamic.Broadcast(NewType);

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Device changed to %d."), static_cast<int32>(NewType));
#endif
}


// ── Glyph driver ─────────────────────────────────────────────────────────────────

FKey UNexusInputManager::GetKeyForInputTag(FGameplayTag Verb) const
{
	const TWeakObjectPtr<UInputAction>* Found = VerbToAction.Find(Verb);
	UInputAction* Action = Found ? Found->Get() : nullptr;
	if (!Action)
	{
		return FKey();
	}

	UEnhancedInputLocalPlayerSubsystem* EI = GetEnhancedInputSubsystem();
	if (!EI)
	{
		return FKey();
	}

	// Live mapping query: reflects applied IMCs + any user rebind, so the glyph follows a
	// rebind with no widget change.
	const TArray<FKey> Keys = EI->QueryKeysMappedToAction(Action);
	if (Keys.Num() == 0)
	{
		return FKey();
	}

	// Prefer a key matching the current device family (gamepad vs KB&M).
	const bool bWantGamepad = (CurrentDevice == ECommonInputType::Gamepad);
	for (const FKey& Key : Keys)
	{
		if (Key.IsGamepadKey() == bWantGamepad)
		{
			return Key;
		}
	}
	return Keys[0];
}

FSlateBrush UNexusInputManager::GetGlyphForInputTag(FGameplayTag Verb) const
{
	const FKey Key = GetKeyForInputTag(Verb);
	if (!Key.IsValid())
	{
		return FSlateBrush();
	}

	// Resolve the brush through the project's existing icon resolver (which calls Common
	// Input's TryGetInputBrush) — one icon set, no second source of truth.
	const ULocalPlayer* LP = GetLocalPlayer<ULocalPlayer>();
	UObject* WorldContext = LP ? static_cast<UObject*>(LP->GetPlayerController(LP->GetWorld())) : nullptr;
	if (!WorldContext)
	{
		WorldContext = const_cast<ULocalPlayer*>(LP);
	}
	return UNexusUIUtility::GetIconForFKey(WorldContext, Key);
}

void UNexusInputManager::NotifyRawAnyKey()
{
	OnRawAnyKey.Broadcast();
}


// ── Logging ──────────────────────────────────────────────────────────────────────

void UNexusInputManager::RecordRefusal(FGameplayTag Verb, const FString& Reason)
{
	LastRefusedVerb = Verb;
	LastRefusalReason = Reason;

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Refused %s: %s"), *Verb.ToString(), *Reason);
#endif
}

bool UNexusInputManager::TickDebugOverlay(float /*DeltaTime*/)
{
#if !UE_BUILD_SHIPPING
	// Keep ticking regardless; the work below only runs while the cvar is on and this manager
	// owns the active pawn (so split managers don't double-draw).
	if (CVarNexusInputDebug.GetValueOnGameThread() != 0 && GEngine && ActivePawn.IsValid())
	{
		TStringBuilder<1024> Builder;
		Builder.Appendf(TEXT("[nexus.input]  device=%s  pawn=%s\n"), LexDevice(CurrentDevice), *GetNameSafe(ActivePawn.Get()));

		// Stack top (highest priority) -> bottom, with modal flag and applied marker.
		bool bHasModal = false;
		int32 TopModalPriority = TNumericLimits<int32>::Lowest();
		for (const FNexusActiveContext& Active : ContextStack)
		{
			if (Active.Context && Active.Context->bModal)
			{
				bHasModal = true;
				TopModalPriority = FMath::Max(TopModalPriority, Active.Context->Priority);
			}
		}
		Builder.Append(TEXT("stack (top->bottom):\n"));
		for (int32 Index = ContextStack.Num() - 1; Index >= 0; --Index)
		{
			const UNexusInputContext* Context = ContextStack[Index].Context;
			if (!Context)
			{
				continue;
			}
			const bool bApplied = !bHasModal || Context->Priority >= TopModalPriority;
			Builder.Appendf(TEXT("  %s  p%d  %s  %s\n"),
				*Context->ContextTag.ToString(), Context->Priority,
				Context->bModal ? TEXT("[modal]") : TEXT("[overlay]"),
				bApplied ? TEXT("(applied)") : TEXT("(suspended)"));
		}

		Builder.Appendf(TEXT("applied IMCs: %d   active verbs: %d\n"), AppliedMappingContexts.Num(), ActiveBindings.Num());
		Builder.Appendf(TEXT("last fired: %s (%s)\n"),
			LastFiredVerb.IsValid() ? *LastFiredVerb.ToString() : TEXT("-"), LexTriggerEvent(LastFiredEvent));
		Builder.Appendf(TEXT("last refused: %s%s%s"),
			LastRefusedVerb.IsValid() ? *LastRefusedVerb.ToString() : TEXT("-"),
			LastRefusalReason.IsEmpty() ? TEXT("") : TEXT(" — "),
			*LastRefusalReason);

		// Stable key so the overlay refreshes in place; short lifetime refreshed each tick.
		GEngine->AddOnScreenDebugMessage(
			static_cast<uint64>(GetUniqueID()), 1.1f, FColor::Cyan, Builder.ToString());
	}
#endif // !UE_BUILD_SHIPPING
	return true; // keep ticking
}
