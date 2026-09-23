# `system` — primary structural package

The primary structural package of Rebuntu is **`system`** (not `rebuntu`).
Rebuntu is the *project*; `system` is the *structural package* that contains
its coherent parts. See `docs/discoveries/0001-primary-package-system.md`.

Taxonomy: **SYSTEM → MODULE → UNIT** (`docs/VOCABULARY.md`,
`docs/ONTOLOGY.md`). A **Module** is a substantial reusable functional
component; a **Unit** is a smaller identifiable unit of work/specification.

## Areas (reserved — NOT implemented in Phase 0.0)

| Area | Responsibility (reserved) |
|---|---|
| `core` | Foundational contracts & semantic primitives. **CURRENT** (see `cpp/include/system/core/`). |
| `shell` | Interactive command environment / shell-facing interface. |
| `runtime` | Runtime / execution foundation. |
| `state` | Authoritative state management. |
| `environment` | Host environment observation (native: procfs/sysfs/cgroups). |

**These are starting hypotheses** (Phase 0.1 "Structural Taxonomy"), not a fixed
tree. They may be merged, renamed, split, or omitted as evidence warrants.

> **A directory is not a capability.** None of these areas is implemented yet
> except the `core` contracts that already live in `cpp/`.

Note: the **directory** is `system`; the **C++ namespace** is `rebuntu::`
(see `docs/discoveries/0002-system-namespace.md`).
