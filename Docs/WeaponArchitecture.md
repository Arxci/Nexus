# Weapon System — Architecture Plan (RE4R-class target)

> Authoritative spec for the Nexus weapon system: ranged guns AND melee weapons,
> survival-horror, RE4R-style. This is a target design used to review, complete,
> and align the existing (partial) weapon code. Where it conflicts with an offhand
> instruction, this file wins.

The weapon system is a **consumer** of two systems that already exist: the
**equipment/equipped-actor** runtime (spawns the gun, owns the assembly) and the
**attachment/customization** system (`Docs/AttachmentArchitecture.md`), which
resolves the single effective-stat block. This spec does NOT redesign those — it
reads them. Damage flows into the existing `FNexusDamageContext` →
`INexusDamageReceiver` → `UNexusHealthComponent` pipeline, which it also reuses.

## Locked design decisions (fixed)
- **One weapon system, two capabilities, composed — not two systems.** A weapon
  declares a **Ranged** capability, a **Melee** capability, or both. The equip path
  grants the abilities each capability needs. A knife is Melee-only; a pistol is
  Ranged-only; a rifle with a bayonet is both. No parallel "melee weapon" class
  tree — guns and melee share the lifecycle, the host, the animation resolution,
  the damage packet, and the effective-stat read.
- **Actions are abilities on the custom ASC.** Fire, Reload, Aim, Melee (and future
  Special) are `UNexusAbility_Weapon` subclasses activated through
  `UNexusAbilitySystemComponent`. KEEP the existing bespoke ability framework
  (lifecycle, tags, cooldown, SaveGame) — this is NOT Epic GAS and won't become it.
- **Hit delivery is a strategy; the damage packet is uniform.** *How* an attack
  finds targets — **hitscan**, **projectile**, or **melee sweep** — is
  interchangeable. *What* it does to a target is always one `FNexusDamageContext`
  routed to `INexusDamageReceiver`. Every weapon, ranged or melee, ends in that one
  packet. Receivers (`UNexusHealthComponent`) apply resistance + weak-point
  multipliers; weapons never reach into health.
- **Effective stats are read, never recomputed.** Damage, RPM, spread, mag size,
  reload time, recoil, ADS time, melee damage/range/stamina/durability all come
  from `ANexusEquippedActor::GetEffectiveStat` — the single resolution that already
  folds base + attachments + merchant upgrades + clamps. Weapons add new
  `Stat.Weapon.*` / `Stat.Melee.*` keys; they never re-read raw fragment values for
  a tunable stat.
- **Data-driven, host-agnostic.** A weapon is `FNexusFragment_Weapon` data on a
  `UNexusItemDefinition`; behavior is selected by data (fire mode, ammo model,
  capability), not by C++ weapon subclasses. The same fire/reload/melee code drives
  the player's view-space mesh and an NPC's body mesh through
  `INexusEquipmentInterface` — no `Cast<ACharacter>`, no first-person assumption.
- **Animation is resolved, not hardcoded.** Per-action montages (Fire, Reload,
  MeleeLight, MeleeHeavy, AimIn/Out) live on `FEquippableAnimationSet::Actions` and
  resolve through the assembly's override-then-fallback walk — the SAME path
  attachments already hook. Timing-critical effects (ammo transfer, melee hit
  window, shell eject) fire from anim notifies, as reload already does.

Legend: **KEEP** = already aligned · **CHANGE** = structural rework · **ADD** = new.

---

## 1. Goals & Scope
A modular, data-driven weapon framework covering ranged firearms and melee weapons,
where both resolve to the same effective-stat block, the same animation resolution,
and the same damage pipeline. Scarcity-driven, weighty, RE4R-feel combat.

**In scope (v1):**
- Ranged firing — hitscan, semi-auto + shotgun spread today; full-auto / burst as
  data-driven fire modes (CHANGE — only semi/shotgun handled now)
- Aim / steady-aim — sets the aiming state, tightens spread, drives the laser/reticle
  and ADS-time gate (ADD — state + stat seeded, no ability today)
- Reload — magazine model today; pooled model; per-action montage + ammo-transfer
  notify (KEEP magazine, ADD pooled)
- Melee weapons — swing attacks with an anim-notify hit window, sweep hit detection,
  stamina + durability, light/heavy attacks (ADD — declared in enums/tags only)
- Hit delivery abstraction — hitscan / projectile / melee-sweep → one
  `FNexusDamageContext` (CHANGE — fold the inline trace into a strategy; ADD
  projectile + melee)
- Damage pipeline — context → receiver → health, resistances by damage type,
  weak-point (bone) multipliers, headshot/stagger context tags (KEEP, extend)
- Ammo model — magazine (reserve from inventory by `AmmoIdentityTag`), pooled, none
  (KEEP magazine, ADD pooled/none handling)
- Weapon feel — recoil (vertical/horizontal stats seeded), camera shake, muzzle FX,
  chamber-round + magazine visuals (KEEP visuals, ADD recoil application)
- NPC weapons — same fragment + abilities, AI-driven activation, no UI (CHANGE —
  ensure the firing path is host-agnostic end to end)
- HUD/feedback hooks — ammo count, reticle/laser, hit-marker, durability (ADD hooks)

**Out of scope in v1 (must stay cheap to add):** the full ballistics sim (penetration,
ricochet, bullet drop); weapon-sway/breathing systems; dual-wield; the gunsmith
*screen* UI (the attachment spec owns those hooks); dismemberment/gore tech; networked
prediction/replication; contextual finisher *cinematics* (the melee verb is in scope,
the staged finisher animation flow is not).

## 2. Key Design Decisions

| Decision | Choice | KEEP/CHANGE/ADD |
|---|---|---|
| Weapon data | `FNexusFragment_Weapon` on the item definition; behavior from data | KEEP |
| Guns + melee | One system, capability-composed (Ranged and/or Melee); abilities granted per capability | CHANGE |
| Action model | `UNexusAbility_Weapon` subclasses on `UNexusAbilitySystemComponent` | KEEP |
| Fire modes | `ENexusWeaponFireMode` data-driven: Semi, Shotgun today; FullAuto, Burst | CHANGE (add auto/burst) |
| Hit delivery | Strategy: Hitscan / Projectile / MeleeSweep → one damage packet | CHANGE (extract) + ADD |
| Damage packet | `FNexusDamageContext` → `INexusDamageReceiver` (uniform) | KEEP |
| Receiver | `UNexusHealthComponent`: resistance by `Damage.Type`, bone multipliers, death | KEEP |
| Stats | `GetEffectiveStat` only (base + attachments + upgrades + clamp) | KEEP (extend keys) |
| Ammo | `ENexusWeaponAmmoModel`: Magazine, Pooled, None; reserve via inventory ammo tag | CHANGE (add Pooled/None) |
| Melee | Swing ability, anim-notify hit window, sweep, stamina + durability | ADD |
| Aim | Aim ability sets `Character.State.Weapon.Aiming`, gates spread + ADS time | ADD |
| Animation | Per-action montages via assembly override-then-fallback; notify-driven timing | KEEP |
| Recoil | `Stat.Weapon.Recoil*` applied to controller/camera per shot | ADD |
| Persistence | Ammo-in-mag, durability, upgrades on the item instance; ability state SaveGame | KEEP |

## 3. Architectural Components
- **`FNexusFragment_Weapon`** (KEEP + CHANGE): the weapon's authored data. Today:
  `Ammo`, `Combat`, `Reload`, `AmmoVisual`, `Presentation`, `StatClamps`,
  `UpgradeTracks`. CHANGE: split the ranged-specific and melee-specific authoring so
  a knife isn't authoring RPM/magazine and a pistol isn't authoring a swing arc
  (capability composition — see Open Questions for the exact shape).
- **`UNexusAbility_Weapon`** (KEEP): base resolves equipment / instance / definition
  / equipped actor / weapon fragment / host. Subclasses:
  - `UNexusAbility_WeaponFire` (KEEP + CHANGE): branch fire delivery by mode; apply
    recoil; honor full-auto via cooldown re-arm (`RestartCooldown` already hints it).
  - `UNexusAbility_WeaponReload` (KEEP + CHANGE): magazine today; add pooled/none.
  - `UNexusAbility_WeaponAim` (ADD): sets the aiming state, drives reticle/laser,
    ADS-time gate, spread tightening.
  - `UNexusAbility_WeaponMelee` (ADD): light/heavy swing, anim-notify hit window,
    sweep detection, stamina cost, durability tick.
- **Hit-delivery strategies** (CHANGE/ADD): `Hitscan` (extract the current
  `FireOnePellet` camera trace), `Projectile` (spawn + on-hit), `MeleeSweep`
  (capsule/sphere sweep during the notify window). Each emits `FNexusDamageContext`.
- **`UNexusWeaponBehaviorComponent`** (KEEP + ADD): per-equipped-actor runtime visual
  state — chamber round, magazine loaded/empty swap today; ADD melee trail/impact,
  laser-sight beam, recoil-driven mesh kick if desired.
- **`FNexusDamageContext` / `INexusDamageReceiver` / `UNexusHealthComponent`** (KEEP):
  the damage pipeline. Weak points via `BoneDamageMultipliers`, resistances via
  `Resistances`, branchable `ContextTags` (Headshot, Stagger, Critical).
- **`NexusGameplayTags`** (ADD keys): `Stat.Melee.*` (Damage, Range, Stamina*,
  Durability is `Stat.Durability`), `Action.Equipment.Weapon.Melee*`,
  `Ability.Weapon.Melee` (exists), `Character.State.Weapon.Aiming` (exists).

## 4. Weapon Lifecycle
Acquire → equip (equipment component spawns `ANexusEquippedActor`, assembly rebuilds,
abilities granted per the equippable fragment + weapon capability) → ready → the
player/AI activates Fire / Aim / Reload / Melee through the ASC → holster. The
equipped actor and its behavior component are the runtime; the chosen attachments,
ammo-in-mag, durability, and upgrades live on `UNexusItemInstance` and survive
unequip/save/load. Switching weapons swaps the active slot; abilities of the inactive
weapon are disabled, not destroyed.

## 5. The Action Model (abilities)
Every weapon verb is an ability with the existing lifecycle
(`RequestActivateAbility` → `CommitAbility` → Active → `CommitAbilityEnd`) and tag
gating (`ActivationBlockedTags`, `CancelAbilitiesWithTags`, owned-state tags). KEEP:
- **Fire** gated by ammo + cooldown (RPM via effective stat); blocked while
  Reloading/Swapping. Full-auto re-arms via `RestartCooldown` while held; semi is
  one-shot-per-press; shotgun fires N pellets; burst fires a fixed count.
- **Reload** cancels Fire, plays the host reload montage, transfers reserve→mag on the
  `AmmoTransfer` notify (magazine), or refills from the pool (pooled).
- **Aim** is a held state ability: owns `Character.State.Weapon.Aiming`, tightens
  spread (Fire already reads the aiming branch), gates the ADS-time stat, toggles the
  laser/reticle. Does not block Fire.
- **Melee** (light/heavy) plays a swing montage; an anim-notify-state opens the hit
  window; the sweep strategy collects targets and emits damage; costs stamina and
  ticks durability. On a ranged weapon, Melee is the contextual bash; on a knife it
  is the primary attack.

## 6. Hit Delivery (one packet, three strategies)
The variable is *target acquisition*; the constant is the `FNexusDamageContext`:
- **Hitscan** (KEEP, extract): camera-forward trace with per-pellet cone spread,
  range + spread + damage from effective stats, falloff curve → context.
- **Projectile** (ADD): spawn a projectile actor; on impact it builds the same
  context (for grenades, bolts, flame). Keeps the firing ability identical; only the
  delivery differs.
- **MeleeSweep** (ADD): during the anim-notify hit window, sweep a shape from the
  weapon socket; first/all overlapped receivers each get a context with melee damage,
  knockback impulse, and a `Stagger`/`Melee` context tag. De-dupe per swing.
All three set `Instigator`, `Causer` (the equipped actor), `DamageTypeTag`,
`BaseDamage` (effective), `Multiplier` (falloff/headshot), `HitResult`, impulse.

## 7. Stat & Ammo Model
- **Single effective-stat read.** Tunable values come from `GetEffectiveStat`
  (`Stat.Weapon.Damage/RPM/MagazineSize/MaxRange/SpreadHip/SpreadADS/ADSTime/
  Recoil*/ReloadDuration`, and new `Stat.Melee.*`). Base from the fragment's
  `SeedStatTags`; attachments + upgrades fold in; clamped. Weapons never recompute a
  tunable from the raw fragment when an equipped actor exists.
- **Ammo models** (`ENexusWeaponAmmoModel`): **Magazine** — `Stat.Ammo.InMagazine`
  on the instance, reserve drawn from inventory by `AmmoIdentityTag` (KEEP); **Pooled**
  — no magazine, fire decrements a reserve pool directly (ADD); **None** — melee /
  infinite (ADD; melee weapons use this).
- **Durability** (ADD, optional per weapon): `Stat.Durability` on the instance; melee
  swings (and optionally firing) decrement it; at zero the weapon breaks or blunts
  (Open Question). Persists + folds like any instance stat.

## 8. Damage Pipeline
KEEP. A source builds `FNexusDamageContext` and calls `Execute_ReceiveDamage` on the
hit actor's `INexusDamageReceiver`. `UNexusHealthComponent` applies
`GetResistance(DamageType)` and `GetBoneMultiplier(BoneName)`, raises
`OnDamageTaken` / `OnHealthChanged` / `OnDeath`. Weak points = high bone multipliers;
immunities = zero resistance. Headshots/staggers are computed at the source (bone →
`Multiplier` + `ContextTags`) so AI and FX can branch. Weapons own no health math.

## 9. Cross-System Integration (decoupling contract)
- **Weapons consume, never own.** Abilities read the equipment component (active
  slot/instance), the equipped actor (`GetEffectiveStat`, montage resolution,
  sockets), the assembly (effective stats), inventory (reserve ammo via the public
  query/remove API), and the damage interface. They mutate item state only through
  the instance's public stat API (`ModifyStat`/`SetStat` for ammo/durability).
- **Attachments feed weapons, not vice versa.** The weapon reads the resolved stat
  block; it never reaches into the attachment tree. A magazine attachment changing
  mag size or a muzzle changing spread requires zero weapon code — it's already a
  stat read. (This is the seam the attachment system was built for.)
- **Animation is shared, not duplicated.** Weapon montages resolve through the same
  assembly override-then-fallback as attachments, so an attachment can override a
  weapon's reload/fire/melee animation with no weapon-side branch.
- **Damage is one-way.** Weapons → `FNexusDamageContext` → receiver. Receivers never
  call back into weapons.

## 10. NPC / AI Weapons
NPCs equip the same definitions and run the same abilities through their own ASC; the
equipped actor is host-agnostic (`INexusEquipmentInterface`), so fire/reload/melee
play on the NPC body mesh with no special path. AI activates abilities via behavior
logic instead of input. No HUD, no aim reticle, no merchant. Effective stats may
differ (NPC weapons need not carry player upgrades) but the read path is identical.

## 11. Save / Load
Ammo-in-magazine, durability, and merchant upgrades ride `UNexusItemInstance`'s save
descriptor (the same round-trip ammo already uses). Ability state (cooldown, enabled,
activation) is `SaveGame` on `UNexusAbility`; an active Fire/Reload/Melee reconciles on
load via `OnSaveStateRestored` (Reload already force-ends). A weapon mid-reload at save
restores to a clean ready state, not a stuck montage.

## 12. UI / Feedback Hooks
Ammo-in-mag + reserve count, the reticle/laser dot (aim), a hit-marker on a confirmed
damaging hit, a weak-point/critical cue, durability for melee weapons, and the
low-ammo/empty state — all read off the instance stat, the aiming state tag, and the
damage events. Components stay UI-shape-agnostic; HUD subscribes to instance / health
delegates.

## 13. Extension Points (must stay cheap)
- New fire mode → an `ENexusWeaponFireMode` value + a branch in the fire delivery. No
  new ability.
- New hit-delivery (e.g. beam, chain) → a new strategy emitting the same context. No
  ability change.
- New damage type → a `Damage.Type.*` tag + receiver resistances. No weapon change.
- New melee weapon → a definition with the Melee capability + swing montages. No code.
- New tunable stat → a stat tag + `SeedStatTags` + (optionally) a merchant upgrade
  track. The resolution already folds it.
- New equippable that attacks (a thrown bottle) → author the capability + a delivery
  strategy.

## 14. Acceptance Criteria (definition of done / review yardstick)
1. Ranged and melee weapons run through ONE system — shared lifecycle, host,
   animation resolution, damage packet, and effective-stat read — with no parallel
   melee-weapon class tree and no weapon-specific `Cast` in the firing/melee path.
2. A weapon declares Ranged and/or Melee capability as data; equipping grants exactly
   the abilities that capability needs.
3. Every attack — hitscan, projectile, or melee sweep — ends in one
   `FNexusDamageContext` routed to `INexusDamageReceiver`; weapons contain no health
   or resistance math.
4. Hit delivery is a swappable strategy: changing a weapon from hitscan to projectile
   is data + a strategy, not a rewrite of the fire ability.
5. Every tunable (damage, RPM, spread, mag, reload, recoil, ADS time, melee
   damage/range) is read via `GetEffectiveStat`; none is recomputed from the raw
   fragment when an equipped actor exists, so attachments/upgrades apply for free.
6. Fire modes are data-driven: semi, shotgun (pellets), full-auto (held re-arm via
   cooldown), and burst all work from `FireMode` with no per-weapon subclass.
7. Reload supports magazine (reserve from inventory by `AmmoIdentityTag`, ammo-transfer
   notify) and pooled; melee/none weapons never offer reload.
8. Melee weapons attack with an anim-notify hit window + sweep detection, cost stamina,
   tick durability, and support light/heavy; a ranged weapon can also melee-bash.
9. Aim sets `Character.State.Weapon.Aiming`, tightens spread, gates ADS time, and drives
   the reticle/laser — without blocking Fire.
10. Recoil from `Stat.Weapon.Recoil*` is applied per shot and is attachment/upgrade
    tunable.
11. Weak points (bone multipliers) and damage-type resistances resolve on the receiver;
    headshot/stagger/critical are conveyed via `Multiplier` + `ContextTags`.
12. Ammo-in-mag, durability, and upgrades persist per instance and survive
    unequip/save/load; an ability saved mid-action reconciles to a clean ready state.
13. NPC weapons use the same fragment + abilities on the AI's ASC with no player-only
    path; the equipped actor is host-agnostic.
14. The weapon system depends one-way on equipment/attachments/inventory/damage; none
    of those depend on the weapon runtime, and weapons mutate item state only through
    public instance APIs.
15. A HUD can show ammo/reserve, reticle, hit-marker, weak-point cue, and melee
    durability purely from instance stats, the aiming state tag, and damage events.

## 15. Non-Goals (so a reviewer doesn't flag them as missing)
- Network replication / prediction.
- Full ballistics (penetration, ricochet, bullet drop), bullet-time, weapon sway/breath.
- Dismemberment / gore tech and staged finisher cinematics (the melee *verb* is in
  scope; the cinematic flow is not).
- The gunsmith *screen* UI / attachment authoring (owned by `Docs/AttachmentArchitecture.md`).
- Dual-wield, weapon-mounted equipment beyond attachments, crafting of ammo.

## 16. Open Questions (resolve before implementing — do not guess)
- **Capability shape:** one `FNexusFragment_Weapon` with optional `Ranged` / `Melee`
  sub-specs, or separate `FNexusFragment_Weapon` (ranged) + `FNexusFragment_MeleeWeapon`
  sharing a base? (Affects authoring + which abilities are granted.)
- **Melee hit detection:** anim-notify-state sweep window (capsule/sphere sweep) vs
  per-frame overlap vs a traced arc — and single-target (first hit) vs cleave (all in
  the arc)?
- **Aim model:** RE4R over-the-shoulder steady-aim with a laser dot (no FOV change,
  spread tightening + recoil control), or classic ADS with FOV zoom? Both?
- **Projectiles in v1?** Hitscan + melee only for v1, with projectile as the proven
  extension point, or is a projectile weapon (grenade/bolt) required now?
- **Melee durability:** do melee weapons degrade (RE4R knife), and at zero do they
  break (removed) or blunt (reduced damage)? Does firing degrade guns at all?
- **Fire modes for v1:** is full-auto/burst required now, or semi + shotgun only with
  the mode enum proven for later?
- **Contextual melee:** is the post-stagger kick/finisher part of the weapon system
  (a universal Melee ability) or the interaction system? v1 boundary?
- **Stamina:** dedicated melee stamina resource (new attribute) or reuse an existing
  one? Where does it live (health component, a stamina component, the ASC)?
