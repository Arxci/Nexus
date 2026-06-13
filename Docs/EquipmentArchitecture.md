# Equipment

> The component that hosts in-hand items (guns, melee, throwables) and
> passive items (armor, charms) on any actor — player or NPC — through a
> single data-driven slot model. RE7 / Village-style.

## What the system does

- Defines per-character loadouts as data assets — designers add slots
  without touching code.
- Filters which items each slot accepts via gameplay tags.
- Drives the holster / unholster lifecycle for in-hand items, including a
  "ceremony" first-pickup or inspect flourish.
- Applies passive effects (armor, charms) while assigned. No in-world actor,
  no holster animation.
- Keeps a single in-hand item active at a time, with deliberate
  non-interruptible transitions.
- Persists slot assignments and active state across save and load.

## How a designer uses it

- Author one UNexusEquipmentLoadout per character class. Each slot is one
  entry in the loadout.
- Set the slot tag, display name, icon, accepted item tags, and the slot
  mode (in-hand or passive).
- Choose default starter items per slot if needed.
- Add a new slot type by adding a tag and a loadout row. No code changes.
- Player input bindings live on the input asset, not in C++.

## Concepts

### Equipment interface

Any actor that hosts equipment implements INexusEquipmentInterface. The
interface returns the mesh items attach to, the AnimInstance montages play
on, and a convenience PlayMontage helper. Hero actors override it to point
at first-person arms; NPCs return the body mesh. No code path in the
equipment component casts to a concrete character class.

### Loadout

A UNexusEquipmentLoadout data asset, one per character class. Lists the
slots that character has. Each slot carries its tag, label, icon, accepted
item tags, passive-vs-in-hand mode, a sort order, and an advisory input
action hint.

### Equipment component

The runtime. Owns one state record per slot, keyed by slot tag. Each record
tracks the assigned item instance (a pointer into inventory; never owned),
the spawned in-world actor (null for passive slots), what abilities and
tags were granted to the host ASC, and the phase the slot is in.

### Equipped actor

The in-world actor spawned for an active in-hand item. Attaches to the
host's mesh at the item's authored socket (default ik_hand_gun). Resolves
the host-side and item-side montage for any action through its assembly,
so an attachment can override a base montage with no equipment-side branch.

### Item fragments

An item is in-hand-equippable when it has FNexusFragment_Equippable. That
fragment carries the attach socket, the action-to-montage map, the equipped
actor class, abilities to grant, tags to own, and which slots accept the item.

An item is passive when it has FNexusFragment_PassiveEquipment. The fragment
lists abilities and tags to grant through the host's ASC while the item is
assigned. No actor, no montage.

The slot decides the mode; the fragment routes through the right path.

## Slot lifecycle (in-hand item)

- Empty until the player or AI assigns an item.
- Idle once assigned, before a draw.
- Unholstering while the draw montage plays.
- Active once the draw blends out. Only one slot is Active at a time.
- Holstering while the put-away montage plays.
- Back to Idle (or Empty if the item left inventory) on completion.

Activating slot B while slot A is Active chains Holstering A then
Unholstering B. The single-active invariant is strict.

Transitions are non-interruptible. A press during a draw or holster is
dropped, not queued. Animations always play to completion.

Phase advancement is driven by the montage blending out, not by a timer or
an anim notify, so an item without montages still transitions instantly and
no idle frame ever pops in the middle of a swap.

Passive slots short-circuit. Assign applies effects immediately. Clear
removes them. No phases.

## Input

- Each in-hand slot binds an Enhanced Input action.
- A tap activates the slot in Normal mode.
- A hold past the ceremony threshold activates it in Ceremony mode.
- Pressing the same slot's key while it's active deactivates it (toggle to
  empty hands).
- Passive slots have no input action.
- NPC controllers bypass input and call RequestActivateSlot directly.

## Inventory integration

- Equipment never owns items. A slot holds a pointer into the inventory.
- The inventory component is discovered via FindComponentByClass on the host
  actor.
- AssignItemToSlot rejects an item whose CategoryTags don't intersect the
  slot's AcceptedItemTags, or whose fragment doesn't match the slot mode.
- The UI uses the same check to grey out incompatible drop targets.
- Equipment subscribes to inventory's OnItemRemoved. If the assigned item
  leaves the inventory, the slot clears (and deactivates if it was active).
- Cross-system references survive save and load by item GUID.

## Passive equipment

- Identified by FNexusFragment_PassiveEquipment.
- The slot must be marked passive and accept the item's tags.
- On assign, the equipment component grants the passive abilities and owned
  tags through the host's ASC.
- On clear, it removes exactly what it added.
- This is how armor works on day one. Visible armor (a mesh on a body
  socket) is a v2 extension to the same fragment; slot logic is unchanged.

## NPC support

- Any actor implementing INexusEquipmentInterface can host equipment.
- Most enemies inherit ANexusCharacterBase, so they get it for free with the
  body mesh as both the attach target and the anim target.
- An NPC class is configured with a loadout plus an optional starter list
  mapping slot tag to item definition.
- The AI controller calls the same RequestActivateSlot API.
- The component doesn't care whether the caller is the player or an AI.
- An NPC weapon attaches to the body mesh's ik_hand_gun socket — same
  skeleton, same anim contract as the hero.

## Animation and IK

- The host's animated mesh carries the ik_hand_gun socket and the hand-IK
  bones the anim BP locks to.
- The active item's actor attaches there via the equipment interface.
- Montages play through the interface — Host->PlayMontage or
  Host->GetAnimInstance()->Montage_Play. There is no hero-named helper.
- The hero's animated mesh is its first-person arms. They're not a
  leader-pose follower of the body; they play their own montages. The arms
  hide when nothing is in hand.

Two anim notifies are polish, not load-bearing:

- NexusAnimNotify_EquipmentAction plays the item-mesh montage for an
  action (slide, bolt, magazine release) in lockstep with the host montage.
- NexusAnimNotify_HideOutgoingEquipped hides the outgoing weapon mid-holster
  for a clean hand-off. Without it the weapon hides when the holster
  montage ends.

## Save and load

- Slot assignments and the active slot persist via the actor's save interface.
- The component stores slot tag to item-instance GUID, plus the active slot tag.
- On load (deferred one tick so inventory restores first) it re-resolves
  each GUID, re-applies passive effects, re-spawns in-world actors, and
  silently re-draws the previously-active slot. No draw montage plays on load.
- Slots whose item is gone, or whose tag the loadout no longer exposes,
  are skipped.

## UI hooks

UMG queries the component:

- GetLoadout and GetSlots for layout.
- GetAssigned, IsSlotActive, GetActiveSlot, GetSlotPhase for per-slot state.
- OnSlotAssigned, OnSlotCleared, OnSlotActivated, OnSlotDeactivated for
  live updates.

Inventory drag-drop calls AssignItemToSlot. The UI uses CanAssignToSlot or
GetCompatibleSlotsForInstance to grey incompatible drop targets during a
drag. The component is agnostic about UI shape — quick-slots, grid, radial,
anything works.

## What's out of scope (v1)

- Network replication.
- Off-hand items and dual-wield (the slot model accommodates them; anim
  IK is a v2 cost).
- Visible armor meshes on body sockets (passive items are stat-only in v1).
- Inventory grid layout and item combination (inventory's concern).
- Weapon attachments (separate system).
- Item upgrades and weapon levelling (separate systems).

## Open questions

- Starter equipment ownership. Should the equipment component keep its own
  StarterEquipment list, or should starting gear route through the inventory
  acquire library so inventory owns item creation and equipment only slots?
- Pre-spawn vs lazy-spawn of slot actors. Current behaviour pre-spawns
  in-hand actors on assign (hidden) so swaps don't hitch. That means two
  filled in-hand slots own two actors, one of them hidden. Worth the memory?
