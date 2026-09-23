# Rebuntu — Roadmap (Phase 0.0)

Phases are intentionally sparse. Do **not** invent a long list of future
phases. Committed phases and candidate directions are kept separate.

## Committed

### Phase 3.6 — Container Runtime Contracts
**Status: COMPLETE.**

Generalizes container runtime contracts beyond Docker to support multiple
container runtimes (Docker, Podman, runc). Establishes a provider registry
pattern for multi-runtime support while maintaining backward compatibility with
Phase 3.5 Docker integration.

Key implementation:
- Generalized ContainerProvider interface in `cpp/include/system/infrastructure/container.hpp`
- Provider registry pattern for selecting available container runtime
- Unit tests for container contracts (9 tests, all passing)
- Header-only contracts following Rebuntu's existing patterns

See docs/PHASE_3.6_CONTAINER_RUNTIME_CONTRACTS.md for full details.

### Phase 1.11 — Lifecycle Management
**Status: COMPLETE.**

Lifecycle management operations for an existing Rebuntu installation:

- **RECONFIGURE**: Change configuration without reinstalling
  - `rebuntu reconfigure <key=value> [key2=value2...]`
  - Dry-run, verification, idempotency

- **REPAIR**: Restore Rebuntu-owned artifacts to correct state
  - `rebuntu repair [path1 path2...]`
  - Detects missing/wrong-type files
  - Skips user-modified files (no silent overwrites)

- **UPGRADE**: Version-aware migration between schema versions
  - `rebuntu upgrade <target-version>`
  - Placeholder for future migrations

- **UNINSTALL/PURGE**: Remove Rebuntu-owned artifacts
  - `rebuntu uninstall [--dry-run] [--force]` (standard mode)
  - `rebuntu purge [--dry-run]` (removes everything including user config)

### Phase 0.0 — Repository Architecture & Project Skeleton
**Status: COMPLETE.**
Establishes the repository skeleton, engineering contract (AGENTS.md),
vocabulary, ontology, safety, the C++20 foundation (builds + tests green), the
`system` primary structural package (reserved), tooling, and the discovery
mechanism. No system-management capability is implemented.

### Phase 0.1 — Native System LLM Bootstrap
**Status: PLANNED (next).**
The first real runtime subsystem and the first real service:

- a **CPU-only native system LLM service** based initially on
  **Microsoft BitNet b1.58 2B4T**;
- proper **Linux service** (systemd) — lifecycle, PID, restart, watchdog,
  journald integration delegated to systemd;
- a **model-provider abstraction** (Provider pattern) so the specific model is
  an interchangeable capability, not a hard dependency;
- configuration, IPC/protocol boundary, tests, and documentation.

Phase 0.1 must land inside the Phase 0.0 structure **without an architectural
exception** — specifically: a place for the semantic service
(`system/shell` or a dedicated area), a model provider, BitNet runtime
integration, configuration, IPC, the systemd unit, tests, and docs.

## Candidate directions (not committed)

These are *directions*, not phases. They become committed only when a real need
and evidence justify them:

- **Assertion / condition engine** — declarative relationships and combination
  over system state (facts → conditions → violations → alerts).
- **Desired-state reconciliation** — converge observed state toward desired
  state, idempotently, within policy.
- **InternalAlert pipeline** — deterministic correlation → compact internal
  structured message → local semantic model → structured Assessment.
- **Workflow / operation runtime** — Phase → Stage → Step composition and the
  operation lifecycle (discover → precheck → plan → execute → verify → report).
- **Automation** — trigger + policy that initiates operations/workflows.
- **Capability discovery** — the systematic "discover existing Rebuntu, then
  Linux, compose, find the gap" pipeline.

## Historical reference (not a roadmap)

The prior Rebuntu corpus under `.phases/` contains a full phase plan (0.0 →
20.20) and per-domain systems (5.x–45.x). That is **HISTORICAL** material: a
source of terminology, problems, and design ideas — **not** an authoritative
schedule and **not** implementation authority. See ARCHAEOLOGY.md.
