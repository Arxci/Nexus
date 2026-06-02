# NexusEditor module — content validator + dashboard

This is an **editor-only** module that adds two authoring tools, both driven by one
shared audit core (`FNexusContentAudit`):

- **Idea #2 — cross-asset validator** (`UNexusContentGraphValidator`): hooks into the
  editor's *Validate Assets* / validate-on-save / cook-time checks and flags problems a
  single asset can't see on its own — **duplicate identity tags** and **attachment
  `RequiredTags` that no attachment in the project provides**.
- **Idea #3 — content dashboard** (`SNexusContentDashboard`): a dockable window
  (**Tools → Nexus Content Dashboard**) with three tables: audit findings, items (with
  their resolved base `Stat.*` values), and attachments (provided/required/conflict tags
  + a per-row issue summary). Double-click any row to open the asset; **Refresh** re-runs
  the audit.

It lives in its own module (not the runtime `Nexus` module) because it links editor-only
modules (`UnrealEd`, `DataValidation`, `Slate`, `ToolMenus`) that must never ship in a
packaged build.

## Setup (one-time)

1. **Unzip at your repo root** so the files land under `Source/NexusEditor/...` and the
   updated `Source/NexusEditor.Target.cs` overwrites the old one.

2. **Register the module in your `.uproject`.** (Your `.uproject` isn't in the repo —
   it's gitignored — so I couldn't edit it.) Add a `NexusEditor` entry to the `Modules`
   array, alongside the existing `Nexus` entry:

   ```json
   "Modules": [
       {
           "Name": "Nexus",
           "Type": "Runtime",
           "LoadingPhase": "Default"
       },
       {
           "Name": "NexusEditor",
           "Type": "Editor",
           "LoadingPhase": "PostEngineInit"
       }
   ]
   ```

3. **Regenerate project files** (right-click the `.uproject` → *Generate Visual
   Studio / Rider project files*).

4. **Build the editor target.**

## Using it

- **Validator:** right-click an item/attachment (or a folder) → **Asset Actions →
  Validate Assets**, or enable *Project Settings → Editor → Data Validation → Validate on
  Save*. Duplicate identities and unsatisfiable attachment requirements fail validation.
  (This complements the per-asset `IsDataValid` checks from the first pass — those catch
  single-asset issues; this catches cross-asset ones.)
- **Dashboard:** **Tools → Nexus Content Dashboard**.

## Heads-up: this is untested editor C++

Unlike the first validation pass (a tiny, well-trodden API surface), this module is a few
hundred lines against editor/Slate APIs I couldn't compile here. Expect maybe one or two
small fixups for your exact engine version. The two most likely spots:

1. **Validator signatures** (`UNexusContentGraphValidator.h/.cpp`). These use the **UE
   5.4+** form (`CanValidateAsset_Implementation(const FAssetData&, UObject*,
   FDataValidationContext&)` etc.). On **5.3 and earlier** the signatures are the older
   `(UObject*)` / `(UObject*, TArray<FText>&)` forms — there's a comment in the header
   with the exact replacement if the build complains about `override`.
2. **A Slate style name or two** (e.g. the `"Brushes.Header"` brush or `"Bold"` font in
   `SNexusContentDashboard.cpp`). A wrong style key renders blank/default and logs a
   warning — it won't fail the build.

If a link error mentions a missing symbol, add the relevant module to
`PrivateDependencyModuleNames` in `NexusEditor.Build.cs`.

## Extending it

All the logic is in `FNexusContentAudit` (`Private/Audit/`). Add a check there, push a
`FNexusAuditFinding`, and it shows up in the dashboard automatically; expose it as a
focused helper and the validator can call it per-asset too. Ideas: weak-but-buyable
economy checks, recipes whose inputs/outputs reference deleted items, per-stat columns in
the items table instead of the single compact string.
