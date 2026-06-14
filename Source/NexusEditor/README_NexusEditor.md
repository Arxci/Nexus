# NexusEditor — authoring, inspection & auditing suite

`NexusEditor` is the **editor-only** companion module to the runtime `Nexus`
module. It hosts the Nexus tool suite — asset creation, content auditing, and
the **API Reference** documentation browser — behind a single Workbench window
and a `Tools → Nexus` submenu.

It lives in its own module (never the runtime `Nexus` module) because it links
editor-only modules — `UnrealEd`, `Slate`, `ToolMenus`, `DataValidation`,
`PropertyEditor`, … — that must never ship in a packaged game build.

> **Wiring:** the module is part of the source tree and is loaded through
> `Source/NexusEditor.Target.cs` (`ExtraModuleNames` lists `NexusEditor`). There
> is **no** `.uproject` edit to make — regenerate project files and build the
> editor target and it's there. (Older copies of this README described a
> manual zip-and-register step; that no longer applies.)

## Opening the tools

- **Toolbar:** the **Nexus** split-button on the Level Editor toolbar. Primary
  click opens the **Workbench**; the drop-down lists every tool.
- **Menu:** **Tools → Nexus**, grouped into *Authoring*, *Inspection*, and
  *Auditing*.
- Every tool is also a tear-off **nomad tab**, so it can be docked anywhere.

The catalogue of tools is a single source of truth in
`Private/Shared/NexusEditorTools.cpp`; the menu, the toolbar drop-down, and the
Workbench sidebar all walk that list, so adding a tool is a one-place edit.

---

## API Reference (the documentation browser)

**Tools → Nexus → API Reference** (`SNexusDocsBrowser`). A designer-friendly,
auto-generated reference for every Nexus `UCLASS` / `UScriptStruct` and its
Blueprint-exposed surface. Nothing is hand-maintained: the tool walks the live
reflection database, so it can never drift from the code. Descriptions come from
the `/** doc comments */` UHT already harvests, which means **the reference is
exactly as good as the runtime code is documented** — and the header band tells
you, at a glance, what that coverage is.

### Layout

- **Header band** — title, a live coverage summary (`N types · M functions ·
  …% documented`), back/forward history, a *Show internal API* toggle, a
  *Refresh*, and **Export Markdown** (see below). Below it, a row of type-filter
  pills (All / Components / Subsystems / Libraries / Interfaces / Actors / …).
- **Left pane** — a debounced search box and a tree grouped by source folder
  (Combat, Inventory, Weapon, …). Each leaf carries a consistent coloured **type
  chip** (`COMP` / `SUB` / `STRUCT` / …) so the tree scans by colour. A `★
  Pinned` section floats favourites to the top.
- **Right pane** — a header card (display name, kind chip, parent / derived
  links, **Used By** callers, source path with *Open Source* + *Copy*), a
  **Summary** chip row that scrolls straight to a section, a per-class member
  quick-filter and sort toggle, and the **Functions / Events / Properties**
  rendered as cards with Blueprint-style signatures, badges (Pure / Callable /
  Event / Server / Latent / Static / Replicated / …), parameters, and returns.
- **Footer** — a collapsible **Reading Guide** explaining the chips and badges,
  plus shortcuts to the hand-written architecture docs under `<Project>/Docs`.

### Navigation & state

- Type names in *Inherits*, *Derived*, *Used By*, and on property cards are
  **clickable links** — chase a relationship without going back to the tree.
- **Pinned** types, **navigation history**, and the **last-viewed type** persist
  per-user (`GEditorPerProjectIni`, `[NexusWorkbench]`), so the tool reopens
  where you left off. The search box takes focus on open.
- **Refresh** re-walks the reflection DB — use it after recompiling C++.

### Export

**Export Markdown** writes the whole reference to a single committable file at
`Saved/NexusDocs/NexusAPIReference.md` (coverage summary, then a section per
category, then a sub-section per type with signatures, parameters, properties,
and events) and offers a *Show in folder* link. Use it to diff API changes in
review or publish a static reference. The generator
(`NexusDocs::ExportMarkdown`) is pure and deterministic.

### In-editor architecture-doc reader

The architecture notes in `<Project>/Docs/*.md` open **inline** in an editor
window, rendered by the small `NexusMarkdown` reader: ATX headings, ordered and
unordered (nested) lists, blockquotes, fenced code, horizontal rules, and inline
**bold** / *italic* / `code` / ~~strike~~ / links. It deliberately covers only
the subset those docs use and degrades gracefully on anything else.

---

## Other tools (one line each)

| Tool | Category | What it does |
|------|----------|--------------|
| **Asset Creator** | Authoring | Stamp items / attachments / recipes / manifests with templates and smart defaults. |
| **Assembly Preview** | Inspection | Resolved weapon stats across attachments and upgrade tiers. |
| **Crafting Tree** | Inspection | Recipes and their input / output dependency chains. |
| **Attachment Matrix** | Inspection | Provides / requires / conflicts compatibility grid. |
| **Inventory** | Inspection | Audit footprints and pack a real attaché case. |
| **Icon Sheet** | Inspection | Every item icon at its grid footprint, framed by category. |
| **Live Inventory** | Inspection | Inspect & drive the player's real inventory during PIE. |
| **Content Dashboard** | Auditing | Cross-asset audit findings + item / attachment tables. |
| **Tag Audit** | Auditing | Orphaned identity tags no asset references. |
| **Economy View** | Auditing | Value-per-cell balance sheet with outliers flagged. |
| **Content Insights** | Auditing | Reachability, scarcity, localization, where-used, buildability. |

The cross-asset validator (`UNexusContentGraphValidator`) also hooks the
editor's *Validate Assets* / validate-on-save / cook checks, flagging duplicate
identity tags and unsatisfiable attachment `RequiredTags`.

## Code map

| Area | Path |
|------|------|
| API Reference UI | `Private/Docs/SNexusDocsBrowser.{h,cpp}` |
| API Reference model (pure reflection walk + Markdown export) | `Private/Docs/NexusDocsModel.{h,cpp}` |
| Markdown reader (inline + block rendering) | `Private/Docs/NexusMarkdown.{h,cpp}` |
| Shared widget kit / style / persistence | `Private/Shared/NexusEditor*.h` |
| Tool registry (menu / toolbar / Workbench) | `Private/Shared/NexusEditorTools.cpp` |
| Module entry point + menus | `Private/NexusEditorModule.cpp` |

## Tests

Editor automation specs live under `Private/Tests/`. The documentation back end
is covered by `NexusDocsModelTests.cpp` — reflection-walk invariants (counter
consistency, name-cache round-trip, cross-reference symmetry), the Markdown
exporter, and the `NexusMarkdown::ToSlateMarkup` inline transform (escaping,
emphasis flanking, interleaved runs). Run them from **Tools → Test Automation**,
or:

```
Automation RunTests Nexus.Docs
```
