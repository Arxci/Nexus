# Input

> A clean intent-based layer over UE Enhanced Input. Decouples gameplay,
> UI, and abilities from raw Input Action bindings, supports a context
> stack for modal modes (Gameplay, Inventory, Examine, Dialog, Cinematic),
> drives HUD glyphs off the last-used device, and persists rebinding
> through Enhanced Input User Settings. RE4R-class target.

## What the system does

- Wraps Enhanced Input so no gameplay code binds to Input Actions directly.
- Resolves a designer-named intent (Input.Intent.Fire, Input.Intent.Reload)
  from raw input on the active context.
- Maintains a context stack — Gameplay at the bottom, Inventory / Examine /
  Dialog / Cinematic pushed on top — that swaps Input Mapping Contexts and
  routes intents to whoever owns them right now.
- Modal contexts block intents below them. Passive overlay contexts let
  them through.
- Gates each intent by gameplay state tags (Character.State.*) so an active
  reload, a stagger, or an in-progress hold can refuse the press without
  the caller writing a check.
- Tracks the last-used device (KB&M / Xbox / PlayStation / generic gamepad)
  and exposes per-action glyph lookups so the HUD prompt swaps the right
  glyph automatically.
- Persists rebindings via UEnhancedInputUserSettings.
- Surfaces a debug overlay listing the active stack, the active IMCs, the
  last fired intent, and the latest gate-block reason.

## How a designer uses it

- Add a new input verb: author an Input Action asset, register it in the
  Input.Intent.* tag list, add it to the relevant Input Context data asset.
- Add a new mode: author a UNexusInputContext data asset listing the
  intents it offers, its IMC, its priority, and whether it's modal or
  overlay. Push it onto the stack from the system that owns the mode.
- Hold vs tap: author the Enhanced Input Hold trigger on the IA. The intent
  carries the hold threshold; the dispatcher emits a Tapped or Held variant.
- Gate an intent: list the blocking-state tags on the intent. The dispatcher
  refuses the press while any blocker is owned.
- Swap a binding at runtime (settings menu): call the rebinding API. It
  writes through to the Enhanced Input User Settings and persists.
- Add gamepad-specific behaviour: author a separate IMC for that device
  and let the context auto-add it when the last-used device matches.

## Concepts

### Intent

A named verb the game cares about. Identified by a gameplay tag under
Input.Intent.* (Input.Intent.Move, Input.Intent.Aim, Input.Intent.Fire,
Input.Intent.Reload, Input.Intent.Melee, Input.Intent.Interact,
Input.Intent.Examine, Input.Intent.QuickTurn, Input.Intent.Sprint,
Input.Intent.Crouch, Input.Intent.QuickHeal, Input.Intent.OpenAttache,
Input.Intent.OpenMap, Input.Intent.Cancel, Input.Intent.Pause).

An intent describes the verb — never the key. The same intent fires from
KB&M and gamepad, in different contexts, on rebinding, without any
listener code changing.

### Intent binding

The link between an intent and an Input Action, carried on a Input Context.
Each binding declares:

- The Input.Intent.* tag.
- The Input Action asset that triggers it.
- The trigger semantic (Pressed, Released, Held, Tapped, Down-with-value).
- The hold threshold for Tapped vs Held.
- The blocker tag query (intent refused while any blocker is owned).
- Optional priority within the context (higher fires first when two intents
  could match the same press).

### Input context

A UNexusInputContext data asset. Carries:

- Context tag (Input.Context.Gameplay, Input.Context.Inventory,
  Input.Context.Examine, Input.Context.Dialog, Input.Context.Cinematic,
  Input.Context.Vehicle).
- Priority — higher contexts sit on top of the stack.
- Modal flag — modal contexts block every intent below them; overlay
  contexts let intents below fire.
- Block tag query — intents below that match this query are blocked even
  if the context is overlay.
- Input Mapping Context reference plus an optional per-device IMC list
  (different KB&M and gamepad layouts).
- The list of intent bindings the context exposes.
- Optional default-cursor mode (Game, GameAndUI, UI).

### Context stack

A UNexusInputSubsystem (LocalPlayer subsystem). Owns the stack. Pushes
and pops contexts, applies the right IMCs to the Enhanced Input subsystem,
walks the stack top-down to resolve each press to an intent, and dispatches
the intent to its listeners.

Push / Pop / Replace are the only mutators. A pushed context is identified
by an opaque handle so the caller can pop only its own context (handles
prevent "pop the wrong thing" bugs when two systems share a context tag).

### Intent dispatcher

The fan-out side. Anything that wants to respond to an intent calls
RegisterIntentListener(IntentTag, Callback) and receives a delegate handle.
Listeners persist across context switches; the dispatcher only fires them
when the active stack actually emits the intent.

A listener gets the intent payload (axis value, trigger phase, hold
duration) plus the originating device. It returns Handled or Unhandled;
Handled stops the dispatch walk for that intent on that frame.

### Glyph driver

Tracks the last device that produced input. Emits OnInputDeviceChanged.
Resolves a Input Action plus the current device into a glyph asset (a
texture / soft reference) the HUD draws.

The glyph driver reads through to Enhanced Input's mapping query so a
rebound key automatically updates its glyph. UI doesn't cache glyphs;
it subscribes to OnInputDeviceChanged and re-queries.

### Rebinding service

Thin wrapper over UEnhancedInputUserSettings. Exposes:

- ListBindableActions(Context) — what the settings screen displays.
- BeginRebind(Action, Slot) — start capturing the next press.
- CommitRebind(Action, Slot, Key) — write through to user settings.
- ResetActionToDefault(Action) — revert one action.
- ResetAllToDefault() — revert everything.
- SaveBindings() / LoadBindings() — explicit persistence (auto-saved
  on commit; explicit calls are for settings-screen flows).

### Input policy

Per-context, per-intent gating rules. Encoded on the intent binding:

- Required state tags (Character.State.OnGround for jump, etc.).
- Forbidden state tags (Character.State.Reloading blocks Fire).
- Required ability ready (intent is forwarded to an ability; if the
  ability can't activate, the policy logs a reason and the press is dropped).
- Hold-cancellation policy — what happens to an in-progress hold when a
  blocker appears (cancel vs ignore vs queue).

### Input host

The minimum-viable hero-side hook. The hero class (or any pawn that owns
local input) holds one component, UNexusInputHostComponent. It:

- Owns the EnhancedInputComponent (UE requires it).
- On possession, registers the pawn with the input subsystem.
- On unpossession, unregisters and pops any pawn-owned contexts.
- Forwards raw events to the subsystem.
- Holds no per-action C++ binding methods. Adding a new input action does
  not touch the hero.

## Lifecycle

1. Player possesses the hero. The InputHostComponent registers with the
   input subsystem.
2. The subsystem pushes the default Gameplay context.
3. Each press walks the stack from the top. The first context whose IMC
   recognises the press resolves it to an intent.
4. The dispatcher checks gate policy. If a blocker is owned, the press is
   refused and a fail reason is recorded for debug.
5. If the press is accepted, the intent is fired to registered listeners
   in priority order until one returns Handled or the list is exhausted.
6. A mode change (open the attaché, enter Examine, start a dialog,
   trigger a cinematic) pushes its context. Lower contexts continue to
   exist; modal contexts block their intents.
7. Mode exit pops the context by handle. The lower context resumes.
8. Player unpossesses or the level changes. The host component
   unregisters; the stack is reset to the configured boot state.

## Survival-horror specifics

- Aim is held. While held, the Aim intent owns Character.State.Aiming;
  Fire's spread tightens because the weapon reads the aiming branch off
  the effective-stat block. Releasing Aim clears the state tag.
- Fire's trigger semantic is data-driven per weapon's fire mode: a
  per-press Tapped for semi and shotgun, a held Down for full-auto with
  the WeaponFire ability honouring its cooldown re-arm.
- Interact uses the existing hold-to-progress model. The Interact intent
  exposes both Press (start the hold) and Hold-threshold-crossed
  (commit the action). The interaction ability hosts the progress timer.
- Examine is its own context. While active it pushes
  Input.Context.Examine on top, suppresses gameplay intents through the
  modal flag, and exposes Look as a re-purposed axis that rotates the
  mesh instead of the camera. Cancel pops the context.
- Quick-turn is a chord intent — Back-on-Move plus Sprint (or its gamepad
  equivalent). The chord lives on the gameplay context as a single
  Input.Intent.QuickTurn binding so the listener doesn't see the chord
  semantics.
- Quick-heal is a single press intent on the gameplay context. The heal
  ability listens; if it can't activate (no consumable in the assigned
  slot) the policy fails the press and the HUD surfaces the reason.
- The attaché toggle pushes Input.Context.Inventory. Inventory navigation
  uses its own bindings (D-pad + grid). Cancel pops the context. The
  weapon-equip context is reused under the attaché.

## Hero refactor (the removal plan)

- The hero's existing raw IA binding callbacks move to listeners on the
  appropriate component or ability:
  - Move, Look → CharacterMovement-side listeners on the gameplay context.
  - Aim, Fire, Reload, Melee → WeaponAim / WeaponFire / WeaponReload /
    WeaponMelee abilities register themselves.
  - Interact → UNexusAbility_Interaction registers itself.
  - Slot activations → UNexusEquipmentComponent listens for the per-slot
    Activate intent.
  - QuickHeal → consumable ability listens.
  - OpenAttache, OpenMap, Pause → owning UI systems push their context on
    press (and pop on close).
- The hero ends up with one component (InputHostComponent) and zero
  SetupPlayerInputComponent / BindAction calls.
- AI-controlled hero instances skip the InputHostComponent and use the
  same ability system through behaviour logic.

## Decoupling contract

- The hero class does not call BindAction or read Input Action values.
- Gameplay components and abilities subscribe to intents, never to raw
  Input Actions.
- UI subscribes to OnInputDeviceChanged and queries the glyph driver.
  No widget polls Enhanced Input directly.
- Rebinding goes through the rebinding service. No system writes
  Enhanced Input User Settings directly.
- Modes own their contexts. The inventory system pushes
  Input.Context.Inventory. The dialog system pushes Input.Context.Dialog.
  Nothing else mutates the stack on their behalf.
- The input subsystem is a LocalPlayer subsystem, never a UObject inside
  a pawn — its lifetime matches the local player, not the possessed actor.

## NPC and AI

Not applicable. NPCs activate abilities directly through their ASC; the
input layer is player-only. The input subsystem is a no-op on AI
controllers; the InputHostComponent simply does not register.

## Save and load

- Rebindings ride UEnhancedInputUserSettings. The user-settings save
  slot is independent of the gameplay save and persists across save
  files (rebinding once is a global preference).
- Context stack state does not persist. On load the boot state is
  re-applied: Gameplay context active, every modal context dismissed.
- An in-progress hold (interact, ceremony) does not persist; resolved as
  cancelled on load.

## UI and HUD hooks

- HUD prompts subscribe to OnInputDeviceChanged and call
  GetGlyphForIntent(IntentTag) each refresh. No widget hard-codes a key.
- The interact prompt reads the focused interactable's verb and gate
  reason (from the interaction system) plus the resolved glyph (from the
  input system). Two systems, one prompt.
- The pause / settings screen drives rebinding through the rebinding
  service. No direct UEnhancedInputUserSettings access from UI.
- A "press any key" splash uses the input subsystem's RawAnyPress event
  rather than polling.

## Debug

- A console command nexus.input.debug toggles an overlay that lists the
  active stack from top to bottom, each context's modal flag, the active
  IMCs, the last fired intent and its trigger phase, the last refused
  intent plus the blocker that refused it, and the current last-used
  device.
- A log channel LogNexusInput emits stack mutations, intent fires, and
  intent refusals at verbose-and-above so a designer can scrub a session
  log to see what the input layer did.

## What's out of scope (v1)

- Couch co-op and split-screen.
- Network input prediction and replication.
- Replay / input recording.
- Steam Deck / touch-screen native bindings (Steam Input pass-through
  works; native touch is deferred).
- Accessibility features like hold-to-toggle conversion, sensitivity
  curves beyond what Enhanced Input modifiers provide, and on-screen
  reader prompts (designed for v2; the architecture leaves the seams in).

## Open questions

- Character switching. If gameplay later allows the player to take over
  a second character (escort segment), does the input subsystem follow
  the new pawn automatically (re-register on possession), or do we want
  an explicit hand-off?
- Cinematic ownership. Does the cinematic system push its own context
  (Input.Context.Cinematic, modal, only Skip + Pause routed) or does
  the player controller flip into a fully blocking mode?
- Multiple modal contexts. Inventory open + an opening dialog — does
  the second modal context stack and the lower one pause, or does the
  first pop first? Default plan: stack. Open for review.
- Intent payloads. Should axis intents carry the raw float every frame
  (per-tick) or only on threshold crossings? Default plan: per-tick for
  Move / Look, threshold for everything else.
- Per-device IMC switching. Auto-swap the IMC when the player switches
  device mid-session, or require an explicit reload? Default plan:
  auto-swap on OnInputDeviceChanged.
- Rebinding scope. Can intents be rebound only at the IA level (engine
  default), or do we allow per-context intent overrides ("Reload" can
  be a different key inside Vehicle context)? Default plan: IA-level
  only for v1; per-context overrides on the open list.
- Whether to route accessibility transforms (toggle-to-hold, sensitivity
  curve overrides) through Enhanced Input modifiers or through our
  policy layer.
