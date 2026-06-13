# Attachment & Weapon Customization

> The runtime that bolts physical parts onto weapons (and any other
> equippable) and stacks merchant tune-ups on top. Both layers fold into a
> single effective-stat block and a single animation resolution that every
> consumer reads. First-person survival-horror target.

## What the system does

- Hosts data-driven parts on sockets — scopes, stocks, muzzles, magazines, lasers.
- Changes both the look (a mesh on a socket) and the stats (additive plus multiplicative modifiers).
- Layers persistent merchant tune-ups (Power, Reload Speed, Ammo Capacity, Fire Rate) on top.
- Resolves base, attachments, and upgrades into one effective-stat block.
- Resolves per-action animations the same way, deepest-attachment-wins with a fragment fallback.

## How a designer uses it

- An attachment is a UNexusAttachmentDefinition data asset.
- A slot is a FAssemblySlotDefinition on the equippable's fragment.
- A slot accepts an attachment when their tags intersect — slot AcceptedTags meets attachment ProvidedTags.
- Slots can be nested: a mount attachment provides further sub-slots a scope can fill.
- A new attachment category is a new fragment subtype plus a data asset; no assembly code changes.
- A new slot is data on the equippable; no code changes.
- A new tune-up stat is a new gameplay tag plus a merchant offer; the resolution already folds it.

## Concepts

### Attachment definition

Carries identity tags, the visual mesh, stat modifiers, action animation
overrides, optional provided sub-slots, and one or more fragment subtypes
that specialise behaviour (magazine, scope, laser, light, stock, muzzle).

### Slot definition

Lives on the equippable's fragment. Carries a slot ID, the host socket name,
an accepted-tags filter, a required flag, and a default attachment. Default
attachments fill empty slots so an NPC weapon always assembles complete,
and defaults are never persisted to the inventory.

### Assembly component

Owns the runtime tree on the equipped actor. Spawns and tears down meshes,
leader-poses shared skeletons, mirrors the host's viewpoint, persists
chosen attachments back to the item instance, and rebuilds the cached
effective-stat block on demand.

### Effective stats

The single value every consumer reads. Computed as
(base + sum of additive) times product of multiplicative, then clamped to
the stat's authored bounds, then folded with persistent upgrade tags as a
final additive tier. Weapon abilities, the HUD, and the AI all call
GetEffectiveStat instead of inspecting fragments or attachments directly.

### Persistent upgrades

Stored as per-instance stat tags on the item instance. They survive unequip,
save, and load alongside the chosen attachments. They have no mesh and no
animation effect — stats only — and they fold into the resolution as a final
additive tier.

### Attachment catalog

A subsystem that answers "what attachments fit this slot?" for a gunsmith
UI. Exposes a stat-delta preview so the UI can show "+8 damage, -0.2s reload"
before the player commits to an install or an upgrade.

## Lifecycle

- Acquire a weapon.
- Equip it. The assembly rebuilds from the persisted attachment tree, fills
  empty slots with defaults, registers nested sub-slots recursively.
- Read stats lazily. Cached; invalidated on any attach, detach, or upgrade.
- Install or buy at a workbench. The assembly re-spawns the affected mesh,
  re-persists the player's choice, and invalidates the stat cache.
- Unequip. Per-instance state (attachments and upgrade tags) rides the item
  instance back to the inventory.
- Save and load. The full attachment tree (nested, via dotted slot paths)
  and the persistent upgrade tags ride the item instance's save descriptor.

## Animation overrides

- Per-action montages (Fire, Reload, MeleeLight, MeleeHeavy, AimIn, AimOut)
  resolve through the assembly with override-then-fallback.
- Deepest attachment wins; a stable tie-break keeps the result deterministic.
- The host stream and the item-mesh stream are resolved independently.
- The fragment's authored montage is the fallback when nothing overrides.
- Results are cached and invalidated on any tree change.

## Decoupling contract

- Inventory is the leaf. It persists chosen attachments as opaque per-instance
  state and includes no attachment runtime types.
- The assembly consumes inventory and the equippable fragment. Inventory
  never reaches into the assembly.
- The merchant and the gunsmith only call the public assembly API
  (attach, detach), the item instance (set stat tags for upgrades), and
  the currency wallet. Neither owns shop or upgrade logic in the assembly.
- The damage and HUD systems read GetEffectiveStat. They never recompute a
  tunable from a raw fragment.
- The assembly is equippable-agnostic. No code path type-checks for "weapon".

## NPC support

NPC weapons assemble from slot DefaultAttachment values plus any authored
per-instance overrides. The assembly lives on the spawned equipped actor,
which is host-agnostic — no gunsmith UI, no upgrade purchases.

## Save and load

The chosen attachment tree (including nested sub-slots via dotted slot paths)
and the persistent upgrade stat tags ride the item instance's save descriptor.
A missing attachment asset degrades gracefully — the slot is left empty and
logged, never a crash.

## UI hooks

The gunsmith UI reads:

- The catalog of compatible attachments per slot.
- The stat delta of a hypothetical install or upgrade (preview before commit).
- Install, uninstall, and buy-upgrade through the public API.

The assembly stays UI-shape-agnostic. An OnAssemblyChanged delegate drives
the refresh.

## What's out of scope (v1)

- The gunsmith screen UI flow and layout (only the hooks are in scope).
- Network replication.
- The damage / ballistics model itself (attachments only feed stat values into it).
- Cosmetic-only skins and camos.
- Per-round magazine visibility (binary loaded / empty by design).
- Attachment authoring and import tooling.

## Open questions

- Are attachments inventory items (occupy the grid, sellable, transferable)
  or merchant-menu unlocks with no inventory footprint?
- Upgrade model: discrete tiers (Power Lv.1-5) or continuous? Per-stat cap?
  Refundable? Do exclusive or final upgrades need a separate currency?
- Upgrade fold order: are persistent upgrade tags applied before the
  attachment Mul tier, or as a separate final additive tier after?
- Cross-attachment constraints — a scope needing a mount, two muzzles
  conflicting — or stay purely slot-based for v1?
- Detach destination: if attachments are items, does detaching return the
  part to inventory, or is install one-way?
