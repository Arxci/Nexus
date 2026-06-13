#pragma once

#include "CoreMinimal.h"

#include "Subsystems/LocalPlayerSubsystem.h"

#include "GameplayTagContainer.h"

#include "InputCoreTypes.h"
#include "Styling/SlateBrush.h"

#include "Containers/Ticker.h"

#include "CommonInputBaseTypes.h"

#include "Nexus/Input/NexusInputTypes.h"

#include "NexusInputManager.generated.h"

class APawn;
class APlayerController;
class UInputAction;
class UInputMappingContext;
class UCommonInputSubsystem;
class UEnhancedInputLocalPlayerSubsystem;
class UNexusAbilitySystemComponent;
class UNexusInputContext;
class UNexusInputRebindFacade;
struct FInputActionInstance;
struct FInputActionValue;


/** Broadcast when the last-used input device changes; the HUD re-queries glyphs (native). */
DECLARE_MULTICAST_DELEGATE_OneParam(FNexusOnInputDeviceChanged, ECommonInputType);
/** Blueprint-facing mirror of the same event for UMG widgets. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNexusOnInputDeviceChangedDynamic, ECommonInputType, DeviceType);
/** Broadcast when the applied set changes; the per-pawn binder re-pulls and rebinds. */
DECLARE_MULTICAST_DELEGATE(FNexusOnActiveBindingsChanged);
/** Broadcast on a raw key press while a "press any key" splash is listening. */
DECLARE_MULTICAST_DELEGATE(FNexusOnRawAnyKey);


/**
 * One active entry on the stack: the pushed context plus the opaque handle id it was
 * given. Kept sorted by ascending Priority (Gameplay at the front/bottom). A hard ref
 * on Context keeps a pushed asset (e.g. the loaded Menu context) alive while active.
 */
USTRUCT()
struct FNexusActiveContext
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UNexusInputContext> Context = nullptr;

	int32 HandleId = INDEX_NONE;
};


/**
 * The context-stack brain. A LocalPlayer subsystem — never a member of the pawn — so
 * its lifetime is the local player and a pawn swap can't lose or double-register it.
 *
 * It owns the only stack mutators (Push / Pop / Replace, keyed by opaque handle),
 * applies each active context's Input Mapping Context(s) at the right priority,
 * resolves each raw press to an Input.* verb top-down, runs the input-mode gate, and
 * fans the verb out two ways: a declarative binding drives the bespoke ASC directly
 * (TryActivate/Deactivate by tag); a listener binding fires handlers registered via
 * RegisterInputHandler. Gameplay gating stays on the abilities — this layer only adds
 * mode suppression and records a fail reason for the HUD.
 *
 * Player-only by construction: with no registered local pawn every entry point is a
 * safe no-op, so an AI controller (which never gets a UNexusInputHostComponent) drives
 * the same abilities through behaviour logic without touching this at all.
 */
UCLASS()
class NEXUS_API UNexusInputManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	//~Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~End USubsystem

	/** Resolve the manager for a local player controller (null for AI / remote). */
	static UNexusInputManager* GetForController(const APlayerController* PC);
	/** Resolve the manager for a pawn via its (player) controller (null for AI). */
	static UNexusInputManager* GetForPawn(const APawn* Pawn);
	/** Resolve the manager for any actor via its instigating (player) controller (null for AI). */
	static UNexusInputManager* GetForActor(const AActor* Actor);

public:
	// ── Pawn registration (called by UNexusInputHostComponent) ────────────────────
	/**
	 * The local controller possessed Pawn. Records it as the active pawn, pushes the
	 * pawn's default contexts (Gameplay at the bottom) and applies their IMCs. The
	 * pawn's binder, having subscribed to OnActiveBindingsChanged, rebinds in response.
	 */
	void RegisterInputPawn(APawn* Pawn, const TArray<UNexusInputContext*>& DefaultContexts);

	/** The local controller unpossessed Pawn. Resets the stack to the boot state and clears bindings. */
	void UnregisterInputPawn(APawn* Pawn);

	UFUNCTION(BlueprintPure, Category = "Input")
	APawn* GetActivePawn() const { return ActivePawn.Get(); }

	/** The resolved (action -> verb) list for the applied set. The binder pulls this on notify. */
	const TArray<FNexusBoundActionEntry>& GetActiveBoundActions() const { return ActiveBoundActions; }

	/** Subscribed by the per-pawn binder; broadcast whenever the applied set changes. */
	FNexusOnActiveBindingsChanged OnActiveBindingsChanged;

	// ── Context stack (the only mutators) ─────────────────────────────────────────
	/** Push Context onto the stack and reapply input. Returns an opaque handle to pop with. */
	FNexusInputContextHandle PushContext(UNexusInputContext* Context);
	/** Pop the context this handle owns. No-op (returns false) if it isn't on the stack. */
	bool PopContext(FNexusInputContextHandle Handle);
	/** Swap the context Handle owns for NewContext in place, preserving the handle's identity. */
	FNexusInputContextHandle ReplaceContext(FNexusInputContextHandle Handle, UNexusInputContext* NewContext);

	UFUNCTION(BlueprintPure, Category = "Input")
	bool IsContextActive(FGameplayTag ContextTag) const;

	// ── Listener API (the uncommon case: Move/Look/Interact/Slots/…) ──────────────
	/**
	 * Subscribe Handler to Verb. Returns a handle to unregister with. Scope (optional)
	 * binds the handler to one pawn — it only fires while that pawn is the active pawn,
	 * so a possession swap silently stops a stale pawn's handlers. Higher Priority fires
	 * first; a handler returning Handled stops the walk to lower handlers.
	 */
	FNexusInputListenerHandle RegisterInputHandler(FGameplayTag Verb, FNexusInputHandlerSignature Handler, AActor* Scope = nullptr, int32 Priority = 0);
	void UnregisterInputHandler(FNexusInputListenerHandle Handle);

	// ── Cached per-verb values (the Anim BP getters re-source from here) ───────────
	UFUNCTION(BlueprintPure, Category = "Input")
	FVector2D GetCachedAxis(FGameplayTag Verb) const;
	UFUNCTION(BlueprintPure, Category = "Input")
	bool GetCachedBool(FGameplayTag Verb) const;

	/**
	 * After a save-load, end any active hold-style ability whose verb isn't currently held —
	 * the input layer's half of "in-progress holds don't persist." Replaces the hero's old
	 * per-mode ActorLoaded flush, applied generically to every Hold / HoldOrToggle(Hold) verb
	 * in the active set (Run, Crouch, Aim, …).
	 */
	void ReconcileHoldVerbsAfterLoad();

	// ── Device ────────────────────────────────────────────────────────────────────
	UFUNCTION(BlueprintPure, Category = "Input")
	ECommonInputType GetCurrentInputType() const { return CurrentDevice; }

	/** Native HUD subscription point (re-query glyphs on change). */
	FNexusOnInputDeviceChanged OnInputDeviceChanged;
	/** Blueprint mirror of OnInputDeviceChanged. */
	UPROPERTY(BlueprintAssignable, Category = "Input")
	FNexusOnInputDeviceChangedDynamic OnInputDeviceChangedDynamic;

	// ── Glyph driver (built on UNexusUIUtility + Common Input) ─────────────────────
	/**
	 * The key currently bound to Verb for the live device — resolved through Enhanced Input's
	 * live mapping (so a rebind is reflected for free). Prefers a key matching the current
	 * device family (gamepad vs KB&M). Invalid FKey if unbound.
	 */
	UFUNCTION(BlueprintPure, Category = "Input|Glyph")
	FKey GetKeyForInputTag(FGameplayTag Verb) const;

	/**
	 * The glyph for Verb on the live device — Verb -> Input Action -> bound key ->
	 * UNexusUIUtility::GetIconForFKey (which already calls TryGetInputBrush). The HUD calls
	 * this each refresh and never caches; OnInputDeviceChanged tells it when to refresh.
	 */
	UFUNCTION(BlueprintPure, Category = "Input|Glyph")
	FSlateBrush GetGlyphForInputTag(FGameplayTag Verb) const;

	// ── Rebind facade ──────────────────────────────────────────────────────────────
	/** The single seam to Enhanced Input User Settings; the settings screen talks only to this. */
	UFUNCTION(BlueprintPure, Category = "Input|Rebind")
	UNexusInputRebindFacade* GetRebindFacade() const { return RebindFacade; }

	// ── "Press any key" ─────────────────────────────────────────────────────────────
	/** Event for a "press any key" splash (driven, not polled). */
	FNexusOnRawAnyKey OnRawAnyKey;
	/** Broadcast OnRawAnyKey (a splash screen forwards a raw key press here). */
	void NotifyRawAnyKey();

	// ── Per-verb survival-horror options (persist via UNexusInputUserOptions) ─────────
	/** The effective Hold/Toggle mode for a HoldOrToggle verb (Aim/Run/Crouch). */
	UFUNCTION(BlueprintPure, Category = "Input|Options")
	ENexusHoldToggleMode GetVerbMode(FGameplayTag Verb) const { return ResolveHoldToggleMode(Verb); }

	/** Set and persist the player's Hold/Toggle choice for a verb (settings screen calls this). */
	UFUNCTION(BlueprintCallable, Category = "Input|Options")
	void SetVerbMode(FGameplayTag Verb, ENexusHoldToggleMode Mode);

	/** Whether repeated taps count as a held button for this verb (RE accessibility option). */
	UFUNCTION(BlueprintPure, Category = "Input|Options")
	bool GetRepeatedInputAsHold(FGameplayTag Verb) const;

	UFUNCTION(BlueprintCallable, Category = "Input|Options")
	void SetRepeatedInputAsHold(FGameplayTag Verb, bool bEnabled);

public:
	// ── EI dispatch entry points (bound by UNexusInputComponent; not for direct call) ─
	void HandleInputStarted(const FInputActionInstance& Instance, FGameplayTag Verb);
	void HandleInputTriggered(const FInputActionInstance& Instance, FGameplayTag Verb);
	void HandleInputCompleted(const FInputActionInstance& Instance, FGameplayTag Verb);
	void HandleInputCanceled(const FInputActionInstance& Instance, FGameplayTag Verb);

protected:
	/** The dispatch-table entry for one verb in the currently-applied (unsuppressed) set. */
	struct FNexusResolvedBinding
	{
		FGameplayTag InputTag;
		TWeakObjectPtr<UInputAction> InputAction;
		ENexusInputActivationStyle ActivationStyle = ENexusInputActivationStyle::Listener;
		FGameplayTag ActivateAbilityTag;
		FGameplayTag ToggleDeactivateIntentTag;
		FGameplayTag RequestUIPanelTag;
		FGameplayTag PayloadTag;
		FGameplayTag OwningContextTag;
		int32 OwningContextPriority = 0;
	};

	/** A registered verb handler. */
	struct FNexusInputListener
	{
		int32 HandleId = INDEX_NONE;
		FGameplayTag Verb;
		FNexusInputHandlerSignature Delegate;
		/** True when registered with a pawn scope: the handler only fires while that pawn is active. */
		bool bScoped = false;
		TWeakObjectPtr<AActor> Scope;
		int32 Priority = 0;
	};

protected:
	// Stack mechanics
	int32 IndexOfHandle(int32 HandleId) const;
	void InsertContextSorted(UNexusInputContext* Context, int32 HandleId);

	/** Recompute the applied context set, (re)apply IMCs, rebuild the dispatch table, rebind the pawn, log. */
	void RebuildActiveInput();

	/** The contexts whose input is live: the topmost modal context and everything above it (all if none modal). */
	void GetAppliedContexts(TArray<UNexusInputContext*>& OutApplied) const;

	// Dispatch
	void Dispatch(const FInputActionInstance& Instance, FGameplayTag Verb, ENexusInputTriggerEvent Event);
	bool FireListeners(FGameplayTag Verb, const FNexusInputActionPayload& Payload);

	/** True if Verb is blocked by an active context above its owner (overlay input-mode gate). */
	bool IsVerbSuppressed(FGameplayTag Verb, int32 OwningContextPriority, FGameplayTag& OutSuppressorContext) const;

	// Declarative routing helpers
	UNexusAbilitySystemComponent* GetActiveASC() const;
	void RouteDeclarative(const FNexusResolvedBinding& Binding, ENexusInputTriggerEvent Event);
	void ToggleAbility(UNexusAbilitySystemComponent* ASC, FGameplayTag AbilityTag, FGameplayTag DeactivateIntentTag);
	ENexusHoldToggleMode ResolveHoldToggleMode(FGameplayTag Verb) const;
	void RequestUIPanel(FGameplayTag PanelTag);

	// Device
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
	UCommonInputSubsystem* GetCommonInputSubsystem() const;
	void HandleInputMethodChanged(ECommonInputType NewType);

	// Logging / debug bookkeeping
	void RecordRefusal(FGameplayTag Verb, const FString& Reason);

	/** Per-frame ticker driving the nexus.input.debug overlay; cheap no-op while the cvar is off. */
	bool TickDebugOverlay(float DeltaTime);

	/** Mirror the persisted per-verb options (UNexusInputUserOptions) into the runtime maps. */
	void LoadUserOptions();

protected:
	// Per-verb hold/toggle override store, mirrored from the persisted user options.
	TMap<FGameplayTag, ENexusHoldToggleMode> VerbModeOverrides;

	// Per-verb repeated-input-as-hold option, mirrored from the persisted user options.
	TMap<FGameplayTag, bool> VerbRepeatAsHold;

	UPROPERTY(Transient)
	TArray<FNexusActiveContext> ContextStack;

	UPROPERTY(Transient)
	TWeakObjectPtr<APawn> ActivePawn;

	/** Handle ids of the contexts the active pawn pushed (popped on unregister). */
	TArray<int32> PawnContextHandleIds;

	/** Dispatch table for the applied set, keyed by verb. Rebuilt on every stack change. */
	TMap<FGameplayTag, FNexusResolvedBinding> ActiveBindings;

	/** Flat (action -> verb) list the binder pulls; kept in sync with ActiveBindings. */
	TArray<FNexusBoundActionEntry> ActiveBoundActions;

	/** Verb -> Input Action across the whole current stack (for glyph lookup of inactive verbs). */
	TMap<FGameplayTag, TWeakObjectPtr<UInputAction>> VerbToAction;

	/** IMCs currently added to the Enhanced Input subsystem (removed before the next apply). */
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInputMappingContext>> AppliedMappingContexts;

	TArray<FNexusInputListener> Listeners;

	TMap<FGameplayTag, FVector2D> CachedAxisValues;
	TMap<FGameplayTag, bool> CachedBoolValues;

	int32 NextContextHandleId = 1;
	int32 NextListenerHandleId = 1;

	UPROPERTY(Transient)
	TWeakObjectPtr<UCommonInputSubsystem> CommonInput;

	UPROPERTY(Transient)
	TObjectPtr<UNexusInputRebindFacade> RebindFacade;

	ECommonInputType CurrentDevice = ECommonInputType::MouseAndKeyboard;

	// Debug snapshot (surfaced by the nexus.input.debug overlay).
	FGameplayTag LastFiredVerb;
	ENexusInputTriggerEvent LastFiredEvent = ENexusInputTriggerEvent::Started;
	FGameplayTag LastRefusedVerb;
	FString LastRefusalReason;

	FTSTicker::FDelegateHandle DebugTickerHandle;
};
