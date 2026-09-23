# Contributing to Rebuntu

## Read first

1. `AGENTS.md` — the binding engineering contract (for humans and agents).
2. `ARCHITECTURE.md` — the structural hypothesis and dependency direction.
3. `VOCABULARY.md` / `ONTOLOGY.md` — how terms and relationships are used.
4. `SAFETY.md` — the non-negotiable mutation/safety rules.
5. `DEVELOPMENT.md` — build, test, and phase workflow.

## The working style

- **REPOSITORY DISCOVERY IS PART OF IMPLEMENTATION.** Do not start by writing
  code. Search for existing Rebuntu capability, then existing Linux/native
  capability, then compose, then find the actual gap.
- Extend, compose, and refactor before creating parallel implementations.
- Implement the **smallest coherent missing abstraction** for a real need.
- Generalize only when evidence (two or more independent uses) justifies it.
- Prefer working implementation over scaffolding — but respect the current
  phase's scope.

## Making a change

1. Inspect `git status` and the relevant subtree; read applicable `AGENTS.md`.
2. Search for the capability you think is missing.
3. Record any architectural discovery in `docs/discoveries/`.
4. Implement, keeping the C++20 + CMake/CTest baseline and the dependency
   direction intact.
5. Add or update tests; build; run the relevant and full test suites.
6. Update documentation when architectural meaning changes.
7. Regenerate `__tree__.txt` if structure changed.
8. Review the full diff for accidental files, generated artifacts, and secrets.
9. Report honestly (COMPLETE / PARTIAL / BLOCKED).

## What we will not merge

- Duplicated implementations of existing capability.
- An OS-object inventory or cognitive-category reorganization.
- Shell as the runtime, or a presentation surface as a system controller.
- Secret material in code, logs, diffs, or test output.
- Unrelated refactors bundled with a change.
- A `src/` umbrella or a Python runtime for Rebuntu itself.
