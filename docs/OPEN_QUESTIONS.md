# Rebuntu — Open Architectural Questions (Phase 0.0)

Section 46 of the Phase 0.0 mandate requires these questions to be reasoned
about explicitly. An honest answer may be **"unresolved pending implementation
evidence."** This register records the disposition of each.

Statuses: **RESOLVED** (answer fixed, documented) · **RESOLVED-PRINCIPLE**
(direction fixed, owner deferred) · **UNRESOLVED** (pending evidence; do not
force an answer).

| # | Question | Status | Disposition |
|---|---|---|---|
| 1 | What is "core" allowed to contain? | RESOLVED | Only functionality whose absence prevents the basic runtime/model from existing coherently. Core is never "miscellaneous important code" (ARCHITECTURE §2). |
| 2 | What makes something an operation? | RESOLVED | A contractual target action with inputs, preconditions, outcome, verification, evidence. `Outcome`/`Result` fix the contract (cpp/include/system/core/contracts.hpp); the operation runtime is deferred (CANDIDATE). |
| 3 | Operation vs workflow? | RESOLVED | An Operation is one contractual action; a Workflow is a Phase→Stage→Step composition. An operation may be executed *within* a step; a workflow may contain many operations. (VOCABULARY, ONTOLOGY) |
| 4 | Automation vs workflow? | RESOLVED | Automation is a *trigger + policy* that initiates operations/workflows in response to events/conditions; a workflow is a declarative flow. Different relations: initiation vs composition. (VOCABULARY) |
| 5 | Where does policy live? | UNRESOLVED | Policy is *data that constrains* operations/automation. Owner module not yet justified (candidates: `system/state` or a control area). Revisit at first policy implementation. |
| 6 | Where does verification live? | RESOLVED-PRINCIPLE | Verification is a distinct postcondition stage turning "completed" → "verified success" (`Outcome::success` vs `completed`). The contract exists in core; verifiers are deferred with each operation. |
| 7 | Where does Linux-specific integration live? | RESOLVED-PRINCIPLE | Adapters/providers isolate mechanism (ARCHITECTURE §10, §13); no scattering of procfs/systemd/netlink code. |
| 8 | What belongs in adapters? | RESOLVED | Mechanism isolation: connecting Rebuntu to a specific native mechanism. Adapters never own business semantics. |
| 9 | What belongs in providers? | RESOLVED | Interchangeable implementations of a capability (e.g. a CPU-only BitNet provider in Phase 0.1). |
| 10 | Runtime state vs configuration? | RESOLVED | Configuration = variable specification applied at init (WITH WHAT); runtime state = authoritative runtime-owned data (future /var/lib class). Setup = WHERE. Never mixed (VOCABULARY; config/README). |
| 11 | What belongs in src vs cpp? | UNRESOLVED | `src/system/` = architectural ownership (areas + documentation); `cpp/` = buildable native code (headers, impl, tests, CMake). The precise future file division (e.g. where `system/shell` sources live) is pending first implementation evidence. |
| 12 | bin vs CLI code? | RESOLVED | `bin/` = thin dispatch only (`bin/rebuntu` execs the native binary). All CLI logic is in `cpp/src/cli.cpp`. |
| 13 | Where do cross-cutting contracts live? | RESOLVED | `cpp/include/system/core/` (`rebuntu::core`); exchange/protocol schemas later in `schemas/` (ARCHITECTURE §12). |
| 14 | How are architectural discoveries recorded? | RESOLVED | `docs/discoveries/` with DISCOVERY/CANDIDATE/ACCEPTED/DEFERRED/REJECTED/SUPERSEDED (docs/discoveries/README.md). |
| 15 | How does experimental functionality get promoted? | RESOLVED | experiment → evaluated result → architectural decision (discovery record) → production implementation. `experiments/` must never become a production dependency (experiments/README, CONTRIBUTING). |
| 16 | Domain classification vs functional architecture? | RESOLVED | Structural is the dominant physical dimension; target domain is a secondary dimension via metadata/registries/schemas when justified (ARCHITECTURE §8). |
| 17 | Code vs metadata vs registries? | RESOLVED-PRINCIPLE | Code = behavior/contracts; metadata = classification (role/domain); registries = structural relationships (`ComponentRegistry`). Concrete schemas deferred to first need. |
| 18 | Which questions stay unresolved? | RESOLVED | #5 and #11 are deliberately **UNRESOLVED pending implementation evidence**. Forcing an answer now would be over-normalization (Section 47). |

Additional unresolved vocabulary distinctions (VOCABULARY.md): **Engine vs
Module** (not separate structural kinds yet) and **Route vs Path** (no stable
distinction forced).

This register is a living document: UNRESOLVED items become RESOLVED when an
implementation provides the evidence, and the change is recorded in
`docs/discoveries/`.
