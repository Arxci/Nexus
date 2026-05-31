# Equipment System — Architecture Plan

> Authoritative spec for the Nexus equipment system. Survival-horror, RE7 / RE Village /
> RE4R-style. This reflects the system as built (post-refactor) and is the yardstick for
> reviewing/aligning the code. Inventory is a sibling system; see InventoryArchitecture.md.

## 1. Goals & Scope
A reusable equipment system for a single-player survival horror game. Hosts in-hand items
(guns, melee, throwables) and passive items (armor, charms) on **any** actor — player or NPC
— through a unified, data-driven slot abstraction. The component owns per-slot runtime state
only; it never owns items (those live in the inventory) and never hard-references a concrete
character class (it talks to its host through an interface).

**In scope (v1):**
- Designer-configurable slots per character (a loadout **data asset**)
- Slot ↔ item compatibility filtering via gameplay tags
- In-hand items with a full holster/unholster lifecycle, including a "ceremony" unholster
  (weapon inspect / first-pickup flourish)
- Passive items that apply effects while assigned (no holster lifecycle, no in-world actor)
- A single active in-hand item at a time
- Inventory → slot assignment from the UI
- NPC support — works for any actor that implements the host interface
- Save / load of slot assignments and active state

**Out of scope in v1 (design must not foreclose them):**
- Off-hand item (flashlight + knife combos) — the slot model accommodates; anim/IK is a v2 cost
- Visible armor meshes on body sockets — passive items are stat-only in v1
- Multiplayer / replication
- Crafting / item combination (inventory's concern)
- Weapon attachments (separate `NexusAttachment*` system)

## 2. Key Design Decisions

| Decision | Choice | Why |
|---|---|---|
| Armor model | Unified — the same slot system handles in-hand and passive | One abstraction; the slot config decides the mode; cheap to add visible armor later |
| Slot configuration | Per-character `UNexusEquipmentLoadout` data asset | Designers add slots without code; each NPC class gets its own loadout |
| Slot ↔ item compatibility | Typed by gameplay tags (slot `AcceptedItemTags` ∩ item `CategoryTags`) | Reuses the existing tag system; UI can grey incompatible targets; prevents nonsense |
| Off-hand | Single active in v1; slot model open to off-hand later | Anim BP / hand-IK stays simple; the model itself needs no rewrite |
| Owner coupling | Talks to the host through `INexusEquipmentInterface` | Mirrors `INexusAbilitySystemInterface`; non-character actors (turret, deployable) can host equipment |
| Transition driver | Phase advances on montage **blend-out**, never on a timer or anim notify | No one-frame idle pop; animators don't have to hit a frame; transitions always complete |
| Interruptibility | **Non-interruptible**: a draw/holster always plays to completion; presses during a transition are dropped (not queued) | Deliberate, weighty weapon handling; spam-clicking can't stack actions or cut an animation short |

## 3. Architectural Components

**`INexusEquipmentInterface` — host contract.** The interface any equipment-hosting actor
implements. Mirrors `INexusAbilitySystemInterface` in style:
- `USkeletalMeshComponent* GetEquipmentAttachMesh() const` — where the active item attaches.
- `UAnimInstance* GetAnimInstance() const` — which AnimInstance montages play on.
- `float PlayMontage(UAnimMontage*) const` — non-virtual convenience on the I-class.

`ANexusCharacterBase` implements it and returns the **body** mesh / body anim instance (NPC
default). The hero overrides **both** to return its **first-person arms** mesh + arms anim
instance, so the held item attaches to the arms and all montages (equip *and* weapon
fire/reload) play on the arms. `UNexusEquipmentComponent` and the weapon abilities cast the
owner to the interface, never to a concrete character class.

**`UNexusEquipmentLoadout` — primary data asset.** Defines the slots a character has; one
asset per character class. Each `FNexusEquipmentSlotDef` carries:
- `FGameplayTag SlotTag` (e.g. `Equipment.Slot.Primary`) — the runtime key
- `FText DisplayName`, `TSoftObjectPtr<UTexture2D> Icon` — the slot's UI label/glyph
- `FGameplayTagContainer AcceptedItemTags` — item categories this slot accepts (empty = any
  item of the slot's mode)
- `bool bIsPassive` — true → armor/charm mode; false → in-hand mode
- `int32 SortOrder` — UI ordering and the cycle-next/prev step order
- `FName DefaultInputActionHint` — advisory only; the real binding lives in the input config

**`UNexusEquipmentComponent` — the host component.** Owns per-slot runtime state keyed by
`SlotTag`, with the slot list read from the loadout (never hardcoded). Per slot
(`FNexusEquipmentSlotState`): `Assigned` (pointer into inventory; never owned here),
`InWorld` (the spawned in-world actor; null for passive), `GrantedAbilities` + `GrantedTags`
(what was pushed to the host ASC, removed on clear), `Phase`, `bPassive`.

**`ANexusEquippedActor` — the in-world item actor.** Spawned for an active in-hand item;
attaches to the host's `GetEquipmentAttachMesh()` at the item's
`FNexusFragment_Equippable::AttachSocket` (default `ik_hand_gun`). Resolves montages through
its assembly: `GetEffectiveHostMontage(ActionTag)` (plays on the host's animated mesh) and
`GetEffectiveItemMontage(ActionTag)` (plays on the gun's own mesh). Passive items never spawn one.

**`EUnholsterStyle { Normal, Ceremony }`** — selects which unholster montage a draw plays.

**`EEquipmentSlotPhase { Idle, Unholstering, Active, Holstering }`** — the per-slot lifecycle
state. Passive slots stay `Idle`.

**Item fragments.**
- `FNexusFragment_Equippable` (existing) — marks an item in-hand-equippable; carries
  `AttachSocket`, the action→montage map (via the assembly), `EquippedActorClass`, `WorldMesh`,
  granted abilities, owned tags, `AllowedSlots`/`PreferredSlot`/`bAllowAutoAssign`.
- `FNexusFragment_PassiveEquipment` (new) — armor/charm: `GrantedAbilities` +
  `GrantedTags` applied through the host ASC while assigned. No actor, no montage.

An item with the equippable fragment goes in in-hand slots; an item with the passive fragment
goes in passive slots. Mode is decided by the slot, routed by the fragment.

## 4. Slot Lifecycle (in-hand item)
```
Empty ──Assign──▶ Idle ──Activate(Normal)────▶ Unholstering ──(montage blend-out)──▶ Active
                  │  └──Activate(Ceremony)───▶ Unholstering(Ceremony) ──blend-out──▶ Active
                  ▲                                                                    │
                  └──(blend-out)── Holstering ◀── Activate(active slot) / Clear / item gone
```
- **Single-active invariant:** only one in-hand slot is `Active` at a time. Activating slot B
  while A is active chains holster A → unholster B.
- **Non-interruptible:** while a transition is in flight (`IsSwapping()`), `RequestActivateSlot`
  and `RequestDeactivateActiveSlot` return false — presses are **dropped, not queued**. A draw
  or holster always plays to completion.
- **Advancement is montage-blend-out-driven:** `FinishHolsterPhase` / `FinishDrawPhase` fire
  from the montage's *blending-out* delegate (so the next montage cross-fades in and the
  outgoing actor hides before the pose resolves to idle — no one-frame pop). Each Finish is
  guarded by a phase check so a late/duplicate call is a no-op. Missing montage → instant
  transition (still works for items without animations).
- **Action → montage lookup:** the slot resolves `Action.Equipment.Holster`,
  `Action.Equipment.Unholster`, and `Action.Equipment.Ceremony` through the equipped actor's
  assembly. Ceremony falls back to the normal unholster when an item doesn't author one.
- **Passive slots short-circuit:** assign applies effects immediately; clear removes them. No
  Unholstering/Active/Holstering phases.
- **No double-spawn:** assignment finalize and effect-application are idempotent — a slot can
  never own two in-world actors.

## 5. Input → Slot Activation
- The player binds an Input Action per slot tag. Tap vs hold is distinguished by an Enhanced
  Input **Hold** trigger: tap (Canceled) → `RequestActivateSlot(Slot, Normal)`; hold past the
  trigger threshold (Triggered) → `RequestActivateSlot(Slot, Ceremony)`. The ceremony threshold
  lives on the Input Action asset, not in C++.
- Pressing the active slot's key again → `RequestDeactivateActiveSlot()` (true toggle to empty
  hands).
- Pressing a different slot's key → swap (holster current, unholster new). Toggle semantics
  scope to the same slot.
- Passive slots have no input action — they're always "on" while assigned.
- NPC controllers bypass input and call `RequestActivateSlot` directly.

## 6. Inventory ↔ Equipment Integration
- Equipment **never owns** items; slots hold a pointer into `UNexusInventoryComponent`,
  discovered via `GetOwner()->FindComponentByClass<UNexusInventoryComponent>()`.
- **Compatibility on assign:** the item's `CategoryTags` must intersect the slot's
  `AcceptedItemTags` (empty = any), and the fragment must match the slot mode. `AssignItemToSlot`
  rejects mismatches with a warning. The UI uses the same check to grey incompatible drop targets.
- **Inventory-item-removed handler:** equipment subscribes to `OnItemRemoved` and clears the
  slot (and deactivates if it was active).
- Cross-system links survive save/load by **GUID**, re-resolved against the restored inventory.
- Ammo is **not** an equipment slot — it lives in inventory and is consumed by reload, RE-style.

## 7. Passive Equipment (armor, charms)
- Identified by `FNexusFragment_PassiveEquipment`; the slot must have `bIsPassive = true` and
  `AcceptedItemTags` matching the item.
- On assign: the component grants the passive abilities + owned tags through the host's ASC
  (looked up via `INexusAbilitySystemInterface`). On clear: removes exactly what it added.
- This is how armor works on day one with zero new visual-asset work. Visible armor (a mesh on
  a body socket) is a v2 extension to the passive fragment; slot logic unchanged.

## 8. NPC Support
- Any actor implementing `INexusEquipmentInterface` can carry equipment. Most enemies inherit
  `ANexusCharacterBase`, so they get it for free (body mesh as the attach + anim target).
- An NPC class is configured with a `UNexusEquipmentLoadout` and an optional starter list
  (`TArray<FNexusStarterEquipped>` mapping slot tag → item definition + a pre-active flag).
- The AI controller calls the same `RequestActivateSlot` API — there is no parallel AI path.
  The component doesn't know or care who's calling.
- The enemy's in-world weapon attaches to the body mesh's `ik_hand_gun` socket; same skeleton,
  same socket name, same anim contract as the hero.

## 9. Animation / IK Contract
- The host's animated mesh carries `ik_hand_gun` (and the hand-IK bones the anim BP locks to).
- The active item's `ANexusEquippedActor` attaches to the host's `ik_hand_gun` via
  `INexusEquipmentInterface::GetEquipmentAttachMesh()`.
- Montages play through the host interface — `Host->PlayMontage(...)` or
  `Host->GetAnimInstance()->Montage_Play(...)`. There is no hero-named montage helper.
- The hero's animated mesh is the **first-person arms** (their own AnimBP); they are NOT a
  leader-pose follower of the body, so they play their own montages. The arms are hidden when
  nothing is in hand (driven by `OnSlotActivated` / `OnSlotDeactivated`).
- Two anim notifies are **polish, not load-bearing** (phase advancement is montage-driven):
  - `NexusAnimNotify_EquipmentAction` — at its frame, plays the item-mesh montage for an action
    (slide/bolt/mag) in lockstep with the host montage. Item-mesh anim only.
  - `NexusAnimNotify_HideOutgoingEquipped` — hides the outgoing weapon mid-holster for a clean
    hand-off. Optional; without it the weapon hides when the holster montage ends.

## 10. Save / Load
- Slot assignments + active state persist via `IEMSCompSaveInterface` on the component.
- Per slot we persist `{ SlotTag → ItemInstanceGUID }` plus the active slot tag; the runtime
  instance pointers can't round-trip through EMS.
- On load (deferred one tick so the inventory restores first): re-resolve each GUID against the
  inventory, re-apply effects (passive grants / in-hand actor spawn), then **silently** re-draw
  the previously-active slot (no montage — no draw plays on level load). A slot whose item is
  gone, or whose tag the loadout no longer exposes, is skipped.

## 11. UI Hooks
UMG queries the component: `GetLoadout()` / `GetSlots()` for layout; `GetAssigned(SlotTag)` /
`IsSlotActive` / `GetActiveSlot` / `GetSlotPhase` for per-slot state; subscribe to
`OnSlotAssigned / OnSlotCleared / OnSlotActivated / OnSlotDeactivated` for live updates.
Inventory drag-drop calls `AssignItemToSlot`; the UI uses `CanAssignToSlot` /
`GetCompatibleSlotsForInstance` (the slot's `AcceptedItemTags`) to grey incompatible targets
during a drag. The component is agnostic to UI shape (quick-slots vs grid).

## 12. Extension Points (deferred work that must stay cheap)
- New slot type / item category → edit the loadout asset + the gameplay tag list. No C++.
- Adding a slot → new tag + new entry in the loadout + (if player-driven) one input binding.
- Off-hand item → add a parallel non-passive slot; the single-active invariant becomes "one
  active per hand-group." Real cost: anim BP gains a second hand-IK chain.
- Visible armor → extend `FNexusFragment_PassiveEquipment` with an optional socket + attach
  mesh; the component spawns an attach component on assign, removes it on clear. Slot logic unchanged.
- Per-slot cooldowns / overrides → already supported via the per-slot phase machine; add states
  without changing the public API.
- Replication → component is a `UActorComponent`; the lifecycle is notify/blend-driven, which
  translates cleanly to state-only replication.

## 13. Acceptance Criteria (the reviewer's checklist)
The equipment system aligns with this plan iff:
1. `UNexusEquipmentComponent` does not `Cast<ANexusCharacterBase>` (or `ACharacter`, or
   `ANexusHeroCharacter`) anywhere. All host access goes through `INexusEquipmentInterface`
   (and `INexusAbilitySystemInterface` for the ASC).
2. A `UNexusEquipmentLoadout` data-asset class exists; the component reads slot definitions from
   it; the slot list is not hardcoded in C++.
3. Adding a new slot requires only a new tag, a new loadout entry, and an input binding — no
   `UNexusEquipmentComponent` code change.
4. `AssignItemToSlot` rejects items whose category tags don't intersect the slot's
   `AcceptedItemTags` (or whose fragment doesn't match the slot mode), and emits a warning.
5. Assigning a passive item to a `bIsPassive=true` slot applies effects via the ASC without
   spawning an in-world actor or playing any montage; clearing removes the effects.
6. Activating slot B while A is active chains Holstering A → Unholstering B; no frame shows both
   equipped actors (the HideOutgoing notify and/or the blend-out hand-off mediate it).
7. Pressing the active slot's input deactivates it (toggle to empty hands). Holding a slot's
   input plays the ceremony unholster; tapping plays the normal one.
8. Transitions are non-interruptible: a press during a draw/holster is dropped, not queued, and
   the animation always plays to completion (no spam-interrupt, no action stacking).
9. Phase advancement is driven by the montage blending out — not a timer, not an anim notify —
   so there is no one-frame idle pop and an item without montages still transitions instantly.
10. A slot never spawns a second in-world actor (finalize/spawn are idempotent).
11. Removing an item from the inventory while it is assigned clears the slot and deactivates it
    if active (via the `OnItemRemoved` hook).
12. The system runs end-to-end on a non-hero actor implementing the interface: spawn an enemy
    with a loadout + starter item, have its AI call `RequestActivateSlot`, and observe the
    in-world weapon on its body mesh's `ik_hand_gun` and fire/reload montages on the body.
13. Save → quit → load restores every slot's assignment and the previously-active slot
    (silently, no draw), including passive effects.
14. No name within `UNexusEquipmentComponent`, the loadout asset, `INexusEquipmentInterface`,
    or `FNexusFragment_PassiveEquipment` contains Hero, Player, FirstPerson, or Arms.
15. Montage playback in equipment / weapon-ability code goes through the host interface
    (`Host->PlayMontage` or `Host->GetAnimInstance()->Montage_Play`) — no dedicated montage-play
    helper sits in a hero-named utility.

## 14. Non-Goals (so a reviewer doesn't flag them as missing)
- Network replication.
- Off-hand items / dual-wield.
- Visible armor meshes attached to body sockets.
- Inventory grid layout, item combinations, ammo crafting (inventory's concern).
- Weapon attachment system (lives in `NexusAttachment*`).
- Item upgrades, weapon levelling, merchant / shop (separate systems).

## 15. Open Questions / Decisions (not yet settled)
- **Starter-equipment ownership:** today the component has a `StarterEquipment` list that
  creates items directly. The cleaner option is to route starting gear through
  `UNexusInventoryAcquireLibrary::AcquireItem` (inventory owns item creation; equipment only
  slots) — which also gives stat-seeding and dedupe for free. Decide whether to keep the
  equipment-side list (NPC convenience) or move creation to inventory/acquire (single source of
  truth). Recommendation: inventory owns creation; equipment slots only.
- **Pre-spawn vs lazy-spawn of slot actors:** in-hand slots currently spawn their actor on
  assign (hidden) so swaps don't hitch. This means two filled in-hand slots legitimately have
  two actors, one hidden. Confirm this is the desired memory/perf trade vs spawning on draw.
