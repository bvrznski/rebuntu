# Rebuntu Phase Execution Contract

## Purpose
This is the canonical execution algorithm for every aggregate `.phases/phases/phase-*/TASK.md`.
A phase `TASK.md` is an **executable phase entrypoint**, not merely documentation or a progress report.

When an agent is told to execute a phase `TASK.md`, the instruction means: **execute the complete phase scope represented by that task, including every listed source prompt/subtask, subject only to explicit blockers that the agent cannot safely or technically resolve.**

## Instruction precedence
1. Repository/user instructions with higher authority.
2. `.phases/AGENTS.md`.
3. This `.phases/EXECUTION_CONTRACT.md`.
4. The selected phase `TASK.md` and its Subtask Coverage Ledger.
5. Source prompts/specifications referenced by that task, with later explicit amendments superseding conflicting earlier requirements.

A `TASK.md` may add phase-specific requirements but MUST NOT weaken this contract.

## Complete-phase execution algorithm
When executing a phase `TASK.md`, the agent MUST:

1. **Load governing instructions.** Read `.phases/AGENTS.md`, this contract, and the selected `TASK.md` completely before implementation.
2. **Resolve the entire scope.** Discover every prompt/specification/subtask belonging to the phase and reconcile that inventory with the task's Subtask Coverage Ledger. Missing, duplicate, or orphan ledger entries are defects to fix before claiming phase completion.
3. **Read every source subtask.** Do not implement from headings, summaries, requirement cues, maturity scores, or previous agent claims alone. Every listed source prompt is required scope.
4. **Build a requirement map.** For each subtask, identify its concrete requirements, amendments, acceptance conditions, dependencies, Native Authority boundaries, expected implementation destinations, and overlaps with other subtasks.
5. **Inspect before editing.** Inspect current `src/`, providers, tests, build files, callers, configuration, evidence and relevant history. Existing ledger claims are hypotheses to verify against repository reality.
6. **Classify each requirement.** Mark it as implemented, partial, structural-only, absent, superseded, not-applicable, or blocked. Skeletons/interfaces/TODOs/directories do not count as behavioral implementation.
7. **Implement the complete implementable scope.** Continue across all subtasks; do not stop after one successful change, one representative sample, or an arbitrary token-sized subset. Prefer saturation and aggregational morphing of canonical code over parallel subsystems.
8. **Respect Native Authority.** Linux mechanisms remain authoritative. Rebuntu adds typed semantics, composition, evidence, desired state, policy, planning, reconciliation, recovery and operator/automation behavior. Providers remain narrow typed translation boundaries.
9. **Integrate, do not merely add.** Wire implementations into canonical callers/build/runtime paths. Migrate callers before retiring superseded mechanics. Avoid unreachable implementations and phase-numbered runtime architecture.
10. **Exercise behavior.** Add or extend tests for normal paths and applicable failure, stale-state, verification, rollback/recovery, idempotence and boundary cases. Compile new C++20 code at least with `-std=c++20 -Wall -Wextra -Wpedantic -Werror` where practical.
11. **Record only observed evidence.** Never claim a test PASS, integration, runtime reachability or maturity increase that was not actually verified.
12. **Update every affected subtask ledger entry.** For each source subtask, record status/depth, implementation paths, test/evidence, remaining gaps, Native Authority assessment and blockers. Cross-phase changes require updating every affected phase task.
13. **Run phase-wide closure checks.** Reconcile the final repository against every source subtask and phase acceptance criterion. Run `.phases/tools/validate_phase_contracts.py` and other relevant integrity/build/test checks.
14. **Finish truthfully.** A run may finish with explicit BLOCKED/PARTIAL entries when a real blocker exists. It MUST NOT call the phase complete while silently leaving implementable subtasks uninspected or unfinished.

## No representative-subset completion
The following are explicitly invalid completion behaviors:
- implementing only the easiest or most visible prompts;
- stopping after a useful patch while other implementable subtasks remain;
- treating a directory/header/interface/TODO as implementation;
- assigning every subtask the aggregate phase maturity without evidence;
- marking prompts complete from filename/keyword similarity;
- skipping source prompts because the aggregate task contains a summary;
- replacing native Linux authorities with Rebuntu replicas for phase coverage;
- hiding unresolved work by deleting ledger entries.

## Completion semantics
A phase execution is **phase-complete** only when:
- every source subtask has been read and individually reconciled with repository reality;
- every applicable, implementable requirement is implemented and integrated;
- every subtask ledger entry contains concrete evidence or an explicit justified blocker/N/A state;
- applicable tests and acceptance checks have been executed and recorded;
- Native Authority and canonical architecture constraints are satisfied;
- no known implementable gap is silently deferred;
- the aggregate phase depth is evidence-consistent with `.phases/AGENTS.md`.

Making substantial progress is not the same as completing the phase.

## Agent handoff / continuation
If execution must stop because of a genuine external blocker or execution limit, leave the repository in a resumable state. The `TASK.md` must say exactly which subtasks were inspected, which were changed, what tests actually ran, what remains, and the next deterministic action. A later agent must be able to resume from the ledger without guessing.
