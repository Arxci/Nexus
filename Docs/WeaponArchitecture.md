# Weapon

> Ranged guns AND melee weapons under one system. Composed capabilities,
> shared lifecycle, shared host, shared animation resolution, and one
> uniform damage packet. First-person survival-horror target.

## What the system does

- Hosts ranged and melee weapons through the same equipped actor, abilities,
  and animation pipeline.
- Lets a weapon declare a Ranged capability, a Melee capability, or both. A
  rifle with a bayonet is both. A knife is melee-only. A pistol is ranged-only.
- Resolves every tunable (damage, RPM, spread, mag size, reload time,
  recoil, ADS time, melee damage and range, stamina cost, durability) through
  GetEffectiveStat. Attachments and merchant upgrades apply for free.
- Routes every attack — hitscan, projectile, melee sweep — through one
  FNexusDamageContext and one INexusDamageReceiver.
- Drives behaviour by data: fire mode (Semi, Shotgun, FullAuto, Burst),
  ammo model (Magazine, Pooled, None), capability composition.
- Runs the same code on the player's view-space mesh and an NPC's body mesh
  through INexusEquipmentInterface. No hero-vs-NPC fork.

## How a designer uses it

- A weapon is FNexusFragment_Weapon on a UNexusItemDefinition.
- Set the capability (Ranged, Melee, or both) and the fire mode for ranged.
- Author the action montages via the assembly so attachments can override
  any of them.
- A new fire mode is an ENexusWeaponFireMode value plus a branch in fire
  delivery. No new ability.
- A new hit-delivery (beam, chain, ricochet) is a new strategy emitting the
  same damage packet. No ability change.
- A new damage type is a Damage.Type.* tag plus receiver resistances. No
  weapon change.
- A new tunable stat is a stat tag plus a SeedStatTags entry plus
  (optionally) a merchant upgrade track. The resolution already folds it.
- A new melee weapon is a definition with the Melee capability plus swing
  montages. No code.

## Concepts

### Weapon fragment

FNexusFragment_Weapon. The authored data. Ranged-specific authoring
(ammo, combat, reload, ammo visual, presentation, stat clamps, upgrade
tracks) and melee-specific authoring (swing arc, stamina cost, durability)
are kept separate so a knife isn't authoring RPM and a pistol isn't
authoring a swing arc.

### Weapon abilities

UNexusAbility_Weapon subclasses on the bespoke ASC:

- WeaponFire — branches by fire mode, applies recoil, honours full-auto via
  cooldown re-arm.
- WeaponReload — magazine model; pooled and none added.
- WeaponAim — sets the aiming state tag, tightens spread, gates ADS time,
  toggles laser / reticle.
- WeaponMelee — light and heavy swings, anim-notify hit window, sweep
  detection, stamina cost, durability tick.

### Hit-delivery strategies

The variable is target acquisition; the constant is the damage packet:

- Hitscan — camera-forward trace with per-pellet cone spread, range,
  damage, and falloff from effective stats.
- Projectile — spawn a projectile actor; on impact it builds the same
  context (grenades, bolts, flame).
- MeleeSweep — capsule or sphere sweep during the anim-notify hit window
  from the weapon socket. De-duped per swing.

All three set Instigator, Causer (the equipped actor), DamageTypeTag, base
damage (effective), multiplier (falloff or headshot), HitResult, and
impulse.

### Damage pipeline

A source builds FNexusDamageContext and calls Execute_ReceiveDamage on the
hit actor's INexusDamageReceiver. UNexusHealthComponent applies
GetResistance(DamageType) and GetBoneMultiplier(BoneName), then raises
OnDamageTaken, OnHealthChanged, and OnDeath.

Weak points = high bone multipliers. Immunities = zero resistance.
Headshots and staggers are computed at the source (bone yields multiplier
plus context tags) so AI and FX can branch. Weapons own no health math.

### Effective stats

Every tunable comes from GetEffectiveStat:

- Stat.Weapon.Damage, RPM, MagazineSize, MaxRange, SpreadHip, SpreadADS,
  ADSTime, Recoil*, ReloadDuration.
- Stat.Melee.Damage, Range, Stamina, plus Stat.Durability.

Base values come from the fragment's SeedStatTags. Attachments and merchant
upgrades fold in. Results clamp to authored bounds. Weapons never
recompute a tunable from the raw fragment once an equipped actor exists.

### Ammo models

ENexusWeaponAmmoModel:

- Magazine — Stat.Ammo.InMagazine on the instance; reserve drawn from
  inventory by AmmoIdentityTag. Reload transfers reserve to mag on the
  AmmoTransfer notify.
- Pooled — no magazine; fire decrements a reserve pool directly. Reload
  refills from the pool.
- None — melee or infinite ammo.

### Behaviour component

UNexusWeaponBehaviorComponent. Per-equipped-actor runtime visual state:
chamber round, magazine loaded / empty swap, melee trail and impact,
laser-sight beam, recoil-driven mesh kick.

## Lifecycle

1. Acquire. Equip — the equipment component spawns the equipped actor,
   the assembly rebuilds, and abilities are granted per the equippable
   fragment plus the weapon capability.
2. Ready. The player or AI activates Fire, Aim, Reload, or Melee through
   the ASC.
3. Holster. Switching weapons swaps the active slot; the inactive weapon's
   abilities are disabled, not destroyed.
4. The equipped actor and its behaviour component are the runtime.
5. Chosen attachments, ammo-in-magazine, durability, and upgrades live on
   the item instance and survive unequip, save, and load.

## Actions

Every verb is an ability with the existing lifecycle and tag gating.

- Fire — gated by ammo and cooldown (RPM via effective stat). Blocked while
  Reloading or Swapping. Full-auto re-arms via cooldown while held; semi is
  one-shot-per-press; shotgun fires N pellets; burst fires a fixed count.
- Reload — cancels Fire, plays the host reload montage, transfers reserve
  to magazine on the AmmoTransfer notify (Magazine model) or refills from
  the pool (Pooled).
- Aim — a held state ability. Owns Character.State.Weapon.Aiming, tightens
  spread, gates the ADS-time stat, toggles the laser and reticle. Doesn't
  block Fire.
- Melee — plays a swing montage. An anim-notify-state opens the hit window.
  The sweep strategy collects targets and emits damage with a Stagger or
  Melee context tag. Costs stamina and ticks durability. On a ranged
  weapon this is the contextual bash; on a knife it's the primary attack.

## Animation

- Per-action montages live on FEquippableAnimationSet::Actions and resolve
  through the assembly's override-then-fallback walk — the same path
  attachments hook.
- Timing-critical effects (ammo transfer, melee hit window, shell eject)
  fire from anim notifies.
- The host stream and the item-mesh stream are resolved independently so
  an attachment can override one without overriding the other.

## Recoil and weapon feel

- Recoil values come from Stat.Weapon.Recoil* on the effective-stat block.
- Applied to controller or camera per shot. Attachment and upgrade tunable.
- Camera shake, muzzle FX, chamber-round visuals, magazine loaded / empty
  swap are driven by the behaviour component.

## Decoupling contract

- Weapons consume. They don't own.
- Abilities read the equipment component (active slot, instance), the
  equipped actor (GetEffectiveStat, montage resolution, sockets), the
  assembly (effective stats), the inventory (reserve ammo via the public
  query / remove API), and the damage interface.
- Weapons mutate item state only through the instance's public stat API
  (ModifyStat, SetStat for ammo, durability).
- Attachments feed weapons. Weapons don't reach into the attachment tree.
  A magazine attachment that changes mag size or a muzzle that changes
  spread requires zero weapon code — it's already a stat read.
- Animation is shared, not duplicated. Weapon montages resolve through the
  same override-then-fallback as attachments.
- Damage is one-way. Weapons emit a context; the receiver consumes it.
  Receivers never call back into weapons.

## NPC and AI weapons

NPCs equip the same definitions and run the same abilities through their
own ASC. The equipped actor is host-agnostic, so fire / reload / melee
play on the NPC body mesh with no special path. AI activates abilities
via behaviour logic instead of input. No HUD, no aim reticle, no merchant.
Effective stats may differ (NPC weapons need not carry player upgrades)
but the read path is identical.

## Save and load

- Ammo-in-magazine, durability, and merchant upgrades ride the item
  instance's save descriptor.
- Ability state (cooldown, enabled, activation) is SaveGame on the ability.
- An active Fire, Reload, or Melee reconciles on load — Reload force-ends
  so a save mid-reload restores to a clean ready state, not a stuck
  montage.

## UI and feedback hooks

- Ammo-in-magazine plus reserve count.
- Reticle / laser dot (aim).
- Hit marker on a confirmed damaging hit.
- Weak-point / critical cue.
- Durability for melee weapons.
- Low-ammo / empty state.

All of it reads off the instance stat, the aiming state tag, and the
damage events. Components stay UI-shape-agnostic; the HUD subscribes to
instance and health delegates.

## What's out of scope (v1)

- Network replication and prediction.
- Full ballistics (penetration, ricochet, bullet drop), bullet-time,
  weapon sway and breath holding.
- Dismemberment and gore tech, plus staged finisher cinematics (the melee
  verb is in scope; the cinematic flow is not).
- The gunsmith screen UI and attachment authoring (lives in the attachment
  spec).
- Dual-wield, weapon-mounted equipment beyond attachments, crafting of ammo.

## Open questions

- Capability shape: one FNexusFragment_Weapon with optional ranged and
  melee sub-specs, or separate FNexusFragment_Weapon (ranged) plus
  FNexusFragment_MeleeWeapon sharing a base?
- Melee hit detection: anim-notify-state sweep window (capsule or sphere)
  vs per-frame overlap vs traced arc, and single-target vs cleave?
- Aim model: first-person steady-aim with a laser dot (no FOV change,
  spread tightening plus recoil control) or classic ADS with FOV zoom?
- Projectiles in v1: hitscan plus melee only with projectile as the proven
  extension point, or is a projectile weapon (grenade, bolt) required now?
- Melee durability: do melee weapons degrade? At zero do they break
  (removed) or blunt (reduced damage)? Does firing degrade guns at all?
- Fire modes for v1: is full-auto / burst required now, or semi plus
  shotgun only with the mode enum proven for later?
- Contextual melee: is the post-stagger kick or finisher part of the
  weapon system (a universal Melee ability) or the interaction system?
- Stamina: a dedicated melee stamina resource (a new attribute) or reuse
  an existing one? Where does it live (health component, a stamina
  component, the ASC)?
