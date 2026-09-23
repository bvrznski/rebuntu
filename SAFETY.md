# Rebuntu — Safety (Phase 0.0)

Safety is foundational and binding. These rules constrain **all** future work,
including coding agents. Phase 0.0 itself performs **no system mutation**
outside the repository.

## Mutation rules

- **No unexpected deletion.** Never `rm -rf` arbitrary trees.
- **No broad deletion as architecture.** A misplaced file must be inspected and
  migrated, not deleted.
- **No filesystem reorganization** outside explicit task scope.
- **No modification of unrelated user data**, `/etc`, `/usr`, `/home` (outside
  the project), caches, or `/tmp`.
- **Prefer quarantine / checkpoint / backup** before destructive actions.
- **Inspect identity before operating on storage devices.**
- **Mutations should become increasingly transactional and verifiable.**
- **Privileged actions must be explicit**; privilege is a mechanism, not an
  authorization. `PRIVILEGE != AUTHORIZATION`.
- **Dry-run** should be considered for significant mutations.
- **Preserve evidence** during failure investigation.

## Verification rules

- **`COMMAND SUCCESS != OPERATION SUCCESS`.** An exit code of zero is not proof
  that the desired state was achieved. Verify postconditions; return explicit
  `Outcome` with `Evidence`.
- **Establish observable state and evidence BEFORE mutation** (BEFORE →
  DESIRED → ACTION → AFTER → VERIFICATION → EVIDENCE).
- **`UNKNOWN != FALSE != FAILED != PASS`.** Acquisition failure is not a
  negative observation.
- **`EXECUTION SUCCESS != VERIFIED SEMANTIC SUCCESS`.**

## Semantic / LLM rules

- **No raw LLM output directly becoming privileged execution.**
- **Model output is not authority.** It may produce hypotheses, annotations, or
  recommendations; it must not bypass validation, policy, authorization, or
  verification.
- **Data is not control.** Evidence and model output inform; they do not grant
  capability.

## Secret discipline

- **`SecretRef != SecretMaterial`.** Never place plaintext secrets in logs,
  diffs, prompts, model context, IPC traces, audit reports, error messages, or
  test output (except isolated synthetic test fixtures).
- Prefer references and controlled retrieval.

## Agent safety (binding)

- **REPOSITORY DISCOVERY IS PART OF IMPLEMENTATION.** Do not begin by writing
  code; search for existing capability first.
- No destructive cleanup, no unrelated refactors, no host-system changes.
- Distinguish discovery from implementation; document architectural
  discoveries; report incomplete work honestly.

## Phase 0.0 attestation

This phase creates only files/directories inside the repository, builds a
self-contained C++ foundation in `cpp/build/`, and runs its test suite. It does
not install packages, start services, modify `/etc`, require sudo, or touch host
state.
