# Nexus Asset Creator (part of the NexusEditor module)

A one-window hub for stamping out Nexus assets and editing them in place — built to kill
the "a lot of windows" problem when authoring a gun and its attachments.

- A **Create** mode toggle (**Item** / **Attachment** / **Recipe** / **Manifest**) keeps the
  lanes separate — you only ever see the controls for what you're making.
  - **Item** mode: pick a template (Ranged Weapon, Melee Weapon, Consumable, Ammo,
    Treasure, Key Item, Charm, Generic) → **Create Item**. You get a **pre-filled**
    `UNexusItemDefinition`: correct category tag, grid footprint, and the right fragments
    already added (a weapon ships with its Equippable + Weapon fragments).
  - **Attachment** mode: pick a type (Sight / Barrel / Magazine / Slide / Trigger) →
    **Create Attachment**.
  - **Recipe** mode: **Create Recipe** → a blank `UNexusCombinationRecipe` you fill in on the
    right (inputs / output).
  - **Manifest** mode: **Build from Current Level** (the level scan) drops the result into the
    working set to review/edit, or **Create Blank**.
- **New attachments auto-slot onto the active item.** If it already has a matching empty
  slot, the attachment fills it; if it has *no* slot of that type, **a slot is added and
  filled** (so "create a Trigger" gives the gun a Trigger slot with a Trigger in it). The
  "Attaches to: …" line shows which item is the target (the last one you created or
  clicked).
- Everything lands in a **working-set list** (left) and opens in an embedded **Details
  panel** (right) — Unreal's own property editor, so every field of every type just works.
- **Browse** picks the destination folder from the content tree. **Save All** writes the
  session to disk. **Delete** discards the selected asset.
- **Hub actions** (toolbar): **Duplicate** clones the selected asset as a variant,
  **Load Selected** pulls in the assets selected in the Content Browser for editing,
  **Auto-tag** derives + registers a unique `IdentityTag` from the asset's name (so you
  never hand-type tags), and **Sort into type folders** routes saves into per-type
  subfolders (Weapons, Attachments, …).
- **Validation + where-used banner** over the details panel — live `IsDataValid` status
  (Valid / warnings / errors, colour-coded) for the selected asset, plus a "Referenced by
  N" count (hover for the list) so you see impact before you change or delete something.

## Headless validation (CI)

The `NexusValidateContent` commandlet runs the full cross-asset audit and returns a
non-zero exit code on errors, so a PR with broken content fails the build:

    UnrealEditor-Cmd.exe <Project>.uproject -run=NexusValidateContent

The same audit also adds **coverage findings** to the dashboard: items in no level manifest
(first equip will hitch) and attachments nothing references.

## CSV balancing round-trip

In the **Dashboard** toolbar, **Export CSV** writes one row per item — identity, footprint,
economy, and the headline weapon stats (Damage / RPM / Mag / Range / Reload / recoil / melee)
— keyed by asset path. Balance the sheet in Excel or Sheets, then **Import CSV** applies it
back: each row is matched to its asset by path, changed cells are written, and the asset is
marked dirty (Save them in the Content Browser afterward). Blank cells are left untouched, so
you can hand-edit a subset of the roster.

## Live assembly stat preview

**Tools → Nexus Assembly Preview**. Pick a weapon, tick the attachments to install, drag the
upgrade-tier spinner, and the **Resolved Stats** table updates live — **Base**, **+Attach**,
**+Upgrade**, and the final **clamped** value side by side. The numbers run through the same
fold the runtime assembly uses (`base → (base + ΣAdd) × ΠMul → + upgrade → clamp`), reusing
your own `SeedStatTags` / `SeedStatClamps`, so what you see is what you'd get in play. A stat
the clamp pulled in is highlighted, so you can spot "stacked muzzle + max upgrade blew past
the ceiling" at a glance.

## Build Level Manifest from the current level

Two entry points — the **Creator's Manifest mode → Build from Current Level**, or **Tools →
Build Level Manifest from Current Level**. Either scans every placed actor in the open level
for referenced item/attachment definitions (a pickup's `Definition`, etc.) and writes them
into the level's manifest — **updating** the one the World Settings already points at, or
**creating** `LM_<Level>` and wiring it onto the World Settings if there isn't one. The
result lands in the **Creator's working set** so you can review/edit before saving. Follows
hard references (placed pickups/spawners); save the manifest (and the level too, if newly
wired).

## Crafting tree

**Tools → Nexus Crafting Tree**. Every craftable item is a root you can expand to see what
it's made from (its recipe's inputs), recursively — so a full chain (gunpowder + resource →
ammo) reads at a glance. Cycles and runaway depth are guarded; double-click a node to open
its recipe. **New Recipe** creates a recipe with its output seeded from the selected node and
hands it to the Creator — fill a gap in the graph without leaving the view.

## Production hardening pass

- **Trustworthy preview (touches the runtime `Nexus` module).** The Assembly Preview's *Final*
  column now resolves through your runtime `FNexusStatResolver::ApplyFold`, which was lifted out
  of `UNexusAssemblyComponent::ResolveStatsInternal` (now calls it too). The fold is a single
  shared function, so the preview can't drift from in-game. This is a **behaviour-preserving
  code move** — the only runtime change in the suite. New files:
  `Source/Nexus/Equipment/Attachments/NexusStatResolver.{h,cpp}`.
- **Safe CSV import.** Import shows a dry-run confirm ("N assets would change; fields: …") and
  applies inside a transaction — **undoable**.
- **Attachment matrix** — **Tools → Nexus Attachment Matrix**: attachments × type tags, with
  **P / R / C** (Provides / Requires / Conflicts) per cell. Read a column for "who provides this
  mount," a row for "what this part needs and fights."
- **Loadout** is now a Creator mode (`UNexusEquipmentLoadout`).
- **Auto-tag Untagged** (Dashboard toolbar) batch-fixes every item/attachment missing an
  IdentityTag, undoable.
- **Localization coverage** — the audit now flags assets with no Display Name (warning) or
  Description (info).

**The inline flow:** Item mode → Create a Ranged Weapon → switch to Attachment → Create a
Sight (auto-slotted onto the weapon) → configure it on the right → click the weapon in the
list to keep going. No Content Browser round-trip, no second editor window.

### What "Save All" does
New assets exist only in memory until saved (they show with a `*` in the Content Browser).
**Save All** writes every asset you've made this session to `.uasset` files under their
folder. Close without saving and unsaved ones are gone.

## Setup

The module is already registered, so this is just updated source files:

1. **Extract the `NexusEditor` folder into `Source/`, overwriting** when prompted.
2. **Regenerate project files** (Rider will offer to reload the project model — accept).
3. **Build** `NexusEditor / Development Editor`.
4. **Restart** the editor → **Tools → Nexus Asset Creator**.

Module dependencies used by the creator (already in `NexusEditor.Build.cs`):
`PropertyEditor`, `AssetTools`, `ContentBrowser`.

## Untested — likely fixup spots (UE 5.7)

I can't compile here. Structure/braces check out, but if the build complains these are the
most likely one-line tweaks (the details panel, instanced-struct fill, and slot mutation
already compiled for you in the previous round, so the new surface is the combos / picker /
delete):

- **`IContentBrowserSingleton::CreatePathPicker` / `FPathPickerConfig`** in
  `SNexusCreatorWindow.cpp` (the Browse button). If it's unhappy, the plain folder text box
  still works — you can delete the `SComboButton` Browse block.
- **`ObjectTools::DeleteObjects`** (the Delete button) from `ObjectTools.h`.
- **`UGameplayTagsManager::AddNewGameplayTagToINI`** (Auto-tag) — registers the derived
  project tag; editor-only.
- **`IAssetTools::DuplicateAsset` / `IContentBrowserSingleton::GetSelectedAssets`**
  (Duplicate / Load Selected).
- **`IAssetRegistry::GetReferencers`** (the where-used count) — if the `FName` overload
  differs in 5.7, switch to the `FAssetIdentifier` overload.
- **`UObject::IsDataValid` / `FDataValidationContext::GetNumErrors`** (the validation
  banner) and **`SearchAllAssets`** (the commandlet).
- **`FCsvParser`** (`Serialization/Csv/CsvParser.h`) and **`IDesktopPlatform::SaveFileDialog`
  / `OpenFileDialog`** (the CSV export/import buttons).
- **`SSpinBox<int32>`** (the upgrade-tier control in the assembly preview).
- **`FReferenceFinder`** (the manifest builder's level scan) and **`STreeView` /
  `SExpanderArrow`** (the crafting tree).
- **`FScopedTransaction` / `FMessageDialog`** (CSV safety + Auto-tag) and **dynamic
  `SHeaderRow` columns** (the attachment matrix).
- **The runtime move** in `NexusAssemblyComponent.cpp` + new `NexusStatResolver.{h,cpp}` —
  if anything's off, the original fold is preserved verbatim inside `ApplyFold`.
- **`SComboBox` / `SWidgetSwitcher` / `SCheckBox` style name** (`"DetailsView.SectionButton"`,
  `"PrimaryButton"`) — style names fail soft (default look), never a build break.

Paste me any compiler error verbatim and I'll give you the exact fix.

## Extending it

New item template? Add an enum value in `NexusAssetCreationLibrary.h`, a `case` in
`CreateItem` (set the category tag + add fragments), a label in `TemplateLabel`, and one
entry in the `ItemTemplates` array in `SNexusCreatorWindow::Construct`. It shows up in the
Template dropdown automatically. New attachment type? Add one `MakeType(...)` entry to
`AttachmentTypes` in `Construct`.
