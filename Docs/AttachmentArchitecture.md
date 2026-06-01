# Attachment / Weapon-Customization System — Architecture Plan (RE4R-class target)

> Authoritative spec for the Nexus attachment + weapon-upgrade system. Survival-horror,
> RE4R-style. This is a target design used to review and align the existing code.
> Where it conflicts with an offhand instruction, this file wins.

## Locked design decisions (fixed)
- **Two layers of weapon power, one resolved result.**
  - **Attachments** — physical parts (scope, stock, muzzle, magazine, laser) that snap to
    sockets, **change appearance**, and **modify stats**. Swappable at a workbench/merchant.
  - **Upgrades (tune-ups)** — RE4R-style merchant purchases (Power, Ammo Capacity, Reload
    Speed, Fire Rate) that **modify stats only, no mesh**, persisted per weapon instance.
  - The weapon's **effective stat** is a single resolution that folds **base + attachments +
    upgrades**, and every consumer (fire/reload/spread/HUD) reads that one value.
- **Data-driven, composition-first.** Attachments are `UNexusAttachmentDefinition` data assets
  composed of fragments; slots are `FAssemblySlotDefinition` data on the equippable. New
  attachment categories / slots ship as data, not code.
- **Modular & equippable-agnostic.** The assembly never type-checks for "weapon" — any
  equippable (weapon, flashlight, radio) with slots assembles the same way.
- **Runtime on the equipped actor, persisted config on the item instance.** The visual/stat
  tree is rebuilt on the spawned `ANexusEquippedActor`; the *chosen* attachments + upgrades
  live on `UNexusItemInstance` and survive unequip / save / load.
- **Inventory is a leaf.** Inventory persists chosen attachments/upgrades as **opaque**
  per-instance state and must not depend on attachment runtime types. Attachments depend on
  inventory (item instance), never the reverse.

Legend: **KEEP** = already aligned · **CHANGE** = structural rework · **ADD** = new system.

---

## 1. Goals & Scope
A modular, data-driven weapon-customization framework: physical attachments that change a
gun's look and stats, plus persistent merchant upgrades, resolving to a single effective-stat
block and a single animation-override resolution that the weapon runtime consumes.

**In scope (v1):**
- Data-driven slots on the equippable, nested/provided sub-slots, tag-based compatibility (KEEP)
- Attachment definition + fragments (magazine today; scope/laser/stock as data) (KEEP)
- Visual assembly — spawn skeletal/static meshes on sockets, leader-pose for shared skeletons,
  mirror host viewpoint (shadow / first-person) (KEEP)
- Effective-stat resolution = base (fragment `SeedStatTags`) + attachment modifiers +
  **persistent upgrade tags**, clamped, cached, one source of truth (CHANGE — fold in upgrades + clamp)
- Per-action animation overrides (arms + item streams), deterministic deepest-wins (KEEP)
- Persisted attachment tree (incl. nested) + persisted upgrades on the instance (KEEP + ADD upgrades)
- Merchant integration — buy/install attachments, buy tune-up upgrades, all via public API (ADD)
- Gunsmith hooks — catalog of compatible attachments + **stat-delta preview** (CHANGE — add preview)
- NPC weapons assemble from defaults, no UI (KEEP)

**Out of scope in v1 (must stay cheap to add):** the gunsmith *screen* UI flow; networking/
replication; the damage/ballistics model itself (attachments only feed stat values into it);
cosmetic-only skins; per-round magazine visibility (binary loaded/empty by design); attachment
authoring tooling.

## 2. Key Design Decisions

| Decision | Choice | KEEP/CHANGE/ADD |
|---|---|---|
| Slot model | Data `FAssemblySlotDefinition` on the equippable; nested via `ProvidedSlots`; one attachment per slot | KEEP |
| Compatibility | Tag intersection (`ProvidedTags` ∩ slot `AcceptedTags`); `bAcceptsAny` escape hatch | KEEP |
| Attachment data | `UNexusAttachmentDefinition` + `TInstancedStruct<FNexusAttachmentFragment>` | KEEP |
| Stat math | `(base + ΣAdd) × ΠMul`, two-pass; ignore unseeded keys | KEEP |
| Stat sources | base (fragment) + attachment modifiers **+ persistent instance upgrade tags**; one resolution | CHANGE |
| Stat bounds | Per-stat clamp (min/max) after the fold | ADD |
| Visuals | Mesh component per attachment, leader-pose on shared skeleton, viewpoint mirrored | KEEP |
| Animation | Per-action arms/item override, deepest-wins, fragment fallback, cached | KEEP |
| Persistence | Chosen attachments + upgrades on `UNexusItemInstance`; defaults not persisted | KEEP + ADD upgrades |
| Inventory coupling | Inventory stores attachments as **opaque** handles, no attachment-type include | CHANGE |
| Economy | Merchant installs attachments / buys upgrades via public API; owns the shop logic | ADD |
| Discovery | Catalog subsystem + **stat-delta preview** for the gunsmith UI | CHANGE (add preview) |

## 3. Architectural Components
- **`UNexusAttachmentDefinition`** (KEEP): identity, `ProvidedTags`, visual mesh(es),
  `Modifiers`, `ActionOverrides`, `ProvidedSlots`, fragments.
- **`FAssemblySlotDefinition`** (KEEP): `SlotID`, socket, `AcceptedTags`, `bRequired`,
  `DefaultAttachment`. Lives on `FNexusFragment_Equippable::Slots`.
- **Attachment fragments** (KEEP + ADD): `Magazine` today; `Scope` (ADS/FOV/overlay),
  `Laser`/`Light` (beam toggle), `Stock`/`Muzzle` (handling) as data-only additions.
- **`UNexusAssemblyComponent`** (KEEP + CHANGE): owns the runtime tree, mesh spawn/teardown,
  persistence, and resolution. CHANGE: `RebuildStatCache` folds in the instance's persistent
  upgrade stat tags and applies clamps; expose a **preview** that resolves a hypothetical tree.
- **`ANexusEquippedActor::GetEffectiveStat`** (KEEP): the single read consumers use; backed by
  the unified resolution above.
- **Upgrade model** (ADD): persistent per-instance `StatTags` on `UNexusItemInstance` (the
  `UpgradeInstanceStat` primitive on the merchant), folded into the resolution — no new storage.
- **`UNexusAttachmentCatalogSubsystem`** (KEEP + CHANGE): "what fits this slot" discovery;
  CHANGE: add a stat-delta preview helper for try-before-buy.
- **`UNexusMerchantSubsystem`** (ADD, separate): buy/install attachment, buy tune-up upgrade,
  pricing — calls only the public assembly + instance + currency APIs.

## 4. Attachment Lifecycle
Acquire weapon → equip → `RebuildFromInstance` (register slots → fill persisted-or-default
attachments, recursively) → resolve stats/animation lazily on read. Install/detach at runtime
re-spawns the affected meshes, re-persists the player's choice to the instance, and invalidates
caches — on a **live** weapon, no respawn. Defaults fill non-customized slots but never persist.

## 5. Stat Resolution Model
- **One block:** `FResolvedItemStats` = for each seeded key: `(base + ΣAdd) × ΠMul`, then
  **clamp to the stat's authored [min,max]**, then **+ persistent upgrade tags** folded in as
  additional Add/Mul (decide ordering: upgrades treated as Add before the Mul, or as a final
  additive tier — must be explicit and consistent).
- **Single source of truth:** all weapon behavior reads `GetEffectiveStat`; nothing recomputes
  damage/spread/mag-size from the raw fragment.
- **Deterministic & cached:** rebuilt lazily, invalidated on any attach/detach/upgrade/rebuild.
- Modifiers against unseeded stat keys are ignored (no inventing values).

## 6. Compatibility & Slots
- One attachment per slot; replacing detaches the old subtree first.
- A slot accepts an attachment iff `Definition.ProvidedTags` intersects `Slot.AcceptedTags`
  (or `bAcceptsAny`). Nested slots come from the installed attachment's `ProvidedSlots`.
- **Open:** cross-slot constraints (requires/conflicts) beyond one-per-slot.

## 7. Definitions / Fragments / State
KEEP. New attachment type = new `FNexusAttachmentFragment` subtype + a data asset. Per-instance
state (chosen attachments, upgrade tags) lives on `UNexusItemInstance` and rides the existing
save descriptor. Nested attachments persist via dotted slot paths in one flat map.

## 8. Cross-System Integration (decoupling contract)
- **Inventory is the leaf:** it persists attachments/upgrades as opaque per-instance state and
  must not include attachment runtime types. (Today the instance's `Attachments` map is typed to
  `UNexusAttachmentDefinition` — CHANGE to an opaque soft-path / PrimaryAssetId to make the
  module a true leaf, or explicitly bless the seam.)
- **Assembly consumes inventory + equippable fragment**, never the reverse.
- **Merchant/upgrade flows only call** the public assembly (Attach/Detach), the instance
  (SetStat for upgrades), and the currency wallet. No system mutates the attachment tree directly.
- **Effective stats are read, never recomputed**, by weapon abilities, the HUD, and the AI.

## 9. NPC Support
NPC weapons assemble from slot `DefaultAttachment`s (and any authored per-instance config); the
assembly is host-agnostic (it lives on the equipped actor). No gunsmith UI, no upgrade purchases.

## 10. Save / Load
The chosen attachment tree (incl. nested, via dotted slot paths) and the persistent upgrade
stat tags ride the `UNexusItemInstance` save descriptor — the same round-trip weapons already
use. A missing attachment asset degrades gracefully (slot left empty / logged), never a crash.

## 11. UI Hooks
Catalog of compatible attachments per slot (discovery); **stat-delta preview** — resolve the
effective stats for a hypothetical install so the gunsmith can show "+8 damage, −0.2s reload"
before the player commits; install/uninstall + buy-upgrade through the public API. Component
stays UI-shape-agnostic; `OnAssemblyChanged` drives refresh.

## 12. Extension Points (must stay cheap)
- New attachment category → new fragment + data asset. No assembly change.
- New slot → data on the equippable (or a providing attachment). No code change.
- New tune-up stat → a new stat tag + a merchant offer. The resolution already folds it.
- New equippable type with attachments → author slots; the assembly is type-agnostic.
- Replication → component-shaped; the persisted config + stable resolution translate cleanly.

## 13. Acceptance Criteria (definition of done / review yardstick)
1. Attachment runtime depends on no inventory/merchant/UI mutation path — one-way; inventory
   never includes attachment runtime types and stores chosen attachments as opaque state.
2. New attachment category = new attachment fragment + data asset; no assembly code change.
3. New slot = data on the equippable (or a providing attachment); no code change.
4. Slot compatibility is tag-driven (ProvidedTags ∩ AcceptedTags), one attachment per slot,
   nested sub-slots resolve recursively from `ProvidedSlots`.
5. Effective weapon stats fold base (fragment `SeedStatTags`) + attachment modifiers +
   **persistent upgrade tags** into one resolution every consumer reads.
6. Stat math is deterministic — `(base + ΣAdd) × ΠMul` then clamped to authored bounds;
   modifiers/upgrades against unseeded keys are ignored.
7. Player-installed attachments and upgrades persist per item instance and survive
   unequip/save/load; default-fill never persists.
8. Changing an attachment or buying an upgrade on a **live** weapon updates visuals, stats, and
   per-action montage overrides without a respawn.
9. Visual meshes spawn on the correct sockets; shared-skeleton attachments use leader pose;
   viewpoint (shadow / first-person primitive) mirrors the host.
10. Per-action animation overrides resolve deterministically (deepest attachment wins, stable
    tie-break) with a fragment fallback, cached and invalidated on change.
11. Merchant buy/install/upgrade only calls public APIs (assembly attach/detach, instance stat
    tags, currency); the assembly and inventory own no shop logic.
12. The assembly is equippable-agnostic — no weapon-specific type checks anywhere.
13. NPC weapons assemble from defaults with no gunsmith UI; the actor is host-agnostic.
14. Save/load restores the full attachment tree (incl. nested, dotted slot paths) and the
    persistent upgrades; missing attachment assets degrade gracefully.
15. A gunsmith UI can list compatible attachments (catalog) and preview the stat delta of a
    hypothetical install/upgrade before committing, then install via the public API.

## 14. Non-Goals (so a reviewer doesn't flag them as missing)
- Network replication.
- The gunsmith **screen** UI flow / layout (only the hooks are in scope).
- The damage / ballistics model itself (attachments feed stat values into it; they don't own it).
- Cosmetic-only skins / camos.
- Per-round magazine visibility (binary loaded/empty is by design).
- Attachment authoring/import tooling.

## 15. Open Questions (resolve before implementing — do not guess)
- **Attachments as items?** Is an attachment an inventory item (occupies the grid, sellable,
  transferable, consumed on install) or a merchant-menu unlock with no inventory footprint?
- **Upgrade model:** discrete tiers (Power Lv.1–5) or continuous? Per-stat cap? Refundable, and
  do exclusive/final upgrades need a special currency (spinel-style)?
- **Upgrade fold order:** are persistent upgrade tags applied as Add (before the Mul tier) or as
  a separate final tier after attachment Mul?
- **Cross-attachment constraints:** support requires/conflicts (e.g. a scope needs a mount)
  beyond one-per-slot, or keep purely slot-based for v1?
- **Detach destination:** if attachments are items, does detaching return the part to inventory,
  or is install one-way?
