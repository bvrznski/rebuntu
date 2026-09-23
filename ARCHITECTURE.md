# Rebuntu — Architecture (Phase 0.0)

> **Status legend used throughout this document and the repository:**
> - **CURRENT** — exists and works now (builds/tests green).
> - **RESERVED** — a structural location exists; no implementation yet.
> - **PLANNED** — committed to a future phase (see ROADMAP.md).
> - **CANDIDATE** — an architectural direction not yet committed.
> - **HISTORICAL** — from the prior Rebuntu (see `.phases/`, ARCHAEOLOGY.md).
>
> **Directories are not capabilities.** A reserved directory does not mean the
> feature it names is implemented.

## 1. Identity and positioning

Rebuntu is a **C++-native** system-management environment that operates on a
Linux host by **composing the platform's own mechanisms**. Its value is the
*coherent layer above* those mechanisms — observation, desired-state, policy,
verification, evidence, recovery — not reimplementation of what the kernel and
systemd already provide.

The dominant organization is **system-management mechanics**, not an inventory
of Linux nouns (`cpu/`, `disks/`, `network/`, …) and not cognitive categories
(`perception/`, `memory/`, …). Target domains are a **secondary classification
dimension**, represented by metadata/registries when justified (see §8).

## 2. Primary structural package: `system`

The primary structural package is **`src/system/`**. It contains the
coherent parts of Rebuntu (the *System* level of the taxonomy below).

Initial reserved areas (each a **Module**, none implemented in Phase 0.0):

| Area | Responsibility (reserved) |
|---|---|
| `system/core` | Foundational contracts and semantic primitives. **CURRENT** (see `cpp/`). |
| `system/shell` | Interactive command environment / shell-facing interface. |
| `system/runtime` | Runtime / execution foundation. |
| `system/state` | Authoritative state management. |
| `system/environment` | Host environment observation (native: procfs/sysfs/cgroups). |

These are **starting hypotheses** for the Phase 0.1 "Structural Taxonomy"
phase, not a fixed tree. They may be merged, renamed, split, or omitted as
evidence warrants. The historical spec `PHASES/0.1.md` is the authoritative
source of this taxonomy.

**`core` must never become "miscellaneous important code".** Core contains only
functionality whose absence would prevent the basic Rebuntu runtime/model from
existing coherently.

### 2.1 Directory name vs. C++ namespace

The **directory** is `system` (the structural package). The **C++ namespace**
is `rebuntu::` (e.g. `rebuntu::core`, `rebuntu::cli`). This separation is
deliberate and required: the identifier `system` **cannot** occupy the global
C++ namespace because `::system()` is a C function exposed to global scope by
`<cstdlib>`/`<stdlib.h>` (discovery `docs/discoveries/0002-system-namespace.md`).
Directory layout and language namespaces are orthogonal concerns.

## 3. Structural taxonomy — first-class directories

Rebuntu's structural taxonomy encodes *what kind of thing* something is, not
what it does or where it lives. Physical structure reflects **structural type**.

```
src/
├── system/         # primary package (System level)
│   ├── core/
│   ├── shell/
│   ├── runtime/
│   ├── state/
│   └── environment/
├── modules/        # reusable functional components
├── units/          # work/specification units
├── interfaces/     # typed contracts and protocols (NEW in 0.1)
├── adapters/       # native/external mechanism integration (NEW in 0.1)
└── support/        # reusable utilities (NEW in 0.1)
```

### System

A major coherent part of Rebuntu with broad responsibility, internal
organization, and lifecycle. The `system` package is the primary structural
package; it contains Modules.

### Module

A substantial reusable functional component belonging to or used by a System.
A Module may contain Units. A Module may implement Interfaces declared in
`interfaces/`.

### Unit (Phase 0.7)

**Phase 0.7 Update**: A bounded, independently identifiable Rebuntu definition
representing a discrete piece of executable or operational functionality that
may be invoked, activated, composed, scheduled, inspected and verified.

A Unit should normally have:
- **identity** (stable semantic identifier like "filesystem.copy")
- **purpose** (what it does)
- **inputs** (explicit contract for parameters)
- **outputs** (structured result, not just stdout strings)
- **contract** (preconditions, postconditions, side effects)
- **execution semantics** (how it runs: in-process, subprocess, Service IPC)
- **dependencies** (what it needs to run)
- **result semantics** (outcome, verification status, evidence)

A Unit should NOT simply mean:
- any class
- any function
- any file
- any directory
- any systemd unit (.service, .timer, etc.)
- any Service.

**DISTINCTION: REBUNTU UNIT != SYSTEMD UNIT**
- Rebuntu Unit = semantic/operational definition (what can be done)
- systemd Unit = process lifecycle/deployment artifact (how to run it)

A Rebuntu Unit may be implemented or activated through systemd, but they are
fundamentally different concepts.

*Category:* structural family (smallest structural level).
*Status:* CURRENT (ComponentKind::kUnit exists in cpp/include/system/core/contracts.hpp).

Unit relationships:
- A Module may contain or implement multiple Units.
- Task refers to a Unit as its implementation.
- Job is the concrete submitted/executing realization of work using a Unit.
- Workflow composes execution by invoking Units as steps.

**Distinction Summary (Phase 0.7)**:

| Concept | Relation to Unit |
|---------|-----------------|
| **systemd Unit** | Deployment artifact (.service, .timer, etc.). Rebuntu Unit may be implemented through systemd but they are fundamentally different concepts. |
| **Module** | Structural boundary that may contain Units. Do not create one Unit per Module automatically. |
| **Service** | Managed functionality with lifecycle semantics. A Service may expose or invoke Units. |
| **Daemon** | Persistent process role. A daemon may execute Units, but process persistence is irrelevant to Unit identity. |
| **Script** | Executable artifact. A Script may implement a Unit, but Unit identity is not determined by file type. |
| **Operation** | Contractual system action. Unit = execution definition; Operation = semantic contract (likely relation). |
| **Task** | Parameterized work specification. Task refers to Unit as its implementation (Unit is reusable; Task is parameterized). |
| **Job** | Runtime execution/submission of Task. Job is concrete; Unit is reusable definition. |
| **Workflow** | Composed execution. A Workflow may invoke Units but is not itself a Unit. |

Execution chain:
```
Unit (reusable definition) + parameters → Task → submit → Job → execute → Result
```

The execution mode is orthogonal to Unit identity — Units may be invoked in-process,
via subprocess, through Service IPC, or via systemd activation.

### Interface (NEW in 0.1)

A declared contract that consumers depend on. Interfaces contain no runtime
implementation. An Interface may be implemented by an Adapter or Module.
*Directory:* `src/interfaces/`

### Adapter (NEW in 0.1)

Connects Rebuntu to a specific external/native mechanism (systemd, procfs,
D-Bus). Adapters translate between Rebuntu's semantic vocabulary and the
underlying platform's API. Adapters implement Interfaces declared elsewhere.
*Directory:* `src/adapters/`

### Support (NEW in 0.1)

Provides cross-cutting, non-semantic functionality: logging, configuration,
validation, serialization. Support modules may be used by any other structural
type but must not depend on high-level semantics.
*Directory:* `src/support/`

### Forms Infrastructure (Phase 1.3)

Provides structured input layer for collecting installation/setup choices from humans,
CLI frontends, files or future interfaces without binding core installation logic to
interactive prompts.

**Structure:**
- `cpp/include/system/install/forms.hpp` - header-only implementation with:
  - `InputChannel` interface and concrete implementations (`InteractiveInputChannel`,
    `ConfigFileChannel`)
  - `FormParser` - type-aware parsing and validation
  - `FormBuilder` - fluent API for constructing form schemas
  - `InstallationFormFactory` - pre-built common forms

**Field types:** kString, kInteger, kBoolean, kEnum, kPath, kChoice, kMultiSelect  
**Validation levels:** kInfo, kWarning, kError

The forms infrastructure separates:
- question/presentation from raw user input
- raw user input from parsed values
- validated values from effective configuration
- configuration from policy constraints

*Status:* CURRENT (Phase 1.3 implementation complete)

All structural types above are **semantic levels**, not a mandate for exact
filesystem containment.

**Role ≠ structural type.** A word like `Monitor`, `Scheduler`, `Controller`
is usually a **role** that a module or service can *perform*, not a kind of
directory. Physical structure encodes strong structural distinctions; roles are
later represented by **metadata, registries, or classification** — not by
creating a directory per verb/noun. (Historical: `PHASES/0.1.md` §4.)

## 4. Dependency direction

The intended dependency flow is:

```
high-level mechanisms  (operations, workflows, automation)
        ↓
stable Rebuntu contracts  (core: Result/Outcome/Evidence, ComponentRegistry)
        ↓
interfaces / adapters / providers
        ↓
Linux / native / external facilities  (systemd, procfs, D-Bus, …)
```

### Allowed dependency directions

- **System** may depend on nothing (it's at the top)
- **Module** depends on: `system/core`, `interfaces/`
- **Unit** depends on: `modules/`, other `units/`
- **Interface** depends on: `core contracts` only
- **Adapter** depends on: `interfaces/`, `support/`, native mechanisms
- **Support** depends on: `core contracts` only

### Forbidden directions

- core depending on high-level application code;
- adapters owning business semantics (adapters isolate *mechanism*);
- interfaces containing runtime implementation;
- a semantic/ML component controlling system policy or authority;
- support modules depending on high-level semantics;
- `experiments/` becoming a dependency of production modules.

`ComponentRegistry` records these dependencies as **data** and validates
structural integrity (no duplicate ids, no unknown dependencies).

## 5. Operations, workflows, automation — distinct

- **Operation** — a contractual system-level change or query against a target,
  with inputs, preconditions, result, verification, and evidence.
- **Workflow** — a composition of **Phase → Stage → Step** describing execution
  flow toward an objective. **Thread** is *orthogonal* to this hierarchy (an
  independently progressing flow that may cross phases/stages and synchronize).
- **Automation** — a trigger + policy that *initiates* operations or workflows
  in response to events/conditions.

These are **CANDIDATE** semantics for now; none are implemented. The important
principle is fixed: **`COMMAND SUCCESS != OPERATION SUCCESS`** — an exit code of
zero is not evidence that the desired state was achieved. Operations return
explicit `Outcome`/`Result` with `Evidence`, and **verification** is a distinct
postcondition stage.

## 6. Control and desired state

- **Desired state** is what a policy/configuration *declares*.
- **Observed state** is what the host *actually is* (read from native sources).
- **Divergence/drift** is the difference. **Reconciliation** converges observed
  toward desired, **idempotently**, within policy constraints.

This is a **CANDIDATE** direction (historical: `PHASES/19.x`). It is *not*
implemented in Phase 0.0.

## 7. Observation, verification, recovery

- **Observation** produces **Facts** with **Evidence** (provenance-bearing,
  bounded, secret-free).
- **Verification** evaluates **postconditions** after an operation; it is how
  "completed" becomes "verified success".
- **Recovery** restores a prior good state using **checkpoint / rollback /
  quarantine** where the change is destructive or hard to reverse.

**Evidence is DATA, not CONTROL.** It informs but never confers authority.

## 8. Classification dimensions (not one tree)

Rebuntu concepts have multiple independent dimensions. At minimum:

- **A. Structural role** — system / module / unit / core / engine / provider /
  adapter / service.
- **B. Operational role** — observe / configure / coordinate / schedule /
  verify / recover / protect.
- **C. Target domain** — filesystem / process / service / package / network /
  storage / hardware / security.

Only the **dominant** dimension (structural) is encoded physically. The others
are represented **by metadata, manifests, registries, or schemas when
justified** — avoiding both "an encyclopedia of Linux objects" and "an abstract
taxonomy disconnected from implementation".

## 9. Semantic-processing boundary

A future **local semantic model** (Phase 0.1: CPU-only BitNet b1.58 2B4T) is a
**component at an explicit boundary**, not part of the deterministic core. The
anticipated pattern:

```
native events → deterministic observation → facts → assertions/conditions
  → deterministic correlation → compact InternalAlert
  → local semantic model → structured Assessment / EvidenceRequest
```

**Model output is NOT authority.** It may produce hypotheses, annotations, or
recommendations; it must never bypass canonical vocabulary, parsing, target
resolution, validation, policy, authorization, or verification. Raw event
streams should be reduced by deterministic mechanisms *before* any model
sees them. **This pipeline is NOT implemented in Phase 0.0**; the repository
structure must not make it awkward (see §10).

## 10. Provider / adapter principles

- **Adapter** — connects Rebuntu to a specific external/native mechanism
  (e.g. a systemd adapter, a procfs observer). It isolates *mechanism*.
- **Provider** — supplies an **interchangeable implementation** of a capability
  (e.g. a CPU-only BitNet provider, later a different model provider).

Native/Linux-specific code (procfs parsing, systemd calls, netlink, sysfs,
subprocess command parsing) is concentrated in adapters/providers, not scattered
across the repository — but **not** wrapped in a redundant abstraction for
abstraction's sake.

## 11. systemd / native-service doctrine

Rebuntu will contain real Linux services. Services must **not reinvent**
lifecycle, PID management, restart policy, ordering, watchdog, timers, socket /
path activation, cgroup placement, or journald integration when systemd already
provides them. `systemd/` holds Rebuntu-owned unit definitions; **none are
installed in Phase 0.0**. **Phase 0.1 introduces the first real service** (the
semantic LLM service). **Presentation surfaces (CLI/GUI) must never be
independent system controllers** — they express typed intent to the canonical
runtime.

## 12. Schemas / contracts strategy

Typed contracts and protocols (requests, responses, operations, evidence,
alerts, configuration, manifests, IPC) will live in **`schemas/`** as
repository-level artifacts, with the **semantic core contracts already present
in C++** (`cpp/include/system/core/`). Strategy: C++ is the authoritative owner
of runtime contracts; `schemas/` holds the exchange/protocol representations
(JSON-Schema / IDL) once a concrete protocol is needed. No speculative schemas
in Phase 0.0.

## 13. Native boundaries

| Concern | Native mechanism (beneath) |
|---|---|
| service lifecycle / control | systemd (D-Bus where appropriate) |
| process observation | procfs / appropriate kernel interfaces |
| resource control | cgroups v2 |
| device/hardware state | sysfs / udev |
| filesystem events | inotify / fanotify |
| network state/control | netlink |
| advanced observability | tracepoints / perf / eBPF (where justified) |
| logging | journald |

Document the native mechanism beneath each significant capability as it is
implemented.

## 14. Architectural evolution rules

1. **Real need → discover existing (Rebuntu, then Linux) → compose → find the
   actual gap → implement the smallest coherent missing abstraction → verify →
   document → reuse.**
2. **Generalize only when evidence justifies it** (two or more independent uses).
3. **Record architectural discoveries** in `docs/discoveries/` with a
   DISCOVERY / CANDIDATE / ACCEPTED / DEFERRED / REJECTED / SUPERSEDED
   disposition.
4. **Migrate to a fixed point**: when replacing an implementation, migrate all
   callers and remove the old one — do not leave two canonical implementations.
5. **Do not over-normalize terminology**; keep a Rebuntu term only if it expresses
   a distinct concept.
6. **Prefer working implementation over scaffolding** — but Phase 0.0 is
   deliberately a *structural* phase.

## 15. Structural vs Non-Structural Distinctions

| Dimension | Examples | Encoded in tree? |
|---|---|---|
| structural type | System, Module, Unit, Interface, Adapter, Support | YES (directories) |
| operational role | Monitor, Scheduler, Controller, Verifier | NO (metadata/registries) |
| target domain | filesystem, process, network, storage | NO (metadata/directives) |
| lifecycle state | created, started, stopped, failed | NO (runtime attribute) |

**Key principle**: Physical structure encodes *structural type*. Operational
roles, target domains, and lifecycle states are represented by metadata,
registries, or attributes—never by creating a directory per term.

## 16. Operational Architecture (Phase 0.2)

This phase establishes Rebuntu's operational grammar: how entities are
instantiated, activated, executed, controlled, and coordinated.

### Orthogonal State Dimensions

Entities have four independent state dimensions:

| Dimension | Values | Meaning |
|---|---|
| LifecycleState | created, initializing, ready, active, stopping, stopped, failed | stage of existence |
| WorkState | idle, processing, waiting, paused | current activity |
| HealthState | unknown, healthy, degraded, unhealthy | sustained quality |
| RecoveryState | none, retrying, rolling_back, restoring, repairing, failing_over | corrective action |

`ready() = (lifecycle == ready) AND (health == healthy)`.

### Specification vs Instance

- **Specification** — static declaration (TaskDefinition, ServiceConfig).
- **Instance** — runtime occurrence (Job, ServiceInstance).

### Execution Model

```
Request ─submit─▶ Job/Execution ─execute─▶ Result
                      │                  │
                 timeout?            verification?
                      │                  │
                   retry?          verified? ─yes──▶ Evidence
                                         no ──▶ Outcome (not verified)
```

- **Result** — structured outcome with value, status, evidence.
- **Outcome** — semantic conclusion: SUCCESS, FAILURE, PARTIAL, etc.
- **Execution success ≠ Verification success**: operation may complete but
  postconditions may fail verification.

### Retry & Timeout

- **RetryPolicy** — controls failure handling:
  - `max_attempts`: total attempts including initial
  - `exponential_backoff`: delay increases between attempts
  - `retryable_error_codes`: filter which errors trigger retry
- **TimeoutPolicy** — controls timeout behavior:
  - `operation_timeout`, `verification_timeout`
  - `cancel_on_timeout`

### Communication Patterns

| Pattern | Purpose |
|---|---|
| Request | Semantic request with operation, target, parameters, timeout |
| Event | Immutable statement that something occurred (evidence-backed) |
| Signal | Lightweight control indication (pause/resume/cancel/reconfigure) |
| Trigger | Activation decision when criteria are satisfied |

**Key distinctions:**
- `Request` ≠ `Event`: Request asks for action; Event reports occurrence.
- `Signal` ≠ `Event`: Signal is control; Event is observation.

### Native Linux Mappings

| Rebuntu Concept | Native Mechanism |
|---|---|
| LifecycleState transitions | systemd service state changes, kernel processes |
| Schedule (kOnce/kInterval/kCron) | systemd timers, cron, at |
| Event | inotify/fanotify (filesystem), udev (device), netlink (network) |
| Signal | D-Bus signals, Linux signals (for termination only) |
| Evidence | procfs/sysfs observations, systemd state queries |
| Condition evaluation | Custom logic over observed state |

### Current State (honest)

- **CURRENT:** repository skeleton; `src/system/` areas reserved; `cpp/` native
  foundation builds and tests green (`rebuntu` CLI + core contracts);
  Phase 0.2 runtime contracts implemented; all root documents;
  tooling (CMake/CTest, bootstrap/tree scripts); `.gitignore`.
- **RESERVED:** `system/{shell,runtime,state,environment}`; `interfaces/`,
  `adapters/`, `support/`, `modules/`, `units/`; `schemas/`, `packaging/`,
  `systemd/` (empty of units), `examples/`, `experiments/`, `tools/`.
- **PLANNED:** Phase 0.3 — Native System LLM Bootstrap (see ROADMAP.md).
- **CANDIDATE:** assertion/condition engine, desired-state reconciliation,
  InternalAlert pipeline, workflow/operation runtime.
- **HISTORICAL:** the prior Rebuntu corpus under `.phases/`.
