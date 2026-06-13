#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "NexusInputTypes.generated.h"

class UInputAction;


/**
 * How a tagged binding drives gameplay once its verb resolves. The first value is
 * the listener path (Move / Look / Interact / Examine.Rotate — anything that calls
 * UNexusInputManager::RegisterInputHandler); the rest are the declarative fast-path
 * that routes straight to the bespoke ASC with no listener code.
 */
UENUM(BlueprintType)
enum class ENexusInputActivationStyle : uint8
{
	/** No ability routing. Dispatched to RegisterInputHandler callbacks only. */
	Listener      UMETA(DisplayName = "Listener"),
	/** Pressed -> TryActivateAbilityByTag. No deactivate (Reload, Melee). */
	Press         UMETA(DisplayName = "Press"),
	/** Pressed -> activate, Released -> deactivate. Active while held (Fire). */
	HoldActive    UMETA(DisplayName = "Hold (active while held)"),
	/** Pressed flips active state via the loose-tag toggle latch (Aim/Run/Crouch in toggle mode). */
	Toggle        UMETA(DisplayName = "Toggle"),
	/** Hold by default; resolves to Toggle when the per-verb player option says so (Aim/Run/Crouch). */
	HoldOrToggle  UMETA(DisplayName = "Hold or Toggle (per setting)"),
};


/** Per-verb player option for a HoldOrToggle binding, persisted through the rebind facade. */
UENUM(BlueprintType)
enum class ENexusHoldToggleMode : uint8
{
	Hold   UMETA(DisplayName = "Hold"),
	Toggle UMETA(DisplayName = "Toggle"),
};


/** The Enhanced Input trigger phase a verb fired on, surfaced to listeners on the payload. */
UENUM(BlueprintType)
enum class ENexusInputTriggerEvent : uint8
{
	Started   UMETA(DisplayName = "Started"),
	Triggered UMETA(DisplayName = "Triggered"),
	Completed UMETA(DisplayName = "Completed"),
	Canceled  UMETA(DisplayName = "Canceled"),
};


/**
 * One row linking a verb to an Input Action on a context. The unit a designer
 * authors to add input: a tag, the action that triggers it, how it drives gameplay,
 * and — for the common case — the ability to activate. Listener bindings leave the
 * ability tag empty and the owning system subscribes with RegisterInputHandler.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusTaggedInputAction
{
	GENERATED_BODY()

	/** The verb this row defines (Input.*). The vocabulary consumers subscribe to, never the key. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding", meta = (Categories = "Input"))
	FGameplayTag InputTag;

	/** The Enhanced Input action whose triggers produce this verb. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding")
	TObjectPtr<UInputAction> InputAction = nullptr;

	/** How the verb drives gameplay. Listener => RegisterInputHandler; the rest are the declarative ASC fast-path. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding")
	ENexusInputActivationStyle ActivationStyle = ENexusInputActivationStyle::Listener;

	/**
	 * Declarative fast-path: the bespoke-ASC ability activated on press / deactivated
	 * on release. Empty (and Listener style) means the verb is dispatched to listeners.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding",
		meta = (Categories = "Ability", EditCondition = "ActivationStyle != ENexusInputActivationStyle::Listener"))
	FGameplayTag ActivateAbilityTag;

	/**
	 * Toggle / HoldOrToggle only: the loose intent tag the toggle latch consults — the
	 * existing Ability.*.Intent.* handshake (Walk / UnCrouch / Unaim). Reproduces the
	 * hero's HandleToggleAbilityInput with no C++ branch.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding",
		meta = (Categories = "Ability", EditCondition = "ActivationStyle == ENexusInputActivationStyle::Toggle || ActivationStyle == ENexusInputActivationStyle::HoldOrToggle"))
	FGameplayTag ToggleDeactivateIntentTag;

	/**
	 * Optional menu path: open this panel through UNexusUIRequestSubsystem on press.
	 * The opened activatable widget owns the input mode; its activation pushes the
	 * modal Menu context. Independent of ability routing.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding", meta = (Categories = "UI.Panel"))
	FGameplayTag RequestUIPanelTag;

	/**
	 * Optional pass-through tag handed to listeners on the payload — e.g. the equipment
	 * slot an Input.Equipment.Primary row maps to, so the slot->verb mapping stays in data.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding")
	FGameplayTag PayloadTag;

	/** Within a context, higher binds first and wins an Input Action another row also references. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Binding")
	int32 Priority = 0;
};


/**
 * What a listener receives when its verb fires. Carries the trigger phase, the value
 * (as a 2D axis and/or bool), the hold/tap timing the action accumulated, and the
 * binding's pass-through tag. Device-agnostic by design — the same payload shape
 * arrives from KB&M and pad.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusInputActionPayload
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	ENexusInputTriggerEvent TriggerEvent = ENexusInputTriggerEvent::Started;

	/** Axis2D value (Move / Look); a bool/axis1D action reports its magnitude in X. */
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FVector2D AxisValue = FVector2D::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bBoolValue = false;

	/** Seconds the action has been evaluating (Enhanced Input ElapsedTime) — tap vs hold. */
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float ElapsedSeconds = 0.f;

	/** Seconds the action has been in the Triggered phase (Enhanced Input TriggeredTime). */
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	float TriggeredSeconds = 0.f;

	/** The binding's pass-through tag (slot, sub-mode, …); invalid when the row sets none. */
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	FGameplayTag PayloadTag;
};


/**
 * Opaque handle to a pushed context. Push returns one; Pop / Replace take one so a
 * caller only ever pops its own context, never something another system pushed.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusInputContextHandle
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Id = INDEX_NONE;

	bool IsValid() const { return Id != INDEX_NONE; }

	friend bool operator==(const FNexusInputContextHandle& A, const FNexusInputContextHandle& B) { return A.Id == B.Id; }
	friend uint32 GetTypeHash(const FNexusInputContextHandle& H) { return ::GetTypeHash(H.Id); }
};


/** Opaque handle to a registered listener, returned by RegisterInputHandler. */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusInputListenerHandle
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Id = INDEX_NONE;

	bool IsValid() const { return Id != INDEX_NONE; }

	friend bool operator==(const FNexusInputListenerHandle& A, const FNexusInputListenerHandle& B) { return A.Id == B.Id; }
	friend uint32 GetTypeHash(const FNexusInputListenerHandle& H) { return ::GetTypeHash(H.Id); }
};


/**
 * A verb-handler callback. Returns true (Handled) to stop the dispatch walking to
 * lower-priority listeners, false (Unhandled) to let it continue. C++ delegate — the
 * consumers (locomotion component, equipment component, abilities) are native.
 */
DECLARE_DELEGATE_RetVal_OneParam(bool, FNexusInputHandlerSignature, const FNexusInputActionPayload&);


/**
 * One resolved (Input Action -> verb) pair the per-pawn binder binds for the active
 * set. Transient hand-off from the manager to UNexusInputComponent — not a UPROPERTY
 * type, so it carries a raw action pointer that lives only for the rebind call.
 */
struct FNexusBoundActionEntry
{
	TObjectPtr<UInputAction> Action = nullptr;
	FGameplayTag Verb;
};
