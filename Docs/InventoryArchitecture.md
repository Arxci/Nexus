# Inventory System — Architecture Plan (RE4R-class target)

> Authoritative spec for the Nexus inventory system. Survival-horror, RE4R-style.
> This is a target design used to review and align the existing code.

## Locked design decisions (fixed)
- **Capacity:** Spatial "Tetris" grid — multi-cell rectangles, 90° rotation, tight packing.
- **Key items & treasures:** stored in **separate non-spatial list sections** that consume
  **zero** grid cells (Village/RE4R behavior). The container is sectioned: 1 spatial grid
  section + N list sections, items routed by `CategoryTags`.
- **Merchant/economy:** **Yes** (Duke / RE4R-style). Items carry value; treasures are
  sellable and can take gem sockets; weapons have persistent upgrade state. Inventory owns
  the value/upgrade **data** + sell/buy primitives; the shop **flow** lives in a separate
  subsystem.
- **Case & charms:** **Yes.** The equipped **case** item sets the spatial grid dimensions
  and exposes charm slots; charms grant passive bonuses through the **same passive-effect
  path as armor** (host ASC via the equipment / PassiveEquipment mechanism), not a parallel
  system.

Legend: **KEEP** = already aligned · **CHANGE** = structural rework · **ADD** = new system.

---

## 1. Goals & Scope
A spatial, **sectioned**, case-driven inventory + container framework for a single-player
RE4R-style survival horror game, with a decoupled **merchant/economy** and **case/charm**
layer. Inventory remains the **single owner of item lifetime**; equipment, weapons,
attachments, crafting, merchant, and UI reference items and react through a small API +
events — never reaching into each other.

**In scope (v1):**
- Spatial "Tetris" grid — multi-cell rectangles, 90° rotation, tight packing (KEEP)
- Sectioned container — one spatial grid section + non-spatial list sections for **Key
  Items** and **Treasures**, each routed by item category (CHANGE)
- Case as an item — the equipped case sets the grid dimensions and exposes **charm slots**;
  charms grant passive bonuses (ADD)
- Definition + Instance + Fragment model; stacks; per-instance state; partial-fill; transfer (KEEP)
- Economy hooks — per-item value, sellable/buyable flags, treasure **gem-sockets**,
  currency containers, weapon **upgrade** state (ADD)
- Stable, save-safe, location-independent item references (CHANGE — handle vs raw pointer)
- Coalesced change events; capacity preview; attaché UMG queries (KEEP)
- One container type reused for player case, **item box/stash**, and loot (CHANGE — box is subsystem-owned)
- NPC support; first-pickup ceremony; save/load (KEEP)

**Out of scope in v1 (must stay cheap to add):** the merchant *screen* UI and request/reward
logic (economy *hooks* are in scope; the shop flow is separate), multiplayer/replication,
equipment holster lifecycle (`NexusEquipment*`), attachment runtime/visuals
(`NexusAttachment*`; inventory only persists chosen attachments as instance state),
economy balancing.

## 2. Key Design Decisions

| Decision | Choice | KEEP/CHANGE/ADD |
|---|---|---|
| Capacity | Spatial Tetris grid, rotation, multi-cell | KEEP |
| Container shape | Multiple sections: 1 spatial grid + N list sections (Key Items, Treasures); routed by `CategoryTags` | CHANGE |
| Grid size source | Equipped **case** item drives `GridWidth×Height`; not a fixed component property | CHANGE |
| Charms | Case has charm slots; charms grant passive bonuses via the armor/`PassiveEquipment` path | ADD |
| Economy | Value/sellable on definition; **Treasure** fragment w/ gem sockets; currency as counted container; weapon upgrade = persistent instance stat tags | ADD |
| Crafting/ammo | Separate combination subsystem + recipe assets calling the public API | ADD |
| Cross-system ref | Stable item **ID/handle**, not raw `UNexusItemInstance*` | CHANGE |
| Coupling | One-way: every system → inventory; inventory is a leaf | KEEP (principle) |
| Item box | Save/subsystem-owned, level-independent, shared across save rooms | CHANGE |
| Persistence | Flat descriptors + stable ID | KEEP |

## 3. Architectural Components
- **`UNexusItemDefinition`** (KEEP + ADD fields): add `BaseValue`, `bSellable`/`bBuyable`;
  section routing comes free from existing `CategoryTags`.
- **`UNexusItemInstance`** (KEEP): already carries the per-instance `StatTags` and
  `Attachments` maps that weapon **upgrades** and treasure **gem-sockets** write into — no
  structural change, just new tag keys.
- **Fragments** (KEEP + ADD): existing `Stackable/Equippable/Weapon/Consumable/KeyItem/
  PassiveEquipment`, plus:
  - **`Treasure`** — base value, optional gem **sockets** (each accepts a gem category;
    filled sockets raise combined sell value), optional set-bonus tag.
  - **`Case`** — `GridWidth×Height`, charm-slot count/types, default-case flag.
  - **`Charm`** — passive bonus payload (granted tags/abilities), reusing the
    `PassiveEquipment` effect path so charms and armor share one mechanism.
  - Item value/sellable/buyable on the definition (or a `Valuable` fragment); weapon upgrade
    = persistent instance `StatTags` (no new storage).
- **`UNexusInventoryComponent`** (CHANGE): gains a **section model** — each section is
  `{ SectionTag, Placement = Spatial|List, accepted CategoryTags }`. The Spatial section's
  dimensions are pulled from the equipped case. Public API gains section-aware overloads but
  keeps the simple ones (default to the right section by category).
- **`UNexusItemContainerSubsystem`** (ADD): owns the **item box** (save-game/subsystem-
  scoped, level-independent) and the **stable-ID → instance resolver** across all containers.
- **`UNexusMerchantSubsystem` + offer/upgrade assets** (ADD, separate): buy/sell/upgrade by
  calling the public inventory API and reading value/upgrade data.
- **`UNexusItemCombinationSubsystem` + recipe assets** (ADD, separate): ammo crafting, herb
  mixing, gem→treasure socketing — recipes that only read/write inventory via the public API.
- **`UNexusInventoryAcquireLibrary`** (KEEP): still the one "give an item" façade; now routes
  to the correct section by category.

## 4. Item Lifecycle
Acquire → route to section by `CategoryTags` → (Spatial: merge-then-first-fit with rotation;
List: append) → coalesced events. Transfer, consume, save/load as in the existing core.
**New:** equipping a different **case** re-lays-out the spatial section; items that no longer
fit follow the designer **spill policy** (see Open Questions).

## 5. Capacity Model
- **Spatial section:** `GridWidth×Height` **comes from the equipped case**; one overlap test
  underlies all placement/queries (single source of truth). Rotation in scope.
- **List sections (Key Items, Treasures):** no spatial footprint; ordered/auto-arranged
  lists, optionally counted. Do **not** consume grid space.
- Weight: out (space + case size is the constraint). Charms modify effective behavior, not
  raw cell count, unless a charm explicitly grants grid.

## 6–7. Definitions / Stacks / State
KEEP. Weapon **upgrades** and treasure **gem values** are new `StatTag` keys on the instance
— they persist and broadcast automatically, no new storage. Gunpowder/resources/recipes are
ordinary stackable grid items. A stack merges only when it carries no per-instance
customization (no stat tags, no attachments) — one predicate shared by the merge path and
`CanStackWith`.

## 8. Cross-System Integration (decoupling contract)
- Inventory stays the **leaf** — never includes equipment/merchant/attachment/UI types.
- **Case/charm bonuses** route through the **same** passive-effect path as armor (grant
  tags/abilities to the host ASC), so equipment and inventory share one mechanism.
- Merchant/crafting/upgrade systems **only** call the public add/remove/value API and read
  fragments — they never mutate `Items` directly.
- Cross-system links (equipment slot, quest, hotbar, a gem socketed in a treasure) resolve by
  **stable ID** via the container subsystem.
- `OnItemRemoved` is the consistency contract: dependents subscribe and react; inventory
  fires and is done.

## 9. NPC Support
Enemies use the same component (smaller / single-section / locked UI); reserve ammo +
`bDropOnDeath` loot live in inventory; reload, drop, loot, acquire all discover it via
`FindComponentByClass`. No AI-only path. NPCs ignore case/charm/merchant sections.

## 10. Save / Load
KEEP for the player case; **CHANGE** scope: the **item box and currency persist at
save-game/subsystem scope** (not on a world actor), surviving level transitions and shared
across save rooms. Equipped-case selection, charm sockets, treasure gem sockets, and weapon
upgrades ride the existing per-instance descriptor + stable-ID model. Missing-definition
items are dropped, never restored as null. Restore re-broadcasts each item as `OnItemAdded`
inside one broadcast scope.

## 11. UI Hooks
Section-aware queries (grid vs treasure/key lists); one overlap test for all
placement/queries; capacity preview that matches actual placement; context menu built from
**fragment-contributed actions** (Use / Combine / Sell / Examine / Discard / Socket Gem). Case
screen shows grid + charm slots. Merchant screen is a separate consumer of the value/upgrade
hooks. Auto-sort / "Optimize" on the spatial section is in scope (see Open Questions for
timing). Component stays UI-shape-agnostic.

> **Broadcast contract:** every mutator runs inside a deferral scope; events flush when the
> outermost scope exits, coalescing a batch into per-item events + exactly one aggregate. The
> flush re-checks membership so a "changed" for an item a prior listener removed in the same
> batch is suppressed (no phantom events). No mutator broadcasts mid-operation.

## 12. Extension Points (must stay cheap)
- New item category → new fragment + a definition asset. No component change.
- New case / charm / treasure / recipe → a new data asset.
- Merchant requests / rewards → extend the merchant subsystem; inventory untouched.
- Weight as primary → enable the flag + set a capacity; the clamp path already exists.
- Durability / examine / quick-heal → a new stat tag and/or a fragment-contributed action.
- Replication → component-shaped; descriptor model + ID identity translate cleanly.

## 13. Acceptance Criteria (definition of done / review yardstick)
1. `UNexusInventoryComponent` depends on no equipment/merchant/attachment/UI type — one-way.
2. New item category/case/charm/treasure/recipe = data only, no component code change.
3. The spatial section's dimensions come from the equipped case item; changing the case
   re-lays-out the section (per the chosen spill policy).
4. Key items and treasures occupy list sections and consume zero grid cells.
5. Spatial acquire merges into mergeable like-stacks → first-fits with rotation; list acquire
   appends; capacity preview exactly equals what acquire will place.
6. An instance with stat tags/attachments/sockets never auto-merges (one predicate gates both
   merge and can-stack).
7. Treasure gem-socketing raises combined sell value and persists per-instance.
8. Merchant buy/sell/upgrade only calls the public API + reads value/upgrade data; inventory
   exposes value & sellable but owns no shop logic.
9. Charm bonuses apply through the same passive-effect path as armor (host ASC), not a
   parallel system.
10. Cross-system references are stable IDs resolving the same instance after save→load and
    after a container transfer.
11. The item box is subsystem/save-scoped, level-independent, shared across save rooms — not a
    world-actor component.
12. Save/load restores grid placement, list sections, sockets, upgrades, equipped case,
    charms, and currency; missing-definition items are dropped.
13. Every mutator coalesces through the deferred broadcast scope — a multi-item add produces
    per-item events + exactly one aggregate, no phantom event for an item removed mid-batch.
14. The same container class serves the player case and the box/loot, differing only by
    section config + equipped case.
15. Giving an item anywhere in the game goes through the acquire façade (one entry point).

## 14. Non-Goals (so a reviewer doesn't flag them as missing)
- Network replication.
- Crafting recipe logic *inside* the component (it lives in a subsystem; only primitives in scope).
- Item box / loot transfer **UI** (the container-adoption primitive is in scope; the screen is not).
- Equipment slotting & holster lifecycle (`NexusEquipment*`).
- Weapon attachment authoring/runtime/visuals (`NexusAttachment*`); inventory only persists
  the chosen attachments as opaque instance state.
- Merchant **screen** UI flow, request/reward logic, economy balancing.
- Weight as the primary scarcity axis (supported, off by default).

## 15. Open Questions (resolve before implementing — do not guess)
- **Case-swap spill policy:** when a smaller case can't hold current items, do excess items
  (a) auto-send to the box, (b) block the swap, or (c) drop to the world?
- **Currency model:** are Pesetas/Spinels a special counted item *in* the grid, a non-grid
  wallet on the inventory, or owned by the merchant/save subsystem?
- **Auto-sort / "Optimize"** on the spatial section: in scope for v1 or later?
- **Item box scope:** per-save-slot only, or also per-chapter/region variants?
