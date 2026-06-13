# Interaction

> The player's verb on the world. One Interact input resolves — by data on
> the focused object — into Pick Up, Open, Examine, Read, Use, Unlock,
> Search, or Talk. Effects route through public APIs of other systems.
> First-person, survival-horror.

## What the system does

- Detects what the player is looking at and what's nearby (focus plus a
  proximity sphere).
- Resolves a verb from data on the focused object — no input-side branch
  per verb.
- Gates verbs with conditions (a key item, a world flag, free inventory
  space) and surfaces a clear "Locked — needs X" prompt when they fail.
- Runs a list of effects on success — give item, consume item, set world
  state, open a UI panel, play montage / FX / sound, transition a door,
  award currency — all through public APIs.
- Hold-to-interact with progress and cancel-on-release; tap verbs use
  duration zero.
- Persists per-interactable state (consumed, open, used, looted) across save
  and load.

## How a designer uses it

- An interactable is an actor composing UNexusInteractableComponent. No
  bespoke subclass per verb.
- Author one or more interaction entries on the component, each a verb plus
  conditions plus effects.
- A new verb is a new Interaction.Verb.* tag and (optionally) a new effect
  type. No component or ability change.
- A new condition (requires-quest-stage, requires-time-of-day) is a new
  FNexusInteractionCondition subtype.
- A new effect (spawn an actor, trigger a sequence) is a new
  FNexusInteractionEffect subtype.
- A new world fact is a new Interaction.State.* tag that conditions and
  effects already read and write.

## Concepts

### Interactable interface

INexusInteractableInterface is the contract any actor or component
implements. It exposes TryStartInteraction and TryStopInteraction, the
on-entered / on-left range notifications, and on-gained / on-lost focus
notifications. The interactor is passed in by the caller, so an AI could
drive an interaction through the same path with no special code.

### Interactable component

The reusable implementation. Owns the list of interaction entries, runs
the hold/progress/cancel machinery, owns the world-marker indicator, and
fires lifecycle delegates. A door, a note, a lever, a merchant are all
data plus effects on this component.

### Interaction entry

Data: a verb tag, a hold duration, a list of conditions, a list of
effects, a one-shot / toggle / repeatable flag, and the prompt text. The
component picks the best enabled entry for the interactor on press.

### Conditions

Each condition is a small data object with IsMet(interactor) and a
fail-reason string the prompt can show:

- RequiresItem (identity tag plus count)
- RequiresWorldState (key plus expected value)
- RequiresFreeSpace
- NotConsumed

### Effects

Each effect is a small data object with Execute(interactor, interactable):

- GiveItem — calls UNexusInventoryAcquireLibrary::AcquireItem.
- ConsumeItem — calls inventory's public remove API.
- SetWorldState — calls UNexusWorldStateSubsystem::Set.
- OpenUI — fires a UI-request delegate or tag (merchant, save, map).
- PlayMontage / PlayFX / PlaySound.
- DoorTransition.
- AwardCurrency.
- MarkConsumed.

### Interaction ability

UNexusAbility_Interaction lives on the bespoke ASC. It runs the focus trace
per tick, the awareness sphere periodically, and calls the interface on the
focused interactable. It exposes the resolved verb and gate to the HUD.

### World-state subsystem

A flat, save-backed map from gameplay tag to value (bool or int) for things
like "door X open" or "lever Y pulled". Conditions read it, effects write
it, and the quest system layers on top. One source of truth for whether the
world has changed.

### Examine controller

A focus sub-mode. Pulls the examined mesh into view, suppresses other
abilities via a Character.State.Examining tag, rotates on look-input, and
exposes reveal hotspots (a hidden code on the base of a statue, for
example) plus an optional combine step.

## Lifecycle

1. The awareness sphere fires OnEnteredPlayerRange; distant world markers
   appear.
2. The look-at trace fires OnGainedPlayerFocus; the HUD resolves the best
   enabled verb on the focused object.
3. The player presses Interact. The component checks conditions.
4. If conditions fail, the prompt shows the reason and the press aborts.
5. If conditions pass, the hold begins. Progress ticks through delegates.
6. Release before completion fires OnInteractionCancelled.
7. Hold to full fires OnInteractionCompleted; the entry's effects run in
   order through their public APIs.
8. Persistent state is written. Lose focus or leave range tears the prompt
   down.

Instant verbs (duration zero) complete on press. Toggle verbs (a door)
flip state each time.

## Focus and awareness

Two-tier detection. Awareness is a periodic sphere trace on the Interaction
channel — cheap, builds the nearby set, fires range events so distant
markers can render. Focus is a per-tick camera-forward trace on the same
channel that resolves the precise component under the reticle.

The trace stays host-agnostic via the controller viewpoint, the same way
weapon hit delivery works. Tick is gated on a non-empty nearby set so the
system is free when nothing's around.

## Decoupling contract

- Interaction consumes. It never owns.
- Effects mutate state only through public APIs — AcquireItem, inventory
  remove, world-state Set, currency, UI-request. The interaction module
  includes no inventory / equipment / UI internals.
- The player ability calls down. Nothing calls up. Interactables don't
  reach into the player; the HUD subscribes to component delegates and the
  ability's focus accessor.
- Inventory and the world-state subsystem are leaves. Interaction is the
  consumer that wires a verb to their public mutations.
- One prompt source. The HUD reads the focused interactable's resolved verb
  and gate; no system pushes prompt strings into the interactable.

## NPC and AI

The interface takes an Interactor actor, so an AI can drive an interaction
through TryStartInteraction with no special code. V1 focuses on player
detection — whether AI gets a parallel detection driver is an open
question. Interactables stay interactor-agnostic regardless.

## Save and load

- Per-interactable state (consumed, open / closed, used, looted) rides the
  owning actor's save data — the same pattern the pickup actor already uses.
- Cross-actor and abstract world facts (a global flag, a solved puzzle) ride
  the world-state subsystem's save.
- On load a consumed pickup stays gone, an opened door stays open, a pulled
  lever stays pulled, and conditions re-evaluate against the restored world
  state.
- An in-progress hold does not persist. It resolves to idle on load.

## UI and prompt hooks

The HUD shows:

- The focused verb label plus the input glyph plus tap-vs-hold.
- The gate reason when an entry is disabled ("Locked — needs Square Crank").
- The hold progress bar.
- The world marker for in-range-but-unfocused interactables.
- A list or secondary affordance when an object offers more than one
  enabled verb.

All of it reads off the component's delegates, the ability's focus
accessor, and the conditions' fail reasons. The components stay
UI-shape-agnostic.

## What's out of scope (v1)

- Branching dialogue trees (Talk opens the dialogue system; that system
  is separate).
- The merchant / inventory / save / map screen UI flows (interaction only
  requests them).
- Physics push/pull and rigid-body manipulation puzzles.
- Traversal and parkour locomotion (climb/vault is a hook into the
  movement system).
- Sequencer and cutscene authoring; staged finisher cinematics.
- Networked and replicated interaction.
- A full quest-graph engine (the world-state store is a flat key/value
  the quest system layers on).

## Open questions

- Effect and condition shape: instanced-struct data objects resolved in C++,
  BlueprintImplementableEvents on the component, or a hybrid?
- Focus selection: pure look-at trace, closest-in-cone, or a hybrid
  priority score (distance plus view-angle plus interactable priority)?
- Examine scope: full rotate-and-reveal with item combine now, or a
  lighter pull-in plus description plus single reveal for v1?
- World-state ownership: a dedicated subsystem, or fold flags into the
  existing save / quest system?
- Multi-interaction UX: auto-pick the single best verb, primary plus
  secondary (tap vs hold), or a radial list when several are available?
- Item combine home: part of interaction (Examine sub-mode) or inventory's
  UI? Where does the combine recipe data live?
- NPC interaction in v1: does AI get a parallel detection driver now, or
  is detection player-only with the interface left AI-ready?
- Contextual finisher: is the prompt-driven finisher an interaction verb
  (a contextual action on a staggered enemy) or owned elsewhere?
- Door / level transition: is a DoorTransition effect (level streaming plus
  fade) in v1, or just open/close animation with transitions handled by
  the level system?
- Prompt text source: authored per-interaction string, derived from the
  verb tag via a lookup, or item-DisplayName-driven?
