# Input

> A data-driven intent layer over UE Enhanced Input and Common UI. Verbs are
> gameplay tags, not keys; a context stack swaps modal modes (Gameplay,
> Examine, Menu, Dialog, Cinematic); the bespoke ASC, equipment, and UI
> systems subscribe to verbs instead of binding raw actions; HUD glyphs
> follow the last-used device; rebinds persist through Enhanced Input User
> Settings. The hero ends with zero `BindAction` calls. First-person
> survival-horror target (RE7 / Village class).

## What the system does

- Wraps Enhanced Input so no gameplay class binds an Input Action directly.
- Resolves a designer-named verb — an **Input Tag** (`Input.Weapon.Fire`,
  `Input.Interact`, reusing the project's existing `Input.*` tags) — from raw
  input on whichever context is active.
- Maintains a **context stack** — Gameplay at the bottom, Examine / Menu /
  Dialog / Cinematic / Vehicle pushed on top — that swaps Input Mapping
  Contexts and decides who owns each verb right now.
- Routes the common case declaratively: a binding can say "this verb activates
  `Ability.Weapon.Fire`" and the layer drives the bespoke ASC with no listener
  code. The uncommon case (Move, Look, hold-to-interact progress) uses a thin
  listener API.
- Folds **hold vs toggle**, **tap vs hold**, and **repeated-input-as-hold**
  into per-verb data + a user setting, replacing the inline `EInputMode`
  branches scattered through the hero today.
- Defers gameplay gating to the abilities that already own it
  (`ActivationRequiredTags` / `ActivationBlockedTags` / `CanActivateAbility`);
  the input layer adds only **mode suppression** (e.g. Examine eats combat
  verbs) and records a fail reason for the HUD.
- Hands **full-screen UI input** to Common UI's action router instead of
  fighting it: opening a menu pushes a Menu context that suspends gameplay
  IMCs, and the activatable widget owns the input mode through
  `GetDesiredInputConfig`.
- Tracks the last-used device (KB&M / Xbox / PlayStation / generic pad) and
  resolves a per-verb glyph by building on the project's existing
  `UNexusUIUtility::GetIconForFKey` + `UCommonInputSubsystem`.
- Persists rebindings via `UEnhancedInputUserSettings`.
- Surfaces a debug overlay and a verbose log channel for the active stack,
  the active IMCs, the last fired verb, and the last refused verb + reason.

## Prior art (what AAA / Epic samples do)

The plan is deliberately close to **Lyra**, Epic's reference project, adapted
to this codebase's bespoke ability system instead of GAS:

- **Lyra `ULyraInputConfig`** maps `InputTag` → `InputAction`, split into
  *native* actions (Move, Look — bound to typed handlers) and *ability*
  actions (routed generically by tag). A custom `UEnhancedInputComponent`
  subclass binds them all from the config; `Started → Pressed`,
  `Completed/Canceled → Released`. This layer mirrors that split.
- **Lyra IMCs** are added via a Game Feature action
  (`UGameFeatureAction_AddInputContextMapping`); we use an explicit
  push/pop stack instead (no Game Features in this project), but the
  "context = IMC + tagged bindings" shape is the same.
- **Common UI** routes UI input through `UCommonUIActionRouterBase` and the
  activatable-widget tree; each activatable widget declares an
  `FUIInputConfig` (`ECommonInputMode::Game` / `Menu` / `All`, mouse capture,
  cursor) via `GetDesiredInputConfig`. `SetInputMode` is illegal under
  Common UI — the widget is the source of truth for menu input mode.
- **Common Input** (`UCommonInputSubsystem::GetCurrentInputType`,
  `OnInputMethodChangedNative`, `UCommonInputPlatformSettings::TryGetInputBrush`)
  is the device + glyph backbone; the project already calls it from
  `NexusUIUtility`.
- **Enhanced Input User Settings** (UE 5.3+) own rebinding: register an IMC,
  mark mappings player-mappable, capture and persist a key — no hand-rolled
  save slot.
- **Survival-horror conventions** (RE7 / Village): per-verb hold-or-
  toggle for Aim / Run / Crouch, repeated-input-as-hold to avoid mashing,
  contextual hold-to-interact, weapon slot shortcuts, and a paused inventory
  screen — all expressed as data here.

## Layers

```
0  Engine          Enhanced Input (IA/IMC/triggers/modifiers, User Settings)
                   Common UI (action router, activatable widgets)
                   Common Input (device type + glyph data)
        │
1  Vocabulary      Input Tags  (Input.*)        — verbs, not keys
        │
2  Data            UNexusInputContext           — IMC + tagged bindings + policy
                   UNexusInputConfig (optional)  — shared binding sets
        │
3  Per-pawn        UNexusInputComponent : UEnhancedInputComponent  (binder)
                   UNexusInputHostComponent     — the hero's ONLY input member
        │
4  Brain           UNexusInputManager (LocalPlayer subsystem)
                   context stack · dispatcher · glyph driver · rebind facade
                   · Common UI arbitration
        │
5  Consumers       abilities / equipment / movement / UI subscribe to verbs
                   (the hero holds nothing)
```

## How a designer uses it

- **Add an input verb:** author an `IA_*` asset, add an `Input.*` tag, and add
  one binding row to the relevant Input Context (tag + action + trigger +,
  for the common case, the ability tag to activate). No code.
- **Wire a verb to an ability:** set the binding's `ActivateAbilityTag` (e.g.
  `Ability.Weapon.Fire`). Pressed activates, Released deactivates. Done.
- **Wire a verb to custom logic:** leave `ActivateAbilityTag` empty; the owning
  component/ability calls `RegisterInputHandler(Tag, ...)` and gets the
  payload. This is the Move / Look / Interact path.
- **Add a mode:** author a `UNexusInputContext` listing its bindings, its IMC,
  its priority, and whether it's modal (blocks verbs below) or overlay. The
  system that owns the mode pushes it and pops it by handle.
- **Hold vs toggle / tap vs hold:** a property on the binding plus an optional
  player override in settings. No C++ branch.
- **Gate a verb for input reasons:** list contexts that suppress it (Examine
  suppresses Fire). Gameplay gating (no ammo, reloading) stays on the ability.
- **Rebind at runtime:** the settings screen calls the rebind facade; it writes
  through Enhanced Input User Settings and persists.
- **Per-device layout:** author a second IMC for that device on the context;
  the manager swaps it on `OnInputMethodChanged`.

## Concepts

### Input Tag (the verb)

The canonical vocabulary, reusing the project's existing `Input.*` namespace
(`Input.Run`, `Input.Crouch`, `Input.Weapon.Fire`, `Input.Weapon.Reload`,
`Input.Weapon.Aim`, `Input.Weapon.Melee`). Slot draw/swap is equipment-neutral
(any equippable, not just weapons), so it lives under `Input.Equipment.*`
(`Input.Equipment.Slot1/2`, `Input.Equipment.SwapNext/Prev`) — not under
`Input.Weapon.*`. New verbs extend the same root:
`Input.Move`, `Input.Look`, `Input.Interact`, `Input.QuickHeal`,
`Input.Cancel`, `Input.Pause`, `Input.OpenInventory`, `Input.OpenMap`,
`Input.Examine.Rotate`.

A verb describes *what the player meant*, never the key. The same tag fires
from KB&M and pad, across contexts, after a rebind, with no listener change.
(The old draft proposed a parallel `Input.Intent.*` namespace — superseded;
the project already ships `Input.*` and Lyra uses the same flat style.)

### Tagged binding

The link between a verb and an Input Action, carried on a context. Each row:

- the `Input.*` tag;
- the `UInputAction` that triggers it;
- the trigger semantic the listener cares about (Pressed, Released,
  Triggered/axis, Tap, Hold, Hold-threshold-crossed);
- **`ActivateAbilityTag`** (optional) — the bespoke-ASC ability to activate on
  Pressed / deactivate on Released. The declarative fast path.
- **activation style** — Press, Hold (active while held), Toggle, or
  Tap-vs-Hold (two outcomes, like Normal vs Ceremony draw);
- **suppressing contexts / required-absent state tags** — input-mode gating
  only (see Input policy);
- optional priority within the context.

### Input context

A `UNexusInputContext` data asset — the unit the stack pushes. Carries:

- a context tag (`Input.Context.Gameplay`, `.Examine`, `.Menu`, `.Dialog`,
  `.Cinematic`, `.Vehicle`);
- priority (higher sits on top);
- a **modal** flag — modal contexts block every verb below; overlay contexts
  let them through;
- an optional block-tag query — verbs below matching it are blocked even under
  an overlay;
- the IMC (and an optional per-device IMC list);
- its tagged bindings;
- whether it is an **in-world** mode (managed entirely here: Gameplay, Examine,
  Vehicle) or a **UI** mode (its input mode is owned by a Common UI activatable
  widget — see Common UI arbitration).

### Context stack (the brain — `UNexusInputManager`)

A **LocalPlayer subsystem**, not a member of the pawn. Its lifetime matches the
local player, so a pawn swap (escort segment, possession change) never loses or
double-registers the stack — the single biggest correctness fix over today's
hero-owned binding. It:

- owns Push / Pop / Replace (the only mutators), each returning/keyed by an
  **opaque handle** so a caller pops only its own context;
- applies each active context's IMC(s) to `UEnhancedInputLocalPlayerSubsystem`
  at the right priority;
- tells the active pawn's `UNexusInputComponent` to rebind when the active set
  changes;
- resolves each press top-down and dispatches the verb;
- hosts the glyph driver, the rebind facade, and Common UI arbitration.

### Per-pawn binder (`UNexusInputComponent` + `UNexusInputHostComponent`)

`UNexusInputComponent : UEnhancedInputComponent` binds the active contexts'
tagged actions to the manager's dispatch entry points (Lyra's
`BindAbilityActions` shape). `UNexusInputHostComponent` is the **only**
input-related thing the hero owns: on possession by a local controller it
registers the pawn with the manager and creates the input component; on
unpossession it unregisters and pops any pawn-owned contexts. It holds no
per-action methods — adding a verb never touches it or the hero.

### Dispatcher

The fan-out. For a declarative binding the manager activates/deactivates the
named ability on the bespoke ASC directly. For a listener binding, anything
that wants the verb calls `RegisterInputHandler(Tag, Callback)` and gets a
handle; the callback receives the payload (axis value, trigger phase, hold
duration, originating device) and returns Handled / Unhandled. Handlers persist
across context switches; they only fire when the active stack emits the verb.

### Input policy (gating)

Two distinct gates, kept separate on purpose:

- **Input-mode gate (this layer):** a verb can be suppressed by an active
  context (Examine suppresses Fire/Reload/Melee) or by a "required-absent"
  state tag. This is the home of every `IsExamining()` check the hero scatters
  today — declared once on the binding, enforced centrally.
- **Gameplay gate (the ability):** "can this actually run" — ammo, cooldown,
  reloading, swapping — stays on the ability via its existing
  `ActivationRequiredTags` / `ActivationBlockedTags` / `CanActivateAbility`.
  The input layer does not duplicate it; it forwards the press and lets the
  ability accept or refuse, then reads the refusal for the HUD.

When either gate refuses, the manager records a reason on `LogNexusInput` and
exposes it so the HUD can surface "Can't reload — magazine full".

### Hold / toggle / tap resolution

The hero's `EInputMode` fields (`RunInputMode`, `CrouchInputMode`,
`AimInputMode`) and its `HandleToggleAbilityInput` / slot tap-vs-hold methods
move here as binding data + manager bookkeeping:

- **Hold** — ability active while the action is held (uses the Held trigger).
- **Toggle** — press flips active state; the manager owns the toggle latch and
  the existing `Ability.*.Intent.UnAim` / `.UnCrouch` loose-tag handshake.
- **Tap vs Hold** — one action, two verbs (tap → `Input.SlotPrimary`,
  hold-threshold → a "ceremony" variant), reproducing today's slot behaviour
  through the Enhanced Input Hold trigger instead of hand-timed code.
- **Repeated-input-as-hold** (RE accessibility) — a per-verb option that lets a
  held button stand in for repeated taps.

The chosen mode comes from the binding default, overridable per player through
Enhanced Input User Settings.

### Glyph driver

Built on what already exists. The driver subscribes to
`UCommonInputSubsystem::OnInputMethodChangedNative`, exposes
`GetGlyphForInputTag(Tag)` — resolve Tag → Input Action → current bound key
(Enhanced Input / player-mappable query) → `UNexusUIUtility::GetIconForFKey`
(which already calls `TryGetInputBrush`) — and broadcasts
`OnInputDeviceChanged`. The HUD subscribes and re-queries; it never caches a
glyph and never reads Enhanced Input directly. A rebind updates the glyph for
free because the lookup runs through the live mapping.

### Rebind facade

A thin wrapper over `UEnhancedInputUserSettings`:
`RegisterContext(IMC)` (calls `RegisterInputMappingContext`),
`ListMappings(Context)`, `BeginRebind(Mapping)`, `ApplyKey(Mapping, Key)`,
`ResetMapping` / `ResetAll`, `Save` / `Load`. Mappings are marked
player-mappable in the IMC. The settings screen talks only to this facade; no
system writes user settings directly.

### Common UI arbitration

The piece the old draft under-specified, and the crux of "compatible with
Common UI." There are two input worlds and the manager keeps them out of each
other's way:

- **World input** → Enhanced Input IMCs + our stack. In-world modes (Gameplay,
  Examine, Vehicle) live entirely here.
- **Menu input** → Common UI's action router + activatable widgets. When a
  full-screen panel (attaché, map, pause, merchant, dialog) opens, its
  `UCommonActivatableWidget` declares `GetDesiredInputConfig` (Menu / Game /
  All, mouse capture, cursor) — Common UI sets the input mode. We never call
  `SetInputMode`.

The bridge: a menu opening pushes `Input.Context.Menu` (modal) onto the stack,
which **suspends the gameplay IMCs** so world verbs stop firing while the menu
routes navigation through Common UI; closing pops it and the gameplay IMCs
return. Panels are opened through the existing **`UNexusUIRequestSubsystem`**
seam (interaction requests a panel by tag; the layout opens the activatable
widget; the widget's activation pushes the Menu context). Examine, by contrast,
is *not* a Common UI panel — it's an in-world sub-mode, so it stays a Gameplay-
stack context that repurposes Look. Recommendation: stand up a Common UI
`PrimaryGameLayout` with named layers (Game / GameMenu / Menu / Modal) as the
panel host; a `GameUIPolicy` (Common Game) is optional and noted under open
questions.

## Lifecycle

1. The local controller possesses the hero. `UNexusInputHostComponent`
   registers the pawn with `UNexusInputManager` and creates the input
   component.
2. The manager pushes `Input.Context.Gameplay` and applies its IMC.
3. Each press walks the stack top-down. The first context whose IMC recognises
   the action resolves it to an `Input.*` verb.
4. The input-mode gate runs. If a context suppresses the verb, the press is
   refused and a reason is logged.
5. Accepted: a declarative binding activates/deactivates its ability on the
   ASC; a listener binding fires registered handlers in priority order until
   one returns Handled.
6. A mode change pushes its context. In-world modes (Examine) suspend lower
   verbs via the modal flag; UI modes additionally hand input to Common UI.
7. Mode exit pops the context by handle; the lower context resumes.
8. Unpossession or level change: the host unregisters and the stack resets to
   the boot state (Gameplay active, every modal context dismissed).

## Survival-horror specifics

- **Aim** is hold by default, toggle by setting. While active the WeaponAim
  ability owns `Character.State.Weapon.Aiming`; the input layer only forwards
  press/release and runs the toggle latch.
- **Fire** semantics are the weapon's, not the input layer's: a per-press tap
  for semi/shotgun, a held action for full-auto with the ability honouring its
  cooldown re-arm. The binding forwards Pressed/Released; the WeaponFire ability
  branches on fire mode.
- **Run / Crouch** are hold-or-toggle per setting, routed to the locomotion
  abilities, reproducing today's behaviour without the hero's `EInputMode`
  branches.
- **Interact** is one verb resolved by the focused object's data (the
  interaction system already picks Pick Up / Open / Read / …). The binding
  forwards Pressed (start hold), the Hold-threshold crossing (commit), and
  Released (cancel); the interaction ability owns the progress timer. While
  Examine is active, Interact exits Examine instead — expressed by the Examine
  context, not by a hero `if`.
- **Examine** pushes `Input.Context.Examine` (modal, in-world): Look becomes
  `Input.Examine.Rotate` into `UNexusExamineComponent::AddRotationInput`,
  combat/locomotion verbs are suppressed, Cancel pops the context. This
  replaces the hero rerouting Look and gating on `IsExamining()`.
- **Equipment slots** — `Input.Equipment.Slot1/2` (equipment-neutral; any
  equippable, not just weapons) with tap → Normal draw, hold → Ceremony, routed to
  `UNexusEquipmentComponent::RequestActivateSlot(SlotTag, Style)`. The verb → slot
  mapping is data (`SlotActivationVerbs`); slot identity stays `Equipment.Slot.*`.
  `Input.Equipment.SwapNext/Prev` (and last) map to
  `RequestActivateNextSlot` / `PrevSlot` / `LastSlot`.
- **Quick-heal** is a single press routed to the consumable ability; if it
  can't run (no consumable) the ability refuses and the HUD shows why.
- **Inventory / map / pause** are Common UI menu layers: opening pushes
  `Input.Context.Menu` (gameplay suspended) and the activatable widget owns the
  input mode. The attaché reuses the equip context underneath.
- **Inverted look (separate move/aim), camera-wobble toggles, sensitivity
  curves, aim assist** live as Enhanced Input modifiers + Enhanced Input User
  Settings, not as bespoke code.

## Hero refactor (the removal plan)

Today `ANexusHeroCharacter` owns ~15 `UInputAction*` properties, a
`SetupPlayerInputComponent` full of `BindAction`s, a dozen `On*Input*`
handlers, three `EInputMode` fields, the slot tap/hold methods,
`HandleToggleAbilityInput`, and four `GetXxxInput()` pollers. All of it leaves:

- **Move / Look** → a locomotion listener (a small component or the movement
  component) registered on the Gameplay context.
- **Aim / Fire / Reload / Melee** → declarative bindings (`ActivateAbilityTag =
  Ability.Weapon.*`); the weapon abilities need no input code.
- **Run / Crouch** → declarative bindings with hold/toggle data.
- **Interact** → the interaction ability registers a listener.
- **Slots / swap** → the equipment component listens (or declarative routes to
  its public API).
- **Quick-heal** → the consumable ability listens.
- **Open inventory / map / pause** → the owning UI systems push a Menu context.
- **`GetLookInput()` / `GetMoveInput()` / `GetRunInput()` / `GetCrouchInput()`**
  (read by the Anim BP) → served by the manager's cached per-tag axis/bool
  values, or kept as thin pass-throughs that read the manager. The Anim BP
  contract is preserved; its data source changes.

End state: the hero holds one `UNexusInputHostComponent` and zero
`SetupPlayerInputComponent` / `BindAction` code. An AI-controlled instance of
the same character simply never gets a host component and drives the same
abilities through behaviour logic.

## Decoupling contract

- The hero does not call `BindAction` or read Input Action values.
- Gameplay code subscribes to `Input.*` verbs (or is named on a binding), never
  to raw Input Actions.
- The input layer drives the bespoke ASC and component public APIs
  (`TryActivateAbilityByTag`, `RequestActivateSlot`, …); it does not reach into
  ability internals, and abilities never reach back into input.
- Gameplay gating belongs to abilities; the input layer owns only input-mode
  gating and forwards the result.
- UI owns its own input mode through Common UI activatable widgets; the input
  layer only suspends gameplay underneath. No system calls `SetInputMode`.
- Rebinding goes through the rebind facade; nothing writes Enhanced Input User
  Settings directly.
- The manager is a LocalPlayer subsystem; its lifetime is the local player, not
  the possessed pawn.

## NPC and AI

Player-only. NPCs activate the same abilities directly through their own ASC
via behaviour logic; the input layer is a no-op for them — an AI controller's
pawn simply never gets a `UNexusInputHostComponent`, so nothing registers. The
manager's API is safe to call from anywhere but does nothing without a
registered local pawn.

## Save and load

- Rebindings and per-verb input options (hold/toggle, sensitivity, invert) ride
  `UEnhancedInputUserSettings` — a global preference slot independent of the
  gameplay save, persisting across save files.
- The context stack does **not** persist. On load the boot state re-applies:
  Gameplay active, every modal/UI context dismissed, mouse/cursor reset.
- In-progress holds (interact, ceremony) do not persist; they resolve as
  cancelled on load — matching how the abilities already reconcile on load.

## UI and HUD hooks

- HUD prompts subscribe to `OnInputDeviceChanged` and call
  `GetGlyphForInputTag(Tag)` each refresh. No widget hard-codes a key or caches
  a glyph.
- The interact prompt reads the focused interactable's resolved verb + gate
  reason (interaction system) and the glyph (input layer): two systems, one
  prompt.
- A Common Bound Action Bar (Common UI) can drive on-screen "back / confirm"
  affordances in menus straight from the activatable widget's actions.
- The pause / settings screen drives rebinding through the rebind facade only.
- A "press any key" splash uses a manager `RawAnyKey` event, not polling.

## Debug

- `nexus.input.debug` toggles an overlay: the active stack top-to-bottom with
  each context's modal flag, the active IMCs, the last fired verb + trigger
  phase, the last refused verb + the gate that refused it, and the current
  device.
- `LogNexusInput` emits stack mutations, verb fires, and refusals at
  verbose-and-above so a designer can scrub a session log.

## What's out of scope (v1)

- Couch co-op and split-screen.
- Network input prediction and replication.
- Replay / input recording.
- Native touch and Steam Deck bindings (Steam Input pass-through works; native
  touch deferred).
- A full Common Game `GameUIPolicy` / `UIManagerSubsystem` (the
  `PrimaryGameLayout` + Menu-context bridge is in scope; the policy layer is
  optional — see open questions).
- Accessibility transforms beyond what Enhanced Input modifiers + user settings
  provide (screen-reader prompts, hold-to-toggle global conversion) — seams
  left in for v2.

## Open questions

- **Dispatch shape.** Declarative `ActivateAbilityTag` for the common case plus
  a listener API for the rest (proposed) — or a uniform listener model where
  even Fire/Aim register handlers? Proposed: hybrid, because it deletes the most
  hero code for the least machinery.
- **Move/Look home.** A dedicated locomotion input component on the pawn, or
  listeners on the existing `UNexusCharacterMovementComponent`? Proposed:
  a small component, so an AI pawn omits it cleanly.
- **Axis payload cadence.** Per-tick for Move/Look, threshold-only for the rest
  (proposed), matching how the Anim BP consumes Move/Look today.
- **Common UI layout ownership.** Stand up a `PrimaryGameLayout` owned by the
  HUD/PC now, or adopt Common Game's `GameUIManagerSubsystem` + `GameUIPolicy`?
  Proposed: a lightweight `PrimaryGameLayout` first; policy layer later.
- **Per-device IMC swap.** Auto-swap on `OnInputMethodChanged` (proposed) vs an
  explicit reload.
- **Rebinding scope.** IA-level rebinds only for v1 (engine default, proposed)
  vs per-context overrides ("Reload" differs inside Vehicle).
- **Stacked modals.** Inventory open + a dialog opening — does the second modal
  stack and pause the first (proposed) or force the first to pop?
