# AGENTS.md — Rebuntu Phase Implementation Contract

## Scope
This file governs **all work under `.phases/` and every implementation pass derived from a phase specification**. It is mandatory. Phase prompts are the source specification; each phase `TASK.md` is a living implementation ledger and execution guide.


## Executable phase entrypoint contract
Every aggregate `.phases/phases/phase-*/TASK.md` is an **executable complete-phase entrypoint**. When an agent is instructed to execute one, it MUST also read and obey `.phases/EXECUTION_CONTRACT.md`. The complete set of source prompts/subtasks referenced by that task is mandatory execution scope, not optional documentation. The agent must inspect and classify every subtask, implement every currently implementable missing requirement, test and integrate the result, and update every affected subtask ledger entry. It MUST NOT stop after a representative subset merely because useful progress was made. Genuine blockers may remain only when they are explicit and evidenced.

`TASK.md` files inherit this behavior through their `PHASE_EXECUTION_CONTRACT` hook. They may add stricter phase-specific requirements but MUST NOT redefine, bypass, or weaken the canonical execution contract.

## Mandatory workflow
1. Before working on any phase, read this file completely.
2. Read that phase's `TASK.md` completely.
3. Read **all source prompts and architecture material referenced by the task**. Never implement from the task summary alone.
4. Inspect the current `src/`, tests, build integration and callers before changing code. Status in `TASK.md` is evidence to verify, not an excuse to skip inspection.
5. Implement into the canonical architecture under `src/`; never create runtime `phase_XX` trees.
6. Preserve useful existing implementation through **aggregational morphing**: classify responsibility, identify native authority, migrate semantics/callers, verify, then retire superseded mechanics. Do not create parallel replacement subsystems.
7. Rebuntu is **not a Linux reimplementation**. Kernel, systemd, cgroups, namespaces, procfs/sysfs, udev, D-Bus, Netlink, NetworkManager, nftables, PAM/NSS, polkit/sudo, package managers, filesystems, device/process/service mechanisms and schedulers remain native authorities. Providers are narrow typed boundaries. Rebuntu adds semantics, composition, evidence/provenance, desired state, policy/security integration, planning, verification, reconciliation, recovery, automation and operator coordination.
8. Skeletons, interfaces, TODOs, registries, phase-coverage tables and documentation are **not implementation evidence** by themselves.
9. Prefer concrete behavior, integration and tests. A feature is not complete merely because it compiles. Exercise success, failure, verification and recovery paths where applicable.
10. After **every implementation pass**, update every affected phase `TASK.md`: implementation evidence, test evidence, missing work, risks, architectural compliance and depth. If inspection disproves an old claim, lower its status.
11. When one change implements requirements from multiple phases, update all affected tasks.
12. Do not mark a phase 5/5 until all prompt requirements are implemented, integrated, verified, architecture-compliant, and relevant failure/recovery paths are covered.

## Depth scale
- **0/5 — Absent:** no meaningful implementation.
- **1/5 — Contract/Skeleton:** types/interfaces/scaffolding only.
- **2/5 — Partial:** concrete behavior exists but major requirements/integration are missing.
- **3/5 — Functional subsystem:** core behavior works; integration/coverage remains incomplete.
- **4/5 — Integrated + verified:** substantial prompt coverage, canonical integration and meaningful tests; closure gaps remain.
- **5/5 — Phase-complete:** every applicable requirement is implemented and verified, including failure/recovery and Native Authority compliance.

## Required TASK.md maintenance
Every phase task must always contain: source prompt locations; how to execute the phase; current depth; implemented/partial/missing requirements; concrete source/test evidence; native authorities/provider boundaries; integration dependencies; acceptance criteria; and an update log. Do not delete unresolved items to make progress appear higher.

## Structural translation-unit scaffolding
Generated `.cpp` pairing for skeleton headers is structural reachability only. A paired `.hpp`/`.cpp`, compile anchor, empty out-of-line definition, or successful aggregate skeleton compile MUST NOT be counted as behavioral implementation evidence and MUST NOT raise phase/subtask depth. Depth increases require prompt-derived behavior, canonical caller integration, and applicable verification evidence.

## Materialized Tree Preservation Contract (XXV)
The materialized repository tree is intentional architecture. Existing files and directories, including skeletal, currently unused, header-only, and translation-unit placeholders, MUST be preserved by default and implemented in place. An agent MUST NOT delete, collapse, prune, or replace them merely because they appear empty, redundant, unreferenced, over-granular, or not yet implemented. Prefer PRESERVE -> IMPLEMENT -> EXTEND -> MIGRATE; deletion is last and requires an explicit owning phase/subtask requirement or proof that the artifact is generated/transient build output. Misplaced architectural artifacts must be migrated with content preserved, not removed as cleanup. Structural skeletons still receive zero behavioral maturity credit until prompt-derived behavior and evidence exist.

## Subtask Structural Closure Contract (XXVI)
Every source prompt/subtask is now assigned explicit canonical implementation and structural test targets. These targets are architectural reservations: agents MUST preserve them and preferentially implement prompt-derived behavior in place rather than inventing parallel locations or deleting apparently redundant slots. A `SKELETON_MATERIALIZED` mapping gives zero behavioral maturity credit. Before changing a mapped target, read its source prompt and owning aggregate `TASK.md`; if responsibility truly belongs elsewhere, migrate/bridge content while preserving the mapping and record the canonical replacement in the ledger. Structural closure is validated by `.phases/tools/validate_subtask_structural_closure.py`.

## Prompt-Derived Subtask Package Contract (XXVII)
Each source prompt/subtask has a local structural package under its canonical phase subsystem. The package reserves prompt-derived responsibility slots such as contract, model, state, errors, evidence, verification and integration, plus conditional lifecycle/execution/recovery/persistence/policy/observability/concurrency/transaction/scheduling/resolution/planning/event slots when the prompt text indicates those concerns. These are intentional architectural reservations and MUST be preserved, implemented in place, or explicitly bridged/migrated with ledger evidence. They provide zero behavioral maturity credit until real prompt-derived behavior, integration and executed verification exist. Agents MUST NOT delete or collapse these packages merely because several aspects later share an implementation.
