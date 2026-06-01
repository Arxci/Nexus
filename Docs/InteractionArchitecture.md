# Interaction System — Architecture Plan (RE4R-class target)

> Authoritative spec for the Nexus interaction system: a first-person, survival-horror,
> RE4R-style game. This is a target design used to review, complete, and align the
> existing (partial) interaction code. Where it conflicts with an offhand instruction,
> this file wins.

The interaction system is the player's verb on the world — pick up, open, examine, read,
use, unlock, search, talk, save. It is a **consumer** of systems that already exist: the
**inventory** (`UNexusInventoryComponent` + `UNexusInventoryAcquireLibrary::AcquireItem`),
the **equipment** runtime, the bespoke **ability system** (`UNexusAbilitySystemComponent`,
NOT Epic GAS), and a **world/quest state** store. It does NOT redesign those — it reads
them and routes outcomes through their public APIs. It already has a working spine:
`INexusInteractableInterface`, `UNexusInteractableComponent` (hold-to-interact + progress +
world-marker), and `UNexusAbility_Interaction` (focus + proximity awareness). This spec
completes that spine into a data-driven verb/condition/effect model.

## Locked design decisions (fixed)
- **One interface, many interactables — composition, not a class tree.** Anything
  interactable implements `INexusInteractableInterface`; the canonical implementation is
  the reusable `UNexusInteractableComponent` an actor composes (as `ANexusItemPickup`
  already does). A door, a note, a lever, a merchant are **data + effects on that
  component**, not bespoke C++ actor subclasses.
- **The player drives focus; the interactable owns its behavior.** `UNexusAbility_Interaction`
  on the bespoke ASC finds what the player is looking at / near and calls the interface;
  the interactable decides what happens. KEEP the bespoke `UNexusAbility` framework
  (lifecycle, tags, SaveGame) — this is NOT Epic GAS and won't become it.
- **Interactions are data: a verb, conditions, and effects.** An interactable exposes one
  or more interactions; each is a **verb** (Pick Up / Open / Examine / Read / Use / Unlock /
  Search / Talk), a set of **conditions** that gate it (key item held, world flag set, free
  inventory space), and a list of **effects** that run on success. New interaction types
  ship as data + an effect, not a new actor class. (CHANGE — today the component is a
  single hard-coded hold duration with listeners hand-bound per actor.)
- **Decoupled, one-way.** Interaction is a CONSUMER of inventory, equipment, the world/quest
  state, and the UI. Effects mutate the world ONLY through public APIs (`AcquireItem`,
  inventory remove, a world-state subsystem `Set`, a UI open request). Interactables never
  reach into the player; the player's ability calls the interface; nothing calls back up
  into the interaction ability.
- **Held timing, tap/hold, cancel-on-release.** KEEP the existing hold-to-interact model:
  `InteractionDuration`, `OnInteractionProgressed/Completed/Cancelled/Ended`, complete-on-
  hold, cancel-on-early-release. Instant verbs use Duration 0.
- **The prompt is resolved, never hard-coded.** The HUD reads the focused interactable's
  *available* verb(s) and gating state (e.g. "Open", "Examine", or "Locked — needs Square
  Crank") off the component + conditions. KEEP the world-marker indicator; extend it to show
  the verb + gate.
- **State persists per interactable.** A pulled lever, an opened door, a looted container, a
  consumed one-shot survive save/load — via the same EMS actor-save the pickup already uses
  (`bWasCollected`). The interaction system never re-grants a consumed pickup on reload.
- **Host-agnostic.** The interface takes an `Interactor` actor; nothing assumes the player
  pawn, a camera, or a first-person mesh. An AI or a turret could interact through the same
  contract. (Player-only awareness is the ability's concern, not the interactable's.)

Legend: **KEEP** = already aligned · **CHANGE** = structural rework · **ADD** = new.

---

## 1. Goals & Scope
A modular, data-driven first-person interaction framework where the player's single
"interact" verb resolves — by data on the focused object — into pick-up, open/close,
examine, read, use, unlock, search, or talk, gated by conditions and producing effects that
route through the existing inventory / equipment / world-state APIs. Scarcity-driven,
deliberate, RE4R-feel exploration.

**In scope (v1):**
- Focus + proximity awareness — camera-forward trace on the `Interaction` channel + a
  proximity sphere; focus gained/lost, range entered/left (KEEP `UNexusAbility_Interaction`)
- Hold-to-interact with progress + cancel-on-release; instant (tap) verbs (KEEP
  `UNexusInteractableComponent`)
- **Verb + condition + effect model** — an interactable declares interactions as data
  (CHANGE/ADD; today it's one duration + per-actor delegate binding)
- Interaction verbs: Pick Up (KEEP, generalize off `ANexusItemPickup`), Open/Close toggle
  (door/drawer/container), Use (lever/switch/valve/button), Unlock (key item / code),
  Read (note/file/map), Search/Loot (container with contents), Examine/Inspect (RE-style),
  Talk/Merchant/Save/Heal as **open-UI hooks** (ADD)
- **Conditions/gating** — requires-key-item, requires/sets world flag, free-inventory-space,
  one-shot-already-used → drives an enabled/"Locked"/"Need X" prompt (ADD)
- **Effects/outcomes** — give item (`AcquireItem`), remove/consume item, set world/quest
  state, play montage/sound/FX, open a UI panel, door transition, award currency — all via
  public APIs (ADD)
- **Multiple interactions per object** — a primary + optional secondary verb (e.g. Open /
  Examine), surfaced to the prompt (ADD)
- **Examine / Inspect sub-mode** — pull the item into a focus view, rotate it, reveal a
  hidden detail / unlock a combine (ADD; the RE signature feature)
- Save/load of interactable state (open, looted, used, consumed) (ADD; KEEP the pickup's pattern)
- HUD prompt hooks — verb label, key, hold-vs-tap, gate reason, progress (KEEP marker, EXTEND)

**Out of scope in v1 (must stay cheap to add):** branching dialogue trees (Talk is a hook
that opens the dialogue system, which is separate); the merchant / inventory / save *screen*
UIs (interaction only *requests* them — those systems own their flows); physics push/pull
puzzles and rigid-body manipulation; traversal/parkour locomotion (climb/vault is a hook into
the movement system, not authored here); sequencer/cutscene authoring; networked/replicated
interaction; full quest-graph logic (the world-state store is a flat key/value the quest
system layers on).

## 2. Key Design Decisions

| Decision | Choice | KEEP/CHANGE/ADD |
|---|---|---|
| Interactable contract | `INexusInteractableInterface` on any actor/component | KEEP |
| Reusable behavior | Compose `UNexusInteractableComponent`; data + effects, no actor subclass tree | KEEP + CHANGE |
| Player detection | `UNexusAbility_Interaction`: per-tick focus trace + periodic awareness sphere | KEEP |
| Interaction unit | Data **verb + conditions + effects** (instanced struct), one or many per interactable | CHANGE/ADD |
| Timing | Hold w/ progress + cancel-on-release; Duration 0 = instant tap | KEEP |
| Conditions | Data gates (key item / world flag / inventory space) → enabled / "Locked" / "Need X" | ADD |
| Effects | `AcquireItem`, remove item, set world state, montage/FX, open-UI, door transition, currency | ADD |
| Examine | RE-style focus-and-rotate sub-mode w/ reveal + combine hook | ADD |
| World state | A flat, saveable key→value subsystem (`Interaction.State.*`) conditions read/write | ADD |
| Prompt | HUD reads focused verb(s) + gate off the component (extends the world marker) | KEEP + EXTEND |
| Persistence | Per-interactable saved state via the EMS actor-save (as the pickup does) | KEEP + ADD |
| Input | Single interact action; tap vs hold; press starts, release stops/cancels | KEEP |
| Host | `Interactor` actor through the interface; no player/camera/first-person assumption | KEEP |

## 3. Architectural Components
- **`INexusInteractableInterface`** (KEEP): the contract —
  `TryStartInteraction`/`TryStopInteraction` + the `OnEntered/LeftPlayerRange` and
  `OnGained/LostPlayerFocus` notifications. EXTEND with a query the prompt/ability use to
  ask "what interactions do you offer this interactor, and are they enabled?"
- **`UNexusInteractableComponent`** (KEEP + CHANGE): the reusable interactable. Today: one
  `InteractionDuration`, progress tick, `OnInteractionProgressed/Completed/Cancelled/Ended`,
  a world-marker indicator (`FComponentPicker` indicator + trigger targets). CHANGE: own a
  list of **interaction entries** (verb + conditions + effects); pick the best enabled entry
  for the interactor; run its effects on Complete. KEEP the hold/progress/cancel machinery
  and the indicator.
- **Interaction entry** (ADD): `FNexusInteraction` data — `Verb` tag, `HoldDuration`,
  `Conditions` (`TArray<TInstancedStruct<FNexusInteractionCondition>>`), `Effects`
  (`TArray<TInstancedStruct<FNexusInteractionEffect>>`), `bRepeatable`/`bToggle`/`bOneShot`,
  prompt text.
- **Condition types** (ADD): `FNexusInteractionCondition` subtypes — `RequiresItem`
  (identity tag + count), `RequiresWorldState` (key + expected value), `RequiresFreeSpace`,
  `NotConsumed`. Each answers `IsMet(Interactor)` + supplies a fail reason for the prompt.
- **Effect types** (ADD): `FNexusInteractionEffect` subtypes — `GiveItem`, `ConsumeItem`,
  `SetWorldState`, `PlayMontage`/`PlayFX`/`PlaySound`, `OpenUI` (panel tag), `DoorTransition`,
  `AwardCurrency`, `MarkConsumed`. Each `Execute(Interactor, Interactable)` through a public API.
- **`UNexusAbility_Interaction`** (KEEP + EXTEND): focus trace + awareness sphere + focus/
  range events. EXTEND: expose the focused interactable's resolved verb + gate to the HUD;
  optionally choose between primary/secondary verbs.
- **`UNexusWorldStateSubsystem`** (ADD): a saveable flat `TMap<FGameplayTag,int32/flag>` for
  `Interaction.State.*` (door open, lever pulled, puzzle solved). Conditions read it, effects
  write it; the quest system layers on top. One source of truth for "has the world changed."
- **Examine controller** (ADD): a focus sub-mode actor/component that pulls the examined
  mesh into view, rotates it on look-input, and exposes "reveal" hotspots + a combine hook.
- **`NexusGameplayTags`** (ADD keys): `Interaction.Verb.*` (PickUp, Open, Examine, Read, Use,
  Unlock, Search, Talk), `Interaction.State.*` roots, `Action.Interaction.*` montages,
  `Character.State.Interacting`. KEEP `Interactable.Proximity.PlayerInRange`,
  `Interactable.State.HasPlayerFocus`, `WorldMarker.State.*`.

## 4. Interaction Lifecycle
Enter range (awareness sphere → `OnEnteredPlayerRange`, show marker) → gain focus (look-at
trace → `OnGainedPlayerFocus`, prompt resolves the best enabled verb) → press interact
(`TryStartInteraction`) → if the chosen entry is gated, show the fail reason and abort;
else begin the hold (progress ticks) → release early → `OnInteractionCancelled`; hold to full
→ `OnInteractionCompleted` → run the entry's **effects** in order through public APIs →
persist any state change (consumed / open / used) → lose focus / leave range tears the prompt
down. Instant verbs (Duration 0) complete on press. Toggle verbs (door) flip state each time.

## 5. Focus & Awareness Model
KEEP the two-tier detection in `UNexusAbility_Interaction`:
- **Awareness** — a periodic `SphereTraceMulti` on the `Interaction` channel
  (`AwarenessRadius`, `AwarenessUpdateInterval`) builds the nearby set and fires
  `OnEntered/LeftPlayerRange` so distant markers can show; `CanTick` is gated on a non-empty
  nearby set (cheap when nothing's around).
- **Focus** — a per-tick `CameraForwardTrace` (`FocusReachDistance`) on the `Interaction`
  channel resolves the precise component under the reticle (matched by the hit
  `InteractionTriggerTarget`), firing `OnGained/LostPlayerFocus`. **Open:** pure look-at (today)
  vs closest-in-cone vs a hybrid priority score (see Open Questions). The trace stays
  host-agnostic via the controller viewpoint, exactly as the weapon hit-delivery does.

## 6. The Interaction Model (verbs · conditions · effects)
The variable is the **verb + outcome**; the constant is the focus → prompt → hold → complete
spine. An interactable owns `TArray<FNexusInteraction>`. On `TryStartInteraction`, the
component selects the **best enabled** entry for the interactor (priority order; gated entries
still surface to the prompt with a reason). On `OnInteractionCompleted`, it runs that entry's
**effects** in order — each effect a small data object executed through a public API, so the
interaction system stays a leaf:
- `GiveItem` → `UNexusInventoryAcquireLibrary::AcquireItem` (the pickup path, generalized).
- `ConsumeItem` → inventory public remove (spend a key, a battery, a fuse).
- `SetWorldState` → `UNexusWorldStateSubsystem::Set` (door=open, lever=pulled).
- `OpenUI` → a UI-request delegate/tag (merchant, save, map) — interaction doesn't own the UI.
- `PlayMontage/FX/Sound`, `DoorTransition`, `AwardCurrency`, `MarkConsumed`.
A new verb is a new `Verb` tag + (maybe) a new effect type — no interactable subclass.

## 7. Examine / Inspect Sub-Mode
The RE signature verb (ADD). On the Examine effect, enter a focus sub-mode: pull the item's
mesh in front of the camera, suppress movement/fire (own a `Character.State.Interacting` /
`Examining` tag that gates other abilities), rotate the mesh on look-input, and expose
**reveal hotspots** (rotating to the base of a statue reveals a hidden key code) and an
optional **combine** step (examined item + inventory item → new item via inventory). Exit
returns control. Description text + the reveal payload are data on the interactable / item
definition. (Scope of "reveal + combine vs description-only" is an Open Question.)

## 8. Cross-System Integration (decoupling contract)
- **Interaction consumes, never owns.** Effects call the public inventory acquire/remove API,
  the world-state subsystem `Set`, the equipment component, the currency wallet, and a UI-open
  request — never the internals. The interactable reads conditions off inventory/world-state;
  it does not reach into the player controller or HUD.
- **The player ability calls down, nothing calls up.** `UNexusAbility_Interaction` invokes
  the interface (`TryStart/Stop`, focus/range events). Interactables never call back into the
  ability; the HUD subscribes to the component's delegates + the ability's focus accessor.
- **Inventory/world-state are leaves.** Inventory persists items; the world-state subsystem
  persists flags; interaction is the consumer that wires a verb to those public mutations.
- **One prompt source.** The HUD reads the focused interactable's resolved verb + gate; no
  system pushes prompt strings into the interactable.

## 9. NPC / AI Interaction
The interface takes an `Interactor` actor, so an AI *can* drive an interaction (open a door)
through the same `TryStartInteraction` path with no special code. v1 focuses player detection
(the awareness/focus ability is player-driven); whether AI gets a parallel detection driver is
an Open Question. Interactables themselves stay interactor-agnostic.

## 10. Save / Load
Per-interactable state (consumed, open/closed, used, looted) rides the owning actor's EMS
actor-save — the exact pattern `ANexusItemPickup::bWasCollected` already uses, restored in
`ActorLoaded`. Cross-actor / abstract world facts (a global flag, a solved puzzle) ride the
`UNexusWorldStateSubsystem` save. On load, a consumed pickup stays gone, an opened door stays
open, a pulled lever stays pulled, and conditions re-evaluate against the restored world
state. An in-progress hold does not persist — it resolves to idle on load.

## 11. UI / Prompt Hooks
The HUD shows: the focused verb label + input glyph + hold-vs-tap, the gate reason when an
entry is disabled ("Locked — needs Square Crank"), the hold progress bar
(`OnInteractionProgressed`), and the world marker for in-range-but-unfocused interactables.
A list/secondary affordance appears when an object offers more than one enabled verb. All of
it reads off the component's delegates + the ability's focus accessor + the conditions'
fail reasons — the components stay UI-shape-agnostic; the HUD subscribes.

## 12. Extension Points (must stay cheap)
- New verb → an `Interaction.Verb.*` tag + (optionally) an effect type. No actor subclass.
- New condition (requires-quest-stage) → a new `FNexusInteractionCondition` subtype.
- New effect (spawn an actor, trigger a sequence) → a new `FNexusInteractionEffect` subtype.
- New interactable (a lever, a safe, a typewriter) → a placed actor with the component + data.
- New world fact → an `Interaction.State.*` tag; conditions/effects already read/write it.
- New examinable → data on the item/interactable; the sub-mode is generic.

## 13. Acceptance Criteria (definition of done / review yardstick)
1. An interactable is an actor composing `UNexusInteractableComponent` with **data** (verbs +
   conditions + effects) — no per-interaction-type C++ actor subclass, and no interactable
   reaching into the player/HUD.
2. The player's focus + proximity awareness run through `UNexusAbility_Interaction` on the
   bespoke ASC; focus/range events fire on gain/loss/enter/leave, host-agnostically.
3. A single "interact" input resolves — by data on the focused object — to the correct verb
   (Pick Up / Open / Examine / Read / Use / Unlock / Search / Talk) with no input-side branch
   per verb.
4. Hold-to-interact with progress + cancel-on-release is preserved; instant verbs use
   Duration 0; toggle verbs flip state per use.
5. Each interaction's **conditions** gate it (key item / world flag / free space / not-
   consumed), and a failed gate surfaces a reason to the prompt ("Locked — needs X") rather
   than silently doing nothing.
6. On success, the interaction runs its **effects** in order, and every world mutation goes
   through a public API (`AcquireItem`, inventory remove, world-state `Set`, currency, UI
   request) — the interaction module includes no inventory/equipment/UI internals.
7. Pick Up is one such effect (`GiveItem` → `AcquireItem`); `ANexusItemPickup` is reskinned as
   data on the generic component with identical acquire behavior.
8. Examine/Inspect enters a focus sub-mode that pulls the mesh in, rotates on look-input,
   gates other abilities via an owned state tag, and supports at least a reveal payload (and a
   combine hook if the Open Question resolves that way).
9. An object can offer multiple interactions (primary + secondary), and the prompt presents the
   enabled one(s) deterministically.
10. Interactable state (consumed / open / used / looted) persists per actor via the EMS
    actor-save, and abstract world facts via `UNexusWorldStateSubsystem`; a reload restores
    them and re-evaluates conditions. An in-progress hold resolves to idle on load.
11. The interaction system depends one-way on inventory / equipment / world-state / UI; none of
    those depend on the interaction runtime, and effects mutate state only through public APIs.
12. The HUD can show verb label, input glyph, hold-vs-tap, gate reason, and progress purely
    from the component delegates, the ability's focus accessor, and the condition fail reasons.
13. Focus selection is well-defined and tunable (look-at, or closest-in-cone, or hybrid) and
    matches whatever the Open Question resolves; the `Interaction` collision channel and the
    `FComponentPicker` trigger/indicator targets are honored.
14. A new verb / condition / effect / interactable / world fact is added as data + (at most) a
    new condition or effect struct — proven by adding one of each with no change to the
    component, ability, or input.
15. Talk / Merchant / Save / Heal are **open-UI hooks** (effects that request a panel), so the
    interaction system triggers those systems without owning their flows.

## 14. Non-Goals (so a reviewer doesn't flag them as missing)
- Branching dialogue trees / conversation graphs (Talk opens the dialogue system; that system
  is separate).
- The merchant / inventory / save / map *screen* UI flows (interaction only requests them).
- Physics push/pull/rigid-body manipulation puzzles.
- Traversal / parkour locomotion (climb/vault is a hook into the movement system).
- Sequencer / cutscene authoring; staged finisher cinematics.
- Networking / replicated interaction.
- A full quest-graph engine (the world-state store is a flat key/value the quest system layers on).

## 15. Open Questions (resolve before implementing — do not guess)
- **Effect/condition shape:** instanced-struct data objects (`TInstancedStruct<FNexusInteractionEffect>`)
  resolved in C++, BlueprintImplementableEvents on the component, or a hybrid (data effects +
  a BP escape hatch)? (Affects authoring + how designers add one-off behaviors.)
- **Focus selection:** pure look-at trace (current), closest-interactable-in-cone, or a hybrid
  priority score (distance + view-angle + interactable priority)? Tie-breaking when two overlap?
- **Examine scope:** full RE-style rotate-and-reveal sub-mode **with item combine** now, or a
  lighter "pull in + description + single reveal" for v1 (combine deferred to inventory)?
- **World-state ownership:** a dedicated `UNexusWorldStateSubsystem` (flat saved key/value), or
  fold interaction flags into the existing save/quest system? Who owns the save round-trip?
- **Multi-interaction UX:** auto-pick the single best verb, a primary+secondary (tap/hold), or
  a radial/list selector when several are available?
- **Item combine home:** is RE-style item combination part of interaction (Examine sub-mode) or
  the inventory system's UI? Where does the combine recipe data live?
- **NPC interaction in v1:** does AI get a parallel detection/driver now (open doors, hit
  switches), or is detection player-only with the interface left AI-ready?
- **Contextual melee / finisher:** the weapon spec deferred the post-stagger finisher
  *cinematic* — is the prompt-driven finisher an interaction-system "contextual action" (a verb
  that appears on a staggered enemy) or owned elsewhere? v1 boundary?
- **Door / level transition:** is a `DoorTransition` effect (level streaming / teleport + fade)
  in v1 scope, or just open/close animation with transitions handled by the level system?
- **Prompt text source:** authored per-interaction string, derived from the `Interaction.Verb.*`
  tag via a lookup table, or item-definition `DisplayName`-driven? (Localization seam.)
