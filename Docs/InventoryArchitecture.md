# Inventory

> A spatial, sectioned, case-driven inventory and container framework.
> First-person survival-horror target. Owns item lifetime; every other system reads it through
> a small API and reacts to its events.

## What the system does

- Stores items in a spatial Tetris-style grid: multi-cell rectangles, 90°
  rotation, tight packing.
- Adds non-spatial list sections for Key Items and Treasures, each routed
  by item category, consuming zero grid cells.
- Drives the spatial grid dimensions from the equipped Case item — the
  player upgrades their case to gain more grid.
- Exposes charm slots on the case, with bonuses applied through the same
  passive-effect path armor uses.
- Tags items with a value and sell/buy flags. Treasures take gem sockets
  that raise combined sell value. Weapons accept persistent upgrade tags.
- Persists everything cleanly: grid placement, list sections, sockets,
  upgrades, equipped case, charms, currency.
- Coalesces change events so a batch acquire fires per-item events plus
  exactly one aggregate.
- Survives transfers between containers via stable IDs, not raw pointers.

## How a designer uses it

- A new item category is a new fragment plus a definition asset.
- A new case is a data asset (sets the grid size and the charm slot count).
- A new charm is a data asset with the passive payload.
- A new treasure is a data asset; gem sockets are authored as part of the
  Treasure fragment.
- A new recipe is a data asset registered with the combination subsystem.
- Items route to the right section automatically by their CategoryTags. No
  component edit.
- Giving an item anywhere in the game goes through the acquire library
  facade — single entry point.

## Concepts

### Item definition

UNexusItemDefinition. Authors identity, category tags, base value, sellable
and buyable flags, and the fragments that drive behaviour.

### Item instance

UNexusItemInstance. The per-pickup state. Carries per-instance stat tags
(weapon upgrades, treasure socket values) and the attachment map. No new
storage was needed when upgrades and gem sockets were added — they ride the
existing tag map.

### Fragments

The pieces that compose an item:

- Stackable — items that merge by count when identical.
- Equippable — in-hand items (weapons, flashlights).
- Weapon — weapon-specific authoring on top of equippable.
- Consumable — health, ammo refill, status cures.
- KeyItem — routes to the Key Items list section.
- PassiveEquipment — armor and charm payload (granted abilities, granted tags).
- Treasure — sell value, optional gem sockets, optional set-bonus tag.
- Case — grid width, grid height, charm slot count and types, default-case flag.
- Charm — passive-bonus payload that reuses the PassiveEquipment effect path.
- Valuable (or fields on the definition) — base value, sellable, buyable.

### Inventory component

Owns the section model. Each section is a tuple of section tag, placement
(Spatial or List), and accepted category tags. The Spatial section's
dimensions come from the equipped case. The public API has section-aware
overloads, plus simpler overloads that route to the right section by
category.

### Container subsystem

UNexusItemContainerSubsystem. Owns the item box — save-scoped, level-
independent, shared across save rooms. Also owns the stable-ID to instance
resolver across all containers.

### Merchant subsystem

UNexusMerchantSubsystem. Owns buy, sell, and upgrade flows. Calls only the
public inventory API and reads value and upgrade data. Inventory owns no
shop logic.

### Combination subsystem

UNexusItemCombinationSubsystem with recipe assets. Ammo crafting, herb
mixing, gem-into-treasure socketing. Recipes only read and write inventory
through the public API.

### Acquire library

UNexusInventoryAcquireLibrary. The single "give an item" facade. Routes
to the correct section by category. Every pickup, reward, debug spawn, and
starter item flows through it.

## Capacity model

- The Spatial section's grid is GridWidth times GridHeight, sourced from
  the equipped case. One overlap test underlies every placement and query.
- Items can rotate 90 degrees. A capacity preview matches what acquire will
  actually place.
- List sections (Key Items, Treasures) consume zero grid cells. They're
  ordered, auto-arranged, optionally counted.
- Weight is out of scope. The grid plus case size is the constraint. A
  charm could grant grid, but charms generally modify behaviour, not raw
  cell count.

## Item lifecycle

1. Acquire. Acquire library routes by CategoryTags.
2. Spatial route: merge into a mergeable like-stack, else first-fit with
   rotation. List route: append.
3. Events coalesce through a deferral scope; the outermost scope's flush
   emits per-item events plus exactly one aggregate.
4. A stack merges only when it carries no per-instance customization (no
   stat tags, no attachments). One predicate shared by the merge path and
   CanStackWith.
5. Transfer, consume, drop. Cross-system links survive by stable ID.
6. Case-swap: the spatial section re-lays-out for the new dimensions.
   Items that no longer fit follow the designer-set spill policy (auto-send
   to the box, block the swap, or drop to the world — open question).

## Economy

- Per-item base value plus sellable / buyable flags on the definition.
- Treasure fragment with optional gem sockets. Each socket accepts a gem
  category; filled sockets raise combined sell value. Optional set-bonus
  tag rewards completing a treasure set.
- Currency. Pesetas or spinels. Modelled as a counted container or a
  non-grid wallet (open question).
- Weapon upgrades persist as instance stat tags. No new storage; the
  resolution already folds them.
- Merchant buy / sell / upgrade only calls public APIs and reads value and
  upgrade data. The inventory exposes value and sellable but owns no shop
  logic.

## Case and charms

- The equipped case sets the spatial grid dimensions.
- The case exposes charm slots. Each slot has a type and accepts a charm of
  that type.
- A charm grants passive abilities and owned tags through the host's ASC —
  the same passive-effect path armor uses.
- One mechanism, two surfaces. Equipment routes armor; inventory routes
  charms; both wind up on the host ASC the same way.

## Decoupling contract

- Inventory is the leaf. It never includes equipment, merchant, attachment,
  or UI types.
- Merchant, crafting, and upgrade systems only call public add / remove /
  value APIs and read fragments. They never mutate Items directly.
- Cross-system references (a quest item link, a hotbar slot, a gem
  socketed in a treasure) resolve by stable ID via the container subsystem.
- OnItemRemoved is the consistency contract. Dependents subscribe and react;
  inventory fires and is done.

## NPC support

NPCs use the same component (smaller, single-section, locked UI). Reserve
ammo and drop-on-death loot live in inventory. Reload, drop, loot, and
acquire all discover the component via FindComponentByClass on the actor.
No AI-only path. NPCs ignore case, charm, and merchant sections.

## Save and load

- The player case persists per the existing pattern.
- The item box and the currency wallet persist at save-game / subsystem
  scope. They survive level transitions and are shared across save rooms —
  not on a world actor.
- Equipped-case selection, charm sockets, treasure gem sockets, and weapon
  upgrades ride the existing per-instance descriptor plus stable-ID model.
- Missing-definition items are dropped, never restored as null.
- Restore re-broadcasts each item as OnItemAdded inside one broadcast scope.

## Broadcast contract

Every mutator runs inside a deferral scope. Events flush when the outermost
scope exits, coalescing a batch into per-item events plus exactly one
aggregate. The flush re-checks membership, so a "changed" event for an
item a prior listener removed in the same batch is suppressed. No mutator
broadcasts mid-operation.

## UI hooks

- Section-aware queries (grid vs treasure / key lists).
- One overlap test for all placement and queries.
- Capacity preview that matches actual placement.
- Context menu built from fragment-contributed actions — Use, Combine,
  Sell, Examine, Discard, Socket Gem.
- The case screen shows the grid plus the charm slots.
- The merchant screen is a separate consumer of the value and upgrade hooks.
- Auto-sort or "Optimize" on the spatial section is in scope (timing is
  an open question).

The component stays UI-shape-agnostic. Attaché grid, list, radial — all work.

## What's out of scope (v1)

- Network replication.
- Crafting recipe logic inside the component (it lives in a subsystem;
  only primitives are in scope).
- Item box and loot transfer UI (the container-adoption primitive is in
  scope; the screen is not).
- Equipment slotting and holster lifecycle (separate system).
- Weapon attachment runtime and visuals (separate system; inventory only
  persists the chosen attachments as opaque instance state).
- Merchant screen UI flow, request and reward logic, economy balancing.
- Weight as the primary scarcity axis (supported, off by default).

## Open questions

- Case-swap spill policy. When a smaller case can't hold current items, do
  excess items auto-send to the box, block the swap, or drop to the world?
- Currency model. Pesetas and spinels — a special counted item in the grid,
  a non-grid wallet on the inventory, or owned by the merchant or save
  subsystem?
- Auto-sort / Optimize on the spatial section: v1 or later?
- Item box scope: per-save-slot only, or per-chapter / region variants?
